// Name: Uyen Tran
// Project 9 CS 326
/*Note: For the images, the pdf did not specify how the svg file content look like/ content of it
so i just leave it with the content i scraped and i use src to get the images
The pdf did not ask to check error or specify how it will be format so i did the way that more convenient for me.
I also remove duplicate images links, external links and images and make svg file to be only 1 file (uppercase)
The order of txt file could be change little bit because i have to remove duplicate links and images
I also have data-src to scrape images and replace the src to get the images due to the fact that it not
work before, but it currently work so i just use src to get the images.
So if you need more pics or all pics, you could also include data-src to get the images
I probably have more images due to inlcude svg file.
*/
package main

//some libraries
import (
	"fmt"
	"golang.org/x/net/html"
	"io"
	"net/http"
	"os"
	//"path"
	"strings"
	"time"
)

// function getLinks() to get all external links from the html
func getLinks(n *html.Node) []string {
	var links []string
	//check if the node is an anchor tag and the link is external
	if n.Type == html.ElementNode && n.Data == "a" {
		//loop through the attributes of the anchor tag
		for _, a := range n.Attr {
			//check if the attribute is the href
			if a.Key == "href" {
				//if the link is not relative or absolute, then it is an external link
				if strings.HasPrefix(a.Val, "http") || strings.HasPrefix(a.Val, "www") {
					links = append(links, a.Val)
				} //else {
				//we will need to reformat the relative links to absolute links
				//fmt.Println("relative link: ", a.Val)
				//}
				//links = append(links, a.Val)
			}
		}
	}

	// recursively call getLinks() to get all external links from the html
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		links = append(links, getLinks(c)...)
	}
	return links
}

// go routine to get the external links from each url in the urlList[] by calling getLinks()
// and then sending the links to the channel foundUrls to be written to the file foundUrls.txt
func getExternalLinks(urlList []string, foundUrls chan string) {
	//loop through the urlList
	for _, url := range urlList {
		//get the response from the url
		resp, err := http.Get(url)
		if err != nil {
			fmt.Println(err)
		}
		//close the response
		defer resp.Body.Close()
		//parse the response
		doc, err := html.Parse(resp.Body)
		if err != nil {
			fmt.Println(err)
		}
		//get link
		links := getLinks(doc)
		// send the links to the channel foundUrls
		for _, link := range links {
			foundUrls <- link
		}
	}
	close(foundUrls)
}

// function to remove duplicate links in the foundUrls.txt
func removeDuplicateLinks() {
	//open the file
	f, err := os.Open("foundUrls.txt")
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()

	//make a map to store the links
	linksMap := make(map[string]bool)
	//make a slice to store the links
	var links []string
	//read the file
	var line string
	for {
		//read the file line by line
		_, err := fmt.Fscanln(f, &line)
		//read the file until the end of the file
		if err == io.EOF {
			break
		}
		//check if the link is already in the map
		if _, ok := linksMap[line]; !ok {
			//if not, then put the link into the map
			linksMap[line] = true
			//and put the link into the slice
			links = append(links, line)
		}
	}

	//open the file
	f, err = os.Create("foundUrls.txt")
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()

	//write the links to the file
	for _, link := range links {
		f.WriteString(link + "\r\n")
	}
}

// function to write the external links to the file foundUrls.txt
func writeLinksToFile(foundUrls chan string) {
	//open the file
	f, err := os.Create("foundUrls.txt")
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()

	//check if the string is already in the file
	//if not, then write the string to the file
	//if yes, then do not write the string to the file
	var str string
	for link := range foundUrls {
		if str != link {
			str = link
			f.WriteString(link + "\r\n")
		}
	}
	//close the file
	f.Close()
}

// function getImagesLink() to get all images from the html
// make sure to get the full path of the image
func getImagesLink(n *html.Node) []string {
	//make a slice to store the images
	var images []string
	//check if the node is an image
	if n.Type == html.ElementNode && n.Data == "img" {
		//loop through the attributes of the image
		for _, a := range n.Attr {
			//check if the attribute is the src
			/*if a.Key == "data-src" {
				images = append(images, a.Val)
			}*/
			if a.Key == "src" {
				images = append(images, a.Val)
			}
		}
	}

	// recursively call getLinks() to get all external links from the html
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		images = append(images, getImagesLink(c)...)
	}
	return images
}

// function to get all of the images from each url in the urlList[] by calling getImagesLink()
// and then sending the images to the channel foundImages to be written to the file foundImages.txt
func getImages(urlList []string, foundImages chan string) {
	//loop through the urlList
	for _, url := range urlList {
		//get the response from the url
		resp, err := http.Get(url)
		// if it not return 200, then skip the url
		if err != nil {
			fmt.Println(err)
		}
		//close the response
		defer resp.Body.Close()
		//parse the response
		doc, err := html.Parse(resp.Body)
		if err != nil {
			fmt.Println(err)
		}
		//get link
		images := getImagesLink(doc)
		//it will need to join the url and the image path
		for _, image := range images {
			//get the full path of the image
			fullImagePath := joinUrlAndImagePath(url, image)
			// send the images to the channel foundImages
			foundImages <- fullImagePath

		}
	}
	close(foundImages)
}

// function to write the images to the file foundImages.txt with full path
// then return list of images with full path
func writeImagesToFile(foundImages chan string) []string {
	//make a slice to store the images with full path
	var images []string
	//open the file
	f, err := os.Create("foundImages.txt")
	if err != nil {
		fmt.Println(err)
	}
	//close the file
	defer f.Close()

	//write the the file and put the images into an array
	for image := range foundImages {
		f.WriteString(image + "\r\n")
		images = append(images, image)
	}

	//close the file
	f.Close()
	return images
}

// function to join the url and the image path
// the return path should look like this: http://www.example.com/images/image1.jpg
func joinUrlAndImagePath(url string, imagePath string) string {
	//get the base url
	baseUrl := getBaseUrl(url)
	//check if imagePath has / at the beginning
	//if not, then add / to the beginning of the imagePath
	//if yes, then do nothing
	if !strings.HasPrefix(imagePath, "/") {
		imagePath = "/" + imagePath
	}
	//join the base url and the image path
	joinedUrl := baseUrl + imagePath
	return joinedUrl
}

// function to get the base url
func getBaseUrl(url string) string {
	//split the url into an array
	urlArray := strings.Split(url, "/")
	//get the base url
	baseUrl := urlArray[0] + "//" + urlArray[2]
	return baseUrl
}

// goRountine function to download the images that passed in the images[] slice
// make a folder called images and save the images in the folder
func downloadImages(images []string) {
	//make a folder called images
	os.Mkdir("imagesUT", 0777)
	//download the images
	for _, image := range images {
		//get the image name
		imageName := getImageName(image)
		downloadImage(image, imageName)
	}
}

// function to get the image name, it should stop if it found common image extensions
// the image name should look like this: image1.jpg instead of image1.jpg?w=300 due to the query string
func getImageName(image string) string {
	//split the image into an array
	imageArray := strings.Split(image, "/")
	//get the last element of the array
	imageName := imageArray[len(imageArray)-1]
	//check if the imageName has a query string
	//if yes, then remove the query string
	//if no, then do nothing
	if strings.Contains(imageName, "?") {
		imageName = strings.Split(imageName, "?")[0]
	}
	return imageName
}

// function to download the image and save it in the images folder
func downloadImage(image string, imageName string) {
	//get the image
	resp, err := http.Get(image)
	if err != nil {
		fmt.Println(err)
	}
	defer resp.Body.Close()
	//check to see if we can get the image or not
	//if not then error out and not download the image
	if resp.StatusCode != http.StatusOK {
		fmt.Println("Error on ", resp.StatusCode)
		//print the image that we cannot get
		fmt.Println(imageName)
		return
	}

	//check to see if the image is .svg or not
	//if it is .svg then download it but make sure the name will be all uppercase
	//if it is not .svg then download it with the original name
	if strings.Contains(imageName, ".svg") {
		//make the name all uppercase
		imageName = strings.ToUpper(imageName)

		//create the file
		f, err := os.Create("imagesUT/" + imageName)
		if err != nil {
			fmt.Println(err)
		}
		defer f.Close()

		//copy the image to the file
		_, err = io.Copy(f, resp.Body)
		if err != nil {
			fmt.Println(err)
		}
	} else {

		//create the file
		file, err := os.Create("imagesUT/" + imageName)
		if err != nil {
			fmt.Println(err)
		}
		defer file.Close()

		//copy the image to the file
		_, err = io.Copy(file, resp.Body)
		if err != nil {
			fmt.Println(err)
		}
	}
}

// function to remove the duplicate images from the images slice and the foundImages.txt file
func removeDuplicates(images []string) {
	//make a map to store the images
	imageMap := make(map[string]bool)
	//make a slice to store the unique images
	var uniqueImages []string
	//loop through the images slice
	for _, image := range images {
		//check if the image is in the map
		//if yes, then do nothing
		//if no, then add the image to the map and the uniqueImages slice
		if !imageMap[image] {
			imageMap[image] = true
			uniqueImages = append(uniqueImages, image)
		}
	}
	//open the file
	f, err := os.Create("foundImages.txt")
	if err != nil {
		fmt.Println(err)
	}
	//close the file
	defer f.Close()

	//write the the file and put the images into an array
	for _, image := range uniqueImages {
		f.WriteString(image + "\r\n")
	}

	//close the file
	f.Close()
}

func main() {
	urlList := []string{
		"https://www.unlv.edu/cs",
		"https://www.unlv.edu/engineering",
		"https://www.unlv.edu/engineering/advising-center",
		"https://www.unlv.edu/engineering/about",
		"https://www.unlv.edu/engineering/academic-programs",
		"https://www.unlv.edu/ceec",
		"https://ece.unlv.edu/",
		"https://www.unlv.edu/me",
		"https://www.unlv.edu/rotc",
		"https://www.unlv.edu/afrotc",
		"https://www.unlv.edu/eed",
		"https://www.unlv.edu/engineering/mendenhall",
		"https://www.unlv.edu/engineering/uas",
		"https://www.unlv.edu/engineering/solar",
		"https://www.unlv.edu/engineering/techcommercialization",
		"https://www.unlv.edu/engineering/railroad",
		"https://www.unlv.edu/engineering/future-students",
		"https://www.physics.unlv.edu/",
	}

	start := time.Now()

	fmt.Printf("Start the web scrape program:\n\n")
	//call go routine to get the external links from each url in the urlList[] by calling getLinks()
	//and then sending the links to the channel foundUrls to be written to the file foundUrls.txt
	foundUrls := make(chan string)
	go getExternalLinks(urlList, foundUrls)

	//call function to write the external links to the file foundUrls.txt
	writeLinksToFile(foundUrls)

	//remove the duplicate links from the foundUrls.txt file
	removeDuplicateLinks()

	//call go routine to get the images from each url in the urlList[] by calling getImages()
	//and then sending the images to the channel foundImages to be written to the file foundImages.txt
	foundImages := make(chan string)
	go getImages(urlList, foundImages)

	//call function to write the images to the file foundImages.txt and get the images with full path
	images := writeImagesToFile(foundImages)

	//remove the dupliacates links in the images[] slice and foundImages.txt
	removeDuplicates(images)

	//call function to download the images from the urlList[] and save them to the folder images
	downloadImages(images)

	elapsed := time.Since(start)
	fmt.Printf("\n\nDownloads completed in %s \n", elapsed)
}
