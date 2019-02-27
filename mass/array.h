#ifndef ARRAY_H
#define ARRAY_H

#include "errors.h"

#define MAX_PRINT 20

template <class T>
err_code read_array(std::unique_ptr<T []>& a, int n, const char * name) {
	FILE * fp;

	a = std::make_unique<T []>(n);
	if (!a) {
		printf("Not enough memory\n");
		return MEM_ERR;
	}
	if (!(fp = fopen(name, "r"))) return CANNOT_OPEN;
	for (int i = 0; i < n; i++) {
		err_code res = (a)[i].read(fp);
		if (res > 0) {
			fclose(fp);
			return res;
		}
	}
	fclose(fp);
	return ALL_RIGHT;
}

template <class T>
err_code read_array(T * a, int n, const char * name) {
	FILE * fp;

	if (!(fp = fopen(name, "r"))) return CANNOT_OPEN;
	for (int i = 0; i < n; i++) {
		err_code res = a[i].read(fp);
		if (res > 0) {
			fclose(fp);
			return res;
		}
	}
	fclose(fp);
	return ALL_RIGHT;
}

template <class T>
void print_array(std::unique_ptr<T []>& a, int n, FILE * fp = stdout) {
	if (n > MAX_PRINT) n = MAX_PRINT;
	for (int i = 0; i < n; i++) a[i].printn(fp);
	printf("\n");
}

template <class T>
void print_array(T * a, int n, FILE * fp = stdout) {
	if (n > MAX_PRINT) n = MAX_PRINT;
	for (int i = 0; i < n; i++) a[i].printn(fp);
	printf("\n");
}

#endif

