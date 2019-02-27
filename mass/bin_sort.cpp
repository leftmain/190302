#include "student.h"

int bin_search(Student *, int, Student&);

void sort(std::unique_ptr<Student []>& a, int n) {
    Student x;
    int i, j, k;
    for (i = 1; i < n; i++) {
        if ((a[i] < a[0]) < 0) k = -1;
        else k = bin_search(a.get(), i, a[i]);
        x == a[i];
        for (j = 0; j < i - k - 1; j++) a[i - j] == a[i - j - 1];
        a[k + 1] == x;
    }
}

int bin_search(Student * a, int n, Student& x) {
    int i = 0, j = n - 1;

    if (n == 0) return 0;

    if ((x < a[n - 1]) > 0) return n - 1;
    if ((x < a[0]) < 0) return 0;
    
    while (i != j && i != j - 1) {
        if ((x < a[(i + j) / 2]) > 0) i = (i + j) / 2;
        else j = (i + j) / 2;
    }

    return i;
}

