#include<iostream>
#include"RBTree.h"

using namespace std;

int main()
{
	system("color F0");
	RBTree<int> *t=new RBTree<int>;
	int ll[20] = { 15,53,92,4,62,8,73,11,59,60,16,99,34,75,46,33,15,99,87,50};
	for (int i = 0; i < 10; i++)
	{
		t->Insert(ll[i]);
	}
	t->DrawPicture();
	return 0;
}