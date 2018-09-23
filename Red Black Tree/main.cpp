#include <iostream>
#include "RBT.h"

using namespace std;

int main()
{
	RBTree<int> T;
	T.Insert(41);
	T.Insert(38);
	T.Insert(31);
	T.Insert(12);
	T.Insert(19);
	T.Insert(8);
	T.Traversal();
	getchar();
	return 0;
}