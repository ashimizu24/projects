#include <iostream>
#include <cmath>
#include <string>

#include "splay.h"

using namespace std;

int main(){
	Splay<int, int> tree;
	//empty tree
	tree.print();

	//only root
	tree.insert(make_pair(3,3));
	tree.print();

	tree.insert(make_pair(4,4));
	tree.print();
	tree.insert(make_pair(1,1));
	tree.print();
	tree.insert(make_pair(2,2));
	tree.print();
	tree.insert(make_pair(6,6));
	tree.print();
	tree.insert(make_pair(5,5));
	

	//only left subtree
	tree.find(6);
	tree.erase(6);
	tree.print();
	//subtrees on both sides
	tree.find(3);
	tree.print();
	tree.erase(3);
	tree.print();
	//only right subtree
	tree.find(1);
	tree.print();
	tree.erase(1);
	tree.print();

	tree.insert(make_pair(8,8));
	tree.print();
	tree.insert(make_pair(0,0));
	tree.print();
	tree.insert(make_pair(6,6));
	tree.print();
	







	return 0;
}