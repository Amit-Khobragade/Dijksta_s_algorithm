#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "graph.h"
#include "priority_queue.h"


class dijkstra_s {
public:
	dijkstra_s( int _start, int _end );
	int shortest_path_length(graph& G);
	~dijkstra_s();

private:
	inline int calc( graph& G );
	int path_length;
	const int start_pt, end_pt;
	std::vector<int> path;
};