//�ɶ��û��O�}�C�[�@! 
//�Ψӧ����˴��C�ӳW�h���g�� 
//2^25=>167761     =># of single 1
#include <iomanip>
#include <cstdlib>
#include <vector> 
#include <iostream>
#include <cmath> 
#include "binary.h"
//#include <stdio.h>
//#include "ca.h"
using namespace std;

class carule 
{        
    int asign[8] ; //�B��W�h�}�C 
    int cellnumber ;// number of cells(L) 
    int rulenumber ;// �o�̫��w�O�Ψ���rule 
    int timestep ;//number of time steps
    int *s;//�H�@���x�s�Ҧ���� 
    int *state2; 
 
  
    public: 
    //constructors:
    carule (){;}; 
    carule (int ,int ,int ,int ) ;//�D�ʵ���ini 
    ~carule() { delete [] this->s;    // destructor
                delete [] this->state2; 
                this->cellnumber = this->timestep = this->rulenumber = 0;
                    }
    
    //member function 
    inline int CV(const int i,const int j) const {return(cellnumber*i + j);}
    inline void rule(int rulee) { this->rulenumber = rulee;} 
    inline void nstep(int cell) { this->cellnumber = cell;}
           void sites(int ) ;  //3008.3.27 adding in!!
    inline void times(int timenumber) { this->timestep = timenumber;} 
    void ruletransf() ; //�ഫ�ܤG�i�� 
    inline int get(const int i, const int j) const  //�o��Y�Ӯɶ����}�C�� 
                        { return this->s[CV(i,j)]; }                   
    inline int get2(const int timee ) const
                        { return this->state2[timee] ;} 
    inline void set(const int i, const int j, int xx) // ��J�Y�Ӯɶ����}�C�� 
                     { this->s[CV(i,j)] = xx; }
    //void caevaluate(); //�p�⪬�A�H�ɶ����t�i 
    //void cadiscrete2(); //�ϥΥt�~�@�ؤ�k 
    
      } ;
carule::carule(int rule,int time,int cell,int state) 
{
  this->rulenumber = rule;
  this->timestep   = time;
  this->cellnumber = cell;
  
  ruletransf();
  this->s = new int [time*cell+cell] ;
  this-> state2 = new int  [this->timestep+2] ;
  int* a = NULL; a = new int [cellnumber+3];
  int* b = NULL; b = new int [cellnumber+3];

  int n=0;    
  a[0]=0; b[0]=state;
  int i = 0, k =0, m = 0 ;
   
   for (i = 1; i < (cellnumber+1);i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2; 
   }
  
   for(m=0;m<cellnumber;m++)
   {
     
     if(a[m+1]>0.0) s[CV(0,m)]=1;
       else  s[CV(0,m)]=0;
     }      
delete  a;
delete  b; 
} 

void carule::sites(int state) 
{
  int* a = NULL; a = new int [cellnumber+3];
  int* b = NULL; b = new int [cellnumber+3];
  a[0]=0; b[0]=state;
  int i = 0, m = 0 ;
   
  for (i = 1; i < (cellnumber+1);i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2; 
   }
  
  for(m=0;m<cellnumber;m++)
   {     
     if(a[m+1]>0.0) s[CV(0,m)]=1;
       else  s[CV(0,m)]=0;
     }          
  int t = 0, j = 0;
  int tim =  this->timestep, n = this->cellnumber; 
  int sum = 0;
  
  for(t=0;t< tim;t++)
  {
    for ( j=0;j<n;j++)
    {
        sum = 1*s[CV(t,(j+1)%n)] + 2* s[CV(t,j)] + 4*s[CV(t,((j-1)+n)%n)];
        s[CV(t+1,j)]= this->asign[7-sum] ;  //new method    
        sum = 0;          
     }
  } 
delete  a;
delete  b;  
 int k=0 ,cell =0;
 int total = 0; 
 for(k = 0;k < this->timestep ;k++) 
 {
    for(cell = 0;cell < this -> cellnumber; cell++)
    {
           total =  total +  (int) pow(2.0,(double) cellnumber-cell-1) * get(k,cell);
       } 
     this->state2[k]= total; 
     total = 0; 
 }        
} 

void carule::ruletransf() //rulenumber�ഫ���G�i��A�w�ק�^^ 
{ 
   int a[9];
   int b[9]; 
   a[0] = 0;b[0] = this->rulenumber;
   int i = 0, j = 0, k =0;
   
   for (i = 1; i < 9;i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2;       
   }
   for (j = 0;j < 8;j++) this->asign[7-j] = a[j+1];
   
} 
int GG(int num1,int num2) 
{
  return (num1*2 + num2 ) ; 
    }
main()
{ 
  int rule = 18;
  int time = 5;
  int cell = 15;
  int indegree_type = 1;
  int indegree_test = 0;
  int alarm = 1;
  
 // ULI totall = (int)pow(2.0,25.0);//guess the # of lines
  int node = (int) pow(2.0,cell) ; 
  vector< vector<int> > arrayca(node, vector<int>(0));  
  FILE *lp;
  lp=fopen("result_rule18_cell12_time5 all.txt","w") ;     
  
  int in= 0;
  int out=0;  
  int i=0,t = 0,h = 0,q = 0,state = 0;
  int sum =0, summ =0;//summ�O�i�h �Asum�O�X�� (��ӹF�쪺���A) 
  carule ca(rule,time,cell,i);
  
//*************************step1:CA evaluation
  do
   {         
     ca.sites(i);
     for(q=0 ; q<time ;q++)
     { 
       sum = ca.get2(q) ;       	   
       if(q>0)
        {// || sum ==0 
           if(sum == out && summ == in)
           {   //if(q == 1)arrayca[summ].clear();    
              goto next;
                  }           
           arrayca[sum].push_back(1);
           state = arrayca[sum].size()-1;           
           arrayca[sum][state]=summ;  
        } 
       in = summ;
       out = sum;
       summ = sum;
       sum = 0;
     }
     
     next: 
	 sum = 0;    
    cout << "situation = " << i  <<" " <<endl; // use to check the process    
     i++;      
  }  while(i<node);
 ca.~carule();

//****************step2:network calculate
//****************REMAIN THE PREVIOUS METHOD
  vector<int> indegree(2);
  indegree[GG(0,0)]=0;indegree[GG(0,1)]=0;
  vector< vector<int> > indegree_note(13000000, vector<int>(0));  
  int stable = 0,move = 0,p=0,k=0,j=0; 
  i = 0;
  
 do
  {    
    printf("i=%d ",i) ; //�ʱ��i�檺�B�J 
    sum = 0;
    //2.�S���u�i�ӡA�N���򳣤��ΰ��F�C�`�٭p��B�J����k 
    if(arrayca[i].size()==0)      
       {
           sum = 0;
           goto stop;
       }    
    //3.���h���ƽu�q 
    stable = 1;
    do     
    {
     do{ 
         if(arrayca[i][move]== arrayca[i][stable])
          {                    
            arrayca[i][move]=0;
          }
         move ++;        
       }while(move < stable) ; 
       move = 0;
       stable++;
    }while(stable < arrayca[i].size());
    
    //3. Statics
    do
    {
     if (arrayca[i][k]>0)   
        { sum++;}
     k++; 
    }while(k<arrayca[i].size()) ; 
    stop:
         
    //4. adding in-degree or adding new kind of in-degree
    do{
        if(sum == indegree[GG(indegree_test,0)]) 
            {
                  indegree[GG(indegree_test,1)]++;
                  alarm =0;
                  break;
            }
         indegree_test++;    
    }while(indegree_test<indegree_type);
    if(alarm >0)
          {              
              indegree.push_back(1); 
              indegree.push_back(1);              
              indegree[indegree.size()-2] = sum;
              indegree[indegree.size()-1] = 1;
              indegree_type++;
          }
    indegree_test = 0;
    
    //5. Note the anscetors
    indegree_note[sum].push_back(1);
    state = indegree_note[sum].size()-1;
    indegree_note[sum][state]=i;
    
    alarm = 1;
    sum =k=j=p=0; 
    arrayca[i].clear();
    i++;
   }while(i<node);
    arrayca.clear();






  // PART 3: accummulate the number of isolated "1"
  i=j=k=sum=p=0; //generate new parameter  
  int *show_lattice = NULL ; show_lattice = new int [cell]; // show the particular state
  int isolate_type = 1; 
  int isolate_test = 0;
  
  for(i = 1;i < indegree_type;i++)
  {
   vector<int> isolate_n(2);  // re-announce the data which record the # of isolate "1" 
   isolate_n[0] = 0;
   isolate_n[1] = 0;
   fprintf(lp,"indegree %d   # %d\n",indegree[GG(i,0)],indegree[GG(i,1)]);  // indegree and # of state with particular indegree
   
   for(j = 0;j <indegree_note[indegree[GG(i,0)]].size(); j++)
   {
    sum = 0;       // means the # of isolate "1"
    alarm = 1;     //alarm the different kind of the indegree
    binary bibi(indegree_note[indegree[GG(i,0)]][j],cell);
    for( p=0 ; p<cell ; p++)show_lattice[p] = bibi.get(cell-p-1);
    for( k=0 ; k<cell ; k++)
     { if(show_lattice[k]==1)sum++;}
     
    do{
        if(sum == isolate_n[GG(isolate_test,0)]) 
            { isolate_n[GG(isolate_test,1)]++;
              alarm =0;
              break;     }
         isolate_test++; }while(isolate_test<isolate_type);
    
    if(alarm >0)
        {   isolate_n.push_back(1); 
            isolate_n.push_back(1);              
            isolate_n[isolate_n.size()-2] = sum;
            isolate_n[isolate_n.size()-1] = 1;
            isolate_type++;        }
    alarm = 1;
    isolate_test = 0;
    k = 0;            }
    
    for(k = 0; k <isolate_type; k++ )fprintf(lp,"n = %d with %d state \n",isolate_n[GG(k,0)],isolate_n[GG(k,1)]);   
    isolate_n.clear(); 
    isolate_type = 1;
}     
  fclose(lp);
  indegree.clear();
  system("PAUSE");
  return 0; 

} 
