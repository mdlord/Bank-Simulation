#include <iostream>
#include <random>
#include <fstream>                                                                                                  //header files
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
  int expnumber = 2000; 
  int numberofCustomers = 20;   

  int p_mean;
  int copyarr[20];

  cout<<"\n --------> POISSON FILE GENERATOR <--------";
  cout<<"\n\nEnter mean for the distribution: ";
  cin>>p_mean;                                                                                                      //input the mean


  cout<<"\n\nThe curve of poisson arrival looks like this";

  
  default_random_engine generator;    
  poisson_distribution<int> distribution(p_mean);                                                                   //source: cplusplus.com

  int p[10]={};     

  for (int i=0; i<expnumber; ++i) {
    int number = distribution(generator);
    if (number<10) ++p[number];                                                                                     //the value generator
  }

  std::cout << "poisson_distribution:";
  
  for (int i=0; i<10; ++i)
  {
    cout<<"\n"<< p[i]*numberofCustomers/expnumber <<string(p[i]*numberofCustomers/expnumber,'*');
    copyarr[i] = p[i]*numberofCustomers/expnumber;
  }
  int z= 1;
  ofstream poissonfile("poissonarrival.txt");
  
  if(poissonfile.is_open())                                                                                         //making the file using the values generated
  {
    for (int i=0; i<10; i++)
    {
     for(int j=0; j<copyarr[i]; j++)
      {
       poissonfile<< z <<"\n";
      }
    z++;
    }
  }

  ofstream expfile("expprocess.txt");
  
  int e=0;                                                                                                          //making a file for exponential process times
  //expfile<< 0 <"\n";
  if(expfile.is_open())
  {
    for (int i=0; i<14; i++)
    {
        e=exp(i);
       expfile <<e <<"\n";
       //expfile<<"\n" <<e;
    }
  }

cout<<"\n FILES CREATED-";
cout<<"Now run the poisson.cpp file\n\n";
  return 0;
}