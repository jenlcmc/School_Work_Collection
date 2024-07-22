def histogram_analysis(image):
    """Calculate and analyze the histogram of the image."""
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])
    hist_normalized = hist.ravel() / hist.sum()
    return hist_normalized

# function to calculate entropy of an image that we use to detrmine the noise type 
def calculate_entropy(image):
    # Calculate the histogram
    hist = histogram_analysis(image)

    # Calculate the entropy
    entropy = -np.sum(hist * np.log2(hist + 1e-10))

    return entropy

def calculate_variance_std(image):
    """Calculate the variance and standard deviation of the image."""
    variance = np.var(image)
    std_deviation = np.std(image)
    return variance, std_deviation

import scipy.stats as sp

def calculate_skewness(image):
    """Calculate skewness of the image."""
    skewness = sp.skew(image.ravel())
    return skewness

# func to calculate fourier transform of the image
def calculate_fourier_transform(image):
    # Calculate the 2D Fourier transform of the image
    fourier_transform = np.fft.fft2(image)

    # Shift the zero frequency component to the center
    fourier_transform_shifted = np.fft.fftshift(fourier_transform)

    # Calculate the magnitude spectrum
    magnitude_spectrum = 20 * np.log1p(np.abs(fourier_transform_shifted))

    # Normalize the magnitude spectrum
    magnitude_spectrum -= np.min(magnitude_spectrum)
    magnitude_spectrum /= np.max(magnitude_spectrum)

    return magnitude_spectrum

# add noises to folder of images to use it to do the noise level assessment
"""list_noise_types = [
        'Rayleigh_Noise',
        'Erlang_Gamma_Noise',
        'Exponential_Noise',
        'Uniform_Noise',
        'Periodic_Noise', x 
        'Gaussian_Noise',
        'Salt_and_Pepper_Noise', x
        'Speckle_Noise', x
        'Poisson_Noise',
    ]
"""

# use all the above functions to do noise level assessment
def noise_level_assessment(image):
    # Calculate the entropy of the image
    entropy = calculate_entropy(image)

    # Calculate the variance and standard deviation of the image
    variance, std_deviation = calculate_variance_std(image)

    # Calculate the skewness of the image
    skewness = calculate_skewness(image)

    # Calculate the 2D Fourier transform of the image
    magnitude_spectrum = calculate_fourier_transform(image)

    # show graph or the histogram of the image
    plt.hist(image.ravel(), 256, [0, 256])
    plt.show()
    