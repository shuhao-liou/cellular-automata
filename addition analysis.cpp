//check:每一點的資訊都正確無誤的確認(用人工確認) 
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <cmath> 
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "binary.h"
using namespace std;
int GG(int num1,int num2) 
{
  return (num1*2 + num2 ) ; 
    }
main()
{
  FILE *lp;
  lp=fopen("rule9_cell10 hubstate analysis.txt","r"); 
  FILE *fp;
  fp=fopen("rule9_cell10 hubstate.txt","w");
  int cell = 10;
  int kmax = 1000;
  int n= 0;
  int nstate = (int)pow((double)2.0,(double)cell);
  int* note = NULL; note = new int [nstate];
  while ( !feof(lp)  )//read data 
  { 
    fscanf(lp, "%d %d " , &note[GG(n,0)], &note[GG(n,1)]);         
    n++;
    printf("n = %d \n",n);
  }
  
  int i = 0, j = 0,sum = 0,nt;
  for(j=0;j<kmax;j++)
  {
    for(i=0;i<n;i++)
     {
        if (note[GG(i,1)] == j)
        {  
           nt= note[GG(i,0)];
           binary bibi(nt,(int)cell);//addition             
           fprintf(fp,"node %d = %d  ",note[GG(i,0)],j);         
           for(int q=0 ; q<cell ; q++)fprintf(fp,"%d",bibi.get(cell-q-1));//addition          
           fprintf(fp,"\n");//addition
           sum ++;
         }
      }
   } 
   
   system("PAUSE");
   return 0;
}
