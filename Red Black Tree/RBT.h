#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <stack>

using namespace std;

#define RED 0
#define BLACK 1

template<class T>
class RBTnode {
public:
	RBTnode() :lchild(NULL), rchild(NULL) ,parent(NULL), color(BLACK) {}
	T data;
	RBTnode<T>* lchild;
	RBTnode<T>* rchild;
	RBTnode<T>* parent;
	int color;
};

template<class T>
class RBTree {
public:
	RBTree() :root(nil) {}
	void Insert(T x);
	RBTnode<T>* Search(T x);
	void Delete(T x);
	void Traversal();
private:
	RBTnode<T>* root;
	static RBTnode<T>* nil;
	void LeftRotate(RBTnode<T>* &node);
	void RightRotate(RBTnode<T>* &node);
	void RB_Insert_Fixup(RBTnode<T>* &node);
	void RB_Insertnode(RBTnode<T>* &node, T x);
	void RB_Transplant(RBTnode<T>* &u, RBTnode<T>* &v);
	void RB_Delete_Fixup(RBTnode<T>* &node);
	void RB_Deletenode(RBTnode<T>* &node, T x);
	RBTnode<T>* get_minimum(RBTnode<T>* node);
	RBTnode<T>* Searchnode(RBTnode<T>* node, T x);
	void Preorder(RBTnode<T>* node);
};

template<class T>
RBTnode<T>* RBTree<T>::nil = new RBTnode<T>;

template<class T>
void RBTree<T>::LeftRotate(RBTnode<T>* &node)
{
	RBTnode<T>* rnode = node->rchild;
	node->rchild = rnode->lchild;
	if (rnode->rchild != nil)
	{
		rnode->lchild->parent = node;
	}
	rnode->parent = node->parent;
	if (node->parent == nil)
	{
		root = rnode;
	}
	else if (node == node->parent->lchild)
	{
		node->parent->lchild = rnode;
	}
	else
	{
		node->parent->rchild = rnode;
	}
	rnode->lchild = node;
	node->parent = rnode;
}

template<class T>
void RBTree<T>::RightRotate(RBTnode<T>* &node)
{
	RBTnode<T>* lnode = node->lchild;
	node->lchild = lnode->rchild;
	if (lnode->rchild != nil)
	{
		lnode->rchild->parent = node;
	}
	lnode->parent = node->parent;
	if (node->parent == nil)
	{
		root = lnode;
	}
	else if (node == node->parent->lchild)
	{
		node->parent->lchild = lnode;
	}
	else
	{
		node->parent->rchild = lnode;
	}
	lnode->rchild = node;
	node->parent = lnode;
}

template<class T>
void RBTree<T>::RB_Insert_Fixup(RBTnode<T>* &node)
{
	RBTnode<T>* ppnode;
	RBTnode<T>* qnode;
	while (node->parent->color == RED)
	{
		ppnode = node->parent->parent;
		if (node->parent == ppnode->lchild)
		{
			qnode = ppnode->rchild;
			if (qnode->color == RED)
			{
				node->parent->color = BLACK;
				qnode->color = BLACK;
				ppnode->color = RED;
				node = ppnode;
			}
			else
			{
				if (node == node->parent->rchild)
				{
					node = node->parent;
					LeftRotate(node);
				}
				node->parent->color = BLACK;
				ppnode->color = RED;
				RightRotate(ppnode);
			}
		}
		else
		{
			qnode = ppnode->lchild;
			if (qnode->color == RED)
			{
				node->parent->color = BLACK;
				qnode->color = BLACK;
				ppnode->color = RED;
				node = ppnode;
			}
			else
			{
				if (node == node->parent->lchild)
				{
					node = node->parent;
					RightRotate(node);
				}
				node->parent->color = BLACK;
				ppnode->color = RED;
				LeftRotate(ppnode);
			}
		}
	}
	root->color = BLACK;
}

template<class T>
void RBTree<T>::RB_Insertnode(RBTnode<T>* &node, T x)
{
	RBTnode<T>* newnode = new RBTnode<T>;
	newnode->data = x;
	newnode->color = RED;
	newnode->lchild = newnode->rchild = newnode->parent = nil;
	if (root == nil)
	{
		root = newnode;
	}
	else
	{
		RBTnode<T>* pnode = root;
		RBTnode<T>* qnode = nil;
		while (pnode != nil)
		{
			qnode = pnode;
			if (pnode->data > newnode->data)
			{
				pnode = pnode->lchild;
			}
			else
			{
				pnode = pnode->rchild;
			}
		}
		newnode->parent = qnode;
		if (qnode->data > newnode->data)
		{
			qnode->lchild = newnode;
		}
		else
		{
			qnode->rchild = newnode;
		}
	}
	RB_Insert_Fixup(newnode);
}

template<class T>
void RBTree<T>::RB_Transplant(RBTnode<T>* &u, RBTnode<T>* &v)
{
	if (u->parent == nil)
	{
		root = v;
	}
	else if (u == u->parent->lchild)
	{
		u->parent->lchild = v;
	}
	else
	{
		u->parent->rchild = v;
	}
	v->parent = u->parent;
}

template<class T>
void RBTree<T>::RB_Delete_Fixup(RBTnode<T>* &node)
{
	while (node != root && node->color == BLACK)
	{
		RBTnode<T>* qnode, pnode;
		if (node == node->parent->lchild)
		{
			qnode = node->parent->rchild;
			if (qnode->color == RED)
			{
				qnode->color = BLACK;
				node->parent->color = RED;
				LeftRotate(node->parent);
				qnode = node->parent->rchild;
			}
			if (qnode->lchild->color == BALCK && qnode->rchild->color == BALCK)
			{
				qnode->color = RED;
				node = node->parent;
			}
			else
			{
				if (qnode->rchild->color == BLACK)
				{
					qnode->lchild->color = BLACK;
					qnode->color = RED;
					RightRotate(qnode);
					qnode = node->parent->rchild;
				}
				qnode->color = node->parent->color;
				node->parent->color = BLACK;
				qnode->rchild->color = BLACK;
				LeftRotate(node->parent);
				node = root;
			}
		}
		else
		{
			qnode = node->parent->lchild;
			if (qnode->color == RED)
			{
				qnode->color = BLACK;
				node->parent->color = RED;
				RightRotate(node->parent);
				qnode = node->parent->lchild;
			}
			if (qnode->lchild->color == BLACK && qnode->rchild->color == BLACK)
			{
				qnode->color = RED;
				node = node->parent;
			}
			else
			{
				if (qnode->lchild->color == BLACK)
				{
					qnode->rchild->color = BLACK;
					qnode->color = RED;
					LeftRotate(qnode);
					qnode = node->parent->lchild;
				}
				qnode->color = node->parent->color;
				node->parent->color = BLACK;
				qnode->lchild->color = BLACK;
				RightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}

template<class T>
void RBTree<T>::RB_Deletenode(RBTnode<T>* &node, T x)
{
	RBTnode<T>* pnode = Searchnode(root, x);
	if (pnode != nil)
	{
		RBTnode<T>* qnode, tnode;
		qnode = pnode;
		int original_color = pnode->color;
		if (pnode->lchild == nil)
		{
			tnode = pnode->rchild;
			RB_Transplant(pnode, pnode->rchild);
		}
		else
		{
			qnode = get_minimum(pnode->rchild);
			original_color = qnode->color;
			tnode = qnode->rchild;
			if (qnode->parent == pnode)
			{
				tnode->parent = qnode;
			}
			else
			{
				RB_Transplant(qnode, qnode->rchild);
				qnode->rchild = pnode->rchild;
				qnode->rchild->parent = qnode;
			}
			RB_Transplant(pnode, qnode);
			qnode->lchild = pnode->lchild;
			qnode->lchild->parent = qnode;
			qnode->color = pnode->color
		}
		if (original_color == BLACK)
		{
			RB_Delete_Fixup(tnode);
		}
		delete pnode;
	}
}

template<class T>
RBTnode<T>* RBTree<T>::get_minimum(RBTnode<T>* node)
{
	RBTnode<T>* tnode = node;
	while (tnode->lchild != nil)
	{
		tnode = tnode->lchild;
	}
	return tnode;
}

template<class T>
RBTnode<T>* RBTree<T>::Searchnode(RBTnode<T>* node, T x)
{
	RBTnode<T>* pnode = node;
	while (pnode != nil)
	{
		if (pnode->data == x)
		{
			break;
		}
		else if (pnode->data > x)
		{
			pnode = pnode->lchild;
		}
		else
		{
			pnode = pnode->rchild;
		}
	}
	return pnode;
}

template<class T>
void RBTree<T>::Preorder(RBTnode<T>* node)
{
	if (node != NULL)
	{
		stack<RBTnode<T>*> s;
		RBTnode<T>* pnode = root;
		while (pnode != nil || !s.empty())
		{
			if (pnode != nil)
			{
				s.push(pnode);
				pnode = pnode->lchild;
			}
			else
			{
				pnode = s.top();
				s.pop();
				cout << pnode->data << ":";
				if (pnode->color == BLACK)
				{
					cout << "BLACK" << endl;
				}
				else
				{
					cout << "RED" << endl;
				}
				pnode = pnode->rchild;
			}
		}
	}
}

template<class T>
void RBTree<T>::Insert(T x)
{
	RB_Insertnode(root, x);
}

template<class T>
RBTnode<T>* RBTree<T>::Search(T x)
{
	return Searchnode(root, x);
}

template<class T>
void RBTree<T>::Delete(T x)
{
	RB_Deletenode(root, x);
}

template<class T>
void RBTree<T>::Traversal()
{
	Preorder(root);
}

#endif // !RBT_H



