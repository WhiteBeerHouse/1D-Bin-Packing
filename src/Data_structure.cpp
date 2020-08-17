#include "Data_structure.h"

#define MAX 100

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
	bins_weight.clear();
	vector<int>().swap(bins_weight);
	for (int i = 0; i < record.size(); ++i){
		record[i].clear();
		vector<int>().swap(record[i]);
	}
	record.clear();
	vector<vector<int>>().swap(record);
}

//Result::Result(int bins_count0, vector<int> bins_weight0) : bins_count(bins_count0), bins_weight(bins_weight0){}


Result Result::move(int item, int tar_bin){
	Result res = *this;
	int i = 0;
	for (; i < bins_count; ++i){
		if (record[item][i] == 1)
			break;
	}
	res.bins_weight[i] += data.items[item];
	res.bins_weight[tar_bin] -= data.items[item];
	if (res.bins_weight[i] == data.c){
		--bins_count;
		record[item][i] = 0;
	}
	return res;
}

bool Result::swap(int item1, int item2, Result & res){
	if (item1 == item2)	return false;
	res = *this;
	int bin1, bin2;
	for (int i = 0; i < bins_count; ++i){
		if (record[item1][i] == 1)	bin1 = i;
		if (record[item2][i] == 1)	bin2 = i;
	}
	if (bin1 == bin2)	return false;
	if (data.items[item1] == data.items[item2])	return false;
	if (data.items[item1] > res.bins_weight[bin2] + data.items[item2] || data.items[item2] > res.bins_weight[bin1] + data.items[item1])	return false;
	record[item1][bin1] = record[item2][bin2] = 0;
	record[item1][bin2] = record[item2][bin1] = 1;
	res.bins_weight[bin1] = res.bins_weight[bin1] + data.items[item1] - data.items[item2];
	res.bins_weight[bin2] = res.bins_weight[bin2] + data.items[item2] - data.items[item1];
	return true;
}

Range Result::get_neighbor_range(Data data){
	Range range;
	//int count = 0;
	bool flag = true;
	for (int i = 0; i < data.items.size(); ++i){
		for (int j = 0; j < bins_count; ++j){
			if (data.items[i] <= bins_weight[j]){
				Result temp = move(i, j);// judge?
				if (temp.bins_count < bins_count){
					flag = false;
				}
				range.neighbors.push_back(temp);//
			}			
		}
	}

	if (flag){
		for (int i = 0; i < data.items.size(); ++i){
			for (int j = 0; j < data.items.size(); ++j){
				Result temp;
				if (swap(i, j, temp))
					range.neighbors.push_back(temp);
			}
		}
	}
	return range;
}

void Result::create_random_result(Result & res, Data data){
	res.data = data;
	record.resize(data.n);
	srand((unsigned)time(NULL));
	for (int i = 0; i < data.n; ++i){
		record[i].resize(MAX);
		int j = 0;
		for (; j < res.bins_count; ++j){
			record[i][j] = 0;
			if (data.items[i] <= res.bins_weight[j]){
				double rand_factor = (rand() % 100) / (double)100;
				//cout << "rand: " << rand_factor << endl;
				if (rand_factor > 0.3){
					res.bins_weight[j] -= data.items[i];
					record[i][j] = 1;
					break;
				}			
			}
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

bool Result::better(Result* res){
	if (this->bins_count < res->bins_count)	
		return true; 
		//{cout << "c_better" << endl; return true;}
	else if (this->bins_count > res->bins_count)	return false;

	vector<int> bins1 = this->bins_weight;
	vector<int> bins2 = res->bins_weight;
	sort(bins1.begin(), bins1.end());
	sort(bins2.begin(), bins2.end());

	for (int i = 0; i < bins1.size(); ++i){
		if (bins1[i] < bins2[i])	
			return true; 
			//{cout << "b_better" << endl; return true;}
		else return false;
	}
}

/*bool Result::better(Result res1, Result res2){
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
}*/

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
