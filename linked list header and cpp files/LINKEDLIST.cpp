#include "LINKEDLIST.h"
#include <iostream>

template<class TYPE>
void init_node(node<TYPE>* newNode){
  newNode->next=NULL;
  newNode->data=0;
}


/*----------------------------------------------------------init_list()
initiaize list: set default values
input: List*
output: void
------------------------------------- */
template<class TYPE>
void init_list(List<TYPE>* list){
 list->head=NULL;
 list->size=0;
}
/*----------------------------------------------------------insert_node()
Insert node
input: list | target index | datatype | data to be inserted
------------------------------------- */
template<class TYPE>
void insert_node(List<TYPE>* list, TYPE data, int index){
 if (index >= 0 && index <= list->size){
   node<TYPE>* newNode = new node<TYPE>;
   init_node(newNode);
   newNode->data = data;

   // insert end middle beginning, is list empty?
   if(index==0){
     newNode->next=list->head;
     list->head=newNode;
   }
   else{
     // insert in the middle / end
     node<TYPE>* previous= NULL;
     node<TYPE>* current= list->head;

     //traverse: current is at i, previous is at i-1
     for(int i=0; i < index; i++){
       previous = current;
       current = current->next;
     }
     newNode->next= current;
     previous->next= newNode;
   }
   //increase list size by +1
   list->size++;
 }
 else{
   cout << index << "is out of bounds. enter between 0-" << list->size ;
 }

}

/*----------------------------------------------------------print_list()
Priunt entire list:
input: List
output: void
------------------------------------- */
template<class TYPE>
void print_list(List<TYPE>* list){
 node<TYPE>* current= list->head;
 while(current!=NULL){
   cout << current->data << "\t";
   current=current->next;
 }
 cout << "\n";
}

/*----------------------------------------------------------get_data()
Get data: cout's data at node corresponding to target index
input:
------------------------------------- */
template<class TYPE>
TYPE get_data(List<TYPE>* list, int index){
 if(index >= 0 && index < list->size){
   node<TYPE>* current= list->head;
   //traverse: current is at i, previous is at i-1
   for(int i=0; i < index; i++){
     current = current->next;
   }
   return current->data;
 }
 else{
   cout << "index is out of bounds, please enter between 0-" <<
     list->size -1 << endl;
 }
}

/*----------------------------------------------------------

------------------------------------- */

/*----------------------------------------------------------deleteNode()
Delete node
Input: List<TYPE>*, index to Delete
Output: void
------------------------------------- */
template <class TYPE>
void deleteNode(List<TYPE>* list, int index){
 if (index >= 0 && index < list->size){
   if (index==0){
     node<TYPE>* temp = list->head;
     list->head = list->head->next;
     delete temp;
   }
   else{
     node<TYPE>* previous= NULL;
     node<TYPE>* current= list->head;

     //traverse: current is at i, previous is at i-1
     for(int i=0; i < index; i++){
       previous = current;
       current = current->next;
     }
     previous->next= current->next;
     delete current;
   }
   //decrease list size by -1
   list->size-=1;
 }
 else{
   cout << index << "is out of bounds. enter between 0-" << list->size-1;
 }
}
