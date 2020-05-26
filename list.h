/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains a remodel of the STL List class
*
*    This will contain the class definition of:
*        List         : A class that holds Nodes
*        ListIterator : An interator through List Node
*                     : A single Node
* Author
*    Daniel Thomson
************************************************************************/

#ifndef List_H
#define List_H

#include <cassert>

// forward declaration for ListIterator
template <class T>
class ListIterator;

// forward declaration for Node
template <class T>
class Node;

/************************************************
 * List
 * A class that holds stuff
 ***********************************************/
template <class T>
class List
{
public:
   // default constructor : empty and kinda useless
  List() : numItems(0), pHead(NULL), pTail(NULL) {}
   
   // copy constructor : copy rhs
   List(const List & rhs) throw (const char *);
   
   // destructor : free everything
   ~List()
   {
      if (numItems > 0 || pHead != NULL || pTail != NULL)
      {
         clear();
      }
   }
   
   // is the List currently empty
   bool empty() const { return pHead == NULL; }
   
   // remove all the items from the List
   void clear();
   
   // how many items are currently in the List?
   int size() const { return numItems; }
   
   // Add an item to the back of the list
   void push_back(const T & t) throw (const char *);
   
   // Add an item to the front of the list
   void push_front(const T & t) throw (const char *);
   
   // Add an item anywhere in the List
   ListIterator <T> insert(ListIterator <T> & it, const T & t) throw (const char *);
   
   // The item at the front
   T & front() throw (const char *);
   
   // The item at the back
   T & back() throw (const char *);
   
   // Remove an element from the List.
   void remove(ListIterator <T> it) throw (const char *);
   
   // The assignment operator for the List class.
   List <T> & operator= (const List <T> & rhs) throw (const char *);
   
   // return an iterator to the beginning of the list
   ListIterator <T> begin() { return ListIterator<T>(pHead); }
   ListIterator <T> begin() const { return ListIterator<T>(pHead); }
   
   // return an iterator to the beginning of the list
   ListIterator <T> rbegin() { return ListIterator<T>(pTail); }
   ListIterator <T> rbegin() const { return ListIterator<T>(pTail); }
   
   // return an iterator to the end of the list
   ListIterator <T> end() { return ListIterator<T>(NULL); }
   ListIterator <T> end() const { return ListIterator<T>(NULL); }
   
   // return an iterator to the end of the list
   ListIterator <T> rend() { return ListIterator<T>(NULL); }
   ListIterator <T> rend() const { return ListIterator<T>(NULL); }
   
  private:
   Node <T> * pHead; // Pointer to the first Node
   Node <T> * pTail; // Pointer to the last Node
   int numItems;     // how many items are currently in the List?
};

/************************************************
* Node
* A class that holds data and pointers to next.
***********************************************/
template <class T>
class Node
{
  public:
   T data;           // Data of type T
   Node <T> * pNext; // Pointer to the next node
   Node <T> * pPrev; // Pointer to the previous node
   
   // default constructor : Creates empty node
  Node() : data(T()), pNext(NULL), pPrev(NULL) { }
   
   // non-default constructor : Assign data     
  Node(const T & t) : pNext(NULL), pPrev(NULL)
   {
      this->data = t;
   }
};

/**************************************************
 * List ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
  public:
   // default constructor
  ListIterator() : p(NULL) {}

   // initialize to direct p to some item
  ListIterator(Node <T> * pNode) : p(pNode) {  }
   
   // Copy constructor
   ListIterator(const ListIterator & rhs)
   {
      *this = rhs;
   }
   
   ~ListIterator()
   {		
      // No need to delete because we never allocate
      p = NULL;
   }
   
	// Equals operator
   bool operator == (const ListIterator & lhs) const
   {
      return this->p == lhs.p;
   }

   // Not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return this->p != rhs.p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return p->data;
   }
   
   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   
   // prefix decrement USED IN REVERSING
   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }
   
   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   
   // assignment operator
   ListIterator <T> & operator = (const ListIterator <T> & rhs)
      {
         // If there is some to assign point to it.
         if (rhs.p)
         {
            this->p = rhs.p;
         }
         
         return *this;
      }
   
   friend ListIterator <T> List <T> ::insert(ListIterator <T> & it, const T & t) throw (const char *);
   friend void List <T> ::remove(ListIterator <T> it) throw (const char *);

  private:
   Node <T> * p; // A pointer to an Node
};

/**********************************************
 * COPY CONSTRUCTOR
 * Copy each item over from an old list to a
 * new
 **********************************************/
template <class T>
List <T> ::List(const List <T> & rhs) throw (const char *)
{
   // do nothing if there is nothing to do
   if (rhs.numItems == 0)
   {
      numItems = 0;
      if (pHead != NULL && pTail != NULL)
      {
         // To prevent memory leaks
         clear();
      }
      this->pHead = NULL;
      this->pTail = NULL;
      return;
   }
   else
   {
      /*Copy the items over one node at a time*/
      numItems = rhs.numItems;
      
      // Temporary pointer to use during iterating
      Node <T> * temp;
      try
      {
         temp = new Node <T>(rhs.pHead->data);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new node for a list";
      }
      // Point the new head and tail to the temporary pointer to the old head
      this->pHead = temp;
      this->pTail = temp;
      
      // Create a pointer to the old Node's pNext after it's head
      Node <T> * pSrc = rhs.pHead->pNext;
      
      // Create a pointer to the new Head and temp
      Node <T> * pDes = pHead;
      
      // copy all the values over
      // Starting for the rhs's first pNext to avoid a recopy
      // ending at the NULL pointer
      // and moving the pointers of both the lhs and rhs
      
      for (pSrc->pNext; pSrc; pSrc = pSrc->pNext, pDes = pDes->pNext)
      {
         // Make a new node that has the desired data.
         Node <T> * pInsert;
         try
         {
            pInsert = new Node <T>(pSrc->data);
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: unable to allocate a new node for a list";
         }
         
         pDes->pNext = pInsert;
         pInsert->pPrev = pDes;
         this->pTail = pInsert;
      }
   }
}

/***************************************************
 * List :: Clear
 * Remove all elements from list
 **************************************************/
template <class T>
void List <T> ::clear()
{
   // Start at the head and carefully delete as we go.
   while (pHead != NULL)
   {
      Node <T> * pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
   // Reset the variables.
   numItems = 0;
   pHead = NULL;
   pTail = NULL;
}

/***************************************************
 * List :: Push Back
 * Adds an item to the end of the list
 **************************************************/
template<class T>
void List<T>::push_back(const T & t) throw(const char *)
{
   // Let insert use it's handle for insertion at end
   ListIterator <T> it = NULL;
   this->insert(it, t);
}

/***************************************************
 * List :: Push Front
 * Adds an item to the beginning of the list
 **************************************************/
template<class T>
void List<T>::push_front(const T & t) throw(const char *)
{
   // Let insert use it's handle for insertion at begin
   ListIterator <T> it = begin();
   this->insert(it, t);
}

/**********************************************
 * LIST INSERT
 * Insert a new Node anywhere into the list.
 **********************************************/
template <class T>
ListIterator <T> List <T> ::insert(ListIterator <T> & it, const T & t) throw (const char *)
{
   // Temporary node for insertion
   Node<T> * tmp;
   try
   {
      tmp = new Node<T>(t);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   
   if (this->pHead == NULL)	// insert into an empty list
   {
      this->pHead = tmp;
      this->pTail = tmp;
      it = begin();				// Change where it is now pointing to
   }
   // No need change where it is now pointing to because it's already there
   else if (it == end())		// insert at end of list
   {
      pTail->pNext = tmp;
      tmp->pPrev = pTail;
      pTail = tmp;
   }
   else
   {
      tmp->pNext = it.p;		// insert at beginning or middle
      tmp->pPrev = it.p->pPrev;
      it.p->pPrev = tmp;
      if (it.p == pHead)
         pHead = tmp;			// insert at beginning 
      else
         tmp->pPrev->pNext = tmp;    // insert in middle
      
   }
   numItems++;
   
   return it;
}

/***************************************************
 * List :: Front
 * Return the value at the front
 **************************************************/
template<class T>
T & List<T>::front() throw(const char *)
{
   // If there's data go ahead and return the data at the first node
   if (!empty())
   {
      return pHead->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/***************************************************
 * List :: Back
 * Return the value at the Back
 **************************************************/
template<class T>
T & List<T>::back() throw (const char *)
{
   // If there's data go ahead and return the data at the last node
   if (!empty())
   {
      return pTail->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/***************************************************
 * List :: Remove
 * Remove an element from the List.
 **************************************************/
template<class T>
void List <T>::remove(ListIterator <T> it) throw (const char *)
{
   // Check if it.p->pNext == NULL in which case it is the tail.  
   if (it == rbegin())
   {
      // So reassign tail
      it.p->pPrev->pNext = NULL;
      pTail = it.p->pPrev;
   }
   // Check if it.p->pPrev == NULL in which case it is the head.
   else if (it == begin())
   {
      // So reassign head
      it.p->pNext->pPrev = NULL;
      pHead = it.p->pNext;
      
   } else if (it != end())
      // Removing from the Middle
   {
      if (it.p->pPrev != NULL)
      {
         it.p->pPrev->pNext = it.p->pNext;
      }
      
      if (it.p->pNext != NULL)
      {
         it.p->pNext->pPrev = it.p->pPrev;
      }
      // check if it.p->pPrev and it.p->pNext == NULL in which case it is the last item. SO reassign handle this
   }
   else
   {
      throw "ERROR: unable to remove from an invalid location in a list";
   }
   
   delete it.p;
}

/***************************************************
 * List :: Assignment operator
 * An assignment operator overload that allows one
 * List to be copied into the other.
 **************************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) throw (const char *)
{
   // If they are already identical just move on
   if (this == &rhs)
   {
      return *this;
   }
   
   // do nothing if there is nothing to do
   if (rhs.numItems == 0)
   {
      numItems = 0;
      if (pHead != NULL || pTail != NULL)
      {
         // To prevent memory leaks
         clear();
      }
      this->pHead = NULL;
      this->pTail = NULL;
   }
   else
      // In this case we need to copy
   {
      if (pHead != NULL || pTail != NULL)
      {
         // To prevent memory leaks
         clear();
      }
      
      this->numItems = rhs.numItems;
      
      Node <T> * temp = new Node <T>(rhs.pHead->data);
      
      this->pHead = temp;
      this->pTail = temp;
      
      // Create a pointer to the old Node's pNext after it's head 
      Node <T> * pSrc = rhs.pHead->pNext;
      
      // Create a pointer to the new Head of pDestination
      Node <T> * pDes = this->pHead;
      
      // copy all the values over
      // Starting for the rhs's first pNext to avoid a recopy
      // ending at the NULL pointer
      // and moving the pointers of both the lhs and rhs
      for (pSrc->pNext; pSrc; pSrc = pSrc->pNext, pDes = pDes->pNext)
      {
         // Make a new node that has the desired data.
         Node <T> * pInsert;
         try
         {
            pInsert = new Node <T>(pSrc->data);
         }
         catch (std::bad_alloc)
         {
            throw "Error: Cannot allocate memory for the Node"; // DOUBLE CHECK THIS
         }
         
         pDes->pNext = pInsert;
         pInsert->pPrev = pDes;
         this->pTail = pInsert;
      }
   }
   return *this;
}

#endif // List_H
