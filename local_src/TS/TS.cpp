#include "Data_structure.h"

#define LOOP_TIMES 200

vector<int> items;
int n, c;

void swap_items_and_get_order(int pos1, int pos2, vector<int>& origin_order){
	int temp = origin_order[pos1];
	origin_order[pos1] = origin_order[pos2];
	origin_order[pos2] = temp;
	return;
}

deque<Result> get_neighbor_range(vector<int> items_order){
	deque<Result> neighbor_range;
	for (int i = 0; i < items_order.size(); ++i){
		for (int j = i + 1; j < items_order.size(); ++j){
			Result res;
			vector<int> origin_order = items_order;
			swap_items_and_get_order(i, j, origin_order);
			res.create_result(true, res, Data(n, c, origin_order), i, j);
			neighbor_range.push_back(res);
		}
	}
	return neighbor_range;
}

int find_in_tabu_list(const deque<vector<int>> & tabu_list, const Result & res){
	int i = 0;
	for (; i < tabu_list.size(); ++i){
		if (tabu_list.at(i)[0] == res.swap_record[0] && tabu_list.at(i)[1] == res.swap_record[1]){
			break;
		}
	}
	return i;
}

int tabu_search(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);
	cout << "Random_initial_solution: " << current.get_bins_count() << endl;

	int tabu_tenure = (int)sqrt(n*(n-1)/2);
	deque<vector<int>> tabu_list;

	Result best = current;

	int loop = LOOP_TIMES;
	srand((unsigned)time(NULL));
	while (loop--){
		deque<Result> neighbor_range = get_neighbor_range(current.items_order);
		vector<Result> candidate_set;

		for (int i = 0; i < neighbor_range.size(); ++i){			
			if (candidate_set.empty() ||  ((rand() % (neighbor_range.size())) / (double)(neighbor_range.size())) > 0.6)
				candidate_set.push_back(neighbor_range.at(i));
		}

		Result best_candidate, best_non_tabu_candidate;
		for (int i = 0; i < candidate_set.size(); ++i){
			if (best_candidate.is_null() || candidate_set[i].better(best_candidate))
				best_candidate = candidate_set[i];
			if (find_in_tabu_list(tabu_list, candidate_set[i]) == tabu_list.size()){
				if (best_non_tabu_candidate.is_null() || candidate_set[i].better(best_non_tabu_candidate))
					best_non_tabu_candidate = candidate_set[i];
			}
		}

		if (find_in_tabu_list(tabu_list, best_candidate) == tabu_list.size()//not in tabu_list
			|| (find_in_tabu_list(tabu_list, best_candidate) != tabu_list.size() && best_candidate.better(best))//in tabu_list //not sure
			|| best_non_tabu_candidate.is_null())
		{
			current = best_candidate;
		}
		else {
			current = best_non_tabu_candidate;
		}

		if (tabu_list.size() == 0)
			tabu_list.push_front({current.swap_record[0], current.swap_record[1]});
		else {
			int index = find_in_tabu_list(tabu_list, current);
			if (index != tabu_list.size()){//is in tabu_list
				auto iter = tabu_list.begin() + index;
				iter = tabu_list.erase(iter);
			}
			if (tabu_list.size() == tabu_tenure){
				tabu_list.pop_back();
			}
			tabu_list.push_front({current.swap_record[0], current.swap_record[1]});
		}

		if (current.better(best))
			best = current;
	}
	return best.get_bins_count();
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
	int solution = tabu_search();
	cout << "Solution by tabu-search: " << solution << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}