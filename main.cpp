#include <iostream>
#include "graph.h"
#include "shortest_path.h"

using namespace std;

//use visual studios 2019 for the best results
int main() {
	double densities[2] = { 0.2, 0.4 };
	int verticeNum = 50;
	for (int i = 0; i < 2; ++i) {
		int sum{ 0 }, count{ 0 };
		graph G{ verticeNum,densities[i] };
		for (int n = 1; n < 50; n++) {
			dijkstra_s path_length{ 0,n };
			int path = path_length.shortest_path_length( G );
			if (path != INT_MAX) {
				sum += path;
				count++;
			}
		}
		cout << "the average path length of density:" << densities[i]
			<< endl << " is: " << static_cast< double >(sum) / count << endl;
	}
	return 0;
}