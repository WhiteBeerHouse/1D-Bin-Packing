#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> items;
int n, c;

bool cmp(int item1, int item2){
	return item1 > item2;
}

int first_fit(){
	sort(items.begin(), items.end(), cmp);
	vector<int> bins;
	for (int i = 0; i < n; ++i){
		int j;
		for (j = 0; j < bins.size(); ++j){
			if (items[i] <= bins[j]){
				bins[j] -= items[i];
				break;
			}
		}
		//if no opened bin satisfies, allocate a new bin
		if (j == bins.size()){
			bins.push_back(c - items[i]);
		}		
	}
	return bins.size();
}

int main(int argc, char* argv[]) {
	ifstream file;
	file.open(argv[1]);
	file >> n >> c;
	items.resize(n);
	for (int i = 0; i < n; ++i) {
		file >> items[i];
	}
	file.close();

	clock_t start = clock();
	cout << first_fit() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}