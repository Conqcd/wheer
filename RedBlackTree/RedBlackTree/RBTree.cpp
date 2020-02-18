/*#include "RBTree.h"

template <class Comparable>
RBNode<Comparable>::RBNode(const Comparable & theElement = Comparable(), RBNode *lc = nullptr, RBNode *rc = nullptr, RBNode * pa = nullptr, TYPE col = TYPE::RED)
{
	element = theElement;
	lchild = lc;
	rchild = rc;
	parent = pa;
	colour = col;
}

template <class Comparable>
RBTree<Comparable>::RBTree<Comparable>()
{
	nullNode = new Node();
	root= nullNode;
}

template <class Comparable> 
RBTree<Comparable>::~RBTree<Comparable>()
{
	clear(root);
	delete	nullNode;
}

template <class Comparable>
bool RBTree<Comparable>::isEmpty()
{
	if (root == nullNode)
		return true;
	else	return false;
}

template <class Comparable>
bool RBTree<Comparable>::Insert(const Comparable & x)
{
	if (isEmpty())
	{
		RBNode<Comparable> *newb = new RBNode;
		root = newb;
		root->lchild = root->rchild = nullNode; root->colour = BLACK;
		root->element = x; root->parent = nullNode;
		nullNode->lchild = nullNode->rchild = root;
		return true;
	}
	RBNode<Comparable> *now = root, *last = nullptr;
	while (now!=nullNode)
	{
		last = now;
		if (now->element < x)
			now = now->rchild;
		else if (now->element > x)
			now = now->lchild;
		else return false;
	}
	RBNode<Comparable> *newb = new RBNode;
	newb->lchild = newb->rchild = now;	newb->element = x; newb->parent = last;
	if (last->element < x)		last->rchild = newb;
	else	last->lchild = newb;
	InsertFixUp(newb);
	return true;
}

template <class Comparable>
void RBTree<Comparable>::InsertFixUp(Node now)
{
	while (now->parent->colour==RED)
	{
		if (now->parent == now->parent->parent->lchild)
		{
			RBNode<Comparable> *uncle = now->parent->parent->rchild;
			if (uncle->colour==RED)
			{
				now->parent->colour = BLACK;
				uncle->colour = BLACK;
				uncle->parent = RED;
				now = uncle->parent;
			}
			else
			{
				if (now == now->parent->rchild)
				{
					now = now->parent;
					L(now);
				}
				now->parent->colour = BLACK;
				now->parent->parent->colour = RED;
				R(now->parent->parent);
			}
		}
		else
		{
			RBNode<Comparable> *uncle = now->parent->parent->lchild;
			if (uncle->colour == RED)
			{
				now->parent->colour = BLACK;
				uncle->colour = BLACK;
				uncle->parent = RED;
				now = uncle->parent;
			}
			else
			{
				if (now == now->parent->lchild)
				{
					now = now->parent;
					R(now);
				}
				now->parent->colour = BLACK;
				now->parent->parent->colour = RED;
				L(now->parent->parent);
			}
		}
		root->colour = BLACK;
	}
}

template <class Comparable>
bool RBTree<Comparable>::L(Node & now)
{
	if (now == nullNode || now->rchild==nullNode)
	{
		return false;
	}
	RBNode<Comparable> *temp=now->rchild;
	temp->parent = now->parent;
	now->rchild = temp->lchild;
	if (root == now)
	{
		nullNode->lchild = nullNode->rchild = temp;
		root = temp;
	}
	else
	{
		if (now == now->parent->lchild)
		{
			now->parent->lchild = temp;
		}
		else
		{
			now->parent->rchild = temp;
		}
	}
	if (temp->lchild != nullNode)
	{
		temp->lchild->parent = now;
	}
	now->parent = temp;
	temp->lchild = now;
	return true;
}

template <class Comparable>
bool RBTree<Comparable>::R(RBNode<Comparable> *& now)
{
	if (now == nullNode || now->lchild == nullNode)
	{
		return false;
	}
	RBNode<Comparable> *temp = now->lchild;
	temp->parent = now->parent;
	now->lchild = temp->rchild;
	if (root == now)
	{
		nullNode->rchild = nullNode->lchild = temp;
		temp->parent = nullNode;
		root = temp;
	}
	else
	{
		if (now == now->parent->rchild)
		{
			now->parent->rchild = temp;
		}
		else
		{
			now->parent->lchild = temp;
		}
	}
	if (temp->rchild != nullNode)
	{
		temp->rchild->parent = now;
	}
	now->parent = temp;
	temp->rchild = now;
	return true;
}

template <class Comparable>
RBNode<Comparable> *  RBTree<Comparable>::FindV(Comparable x)
{
	RBNode<Comparable> *fi=root;
	while (f!=nullNode)
	{
		if (fi->element < x)
			fi = fi->rchild;
		else if (fi->element > x)
			fi = fi->lchild;
		else	break;
	}
	return f;
}

template <class Comparable>
bool RBTree<Comparable>::Delete(const Comparable x)
{
	RBNode<Comparable> *delete_point = FindV(x);
	if (delete_point == nullNode)
	{
		return false;
	}if (delete_point->lchild!=nullNode&&delete_point->rchild!=nullNode)
	{
		RBNode<Comparable> successor = Find_Descendant_InOrderSuccessor(delete_point);
		delete_point->element = successor->element;
		delete_point = successor;
	}
	RBNode<Comparable> * delete_point_child;
	if (delete_point->rchild!=nullNode)
	{
		delete_point_child = delete_point->rchild;
	}
	else if (delete_point->lchild != nullNode)
	{
		delete_point_child = delete_point->lchild;
	}
	else
	{
		delete_point_child = nullNode;
	}
	delete_point_child->parent = delete_point->parent;
	if (delete_point == root)
	{
		root = nullNode;
		delete_point_child->lchild = delete_point_child->rchild = delete_point_child->parent = root;
	}
	else if (delete_point== delete_point->parent->lchild)
	{
		delete_point->parent = delete_point_child;
	}
	else
	{
		delete_point->parent = delete_point_child;
	}
	if (delete_point->colour==BLACK&&delete_point!=root)
	{
		DeleteFixUp(delete_point);
	}	
	delete delete_point;
	return true;
}

template <class Comparable>
void RBTree<Comparable>::DeleteFixUp(Node node)
{
	while (node->colour==BLACK&&node!=root)
	{
		if (node==node->parent->lchild)
		{
			RBNode<Comparable> *sibling=node->parent->rchild;
			if (sibling->colour==RED)
			{
				sibling->colour = BLACK;
				node->parent->colour = RED;
				L(node->parent);
				sibling = node->parent->rchild;
			}
			if (sibling->lchild->colour==BLACK&&sibling->rchild->colour==BLACK)
			{
				sibling->colour = RED;
				node = node->parent;
			}
			else
			{
				if (sibling->rchild->colour==BLACK)
				{
					sibling->lchild = BLACK;
					sibling->colour = RED;
					R(sibling);
					sibling = node->parent->rchild;
				}
				sibling->colour = node->parent->colour;
				node->parent->colour = BLACK;
				L(node->parent);
				node = root;
			}
		}
		else
		{
			RBNode<Comparable> *sibling = node->parent->lchild;
			if (sibling->colour == RED)
			{
				sibling->colour = BLACK;
				node->parent->colour = RED;
				L(node->parent);
				sibling = node->parent->lchild;
			}
			if (sibling->rchild->colour == BLACK&&sibling->lchild->colour == BLACK)
			{
				sibling->colour = RED;
				node = node->parent;
			}
			else
			{
				if (sibling->lchild->colour == BLACK)
				{
					sibling->rchild = BLACK;
					sibling->colour = RED;
					L(sibling);
					sibling = node->parent->lchild;
				}
				sibling->colour = node->parent->colour;
				node->parent->colour = BLACK;
				R(node->parent);
				node = root;
			}
		}
	}
	node->colour = BLACK;
}

template <class Comparable>
RBNode<Comparable> * RBTree<Comparable>::Find_Descendant_InOrderSuccessor(Node x)
{
	if (x == nullNode||x->rchild==nullNode)
	{
		return nullNode;
	}
	Node next = x->rchild;
	while (next->lchild!=nullNode)
	{
		next = next->lchild;
	}
	return next;
}

template <class Comparable>
RBNode<Comparable> * RBTree<Comparable>::Find_Descendant_InOrderProcessor(Node x)
{
	if (x == nullNode || x->rchild == nullNode)
	{
		return nullNode;
	}
	Node next = x->lchild;
	while (next->rchild != nullNode)
	{
		next = next->rchild;
	}
	return next;
}

template <class Comparable>
void RBTree<Comparable>::clear(Node x)
{
	if (x == nullNode)	return;
	else
	{
		clear(x->lchild);
		clear(x->rchild);
		delete x;
	}
}*/