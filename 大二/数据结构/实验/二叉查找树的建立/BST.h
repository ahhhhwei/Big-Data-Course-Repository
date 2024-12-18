#pragma once
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

template<class DataType>
class BSTree
{
	//节点 内部类
	template<class DataType>
	class BinNode
	{
	public:
		BinNode<DataType>* _left;
		BinNode<DataType>* _right;
		DataType _val;
		//书上两个合一起写了，带缺省值的构造函数
		BinNode(const DataType& val = DataType())
			:_left(nullptr)
			, _right(nullptr)
			, _val(val)
		{
			
		}
	};

	typedef BinNode<DataType> Node;
	typedef Node* NodePointer;
	
public:
	BSTree()
	{
		_root = nullptr;
	}
	BSTree(const BSTree<DataType>& t)
	{
		_root = CopyTree(t._root);
	}
	BSTree<DataType>& operator=(BSTree<DataType> t)
	{
		swap(_root, t._root);
		return *this;
	}
	~BSTree()
	{
		releaseTree(_root);
		_root = nullptr;
	}
	void exchange()
	{
		swap(_root->_left, _root->_right);
	}
	bool Insert(const DataType& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		NodePointer cur = _root;
		NodePointer parent = nullptr;
		while (cur)
		{
			if (cur->_val < val)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_val > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(val);
		if (parent->_val < val)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}
	// 没有借助search函数，所以没写search2
	bool remove(const DataType& key)
	{
		NodePointer parent = nullptr;
		NodePointer cur = _root;
		while (cur)
		{
			//找到要删除的节点的位置
			if (cur->_val < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_val > key)
			{
				parent = cur;
				cur = cur->_left;
			}

			//分3种情况删除
			else
			{
				//左为空，父亲指向我的右
				if (cur->_left == nullptr)
				{
					//if(parent==nullptr)
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				//右为空，父亲指向我的左
				else if (cur->_right == nullptr)
				{
					//if(parent==nullptr)
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}

				//两个孩子都不为空
				else
				{
					NodePointer minParent = cur;
					NodePointer minRight = cur->_right;
					while (minRight->_left)
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					swap(minRight->_val, cur->_val);
					if (minParent->_left == minRight)
					{
						minParent->_left = minRight->_right;
					}
					else
					{
						minParent->_right = minRight->_right;
					}
					delete minRight;
				}
				return true;
			}
		}
		return false;
	}
	bool Search(const DataType& key)
	{
		NodePointer cur = _root;
		while (cur)
		{
			if (cur->_val > key)
			{
				cur = cur->_left;
			}
			else if (cur->_val < key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}
	void InOrder()
	{
		//解决类外拿不到私有的问题
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
	}
	bool empty()const
	{
		return _root == nullptr;
	}
	int height()const
	{
		return _height(_root);
	}
	int countleaf()const
	{
		return _countleaf(_root);
	}
	void graph(ostream& out)const
	{
		graphAux(out, 0, _root);
	}
private:
	void releaseTree(NodePointer root)
	{
		if (root == nullptr)
		{
			return;
		}
		releaseTree(root->_left);
		releaseTree(root->_right);
		delete root;
	}
	//前序拷贝
	NodePointer CopyTree(NodePointer root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		NodePointer copyNode = new Node(root->_val);
		copyNode->_left = CopyTree(root->_left);
		copyNode->_right = CopyTree(root->_right);
		return copyNode;
	}
	void  _InOrder(NodePointer root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_val << ' ';
		_InOrder(root->_right);
	}
	void _PreOrder(NodePointer root)
	{
		if (root == nullptr)
		{
			return;
		}
		cout << root->_val << ' ';
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}
	void _PostOrder(NodePointer root)
	{
		if (root == nullptr)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_val << ' ';
	}
	void _LevelOrder(NodePointer root)
	{
		if (root == nullptr)
		{
			return;
		}
		queue<NodePointer> q;
		q.push(root);
		while (!q.empty())
		{
			root = q.front();
			q.pop();
			cout << root->_val << ' ';
			if (root->_left)
			{
				q.push(root->_left);
			}
			if (root->_right)
			{
				q.push(root->_right);
			}
		}
		cout << endl;
	}
	int _height(NodePointer _root)const
	{
		if (_root == nullptr)
		{
			return -1;
		}
		else
		{
			return _max(_height(_root->_left), 
				_height(_root->_right)) + 1;
		}
	}
	int _countleaf(NodePointer _root)const
	{
		if (_root->_left == nullptr && _root->_right == nullptr)
		{
			return 1;
		}
		else if (_root->_left == nullptr)
		{
			return _countleaf(_root->_right);
		}
		else if (_root->_right == nullptr)
		{
			return _countleaf(_root->_left);
		}
		else
		{
			return _countleaf(_root->_left) + _countleaf(_root->_right);
		}
	}
	
	int _max(int a, int b)const
	{
		return a > b ? a : b;
	}
	void graphAux(ostream& out, int indent, NodePointer subtreeroot)const
	{
		if (subtreeroot)
		{
			graphAux(out, indent + 8, subtreeroot->_right);
			out << setw(indent) << " " << subtreeroot->_val << endl;
			graphAux(out, indent + 8, subtreeroot->_left);
		}
	}
	NodePointer _root = nullptr;
	//c++11新特性，支持声明时给缺省值
};
