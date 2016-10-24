#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <queue>
#include <limits>
#include <set>

class MyImage
{
public:
	MyImage(std::string path);
	~MyImage();
	bool pointInBounds(cv::Point p1);
	std::vector<cv::Point> shortestPath(cv::Point p1, cv::Point p2);
	bool MyImage::difference(std::string p1, std::string p2);
	cv::Mat getImage();




	class PathPixel {
	public:
		PathPixel(int x1, int y1, double cost1) :x(x1), y(y1), cost(cost1) {};
		~PathPixel(){};
		int x;
		int y;
		double cost;

		bool operator<( const PathPixel& r) {
			return cost < r.cost;
		}
	private:
		
	};

	cv::Mat image;
	cv::Size s;
	int width;
	int height;

};

