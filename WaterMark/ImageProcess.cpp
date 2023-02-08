#include "ImageProcess.h"

Mat ImageProcess::getOriginal() {
	return originalImage;
}

Mat ImageProcess::getGrayImage() {
	return grayImage;
}

void ImageProcess::convertGrayImage(const Mat inputImage) {
	if (inputImage.channels() == 1) return;
	cvtColor(inputImage, grayImage, CV_RGB2GRAY);
}

void ImageProcess::showImage() {
	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", originalImage);
}

void ImageProcess::showGrayImage() {
	namedWindow("GRAY", WINDOW_AUTOSIZE);
	imshow("GRAY", grayImage);
}

void ImageProcess::loadImage(const Mat inputImage) {
	originalImage = inputImage.clone();
}

void ImageProcess::loadImage(string fileDir) {
	originalImage = imread(fileDir, IMREAD_COLOR);
}

void ImageProcess::loadGray(const Mat inputImage) {
	grayImage = inputImage.clone();
}

Mat ImageProcess::grayThrowBits(const Mat inputImage, int bitIndex) {
	Mat temp = inputImage.clone();

	if (bitIndex > 8 || inputImage.channels() != 1) {
		cout << "Warning !!! The input is not Gray Level";
		return inputImage.clone();
	}
	for (int i = 0; i < inputImage.rows; ++i) {		// go through all pixel and set each pixel's some bits zero
		for (int j = 0; j < inputImage.cols; ++j) {
			for (int k = 0; k < bitIndex; ++k) {
				bitSet(temp.at<uchar>(i, j), k, 0);
			}
		}
	}
	return temp.clone();
}

void ImageProcess::bitSet(unsigned char& pixel, int bitIndex, bool number) {
	if (bitIndex > 8) return;
	if (number) {
		pixel |= (1 << bitIndex);					// using or operation and and operation to change the bit of each pixel
	} else {
		pixel &= ~(1 << bitIndex);
	}
}

void ImageProcess::char2binary(unsigned char pixel) {
	for (int i = 7; i >= 0; --i) {
		cout << (char)(((pixel & (1 << i)) >> i) + '0');	// to show the binay of pixel's value from MSB to LSB
	}
	cout << " ";
}

ImageProcess::~ImageProcess() {	// destructer
	originalImage.release();
	grayImage.release();
}

bool ImageProcess::getBit(Mat inputImage, int row, int col, int bitIndex, int channel, bool grayLevel) {
	unsigned char temp;
	if (col > inputImage.rows || col > inputImage.cols) return 0;
	if (grayLevel) {
		temp = inputImage.at<uchar>(row, col);				// to get the specific image's pixel value bit
	} else {
		temp = inputImage.at<Vec3b>(row, col)[channel];
	}
	return  (bool)((temp & (1 << bitIndex)) >> bitIndex);
}

Mat ImageProcess::waterMark(string fileDir, int concateBitNum, int waterMarkChannel, bool grayLevel) {
	Mat temp;
	Mat embedImage;

	if (grayLevel) {
		temp = grayImage.clone();							// load two kind of data, RGB and gray scale image respectedly
		embedImage = imread(fileDir, IMREAD_GRAYSCALE);
		waterMarkChannel = 1;
		resize(embedImage, embedImage, Size(temp.cols, temp.rows), 0, 0, INTER_LINEAR);	// resize the embed image as same as the size of the original image
	} else {
		temp = originalImage.clone();
		embedImage = imread(fileDir, IMREAD_COLOR);
		resize(embedImage, embedImage, Size(temp.cols, temp.rows), 0, 0, INTER_LINEAR);
	}
	cout << embedImage.cols << " " << embedImage.rows << endl;
	cout << temp.cols << " " << temp.rows << endl;
	//imshow("sdf", embedImage);
	
	if (concateBitNum > 8) return originalImage;
	for (int i = 0; i < originalImage.rows; ++i) {				// this function can adjust how many bits we wanna get from the embedded image to put into the origion iamge
		for (int j = 0; j < originalImage.cols; ++j) {			// and can choose embedd grays scale or RGB image and if the input image is RGB it can adjust different channel's data
			for (int q = 0; q < waterMarkChannel; ++q) {
				for (int k = 0; k < concateBitNum; ++k) {
					if (grayLevel) {
						bitSet(temp.at<uchar>(i, j), k, getBit(embedImage, i, j, 8 - concateBitNum + k, q, grayLevel));	// set new image from embedd image
					} else {
						bitSet(temp.at<Vec3b>(i, j)[q], k, getBit(embedImage, i, j, 8 - concateBitNum + k, q, grayLevel));
					}
				}
			}
		}
	}
	return temp.clone();
}

// it can choose the gray scale image or RGB image to reduct the image
Mat ImageProcess::reductWaterMark(const Mat inputImage, int bitIndex, bool grayLevel) {
	Mat reductImage = inputImage.clone();
	unsigned char mask = 0x0, temp;

	for (int i = 0; i < bitIndex; ++i) {
		bitSet(mask, i, 1);
	}
	char2binary(mask);
	cout << "\n";
	if (bitIndex > 8 || !bitIndex) return inputImage;
	for (int i = 0; i < inputImage.rows; ++i) {
		for (int j = 0; j < inputImage.cols; ++j) {
			if (grayLevel) {
				if (inputImage.channels() != 1) return inputImage;	// prevent the RGB image to conduct the process of the gray scale image
				temp = inputImage.at<uchar>(i, j);
				reductImage.at<uchar>(i, j) = (temp & mask) << (8 - bitIndex);
			} else {
				if (inputImage.channels() < 3) return inputImage;	// prevent the gray image to conduct the process of RGB image
				for (int k = 0; k < 3; ++k) {
					reductImage.at<Vec3b>(i, j)[k] = ((inputImage.at<Vec3b>(i, j)[k]) & mask) << (8 - bitIndex);
				}
			}
		}
	}
	return reductImage.clone();
}
