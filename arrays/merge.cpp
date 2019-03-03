#include "student.h"
#include "array.h"

typedef std::unique_ptr<Student []> T;

void merge_sort(T&, T&, int);
void merge(Student *, Student *, Student *, int, int);

void sort(T& a, int n) {
//	auto b = std::make_unique<Student []>(n);
	auto b = std::unique_ptr<Student []>(new Student[n]);
	if (!b) {
		printf("Not enough memory\n");
		return;
	}
	merge_sort(a, b, n);
}

void merge_sort(T& a, T& b, int n) {
//	Student * c = a.get();
    int i = 1, j = 0;
    for (i = 1; i <= n / 2; i *= 2) {
        for (j = 0; j < n - 2 * i + 1; j += 2 * i)
            merge(a.get() + j, a.get() + j + i, b.get() + j, i, i);
        merge(a.get() + j, a.get() + j + i, b.get() + j, i, n - j - i);
		a.swap(b);
    }
    merge(a.get(), a.get() + j, b.get(), j, n - j);
	a.swap(b);
/*
    if (c != a.get()) {
		printf("#\n");
		for (i = 0; i < n; i++) b[i] == a[i];
	}
	b.reset(nullptr);
*/
}

void merge(Student * a, Student * b, Student * c, int n, int m) {
    int i = 0, j = 0, k = 0;
    for (k = 0; k < n + m; k++) {
        if (i < n) {
            if (j < m && (b[j] < a[i]) < 0) {
                c[k] == b[j];
                j++;
            } else {
                c[k] == a[i];
                i++;
            }
        } else {
            c[k] == b[j];
            j++;
        }
    }
}

