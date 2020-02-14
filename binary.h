//binary input to check the preimage state
#ifndef _nt92_class_binary_
#define _nt92_class_binary_
#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <cmath> 
#include <time.h>
//#include <conio.h>
#include <stdio.h>
using namespace std; 
class binary
{
  int cell;  //L=?
  int totall;  //STATE NUMBER
  int *a;
   
  public:
   //constructor:
   binary(){;};
   binary (int ,int );
   
   //memberfunction:
   inline int get(const int i) const  //得到某個時間的陣列值 
                        { return this->a[i]; } 
   void print() const;
      };
binary::binary(int total ,int cellnum)
{
//  cout << cellnum;
  this->totall = total;
  
  this->cell = cellnum;
  this-> a = new int [cellnum+1]; 
  int* b=NULL;b = new int [cellnum+1];
  b[0]=total;
  int j=0;

  for(j = 0;j < cellnum;j++)
  {
     a[j]=(int)fmod((double)b[j] ,(double) 2);
     b[j+1]=b[j] / 2; 
   }
}
void binary::print() const
{
  //printf("%d ",total);
  int g=0;
  for(g = 0;g <this-> cell;g++)printf("%d",this->a[cell-g-1]);
  printf("\n");
}
#endif
