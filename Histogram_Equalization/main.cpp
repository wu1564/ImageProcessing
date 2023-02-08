#include "Histogram.h"

const string fileName = "photo_dark.jpg";

int main() {
	Mat inputImage;
	Histogram functionTest, testMyFunction;

	inputImage = imread(fileName, IMREAD_GRAYSCALE);			// load image
	resize(inputImage, inputImage, Size(600, 800), 0, 0, INTER_LINEAR);	// resize the image
	imshow("Original Image", inputImage);									// show the image
	testMyFunction.loadImage(inputImage);						// load the image
	testMyFunction.showHistogram("Original");					// show the histogram of the darker image
	inputImage = testMyFunction.equiHist();						// do the histogram Equalization
	testMyFunction.showHistogram("My Equalization");			// show the image after doing histogram Equalization
	imwrite("Equalization.jpg", inputImage);

	// using function to verify
	/*
	equalizeHist(inputImage, inputImage);
	functionTest.loadImage(inputImage);
	functionTest.showHistogram("Funtion Equalization");
	imshow("FUC_EQ", inputImage);
	*/
	waitKey(0);
}
