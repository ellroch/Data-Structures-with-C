#include <iostream>

using namespace std;

template<class TYPE>
TYPE  addType(TYPE x, TYPE y){
  TYPE z=x+y;
  return z;
}

int main (){
  int xi=3;
  int yi=5;

  float xf=3.7;
  float yf=6.2;

  char xc='x';
  char yc='y';
  
  cout<< "Please enter an integer for x: ";
  cin>> xi;

  cout << "The sume of integers x and y is "<< addType(xi, yi)<< endl;
  cout << "The sume of floats x and y is "<< addType(xf, yf)<< endl;
  cout << "The sume of characters x and y is "<< addType(xc, yc)<< endl;



  return 0;
}
