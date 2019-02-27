#ifndef STUDENT_H
#define STUDENT_H

#include <memory>
#include <string.h>
#include <stdio.h>
#include "errors.h"

#define LEN 1024
#define FAST

#ifndef FAST
class Student
{
private:
	std::unique_ptr<char []> name;
	int value = 0;

	err_code init(const char * = 0, int = 0);

public:
	Student(const Student&);
	Student(Student&&);
	Student(const char * = nullptr, int = 0);
	~Student() {}

	Student& operator=(const Student&);
	void operator==(Student&);
	int operator<(const Student&) const;
	err_code read(FILE *);
	void print(FILE * = stdout) const;
	void printn(FILE * = stdout) const;
	void swap(Student&);
	char * get_name() const { return name.get(); }
	int get_value() const { return value; }

};
#endif


// ------------------------------------------------------------


#ifdef FAST
class Student
{
private:
	std::unique_ptr<char []> name;
	int value = 0;

	err_code init(const char * n = 0, int v = 0) {
		value = v;
		if (n) {
			name = std::unique_ptr<char []>(new char[strlen(n) + 1]);
		// name = std::make_unique<char []>(strlen(n) + 1);
			if (!name) return MEM_ERR;
			strcpy(name.get(), n);
		} else name = 0;
		return ALL_RIGHT;
	}

public:
	Student(const Student& a) { init(a.name.get(), a.value); }
	Student(Student&& a) { value = a.value; name = std::move(a.name); a.value = 0; }
	Student(const char * n = nullptr, int v = 0) { init(n, v); }
	~Student() {}

	Student& operator=(const Student& rhs) {
		int err = 0;
		if ((err = init(rhs.name.get(), rhs.value))) {
			printf("%d error in operator=\n", err);
		}
		return *this;
	}
	Student& operator=(Student&& rhs) {
		name = std::move(name);
		value = rhs.value;
		return *this;
	}
	void operator==(Student& rhs) {
		name = std::move(rhs.name);
		value = rhs.value;
	}
	int operator<(const Student& rhs) const {
		if (name.get() && rhs.name.get()) {
			int res = strcmp(name.get(), rhs.name.get());
			if (res) return res;
			return value - rhs.value;
		}
		if (!name.get() && rhs.name.get()) return -1;
		if (name.get() && !rhs.name.get()) return 1;
		return value - rhs.value;
	}
	err_code read(FILE * fp) {
		char buf[LEN];
		int v;
		if (fscanf(fp, "%s%d", buf, &v) != 2) return CANNOT_READ;
		return init(buf, v);
	}
	void print(FILE * fp = stdout) const {
		fprintf(fp, "(%s %d)", name.get(), value);
	}
	void printn(FILE * fp = stdout) const {
		fprintf(fp, "%s %d\n", name.get(), value);
	}
	void swap(Student& a) {
		name.swap(a.name);
		int v = value;
		value = a.value;
		a.value = v;
	}
	char * get_name() const { return name.get(); }
	int get_value() const { return value; }

};
#endif

#endif

