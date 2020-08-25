#include "Data_structure.h"

#define k 0.01
#define r 0.97
#define T 500
#define T_MIN 0.1
#define STEP 1000
#define ITERATION 200

vector<int> items;
int n, c;

void swap_items_and_get_order(int pos1, int pos2, vector<int>& origin_order){
	int temp = origin_order[pos1];
	origin_order[pos1] = origin_order[pos2];
	origin_order[pos2] = temp;
	return;
}

Result get_random_neighbor(int pos1, int pos2, const vector<int> & items_order){
	Result res;
	vector<int> order = items_order;
	swap_items_and_get_order(pos1, pos2, order);
	res.create_result(Data(n, c, order), pos1, pos2);
	return res;
}

double difference_calculator(const Result & New, const Result & Old){
	if (New.get_bins_count() != Old.get_bins_count())	
		return New.get_bins_count() - Old.get_bins_count();

	vector<int> bins1 = New.get_bins_weight();
	vector<int> bins2 = Old.get_bins_weight();
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
	current.create_random_result(data);
	cout << "Random_initial_solution: " << current.get_bins_count() << endl;

	double current_T = T;
	srand((unsigned)time(NULL));
	int count = ITERATION;

	while (current_T > T_MIN && count > 0){
		for (int i = 0; i < STEP; ++i){
			Result neighbor = get_random_neighbor(rand() % n, rand() % n, current.get_items_order());
			double diff = difference_calculator(neighbor, current);

			if (diff < 0){
				current = neighbor;
				count = ITERATION;
			}
			else {
				if (exp(-diff / (k * current_T)) > (rand() % 100) / (double)100){
					current = neighbor;
					count = ITERATION;
				}
				else 
					--count;
			}
		}
		current_T *= r;
	}
	return current.get_bins_count();
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
	int solution = simulated_annealing();
	cout << "Solution by simulated_annealing: " << solution << endl;
	clock_t end = clock();
	cout << fixed << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}