#include "ImageProcess.h"

const string originalFileDir = "./1.jpg";
const string embeddedfileDir = "./0.jpg";

int main() {
	ImageProcess image_process;
	Mat image;
	Mat waterMark;

	// load image
	image_process.loadImage(originalFileDir);
	// convert RGB image to gray scale
	image_process.convertGrayImage(image_process.getOriginal());
	// continuous throw the bits
	for (int i = 1; i < 4; ++i) {
		image = image_process.grayThrowBits(image_process.getGrayImage(), i);
		imshow("THROW BIT" + to_string(i), image);
		imwrite("./THROW BIT" + to_string(i) + ".jpg", image);
	}

	// convert gray image and store
	// water mark and reduct water mark with different bits
	for(int i = 1; i < 4; ++i) {
		waterMark = image_process.waterMark(embeddedfileDir, i, 0, 1);
		imshow("waterMark" + to_string(i), waterMark);						// show watermark
		image = image_process.reductWaterMark(waterMark, i, 1);
		imshow("ReductWaterMark" + to_string(i), image);					// show reduct watermark
		imwrite("./ReductWaterMark" + to_string(i) + ".jpg", image);
	}
	waitKey(0);
	return 0;
}
