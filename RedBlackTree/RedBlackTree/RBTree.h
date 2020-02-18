#ifndef RBTREE_H_
#define RBTREE_H_

#include<vector>
#include<iostream>
#include<cmath>
#include<Windows.h>
#include<queue>

//	#pragma once	这个效果根宏预处理一样

enum TYPE { BLACK, RED };

template <class Comparable>
class RBNode
{
public:
	Comparable			element;
	RBNode				*lchild;
	RBNode				*rchild;
	RBNode				*parent;
	TYPE				colour;
	RBNode(const Comparable & theElement = Comparable(), RBNode *lc = nullptr,
		RBNode *rc = nullptr, RBNode * pa = nullptr, TYPE col = TYPE::RED)
	{
		element = theElement;
		lchild = lc;
		rchild = rc;
		parent = pa;
		colour = col;
	}
private:

};

template <class Comparable>
class RBTree
{
public:
	typedef RBNode<Comparable> * Node;
	RBTree<Comparable>()
	{
		nullNode = new RBNode<Comparable>;
		root = nullNode;
		nullNode->colour = BLACK;
	}
	~RBTree<Comparable>()
	{
		clear(root);
		delete	nullNode;
	}
	bool isEmpty()
	{
		if (root == nullNode)
			return true;
		else	return false;
	}
	bool Insert(const Comparable & x)
	{
		if (isEmpty())
		{
			RBNode<Comparable> *newb = new RBNode<Comparable>;
			root = newb;
			root->lchild = root->rchild = nullNode; root->colour = BLACK;
			root->element = x; root->parent = nullNode;
			nullNode->lchild = nullNode->rchild = nullNode->parent = root;
			return true;
		}
		RBNode<Comparable> *now = root, *last = nullptr;
		while (now != nullNode)
		{
			last = now;
			if (now->element < x)
				now = now->rchild;
			else if (now->element > x)
				now = now->lchild;
			else return false;
		}
		RBNode<Comparable> *newb = new RBNode<Comparable>;
		newb->lchild = newb->rchild = now;	newb->element = x; newb->parent = last;
		if (last->element < x)		last->rchild = newb;
		else	last->lchild = newb;
		InsertFixUp(newb);
		return true;
	}
	Node FindV(Comparable x)
	{
		Node fi = root;
		while (fi != nullNode)
		{
			if (fi->element < x)
				fi = fi->rchild;
			else if (fi->element > x)
				fi = fi->lchild;
			else	break;
		}
		return fi;
	}
	bool Delete(const Comparable x)
	{
		Node delete_point = FindV(x);
		if (delete_point == nullNode)
		{
			return false;
		}if (delete_point->lchild != nullNode&&delete_point->rchild != nullNode)
		{
			Node successor = Find_Descendant_InOrderSuccessor(delete_point);
			delete_point->element = successor->element;
			delete_point = successor;
		}
		Node delete_point_child;
		if (delete_point->rchild != nullNode)
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
		else if (delete_point == delete_point->parent->lchild)
		{
			delete_point->parent->lchild = delete_point_child;
		}
		else
		{
			delete_point->parent->rchild = delete_point_child;
		}
		if (delete_point->colour == BLACK&&delete_point != root)
		{
			DeleteFixUp(delete_point_child);
		}
		delete delete_point;
		return true;
	}
	Node Find_Descendant_InOrderSuccessor(Node x)
	{
		if (x == nullNode || x->rchild == nullNode)
		{
			return nullNode;
		}
		Node next = x->rchild;
		while (next->lchild != nullNode)
		{
			next = next->lchild;
		}
		return next;
	}
	Node Find_Descendant_InOrderProcessor(Node x)
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
	void PreOrder(Node rt)
	{
		if (rt == nullNode)	return;
		cout << rt->element << " ";
		PreOrder(rt->lchild);
		PreOrder(rt->rchild);
	}
	void InOrder(Node rt)
	{
		if (rt == nullNode)	return;
		InOrder(rt->lchild);
		cout << rt->element << " ";
		InOrder(rt->rchild);
	}
	void PostOrder(Node rt)
	{
		if (rt == nullNode)	return;
		PostOrder(rt->lchild);
		PostOrder(rt->rchild);
		cout << rt->element << " ";
	}
	Node SendRoot()
	{
		return root;
	}
	void DrawPicture()
	{
		getHeight(root, 0);
		wideth = pow(2, height - 1);
		queue<Node>	q;
		q.push(root);
		int level = 1, outNum = 0;;
		while (level<=height)
		{
			Node temp = q.front();
			q.pop();
			outNum++;
			if (temp!=nullNode)
			{
				q.push(temp->lchild);
				q.push(temp->rchild);
			}
			else
			{
				q.push(nullNode);
				q.push(nullNode);
			}
			PrintBlank(level);
			PrintNode(temp);
			PrintBlank(level);
			cout << "   ";
			if (outNum==pow(2,level)-1)
			{
				level++;
				cout << endl;
			}
		}
	}
private:
	Node				root;
	Node				nullNode;
	int					height = 0;
	int					wideth;
private:
	void clear(Node x)
	{
		if (x == nullNode)	return;
		else
		{
			clear(x->lchild);
			clear(x->rchild);
			delete x;
		}
	}
	bool R(Node now)
	{
		if (now == nullNode || now->lchild == nullNode)
		{
			return false;
		}
		Node temp = now->lchild;
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
	bool L(Node now)
	{
		if (now == nullNode || now->rchild == nullNode)
		{
			return false;
		}
		Node temp = now->rchild;
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
	void InsertFixUp(Node now)
	{
		while (now->parent->colour == RED)
		{
			if (now->parent == now->parent->parent->lchild)
			{
				RBNode<Comparable> *uncle = now->parent->parent->rchild;
				if (uncle->colour == RED)
				{
					now->parent->colour = BLACK;
					uncle->colour = BLACK;
					uncle->parent->colour = RED;
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
					uncle->parent->colour = RED;
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
	void DeleteFixUp(Node node)
	{
		while (node->colour == BLACK&&node != root)
		{
			if (node == node->parent->lchild)
			{
				Node sibling = node->parent->rchild;
				if (sibling->colour == RED)
				{
					sibling->colour = BLACK;
					node->parent->colour = RED;
					L(node->parent);
					sibling = node->parent->rchild;
				}
				if (sibling->lchild->colour == BLACK&&sibling->rchild->colour == BLACK)
				{
					sibling->colour = RED;
					node = node->parent;
				}
				else
				{
					if (sibling->rchild->colour == BLACK)
					{
						sibling->lchild->colour = BLACK;
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
				Node sibling = node->parent->lchild;
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
						sibling->rchild->colour = BLACK;
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
	void getHeight(Node rt,int h)
	{
		if (rt == nullNode)
		{
			if (h  > height)
			{
				height = h ;
			}
			return;
		}
		getHeight(rt->lchild,h+1);
		getHeight(rt->rchild,h+1);
	}
	void PrintNode(Node rt)
	{
		if (rt == nullNode)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "nil";
		}
		else
		{
			if (rt->colour == RED)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			}
			cout << "(" << rt->element << ")";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	void PrintBlank(int level)
	{
		int w = height - level;
		int sum = 0;
		for (int i = 0; i < w; i++)
		{
			sum = sum * 2 + 1;
		}
		for (int i = 0; i < sum; i++)
		{
			cout << "   ";
		}
	}
};

#endif // DEBUG