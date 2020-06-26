#pragma once
#include <iostream>
#include <vector>
#include <memory> //for smart pointers 


class graph {
public:
	graph( int _vertices = 0, double density = 0 );
	graph( graph& _graph );  //deep copy needed due to the use of smart pointers
	int vertice_num() { return vertices; }
	int edge_num() { return num_of_edges;}
	friend bool adjacent( graph& _graph, int x, int y );
	friend std::vector<int> neighbors( graph& _graph, int x );
	bool add( int x, int y, int value );
	bool remove( int x, int y );
	int get_edge_value( int x, int y );
	bool set_edge_value( int x, int y, int value );
	void print();

private:
	int vertices;
	int num_of_edges;
	std::unique_ptr<std::unique_ptr<int[]>[]> edges;
};
