#include <iostream>

using namespace std;

int digit_extraction(int num, int digit){
  int extract;

  switch(digit){
    case 1:
      extract= num%10;
      break;
    case 2:
      extract= (num/10)%10;
      break;
    case 3:
      extract= (num/100)%10;
      break;
    case 4:
      extract= (num/1000)%10;
      break;
    case 5:
      extract= (num/10000)%10;
      break;
  }

  return extract;
}


int main(){
  int num;
  int extract;
  int digit;
  cout << "gimme a number:\n ";
  cin >> num;
  cout << "which digit to extract:\n"
       << "\t1) 0000_\n"
       << "\t2) 000_0\n"
       << "\t3) 00_00\n"
       << "\t4) 0_000\n"
       << "\t5) _0000\n"
       << "\n\tchoice: ";
  cin >> digit;

  extract=digit_extraction(num, digit);

  cout << "\n" << extract<<"\n\n";

  return 0;
}
