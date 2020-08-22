#include "Data_structure.h"

Result::Result(){
	bins_count = 0;
	swap_record[0] = swap_record[1] = 0;
}

Result::~Result(){
	bins_weight.clear();
	vector<int>().swap(bins_weight);
}

Result Result::create_result(const Data & data, int pos1, int pos2){
	this->data = data;
	for (int i = 0; i < data.n; ++i){
		int j = 0;
		for (; j < this->bins_count; ++j){
			if (data.items[i] <= this->bins_weight[j]){
				this->bins_weight[j] -= data.items[i];
				this->items_order.push_back(data.items[i]);
				swap_record[0] = pos2;
				swap_record[1] = pos1;
				break;	
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == this->bins_weight.size()){
			this->bins_weight.push_back(data.c - data.items[i]);
			++this->bins_count;
			this->items_order.push_back(data.items[i]);
		}
	}
	return *this;
}

Result Result::create_random_result(const Data & data){
	this->data = data;
	srand((unsigned)time(NULL));
	for (int i = 0; i < data.n; ++i){
		int j = 0;
		for (; j < this->bins_count; ++j){
			if (data.items[i] <= this->bins_weight[j]){
				if ((rand() % 100) / (double)100 > 0.7){
					this->bins_weight[j] -= data.items[i];
					this->items_order.push_back(data.items[i]);
					break;
				}			
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == this->bins_weight.size()){
			this->bins_weight.push_back(data.c - data.items[i]);
			++this->bins_count;
			this->items_order.push_back(data.items[i]);
		}
	}
	return *this;
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

int Result::get_bins_count() const{
	return bins_count;
}

vector<int> Result::get_bins_weight() const{
	return bins_weight;
}

vector<int> Result::get_items_order() const{
	return items_order;
}