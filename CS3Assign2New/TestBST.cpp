#include "bst.h"
#include <ctime>
using namespace std;

int main()
{
	int val = 460;
	const int SIZE = 8;
	BinarySearchTree<int> tree0, tree1, tree2, tree3, tree4, tree5, tree6;
	//vector<int> v0{ 25, 10, 60, 55, 45, 30, 14, 10, 75, 80, 20, 10, 5, 3, 61, 62, 63 };
	vector <int> v0{ 25, 10, 60, 55, 45, 30, 14, 75, 80, 5, 20 };
	vector<int> test{ 1, 10, 15, 2, 8, 6, 7, 16, 10, 75, 80, 20 };
	vector<int> v1{ 25, 10, 60, 55, 58, 56, 14, 10, 75, 80, 20, 10, 5, 7, 61, 62, 63 };
	vector<int> v2, v3, v4, v5, v6;
	srand((int)time(0));
	for (int i = 0; i < SIZE; i++){
		int t = rand() % 100;
		v2.push_back(t);
		v3.push_back(t + rand() % 5);
		v4.push_back(t + 18);
		v5.push_back(100 - t);
	}
	for (int i = 0; i < SIZE*SIZE*SIZE; i++){
		int t = rand() % 2000;
		v6.push_back(t);
	}
	v6.push_back(val);
	tree0.makeTree(v0);
	tree1.makeTree(test);
	//tree1.makeTree(v1);
	cout << tree0.toString("Tree 0") << endl << endl;
	//cout << tree1.toString("Tree 1") << endl;

	//cout << "Should be 5: " << tree0.countFringe() << endl;
	//cout << "Should be 3: " << tree1.countFringe() << endl;

	//cout << "Should be 25: "<< tree0.predecessor(10)<< endl;
	//cout << "Should be null: " << tree0.predecessor(25) << endl;

	//cout << "Should be 1: " << tree0.nodesInLevel(0) <<endl;
	//cout << "Should be 2: " << tree0.nodesInLevel(1) << endl;
	//cout << "Should be 4: " << tree0.nodesInLevel(2) << endl;
	//cout << "Should be 3: " << tree0.nodesInLevel(3) << endl;

	cout << "Should be 5: " << tree0.findKthInOrder(1) << endl;
	cout << "Should be 10: " << tree0.findKthInOrder(2) << endl;
	cout << "Should be 14: " << tree0.findKthInOrder(3) << endl;
	cout << "Should be NULL: " << tree0.findKthInOrder(25) << endl;



	//cout << tree1.traverse("Tree 1");
	/*cout << "Fringe count tree1:" << tree1.countFringe() << endl;
	cout << "Minimum element of tree 1 is " << tree1.minimumEle()->element << endl;
	cout << "Maximum element of tree 1 is " << tree1.maximumEle()->element << endl;
	cout << tree1.traverse("Traversal of tree 1");
	int myLevel = 3;
	cout << "Number nodes at level " << myLevel << " is " << tree1.nodesInLevel(myLevel) << endl;
	myLevel = 5;
	cout << "Number nodes at level " << myLevel << " is " << tree1.nodesInLevel(myLevel) << endl;
	cout << "Count of tree nodes " << tree1.count() << endl;
	int k = 1;
	cout << "The" << k << "th smallest value is  " << tree1.findKthInOrder(k) << endl;
	k = 7;
	cout << "The" << k << "th smallest value is  " << tree1.findKthInOrder(k) << endl;
	k = 12;

	cout << "The" << k << "th smallest value is  " << tree1.findKthInOrder(k) << endl;


	cout << "The width of  tree1 is " << tree1.width() << endl;
	tree2.makeTree(v2);
	cout << "The width of  tree2 is " << tree2.width() << endl;
	if (tree1.leastCommonAncestor(7, 15) == NULL)
	cout << "No Least Common Ancestor\n";
	else
	cout << "Least Common Ancestor " << tree1.leastCommonAncestor(7, 15)->element << endl;

	tree3.makeTree(v3);
	tree4.makeTree(v4);
	tree5.makeTree(v5);
	tree6.makeTree(v6);
	cout << tree6.traverse("tree6");
	cout << "starting at " << val << endl;
	for (int i = 0; i < 5; i++)
	{
	val = tree6.predecessor(val);
	cout << "The next predecessor is " << val << endl;
	}

	cout << tree2.toString("tree2");
	cout << tree3.toString("tree3");
	cout << tree4.toString("tree4");
	cout << tree5.toString("tree5");
	if (tree2.isIsomorphic(tree3)) cout << "Trees 2 and 3 are Isomorphic" << endl;
	if (tree2.isIsomorphic(tree4)) cout << "Trees 2 and 4 are Isomorphic" << endl;
	if (tree3.isIsomorphic(tree4)) cout << "Trees 3 and 4 are Isomorphic" << endl;
	if (tree0.isIsomorphic(tree1)) cout << "Trees 0 and 1 Are Isomorphic" << endl;
	if (tree2.isQuasiIsomorphic(tree3)) cout << "Trees 2 and 3 Are Quasi-Isomorphic" << endl;
	if (tree2.isQuasiIsomorphic(tree5)) cout << "Trees 2 and 5 Are Quasi-Isomorphic" << endl;
	if (tree0.isQuasiIsomorphic(tree1)) cout << "Trees 0 and 1 Are Quasi-Isomorphic" << endl;
	if (tree0.isQuasiIsomorphic(tree5)) cout << "Trees 0 and 5 Are Quasi-Isomorphic" << endl;
	tree1.makeEmpty();
	cout << tree1.toString("Is this tree empty?") << endl;
	*/
	return 0;
}