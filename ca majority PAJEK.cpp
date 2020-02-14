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
 int time = 40;
 int hub = 0;
 int nstate = (int) pow(2.0,(double)cell);
 int* w = NULL; w = new int [cell];
 int* in = NULL; in = new int [nstate];
 int* out = NULL; out = new int [nstate];
  
  in[0]= 0;
  out[0]=0;
 int j = 0 , i = 0, h = 0,q = 0, k = 0, numberr = 0;

 discrete site(cell,time);
 FILE *fp;
 fp = fopen("majority.net","w");
 fprintf(fp,"*Vertices  %d \n",nstate);
 int g=0;
 double coor = 0.0;

 for(g = 1;g < (nstate+1); g++)
  {
   fprintf(fp,"%d  *m0%d*    %e    %e    0.5000 \n",g,g,coor,coor);
  // coor = coor + 0.035714285* g;
  }
 fprintf(fp,"*Arcs \n");
 int sum =0, summ =0;
 for(i = 0;i < nstate;i++)
 {
  for(j = 0; j < cell; j++)w[cell-j-1]=site.get(i,j);
  camajority ca(time,cell,w); 
  ca.caevaluate();
  ca.cadiscrete();
   
  for( q=0; q < time;q++)
  {
       sum = ca.get2(q) ; 
       sum = sum +1;
       if(q>0)
        {
            for (h= 0;h<q;h++)
              {
                if(sum == out[h] && summ == in[h]) goto next; 
                }
           fprintf(fp,"   %d",summ );
           fprintf(fp,"   %d",sum );
           fprintf(fp,"   1\n");
           } 
       in[q] = summ;
       out[q] = sum;
       summ = sum;
       sum = 0; 
   }
    next: 
	 sum = 0;    
     cout << "situation = " << i  <<" " <<endl; 
     
} 
  
 fclose(fp);  
 delete [] w;

 system("PAUSE");
 return 0;
}
