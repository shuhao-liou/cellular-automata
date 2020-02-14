//Target : to get the real counting result of the relation between n and k
//
//不想用PAJEK，所以決定寫個程式自己分析 
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
  FILE *fp;
  fp = fopen("rule4_cell10.txt","r");
  FILE *lp;
  lp=fopen("rule4_cell10 hubstate analysis.txt","w"); 
  int cell = 10;
  int n=0 , total = (int) pow(2.0,25.0) ; 
  int node = (int) pow(2.0,(double) cell) ; 
  int* note =NULL ;note = new int [total] ; 
  int i=0,j=0 ,k=0 ,sum = 0,p=0,g = 0; 
   
  while ( !feof(fp)  )//read data 
     { 
       fscanf(fp, "%d %d " , &note[GG(n,0)], &note[GG(n,1)]);         
       n++;
       printf("n = %d \n",n);//已經知道有n條線 
       }
       
  int* situ = NULL ;situ = new int [n+1] ;
  int* indegree=NULL ; indegree = new int [node];
  indegree[0]=0;situ[0] =0; 
  int stable = 0,move = 0,c=0; 
  
  for(i=0;i<node;i++) // 找到每壹點的indegree 
  {  
    printf("i=%d ",i) ; //監控進行的步驟     
    sum = 0;     
    do{         
      if( note[GG(p,1)] == i)
        {
           situ [j] = note[GG(p,0)];           //紀錄某一點indegree的數目 
           j++;           
        }       
         p++ ;       
      }while (p<n) ; //已經知道有n條線，但現在還知道第i點有j個indegree 
     
    if(j==0)  //沒有線進來，就什麼都不用做了。節省計算步驟的方法 
       {
           sum = 0;   
           situ[0]=-1;
           goto stop;
       }    
    
    for(stable = 1;stable < j;stable++) //消去重複線段 
    { 
     do{ 
         if( situ[move] == situ[stable]) 
          {
            situ[move] =-1;//表示沒有了這段線條 
          }                     
         move ++;        
       }while(move < stable) ; 
       move = 0;
    } 

    k=0;
    stop:
    do
    {
     if (situ[k]>=0)   // 有這段線條的才要計算 
        { sum++; 
        }
     k++; 
    }while(k<j) ; 
           
    if(sum > 0)
    {
     for(int g = 0 ;g< j ; g++)
      {
       if(situ[g]>0)     
       {
          fprintf(lp," %d   ",situ[g]);    
          binary bibi(situ[g],cell);
          for(int q=0 ; q<cell ; q++)fprintf(lp,"%d",bibi.get(cell-q-1)); 
          fprintf(lp,"\n");
         }
        }
        binary bibi(i,cell);//addition
        
      fprintf(lp," hubstate = %d with indegree %d  ",i,sum);
//      for(int q=0 ; q<cell ; q++)fprintf(lp,"%d",bibi.get(cell-q-1));//addition
      fprintf(lp,"\n");//addition
     }
    sum = 0;
     k=0;
    for (k=0;k<j;k++)situ[k] = -1;//最後把全部都變成零 
    j=k=p=0; //    k=0;    p=0; 
   }
  fclose(fp);
  fclose(lp);
  getch();   
  return 0; 
   
} 
