// example1.cpp

int foo(int param) {
	if (param) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char* argv[]) {
	foo(0);
	foo(1);
	foo(2);
	return 0;
}
