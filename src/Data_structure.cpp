#include "Data_structure.h"

Result::Result(){
	bins_count = 0;
	swap_record[0] = swap_record[1] = 0;
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
	if (item1 == item2 || data.items[item1] == data.items[item2])	return false;
	res = *this;
	int bin1 = 0, bin2 = 0;
	for (int i = 0; i < bins_count; ++i){
		if (record[item1][i] == 1)	bin1 = i;
		if (record[item2][i] == 1)	bin2 = i;
		if (bin1 && bin2) break;
	}
	if (bin1 == bin2)	return false;
	if ((data.items[item1] > res.bins_weight[bin2] + data.items[item2]) || (data.items[item2] > res.bins_weight[bin1] + data.items[item1]))	return false;
	record[item1][bin1] = record[item2][bin2] = 0;
	record[item1][bin2] = record[item2][bin1] = 1;
	res.bins_weight[bin1] = res.bins_weight[bin1] + data.items[item1] - data.items[item2];
	res.bins_weight[bin2] = res.bins_weight[bin2] + data.items[item2] - data.items[item1];
	return true;
}

Range Result::get_neighbor_range(Data data){
	Range range;
	bool flag = true;
	for (int i = 0; i < data.items.size(); ++i){
		for (int j = 0; j < bins_count; ++j){
			if (data.items[i] <= bins_weight[j]){
				Result temp = move(i, j);
				if (temp.bins_count < bins_count){
					flag = false;
				}
				range.neighbors.push_back(temp);
			}			
		}
	}

	if (flag){
		for (int i = 0; i < data.items.size(); ++i){
			for (int j = i + 1; j < data.items.size(); ++j){
				Result temp;
				if (swap(i, j, temp))
					range.neighbors.push_back(temp);
			}
		}
	}
	return range;
}

Range Result::get_neighbor_range_move(Data data){
	Range range;
	for (int i = 0; i < data.items.size(); ++i){
		for (int j = 0; j < bins_count; ++j){
			if (data.items[i] <= bins_weight[j]){
				Result temp = move(i, j);
				range.neighbors.push_back(temp);
			}			
		}
	}
	return range;
}

Range Result::get_neighbor_range_random_move(int times, Data data){
	Range range;
	int item = 0, bin = 0;
	for (int i = 0; i < times; ++i){
		//while (true){
			item = rand() % data.items.size();
			bin = rand() % data.items.size();
			if (data.items[item] <= bins_weight[bin]){
				Result temp = move(item, bin);
				range.neighbors.push_back(temp);
				//break;
			}
			//cout << "item1: " << item1 << " item2: " << item2 << endl;		
		//}
	}
	return range;
}

Range Result::get_neighbor_range_swap(bool flag, Data data){
	Range range;	
	for (int i = 0; i < data.items.size(); ++i){
		for (int j = i + 1; j < data.items.size(); ++j){
			Result temp;
			if (swap(i, j, temp)){
				if (flag){
					swap_record[0] = i > j ? i : j;
					swap_record[1] = i < j ? i : j;
				}
				range.neighbors.push_back(temp);
			}
		}
	}	
	return range;
}

Range Result::get_neighbor_range_random_swap(int times, Data data){
	Range range;
	int item1 = 0, item2 = 0;
	for (int i = 0; i < times; ++i){
		item1 = rand() % data.items.size();
		item2 = rand() % data.items.size();
		Result temp;
		if (swap(item1, item2, temp))
			range.neighbors.push_back(temp);
	}	
	return range;
}

void Result::create_result(bool flag, Result & res, Data data, int pos1, int pos2){
	//FF
	res.data = data;
	record.resize(data.n);
	for (int i = 0; i < data.n; ++i){
		record[i].resize(data.n);
		int j = 0;
		for (; j < res.bins_count; ++j){
			record[i][j] = 0;
			if (data.items[i] <= res.bins_weight[j]){
				res.bins_weight[j] -= data.items[i];
				record[i][j] = 1;
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
			if (j > record[i].size())
				record[i].resize(j);
			record[i][j] = 1;
			res.items_order.push_back(data.items[i]);
		}
	}
	return;
}

void Result::create_random_result(Result & res, Data data){
	res.data = data;
	record.resize(data.n);
	srand((unsigned)time(NULL));
	for (int i = 0; i < data.n; ++i){
		record[i].resize(data.n);
		int j = 0;
		for (; j < res.bins_count; ++j){
			record[i][j] = 0;
			if (data.items[i] <= res.bins_weight[j]){
				if ((rand() % 100) / (double)100 > 0.3){
					res.bins_weight[j] -= data.items[i];
					record[i][j] = 1;
					res.items_order.push_back(data.items[i]);
					break;
				}			
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == res.bins_weight.size()){
			res.bins_weight.push_back(data.c - data.items[i]);
			++res.bins_count;
			if (j > record[i].size())
				record[i].resize(j);
			record[i][j] = 1;
			res.items_order.push_back(data.items[i]);
		}
	}
	return;
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
	this->data = res.data;
	this->record = res.record;
	this->bins_count = res.bins_count;
	this->bins_weight = res.bins_weight;
	this->items_order = res.items_order;
	this->swap_record[0] = res.swap_record[0];
	this->swap_record[1] = res.swap_record[1];
}

bool Result::is_null(){
	return this->bins_count == 0;
}

int Result::get_bins_count(){
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
