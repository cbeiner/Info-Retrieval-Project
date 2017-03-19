all:
	g++ FullFunction.cpp avlTree.cpp avlNode.h -std=c++11
	./a.out

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

