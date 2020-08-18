#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
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
	void create_result(Result & res, Data data);
	void create_random_result(Result & res, Data data);
	Result move(int item, int tar_bin);
	bool swap(int item1, int item2, Result & res);
	bool better(Result* res);
	Result& operator = (const Result& res);
	int get_bins_count();

//private:
	Data data;
	vector<vector<int>> record;
	int bins_count;
	vector<int> bins_weight;

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