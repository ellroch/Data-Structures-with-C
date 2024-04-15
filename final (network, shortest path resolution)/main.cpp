/*
dealing with strings in c++ gave me a lot of trouble - was trying to store the
final path as a string initially, but after I wrote it I realized that char*'s
cause a lot of problems... :/ gotta play with that some more.

if you want to watch it step by step through the recursive funcion I left in the
stuff I used for debugging, thought it was fun to go through...
all the cout's are commented out and tagged with this line "//q243tqrg3564ade5"

Sorry, I could have thrown it in a loop that lets you run through until you hit an
escape key but :/ I just want to submit it before I break it again. (ive broken it many times now)

*/

//---------//---------//---------//---------//---------//---------// Preprocessor
#include <iostream>
#include <iomanip>
//#include <string>
#include "structures.h"

using namespace std;

//---------//---------//---------//---------//---------//---------// GlobalScope Vars;
network Net;
navigator Nav;
int RecursionDepth;


//---------//---------//---------//---------//---------//---------// Init Functions
void init_path_tree_node(path_tree_node &branch);
void init_nav();
void init_connection_node(connection_node &connection);
void init_network_node(network_node &node);
void init_network();
void print_Net();
void find_path_from(path_tree_node* curr_point);// recursive
void clear_path();
void submit_path(path_tree_node* tree_node);
void print_path();
network_node* find_node(char ID);
connection_node* create_arc(char ID, int weight);
path_tree_node* reverse_nav(path_tree_node* curr_branch);
bool is_repeat(path_tree_node* path, char ID);
//---------//---------//---------//---------//---------//---------// Utility Functions

//---------//---------//---------//---------//---------//---------// Core Functions

//---------//---------//---------//---------//---------//---------// Recursive Function


//---------//---------//---------//---------//---------//---------// main function
int main(){
  //---------//---------// init independent structures
  RecursionDepth=0;
  init_nav();
  init_network();
  //---------//---------// build the network to match the map
  connection_node* last_connect=NULL;
  connection_node* connect=NULL;
  network_node* last_node=NULL;
  network_node* net_node=NULL;
  int counter=0;
  char ID='A';
  while (Net.node_count<17){ //iterate over each node on the map, ID's A-Q (noted on the .jpg included)
    //-------//------//make new node
    net_node= new network_node;
    if (net_node!=NULL && net_node!=last_node){ // just making sure
      init_network_node(*net_node);
    }
    //-------//------//Name the node:
    net_node->node_id= ID;

    //-------//------//point the last node to this one to maintain the net_list
    if (Net.node_count==0){ //the Net.net_list is empty and NULL
      Net.net_list=net_node;
    }
    else{
      last_node->net_list=net_node;
    }
    last_node=net_node;
    //-------//------//prepare for next node / iteration of loop
    //cout << "\n" << ID; // debugging
    //cout << "\n" << Net.node_count; // debugging
    ID+=1;
    Net.node_count+=1;
  }
  cout << "\nTotal Node Count: " << Net.node_count;
  //-------//------//set up so we can navigate over the Net struct and insert arcs
  net_node=Net.net_list;
  last_node=NULL;
  //-------//------//add the arcs to the nodes --- this is super convoluted ... probly could have used a loop but it was late when I did this and my brain was taking a break...
  while(counter<Net.node_count){
    switch(counter){
      case 0:
      ////////////////////////////insert connections here "A"
      connect = create_arc('B', 12); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('E', 18);
      connect= connect->next_arc;
      net_node=net_node->net_list;
      break;
      //-------
      case 1:
      ////////////////////////////insert connections here "B"
      connect = create_arc('A',12); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('C',3);
      connect=connect->next_arc;
      connect->next_arc=create_arc('D',3);
      net_node=net_node->net_list;
      break;
      //-------
      case 2:
      ////////////////////////////insert connections here "C"
      connect = create_arc('B',3); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('D',4);
      connect=connect->next_arc;
      connect->next_arc=create_arc('E',7);
      connect=connect->next_arc;
      connect->next_arc=create_arc('F',21);
      net_node=net_node->net_list;
      break;
      //-------
      case 3:
      ////////////////////////////insert connections here "D"
      connect = create_arc('B',3); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('C',4);
      connect=connect->next_arc;
      connect->next_arc=create_arc('G',19);
      net_node=net_node->net_list;
      break;
      //-------
      case 4:
      ////////////////////////////insert connections here "E"
      connect = create_arc('A',18); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('C',7);
      connect=connect->next_arc;
      connect->next_arc=create_arc('H',18);
      connect=connect->next_arc;
      connect->next_arc=create_arc('J',31);
      net_node=net_node->net_list;
      break;
      //-------
      case 5:
      ////////////////////////////insert connections here "F"
      connect = create_arc('C',21); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('G',4);
      connect=connect->next_arc;
      connect->next_arc=create_arc('I',13);
      connect=connect->next_arc;
      connect->next_arc=create_arc('M',6);
      net_node=net_node->net_list;
      break;
      //-------
      case 6:
      ////////////////////////////insert connections here "G"
      connect = create_arc('D',19); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('F',4);
      connect=connect->next_arc;
      connect->next_arc=create_arc('N',7);
      net_node=net_node->net_list;
      break;
      //-------
      case 7:
      ////////////////////////////insert connections here "H"
      connect = create_arc('E',18); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('I',3);
      connect=connect->next_arc;
      connect->next_arc=create_arc('J',12);
      net_node=net_node->net_list;
      break;
      //-------
      case 8:
      ////////////////////////////insert connections here "I"
      connect = create_arc('F',13); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('H',3);
      connect=connect->next_arc;
      connect->next_arc=create_arc('K',9);
      net_node=net_node->net_list;
      break;
      //-------
      case 9:
      ////////////////////////////insert connections here "J"
      connect = create_arc('E',31); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('H',12);
      connect=connect->next_arc;
      connect->next_arc=create_arc('Q',35);
      net_node=net_node->net_list;
      break;
      //-------
      case 10:
      ////////////////////////////insert connections here "K"
      connect = create_arc('I',9); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('L',9);
      connect=connect->next_arc;
      connect->next_arc=create_arc('Q',24);
      net_node=net_node->net_list;
      break;
      //-------
      case 11:
      ////////////////////////////insert connections here "L"
      connect = create_arc('K',9); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('M',6);
      connect=connect->next_arc;
      connect->next_arc=create_arc('O',6);
      net_node=net_node->net_list;
      break;
      //-------
      case 12:
      ////////////////////////////insert connections here "M"
      connect = create_arc('F',6); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('L',6);
      connect=connect->next_arc;
      connect->next_arc=create_arc('N',5);
      net_node=net_node->net_list;
      break;
      //-------
      case 13:
      ////////////////////////////insert connections here "N"
      connect = create_arc('G',7); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('M',5);
      connect=connect->next_arc;
      connect->next_arc=create_arc('P',14);
      net_node=net_node->net_list;
      break;
      //-------
      case 14:
      ////////////////////////////insert connections here "O"
      connect = create_arc('L',6); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('P',6);
      connect=connect->next_arc;
      connect->next_arc=create_arc('Q',8);
      net_node=net_node->net_list;
      break;
      //-------
      case 15:
      ////////////////////////////insert connections here "P"
      connect = create_arc('N',14); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('O',6);
      connect=connect->next_arc;
      connect->next_arc=create_arc('Q',7);
      net_node=net_node->net_list;
      break;
      //-------
      case 16:
      ////////////////////////////insert connections here "Q"
      connect = create_arc('J',35); //create_arc(char target, int weight)
      net_node->connections= connect;
      connect->next_arc=create_arc('K',24);
      connect=connect->next_arc;
      connect->next_arc=create_arc('O',8);
      connect=connect->next_arc;
      connect->next_arc=create_arc('P',7);
      net_node=net_node->net_list;
      //cout << "\n\nQ\n\n"; //debugging
      break;
      //-------
      default:
        cout << "\n\nPROBLEMS: something went wrong with that long ass switch in main()\n" << counter;
      break;
    }
    counter++;
  }
  //---------//---------// print test the network
  print_Net();
  //---------//---------// prompt user for starting city
  //char* user_in=NULL;
  int start_in = -1;
  cout << "\nWhich node (city) would you like to start at?"
        <<"\n 1) A"
        <<"\n 2) B"
        <<"\n 3) C"
        <<"\n 4) D"
        <<"\n 5) E"
        <<"\n 6) F"
        <<"\n 7) G"
        <<"\n 8) H"
        <<"\n 9) I"
        <<"\n10) J"
        <<"\n11) K"
        <<"\n12) L"
        <<"\n13) M"
        <<"\n14) N"
        <<"\n15) O"
        <<"\n16) P"
        <<"\n17) Q"
        <<"\n\n : ";
  while(start_in<1 || start_in >17){
    cin >> start_in;
    if (start_in<1 || start_in >17){
      cout << "\nERROR: Your selection was invalid, please select a value between 1 and 17"
            << "\n\n : ";
      cin.clear();          // these lines are here just in case
      cin.ignore(100, '\n');// the user input a non-integer value.
    }
  }
  int end_in = -1;
  cout << "\nWhich node (city) would you like to end at?"
        <<"\n 1) A"
        <<"\n 2) B"
        <<"\n 3) C"
        <<"\n 4) D"
        <<"\n 5) E"
        <<"\n 6) F"
        <<"\n 7) G"
        <<"\n 8) H"
        <<"\n 9) I"
        <<"\n10) J"
        <<"\n11) K"
        <<"\n12) L"
        <<"\n13) M"
        <<"\n14) N"
        <<"\n15) O"
        <<"\n16) P"
        <<"\n17) Q"
        <<"\n\n : ";
  while((end_in<1 || end_in >17) || end_in==start_in){
    cin >> end_in;
    if (end_in==start_in){
      cout << "\nERROR: Your destination and your starting point are the same."
            <<"\n       Please select a distinct destination."
            <<"\n\n : ";
    }
    else if (end_in<1 || end_in >17){
      cout << "\nERROR: Your selection was invalid, please select a value between 1 and 17"
            << "\n\n : ";
      cin.clear();          // these lines are here just in case
      cin.ignore(100, '\n');// the user inputs a non-integer value.
    }
  }
  //---------//---------// switch statements to match user input to the appropriate node ID's
  char start_id=0;
  char end_id=0;
  switch(start_in){
    case 1:
      start_id='A';
    break;
    case 2:
      start_id='B';
    break;
    case 3:
      start_id='C';
    break;
    case 4:
      start_id='D';
    break;
    case 5:
      start_id='E';
    break;
    case 6:
      start_id='F';
    break;
    case 7:
      start_id='G';
    break;
    case 8:
      start_id='H';
    break;
    case 9:
      start_id='I';
    break;
    case 10:
      start_id='j';
    break;
    case 11:
      start_id='K';
    break;
    case 12:
      start_id='L';
    break;
    case 13:
      start_id='M';
    break;
    case 14:
      start_id='N';
    break;
    case 15:
      start_id='O';
    break;
    case 16:
      start_id='P';
    break;
    case 17:
      start_id='Q';
    break;
    default:
      cout <<"\nERROR: something went wrong in the switch statement dealing with variable start_in";
    break;
  }
  switch(end_in){
    case 1:
      end_id='A';
    break;
    case 2:
      end_id='B';
    break;
    case 3:
      end_id='C';
    break;
    case 4:
      end_id='D';
    break;
    case 5:
      end_id='E';
    break;
    case 6:
      end_id='F';
    break;
    case 7:
      end_id='G';
    break;
    case 8:
      end_id='H';
    break;
    case 9:
      end_id='I';
    break;
    case 10:
      end_id='j';
    break;
    case 11:
      end_id='K';
    break;
    case 12:
      end_id='L';
    break;
    case 13:
      end_id='M';
    break;
    case 14:
      end_id='N';
    break;
    case 15:
      end_id='O';
    break;
    case 16:
      end_id='P';
    break;
    case 17:
      end_id='Q';
    break;
    default:
      cout <<"\nERROR: something went wrong in the switch statement dealing with variable end_in";
    break;
  }
  // set Nav.target_location to the end_id
  Nav.target_location=end_id;
  //---------//---------// call the recursive function
  net_node=find_node(start_id);
  if (net_node==NULL){
    cout << "ERROR: Strange though it is, the starting node could not be found... try the program again?";
    return 0;//---------//---------//---------//---------//---------//---------//early return call because something must not be working if this happens
  }
  path_tree_node* root= new path_tree_node;
  init_path_tree_node(*root);
  root->net_node=net_node;
  root->cumulative_weight=0;
  find_path_from(root);
  //---------//---------// print the resulting path from
  cout << "\n\nThe Shortest Path from " << start_id << " to " << end_id <<" is as follows:";
  print_path();
  cout << "\n\tTotal Weight: " << Nav.weight << endl;
  //---------//---------// end program
  return 0;
}


//---------//---------//---------//---------//---------//---------// Init Function definitions

//---------//---------//---------// init path_tree_node
void init_path_tree_node(path_tree_node &branch){
  branch.prev=NULL;
  branch.cumulative_weight=0;
  branch.net_node=NULL;
  branch.next=NULL;
}
//---------//---------//---------// init navigator
void init_nav(){
  Nav.target_location=NULL;
  Nav.path=NULL;
  Nav.weight=0;
}
//---------//---------//---------// init connection_node
void init_connection_node(connection_node &connection){
  connection.to=NULL;
  connection.weight=0;
  connection.next_arc=NULL;
}
//---------//---------//---------// init network_node
void init_network_node(network_node &node){
  node.connections=NULL;
  node.net_list=NULL;
  node.node_id=NULL;
}
//---------//---------//---------// init network
void init_network(){
  Net.node_count=0;
  Net.net_list=NULL;
}
//---------//---------//---------// init nav_path_list (node)
void init_nav_path_list(nav_path_list &node){
  node.net_node=NULL;
  node.next=NULL;
}
//---------//---------//---------//---------//---------//---------// Utility Function definitions

//---------//---------//---------// create arc
connection_node* create_arc(char ID, int weight){
  connection_node* new_arc = new connection_node;
      init_connection_node(*new_arc);
      new_arc->weight= weight;
  network_node* target = Net.net_list;

  while(target->node_id!=ID && target!=NULL){
    target= target->net_list;
  }
  if (target!=NULL){
    new_arc->to = target;
  }
  return new_arc;
}
//---------//---------//---------// print network
void print_Net(){
  network_node* current=Net.net_list;
  connection_node* connect;
  cout << "\n\nThe current state of the network is noted below"
      << "\nnotation:\t\"'source_id': ('dest_id','weight'), ('dest_id','weight')\"...\n";
  if(current != NULL){
    while(current!=NULL){
      cout << "\n" << current->node_id <<": ";
      connect= current->connections;
      if (connect!=NULL){
        while(connect!=NULL){
          cout << "(" << connect->to->node_id << ","<< setw(2)<< connect->weight << setw(0) << ")";
          if(connect->next_arc!=NULL){
            cout << ", ";
          }
          connect=connect->next_arc;
        }
      }
      else{
        cout << "NO CONNECTIONS";
      }

      current=current->net_list;
    }
  }
  else{
    cout << "\nThe network is empty, add some nodes and try again\n";
  }
  cout << endl;
}
//---------//---------//---------//find node
network_node* find_node(char ID){
  network_node* current=Net.net_list;
  while(current!=NULL && current->node_id!=ID){
    current=current->net_list;
  }
  return current;
}
//---------//---------//---------//is repeat
bool is_repeat(path_tree_node* path, char ID){
  while(path->next!=NULL){
    if(path->net_node->node_id==ID){
      return true;
    }
    path=path->next;
  }
  return false;
}
//---------//---------//---------//reverse_nav
path_tree_node* reverse_nav(path_tree_node* curr_branch){
  while (curr_branch->prev!=NULL){
    curr_branch=curr_branch->prev;
  }
  return curr_branch;
}
//---------//---------//---------// clear path
void clear_path(){
  nav_path_list* curr=Nav.path;
  nav_path_list* next=NULL;
  while (curr!=NULL){
    next=curr->next;
    delete curr;
    curr=next;
  }
  Nav.path=NULL;
  return;
}
//---------//---------//---------// submit path
void submit_path(path_tree_node* tree_node){
  nav_path_list* path_list=new nav_path_list;
  Nav.path=path_list;
  init_nav_path_list(*path_list);
  while (tree_node!=NULL){
    path_list->net_node=tree_node->net_node;
    tree_node=tree_node->next;
    if (tree_node!=NULL) {// if the increment revealed that there is another step in the path
      path_list->next= new nav_path_list;
      path_list=path_list->next;
      init_nav_path_list(*path_list);
    }
  }
  return;
}
//---------//---------//---------// print path
void print_path(){
  nav_path_list* curr=Nav.path;
  cout << "\n\n\t";
  while (curr!=NULL){
    cout << curr->net_node->node_id;
    if (curr->next!=NULL){
      cout << " -> ";
    }
    curr=curr->next;
  }
  return;
}
//---------//---------//---------//
//---------//---------//---------//
//---------//---------//---------//

//---------//---------//---------//---------//---------//---------// Recursive Func definition
/*  _NAME_GOES_HERE_
a recursive function that charts out each potential path, comparing the cumulative_weight
of any that end on the target node to the shortest path on record (found in Nav struct)...
if the new path's weight is less than theone on record, we reverse navigate back
to the root to trace the current path to a char* which replaces the one on record...
and then we continue exhausting all potential paths. (each node is deleted after it's children
have been exhausted so this helps to manage memory without becoming overly complicated)
Parameters:
      - path_tree_node* : (the root node pointing to the starting city),

*/
void find_path_from(path_tree_node* curr_point){
  //   process this node (this is preorder recursion)
  //  Kill this node immediately if:
  //x   - this ID can be found in the reverse_nav id char*. (prevents loops) ('is_repeat()' will return bool after check)
  //  do not call any connections if:
  //x   - curr_point->net_node->node_id == Nav.target_location
  //x   - curr_point->cumulative_weight >= Nav.weight (unless Nav.weight==0)
  //  escape program if:
  //x   -recursion depth exceeds the total number of nodes in the list

  RecursionDepth++;
  //cout << "\nRecursionDepth: " << RecursionDepth; //q243tqrg3564ade5
  //cout << "\ncurrent node weight is: " << curr_point->cumulative_weight; //q243tqrg3564ade5
  if(RecursionDepth<=Net.node_count){
    //cout << "\ntesting RecursionDepth"; //q243tqrg3564ade5
    path_tree_node* root= reverse_nav(curr_point);
    //cout << "\ntesting reverse_nav()"; //q243tqrg3564ade5
    //cout << "\nroot ID: " << root->net_node->node_id << "\tcurrent ID: " <<  curr_point->net_node->node_id; //q243tqrg3564ade5
    if(!is_repeat(root, curr_point->net_node->node_id)){
      //cout << "\ntesting is_repeat()"; //q243tqrg3564ade5
      if((curr_point->cumulative_weight < Nav.weight && Nav.weight!=0) || Nav.weight==0){
        if (curr_point->net_node->node_id==Nav.target_location){
          clear_path();
          submit_path(root);
          Nav.weight=curr_point->cumulative_weight;
        }
        else{
          //call the recursive function on each connection to the current net_node
          connection_node* connect=curr_point->net_node->connections;
          path_tree_node* next_point=NULL;
          //cout << "\nconnect: " << connect; //q243tqrg3564ade5
          //cout << "\nconnect ID: " << connect->to->node_id; //q243tqrg3564ade5
          while(connect!=NULL){
            next_point= new path_tree_node;
            init_path_tree_node(*next_point);
            curr_point->next=next_point;
            next_point->prev=curr_point;
            next_point->net_node=connect->to;
            next_point->cumulative_weight=curr_point->cumulative_weight + connect->weight;
            //cout << "\nthe weight between node "<< curr_point->net_node->node_id << " and " << next_point->net_node->node_id << " is: " << connect->weight; //q243tqrg3564ade5
            //cout << "\nthe cumulative weight so far is: "<< curr_point->cumulative_weight + connect->weight << endl; //q243tqrg3564ade5
            find_path_from(next_point);
            connect=connect->next_arc;
          }
        }
      }
    }
  }
  //delete the structure at curr_point, end function
  RecursionDepth--;
  delete curr_point;
  return;
}
