// CV_Task1_ShortestPath.cpp : Defines the entry point for the console application.
//
#include "opencv2/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "MyImage.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <set>

//global vars
std::vector<cv::Point> points;
cv::Mat image;
std::vector<MyImage> myimg;

static void negatePixels(std::vector<cv::Point> & points) {
	//somehow this takes very long
	//apply negative values to pixels in path and update window
	for (cv::Point p : points) {
		image.at<cv::Vec3b>(p.y, p.x)[0] = 255-image.at<cv::Vec3b>(p.y, p.x)[0];
		image.at<cv::Vec3b>(p.y, p.x)[1] = 255-image.at<cv::Vec3b>(p.y, p.x)[1];
		image.at<cv::Vec3b>(p.y, p.x)[2] = 255-image.at<cv::Vec3b>(p.y, p.x)[2];
	}
	imshow("image", image);
}

static void handleMouse(int event, int x, int y, int, void*) 
{
	
	if (event != cv::EVENT_LBUTTONDOWN)
		return;
	
	cv::Point point = cv::Point(x, y);
	std::stringstream str;
	str << point.x << " " << point.y << " VALUE " << static_cast<int>(image.at<uchar>(y,x));
	std::cout << str.str() << std::endl;

	if (points.size() < 2) {
		points.push_back(point);
		if (points.size() == 2) {
			std::cout << "searching for shortest path" << std::endl;
			negatePixels(myimg[0].shortestPath(points[0], points[1]));
			points.clear();
		}
	}

	
}

int main(int argc, char** argv)
{
	bool stop = false;
	char* fn = argc >= 2 ? argv[1] : (char*)"fruits.jpg"; 
	cv::namedWindow("image", 0);
	cv::setMouseCallback("image", handleMouse, 0);
	cv::imshow("image", image);
	myimg.push_back(MyImage(fn));


	while (!stop) {
		int key = cv::waitKey(0);
		if (static_cast<char>(key) == 's') stop = true;
	}
	return 0;
}

