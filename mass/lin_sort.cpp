#include "student.h"

void sort(std::unique_ptr<Student []>& a, int n) {
	Student x;
	for (int i = 1, j = 0; i < n; i++) {
		x == a[i];
		j = i - 1;
		while (j >= 0 && (a[j] < x) > 0) {
			a[j + 1] == a[j];
			j--;
		}
		a[j + 1] == x;
	}
}

