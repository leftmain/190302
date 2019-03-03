#include <stdio.h>
#include "student.h"

int main(int argc, char ** argv) {
	const char * sorted = "sorted.txt";
	const char * file = nullptr;
	FILE * fp0, *fp1;
	Student x0, x1;

	if (argc < 2) file  = "out.txt";
	else file = argv[1];
	
	if (!(fp0 = fopen(sorted, "r"))) {
		printf("Cannot open %s\n", sorted);
		return -1;
	}
	if (!(fp1 = fopen(file, "r"))) {
		printf("Cannot open %s\n", file);
		fclose(fp0);
		return -1;
	}

	while (!x0.read(fp0) & !x1.read(fp1)) {
		if ((x0 < x1) != 0) {
			printf("No: ");
			x0.print(); printf(" ");
			x1.print(); printf("\n");
			fclose(fp0);
			fclose(fp1);
			return 0;
		}
	}

//	printf("Yes\n");
///*
	if (!feof(fp0)) {
		if (feof(fp1)) printf("No\n");
		else printf("Yes\n");
	} else {
		if (feof(fp1)) printf("Yes\n");
		else printf("No\n");
	}
//*/

	fclose(fp0);
	fclose(fp1);
	return 0;
}
