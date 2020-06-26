#include "priority_queue.h"

int Priority_Queue::find( int key,int start_pt ) const {
	if (!(start_pt < size() && start_pt >= 0))
		throw "out_of_range";
	if (queue.at( start_pt ).key == key)
		return start_pt;
	int left{ left_child( start_pt ) }, right{ right_child( start_pt ) };
	int result{ -1 };
	if (left != -1)
		result = find( key, left );
	if (right != -1 && result == -1)
		result = find( key, right );
	return result;
	//recurring functions makes the code readable
	//but increases the load make sure you have a proper
	//data structure like binary tree which reduces resource 
	//cost and time taken 
}

bool Priority_Queue::change_priority( const int& key_to_change, const int& new_value ) {
	int i = find( key_to_change );
	if (i == -1)
		return false;
	queue.at( i ).priority = new_value;
	while (i > 0 && queue.at( i ) <= queue.at( parent( i ) )) {
		std::swap( queue.at( i ), queue.at( parent( i ) ) );
		i = parent( i );
	}
	for (; i == -1 || i == -2; i = family_sort( i ));
	//sorting upwards and downwards after a sort
}

bool Priority_Queue::insert( queue_element& to_insert ) {
	queue.push_back( to_insert );
	int i{ size()-1 };
	while (i > 0 && queue.at( i ) <= queue.at( parent( i ) )) {
		std::swap( queue.at( i ), queue.at( parent( i ) ) );
		i = parent( i );
	}
	return true;
	//sorting on insertion and deletion makes the 
	//queue maintainance easy and less heavy
	//on time and resources
}

void Priority_Queue::pop() {
	std::swap( queue.at( 0 ), queue.at( (size() - 1) ) );
	queue.pop_back();
	for (int j = 0; j != -1 && j != -2; j = family_sort( j ));
	//uses the family sort function(line 62)
	//for the easy arrangement
}

inline void Priority_Queue::min_heapify() {
	sort_all( 0 );
}

inline void Priority_Queue::sort_all( int i ) {
	int left{ left_child( i ) }, right{ right_child( i ) };
	int j = family_sort( i );
	if (j == -2)
		return;
	if (left != -1)
		sort_all( left );
	if (right != -1)
		sort_all( right );
}

inline int Priority_Queue::family_sort( int _parent ) {
	if (!(_parent < size() && _parent >= 0))
		return -1;
	int left{ left_child( _parent ) };
	int right{ right_child( _parent ) };
	int j{ -1 };
	if (left != -1 && right != -1)
		j = ((queue.at( left ) < queue.at( right )) ? left : right);

	else if (left != -1)
		j = left;

	else
		return -2;
	
	if (j != -1 && (queue.at( _parent ) > queue.at( j ))) {
		std::swap( queue.at( _parent ), queue.at( j ) );
		return j;
	}
	return -1;
	//if returned value is =-1 then nodes exists below the current parent  
	//but the current family is sorted
	//if returned value is =-2 then the current node is the last parent
	//and has no child
}
