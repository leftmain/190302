#include <memory>
#include <time.h>
#include "student.h"
#include "list.h"
#include "errors.h"

#define DEBUG

typedef Student S;

void sort(Node<S> *);

int main(int argc, char ** argv) {
	List<S> l;
	int n = 0;
	err_code res;
	const char * filename = nullptr;
	FILE * fp = nullptr;
	double t = 0;

	if (argc < 2 || argc > 3 || (argc == 3 && (n = atoi(argv[2])) <= 0)) {
		printf("usage: %s [filename] [n]\n", argv[0]);
		return -1;
	} filename = argv[1];
	if (!(fp = fopen(filename, "r"))) {
		printf("Cannot open %s\n", filename);
		return -2;
	}

	if ((res = l.read(fp, n))) {
		switch (res) {
			case MEM_ERR:
				printf("Not enough memory\n");
				break;
			case CANNOT_READ:
				printf("Cannot read %s\n", filename);
				break;
			case CANNOT_OPEN:
				printf("Cannot open %s\n", filename);
				break;
			default:
				printf("Unknown error\n");
		}
		fclose(fp);
		return -3;
	} fclose(fp);

	l.print();
	t = clock();
//	l.bubble();
//	l.min_sort();
	l.lin_sort();
//	l.merge_sort();
//	l.quick();
	t = (clock() - t) / CLOCKS_PER_SEC;
	l.print();
#ifdef DEBUG
	const char * out_file = "out.txt";
	if (!(fp = fopen(out_file, "w"))) { printf("Cannot open %s\n", out_file); return -4; }
	l.print(fp);
	fclose(fp);
#endif
	printf("Time: %.2lf\n", t);

	return 0;
}

