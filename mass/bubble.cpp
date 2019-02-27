#include "student.h"

void sort(std::unique_ptr<Student []>& a, int n) {
	int i = 0, j = 0;
    for (i = n; i > 1; i--)
        for (j = 1; j < i; j++)
            if ((a[j] < a[j-1]) < 0)
				a[j].swap(a[j-1]);
}

