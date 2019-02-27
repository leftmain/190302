#include <memory>
#include <time.h>
#include "student.h"
#include "array.h"
#include "errors.h"

//#define DEBUG

typedef Student S;

void sort(std::unique_ptr<S []>&, int);

int main(int argc, char ** argv) {
	std::unique_ptr<S []> a;
	int n = 0;
	err_code res;
	const char * filename = nullptr;
	double t = 0;

#ifdef DEBUG
	const char * out_file = "out.txt";
	if (argc < 3 || (n = atoi(argv[2])) <= 0) {
		printf("usage: %s [filename] [n] [out_file]\n", argv[0]);
		return -1;
	} filename = argv[1];
	if (argc == 4) out_file = argv[3];
#else
	if (argc != 3 || (n = atoi(argv[2])) <= 0) {
		printf("usage: %s [filename] [n]\n", argv[0]);
		return -1;
	} filename = argv[1];
#endif

	if ((res = read_array<S>(a, n, filename)) != ALL_RIGHT) {
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
		return -3;
	}

	print_array(a, n);
	t = clock();
	sort(a, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	print_array(a, n);
#ifdef DEBUG
	FILE * fp = fopen(out_file, "w");
	if (!fp) { printf("Cannot open out.txt\n"); return -4; }
	print_array(a, n, fp);
	fclose(fp);
#endif
	printf("Time: %.2lf\n", t);

	return 0;
}

