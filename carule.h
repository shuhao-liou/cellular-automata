//寫出一個1-D Cellular Automaton Rule的Headfile 
#ifndef _nt92_class_carule_
#define _nt92_class_carule_
#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <time.h>
#include <conio.h>
#include <stdio.h>
using namespace std; 

class rule
{ public: 
  int asign[7] ;
  int rulenumber; 
  
//  public:
    inline rule(){;} 
    inline void coef(int rulee) { this->rulenumber = rulee;} 
    int rulen ();
    
      }; 
int rule::rulen () 
{
   
    int i, b[7] ; 
    
    double  a[7] ; 
    a[0]= (double)this->rulenumber; 
    b[0] = 0; 
    
    for (i= 0 ;i < 8 ;i++) 
    {
     a[i+1] = (double)a[i] / pow(2.0,(double)(7-i)); 
     b [i+1]= (int)a[i] % (int)pow(2.0,(7-i));
     if(a[i+1] >= 1.0)   
     {this->asign[i] = 1;
      a [i+1]= b[i+1]; 
      b[i+1] = 0;}
     else if(a[i+1] < 1.0) 
     {this->asign[i]= 0; a[i+1] = a[i];} 
          } 
     int k=0;
     for (k = 0;k < 8;k++) cout <<"Number  "<< k <<"= "  << asign[k] <<endl;    
    return asign[7]; 
} 
#endif 
