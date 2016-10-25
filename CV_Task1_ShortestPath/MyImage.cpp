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
//	std::priority_queue<std::pair<int, cv::Point>,std::vector<std::pair<int, cv::Point>>, MyImage::intPointPairComp> pque;
	//dijkstra using priority queues. Not very fast though due to mishaps trying to optimise early on

	//priority queue using custom comparator
	std::priority_queue <
		std::pair<int, cv::Point>,
		std::vector<std::pair<int, cv::Point>>,
		MyImage::intPointPairComp
	> pque;

	std::map<std::string, int> cost;
	std::map<std::string, bool> visited;
	for (int x = 0; x < image.cols; x++) {
		for (int y = 0; y < image.rows; y++) {
			cost[pts(cv::Point(x, y))] = std::numeric_limits<int>::max(); 
			visited[pts(cv::Point(x, y))] = false;
		}
	}
	std::map<std::string, cv::Point> visitedBy; //Pixel visited From
	cost[pts(start)] = 0;
	cv::Point current(start.x,start.y);


	
	while (current!=end) {
		//std::cout << pts(current) << " " << pts(end) << std::endl;
		//set neighbour distance
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				//if (visited[pts(current)]) std::cout << "nope";
				//if (pts(current) == pts(end)) std::cout << "something went wrong";
				//unvisited neighbour
				cv::Point neighbour(current.x+x, current.y+y);
				if (pointInBounds(neighbour) && !(visited[pts(neighbour)]) && (neighbour != current)){
					//std::cout << "Point " << pts(current) << " visited " << visited[pts(current)];
					int diff = abs(static_cast<int>(image.at<uchar>(neighbour)) - static_cast<int>(image.at<uchar>(current)));
					int costNeighbour = cost[pts(neighbour)];
					int add = (diff + cost[pts(current)]);
					if (add < costNeighbour) {
						cost[pts(neighbour)] = add;
						visitedBy[pts(neighbour)] = current;
						pque.push(std::pair<int, cv::Point>(add, neighbour));
					}
				}
				
			}
			
		}
		visited[pts(current)] = true;
		std::pair<int, cv::Point> pr = pque.top();
		pque.pop();
		//As updated values do not get removed, check for "visited" is necessary
		while (visited[pts(pr.second)]) {
			pr = pque.top();
			pque.pop();
		}
		current = pr.second;
		
	}
	//current == smallest == end
	std::vector<cv::Point> vec;
	std::cout << "here!" << std::endl;
	while (current != start) {
		vec.push_back(current);
		current = visitedBy[pts(current)];
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
