/***********************************************************************
* Program:
*    Week 13, Genealogy
*    Brother Ercanbrack, CS 235
*
* Author:
*   Daniel Thomson
* Summary:
*	This is an implementation of the merge sort using linked lists.
************************************************************************/

#include "list.h" // Homemade list class

using namespace std;

// Prototyping
template <class T>
List <T> split(List <T> & sList1);
template <class T>
List <T> merge(List <T> & sList1, List <T> & sList2);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template <class T>
void mergeSort(List<T> & toSort)
{
   // Split and merge over and over until done (list is sorted)
   toSort = split(toSort);
}

/*************************************************************************
* Read (iterate) through one list and "naturally" split it in two
* Recursive
**************************************************************************/
template <class T>
List <T> split(List<T> & sList)
{
   // Pointer to the current item
   ListIterator <T> current;
   current = sList.begin();
   
   // Pointer to the following item
	ListIterator <T> next;
   next = sList.begin();
   if (next != sList.end())
   {
      next++;
   }
   
   // Potential holders of sublists
	List <T> li1;
	List <T> li2;
   
   // To start things off put an item on the first list 
   li1.push_back(*current);
   
   while (next != sList.end() && *current < *next) 
   {
      // Populate the first list
      current++;
      next++;
      li1.push_back(*current);
   }
   // Recursive Anchor
   if (next == sList.end())
   {
      return li1;
   }
   // else Put the rest in list two
   while (next != sList.end())
   {
      li2.push_back(*next);
      ++next;
   }
   
   // Keep on giving it the longer sublist to naturally split
   sList = split(li2);
   // Merge the sublists as they return
   sList = merge(li1, li2);
   
   // You know that it's sorted when split doesn't populate the second or third list.
   return sList;
}

/*************************************************************************
* Read (iterate) through two sublists and merge them in order into one
**************************************************************************/
template <class T>
List <T> merge(List <T> & sList1, List <T> & sList2)
{
   // The list that things are going to be put into
	List <T> sorted;
   
   // Use two pointers (list iterators) to compare between each list
   ListIterator <T> it1;
   it1 = sList1.begin();
   ListIterator <T> it2;
   it2 = sList2.begin();
   
   // Go until both sublists are iterated through
   while (it1 != sList1.end() || it2 != sList2.end())
   {
      // If needed finish populating sorted with either list1 or list2
      // Case one:
      // populate with the rest of list two
      if (it1 == sList1.end())
      {
         while (it2 != sList2.end())
         {
            sorted.push_back(*it2);
            ++it2;
         }
      }
      // Case two:
      // populate with the rest of list one
      else if (it2 == sList2.end())
      {
         while (it1 != sList1.end())
         {
            sorted.push_back(*it1);
            ++it1;
         }
      }
      // Case three:
      // Normal sort comparison
      // With extra paranoid error handling
      else if (it1 != sList1.end() || it2 != sList2.end())
      {
         if (*it1 < *it2)
         {
            sorted.push_back(*it1);
            // Don't iterate if we don't have to to prevent NULL pointers
            if (it1 != sList1.end())
            {
               ++it1;
            }
         }
         else
         {
            sorted.push_back(*it2);
            // Don't iterate if we don't have to to prevent NULL pointers
            if (it2 != sList2.end())
            {
               ++it2;
            }
         }
      }
   }
   return sorted;
}
