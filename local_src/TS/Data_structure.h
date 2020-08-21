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

class Result{
public:
	Result();
	~Result();
	void create_result(bool flag, Result & res, const Data & data, int pos1, int pos2);
	void create_random_result(Result & res, const Data & data);
	bool is_null();
	bool better(const Result & res);
	Result& operator = (const Result & res);
	int get_bins_count();

	vector<int> items_order;
	int swap_record[2];

private:
	Data data;
	int bins_count;
	vector<int> bins_weight;
};

#endif