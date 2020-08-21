#include "Data_structure.h"

#define LOOP_TIMES 10

vector<int> items;
int n, c;

void swap_items_and_get_order(int pos1, int pos2, vector<int>& origin_order){
	int temp = origin_order[pos1];
	origin_order[pos1] = origin_order[pos2];
	origin_order[pos2] = temp;
	return;
}

vector<Result> get_neighbor_range_TS(vector<int> items_order){
	vector<Result> neighbor_range;
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
	cout << "random_FF: " << current.get_bins_count() << endl;

	int tabu_tenure = (int)sqrt(n*(n+1)/2);
	deque<vector<int>> tabu_list;

	Result best = current;

	int loop = LOOP_TIMES;
	srand((unsigned)time(NULL));
	while (loop--){
		vector<Result> neighbor_range = get_neighbor_range_TS(current.items_order);
		vector<Result> candidate_set;

		for (int i = 0; i < neighbor_range.size(); ++i){			
			if (candidate_set.empty() ||  ((rand() % (neighbor_range.size())) / (double)(neighbor_range.size())) > 0.6)
				candidate_set.push_back(neighbor_range[i]);
		}

		//to find best candidate
		Result best_candidate, best_non_tabu_candidate;
		for (int i = 0; i < candidate_set.size(); ++i){
			if (best_candidate.is_null() || candidate_set[i].better(&best_candidate))
				best_candidate = candidate_set[i];
			if (find_in_tabu_list(tabu_list, candidate_set[i]) == tabu_list.size()){
				if (best_non_tabu_candidate.is_null() || candidate_set[i].better(&best_non_tabu_candidate))
					best_non_tabu_candidate = candidate_set[i];
			}
		}

//		cout << "loop: " << loop << "   " << best_candidate.swap_record[0] << "   " << best_candidate.swap_record[1] << endl;
//		cout << "loop: " << loop << "   " << best_non_tabu_candidate.swap_record[0] << "   " << best_non_tabu_candidate.swap_record[1] << endl;

		if (find_in_tabu_list(tabu_list, best_candidate) == tabu_list.size()//not in tabu_list
			|| (find_in_tabu_list(tabu_list, best_candidate) != tabu_list.size() && best_candidate.better(&best))//in tabu_list //not sure
			|| best_non_tabu_candidate.is_null())
		{
			current = best_candidate;
		}
		else {
			current = best_non_tabu_candidate;
		}
/*
		cout << "loop" << loop << ": " << endl;
		cout << current.swap_record[0] << "  " << current.swap_record[1] << endl;
		for (int i = 0; i < current.items_order.size(); ++i)
			cout << current.items_order[i] << " ";
		cout << endl;
*/

		if (tabu_list.size() == 0){
			vector<int> vec;
			vec.push_back(current.swap_record[0]);
			vec.push_back(current.swap_record[1]);
			tabu_list.push_front(vec);
		}
		else {
			int index = find_in_tabu_list(tabu_list, current);
			if (index != tabu_list.size()){//is in tabu_list
				auto iter = tabu_list.begin() + index;
				iter = tabu_list.erase(iter);
			}
			if (tabu_list.size() == tabu_tenure){
				tabu_list.pop_back();
			}
			vector<int> vec;
			vec.push_back(current.swap_record[0]);
			vec.push_back(current.swap_record[1]);
			tabu_list.push_front(vec);
		}

		if (current.better(&best)){
//			cout << "------true------" << endl;
			best = current;
		}
/*
		cout << "loop" << loop << ": " << endl;
		for (int i = 0; i < tabu_list.size(); ++i)
			cout << tabu_list.at(i)[0] << " " << tabu_list.at(i)[1] << endl;
*/
	}
/*
	cout << best.swap_record[0] << "  " << best.swap_record[1] << endl;
	for (int i = 0; i < best.items_order.size(); ++i)
		cout << best.items_order[i] << " ";
	cout << endl;
*/
	return best.get_bins_count();
}
/**/
/*int tabu_search(){
	Data data(n, c, items);
	Result current;
	current.create_random_result(current, data);
	cout << "random_FF: " << current.get_bins_count() << endl;

	int** tabu_list = new int*[n];
	for (int i = 0; i < n; ++i){
		tabu_list[i] = new int[n];
		for (int j = 0; j < n; ++j)
			tabu_list[i][j] = 0;
	}

	int tabu_tenure = 3;//to be determined
	Result best = current;

	int loop = LOOP_TIMES;
	srand((unsigned)time(NULL));
	while (loop--){
		Range neighbor_range = current.get_neighbor_range_swap(true, data); //to be modified
		vector<Result> candidate_set;

		if (neighbor_range.neighbors.empty()) break;

		while (!neighbor_range.empty()){
			Result neighbor = neighbor_range.next();
			if (candidate_set.empty() || ((rand() % (neighbor_range.neighbors.size())) / (double)(neighbor_range.neighbors.size())) > 0.3)
				candidate_set.push_back(neighbor);
		}


		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (tabu_list[i][j] > 0)
					--tabu_list[i][j];
			}
		}		

		//to find best candidate
		Result best_candidate, best_non_tabu_candidate;
		for (int i = 0; i < candidate_set.size(); ++i){
			if (best_candidate.is_null() || candidate_set[i].better(&best_candidate))
				best_candidate = candidate_set[i];
			if (tabu_list[candidate_set[i].swap_record[0]][candidate_set[i].swap_record[1]] == 0){
				if (best_non_tabu_candidate.is_null() || candidate_set[i].better(&best_non_tabu_candidate))
					best_non_tabu_candidate = candidate_set[i];
			}
		}

		//if the best candidate is in tabu list
		if ((tabu_list[best_candidate.swap_record[0]][best_candidate.swap_record[1]] == 0) 
			|| (tabu_list[best_candidate.swap_record[0]][best_candidate.swap_record[1]] > 0 && best_candidate.better(&best))//not sure
			|| best_non_tabu_candidate.is_null())
		{
			current = best_candidate;
		}
		else {
			current = best_non_tabu_candidate;
		}
		tabu_list[current.swap_record[0]][current.swap_record[1]] = tabu_tenure;

		if (current.better(&best))
			best = current;
	}
	return best.get_bins_count();
}*/

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