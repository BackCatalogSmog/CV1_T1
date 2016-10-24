#include "MyImage.h"



MyImage::MyImage(std::string path) {
	image = cv::imread(path, 0);//read grayscale
	s = image.size();
	height = s.height;
	width = s.width;
}


MyImage::~MyImage() {
}

bool MyImage::difference(std::string p1, std::string p2){
	return true;
}

std::vector<cv::Point> MyImage::shortestPath(cv::Point p1, cv::Point p2) {
	//std::set<MyImage::PathPixel> cost;
	std::map<std::string, std::string> visited; //Pixel visited From
	std::stringstream current;
	current << p1.x << ":" << p1.y;

	std::stringstream end;
	end << p2.x << ":" << p2.y;
	
	//cost.insert(MyImage::PathPixel(p1.x, p2.x, 0));
	
	cv::Point currentp = p1;

	while (!(visited.find(end.str()) == visited.end())) {
		//set neighbour distance
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				//unvisited neighbour
				std::stringstream neighbour;
				neighbour << currentp.x + x << ":" << currentp.y + y;

				if (
					(x != currentp.x && y != currentp.y) &&
					!(visited.find(neighbour.str()) == visited.end())
					) {
					double diff;
					
						//double newCost = cost[current.str()] + ((cost.find(neighbour.str()) == cost.end()) ? 0 : cost[neighbour.str()]);
					}
			}
		}
		visited[current.str()] = true;
	}
	std::vector<cv::Point> vec;
	return vec;
}

bool MyImage::pointInBounds(cv::Point p) {
	if (p.x > width - 1 || p.x<0 || p.y> height - 1 || p.y < 0) return false;
	else return true;
}

cv::Mat MyImage::getImage() {
	return image;
}
