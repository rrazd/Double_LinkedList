#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Object>
class Double_list {
	private:
		Double_node<Object> *list_head;
		Double_node<Object> *list_tail;
		int node_count; 

	public:
		Double_list();
		Double_list( const Double_list & );
		~Double_list();

		Double_list &operator = ( const Double_list & );

		// Accessors

		int size() const;
		bool empty() const;

		Object front() const;
		Object back() const;

		Double_node<Object> *head() const;
		Double_node<Object> *tail() const;

		int count( const Object & ) const;

		// Mutators

		void push_front( const Object & );
		void push_back( const Object & );

		Object pop_front();
		Object pop_back();

		int erase( const Object & );

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Double_list<T> & );
};

template <typename Object>
Double_list<Object>::Double_list():list_head(0), list_tail(0), node_count(0) {
	// empty constructor
}

template <typename Object>
Double_list<Object>::Double_list( const Double_list<Object> &list ):list_head(0), list_tail(0), node_count(0) {
	
	*this = list;
}

template <typename Object>
Double_list<Object>::~Double_list<Object>() {
	while (!empty()) {
		pop_front();
	}
}

template <typename Object>
Double_list<Object> &Double_list<Object>::operator = ( const Double_list<Object> &rhs ) {


 	if (rhs.empty()) {
		return *this;
	}
	
	while (!empty()) {
		pop_front();
	}
	
	
	
	Double_node<Object> *travel_rhs;
	
	travel_rhs = rhs.head();
	
	while (travel_rhs != 0) {
		
		push_back(travel_rhs -> retrieve());
		travel_rhs = travel_rhs -> next();
 		
	}
	
	return *this;
}

template <typename Object>
int Double_list<Object>::size() const {
	return node_count;
}

template <typename Object>
bool Double_list<Object>::empty() const {
	if (list_head == 0) {
		return true; 
	}
	return false;
}

template <typename Object>
Object Double_list<Object>::front() const {
	if (empty()) {
		throw overflow();
	}
	
	return head()-> retrieve();
}

template <typename Object>
Object Double_list<Object>::back() const {
	if (empty()) {
		throw overflow();
	}
	
	return tail()-> retrieve();
}

template <typename Object>
Double_node<Object> *Double_list<Object>::head() const {

	return list_head;
}

template <typename Object>
Double_node<Object> *Double_list<Object>::tail() const {
	return list_tail;
}

template <typename Object>
int Double_list<Object>::count( const Object &obj ) const {
	
	Double_node<Object> *travel;
	travel = head();
	
	while (travel != 0) {
	
		if(travel -> retrieve() == obj)
		{
			return 1;
		}
		
		travel = travel -> next();
	}
	
	return 0;

}

template <typename Object>
void Double_list<Object>::push_front( const Object &obj ) {
	
	Double_node<Object> *new_insertion;
	
	if (empty()) {
		new_insertion = new Double_node<Object>(obj, 0,0);
		list_head = new_insertion;
		list_tail = new_insertion;
	}
	else {
		//if list is not empty
		new_insertion = new Double_node<Object>(obj, 0, head());
		head() -> previous_node = new_insertion;
		list_head = new_insertion;
	}
	
	++node_count;
}

template <typename Object>
void Double_list<Object>::push_back( const Object &obj ) {
	
	Double_node<Object> *new_insertion;
	if (empty()) {
		new_insertion = new Double_node<Object>(obj, 0,0);
		list_head = new_insertion;
		list_tail = new_insertion;
	}
	 
	else{ 
		//if list is not empty
		new_insertion = new Double_node<Object>(obj, tail(), 0);
		tail() -> next_node = new_insertion;
	}
	
	++node_count;
}

template <typename Object>
Object Double_list<Object>::pop_front() {
	
	//empty
	if (empty()) {
		throw underflow();
	}
	
	
	Object hold;
	Double_node<Object> *temp;
	temp = head();

	
	//one node in list
	if (size()==1) {
		hold = temp -> retrieve();
		delete temp;
		list_head=0;
		list_tail=0;
		--node_count;
		return hold;
	}
	
	//multiple nodes
	else{
	list_head = head() -> next();
	hold = temp -> retrieve();
	delete temp;
	head() -> previous_node = 0;
	--node_count;
	return hold;
	}
}

template <typename Object>
Object Double_list<Object>::pop_back() {
	if (empty()) {
		throw underflow();
	}
	
	Object hold;
	
	Double_node<Object> *temp;
	
	temp = tail();
	
	list_tail = tail()-> previous();
	
	tail()->next_node = 0;
	
	hold = temp -> retrieve();
	delete temp;
	
	--node_count;
	return hold;
}

template <typename Object>
int Double_list<Object>::erase( const Object &obj ) {
	if (empty()) {
		throw underflow();
	}
	
	Double_node<Object> *traverse;
	traverse = head();
	
	while (traverse -> retrieve() != 0) {
		if (traverse -> retrieve() == obj) {
			if (size() == 1) {
 				list_head = 0;
				list_tail = 0;
			}
			
			else {
				Double_node<Object> *prev;
				Double_node<Object> *next;
				
				next = traverse -> next();
				prev = traverse -> previous();
				
				prev -> next_node = next;
				next -> previous_node = prev; 
			}

			delete traverse;
			--node_count;
			return 1;
		}
		
		traverse = traverse-> next();
	}
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Double_list<T> &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != 0; ptr = ptr->next() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != 0; ptr = ptr->previous() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
