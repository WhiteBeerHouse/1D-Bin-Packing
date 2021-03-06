#include "Data_structure.h"

vector<int> items;
int n, c;

void swap_items_and_get_order(int pos1, int pos2, vector<int>& origin_order){
	int temp = origin_order[pos1];
	origin_order[pos1] = origin_order[pos2];
	origin_order[pos2] = temp;
	return;
}

deque<Result> get_neighbor_range(const vector<int>& items_order){
	deque<Result> neighbor_range;
	for (int i = 0; i < items_order.size(); ++i){
		for (int j = i + 1; j < items_order.size(); ++j){
			Result res;
			vector<int> origin_order = items_order;
			swap_items_and_get_order(i, j, origin_order);
			res.create_result(Data(n, c, origin_order), i, j);
			neighbor_range.push_back(res);
		}
	}
	return neighbor_range;
}

int hill_climbing(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(data);
	cout << "Random_initial_solution: " << current.get_bins_count() << endl;

	Result best = current;
	while (true){
		deque<Result> neighbor_range = get_neighbor_range(current.get_items_order());
		for (int i = 0; i < neighbor_range.size(); ++i){
			if (neighbor_range.at(i).better(current))
				current = neighbor_range[i];
		}
		if (current.better(best))
			best = current;
		else
			return best.get_bins_count();
	}
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
	int solution = hill_climbing();
	cout << "Solution by hill_climbing: " << solution << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}