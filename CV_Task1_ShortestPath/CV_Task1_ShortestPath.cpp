// CV_Task1_ShortestPath.cpp : Defines the entry point for the console application.
//
#include "opencv2/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui.hpp"
//#include "MyImage.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <set>

std::vector<cv::Point> points;
cv::Mat image;

class testclass {
public:
	bool operator<(const std::string& other){

	}
	std::string test;
};

static void negatePixels(std::vector<cv::Point> points) {
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
	str << point.x << " " << point.y << " VALUE " << image.at<uchar>(y,x);
	std::cout << str.str() << std::endl;

	if (points.size() < 2) {
		points.push_back(point);
		if (points.size() == 2) {
			std::cout << "searching for shortest path" << std::endl;
			//
			points.clear();
		}
	}

	
}

int main(int argc, char** argv)
{
	bool stop = false;
	char* fn = argc >= 2 ? argv[1] : (char*)"C:\\Users\\Ull\\Desktop\\sadmeme.jpg"; //change dis line  tho
	image = cv::imread(fn, 1);
	cv::namedWindow("image", 0);
	cv::setMouseCallback("image", handleMouse, 0);
	cv::imshow("image", image);
	



	while (!stop) {
		int key = cv::waitKey(0);
		if (static_cast<char>(key) == 's') stop = true;
	}
	return 0;
}

