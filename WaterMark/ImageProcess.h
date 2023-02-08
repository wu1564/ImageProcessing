#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <math.h>
#include <string>

using namespace cv;
using namespace std;

class ImageProcess {
	public:
		Mat grayThrowBits(const Mat inputImage, int bitIndex);	// throw the lowest bits from original image
		Mat getOriginal();										// copy a original image from this class
		Mat getGrayImage();										// copy a gray image from this class
		Mat waterMark(string fileDir, int concateBitNum, int waterMarkChannel, bool grayLevel); // embedd watermark 
		Mat reductWaterMark(const Mat inputImage, int bitIndex, bool grayLevel);				// reduct watermark
		void loadImage(string fileDir);							// load original image from direction
		void loadImage(const Mat inputImage);					// load original image Mat type
		void loadGray(const Mat inputImage);                    // load gray scale image from Mat type
		void convertGrayImage(const Mat inputImage);			// convert gray image
		void showImage();										// show the image
		void showGrayImage();									// show the gray image
		bool getBit(Mat inputImage, int col, int row, int bitIndex, int channel, bool grayLevel);// get one bit from the image
		~ImageProcess();
	private:
		void char2binary(unsigned char pixel);					// char to binary to show the number
		void bitSet(unsigned char& pixel, int bitIndex, bool number);	// set the bit of the image pixel
		Mat originalImage;
		Mat grayImage;
};
