#include <stdio.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cfloat>

class Pose {
public:
	double x, y;
	Pose () {}
	Pose (double xx, double yy):x(xx), y(yy) {}

	double distance_sqrt (Pose p) {
		return sqrt((p.x-this->x)*(p.x-this->x)+(p.y-this->y)*(p.y-this->y));
	}
};

void TSP (int cnt, std::vector<bool> visited, std::vector<Pose> &pos,
		std::vector<Pose> &tmp_route, std::vector<Pose> &ans_route, double &ans_length) {
	if (cnt == pos.size()-1) {
		tmp_route.push_back(pos[cnt]);
		double tmp_length(0);
		for (unsigned i=0;i<tmp_route.size()-1;++i)
			tmp_length += tmp_route[i].distance_sqrt(tmp_route[i+1]);
		if (ans_length > tmp_length) {
			ans_length = tmp_length;
			ans_route = tmp_route;
		}
		return ;
	}
	for (unsigned i=0;i<pos.size()-1;++i) {
		if (!visited[i]) {
			visited[i] = true;
			tmp_route.push_back(pos[i]);
			TSP (cnt+1, visited, pos, tmp_route, ans_route, ans_length);
			tmp_route.pop_back();
			visited[i] = false;
		}
	}
}

int main (int argc, char *argv[]) {

	std::string file_name;
	if(argc == 1) file_name = "./test/file.txt";
	else		  file_name = argv[1];
	
	std::ifstream my_file(file_name);
	if (my_file.is_open()) {
		std::vector<Pose> pos;
		std::string line;
		while (getline(my_file, line)) {
			double x, y;
			sscanf(line.c_str(), "%lf%lf", &x, &y);
			pos.push_back(Pose(x, y));
		}
		std::vector<bool> visited(pos.size(), false);
		std::vector<Pose> tmp_route, ans_route;

		double ans_length(DBL_MAX);
		TSP (0, visited, pos, tmp_route, ans_route, ans_length);

		for (unsigned i=0;i<ans_route.size();++i) {
			if (i != 0) std::cout << " -> ";
			std::cout << "(" << ans_route[i].x << "," << ans_route[i].y << ")";
		}
		std::cout << std::endl;
		std::cout << "Route length: " << ans_length << std::endl;
	}
	else std::cerr << "Unable to open " << file_name << std::endl;

	return 0;
}
