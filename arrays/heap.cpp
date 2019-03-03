#include "student.h"

void second_step(Student *, int);

void sort(std::unique_ptr<Student []>& a, int n) {
    Student x;
    int i, j;

    for (i = 1; i < n; i++) {
        x == a[i];
        j = i;
        while (j > 0) {
            if ((x < a[(j - 1) / 2]) > 0) {
                a[j] == a[(j - 1) / 2];
                j = (j - 1) / 2;
            } else break;
        }
        a[j] == x;
    }
    
    for (i = n - 1; i > 0; i--) {
		a[i].swap(a[0]);
        second_step(a.get(), i);
    }
}

void second_step(Student * a, int n) {
    Student x;
    int i = 0;
    x == a[0];
    while (1) {
        if (2 * i + 2 < n) {
            if ((a[2 * i + 1] < a[2 * i + 2]) > 0) {
                if ((x < a[2 * i + 1]) < 0) {
                    a[i] == a[2 * i + 1];
                    i = 2 * i + 1;
                } else break;
            } else {
                if ((x < a[2 * i + 2]) < 0) {
                    a[i] == a[2 * i + 2];
                    i = 2 * i + 2;
                } else break;
            }
        } else if (2 * i + 1 < n) {
            if ((x < a[2 * i + 1]) < 0) {
                a[i] == a[2 * i + 1];
                i = 2 * i + 1;
            } else break;
        } else break;
    }
    a[i] == x;
}

