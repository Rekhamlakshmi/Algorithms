#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int c=0;

void Exchange(int *x,int *y)
{

    int temp=*x;
    *x=*y;
    *y=temp;
}

void init(int N,int *A,int *B)
{
    A[0]=0;
    int i;
    for(i=1;i<=N;i++)
    {
        A[i]=B[i-1];
    }

}
void calculate_rank(int *QR,int N,int K)
{
    QR[0]=0;
    int i;
    double k=K,n=N;
    for(i=1;i<=K;i++)
    {
        double v=ceil((i*n)/k);
        QR[i]=v;
    }
}

int Partition(int *A,int p,int r,int ind)
{
    int index=ind;
    int x=A[index];
    Exchange(&A[r],&A[index]);
    int i=p-1;
    int j;
    for(j=p;j<r;j++)
    {
        if(A[j]<=x)
        {
            i=i+1;
            Exchange(&A[i],&A[j]);
        }
    }
    Exchange(&A[i+1],&A[r]);
    return i+1;

}

void Print_Output(int *Q,int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        cout<<"\t"<<Q[i];
    }
    cout<<"\n";
}


int Select(int *A,int p,int r,int k)
{
    int q;
    if(p==r)
        return p;
    else
    {
        q=Partition(A,p,r,r);
        if(q==k)
        {

            return q;
        }
        else if(q>k)
            return Select(A,p,q-1,k);
        else
            return Select(A,q+1,r,k);
    }
}

void calculate_quantile(int *A,int p,int r,int *QR,int p11,int r11,int *Q)
{
   int q,f,val,k1;
   double p1=p11;
   double r1=r11;
//if(p11!=0 && r11<K && r11!=0)
//{
   double value=floor((p1+r1)/2);
   val=(int)value;
   k1=QR[val];
   f=Select(A,p,r,k1);
   q=Partition(A,p,r,f);
   Q[c]=A[f];
   c=c+1;
   if(p11<val)
        calculate_quantile(A,p,q-1,QR,p11,val-1,Q);
  if(val<r11)
        calculate_quantile(A,q+1,r,QR,val+1,r11,Q);
//}
}
void read_input(int N,int *B)
{
    int i;
    for(i=0;i<N;i++)
    {
        cin>>B[i];
    }
}

void Deallocate(int *A,int *B,int *QR,int *Q)
{
    delete []A;
    delete []B;
    delete []QR;
    delete []Q;

}
int main()
{
     int N,K;
     int *A;
     int *B;
     int *QR;
     int *Q;
    cout<<"\n K-th Quantile Problem:";
    cout<<"\n\n Enter the input\n";
    do
    {
    cout<<"\n";
    cin>>N>>K;
    c=0;
    if(N==0 || K==0)
        exit(0);
    B=new int[N];
    A=new int[N+1];
    QR=new int[K];
    Q=new int[K-1];
    read_input(N,B);
    cout<<"\n The quantiles are ";
    init(N,A,B);
    calculate_rank(QR,N,K);
    calculate_quantile(A,1,N,QR,1,K-1,Q);
    Print_Output(Q,K-1);
    Deallocate(A,B,QR,Q);
    }while(N!=0 || K!=0);
    return 0;
}
