#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*----------------------------------------------------------node
Holds:
  - any data type
  - node*
Note: this node is intended for a list
------------------------------------ */
template<class TYPE>
struct node{
  TYPE data;
  node<TYPE>* next;
};

/*----------------------------------------------------------List
List: holds information on the nodes in the list
holds:
  - head pointer (node<TYPE>*)
  - list size (int)
------------------------------------ */
template<class TYPE>
struct List{
  node<TYPE>* head;
  int size;
};

template<class TYPE>
void init_node(node<TYPE>* newNode);

template<class TYPE>
void init_list(List<TYPE>* list);

template<class TYPE>
void insert_node(List<TYPE>* list, TYPE data, int index);

template<class TYPE>
void print_list(List<TYPE>* list);

template<class TYPE>
TYPE get_data(List<TYPE>* list, int index);

template <class TYPE>
void deleteNode(List<TYPE>* list, int index);

#endif
