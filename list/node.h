#ifndef NODE_H
#define NODE_H

#include <memory>
#include "errors.h"
//#include "student.h"

template <class T>
class Node : public T
{
private:
	Node<T> * next = 0;

public:
	Node(const char * n = 0, int v = 0) : T(n, v) {}
	Node(const Node<T>& i) : T(i) {}
	~Node() { }
	Node& operator=(const Node<T>& rhs) {
		*((T *)this) = rhs;
		next = 0;
		return *this;
	}
	Node<T> * get_next() const { return next; }
	void set_next(Node<T> * n) { next = n; }
	err_code init_next(Node<T>& a) {
		next = new Node<T>;
		if (!next) return MEM_ERR;
		(T *)next = std::move(a);
		return ALL_RIGHT;
	}
};
/*
template <class T>
class Node : public T
{
private:
	std::unique_ptr<Node<T> *> next;

public:
	Node(const char * n = 0, int v = 0) : T(n, v) {}
	Node(const Node<T>& i) : T(i) {}
	~Node() {}
	Node& operator=(const Node<T>& rhs) {
		*((T *)this) = rhs;
		next.rest(nullptr);
		return *this;
	}
	Node<T> * get_next() const { return *next; }
	void set_next(Node<T> * n) { *next = n; }
	err_code init_next(const Node<T>& a) { next = std::make_unique<Node<T> *>(a); if (!next) return MEM_ERR; return ALL_RIGHT; }
};
*/

#endif

