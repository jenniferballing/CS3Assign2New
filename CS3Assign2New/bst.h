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
	TreeNode<Etype> * findKthInOrder(TreeNode<Etype> * t, int k);
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
		TreeNode<Etype>* t = findKthInOrder(root, k);
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

//Accidently left written by Professor
//Big-oh expression: O(n)
template <class Etype>
TreeNode<Etype>*  BinarySearchTree<Etype>::leastCommonAncestor(TreeNode < Etype>* r, Etype a, Etype b)
{
	if (r == NULL){ return r; }
	assert(a < b);
	if (a <= r->element && b >= r->element) return r;
	if (b <= r->element) return leastCommonAncestor(r->left, a, b);
	return leastCommonAncestor(r->right, a, b);
}


//Big-oh expression: O(n^2)
template <class Etype>
bool BinarySearchTree<Etype>::isIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2)
{
	if (t1 == NULL && t2 == NULL) return true; 
	
	if (t1 == NULL ^ t2 == NULL) return false; //if the nodes are not the same

	//keep running until we find the null nodes
	bool is = isIsomorphic(t1->right, t2->right);
	bool iso = isIsomorphic(t1->left, t2->left);
}


//Big-oh expression: O(n^4)
template <class Etype>
bool BinarySearchTree<Etype>::isQuasiIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2 )
{
	//create trees so that count and width can be reused
	BinarySearchTree<Etype> *tree1 = new BinarySearchTree<Etype>();
	BinarySearchTree<Etype> *tree2 = new BinarySearchTree<Etype>();

	int t1NumNodes = tree1->count(t1);
	int t2NumNodes = tree2->count(t2);
	if (t1NumNodes != t2NumNodes) return false; //if the number of nodes is not the same- it is not quasi

	int tree1Height=0, tree2Height=0;
	int t1Width = tree1->width(t1, tree1Height);
	int t2Width = tree2->width(t2, tree2Height);
	if (t1Width != t2Width)return false; //if the width is not the same- it is not quasi

	if (tree1Height != tree2Height)return false; //if the height is not the same- it is not quasi

	return true;
}

//Big-oh expression: O(n)
template <class Etype>
int BinarySearchTree<Etype>::width(TreeNode<Etype> *t, int &height)
{
	if (t == NULL)
	{
		height = 0;
		return 0;
	}
	
	//temp variables
	int lHeight= height, rHeight= height;

	int lWidth = width(t->left, lHeight);
	int rWidth = width(t->right, rHeight);
	
	//set the height to the longest subtree
	if (lHeight > rHeight) height = lHeight;
	else height = rHeight;

	height++;

	//add the height of the two trees plus the root
	return lHeight + rHeight + 1;
}


//Big-oh expression: O(n)
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


//Big-oh expression: O(n)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::findKthInOrder(TreeNode<Etype>*t, int k)
{
	int count = 1;
	
	if (t == NULL)return NULL;

	while (t->left != NULL)t = t->left;// move to the left-most node
	
	if (count == k) return t;//if k=1
	
	while (count<k)
	{
		count++;
		if (t->parent == NULL) return NULL;
		
		t = t->parent;
		
		if (count == k) return t;
		
		if (t->right != NULL && t->parent != NULL) //check right child
		{
			count++;
			t = t->right;
			if (count == k) return t;
		}
		
		if (t->parent == NULL) return NULL;
		
		if (t->parent->parent != NULL) //check grandparent
		{
			count++;
			t = t->parent->parent;
			if (count == k) return t;
		}
	}return NULL;
}


//Big-oh expression: Olog(n)
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



//Big-oh expression: Olog(n)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::predecessor(TreeNode<Etype> * & t)
{
	if (t == NULL)return NULL;
	if (t->parent != NULL)
	{
		if (t->element > t->parent->element && t->left == NULL) return t->parent; // check parent value

		if (t->element > t->parent->element && t->left->element > t->parent->element) return t->left; //check left element

		if (t->parent->parent != NULL)//check grandparent
		{
			if (t->element < t->parent->element && t->parent->element> t->parent->parent->element) return t->parent->parent;
		}
		else return predecessor(t->left);
	}	
}

//Big-oh expression: O(n)
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
			left = "\n" + toString(t->left, indent + "  ");//create left string
		}
		else left = "";
		if (t->right != NULL)
		{
			right = "\n" + toString(t->right, indent + "  ");//create right string
		}
		else right = "";
		return right + indent + current + "(" + parent + ")" + left + indent + "\n"; //combine strings and print with indent
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


//Big-oh expression: O(n)
template <class Etype>
void BinarySearchTree<Etype>::makeEmpty(TreeNode<Etype> *&t)
{
	if (t == NULL)
	{
		return;
	}
	if (t->left != NULL) //go left and delete
	{
		TreeNode <Etype> *left = new TreeNode <Etype>();
		left = t->left;
		makeEmpty(left);
	}
	if (t->right != NULL) //go right and delete
	{
		TreeNode <Etype> *right = new TreeNode <Etype>();
		right = t->right;
		makeEmpty(right);
	}
	t = NULL; //set to null and delete
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


//Big-oh expression: O(n)
template <class Etype>
int BinarySearchTree<Etype>::countFringe(TreeNode<Etype> *t) const
{
	int count = 0;
	if (t == NULL)
	{
		return 0;
	}
	if (t->left == NULL && t->right == NULL)//check for leaf node
	{
		count = 1;
	}
	return count + countFringe(t->left) + countFringe(t->right);

}

