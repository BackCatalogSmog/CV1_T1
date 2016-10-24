#include "MyImage.h"



MyImage::MyImage(std::string path) {
	image = cv::imread(path, 0);//read grayscale
	s = image.size();
	height = s.height;
	width = s.width;
}


MyImage::~MyImage() {
}

/*MyImage::PathPixel getSmallest(std::map<> &vec) {
	unsigned int index=0;
	if (vec.size() == 0) return MyImage::PathPixel(-1, -1,-1);
	MyImage::PathPixel smallest = vec[0];
	for (MyImage::PathPixel p : vec) {
		if (p < smallest) smallest = p;
		index++;
	}
	vec.erase(vec.begin() + index);
	return smallest;
}*/
std::string pts(cv::Point p) {
	std::stringstream s;
	s << p.x << ":" << p.y;
	return s.str();
}

std::vector<cv::Point> MyImage::shortestPath(cv::Point start, cv::Point end) {
	cv::Point smallest(start.x, start.y);
	int smallestCost = 257;

	std::map<cv::Point, int> cost;
	std::map<cv::Point, bool> visited;
	for (int x = 0; x < image.cols; x++) {
		for (int y = 0; y < image.rows; y++) {
			cost[cv::Point(x, y)] = 256; // == 255 + 1
			visited[cv::Point(x, y)] = false;
		}
	}
	std::map<cv::Point, cv::Point> visitedBy; //Pixel visited From
	cost[start] = 0;
	cv::Point current(start.x,start.y);



	while (current!=end) {
		//set neighbour distance
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				//unvisited neighbour
				cv::Point neighbour(current.x+x, current.y+y);
				if (pointInBounds(neighbour) && !(visited[neighbour]) && (neighbour != current)){
					int diff = abs(static_cast<int>(image.at<uchar>(neighbour)) - static_cast<int>(image.at<uchar>(current)));
					int add = (diff + cost[current]);
					if (add < cost[neighbour]) {
						cost[neighbour] = add;
						visitedBy[neighbour] = current;
						if (add < smallestCost){
							smallestCost = add;
							smallest = neighbour;
						}
					}
				}	
			}
		}
		visited[current] = true;
		current = smallest;
	}
	//current == smallest == end
	std::vector<cv::Point> vec;
	while (current != start) {
		vec.push_back(current);
		current = visitedBy[current];
	}
	vec.push_back(current);
	
	return vec;
}

bool MyImage::pointInBounds(cv::Point p) {
	if (p.x > width - 1 || p.x<0 || p.y> height - 1 || p.y < 0) return false;
	else return true;
}

cv::Mat MyImage::getImage() {
	return image;
}
