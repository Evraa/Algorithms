#include "BST.h"
#include <iostream>
#include <algorithm>
using namespace std;


//Generates a random number within the range [min:max)
int random(int min, int max) //range : [min, max)
{
	if (min == max)
		return min;
	if (min > max)
	{
		int temp = max;
		max = min;
		min = temp;
	}
	int range = max - min + 1;
	return rand() % range + min;
}

int main()
{
	BST ev;
	for (int i = 0; i < 100; i++)
		ev.insert(random(1,1000));

	ev.callInOrderTraversal();
	

	while (!ev.isempty())
	{
		int x = random(1, 1000);
		cout << x << " : is to be deleted" << endl;
		ev.deleteNode(x);

	}
	
	ev.callInOrderTraversal();
	

	return 0;
}