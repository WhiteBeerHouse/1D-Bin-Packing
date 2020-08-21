#include "Data_structure.h"
#include <cmath>

#define k 0.01
#define r 0.97
#define T 500
#define T_MIN 1
#define L 100
#define SWAP_TIMES 20
#define CONDITION 200

vector<int> items;
int n, c;

double difference_calculator(Result New, Result Old){
	if (New.bins_count != Old.bins_count)	
		return New.bins_count - Old.bins_count;

	vector<int> bins1 = New.bins_weight;
	vector<int> bins2 = Old.bins_weight;
	sort(bins1.begin(), bins1.end());
	sort(bins2.begin(), bins2.end());

	for (int i = 0; i < bins1.size(); ++i){
		if (bins1[i] > bins2[i])
			return ((bins1[i] - bins2[i]) % 10) / (double)10;
		else if (bins1[i] < bins2[i])
			return -(((bins2[i] - bins1[i]) % 10) / (double)10);
	}
	return 0;
}

int simulated_annealing(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);
	cout << "random_FF: " << current.get_bins_count() << endl;

	double current_T = T;
	srand((unsigned)time(NULL));
	int count = CONDITION;

	while (current_T > T_MIN && count > 0){
		Range neighbor_range;
		do{
			neighbor_range = current.get_neighbor_range_move(data);
		} while(neighbor_range.neighbors.size() == 0);

		for (int i = 0; i < L; ++i){
			int random_index = rand() % (neighbor_range.neighbors.size());
			Result neighbor = neighbor_range.neighbors[random_index];
			double diff = difference_calculator(neighbor, current);

			if (diff == 0)	--count;
			else count = CONDITION;

			if (diff < 0)
				current = neighbor;
			else {
				if (exp(-diff / (k * current_T)) > (rand() % 100) / (double)100)
					current = neighbor;
			}
		}
		current_T *= r;
	}
	return current.get_bins_count();
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
	cout << simulated_annealing() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}