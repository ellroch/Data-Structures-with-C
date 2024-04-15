/*
// how to read the output:

note: some random longs scattered around... not really necessary, they are left
      over from the dumpster file...

// something of a disclaimer?:
// I feel like my recent output organization is derived from jared's
// (he helped me try to fix the old file) and I want to openly acknowledge that
// and give him what credit he is due... I can't remember exactly what his looked
// like but in retrospection I am confident it was a major influence in my output.
// organization.

I apologize for the late submission, especially considering
how this is just the base assignment without any improvements...

I rewrote the file from scratch for a couple reasons...
1.  I decided to just stop messing with the frankenstein hash because
    It was taking too long to debug, and being hastily put together it
    was with poor organization

2.  after giving up the frankenstein hash almost all of hashing and
    collision resolution functions accounted for a variety of
    exceptions that would only occur as a result of calculations in
    the frankenstein hash

3.  the main function's distribution of tasks was rather poor,
    readability would be significantly easier if I just redid it,

4.  using the abandoned file as a dumpster to pick through would
    be faster than fixing it...

    again... I apologize for the alte submission...

    //if some of the naming conventions seem wierd... thats because they were pulled from and edited from the dumpster file...
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <stdint.h> //this is for a max_int check to ensure we dont exceed the int ceiling

using namespace std;

#define SIZE 71
#define FILLCOUNT 35
int breaker=0; //this is also a tip jared showed me (btw i'm not sure if im spelling his name correctly... hopefully i am :?)

/*    quick overview:
list structs in use:
  -1x linked list with overflow accommodations (71x preallocated nodes) (ll)
  -1x linked list with bucket storage (71x preallocated nodes) (ll)
  -2x static arrays (ba)

hashing methods (each will be paired with the modulo division method):
  -1x original list of keys
  -1x digit extract (de)
  -1x direct hash (dh)
  -1x folding method (Fm)
  -1x rotation method + digit extraction (rm_de)

collision resolution methods:
  -1x overflow list method (ol)
  -1x bucket method (bm)
  -1x quadratic probe (qp)
  -1x hash^2 and pseudorandom resolution via rehash (pr)

so resulting combinations:
  -1x overflow list with a digit extract hash (ll_ol_de)
  -1x bucket list with a folding method (ll_bl_fm)
  -1x static array with a direct hash, and quadratic probe
          resolution. (sa_dh_qp)
  -1x static array with a rotation method + digit extract hash,
          and a double hash collision resolution. (sa_rm_pr)

*/
//--------------------------------------------Node structs
struct Node{
  int key;

  bool nodeIsFull;

  int overflow_len;
  Node* overflow;
  Node* next;
};
//------------------
struct Bucket_Node{
  int key1;

  int key2;

  int key3;

  int key4;

  bool nodeIsEmpty;
  bool nodeIsFull;

  Bucket_Node* next;
};
//-------------------------------------------List Structs
int sa_dh_qp[SIZE];//curious if I was supposed to make these
int sa_rm_pr[SIZE];//structs or nah... maybe leaving as global
int ORIGINALS[SIZE];//variables is ok? .. actually realizing now that I dont
                    //know how to make a known variable behave as a struct.
                    //capable of creating instances of it and whatnot...
                    //perhaps that would be something to do with classes?
//------------
struct List{
  Node* head;
  int size;
};
//------------
struct Bucket_List{
  Bucket_Node* head;
  int size;
};
//--------------------------------------------Other Functions
int num_len(int num){
  int len=0;
  while(num!=0){
    num/=10;
    len+=1;
  }
  return len;
}
//--------------------------------------------Init functions
void init_array(int* array){
  int counter=0;
  while (counter<SIZE){
    array[counter]=-1;
    counter++;
  }
  return;
}
//------------------------
void init_node(Node* &node){
  node->key=-1;

  node->nodeIsFull=false;

  node->overflow_len=0;
  node->overflow=NULL;
  node->next=NULL;
  return;
}
//---------------
void init_bucket_node(Bucket_Node* &node){
  node->key1=-1;

  node->key2=-1;

  node->key3=-1;

  node->key4=-1;

  node->nodeIsEmpty=true;
  node->nodeIsFull=false;

  node->next=NULL;
  return;
}
//-------------
void init_list(List* &list){
  list= new List;
  list->head=NULL;
  list->size=0;
  return;
}
//--------------
void init_bucket_list(Bucket_List* &list){
  list= new Bucket_List;
  list->head=NULL;
  list->size=0;
  return;
}
//---------------
void populate_list(List* &list){
  Node* current=NULL;
  while (list->size < SIZE){
    if(list->head==NULL){//if first node in list
      list->head= new Node;
      current=list->head;
    }
    else{
      current->next= new Node;
      current= current->next;
    }
    init_node(current);
    list->size++;
  }
  return;
}
//--------------
void populate_bucket_list(Bucket_List* &list){
  Bucket_Node* current=NULL;
  while(list->size<SIZE){
    if(list->head==NULL){//if first node in list
      list->head= new Bucket_Node;
      current=list->head;
    }
    else{
      current->next= new Bucket_Node;
      current= current->next;
    }
    init_bucket_node(current);
    list->size++;
  }
  return;
}
//--------------------------------------------Hash functions
int extract_digit(int source_number){
  int extraction=0;
  int hold[3]={0,0,0};

  // we want the first third and fifth digits
  hold[0]=source_number%10;
  source_number/=100;
  hold[1]=source_number%10;
  source_number/=100;
  hold[2]=source_number%100;

  int loopcounter=2;
  while(loopcounter>-1){
    extraction*=10;
    extraction+=hold[loopcounter];
    loopcounter--;
  }
  return extraction;
}
//-----------------------
int rotation(int number){// rotates numbers like so: 10000-> 01000 -> 00100 ... ...
  int counter=0;
  int temp;
  while (counter<2){
    temp=number%10;
    number=number/10;
    temp=temp*10000;
    number=number+temp;
    counter++;
  }
  number=extract_digit(number);
  return number;
}
//----------------------
int fold(int number){
  int hold[3];  //we are going to grab 3 2 digit segments from the 5 digit key
  int counter=0;
  while (counter<3){
    hold[counter]=number%100;
    number%=100;
    counter++;
  }
  counter=0;
  while (counter<3){
    number+=hold[counter];
    counter++;
  }
  return number;
}
//-----------------
int direct_hash(int number){
  number=number%SIZE;
  return number;
}
//--------------------------------------------Collision Resolution Algoriddims
Node* probe_list(List* list, int address){
  Node* current= list->head;
  int counter=0;
  while(counter<address){
    current=current->next;
    counter++;
  }
  return current;
}
//------------------
Bucket_Node* probe_bucket_list(Bucket_List* list, int address){
  Bucket_Node* current= list->head;
  int counter=0;
  while(counter<address){
    current=current->next;
    counter++;
  }
  return current;
}
//--------------------
//--------------------------------------------Insert functions
int insert_overflow(Node* &node, Node* new_node){
  int collisions=0;
  if(node->key<new_node->key){// in order to keep the entire overflow + root node in order we need to be ready to swap the host node information out with new information, and slip it into the overflow list
    Node* slip_node= new Node; //using the slip node to slip the host information into the key-sequenced overflow list withuot disrupting the main list...
    init_node(slip_node);
    slip_node->key=node->key;
    slip_node->nodeIsFull=true;
    slip_node->overflow=node->overflow;
    node->key=new_node->key;
    node->overflow=slip_node;
    delete new_node;
    collisions+=1;
  }
  else{
    collisions+=1;
    if (node->overflow_len==0){
      node->overflow=new_node;
    }
    else{
      Node* current=node;
      Node* n_xt=node->overflow;
      while (n_xt->overflow!=NULL){// the farther into the overflow, the larger the id
        if(n_xt->key < new_node->key){
          current=n_xt;               //'1$&5a_f^aki'
          n_xt=n_xt->overflow;         //'1$&5a_f^aki'
          collisions++;
        }
      }
      if (n_xt->key<new_node->key){
        n_xt->overflow=new_node;
      }
      else{
        current->overflow=new_node;
        new_node->overflow=n_xt;
      }
    }
  }
  return collisions;
}
//--------------
int insert_list(List* list, int key){
  int collisions=0;
  int hash=extract_digit(key);
  int address=hash%SIZE;
  Node* node=probe_list(list, address);
  if (node->nodeIsFull){//its a bool
    Node* new_node= new Node;
    init_node(new_node);
    new_node->key=key;
    new_node->nodeIsFull=true;
    collisions+=insert_overflow(node, new_node);
    node->overflow_len++;
    collisions++;
  }
  else{
    node->key=key;
    node->nodeIsFull=true;
  }
  return collisions;
}
//------------------
int insert_bucket_list(Bucket_List* bucket_list, int key){
  int collisions=0;
  int hash=fold(key);
  int address=hash%SIZE;
  Bucket_Node* node=probe_bucket_list(bucket_list, address);
  if (node->nodeIsFull){//its a bool
    collisions=-4;
    cout<<"\nFailed Insert for bucket: "<<key;
  }
  else{
    if(node->key1==-1){
      node->key1=key;
      collisions=1;
      node->nodeIsEmpty=false;
    }
    else if (node->key2==-1){
      node->key2=key;
      collisions=2;
    }
    else if (node->key3==-1){
      node->key3=hash;
      collisions=3;
    }
    else{
      node->key4=key;
      node->nodeIsFull=true;
      collisions=4;
    }
  }
  return collisions;
}
//----------------
int insert_array_direct(int* array, int key){ //allows for 3 collisions before counting as a fail
  int collisions=0;
  int probecounter=1; //first time probecounter would posibly be used is on the second probe so...
  int hash=direct_hash(key); // first hash
  int address=hash%SIZE;
  while(probecounter<7 && (array[address]==-1 || array[address]!=key)){
    if (array[address]==-1){
      array[address]=key;
    }
    else{
      address=(int)pow(address,probecounter+1)%SIZE; //second hash and third
      collisions++;
    }
    probecounter++;
  }
  if(array[address]!=key){
    collisions*=-1;
    cout<<"\nFailed Insert for Direct Hash: "<<key;
  }
  return collisions;
}
//------------------
int insert_array_rehash(int* array, int key){ //allows for 3 collisions before counting as a fail
  int collisions=0;
  int counter=0;
  int hash=rotation(key);
  int address=hash%SIZE;
  while (counter<7 && (array[address]==-1||array[address]!=key)){
    if (array[address]==-1){
      array[address]=key;
    }
    else{
      while(INT8_MAX/hash>=hash){// this prevents the hash^2 from exceeding int ceiling
        hash=hash/2;
      }
      hash*=hash;
      hash=rotation(hash);
      address=hash%SIZE;
      collisions++;
    }
    counter++;
  }
  if(array[address]!=key){
    collisions*=-1;
    cout<<"\nFailed Insert for Rehash: "<<key;
  }
  return collisions;
}

//--------------------------------------------Print Functions


int main(){
  srand(1);
  int counter=0;
  int key;
  int temp;
  int list_collisions=0;
  int list_failed_inserts=0;
  int bucket_collisions=0;
  int bucket_failed_inserts=0;
  int sa_dh_qp_collisions=0; //sa_dh_qp= static array, direct hash, quadratic probe
  int sa_dh_qp_failed_inserts=0;
  int sa_rm_pr_collisions=0;//sa_rm_pr= static array, rotation method, pseudorandom rehash
  int sa_rm_pr_failed_inserts=0;
  List* list=NULL;
  Bucket_List* bucket=NULL;
  cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
  init_list(list);
  populate_list(list);

  init_bucket_list(bucket);
  populate_bucket_list(bucket);

  init_array(sa_dh_qp);
  init_array(sa_rm_pr);

  while(counter<FILLCOUNT){
    key=rand()%100000;// 00000 - 99999 //
    ORIGINALS[counter]=key;
    //--------
    temp=insert_list(list, key);
    if (temp<0){ // if  not inserted (insert failed) (!insert  (insert== false) !false ==true)
      list_collisions+=(temp*-1);
      list_failed_inserts++;
    }
    else{
      list_collisions+=temp;
    }
    //-------
    temp=insert_bucket_list(bucket, key);
    if (temp<0){
      bucket_collisions+=(temp*-1);
      bucket_failed_inserts++;
    }
    else{
      bucket_collisions+=temp;
    }
    //------------
    temp= insert_array_direct(sa_dh_qp, key);
    if (temp<0){
      sa_dh_qp_collisions+=(temp*-1);
      sa_dh_qp_failed_inserts++;
    }
    else{
      sa_dh_qp_collisions+=temp;
    }
    temp= insert_array_rehash(sa_rm_pr, key);
    if (temp<0){
      sa_rm_pr_collisions+=(temp*-1);
      sa_rm_pr_failed_inserts++;
    }
    else{
      sa_rm_pr_collisions+=temp;
    }
      counter++;
  }

  cout<< "\n\nKey:\n"<<
    "top column: \n\t-headers:\n\t\t-original list\n\t\t-overflow list (list)\n\t\t-bucket\n"
    <<"\t\t-direct hash array (dh_qp)\n\t\t-rotation metod array(rm_pr)";
  cout<<"\n\nLine Notation:\n"<<
  "\nExample: 04.2\n\t\t-'04': means fourth node in list"<<
  "\n\t\t-'.2': means the second node of the overflow buffer (found in the bucket and overflow list...)";

  cout<< "\n\n\n\n00.0" ;
  cout<<"\torig.";
  cout<<"\tbucket";
  cout<<"\tlist";
  cout<<"\tbuckt";
  cout<<"\tdh_qp";
  cout<<"\trm_pr";

  //cout<< setfill('0') <<setw(5) << "";
  Node* node=NULL;
  Bucket_Node* bnode=NULL;
  counter=0;
  bool tabspace=false;
  int inside_count=1;
  while (counter<SIZE){
    cout<<"\n\n";
    cout<< setfill('0') <<setw(2) << counter+1 <<".0";

    node=probe_list(list,counter);
    bnode=probe_bucket_list(bucket,counter);

    cout<<"\t";
    if (node->key==-1)
      cout <<"_____";
    else
      cout<<setfill('0') <<setw(5) <<node->key;
    node=node->overflow;
    cout<<"\t";
    if (bnode->key1==-1)
      cout <<"_____";
    else
      cout<<setfill('0') <<setw(5) <<bnode->key1;
    if(bnode->key2==-1){
      bnode->nodeIsEmpty=true; // this notes there is nothing left in the node
    }
    cout<<"\t";
    if (sa_dh_qp[counter]==-1)
      cout <<"_____";
    else
    cout<<setfill('0') <<setw(5) <<sa_dh_qp[counter];
    cout<<"\t";
    if (sa_rm_pr[counter]==-1)
      cout <<"_____";
    else
    cout<<setfill('0') <<setw(5) <<sa_rm_pr[counter];

    while(node!=NULL || !bnode->nodeIsEmpty){
      cout<< "\n\n";
      cout<< setfill('0') <<setw(2) << counter <<"."<<inside_count;
      //---------list
      if (node==NULL){
        cout<<"\t_N/A_";
        tabspace=true;
      }
      else{
        cout<<"\t"<< setfill('0')<<setw(5)<< node->key;
        node=node->overflow;
      }
      //----------bucket
      switch(inside_count){
        case 1:
            if(!bnode->nodeIsEmpty){
              if (tabspace)
                cout<< "\t";
              else
                cout<< "\t";
              cout<<setfill('0')<<setw(5)<< bnode->key2;
              if(bnode->key3==-1)
                bnode->nodeIsEmpty=true; // marks tha we've read all the relevant information
            }
            else
              cout<<"\t_N/A_";
          break;
        case 2:
            if(!bnode->nodeIsEmpty){
              if (tabspace)
                cout<< "\t";
              else
                cout<< "\t";
              cout<<setfill('0')<<setw(5)<< bnode->key3;
              if(bnode->key4==-1)
                bnode->nodeIsEmpty=true; // marks tha we've read all the relevant information
            }
            else
              cout<<"\t N/A";
          break;
        case 3:
            if(!bnode->nodeIsEmpty){
              if (tabspace)
                cout<< "\t";
              else
                cout<< "\t";
              cout<<setfill('0')<<setw(5)<< bnode->key4;
              bnode->nodeIsEmpty=true;
            }
            else
              cout<<"\t_N/A_";
          break;
        default:
          break;
      }
      cout <<"\t_N/A_\t_N/A_";
      inside_count++;
    }
    tabspace=false;
    inside_count=1;
    counter++;
  }
  cout <<"\n\n";

  cout<<"records per list:"
    <<"\n\noverflow list fails:\t\t"<< list_failed_inserts
    <<"\noverflow list collisions:\t"<< list_collisions
    <<"\n\nbucket list fails:\t\t"<< bucket_failed_inserts
    <<"\nbucket list collisions:\t\t"<<bucket_collisions
    <<"\n\ndirect hash array fails:\t" <<sa_dh_qp_failed_inserts
    <<"\ndirect hash array collisions:\t"<<sa_dh_qp_collisions
    <<"\n\nrotation array fails:\t\t"  <<sa_rm_pr_failed_inserts
    <<"\nrotation array collisions:\t" <<sa_rm_pr_collisions <<"\n\n";
  return 0;
}
