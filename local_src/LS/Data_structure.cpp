#include "Data_structure.h"

Result::Result(){
	bins_count = 0;
	swap_record[0] = swap_record[1] = 0;
}

Result::~Result(){
	bins_weight.clear();
	vector<int>().swap(bins_weight);
}

void Result::create_result(bool flag, Result & res, const Data & data, int pos1, int pos2){
	//FF
	res.data = data;
	for (int i = 0; i < data.n; ++i){
		int j = 0;
		for (; j < res.bins_count; ++j){
			if (data.items[i] <= res.bins_weight[j]){
				res.bins_weight[j] -= data.items[i];
				res.items_order.push_back(data.items[i]);
				if (flag){
					swap_record[0] = pos2;
					swap_record[1] = pos1;
				}
				break;	
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == res.bins_weight.size()){
			res.bins_weight.push_back(data.c - data.items[i]);
			++res.bins_count;
			res.items_order.push_back(data.items[i]);
		}
	}
	return;
}

void Result::create_random_result(Result & res, const Data & data){
	res.data = data;
	srand((unsigned)time(NULL));
	for (int i = 0; i < data.n; ++i){
		int j = 0;
		for (; j < res.bins_count; ++j){
			if (data.items[i] <= res.bins_weight[j]){
				if ((rand() % 100) / (double)100 > 0.7){
					res.bins_weight[j] -= data.items[i];
					res.items_order.push_back(data.items[i]);
					break;
				}			
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == res.bins_weight.size()){
			res.bins_weight.push_back(data.c - data.items[i]);
			++res.bins_count;
			res.items_order.push_back(data.items[i]);
		}
	}
	return;
}

bool Result::better(const Result & res){
	if (this->bins_count < res.bins_count)	return true;
	else if (this->bins_count > res.bins_count)	return false;

	vector<int> bins1 = this->bins_weight;
	vector<int> bins2 = res.bins_weight;
	sort(bins1.begin(), bins1.end());
	sort(bins2.begin(), bins2.end());

	for (int i = 0; i < bins1.size(); ++i){
		if (bins1[i] < bins2[i])	return true;
		else return false;
	}
}

Result& Result::operator = (const Result & res){
	this->data = res.data;
	this->bins_count = res.bins_count;
	this->bins_weight = res.bins_weight;
	this->items_order = res.items_order;
	this->swap_record[0] = res.swap_record[0];
	this->swap_record[1] = res.swap_record[1];
	return *this;
}

bool Result::is_null(){
	return this->bins_count == 0;
}

int Result::get_bins_count(){
	return bins_count;
}