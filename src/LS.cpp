#include "Data_structure.h"

vector<int> items;
int n, c;

int local_search(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);
	cout << current.get_bins_count() << endl;
	//int i = 100;
	while (true){ // i--
		//cout << "loop" << endl;
		Range neighbor_range = current.get_neighbor_range(data);
		cout << "num of range: " << neighbor_range.neighbors.size() << endl;
		Result best_neighbor;
		while (!neighbor_range.empty()){
			Result neighbor = neighbor_range.next();
			if (best_neighbor.get_bins_count() == 0 || neighbor.better(&best_neighbor)){
				best_neighbor = neighbor;
			}
		}

		if (best_neighbor.get_bins_count() != 0 && best_neighbor.better(&current))
			current = best_neighbor;
		else
			return current.get_bins_count();
	}/**/
	return 0;

	/**
	current_result = create_random_result();
	while (true){
		neighbor_range = get_neighbor_range();
		best_neightbor = NULL;
		while (!neighbor_range->empty()){
			neighbor = neighbor_range->next();//next() should implement itself's going
			
			if (best_neighbor == NULL || neighbor is better than best_neighbor){
				best_neighbor = neighbor;
			}
		}

		if (best_neighbor && best_neighbor is better than current_result)
			current_result = best_neighbor;
		
		else //it means that in the range the  current result is the best. end.
			return current_result;
	}	
	 **/
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
	cout << local_search() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}