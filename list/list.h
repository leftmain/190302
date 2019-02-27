#ifndef LIST_H
#define LIST H

#include "node.h"

#define MAX_PRINT 10

template <class T>
class List
{
private:
	Node<T> * head = 0;
	Node<T> * curr = 0;

	void destroy() {
		Node<T> * c = head;
		while (c) {
			curr = c->get_next();
			delete c;
			c = curr;
		}
		head = curr = 0;
	}

public:
	List() {}
	~List() { destroy(); }
	
	void goto_head() { curr = head.get(); }
	void goto_next() { curr = curr->get_next(); }
	Node<T> * get_head() const { return head; }
	Node<T> * get_curr() const { return curr; }

	err_code read(FILE * fp, int n = 0) {
		Node<T> * c = new Node<T>;
		if (!c) { delete c; return MEM_ERR; }
		err_code res = c->read(fp);
		if (res) { delete c; return res; }
		curr = head = c;
		if (n > 0) {
			for (int i = 1; i < n; i++) {
				if (!(c = new Node<T>)) return MEM_ERR;
				if ((res = c->read(fp))) { delete c; return res; }
				curr->set_next(c);
				curr = curr->get_next();
			}
		} else {
			Node<T> a;
			while (!(res = a.read(fp))) {
				if (!(c = new Node<T>)) return MEM_ERR;
				curr->set_next(c);
				*c == a;
				a.clear();
				curr = curr->get_next();
			}
			if (res == MEM_ERR || (res == CANNOT_READ && !feof(fp))) return res;
		}
		return ALL_RIGHT;
	}
	void print(FILE * fp = stdout) {
		Node<T> * c = head;
		int n = MAX_PRINT;
		while (c && n > 0) {
			c->print(fp);
			c = c->get_next();
			n--;
		}
		printf("\n");
	}

	// BUBBLE
	void bubble(Node<T> * a = 0) {
		if (!a) a = head;
		Node<T> * last = 0, * h = a;
		while (h->get_next() != last) {
			while (a->get_next() != last) {
				if ((*a < *a->get_next()) > 0) a->swap(*a->get_next());
				a = a->get_next();
			}
			last = a;
			a = h;
		}
	}
	
	// MIN
	void min_sort(Node<T> * a = 0) {
		if (!a) a = head;
		Node<T> * h = a, * min;
		while (h->get_next()) {
			a = (min = h)->get_next();
			while (a) {
				if ((*a < *min) < 0) min = a;
				a = a->get_next();
			}
			h->swap(*min);
			h = h->get_next();
		}
	}

	// LIN
	void lin_sort(Node<T> ** head = 0) {
		if (!head) head = &this->head;
		Node<T> * a = *head, * res = a, * curr;
		if (!a) return;
		a = a->get_next();
		res->set_next(0);
		while (a) {
			if ((*a < *res) <= 0) {
				curr = a->get_next();
				a->set_next(res);
				res = a;
				a = curr;
			} else {
				curr = res;
				while (curr->get_next()) {
					if ((*a < *curr->get_next()) <= 0) {
						Node<T> * c = a->get_next();
						a->set_next(curr->get_next());
						curr->set_next(a);
						a = c;
						break;
					}
					curr = curr->get_next();
				}
				if (!curr->get_next()) {
					curr->set_next(a);
					a = a->get_next();
					curr->get_next()->set_next(0);
				}
			}
		}
		*head = res;
	}

// MERGE
Node<T> * merge(Node<T> * a, Node<T> * b, Node<T> ** end) {
	Node<T> * res, * c;
	if ((*a < *b) < 0) {
		res = c = a;
		a = a->get_next();
	} else {
		res = c = b;
		b = b->get_next();
	}
	while (a && b) {
		if ((*a < *b) < 0) {
			c->set_next(a);
			a = a->get_next();
		} else {
			c->set_next(b);
			b = b->get_next();
		}
		c = c->get_next();
	}
	if (a) c->set_next(a);
	else c->set_next(b);
	while (c->get_next()) c = c->get_next();
	*end = c;
	return res;
}
void merge_sort(Node<T> ** head = 0) {
	if (!head) head = &this->head;
	Node<T> * a = *head, * begin = a, * last, * first, * second, * end0, *end1;
	int k = 1, i;
	while (1) {
		first = last = a = begin;
		end0 = 0;
		for (i = 0; i < k - 1; i++) {
			if (!a->get_next()) {
				*head = begin;
				return;
			} a = a->get_next();
		}
		if (!a->get_next()) {
			*head = begin;
			return;
		}
		second = a->get_next();
		a->set_next(0);
		a = second;
		for (i = 0; i < k - 1; i++) {
			if (!a->get_next()) {
				*head = merge(first, second, &end1);
				return;
			} a = a->get_next();
		}
		if (!a->get_next()) {
			*head = merge(first, second, &end1);
			return;
		}
		last = a->get_next();
		a->set_next(0);
		begin = merge(first, second, &end1);
		a = last;
		last = begin;
		while (a) {
			first = a;
			for (i = 0; i < k - 1; i++) {
				if (!a->get_next()) {
					last = merge(last, first, &end1);
					if (end0) end0->set_next(last);
					else { *head = last; return; }
					break;
				} a = a->get_next();
			} if (i < k - 1) break;
			if (!a->get_next()) {
				last = merge(last, first, &end1);
				if (end0) end0->set_next(last);
				else { *head = last; return; }
				break;
			}
			if (end0) end0->set_next(last);
			end0 = end1;
			second = a->get_next();
			a->set_next(0);
			a = second;
			for (i = 0; i < k - 1; i++) {
				if (!a->get_next()) {
					last = merge(first, second, &end1);
					end0->set_next(last);
					break;
				} a = a->get_next();
			} if (i < k - 1) break;
			if (!a->get_next()) {
				end0->set_next(merge(first, second, &end1));
				break;
			}
			last = a->get_next();
			a->set_next(0);
			a = last;
			last = merge(first, second, &end1);
		}
		k *= 2;
	}
	*head = begin;
}

// QUICK
void f(Node<T> * a, Node<T> * x, Node<T> ** bb, Node<T> ** cc, int * dif) {
// b: <= a
// c: > a
	Node<T> * b = *bb = 0, * c = *cc = 0;
	int bl = 0, cl = 0;
	while (a) {
		if ((*a < *x) > 0) {
			if (!c) *cc = c = a;
			else {
				c->set_next(a);
				c = c->get_next();
			}
			cl++;
		} else {
			if (!b) *bb = b = a;
			else {
				b->set_next(a);
				b = b->get_next();
			}
			bl++;
		}
		a = a->get_next();
	}
	if (b) b->set_next(0);
	if (c) c->set_next(0);
	*dif = bl - cl;
}
void quick(Node<T> ** head = 0) {
	if (!head) head = &this->head;
	Node<T> * a = *head, * b, * c;
	int dif;
	if (a->get_next()) f(a, a, &b, &c, &dif);
	else { *head = a; return; }
	if (!b) *head = c;
	else if (!c) *head = b;
	else {
		quick(&b);
		quick(&c);
		*head = b;
		while (b->get_next()) b = b->get_next();
		b->set_next(c);
	}
}
};
/*
template <class T>
class List
{
private:
	std::shared_ptr<Node<T> *> head;
	Node<T> * curr = 0;
	int l = 0;

public:
	List() {}
	~List() {}
	
	void goto_head() { curr = head.get(); }
	void goto_next() { curr = curr->get_next(); }
	Node<T> * get_head() const { return head.get(); }
	Node<T> * get_curr() const { return curr; }

	err_code read(FILE * fp, int n = 0) {
		Node<T> a;
		err_code res = a.read(fp);
		if (res) return res;
		head = std::make_unique<Node<T> *>(std::move(a));
		curr = *head;
		if (n > 0) {
			for (int i = 1; i < n; i++) {
				if ((res = a.read(fp))) return res;
				if ((res = curr->init_next(a))) return res;
				curr = curr->get_next();
			}
		} else {
			while (!(res = a.read(fp))) {
				if ((res = curr->init_next(a))) return res;
				curr = curr->get_next();
			}
			if (res == MEM_ERR || (res == CANNOT_READ && !feof(fp))) return res;
		}
		return ALL_RIGHT;
	}
	void print(FILE * fp = stdout) {
		Node<T> * c = *head;
		int n = MAX_PRINT;
		while (c && n > 0) {
			c->print(fp);
			c = c->get_next();
			n--;
		}
		printf("\n");
	}
};
*/
#endif

