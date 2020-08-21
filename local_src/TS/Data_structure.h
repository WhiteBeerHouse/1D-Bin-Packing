#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

struct Data{
	int n;
	int c;
	vector<int> items;
	Data(){}
	Data(int n0, int c0, vector<int> items0) : n(n0), c(c0), items(items0){}
};
class Result;
class Range;

class Result{
public:
	Result();
	~Result();
	Range get_neighbor_range(Data data);
	Range get_neighbor_range_move(Data data);
	Range get_neighbor_range_swap(bool flag, Data data);//bad
	Range get_neighbor_range_random_move(int times, Data data);//not tested
	Range get_neighbor_range_random_swap(int times, Data data);//worst
	void create_result(bool flag, Result & res, Data data, int pos1, int pos2);
	void create_random_result(Result & res, Data data);
	Result move(int item, int tar_bin);
	bool is_null();
	bool swap(int item1, int item2, Result & res);
	bool better(Result* res);
	Result& operator = (const Result& res);
	int get_bins_count();

//private:
	Data data;
	vector<vector<int>> record;
	int bins_count;
	vector<int> bins_weight;
	vector<int> items_order;
	int swap_record[2];
};

class Range{
public:
	Range();
	~Range();
	bool empty();
	Result next();

//private:
	int neighbors_index;
	vector<Result> neighbors;

};


#endif