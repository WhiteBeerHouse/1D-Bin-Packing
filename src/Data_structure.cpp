#include "Data_structure.h"

double get_rand(){
	srand((unsigned)time(0));
	return (rand() % 100) / (double)100;
}

Result::Result(){
	bins_count = 0;
	/**record = new int [data.n];
	for (int i = 0; i < data.n; ++i){
		for (int j = 0; j < data.n; ++j){
			record[i][j] = 0;
		}
	}
	record = 0;*/
}

Result::~Result(){
	/*bins_weight.clear();
	vector<int>().swap(bins_weight);
	for (int i = 0; i < data.n; ++i)
		delete record[i];
	delete record;*/
}

//Result::Result(int bins_count0, vector<int> bins_weight0) : bins_count(bins_count0), bins_weight(bins_weight0){}


Range Result::get_neighbor_range(Data data){
	Range range;
	int count = 0;
	for (int i = 0; i < data.items.size(); ++i){
		for (int j = 0; j < this->bins_count; ++j){
			if (data.items[i] <= this->bins_weight[j]){
				Result temp = this->move(i, j);
				if (temp.better(this)){
					range.neighbors.push_back(temp);
				}
			}			
		}
	}

	return range;
}

void Result::create_random_result(Result & res, Data data){
	res.data = data;
	record.resize(data.n);
	for (int i = 0; i < data.n; ++i){
		int j = 0;
		for (; j < res.bins_weight.size(); ++j){
			if (data.items[i] <= res.bins_weight[j]){
				double rand_factor = get_rand();
				if (rand_factor > 0.5){
					res.bins_weight[j] -= data.items[i];
					record[i][j] = 1;
					break;
				}			
			}			
			record[i][j] = 0;
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == res.bins_weight.size()){
			res.bins_weight.push_back(data.c - data.items[i]);
			++res.bins_count;
			record[i][j] = 1;
		}
	}
	return;
}

Result Result::move(int item, int tar_bin){
	Result res = *this;
	int i = 0;
	for (; i < bins_count; ++i){
		if (record[item][i] == 1)
			break;
	}
	res.bins_weight[i] += item;
	res.bins_weight[tar_bin] -= item;
	return res;
}

bool Result::better(Result* res){
	if (this->bins_count < res->bins_count)	return true;
	else if (this->bins_count > res->bins_count)	return false;

	vector<int> bins1 = this->bins_weight;
	vector<int> bins2 = res->bins_weight;
	sort(bins1.begin(), bins1.end());
	sort(bins2.begin(), bins2.end());

	for (int i = 0; i < bins1.size(); ++i){
		if (bins1[i] < bins2[i])	return true;
		else return false;
	}
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
	this->record = res.record;
	this->bins_count = res.bins_count;
	this->bins_weight = res.bins_weight;
	this->data = res.data;
}

int Result:: get_bins_count(){
	return bins_count;
}



Range::Range(){
	neighbors_index = 0;
}

Range::~Range(){
	neighbors.clear();
	vector<Result>().swap(neighbors);	
}

bool Range::empty(){
	return neighbors_index == neighbors.size();
}

Result Range::next(){
	return neighbors[neighbors_index++];
}
