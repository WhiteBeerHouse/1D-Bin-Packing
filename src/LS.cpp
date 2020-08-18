#include "Data_structure.h"

vector<int> items;
int n, c;

int hill_climbing(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);
	//cout << "random_FF: " << current.get_bins_count() << endl;
	while (true){
		Range neighbor_range = current.get_neighbor_range(data);
		//cout << "num of range: " << neighbor_range.neighbors.size() << endl;
		Result best_neighbor;
		while (!neighbor_range.empty()){
			Result neighbor = neighbor_range.next();
			if (best_neighbor.get_bins_count() == 0 || neighbor.better(&best_neighbor))
				best_neighbor = neighbor;
		}

		if (best_neighbor.get_bins_count() != 0 && best_neighbor.better(&current))
			current = best_neighbor;
		else
			return current.get_bins_count();
	}
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
	cout << hill_climbing() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}