#include <iostream>
#include <vector>
#include <algorithm>
#include "Data_structure.h"
using namespace std;

Result::Result(){
	bins_count = 0;
}

Result::~Result(){
	bins_weight.clear();
	vector<int>().swap(bins_weight);
}

Result::Result(int bins_count0, vector<int> bins_weight0) : bins_count(bins_count0), bins_weight(bins_weight0){}


Range Result::get_neighbor_range(){

}

Result Result::create_random_result(){

}

bool Result::better(Result res1, Result res2){
	if (res1.bins_count < res2.bins_count)	return true;
	else if (res1.bins_count > res2.bins_count)	return false;

	vector<int> bins1 = res1.bins_weight;
	vector<int> bins2 = res2.bins_weight;
	sort(bins1.begin(), bins1.end());
	sort(bins2.begin(), bins2.end());

	for (int i = 0; i < bins1.size(); ++i){
		if (bins1[i] < bins2[i])	return true;
		else return false;
	}
}

Result& Result::operator = (const Result& res){
	this->bins_count = res.bins_count;
	this->bins_weight = res.bins_weight;
}




bool Range::empty(){
	return neighbors_index == neighbors.size();
}

Result Range::next(){
	return neighbors[neighbors_index++];
}