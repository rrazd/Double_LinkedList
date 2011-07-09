#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#include "ece250.h"

template <typename Object>
class Double_list;

template <typename Object>
class Cyclic_double_list;

template <typename Object>
class Double_sentinel_list;

template <typename Object>
class Cyclic_double_sentinel_list;

template <typename Object>
class Double_node {
	private:
		Object       element;
		Double_node *previous_node;
		Double_node *next_node;

	public:
		Double_node( const Object & = Object(), Double_node * = 0, Double_node * = 0 );

		Object retrieve() const;
		Double_node *previous() const;
		Double_node *next() const;

		friend class Double_list<Object>;
		friend class Cyclic_double_list<Object>;
		friend class Double_sentinel_list<Object>;
		friend class Cyclic_double_sentinel_list<Object>;

		// if ptr is a pointer to a Double_node<Object> object
		// in one of the friendly classes, you should:
		//    use   this->next_node   to modify it
		//    use   this->next()      to access it
};

template <typename Object>
Double_node<Object>::Double_node( const Object &e, Double_node<Object> *p, Double_node<Object> *n ):element( e ), previous_node( p ), next_node( n )
{
	// empty constructor
}

template <typename Object>
Object Double_node<Object>::retrieve() const
{
	return element;
}

template <typename Object>
Double_node<Object> *Double_node<Object>::previous() const
{
	return previous_node;
}

template <typename Object>
Double_node<Object> *Double_node<Object>::next() const
{ 
	return next_node;
}

#endif
