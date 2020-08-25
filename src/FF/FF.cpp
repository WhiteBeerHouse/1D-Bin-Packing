#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> items;
int n, c;

int first_fit(){
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
	if (!file.is_open()){
		perror("Error");
		return(-1);
	}
	file >> n >> c;
	items.resize(n);
	for (int i = 0; i < n; ++i) {
		file >> items[i];
	}
	file.close();

	clock_t start = clock();
	int solution = first_fit();
	cout << "Solution by first_fit: " << solution << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}