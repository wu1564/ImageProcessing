#include "Histogram.h"

Histogram::Histogram() {

}

Histogram::Histogram(Mat image) {
	this->image = image.clone();
}

void Histogram::loadImage(string filePath) {
	this->image = imread(filePath, IMREAD_GRAYSCALE);	// read the gray scale image
}

void Histogram::loadImage(Mat image) {
	this->image = image.clone();	// get the image 
}

void Histogram::showHistogram(string imageName) {
	Mat his(image.rows, 256, CV_8UC1, Scalar(0));

	if (image.empty()) {
		cout << "\nImage is empty.\n";		// judge if the image is empty or not
		return;
	}
	memset(record, 0, sizeof(record));		// initialize the frequency record
	for (int i = 0; i < image.rows; ++i) {		// start to record the frequency of gray scale value
		for (int j = 0; j < image.cols; ++j) {
			record[image.at<uchar>(i,j)]++; 
		}
	}
	for (int i = 0; i < 256; ++i) {		// draw the histogram with multiple lines in a image
		if (record[i]/50 > image.rows) {
			line(his, Point(i, image.rows), Point(i, 0), Scalar(255), 1);
		} else {
			line(his, Point(i, image.rows), Point(i, image.rows - (int)record[i]/50), Scalar(255), 1);
		}
	}
	imshow(imageName, his);			// show the image of the histogram
}

// not be used
void Histogram::drawHistogram(unsigned int *in) {
	static int times = 0;
	Mat his(image.rows, 256, CV_8UC1, Scalar(0));	// initial the image

	for (int i = 0; i < 256; ++i) {
		int temp = in[i] / 50; // compressed the value to show the histogram
		if (temp > image.rows) {
			line(his, Point(i, image.rows), Point(i, 0), Scalar(255), 1);		// draw multiple lines
		} else {
			line(his, Point(i, image.rows), Point(i, image.rows - temp), Scalar(255), 1);
		}
	}
	imshow("Draw" + to_string(times), his);
	times++;
}

Mat Histogram::equiHist() {
	Mat newImage(image.rows, image.cols, CV_8UC1, Scalar(0));	// initialize the gray scale image
	vector<unsigned int> indexTemp;
	unsigned int num = 0;
	int index = 0;
	
	for (int i = 0; i < 256; ++i) {								// calculate the q0 ~ q255
		num += record[i];										// accumulate the num to calculate the q
		indexTemp.push_back(255 * num / (image.rows * image.cols));	// calculate the q
	}
	for (int i = 0; i < image.rows; ++i) {						// change the gray scale image value to the q number
		for (int j = 0; j < image.cols; ++j) {
			newImage.at<uchar>(i, j) = indexTemp[image.at<uchar>(i, j)];
		}
	}
	image = newImage.clone();									// copy new image to the original image
	imshow("MY_EQ_HIST", newImage);								// show the image to check the result
	return image.clone();
}

Histogram::~Histogram() {

}
