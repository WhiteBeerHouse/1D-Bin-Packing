#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> items;
int n, c;

int next_fit(){
	vector<int> bins;
	int index = 0;
	bins.resize(1);
	for (int i = 0; i < n; ++i){
		if (items[i] <= bins[index]);
		else {
			++index;
			bins.resize(index + 1);
		}
		bins[index] -= items[i];
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
	cout << next_fit() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}