#include "student.h"
#include "list.h"

typedef Student T;
void sort(Node<T> * a) {
	Node<T> * last = 0, * head = a;
	while (head->get_next() != last) {
		while (a->get_next() != last) {
			if ((*a < *a->get_next()) > 0) a->swap(*a->get_next());
			a = a->get_next();
		}
		last = a;
		a = head;
	}
}

