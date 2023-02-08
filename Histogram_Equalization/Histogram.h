#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace cv;

class Histogram {				// Histogram class to implement the Equalization function 
	public:
		Histogram (Mat image);
		Histogram();
		~Histogram ();
		void loadImage(string filePath);
		void loadImage(Mat image);
		void imageDark();
		void showHistogram(string imageName);
		void drawHistogram(unsigned int *in);
		Mat equiHist();
	private:
		Mat image;
		unsigned int record[256] = {0};
};
