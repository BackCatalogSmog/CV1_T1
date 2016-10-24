#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>

class MyImage
{
public:
	MyImage(std::string path);
	~MyImage();
	bool pointInBounds(cv::Point p1);
	std::vector<cv::Point> shortestPath(cv::Point start, cv::Point end);
	cv::Mat getImage();




	class PathPixel {
	public:
		PathPixel(int x1, int y1, double cost1) :p(x1,y1), cost(cost1) {};
		~PathPixel(){};
		cv::Point p;
		double cost;

		bool operator<( const PathPixel& r) {
			return cost < r.cost;
		}

		bool operator==(const PathPixel& r) {
			return (p==r.p);
		}
	private:
		
	};

	cv::Mat image;
	cv::Size s;
	int width;
	int height;

};

