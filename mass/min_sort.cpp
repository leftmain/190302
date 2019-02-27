#include "student.h"

void sort(std::unique_ptr<Student []>& a, int n) {
	auto min = a.get();
    int i = 1, j = 0;
	for (; i < n - 1; i++) {
		for (j = i + 1; j < n; j++)
			if ((a[j] < (*min)) < 0)
				min = a.get() + j;
		a[i-1].swap(*min);
		min = a.get() + i;
	}
}

