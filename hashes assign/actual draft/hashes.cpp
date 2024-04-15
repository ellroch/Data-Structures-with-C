/*--------------------------------------------------------------File
file comments here~
construction flaw Note: Overflow list,
    on the overflow list I should have continued the chain
    with the "overflow" pointer acting as the "next" pointer
    Instead the first node( the member of the original list
    and also the smallest key value at that address) is the
    only node using it... this caused some behaviors required
    workarounds... had I used the "oveflow" as the 'next' pointer
    I wouldnt have had to do this... if you want to see details...
    I had a lot of trouble with finding the intended location of a node in the overflow list
    it was in the while loop of the else statement in insert_overflow()
    P.S. I went through and did this^^ couldnt actually get it to work around...
          and it wasnt even that hard.. wasted a lot of time there :(

something went wrong... i might miss a few printf"test" statements during cleanup

Notes, And Considerations:
i feel like the main function is rather burly and ugly... I could have created
a struct that stored the list pointers and passed that into a function that
filled them... and another that printed them...
I could also ahve stored the collisions and failed inserts in the list structs
for convenience...
:/ it's kinda late now though :\

the 'id' in the nodes is essentially the result of the hash

I realize put in a number of  unneccessary error handling controls,
I forgot the key was going to be 5 digits long so I was accounting for
excessively large RNG inputs... I imagine there are a few controls left yet...
apologies for any confusion this causes...

Apologies if there is an excess of comments... I had to put in comments of
near-pseudocode to keep things straight... I figured I'd leave them in for
anyone reading this, maybe it's too much tho since you can just read the code...

I also noticed that I didnt account for the off chance that the rng key and/or
hash results in a 0 value... if this happens it might be subject to overwrite or
appear to be empty since all nodes data is defaulted to 0...

I know that I could have accounted for a full bucket with rehashing or a
quadratic probe etc... but I don't quite like the idea of moving something from
the initial hash'ed address... the perfectionist in me would require that any time a value
is removed from the list that any collisions resolved during that node's occupation would
moved back to the now open spot - all for the sake of reducing search time
(albeit by a negligble amount)... but then this reconciliation would itself
cause collision issues if multiple values were offset... I don't like that...
I'm going to have to get used to it... I get how it works... but if reconciling
an offset after a delete is going to cause me more trouble
-- in summary of ^this^ paragraph... I like overflow lists for collision
-- resolution... most of the others irk me... they feel crude :(

Note on Extraction:
    I noticed that I say 'extract by' or 'extracted by' frequently in my comments...
    when you run across that just know that the number being extracted is the
    number X digits from the right, where the number being 'extracted by' is X
    (the rightmost digit being 'X=1')
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip> // in out manipulation ... for padding integer cout with 0's
using namespace std;


#define SIZE 71
#define FILLCOUNT 35

long debug=0;

/*--------------------------------------------------------------STRUCTURE DEFINITIONS
*/

//-------------------------------------------------struct node
struct Node{
  int id;
  int key;

  bool nodeIsFull;

  int overflow_len;
  Node* overflow;
  Node* next;
};
//-------------------------------------------------struct bucket_node
struct Bucket_Node{
  int id1;
  int key1;

  int id2;
  int key2;

  int id3;
  int key3;

  int id4;
  int key4;

  bool nodeIsFull;

  Bucket_Node* next;
};
//-------------------------------------------------struct list
struct List{
  Node* head;
  int size;
};
//-------------------------------------------------struct bucket list
struct Bucket_List{
  Bucket_Node* head;
  int size;
};
/*--------------------------------------------------------------BASIC UTILITIES
*/

/*-------------------------------------------------get int length
the number of digits in an integer  123 in = 3 out; 54321 in = 5 out; etc.
*/
int int_len(int num){
  int len=0;
  while(num!=0){
    num/=10;
    len+=1;
  }
  return len;
}
/*-------------------------------------------------integer exponents
this doesnt account for negative inputs... but we shouldnt need to worry about
that in this program... only reason I don't make it unsigned is I dont want my
text editor whining at me about the comparison between int and unsigned while I
write the rest of this file.
*/
int int_exp(int number, int power){
  // if negative power call a logarithmic function like log(num, power*-1)
  int counter=0;
  int value=1; //if power is 0 then value is 1... if power is 1 answer is number...etc
  while (counter<power){
    value= value*number;
    counter++;
  }
  return value;
}
/*--------------------------------------------------------------HASHING UTILITIES
*/

/*-------------------------------------------------extract_digit
  extracts a single target digit (x digits from the right) using division and modulus division
*/
int extract_digit(int target_digit, int source_number){
  printf("\ntest e_d 1");
  int extraction;
  printf("\ntest e_d 2");
  // because power -1 is not actually accounted for in int_exp we cant allow target digit 0 in this function
  extraction= ( source_number/(int_exp(10,target_digit-1)) )%10;
  printf("\ntest e_d 4");
  return extraction;
  printf("\ntest e_d 5");
}
//------------------------------------------------------------this is for hash_c
int extract_digit_2(int target_digit, int source_number, int length){
  printf("\ntest e_d 1");
  int extraction=0;
  printf("\ntest e_d 2");
  while(extraction==0){
  // because power -1 is not actually accounted for in int_exp we cant allow target digit 0 in this function
  extraction= ( source_number/(int_exp(10,length-target_digit-1) )%10);
  printf("\ntest e_d 4");
   target_digit--;
  }
  printf("\ntest e_d 5");
  return extraction;

}
/*-------------------------------------------------midsquare
  this extracts the middle (2nd-4th) digits from the right of a given number (presumably a 5 digit number)
  and returns that value
*/
int midsquare(int starting_value, int bot_range, int top_range){ //top_range and bot_range signify the ends of the target block
  int mid=0;
  int length=(top_range-bot_range)+1;
  // 5-3 would be 2... but we would want 3 numbers in the places 3, 4, and 5... so +1 to the subtraction
  int *extract_hold= new int[length]; //new int[length];
//  extract_hold= calloc(length, sizeof(int)); //acts like int array[length] ... but c++ doesnt like that syntax so :/
  int counter=0;
  while (counter<length){
    extract_hold[counter]=extract_digit(counter+bot_range,starting_value);
    counter++;
    //^^this^^ will make a [4,3,2] from the number 12345 given a range of 2-4
  }

 counter-=1; /* now we are going to count down in order to preserve the order of
  the chunk... but currently (in order to break the loop) the counter is at
  (max_list_index)+1 so we have to reset it and account for the 0 index in the
   conditional with a condition of >= 0 */
  while(counter>=0){
    // turn [4,3,2] into 234
    mid*=10;
    mid+=extract_hold[counter];
    counter--;
  }
  return mid;
}
/*-------------------------------------------------rotation
this allows for rotation of variant length numbers, however the length needs to be known by the calling function...
--- not sure if there is a way to determine the number of digits in a number without converting to a string and counting
--- characters... i didnt want to convert to alphanumerics though... :/
*/
int rotation(int number, int rotation_count, int number_of_digits){// rotates numbers like so: 10000-> 01000 -> 00100 ... ...
  int counter=0;
  int temp;
  while (counter<rotation_count){
    temp=extract_digit(1, number);
    number=number/10;
    temp=temp*int_exp(10,number_of_digits-1);
    number=number+temp;
    counter++;
  }
  return number;
}
/*-------------------------------------------------Flip
takes an integer and returns a flip of it... so 234 in returns 432... 17845 in returns 54871
*/
int flip(int num){
  int length=int_len(num);// int len() determines the number of digits in length the number is
  int *extract_hold= new int[length];
  int counter=0;
  while (counter<length){
    extract_hold[counter]=extract_digit(counter,num);
    counter++;
    //^^this^^ will make a [5,4,3,2,1] from the number 12345
  }

  counter=0;//reset the counter for the next loop... this will ensure that the numbers come out flipped...
  int flipped=0;

  while(counter<length){
    // turn [5,4,3,2,1] into 54321 (reverse of the original 12345)
    flipped*=10;
    flipped+=extract_hold[counter];
    counter++;
  }

  return flipped;
}
/*-------------------------------------------------Folding
I realize that folding is rather complex, so I'm not going to make this function
fully dynamic right now... maybe over thanksgiving break... I want to create a
fully dynamic function but for this program it's not explicitly necessary nor do
I currently have time to break it down... so I'mma build a gross, arbitrary, hard-
coded version for now... I will fix it later...
*/
int fold(int num){
                   // this is half fold shift and half fold boundary... :/ I feel like i may be overestimating this function but it seems creating a fully dynamic fold is a beefy piece of work
                  //... maybe its better to build static variations rather than have one master function? ... a lot of variables to take into accound with this function if we going dynamic
                 //so this will take num_len/2 into a midsquare to grab a chunk (like the chunk 45 in 12345)
  printf("\ntest b 1");
  int num_len=int_len(num);
  printf("\ntest b 2");
  int chunk_len=num_len/2;
  printf("\ntest b 3");
  int flipping_chunk=midsquare(num, 1, chunk_len);
  printf("\ntest b 4");
                //flip it... (becomes 54)
  flipping_chunk=flip(flipping_chunk);
  printf("\ntest b 5");
               //shift the rest of the number to the front (12300 -> 00123) ... note... we can get the same effect from our rotation function... but for readability we arent going to call any unnecessary functions
  num/=int_exp(10,chunk_len/2);
  printf("\ntest b 6");
              //and tack the flip onto the back (54 + 123 -> 54123)
  flipping_chunk*=int_exp(10,chunk_len-(chunk_len/2));
  printf("\ntest b 7");
  num+=flipping_chunk;
  printf("\ntest b 8");
             //our fold is complete :D
  return num;
}
//-------------------------------------------------
//-------------------------------------------------
/*--------------------------------------------------------------INIT FUNCTIONS
*/

//-------------------------------------------------init node
void init_node(Node* &node){
  node->id=0;
  node->key=0;

  node->nodeIsFull=false;

  node->overflow_len=0;
  node->overflow=NULL;
  node->next=NULL;
  return;
}
//-------------------------------------------------init bucket node
void init_bucket_node(Bucket_Node* &node){
  node->id1=0;
  node->key1=0;

  node->id2=0;
  node->key2=0;

  node->id3=0;
  node->key3=0;

  node->id4=0;
  node->key4=0;

  node->nodeIsFull=false;

  node->next=NULL;
  return;
}
//-------------------------------------------------init list
void init_list(List* &list){
  list= new List;
  list->head=NULL;
  list->size=0;
  return;
}
//-------------------------------------------------init bucket list
void init_bucket_list(Bucket_List* &list){
  list= new Bucket_List;
  list->head=NULL;
  list->size=0;
  return;
}
//-------------------------------------------------populate list
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
//-------------------------------------------------populate bucket list
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
/*--------------------------------------------------------------HASHING FUNCTIONS
*/

/*-------------------------------------------------hash a
this one goes ham...:
the comment block is basically interlaced with the code so... yea...

*/
int hash_a(int hash){
  int master_extract;

  int hash_len=int_len(hash);
  cout<< "\nhash: "<<hash<< "\thash len: "<<hash_len;
  printf("\ntest c 1");
  //digit extract(= 1 digit master extract)->
      // master extract will be determined from 2 extract operations...
      //first extract is by an arbitrary #,
      //second is by the return value of the first extract
  master_extract=extract_digit_2((7%hash_len)+1, hash, hash_len);// 4 is arbitrary
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  printf("\ntest c 2");
  if (master_extract==0){
    master_extract=7;
  }
  master_extract=extract_digit((master_extract%hash_len)+1, hash);
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  // this might return a 0 and if so I considered having a function that iterates over
  // each of the digits until a non-zero is selected... unfortunately this program has sapped me
  // and i dont feel like it s we will assign an arbitrary number
  if (master_extract==0){
    master_extract=7;
  }
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  //
  printf("\ntest c 3");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  //rotation->
  hash=rotation(hash, master_extract, hash_len);
  printf("\ntest c 4");
  //multiply by (master extract^3)->
  hash=hash*(int_exp(master_extract,3));
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  printf("\ntest c 5");
  hash_len=int_len(hash);
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  printf("\ntest c 6");
  //divide by (((master extract)digit extract) digit midsquare)->
      //using the master extract to find second number...
      //this second number (x) is both the starting point of the
      //midsquare and the range of the midsquare
      //to prevent from overreaching the end (any case where hash_len < master_extract + (x))
      //rotate the hash until (x is in the front of the number, and midsquare a range of (range%hash_len))
  int temp=extract_digit_2(master_extract%hash_len, hash, hash_len);
  printf("\ntest c 7");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  int counter=5;
  while(hash_len<6){
    hash=int_exp(hash,counter);
    hash_len=int_len(hash);
    counter--;
    hash-=master_extract;
  }
  hash_len=int_len(hash);
  hash=rotation(hash, master_extract%hash_len, hash_len);
  printf("\ntest c 8");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  hash=midsquare(hash, 1, temp%hash_len+1); //the '1' starts the midsquare at the first digit... which is where temp currently is - the first digit
  printf("\ntest c 9");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  //folding ->

  hash=fold(hash);
  printf("\ntest c 10");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  //divide by 2*(master extract)->
  hash/=(2*master_extract);
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  printf("\ntest c 11");
  //multiply by ((digit extract(master extract))^master extract)->
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  hash_len=int_len(hash);
  printf("\ntest c 12");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;

  int temp2=master_extract%hash_len+1;
  cout << hash<<":-: "<< temp2;
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  temp=extract_digit_2(temp2, hash, hash_len);
  /*if (temp==0){
    master_extract=2;
  }*/
  printf("\ntest c 13");
  cout<< "\nmaster xtract: " <<master_extract<<"\t hash: "<<hash<< "\thash len: "<<hash_len;
  if (temp2==0){
    return hash;
    printf("\ntest c 14");
  }
  else{
    hash*=(temp*master_extract);
    printf("\ntest c 15");
  };
  //-1
  hash-=1;
  printf("\ntest c 16");
  return hash; // high intensity over
}

/*-------------------------------------------------hash b
this is a direct hash... pretty boring
*/
int hash_b(int hash){
  hash%=100000;// 0-99999
  return hash; // boring...
}

/*--------------------------------------------------------------COLLISION RESOLUTION FUNCTIONS
*/

//-------------------------------------------------probe list
Node* probe_list(List &list, int address){
  Node* current= list.head;
  printf("\ntesting p1");
  int counter=0;
  printf("\ntesting p2");
  while(counter<address){
    printf("\ntesting p3");
    current=current->next;
    printf("\ntesting p4");
    counter++;
  }
  printf("\ntesting p5");
  return current;
}

//-------------------------------------------------probe bucket
Bucket_Node* probe_bucket_list(Bucket_List* list, int address){
  Bucket_Node* current= list->head;
  int counter=0;
  while(counter<address){
    current=current->next;
    counter++;
  }
  return current;
}

/*--------------------------------------------------------------FILL FUNCTIONS
Fills the list with keys according to the hashing
and collision resolution methods.
...
they are int functions, returning the number of collisions
...
failed insertions will be signified in negative returns... (# of collisions*-1)
*/
/*-------------------------------------------------insert overflow
the overflow lists are key sequenced lists
*/
int insert_overflow(Node* &node, Node* new_node){
  int collisions=0;
  printf("\ntesting o 1");
  if(node->key<new_node->key){// in order to keep the entire overflow + root node in order we need to be ready to swap the host node information out with new information, and slip it into the overflow list
    Node* slip_node= new Node; //using the slip node to slip the host information into the key-sequenced overflow list withuot disrupting the main list...
    init_node(slip_node);
    printf("\ntesting o 2");
    slip_node->id=node->id;
    slip_node->key=node->key;
    slip_node->nodeIsFull=true;
    slip_node->overflow=node->overflow;
    printf("\ntesting o 3");
    node->id=new_node->id;
    node->key=new_node->key;
    node->overflow=slip_node;
    printf("\ntesting o 4");
    delete new_node;
    collisions+=1;
  }
  else{
    collisions+=1;
    printf("\ntesting o 5");
    if (node->overflow_len==0){
      node->overflow=new_node;
      printf("\ntesting o 6");
    }
    else{
      Node* current=node;
      Node* n_xt=node->overflow;
      printf("\ntesting o 7");
      printf("\noverflow len: %d", node->overflow_len);
      printf("\ncurrent key: %d\tnext key: %d", current->key, n_xt->key);
      while (n_xt->overflow!=NULL){// the farther into the overflow, the larger the id
        printf("\ntest %li", debug++);
        if (debug==100)
          exit(1);
        if(n_xt->key < new_node->key){
          printf("\ntest o p 1");
          current=n_xt;               //'1$&5a_f^aki'
          printf("\ntest o p 2");
          n_xt=n_xt->overflow;         //'1$&5a_f^aki'
          printf("\ncurrent key: %d\tnext key: %d", current->key, n_xt->next->key);
          printf("\ncurrent address: %p\tnext address: %p", current, n_xt);
          printf("\ntesting o 8");
          collisions++;
        }
      }
      printf("\ntesting 0 8.5");
      if (n_xt->key<new_node->key){
        n_xt->overflow=new_node;
      }
      else{
        current->overflow=new_node;
        new_node->overflow=n_xt;
      }
      printf("\ntesting o 9");
    }
  }
  printf("\ntesting o 10");
  return collisions;
}

/*-------------------------------------------------insert list a
*/
int insert_list_a(List list, int key){
  int collisions=0;
  int hash=hash_a(key);
  int address=hash%SIZE;
  printf("\n testing 2");
  Node* node=probe_list(list, address);
  printf("\n testing 3");
  if (node->nodeIsFull){//its a bool
    Node* new_node= new Node;
    printf("\ntesting c 1");
    init_node(new_node);
    printf("\ntesting c 2");
    new_node->id=hash;
    new_node->key=key;
    new_node->nodeIsFull=true;
    printf("\ntesting c 3");
    collisions+=insert_overflow(node, new_node);
    printf("\ntesting c 4");
    node->overflow_len++;
    collisions++;
    printf("\n testing 4");
  }
  else{
    node->id=hash;
    node->key=key;
    node->nodeIsFull=true;
    printf("\n testing 5");
  }
  printf("\n testing 6");

  return collisions;
}

/*-------------------------------------------------insert list b
*/
int insert_list_b(List list, int key){
  int collisions=0;
  printf("\ntesting a");
  int hash=hash_b(key); //hash b is a mod of the list size so we dont need to... mod it here
  printf("\ntesting b");
  int address=hash%SIZE;
  printf("\ntesting c");
  Node* node=probe_list(list, address);
  printf("\n testing 10");
  if (node->nodeIsFull){//its a bool
    Node* new_node= new Node;

    init_node(new_node);

    new_node->id=hash;
    new_node->key=key;
    new_node->nodeIsFull=true;

    collisions+=insert_overflow(node, new_node);
    node->overflow_len++;
    collisions++;
    printf("\n testing 11");
  }
  else{
    node->id=hash;
    node->key=key;
    node->nodeIsFull=true;
    printf("\n testing 12");
  }
  printf("\n testing 13");

  return collisions;
}

/*-------------------------------------------------insert bucket_list a
*/
int insert_bucket_list_a(Bucket_List* bucket_list, int key){
  int collisions=0;
  int hash=hash_a(key);
  int address=hash%SIZE;
  Bucket_Node* node=probe_bucket_list(bucket_list, address);
  printf("\n testing 17");
  if (node->nodeIsFull){//its a bool
    collisions=-1;
    printf("\n testing 18");
  }
  else{
    if(node->id1==0){
      node->id1=hash;
      node->key1=key;
      collisions+=1;
      printf("\n testing 19");
    }
    else if (node->id2==0){
      node->id2=hash;
      node->key2=key;
      collisions+=2;
      printf("\n testing 20");
    }
    else if (node->id3==0){
      node->id3=hash;
      node->key3=hash;
      collisions+=3;
      printf("\n testing 21");
    }
    else{
      node->id4=hash;
      node->key4=key;
      node->nodeIsFull=true;
      collisions+=4;
      printf("\n testing 22");
    }
  }
  printf("\n testing 23");
  return collisions;
}

/*-------------------------------------------------insert bucket_list b
*/
int insert_bucket_bucket_list_b(Bucket_List* bucket_list, int key){
  int collisions=0;
  int hash=hash_b(key);
  int address=hash%SIZE;
  Bucket_Node* node=probe_bucket_list(bucket_list, address);
  printf("\n testing 27");
  if (node->nodeIsFull){//its a bool
    collisions=-1;
    printf("\n testing 28");
  }
  else{
    if(node->id1==0){
      node->id1=hash;
      node->key1=key;
      collisions+=1;
      printf("\n testing 29");
    }
    else if (node->id2==0){
      node->id2=hash;
      node->key2=key;
      collisions+=2;
      printf("\n testing 30");
    }
    else if (node->id3==0){
      node->id3=hash;
      node->key3=hash;
      collisions+=3;
      printf("\n testing 31");
    }
    else{
      node->id4=hash;
      node->key4=key;
      node->nodeIsFull=true;
      collisions+=4;
      printf("\n testing 32");
    }
  }
  printf("\n testing 33");
  return collisions;
}

/*--------------------------------------------------------------MAIN
*/

int main(){ // on hash 'a' I had fun :D ... i wanted to see if crazy crazy complicated hashes actually pay off or nah... so we got some juxtaposition going on here... I have a hunch that this much is excessive and uselessly redundant... but hey :D I get extra credit for having used each of the funky hash algorithms in the hash right?
  srand(1);
  List* list_a=NULL;            //1
  List* list_b=NULL;           // 2
  Bucket_List* bucket_a=NULL; //  3
  Bucket_List* bucket_b=NULL;//   4
  int key=0;
  init_list(list_a);
  populate_list(list_a);

  init_list(list_b);
  populate_list(list_b);

  init_bucket_list(bucket_a);
  populate_bucket_list(bucket_a);

  init_bucket_list(bucket_b);
  populate_bucket_list(bucket_b);

  // la_ = list a ba_= bucket a  etc... bucket (the a and b signify the hashing algorithm - hash_a or hash_b)
  int temp;

  int la_failed_inserts=0;
  int la_collisions=0;

  int lb_failed_inserts=0;
  int lb_collisions=0;

  int ba_failed_inserts=0;
  int ba_collisions=0;

  int bb_failed_inserts=0;
  int bb_collisions=0;

  int counter_l=0; //this is the counter for the loop operating the switch statement for iterating over each list with the same key
  int counter=0;  // this is the counter for the outer loop, generating the 35 keys

  while(counter<FILLCOUNT){

    key=rand()%100000;// 0 - 99999

    cout << "\nkeys generated: ";
    if (counter%4==0){
      cout <<"\n";
    }
    cout << setfill('0') << setw(2) << (counter+1) << ":  ";
    cout << setfill('0') << setw(5) << key << "\t";

    while (counter_l<4){
      switch(counter_l){
        printf("\n testing 1");
        case 0:
            temp=insert_list_a(*list_a, key);
            printf("\n testing 7");
            if (temp<0){ // if  not inserted (insert failed) (!insert  (insert== false) !false ==true)
              la_collisions+=(temp*-1);
              la_failed_inserts++;
              printf("\n testing 8");
            }
            else{
              la_collisions+=temp;
              printf("\n testing 9");
            }
            //list a
          break;
        case 1:
            temp=insert_list_b(*list_b, key);
            printf("\n testing 14");
            if (temp<0){
              lb_collisions+=(temp*-1);
              lb_failed_inserts++;
              printf("\n testing 15");
            }
            else{
              lb_collisions+=temp;
              printf("\n testing 16");
            }
            // list b
          break;
        case 2:
            temp= insert_bucket_list_a(bucket_a, key);
            printf("\n testing 24");
            if (temp<0){
              ba_collisions+=(temp*-1);
              ba_failed_inserts++;
              printf("\n testing 25");
            }
            else{
              ba_collisions+=temp;
              printf("\n testing 26");
            }
            //bucket a
          break;
        case 3:
            temp= insert_bucket_bucket_list_b(bucket_b, key);
            printf("\n testing 34");
            if (temp<0){
              bb_collisions+=(temp*-1);
              bb_failed_inserts++;
              printf("\n testing 35");
            }
            else{
              bb_collisions+=temp;
              printf("\n testing 36");
            }
            //bucket b
          break;
      }
      counter_l++;

    }
    counter_l=0;
    counter++;
  }
  printf("\n testing 37");

  //---------print the lists

 /*counter=0;
 while (counter<SIZE){
   counter_l=0;
   while(counter<4){

     counter_l++;
   }
   counter++;
 }*/











  return 0;
}
