#include "Data_structure.h"

#define LOOP_TIMES 1000

vector<int> items;
int n, c;

int tabu_search(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);

	int** tabu_list = new int*[n];
	for (int i = 1; i < n; ++i){
		tabu_list[i] = new int[i];
		for (int j = 0; j < i; ++j)
			tabu_list[i][j] = 0;
	}/**/

	int tabu_tenure = 10;/*to be determined*/
	Result best = current;

	int loop = LOOP_TIMES;
	srand((unsigned)time(NULL));
	while (loop--){
		Range neighbor_range = current.get_neighbor_range_swap(true, data);
		vector<Result> candidate_set;

		while (!neighbor_range.empty()){
			Result neighbor = neighbor_range.next();
			if ((rand() % (neighbor_range.neighbors.size())) / (double)(neighbor_range.neighbors.size()) > 0.2)
				candidate_set.push_back(neighbor);
		}
		//if the candidate_set is empty ?...


		for (int i = 1; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (tabu_list[i][j] > 0)
					--tabu_list[i][j];
			}
		}
		

		//to find best candidate
		Result best_candidate = candidate_set[0];
		Result best_non_tabu_candidate;
		for (int i = 1; i < candidate_set.size(); ++i){
			if (candidate_set[i].better(best_candidate))
				best_candidate = candidate_set[i];
			if (tabu_list[candidate_set[i].swap_record[0]][candidate_set[i].swap_record[1]] == 0)
				if (best_non_tabu_candidate.is_null() || candidate_set[i].better(best_non_tabu_candidate))
					best_non_tabu_candidate = candidate_set[i];
		}

		//if the best candidate is in tabu list
		if ((tabu_list[best_candidate.swap_record[0]][best_candidate.swap_record[1]] == 0) 
			|| (tabu_list[best_candidate.swap_record[0]][best_candidate.swap_record[1]] > 0 && best_candidate.better(current))
			|| best_non_tabu_candidate.is_null())
		{
			current = best_candidate;
			//tabu_list[][]...
		}
		else {
			current = best_non_tabu_candidate;
			//tabu_list[][]...
		}





		/*if (!best_neighbor.is_null()){

		}
		else {

		}


		if (!best_neighbor.is_null()){
			if (best_neighbor.better(current)){
				current = best_neighbor;
				if (best_neighbor.better(best))
					best = best_neighbor;
			}
		}
		else {

		}*/

	}
	return best.get_bins_count();
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
	cout << tabu_search() << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}