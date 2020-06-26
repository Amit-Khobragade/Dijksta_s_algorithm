#include "shortest_path.h"

dijkstra_s::dijkstra_s( int _start, int _end )
	:start_pt{ _start }, end_pt{ _end }, path_length{ INT_MAX }
{
}

int dijkstra_s::shortest_path_length( graph& G) {
	path_length = calc( G );
	return path_length;
}

dijkstra_s::~dijkstra_s() {
	path.clear();
}

inline int dijkstra_s::calc( graph& G ) {
	int size = G.vertice_num();
	if (start_pt >= size && start_pt < 0 && end_pt >= size && end_pt < 0)
		throw "out_of_range";
	path.clear();
	path.resize( size, -1 );
	Priority_Queue Q;
	for (int i = 0; i < size; ++i) {
		queue_element temp;
		temp.key = i;
		temp.priority = INT_MAX;
		Q.insert( temp );
	}
	Q.change_priority( start_pt, 0 );


	while (Q.size() > 0) {
		queue_element top = Q.top();
		Q.pop();
		if (top.priority == INT_MAX)
			return INT_MAX;
		if (top.key == end_pt)
			return top.priority;


		auto availiable_paths = neighbors( G, top.key );
		for (int i = 0; i < availiable_paths.size(); ++i) {
			int j{ Q.find( availiable_paths.at( i ) ) };
			if (j == -1)//error is here what he wants you to do is insert the priority as well
				continue;
			queue_element& temp = Q.at( j );
			int edge_length{ G.get_edge_value( top.key,temp.key ) };
			if (edge_length + top.priority < temp.priority) {
				path.at( temp.key ) = top.key;
				temp.priority = edge_length + top.priority;
				Q.change_priority( temp.key, temp.priority );
			}
		}
	}
	return INT_MAX;

}

