#include "BST.h"
#include <vector>
int main()
{
	BSTree<int> tree;
	int arr[] = { 7,1,8,6,3,5,9 };
	for (auto e : arr)
	{
		tree.Insert(e);
	}
	cout << "ǰ�� ";
	tree.PreOrder();
	cout << "���� ";
	tree.InOrder();
	cout << "���� ";
	tree.PostOrder();
	cout << "���� ";
	tree.LevelOrder();
	tree.graph(cout);
	cout << "Ҷ�� ";
	cout << tree.countleaf() << endl;
	cout << "���ߣ� ";
	cout << tree.height() << endl;
	cout << endl << endl;

	tree.exchange();
	tree.graph(cout);
	cout << endl << endl;

	tree.remove(7);
	tree.graph(cout);
	cout << "Ҷ�� ";
	cout << tree.countleaf() << endl;
	cout << "���ߣ� ";
	cout << tree.height() << endl;
	return 0;
}