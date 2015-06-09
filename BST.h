#ifndef bTree_H
#define bTree_H
#include <iostream>
using namespace std;

//Binary Tree Template.
template <class T>
class bTree
{
private:
	struct treeNode
	{
		T value;
		int num;
		treeNode *leftSubTree;
		treeNode *rightSubTree;
		
	};

	//Private member functions.
	void insert(treeNode *&, treeNode *&);
	void destroyTree(treeNode *);
	void deleteNode(T, treeNode *&);
	void makeDeletion(treeNode *&);
	void displayInorder(treeNode *) const;
	void displayInorderIndented(treeNode *) const;
	int getLevelUtil(treeNode *nodePtr, T value, int level) const;
	void displayPreorder(treeNode *) const;
	void displayPostorder(treeNode *) const;
	void inorderTraverse(treeNode *root) const;
	void buildTree(treeNode &tree, int n);
	bTree *_search(int target);

public:
	//Constructor.
	bTree()
	{
		root = nullptr;
	}
	//Deconstructor.
	~bTree()
	{
		destroyTree(root);
	}

	treeNode *root;
	void insertNode(T);
	bool searchNode(T);
	void remove(T);
	//NEWLLY ADDED
	//spacing
	void enqueue(T);
	void dequeue(T &);
	bool isEmpty() const;
	bool isFull() const;
	void clear();

	bTree(int);
	bTree(const bTree &);
	//NEWLY ADDED
	//SPACING
	T *queueArray;
	int queueSize;
	int front;
	int rear;
	int numItems;
	bool search(T value);




	void displayInorder() const
	{
		displayInorder(root);
	}
	void displayInorderIndented() const
	{
		displayInorderIndented(root);
	}
	void displayPreorder() const
	{
		displayPreorder(root);
	}
	void displayPostorder() const
	{
		displayPostorder(root);
	}
};

template <class T>
bTree<T>::bTree(int s)
{
	queueArray = new T[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}
template <class T>
bTree<T>::bTree(const bTree &obj)
{
	queueArray = new T[obj.queueSize];
	queueSize = obj.queueSize;
	front = obj.front;
	rear = obj.rear;
	numItems = obj.numItems;

	for (int count = 0; count < obj.queueSize; count++)
		queueArray[count] = obj.queueArray[count];
}

template <class T>
void bTree<T>::enqueue(T num)
{
	if (isFull())
		cout << "The queue is full.\n";
	else
	{
		rear = (rear + 1) % queueSize;
		queueArray[rear] = num;
		numItems++;
	}
}
template <class T>
void bTree<T>::dequeue(T &num)
{
	if (isEmpty())
		cout << "The queue is empty.\n";
	else
	{
		front = (front + 1) % queueSize;
		num = queueArray[front];
		numItems--;
	}
}
template <class T>
bool bTree<T>::isEmpty() const
{
	bool status;
	if (numItems)
		status = false;
	else
		status = true;
	return status;
}
template <class T>
bool bTree<T>::isFull() const
{
	bool status;
	if (numItems < queueSize)
		status = false;
	else
		status = true;
	return status;
}
template <class T>
void bTree<T>::clear()
{
	front = queueSize - 1;
	rear = queueSize - 1;
	numItems = 0;
}


	template <class T>
	void bTree<T>::insert(treeNode *&nodePtr, treeNode *&newNode)
	{
		if (nodePtr == nullptr)
			nodePtr = newNode;
		else if (newNode->value < nodePtr->value)
			insert(nodePtr->leftSubTree, newNode);
		else
			insert(nodePtr->rightSubTree, newNode);
	}
	template <class T>
	void bTree<T>::insertNode(T item)
	{
		treeNode *newNode = nullptr;

		newNode = new treeNode;
		newNode->value = item;
		newNode->leftSubTree = newNode->rightSubTree = nullptr;

		insert(root, newNode);
	}

	template <class T>
	void bTree<T>::destroyTree(treeNode *nodePtr)
	{
		if (nodePtr)
		{
			if (nodePtr->leftSubTree)
				destroyTree(nodePtr->leftSubTree);
			if (nodePtr->rightSubTree)
				destroyTree(nodePtr->rightSubTree);
			delete nodePtr;
		}
	}


	template <class T>
	bool bTree<T>::searchNode(T item) 
	{
		treeNode *nodePtr = root;
		while (nodePtr)
		{
			if (nodePtr->value == item)
				return true;
			else if (item < nodePtr->value)
				nodePtr = nodePtr->leftSubTree;
			else
				nodePtr = nodePtr->rightSubTree;
		}
		return false;
	}
	template <class T>
	void bTree<T>::remove(T item)
	{
		deleteNode(item, root);
	}
	template <class T>
	void bTree<T>::deleteNode(T item, treeNode *&nodePtr)
	{
		if (item < nodePtr->value)
			deleteNode(item, nodePtr->leftSubTree);
		else if (item > nodePtr->value)
			deleteNode(item, nodePtr->rightSubTree);
		else
			makeDeletion(nodePtr);
	}
	template <class T>
	void bTree<T>::makeDeletion(treeNode *&nodePtr)
	{
		treeNode *tempNodePtr = nullptr;

		if (nodePtr == nullptr)
			cout << "Cannot delete an empty node\n";
		else if (nodePtr->rightSubTree == nullptr)
		{
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->leftSubTree;
			delete tempNodePtr;
		}
		else if (nodePtr->leftSubTree == nullptr)
		{
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->rightSubTree;
			delete tempNodePtr;
		}
		else
		{
			tempNodePtr = nodePtr->rightSubTree;
			while (tempNodePtr->leftSubTree)
				tempNodePtr = tempNodePtr->leftSubTree;
			tempNodePtr->leftSubTree = nodePtr->leftSubTree;
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->rightSubTree;
			delete tempNodePtr;
		}
	}
	template <class T>
	void bTree<T>::displayInorder(treeNode *nodePtr) const
	{
		if (nodePtr)
		{
			int level = getLevelUtil(root, nodePtr->value, 1);
			displayInorder(nodePtr->leftSubTree);
			for (int i = 1; i < level; ++i)
			displayInorder(nodePtr->rightSubTree);
			cout << level << " . " << nodePtr->value << endl;
		}
	}
	template <class T>
	void bTree<T>::displayInorderIndented(treeNode *nodePtr) const
	{
		if (nodePtr)
		{
			int level = getLevelUtil(root, nodePtr->value, 1);
			displayInorderIndented(nodePtr->leftSubTree); 
			for (int i = 1; i < level; ++i)
			{
				cout << "\t";
			}
			cout << level << ". " << nodePtr->value << endl;
			displayInorderIndented(nodePtr->rightSubTree);
		}
	}
	template <class T>
	int bTree<T>::getLevelUtil(treeNode *nodePtr, T value, int level) const
	{
		if (nodePtr == nullptr)
			return 0;

		if (nodePtr->value == value)
			return level;

		int downlevel = getLevelUtil(nodePtr->leftSubTree, value, level + 1);
		if (downlevel != 0)
			return downlevel;

		downlevel = getLevelUtil(nodePtr->rightSubTree, value, level + 1);
		return downlevel;
	}
	template <class T>
	void bTree<T>::displayPreorder(treeNode *nodePtr) const
	{
		if (nodePtr)
		{
			cout << nodePtr->value << endl;
			displayPreorder(nodePtr->leftSubTree);
			displayPreorder(nodePtr->rightSubTree);
		}
	}
	template <class T>
	void bTree<T>::displayPostorder(treeNode *nodePtr) const
	{
		if (nodePtr)
		{

			displayPostorder(nodePtr->leftSubTree);
			displayPostorder(nodePtr->rightSubTree);
			cout << nodePtr->value << endl;
		}
	}
#endif

	

	
	
	
	
