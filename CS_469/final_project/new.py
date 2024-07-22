def adaptive_threshold_detection(image, scale_factor=0.5):
    # Convert to grayscale if not already
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) if len(image.shape) > 2 else image

    # Calculate local standard deviation and adaptive threshold
    local_std = local_std_deviation(image)
    adaptive_threshold = local_std / np.mean(local_std) * scale_factor

    # Perform frequency analysis and calculate noise
    magnitude_spectrum = frequency_analysis(image)
    # we do the division to normalize the magnitude_spectrum
    noise = np.divide(magnitude_spectrum, local_std, out=np.zeros_like(magnitude_spectrum), where=local_std!=0)
    noise = (noise > adaptive_threshold).astype(int) # Thresholding that we set it to 1 if the noise is greater than the threshold
    # and 0 otherwise

    return noise

# from the result of the noise level assessment (noise map), we can determine the level of noise in the image and apply the appropriate noise reduction technique
# function to denoising the image

def denoise_image(image, noise_map):
    # Initialize the denoised image
    denoised_image = np.copy(image)

    # Iterate over the image pixels
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            # Define the size of the local region based on the noise level at the current pixel
            kernel_size = 5 if noise_map[i, j] == 1 else 3
            # Stronger denoising where noise is higher and we use kernel 5 for strong noise and 3 for weak noise
            # could chnage this
            d = kernel_size * 2 + 1  # Diameter for bilateral filter

             # Define the region to apply the filter
            min_i, max_i = max(0, i - kernel_size), min(image.shape[0], i + kernel_size + 1)
            min_j, max_j = max(0, j - kernel_size), min(image.shape[1], j + kernel_size + 1)

            # Apply bilateral filter to the local region
            local_region = image[min_i:max_i, min_j:max_j]
            local_denoised = cv2.bilateralFilter(local_region, d=d, sigmaColor=75, sigmaSpace=75)

            # Update the central pixel with the filtered result
            central_i = i - min_i
            central_j = j - min_j
            denoised_image[i, j] = local_denoised[central_i, central_j]

    return denoised_image

from skimage.metrics import structural_similarity

def calculate_metrics(original, denoised):
    # Calculate PSNR, specifying the range of pixel values
    data_range = original.max() - original.min()  # If range is not standard, calculate from images
    # Calculate SSIM
    ssim = structural_similarity(original, denoised, data_range=data_range)
    # the higehr it is the better the denoised images is but we need to be aware of over blurring

    return ssim

# do adaptive histogram equalization to improve the contrast and brightness of the image

def adaptive_histogram_equalization(image, contrastThreshold, gridSize):

    # Convert to grayscale if not already
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) if len(image.shape) > 2 else image
    assert img is not None, "file could not be read, check with os.path.exists()"

    # Create a CLAHE object (higher contrastThreshold means higher contrast variability)
    clahe = cv2.createCLAHE(contrastThreshold, gridSize)
    cl1 = clahe.apply(img)
    return cl1

# do edge detection to detect any scratches or defects on the image
def edge_detection(image, lowerThreshold, upperThreshold):

  # Convert to grayscale if not already
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) if len(image.shape) > 2 else image
    assert img is not None, "file could not be read, check with os.path.exists()"

  # Get edges using Canny edge detection, adjust threshold bounds as needed
    edges = cv2.Canny(img,lowerThreshold,upperThreshold)
    return edges

# Load and process the image
img = cv2.imread('noise_intro_2.jpg', cv2.IMREAD_GRAYSCALE)

if img is None:
    raise FileNotFoundError("The specified image path does not exist.")

scale_factors = [1, 10, 50, 80, 100, 150, 200]
for scale in scale_factors:
    noise_map = adaptive_threshold_detection(img, scale_factor=scale)
    denoised_image = denoise_image(img, noise_map)
    equalized_image = adaptive_histogram_equalization(denoised_image, 2.0, (8,8))
    edges = edge_detection(equalized_image,150,200)

    original = img.astype(np.float32)
    denoised = denoised_image.astype(np.float32)

    ssim = calculate_metrics(original, denoised)
    print(f"Scale Factor: {scale}, SSIM: {ssim}")

    # Create a figure with subplots
    fig, axes = plt.subplots(1, 4, figsize=(20, 5))

    # Display the original image
    axes[0].imshow(img, cmap='gray')
    axes[0].set_title('Original')
    axes[0].axis('off')

    # Display the denoised image
    axes[1].imshow(denoised_image, cmap='gray')
    axes[1].set_title(f'Denoised Image - Scale {scale}')
    axes[1].axis('off')

    # Display the equalized image
    axes[2].imshow(equalized_image, cmap='gray')
    axes[2].set_title(f'Equalized Image - Scale {scale}')
    axes[2].axis('off')

        # Display the equalized image
    axes[3].imshow(edges, cmap='gray')
    axes[3].set_title(f'Edges - Scale {scale}')
    axes[3].axis('off')

    # Ensure equal aspect ratio for all axes
    for ax in axes:
        ax.set_aspect('equal')

        


    plt.show()


