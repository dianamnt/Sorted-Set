#include <iostream>
#include "Windows.h"
#include <stack>
#include <functional>
#include <cassert>

using namespace std;

struct node
{
	int info;
	node* left;
	node* right;
};

class Iterator;

class SortedSet
{

private:

	node* root;

	template <typename A, typename B, typename Relation = less<int>>

	bool relation(A a, B b, Relation relation = Relation())
	{
		return relation(a, b);
	}

	node* makeEmpty(node* n)
	{
		if (n == NULL)
			return NULL;
		makeEmpty(n->left);
		makeEmpty(n->right);
		delete n;

		return NULL;
	}

	node* add(int x, node* n)
	{
		if (n == NULL)
		{
			n = new node;
			n->info = x;
			n->left = NULL;
			n->right = NULL;
		}
		else if (relation(x, n->info)) n->left = add(x, n->left);
		else if (!relation(x,n->info))
			n->right = add(x, n->right);
		return n;
		
	}

	node* findMinNode(node* n)
	{
		if (n == NULL) return NULL;
		else if (n->left == NULL) return n; else return findMinNode(n->left);
	}

	node* remove(int x, node* n)
	{
		node* aux;
		if (n == NULL) return NULL;
		else if (relation(x,n->info))
			n->left = remove(x, n->left);
		else if (x > n->info)
			n->right = remove(x, n->right);
		else if (n->left && n->right)
		{
			aux = findMinNode(n->right);
			n->info = aux->info;
			n->right = remove(n->info, n->right);
		}
		else
		{
			aux = n;
			if (n->left == NULL)
				n = n->right;
			else if (n->right == NULL)
				n = n->left;
			delete aux;
		}
		return n;
	}

	bool find(int x, node* n)
	{
		if (n == NULL)
			return 0;
		else if (relation(x,n->info))
			return find(x, n->left);
		else if(x > n->info)
			return find(x, n->right); else
			return 1;
	}

	int size(node* n)
	{
		if (n == NULL)
			return 0; else
			return(size(n->left) + size(n->right) + 1);
	}

	node* getRoot()
	{
		return root;
	}
	
public:
	friend class Iterator;
	SortedSet()
	{
		root = NULL;
	}

	~SortedSet()
	{
		root = makeEmpty(root);
	}

	void add(int x)
	{	
		if (find(x, root) == 0)
		{
			root = add(x, root);
		}
	}

	void remove(int x)
	{
		root = remove(x, root);
	}


	bool find(int x)
	{
		return find(x, root);
	}

	int size()
	{
		return size(root);
	}

	Iterator iteratorul();
};

class Iterator
{
private:
	SortedSet&  set;
	stack<node*> s;
	node* currentNode;

public:
	friend class SortedSet;
	Iterator() = default;
	Iterator(SortedSet& ss): set(ss)
	{
		node* node = this->set.getRoot();
		while (node != NULL)
		{
			this->s.push(node);
			node = node->left;
		}
		if (!this->s.empty())
			this->currentNode = this->s.top();
		else this->currentNode = NULL;
	}


	bool valid()
	{
		if (this->currentNode == NULL) return 0; else
			return 1;
	}
	void next()
	{
		node* node = this->s.top();
		this->s.pop();
		if (node->right != NULL)
		{
			node = node->right;
			while (node != NULL)
			{
				this->s.push(node);
				node = node->left;
			}
		}

		if (!this->s.empty())
			this->currentNode = this->s.top();
		else this->currentNode = NULL;
	}
	int getCurent()
	{
		return this->currentNode->info;
	}

};

Iterator SortedSet::iteratorul()
{
	Iterator i{ *this };
	return i;
}

void printMenu()
{
	cout << "   ~~~ MENU ~~~   " << endl;
	cout << "1. Add a ticket number to the sorted set." << endl;
	cout << "2. Delete a ticket number from the sorted set." << endl;
	cout << "3. Display the sorted set in increasing order." << endl;
	cout << "4. Intersectie seturi." << endl;
	cout << "0. ...exit." << endl;
}

//void tests();


int main()
{	
	SortedSet s;
	s.add(20);
	s.add(20);
	s.add(25);
	s.add(15);
	s.add(10);
	s.add(30);
	s.add(8);

	SortedSet a;
	a.add(8);
	a.add(25);
	a.add(17);
	a.add(20);
	a.add(35);


	int cmd;

	while (true)
	{
		printMenu();
		cout << "Enter command: ";
		cin >> cmd;
		if (cmd == 1)
		{
			cout << "Enter ticket: ";
			int t;
			cin >> t;
			s.add(t);
		}
		else if (cmd == 2)
		{
			cout << "Enter ticket: ";
			int t;
			cin >> t;
			s.remove(t);
		}
		else if (cmd == 3)
		{
			cout << endl;
			Iterator i = s.iteratorul();
			while (i.valid())
			{
				cout << i.getCurent() << " ";
				i.next();
			}
			cout << endl;
			cout << endl;
		}
		else if (cmd == 4)
		{
			Iterator j = s.iteratorul();
			//Iterator j = a.iteratorul();
			while (j.valid())
			{
				if (a.find(j.getCurent()) == 1)
					cout << j.getCurent() << " ";
				j.next();
			}
			cout << endl;
		}
		else if (cmd == 0)
			break;
		else cout << "Invalid input!" << endl;
	}
	
	//tests();
	return 0;
}
/*
void tests()
{
	SortedSet s;
	s.add(1);
	assert(s.size() == 1);

	// Tests for the ADT SortedSet
	s.add(2);
	s.add(2);
	s.add(3);
	assert(s.size() == 3);

	s.remove(2);
	assert(s.size() == 2);
	s.remove(1);
	s.remove(3);
	//assert(s.getRoot() == NULL);

	s.add(8);
	s.add(3);
	s.add(10);
	s.add(1);
	s.add(6);
	s.add(14);
	s.add(4);
	s.add(7);
	s.add(13);

	s.remove(4);
	s.remove(6);
	s.remove(20);
	s.remove(7);
	s.remove(3);
	s.remove(8);

	assert(s.size() == 3);

	assert(s.find(1) == 1);

	s.remove(1);
	s.remove(10);

	//Tests for the Iterator
	Iterator i{ s };
	assert(i.getCurent() == 13);
	assert(i.valid() == 1);

	s.add(8);
	s.add(3);
	s.add(10);
	s.add(1);
	s.add(6);
	s.add(14);
	s.add(4);
	s.add(7);
	s.add(13);

	Iterator i2 = s.iteratorul();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 1);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 3);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 4);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 6);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 7);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 8);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 10);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 13);
	i2.next();
	assert(i2.valid() == 1);
	assert(i2.getCurent() == 14);

}
*/
