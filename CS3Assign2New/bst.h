#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>
using namespace std;

template <class Etype>
class TreeNode
{
public:
	Etype element;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) { }
};

template <class Etype>
class BinarySearchTree
{
protected:
	TreeNode<Etype> *root;
	bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);
	string toString(TreeNode<Etype> * t, string indent) const;
	string traverse(TreeNode<Etype> * t) const;
	TreeNode<Etype> * minimumEle(TreeNode<Etype> * & t);
	TreeNode<Etype> * maximumEle(TreeNode<Etype> * & t);
	TreeNode<Etype> * predecessor(TreeNode<Etype> * & t);
	int nodesInLevel(TreeNode<Etype> * & t, int level, int count);
	TreeNode<Etype> * findKthInOrder(TreeNode<Etype> * t, int k, int count);
	int count(TreeNode<Etype> *t);
	int width(TreeNode<Etype> * t, int &height);
	bool isIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);
	bool isQuasiIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);
	TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value);
	void makeEmpty(TreeNode<Etype> *&t);
	int countFringe(TreeNode<Etype> *t) const;
	TreeNode<Etype>* leastCommonAncestor(TreeNode <Etype>* r, Etype a, Etype b);
public:
	TreeNode<Etype>* leastCommonAncestor(Etype a, Etype b) {  // order the elements so we know which is smaller
		if (a < b) return leastCommonAncestor(root, a, b);
		return leastCommonAncestor(root, b, a);
	}
	void makeTree(vector<Etype> all);
	Etype predecessor(Etype value)
	{
		TreeNode<Etype> *curr = find(root, value);
		TreeNode<Etype> * p = predecessor(curr);
		if (p != NULL) return p->element;
		else return 0;
	}
	BinarySearchTree() : root(NULL) { }
	TreeNode<Etype> * minimumEle(){
		return minimumEle(root);
	}
	TreeNode<Etype> * maximumEle(){
		return maximumEle(root);
	}
	TreeNode<Etype> * successor(){
		return minimumEle();
	}
	string toString(string msg = "") const
	{
		return msg + "\n" + toString(root, "  ");
	}
	virtual int insert(Etype & x) { return insert(x, root, NULL); }
	string traverse(string msg) const
	{
		return msg + "\n" + traverse(root);
	}
	int nodesInLevel(int level) { 
		int count=0;
		return nodesInLevel(root, level, count); 
	}
	int findKthInOrder(int k) {
		int count=0;
		TreeNode<Etype>* t = findKthInOrder(root, k, count);
		if (t == NULL) return -999;
		return t->element;
	}
	int count() { return count(root); }
	int width() { int height; return width(root, height); }
	bool isIsomorphic(BinarySearchTree<Etype> t) { return isIsomorphic(root, t.root); }
	bool isQuasiIsomorphic(BinarySearchTree<Etype> t) { return isQuasiIsomorphic(root, t.root); }
	TreeNode<Etype> * clone(TreeNode<Etype> *t, TreeNode<Etype> *p) const;
	void makeEmpty() { makeEmpty(root); }
	int countFringe() { return countFringe(root); }

};

template <class Etype>
TreeNode<Etype>*  BinarySearchTree<Etype>::leastCommonAncestor(TreeNode < Etype>* r, Etype a, Etype b)
{
	if (r == NULL){ return r; }
	assert(a < b);
	if (a <= r->element && b >= r->element) return r;
	if (b <= r->element) return leastCommonAncestor(r->left, a, b);
	return leastCommonAncestor(r->right, a, b);
}

template <class Etype>
bool BinarySearchTree<Etype>::isIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2)
{
	return false;
}

template <class Etype>
bool BinarySearchTree<Etype>::isQuasiIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2)
{

	return false;
}
template <class Etype>
int BinarySearchTree<Etype>::width(TreeNode<Etype> *t, int &height)
{
	return -1;
}
template <class Etype>
int BinarySearchTree<Etype>::count(TreeNode<Etype>*t)
{
	if (t == NULL)
	{
		return 0;
	}
	return 1 + count(t->left) + count(t->right);
}

// Using the iterator would be better, as this repeatedly searches the left subtree.

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::findKthInOrder(TreeNode<Etype>*t, int k, int count)
{
	if (t == NULL)return NULL;

	if (count == k) return t;

	count++;

	

	return findKthInOrder(t->left, k, count);
	return findKthInOrder(t->right, k, count);
}

template <class Etype>
int BinarySearchTree<Etype>::nodesInLevel(TreeNode<Etype>*&t, int level, int count)
{
	if (t == NULL) return 0;
	if (count == level)
	{
		return 1;
	}
	count++;
	return nodesInLevel(t->left, level, count) + nodesInLevel(t->right, level, count);
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::minimumEle(TreeNode<Etype> * & t)
{
	if (t->left != NULL)
		return minimumEle(t->left);
	return t;

}

template <class Etype>
string BinarySearchTree<Etype>::traverse(TreeNode<Etype> *t) const
{
	stringstream ss;
	if (t == NULL) return "";
	ss << traverse(t->left);
	ss << t->element << " ";
	ss << traverse(t->right);
	return ss.str();
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::maximumEle(TreeNode<Etype> * & t)
{
	if (t->right != NULL) return maximumEle(t->right);
	return t;
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::predecessor(TreeNode<Etype> * & t)
{
	if (t == NULL)
	{
		return NULL;
	}
	if (t->parent != NULL)
	{
		return t->parent;
	}
	else
	{
		return NULL;
	}
}

template <class Etype>
string BinarySearchTree<Etype>::toString(TreeNode<Etype> *t, string indent) const
{
	string left, right;
	if (t == NULL)
	{
		return "";
	}
	else
	{
		string current, parent;

		stringstream sp, sl;
		sp << t->element;
		sp >> current;
		if (t->parent == NULL)
		{
			parent = "no parent";
		}
		else
		{
			sl << t->parent->element;
			sl >> parent;
		}

		if (t->left != NULL)
		{
			left = "\n" + toString(t->left, indent + "  ");
			/*sl << t->left->element;
			sl >> left;
			element += "(" + parent + ")" + left + indent;
			element += toString(t->left, indent);*/
		}
		else left = "";
		if (t->right != NULL)
		{
			right = "\n" + toString(t->right, indent + "  ");
			/*sr << t->right->element;
			sr >> right;
			element += "(" + parent + ")" + right + indent;
			element += toString(t->right, indent);*/
		}
		else right = "";
		return right + indent + current + "(" + parent + ")" + left + indent + "\n";
	}
}

// Return true if insertion is successful
template <class Etype>
bool BinarySearchTree<Etype>::insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype> *  p)
{
	if (t == NULL)
	{  // cout << "inserting " << x << endl;
		t = new TreeNode<Etype>(x, NULL, NULL, p);
		if (t == NULL) return false;
		return true;
	}
	if (x < t->element) return insert(x, t->left, t);
	if (x > t->element) return insert(x, t->right, t);
	// cout << "Warning, duplicate ignored " << x << endl;

	return false;  // does not allow duplicate insertions
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::find(TreeNode<Etype> * curr, Etype value)
{
	if (curr == NULL) return NULL;
	if (curr->element == value)
		return curr;
	if (value < curr->element) return find(curr->left, value);
	return find(curr->right, value);
}

template <class Etype>
void BinarySearchTree<Etype>::makeTree(vector<Etype> all)
{
	makeEmpty(root);
	for (unsigned i = 0; i < all.size(); i++)
		insert(all[i]);
}

template <class Etype>
void BinarySearchTree<Etype>::makeEmpty(TreeNode<Etype> *&t)
{
	if (t == NULL)
	{
		return;
	}
	if (t->left != NULL)
	{
		TreeNode <Etype> *left = new TreeNode <Etype>();
		left = t->left;
		makeEmpty(left);
	}
	if (t->right != NULL)
	{
		TreeNode <Etype> *right = new TreeNode <Etype>();
		right = t->right;
		makeEmpty(right);
	}
	t = NULL;
	delete t;
}


template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::clone(TreeNode<Etype> *t, TreeNode<Etype> *parent) const
{
	if (t == NULL)
		return NULL;
	TreeNode<Eype>* newNode = new TreeNode < Etype >{ t->element, NULL, NULL, parent };
	newNode->left = clone(t->left, newNode);
	newNode->right = clone(t->right, newNode);
	return newNode;
}

template <class Etype>
int BinarySearchTree<Etype>::countFringe(TreeNode<Etype> *t) const
{
	int count = 0;
	if (t == NULL)
	{
		return 0;
	}
	if (t->left == NULL && t->right == NULL)
	{
		count = 1;
	}
	return count + countFringe(t->left) + countFringe(t->right);

}

