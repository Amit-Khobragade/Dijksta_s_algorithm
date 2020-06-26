#include "graph.h"
#include <ctime>   // for time for seeding the rand function
#include <stdlib.h> //for srand() and rand()

using namespace std;

graph::graph( int _vertices , double density  )
	:vertices{ _vertices }, num_of_edges{ 0 }
{
	//making a 2d dynamically assigned matrix by using smart pointers
	edges = std::make_unique<std::unique_ptr<int[]>[]>( vertices );
	for (int i = 0; i < vertices; ++i)
		edges[i] = std::make_unique<int[]>( vertices );

	//seeding time and then adding new values to the matrix
	srand( time( 0 ) );
	for (int i = 0; i < vertices; ++i)
		for (int j = 0; j < vertices; ++j) {
			double probablity = (rand() % 100) / 100;
			int value = (rand() % 10);
			if (probablity < density) {
				add( i, j, value );
				++num_of_edges;
			}
			else
				add( i, j, 0 );
		}
}

graph::graph( graph& _graph )
	:vertices{ _graph.vertices }, num_of_edges{ _graph.num_of_edges }
{

	edges = std::make_unique<std::unique_ptr<int[]>[]>( vertices );
	for (int i = 0; i <= vertices; ++i)
		edges[i] = std::make_unique<int[]>( vertices );

	//for copying matrix
	for (int i = 0; i < vertices; ++i)
		for (int j = 0; j < vertices; ++j)
			edges[i][j] = _graph.edges[i][j];
}

bool graph::add( int x, int y, int value ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	if (edges[x][y] == 0 && edges[y][x] == 0) {
		edges[x][y] = edges[y][x] = value;
		++num_of_edges;
		return true;
	}
	return false;
}

bool graph::remove( int x, int y ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	if (edges[x][y] != 0 && edges[y][x] != 0) {
		edges[x][y] = edges[y][x] = 0;
		--num_of_edges;
		return true;
	}
	return false;
}

int graph::get_edge_value( int x, int y ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	return edges[x][y];
}

bool graph::set_edge_value( int x, int y, int value ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	edges[x][y] = edges[y][x] = 0;
	--num_of_edges;
	return add( x, y, value );
}


bool adjacent( graph& _graph, int x, int y ) {
	if (x > _graph.vertices && x<0 && y>_graph.vertices && y < 0)
		throw "out_of_range";
	if (_graph.edges[x][y] != 0 || _graph.edges[y][x] != 0)
		return true;
	return false;
}

std::vector<int> neighbors( graph& _graph, int x ) {
	if (x > _graph.vertices && x < 0)
		throw "out_of_range";
	vector<int> temp;
	for (int i = 0; i < _graph.vertice_num(); ++i)
		if (_graph.edges[x][i] > 0)
			temp.push_back( i );
	return temp;
}

void graph::print() {
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j)
			cout << edges[i][j] << " ";
		cout << endl;
	}
}