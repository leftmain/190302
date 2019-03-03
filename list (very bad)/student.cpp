#include "student.h"

#ifndef FAST
err_code Student::init(const char * n, int v) {
	value = v;
	if (n) {
		name = std::unique_ptr<char []>(new char[strlen(n) + 1]);
	// name = std::make_unique<char []>(strlen(n) + 1);
		if (!name) return MEM_ERR;
		strcpy(name.get(), n);
	} else name = 0;
	return ALL_RIGHT;
}

Student::Student(const Student& a) {
	int err = 0;
	if ((err = init(a.name.get(), a.value))) {
		printf("%d error in Student& constructor\n", err);
	}
}

Student::Student(Student&& a) : Student() {
	value = a.value;
	name = std::move(a.name);
	a.value = 0;
	a.name = 0;
}

Student::Student(const char * n, int v) {
	int err = 0;
	if ((err = init(n, v))) {
		printf("%d error in Student(n, v) constructor\n", err);
	}
}

Student& Student::operator=(const Student& rhs) {
	int err = 0;
	if ((err = init(rhs.name.get(), rhs.value))) {
		printf("%d error in operator=\n", err);
	}
	return *this;
}

void Student::operator==(Student& rhs) {
	name = std::move(rhs.name);
	value = rhs.value;
}

int Student::operator<(const Student& rhs) const {
	if (name.get() && rhs.name.get()) {
		int res = strcmp(name.get(), rhs.name.get());
		if (res) return res;
		return value - rhs.value;
	}
	if (!name.get() && rhs.name.get()) return -1;
	if (name.get() && !rhs.name.get()) return 1;
	return value - rhs.value;
}

err_code Student::read(FILE * fp) {
	char buf[LEN];
	int v;
	if (fscanf(fp, "%s%d", buf, &v) != 2) return CANNOT_READ;
	return init(buf, v);
}

void Student::print(FILE * fp) const {
	fprintf(fp, "(%s %d) ", name.get(), value);
}

void Student::printn(FILE * fp) const {
	fprintf(fp, "%s %d\n", name.get(), value);
}

void Student::swap(Student& a) {
	name.swap(a.name);
	int v = value;
	value = a.value;
	a.value = v;
}
#endif

