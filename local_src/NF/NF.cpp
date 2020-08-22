#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> items;
int n, c;

int next_fit(){
	int bins = 1, left = c;
	for (int i = 0; i < n; ++i){
		if (items[i] <= left)
			left -= items[i];
		else {
			++bins;
			left = c - items[i];
		}
	}
	return bins;
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
	int solution = next_fit();
	cout << "Solution by next_fit: " << solution << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}