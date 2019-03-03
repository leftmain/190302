#include "student.h"
#include "array.h"

int ml_sort(Student *, int, Student);
void quick_sort(Student * a, int n);

void sort(std::unique_ptr<Student []>& a, int n) {
	quick_sort(a.get(), n);
}

void quick_sort(Student * a, int n) {
    int i = 0;
    while (n > 1) {
        i = ml_sort(a, n, a[n >> 1]);
        if (i < n - i) {
            quick_sort(a, i);
            a += i;
            n -= i;
        } else {
            quick_sort(a + i, n - i);
            n = i;
        }
    }
}

int ml_sort(Student * a, int n, Student x) {
    int i = 0, j = n - 1;

    while (i < j) {
        if ((a[i] < x) >= 0) {
            while (i < j) {
                if ((a[j] < x) <= 0) {
					a[i].swap(a[j]);
                    break;
                }
                j--;
            }
        }
        if (i < j) i++;
    }

    return i;
}

