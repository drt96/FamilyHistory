/***********************************************************************
 * ADT:
 *    Week 13, GENEALOGY
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Daniel Thomson
 * Summary:
 *    This is the implementation of a binary node used in this program
 *		to implement a Binary Tree
 ************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <iomanip> // for SETW

using namespace std;

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
  public:
   // Default Constructor
  BinaryNode(): data(T()), pLeft(NULL), pRight(NULL), pParent(NULL) { }
   
   // Non-Default Constructor
  BinaryNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL) { }
   
   // return size (i.e. number of nodes in tree)
   int size() const
   {
      return 1 +
         (pLeft== NULL? 0 : pLeft->size()) +
         (pRight == NULL ? 0 : pRight->size());
   }

   // Level order traversal
	void level();

   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);
   
   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;		// FATHER
   BinaryNode <T> * pRight;	// MOTHER
   BinaryNode <T> * pParent;	// unused
   T data;
};

/*****************************************************************
 * LEVEL
 * A function that will print out genealogical data in level order
 *****************************************************************/
template<class T>
void BinaryNode<T>::level()
{
	const int MAX = 100;
	BinaryNode<T> *queue[MAX];
	BinaryNode<T> *temp;

	int genNum = 0;
	int savedBack = 1;

	int front = 0;
	int back = 0;
	bool genPrint = true;

	queue[back++] = this;

	while (front != back)
	{
		// Figure out what generation we're on 
		if (front == savedBack)
		{
			savedBack = back;
			genNum++;
			genPrint = true;
		}

		temp = queue[front];
		front = (front + 1) % MAX;
		if (temp != NULL)
		{
			if (genPrint)
			{
				if (genNum == 1)
				{
					cout << "Parents:\n";
					genPrint = false;
				}
				if (genNum == 2)
				{
					cout << "Grandparents:\n";
					genPrint = false;
				}
				if (genNum == 3)
				{
					cout << "Great Grandparents:\n";
					genPrint = false;
				}
				if (genNum == 4)
				{
					cout << "2nd Great Grandparents:\n";
					genPrint = false;
				}
				if (genNum == 5)
				{
					cout << "3rd Great Grandparents:\n";
					genPrint = false;
				}
				if (genNum > 5)
				{
					cout << (genNum - 2) << "th Great Grandparents:\n";
					genPrint = false;
				}
			}
			
			if (genNum != 0)
			{
				cout << "        ";
			}
			// visit
			cout << temp->data;
			
			// end Visit        
			queue[back] = temp->pLeft;
			back = (back + 1) % MAX;
			queue[back] = temp->pRight;
			back = (back + 1) % MAX;
		}
	}
}

/*************************************************
 * Binary Node: Add Left (TYPE 1)
 *************************************************/
template<class T>
void BinaryNode<T>::addLeft(BinaryNode<T>* pNode)
{
   if (pNode != NULL)
   {
      pNode->pParent = this;
   }
   this->pLeft = pNode;
}

/*************************************************
 * Binary Node: Add Right (TYPE 1)
 *************************************************/
template<class T>
void BinaryNode<T>::addRight(BinaryNode<T>* pNode)
{
   if (pNode != NULL)
   {
      pNode->pParent = this;
   }
   this->pRight = pNode;
}

/*************************************************
 * Binary Node: Add Left (TYPE 2)
 *************************************************/
template<class T>
void BinaryNode<T>::addLeft(const T & t) throw (const char *)
{
   try
   {
      BinaryNode <T> * pAdd = new BinaryNode(t);
      pAdd->pParent = this;
      this->pLeft = pAdd;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************
 * Binary Node: Add Right (TYPE 2)
 *************************************************/
template<class T>
void BinaryNode<T>::addRight(const T & t) throw (const char *)
{
   try
   {
      BinaryNode <T> * pAdd = new BinaryNode(t);
      pAdd->pParent = this;
      this->pRight = pAdd;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************
 * Non-Member function: Delete Binary Tree
 * Takes a BinaryNode as a parameter and deletes
 * all the children and itself.
 *************************************************/
template<class T>
void deleteBinaryTree(BinaryNode <T> * subroot)
{
   // Recursive Anchor
   if (subroot == NULL)
   {
      return;
   }
   
   // POSTFIX Traverse (using LRV)
   deleteBinaryTree(subroot->pLeft);
   deleteBinaryTree(subroot->pRight);
   
   delete subroot;
   
   subroot = NULL;
}

/*************************************************
 * Non-Member function: Insertion Operator
 * Takes a constant BinaryNode * as a parameter
 * and displays the tree under the passed parameter. 
 *************************************************/
template<class T>
std::ostream & operator << (std::ostream & out, BinaryNode <T> & subroot)
{
   // Recursive Anchor
   if (subroot != NULL)
   {
      // INFIX Traverse (using LVR)
      out << (subroot->pLeft);
      out << (subroot->data) << " ";
      out << (subroot->pRight);
   }
   return out;	
}

#endif // BNODE_H