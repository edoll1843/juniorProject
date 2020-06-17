#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

#include <math.h>
#include <io.h>

using namespace cv;
using namespace std;

#define SCALE 0.2
#pragma warning(disable: 4996)

/* given hue value, which is original_hue/2
calculate a corresponding RGB.
It is assumed that luminance is 0.5 (50%), and saturation is 1.0(100%)
*/
float max(float a, float b, float c) {
	return ((a > b) ? (a > c ? a : c) : (b > c ? b : c));
}
float min(float a, float b, float c) {
	return ((a < b) ? (a < c ? a : c) : (b < c ? b : c));
}
int rgb_to_hsv(float r, float g, float b) {
	// R, G, B values are divided by 255
	// to change the range from 0..255 to 0..1:
	float h, s, v;
	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	float cmax = max(r, g, b); // maximum of r, g, b
	float cmin = min(r, g, b); // minimum of r, g, b
	float diff = cmax - cmin; // diff of cmax and cmin.
	if (cmax == cmin)
		h = 0;
	else if (cmax == r)
		h = fmod((60 * ((g - b) / diff) + 360), 360.0);
	else if (cmax == g)
		h = fmod((60 * ((b - r) / diff) + 120), 360.0);
	else if (cmax == b)
		h = fmod((60 * ((r - g) / diff) + 240), 360.0);
	// if cmax equal zero
	if (cmax == 0)
		s = 0;
	else
		s = (diff / cmax) * 100;
	// compute v
	v = cmax * 100;

	if (v>90 && s<10)
	{
		return 0; // White
	}
	if (v<20)
	{
		return 1; // Black
	}
	if (s < 25 && v<70 && v>30)
	{
		return 2; //Gray
	}
	if (h >= 0 && h < 30)
	{
		return 3; // Red
	}
	else if (h >= 30 && h < 70)
	{
		return 4; // Yellow
	}
	else if (h >= 70 && h < 150)
	{
		return 5; //Green
	}
	else if (h >= 150 && h < 200)
	{
		return 6; //Cyans
	}
	else if (h >= 200 && h < 260)
	{
		return 7; // Blue
	}
	else if (h >= 270 && h < 330)
	{
		return 8; //Magenta
	}
	else
		return 3; //red
}


Scalar cvtHLStoRGB(double hue)
{
	double _hue = 2 * hue;
	double C = 1.0;
	double X = (double)(1.0 - abs((double)(((int)(_hue / 60.0) % 2) - 1)));
	double m = 0.0;

	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	if (_hue >= 0 && _hue < 60)
	{
		R = C*255.0;
		G = X*255.0;
	}
	else if (_hue >= 60 && _hue < 120)
	{
		R = X*255.0;
		G = C*255.0;
	}
	else if (_hue >= 120 && _hue < 180)
	{
		G = C*255.0;
		B = X*255.0;
	}
	else if (_hue >= 180 && _hue < 240)
	{
		G = X*255.0;
		B = C*255.0;
	}
	else if (_hue >= 240 && _hue < 300)
	{
		R = X*255.0;
		B = C*255.0;
	}
	else if (_hue >= 300 && _hue < 360)
	{
		R = C*255.0;
		B = X*255.0;
	}
	return Scalar(B, G, R);
}
void HSV() {
	char* argv = "test12.jpg";

	Mat inputImg, dispImg;
	Mat hlsImg;

	inputImg = imread(argv, IMREAD_COLOR);
	resize(inputImg, dispImg, Size(), SCALE, SCALE, INTER_AREA);
	cvtColor(inputImg, hlsImg, COLOR_BGR2HSV);
	// inputImg is too large to be shown.
	// use scaled-down dispImg instead just for display
	// use inputImg for the histogram calculation

	cout << "Width : " << inputImg.cols << endl << "Height : " << inputImg.rows << endl;

	// read a pixel from image directly

	int black = 0; int white = 0; int gray = 0; int red = 0; int yellow = 0; int green = 0;
	int cyan = 0; int blue = 0; int magenta = 0;
	for (int i = 0; i < inputImg.cols; i++) {
		for (int j = 0; j < inputImg.rows; j++) {
			int hue;
			int nBlue, nGreen, nRed;

			nBlue = inputImg.at<Vec3b>(j, i)[0];
			nGreen = inputImg.at<Vec3b>(j, i)[1];
			nRed = inputImg.at<Vec3b>(j, i)[2];
			hue = rgb_to_hsv((float)nRed, (float)nGreen, (float)nBlue);
			switch (hue) {
			case 0: white++; break;
			case 1: black++; break;
			case 2: gray++; break;
			case 3: red++; break;
			case 4: yellow++; break;
			case 5: green++; break;
			case 6: cyan++; break;
			case 7: blue++; break;
			case 8: magenta++; break;
			}
		}
	}

	cout << "Black : " << 100 * black / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"White : " << 100 * white / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Gray : " << 100 * gray / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Red : " << 100 * red / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Yellow : " << 100 * yellow / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Green : " << 100 * green / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Cyan : " << 100 * cyan / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Blue : " << 100 * blue / (inputImg.cols*inputImg.rows) << "%" << endl <<
		"Magenta : " << 100 * magenta / (inputImg.cols*inputImg.rows) << "%" << endl;
	// separate into three images with only one channel, H, L, and S
	vector<Mat> hls_images(3);
	split(hlsImg, hls_images);



	//--------------------------------------
	// H, L, S 채널별로 histogram을 계산
	//--------------------------------------

	// Prepare three histograms for H, L, S
	MatND* histogram = new MatND[hlsImg.channels()];

	// Each image has only one channel.
	const int* channel_numbers = { 0 };

	float channel_range[] = { 0.0, 255.0 };
	const float* channel_ranges = channel_range;
	// 255-bins for histogram
	int number_bins = 255;

	// calculate histograms one at a time, H, L, and S
	// histogram[0] contains H's
	// histogram[1] contains L's
	// histogram[2] contains S's
	for (int chan = 0; chan < hlsImg.channels(); chan++)
	{
		calcHist(&(hls_images[chan]), 1, channel_numbers, Mat(),
			histogram[chan], 1, &number_bins, &channel_ranges);
	}

	//------------------------
	// Plot the histograms in each image
	//------------------------
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / number_bins);

	// histogram image for H channel
	Mat histImageH(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogram[0], histogram[0], 0, histImageH.rows, NORM_MINMAX, -1, Mat());

	// histogram image for L channel
	Mat histImageL(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogram[1], histogram[1], 0, histImageL.rows, NORM_MINMAX, -1, Mat());

	// histogram image for S channel
	Mat histImageS(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogram[2], histogram[2], 0, histImageS.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < number_bins; i++)
	{
		line(histImageH, Point(bin_w*(i - 1), hist_h - cvRound(histogram[0].at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogram[0].at<float>(i))),
			cvtHLStoRGB((double)i), 2, 8, 0);
		line(histImageL, Point(bin_w*(i - 1), hist_h - cvRound(histogram[1].at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogram[1].at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImageS, Point(bin_w*(i - 1), hist_h - cvRound(histogram[2].at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogram[2].at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	namedWindow("Original", WINDOW_AUTOSIZE);


	moveWindow("Original", 100, 100);

	imshow("Original", dispImg);


	waitKey(0);

}
