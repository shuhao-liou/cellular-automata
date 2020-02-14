//1D Cellular Automata discrete state������HEADFILE
//k=1,r=2  �@�@�����ӲӭM�|�v�T�U�@�Ӯɶ������A 
//���ɮץi�H�Ψӭp��CA���U�C�S��
//1.����Rule number����i�H�����������G�i��A�H��CA ������
//2.�i�H�üƵ��w���A�A�Ψ̾ڥD�{�����q��l���A
//3.�p��CA�b�g�L�@�w�ɶ����᪺�̲ת��A
//4.�i�H�Ψ��˵�discrete state network�H�ɶ����t�i(evolution) 
//**���{���@�߫��Ӷ���[rule][timestep][n_step] [initial state] �ƦC 
//**�N�G���}�C���@�@���B�z ->�ǫh 
#ifndef _nt92_class_camajority_
#define _nt92_class_camajority_
#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <cmath> 
#include <time.h>
#include <conio.h>
#include <stdio.h>
using namespace std; 
class camajority
{        
    int asign[32] ; //�B��W�h�}�C 
    int cellnumber ;// number of cells(L) 
   // int rulenumber ;// �o�̫��w�O�Ψ���rule 
    int timestep ;//number of time steps
    int *s;//�H�@���x�s�Ҧ���� 
    int *state2; 
 
  
    public: 
    //constructors:
    camajority (){;}; 
  //  carule (int ,int ) ;//ini�ѶüƵ��w
    camajority (int ,int ,int * ) ;//�D�ʵ���ini 
    ~camajority() { delete [] this->s;    // destructor
                      this->cellnumber = this->timestep = 0;
                    }
    
    //member function 
    void print() const;//�X�{�򥻰ѼƥH�Ϊ�l���A 
    void print(int ) const;//�X�{�Y�Ӯɶ������A
    inline int CV(const int i,const int j) const {return(cellnumber*i + j);}
   // void majoritytransf() ; //
    inline int get(const int i, const int j) const  //�o��Y�Ӯɶ����}�C�� 
                        { return this->s[CV(i,j)]; }                   
    inline int get2(const int timee ) const
                        { return this->state2[timee] ;} 
    inline void set(const int i, const int j, int xx) // ��J�Y�Ӯɶ����}�C�� 
                     { this->s[CV(i,j)] = xx; }
    void caevaluate(); //�p�⪬�A�H�ɶ����t�i 
    void cadiscrete(); //�ϥΥt�~�@�ؤ�k 
    
      };

camajority::camajority(int time,int cell,int *d) 
{
  this-> timestep= time;
  this->cellnumber = cell;
  
  this->s = new int [time*cell+time] ;
  int j;
  for(j = 0;j < cell;j ++)  s[CV(0,j)] = d[j]; 
  
 
   int k =0;
   for(k=0; k < 13;k++)this-> asign[k] =0;
   asign[7] =1; asign[11] = 1;
   k = 0;
   for(k = 13; k < 32;k++) asign[k] =1; 
   asign[24] = 0; asign[20] =0; asign[18] =0; asign[17] =0;asign[16] =0; 
} 
 
void camajority::caevaluate()//�̾ڳW�h�إߪ��A�H�ɶ����t�� 
{
  int t = 0, j = 0 , k = 0;
  int tim =  this->timestep, n = this->cellnumber; 
  int sum = 0;
  
  for(t=0;t< tim;t++)
  {
    for ( j=0;j<n;j++)
    {
        sum = 1*s[CV(t,(j+2+n)%n)] + 2* s[CV(t,(j+1+n)%n)] + 4* s[CV(t,(j+n)%n)]+8* s[CV(t,(j-1+n)%n)]+16*s[CV(t,((j-2)+n)%n)];
        s[CV(t+1,j)] =this->asign [sum] ;
        sum = 0;          
    }
  } 
}                

void camajority::cadiscrete()
{
 //int sum= (int)  pow(2.0,(double) this-> cellnumber) ; 
 this-> state2 = new int  [this->timestep+2] ;
 
 int m=0 ,cell =0;
 int total = 0; 
 for(m = 0;m < this->timestep ;m++) 
 {
    for(cell = 0;cell < this -> cellnumber; cell++)
    {
           total =  total +  (int) pow(2.0,(double) cellnumber-cell-1) * get(m,cell);
       } 
     this->state2[m]= total; 
     total = 0; 
    // cout << "t=" << m << "  " <<this->state2[m] <<endl; 
 }                   
  
} 
void camajority::print()  const //��X�򥻸�� 
{
 
// cout << "rulenumber = " << this->rulenumber << endl;
 cout << "n_step = " << this->cellnumber << endl; 
 cout << "time = " << this->timestep << endl;
 
 int i,j;
  cout << "initial state = " ;
  for(i = 0;i < this->cellnumber;i ++)   cout << " " <<this->s[CV(0,i)] ;
  cout << endl;
  for(j = 0;j < 32;j ++)   cout << "RULE " << pow(2.0,32-j)<< " = "<< this->asign[32-j-1] << endl;
  cout << "*******************************" << endl;
 
} 

void camajority::print(int times) const 
{  
     int m=0 ,k,total = 0;
     k = this->cellnumber;
      for(int cell = 0;cell < k; cell++)
    {
           total =  total +  (int) pow(2.0,(double) k-cell-1) * this->s[CV(times,cell)];
       } 
     cout << "t(" << times  << ") =   "; 
     for(m = 0;m < k;m ++)  cout <<  this->s[CV(times,m)]  ; 
     cout << "      ";
     cout << total;
            
     cout << endl;    
} 
#endif
