//#include <string>

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct navigator;
struct connection_node;
struct network_node;
struct network;
struct path_tree_node;
struct nav_path_list;

//http://en.cppreference.com/w/cpp/string/basic_string/assign  <-- my reference source for the std::string stuff
//template<class CharT, class Traits= std::char traits<CharT>, class Allocator = std::allocator<CharT>>class basic_string;
struct navigator{
  //path_tree_node* shortest_path; //1958giia8489giai
  char target_location;
  //char* shortest_path;
  nav_path_list* path;
  int weight;
};

struct connection_node{
  network_node* to;
  int weight;
  connection_node* next_arc;
};

struct network_node{
  connection_node* connections; //the list of arcs from this node
  network_node* net_list; //the main inventory of nodes on the network
  char node_id; //city name
};

struct network{
  int node_count;
  network_node* net_list; // this points to the next node in the network list, holding all the nodes
};

struct path_tree_node{
  path_tree_node* prev;
  int cumulative_weight;
  network_node* net_node;
  path_tree_node* next;
};

struct nav_path_list{
  network_node* net_node;
  nav_path_list* next;
};

#endif
