#include <iostream>
#include <vector>
using namespace std;

class Range;

class Result{
public:
	Result();
	~Result();
	Result(int bins_count0, vector<int> bins_weight0);
	Range get_neighbor_range();
	Result create_random_result();
	bool better(Result res1, Result res2);
	Result& operator = (const Result& res);

private:
	int bins_count;
	vector<int> bins_weight;

};

class Range{
public:
	bool empty();
	Result next();

private:
	int neighbors_index;
	vector<Result> neighbors;

};