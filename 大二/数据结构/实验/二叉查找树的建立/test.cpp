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
	cout << "Ç°Ðò£º ";
	tree.PreOrder();
	cout << "ÖÐÐò£º ";
	tree.InOrder();
	cout << "ºóÐò£º ";
	tree.PostOrder();
	cout << "²ãÐò£º ";
	tree.LevelOrder();
	tree.graph(cout);
	cout << "Ò¶£º ";
	cout << tree.countleaf() << endl;
	cout << "Ê÷¸ß£º ";
	cout << tree.height() << endl;
	cout << endl << endl;

	tree.exchange();
	tree.graph(cout);
	cout << endl << endl;

	tree.remove(7);
	tree.graph(cout);
	cout << "Ò¶£º ";
	cout << tree.countleaf() << endl;
	cout << "Ê÷¸ß£º ";
	cout << tree.height() << endl;
	return 0;
}