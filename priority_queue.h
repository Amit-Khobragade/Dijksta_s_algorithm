#pragma once
#include <iostream>
#include <vector>

//single queue element with priority and some overloaded 
//operator for cleaner code
struct queue_element {
	int key;
	int priority;
	queue_element( int _key = 0, int _priority = 0 )
		:key{ _key }, priority{ _priority }
	{}
	bool operator<( const queue_element& other ) {
		return (this->priority < other.priority);
	}
	bool operator>( const queue_element& other ) {
		return (this->priority > other.priority);
	}
	bool operator>=( const queue_element& other ) {
		return (this->priority >= other.priority);
	}
	bool operator<=( const queue_element& other ){
		return (this->priority <= other.priority);
	}
};

//priority queue defined as an 
//binary tree
class Priority_Queue {
public:
	//three constructors
	//default constructor
	Priority_Queue() = default;
	//custom constructor
	Priority_Queue( queue_element& _first_elem ) {
		queue.push_back( _first_elem );
	}
	//copy constructor
	Priority_Queue( const Priority_Queue& other )
		:queue{other.queue}
	{
		for (int i = 0; i < other.queue.size(); ++i)
			queue.push_back( other.queue.at( i ) );
	}
	int find( int key, int start_pt = 0 ) const;
	bool change_priority( const int& key_to_change, const int& new_value );
	template<typename T>
	friend bool contains( const Priority_Queue& _queue, T& to_find );
	bool insert( queue_element& to_insert );
	inline queue_element top() { return ((size() != 0) ? queue.at( 0 ) : (-1)); }
	void pop();
	inline queue_element& at( int i ) { return queue.at( i ); }
	inline void min_heapify();
	inline int size() const { return queue.size(); }

private:
	std::vector<queue_element> queue;

	inline void sort_all( int i = 0 );
	inline int family_sort( int _parent );
	inline int parent( int i ) const {
		int temp = ((i % 2 == 0) ? ((i - 2) / 2) : ((i - 1) / 2));
		return ((temp < size() && temp >= 0) ? temp : (-1));
	}

	inline int left_child( int i ) const {
		int temp = 2 * i + 1;
		return ((temp < size() && temp >= 0) ? temp : (-1));
	}
	inline int right_child( int i ) const {
		int temp = 2 * i + 2;
		return ((temp < size() && temp >= 0) ? temp : (-1));
	}
};

template<typename T>
inline bool contains( const Priority_Queue& _queue, T& to_find ) {
	int i = _queue.find( static_cast< int >(to_find) );
	if (i != -1)
		return true;
	return false;
}