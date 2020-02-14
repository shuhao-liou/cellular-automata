//test camajority
#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <cmath> 
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "camajority.h"
#include "binary.h"
using namespace std;
class discrete
{
      int time;
      int cell;
      int *j; 
      
   public:
   //constructor
   discrete(){;} 
         
   discrete(int ,int );
   
   //member function
   inline int CC(const int i,const int r) const {return(cell*i + r);}
   inline int get(const int i, const int m) const  //得到某個時間的陣列值 
                        { return this->j[CC(i,m)]; }    
      };
discrete::discrete(int celll,int timee) 
{ 
  unsigned long int state = (int) pow(2.0,(double)celll);  
  this->cell = celll;
  this->time = timee;
  int* a = NULL; a = new int [celll+celll];
  int* b = NULL; b = new int [celll+celll];
  this->j = new int [state * celll+celll+1] ; 
         
  int n=0;
  do
  {    
   a[0]=0; b[0]=n;
   int i = 0, k =0, m = 0 ;
   
   for (i = 1; i < (celll+1);i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2; 
   }
  
   for(m=0;m<celll;m++)
   {     
     if(a[m+1]>0.0) j[CC(n,m)]=1;
       else  j[CC(n,m)]=0;
     }
   n++;
   }while (n<state);   

} 
main()
{
 int cell = 10;
 int time = 50;
 int hub = 0;
 int* w = NULL; w = new int [cell];
 int* step= NULL; step = new int [time];
 int* preimage = NULL ;preimage = new int [3000000];
 int j = 0 , i = 0, q = 0, k = 0, numberr = 0;
 
 int nstate = (int) pow(2.0,(double)cell);
 discrete site(cell,time);

 for(i = 0;i < nstate;i++)
 {
  for(j = 0; j < cell; j++)w[cell-j-1]=site.get(i,j);
  camajority ca(time,cell,w); 

  ca.caevaluate();
  ca.cadiscrete();
   
  for( q=0; q < time;q++)  step[q] =ca.get2(q) ;
       
   k = 0;
   do
     {
       if(step[k] == hub) 
       {
         if(k==0)preimage[numberr] = step[0];
         if(k>0)preimage[numberr] = step [k-1];
      //   cout << "preimage = " << preimage[numberr] << endl;    
         numberr ++;
         goto next;
        }
       k++;
     }while(k < time);
   
   next:       
   cout << "situation = " << i  <<" " <<endl;     
    
} 
  
    int stable = 1;
    int move = 0;
    for(stable = 1;stable < numberr; stable++) //消去重複線段 
    { 
     do{ 
         if( preimage[move] == preimage[stable]) 
          {
        //    cout << "move = "<< preimage[move] << "  stable = " << preimage[stable] << endl;
            preimage[move] =-1;//表示沒有了這段線條 
          }                     
         move ++;        
       }while(move < stable) ; 
      move = 0; 
    } 
   FILE *fp;
   fp = fopen("rule232 kamx.txt","w");
   int g = 0 ,totalpreimage = 0 ;
   do
    {
     if (preimage[g]>=0)   // 有這段線條的才要計算 
        { totalpreimage++;                       
          fprintf(fp," %d   ",preimage[g]);    
          binary bibi(preimage[g],cell);
          for(int q=0 ; q<cell ; q++)fprintf(fp,"%d",bibi.get(cell-q-1)); 
          fprintf(fp,"\n");
        }
     g++; 
    }while(g<numberr) ;  
  cout << "kmax = " << totalpreimage  <<" " <<endl;   
  
 
 fprintf(fp,"rule 232 cell 10 kmax= %d ",totalpreimage);
 fclose(fp);
  
 delete [] preimage;
 delete [] w;
 delete [] step;
 system("PAUSE");
 return 0;
}

