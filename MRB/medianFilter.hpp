#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <array>
#include <algorithm>
using namespace std;

class medianFilter{
private:

	std::array<double,5> distanceHistory = {0};
	
public:

	double applyFilter(double newDistance){
			for(int i = 1; i < 5; i++){
				distanceHistory[i-1] = distanceHistory[i];
			}
			distanceHistory[4] = newDistance;
			
			std::array<double,5> sortedHistory = distanceHistory;
			std::sort(sortedHistory.begin(), sortedHistory.end());
			
			return sortedHistory[2];
	}
};

#endif