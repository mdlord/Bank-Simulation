#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;
																											//declaring a class
class Customer
{
public:
	int arrivaltime;
	int processtime;
	int waittime;

	string type;

	Customer()
	{
	 arrivaltime=0;
	 processtime=0;
	 waittime=0;
	 type = "";
	}
	Customer(int arrival,int process){
		arrivaltime=arrival;
		processtime=process;
	}
	int getProcessTime(){
		return processtime; 
	}
	int getArrivalTime(){
		return arrivaltime;
	}

};
																											//declaring a class
class teller
{
public:
	bool free;
	int processtime;
};

//driver function
int main(int argc, char** argv)
{
	int a, p;
	ifstream  arrival, process;
	int numberofCustomers = 0;
	int numberofprocess = 0;
	queue<Customer> bank;
	string temp1, temp2;

	ifstream processi("process.txt");																		//reading through file for number of customers
	while(getline(processi,temp1)){
		numberofprocess++;
	}
	
	processi.close();	

	ifstream arrivali("arrival.txt");
	while(getline(arrivali,temp2)){
		numberofCustomers++;
	}

	arrivali.close();

	if(numberofprocess == numberofCustomers)																// checking the number of inputs from the file
	{
		arrival.open("arrival.txt");
		process.open("process.txt");
	
		arrival.clear();
		process.clear();
		Customer Customer_array[numberofCustomers];

		while(!arrival.eof() && !process.eof())																//reading values
		{			
			arrival>>a;
			process>>p;

			Customer c=Customer(a,p);																		// store the customer details						
			Customer_array[numberofCustomers].processtime = c.processtime;
			bank.push(c); 																					//pushing the details of the customer to the queue
		}

		int numteller;	
		cout<< "\nInput the number of tellers: ";
		cin >> numteller;	
		cout<< "The number of customers are " <<numberofCustomers<< '\n';

		teller teller_array[numteller];
	
		for(int i=0; i<numteller; i++){																									//assign each teller to available
			teller_array[i].free=true;																		//assign initial value to 0
			teller_array[i].processtime=0;
			cout<<"Teller "<<i+1 <<" is available" << '\n';	
		}
		Customer t = bank.front();
		int c_time = t.getArrivalTime();	
		int current_time = c_time - 1;
		int wait_time = 0;
		float wait_timesum = 0;
		float sum_process=0;

		int x=0;
		int p_time=0;
	
		std::vector<int> w;
		while(numberofCustomers!=0)
		{
			current_time++;
			for(int i=0; i< numteller; i++)
			{
				//current_time++;
				if(teller_array[i].free==true)																// customer goes from the bank queue to the teller
				{																							//if the teller is free. Otherwise, the customer waits
					Customer c =  bank.front();																//in the queue and is called when teller gets free.
					p_time = c.getProcessTime();					
				
					if(current_time < c.getArrivalTime())
						current_time++;
					
					wait_time = current_time - c.getArrivalTime();
					bank.pop();																				// Customer goes from queue to teller

					sum_process = sum_process+p_time;
										
					w.push_back(wait_time);																	//wait time for each customer being pushed into a vector

					if(wait_time<0)
						wait_time = 0;

					cout<<"\n\n"<<x+1 <<" Customer goes to teller "<<i+1;
					cout<<"\nWait Time: "<< wait_time;

					teller_array[i].free = false;
					teller_array[i].processtime = p_time;
				
					cout<<" |  Processtime: "<< teller_array[i].processtime;

					numberofCustomers--;
					
					cout<<"\n\nNumber of Customers pending:" <<numberofCustomers;
					x++;
					if(numberofCustomers==0)																// if the number of customers pending reaches to 0
					{																						//the lop breaks/
						break;
					}

				}
			//current_time++;
			}
			for(int j=0; j<numteller; j++)																	// With everry iteration the value of each
			{																								//tellers preocess time decreases.																							//As it reaches 0, the teller becomes available again	
				if(teller_array[j].free == false && teller_array[j].processtime != 0){
					teller_array[j].processtime--;
					cout<<"\nTime remaining for teller" <<j+1 <<": " <<teller_array[j].processtime;
				}
				if( teller_array[j].processtime == 0){
					teller_array[j].free = true;
					cout<<"\nteller " << j+1 <<" is now free";
				}
			}
		}
		float avg_waittime;
		for (int k = 0; k < w.size(); k++){																	//adding all the waittimes.
			wait_timesum = wait_timesum + w[k];	
			}
		if(wait_timesum<0)
			wait_timesum = 0;

		float average_wait = wait_timesum/w.size();
		float variance = 0;
		
		for(int h = 0; h < w.size(); h++){																	//Calculating Average Wait Time for all Customers
			variance = variance + pow((w[h] - average_wait),2);												//and the variance of the data.
			}	
		float sigma = pow(variance/w.size(),0.5);

		if(avg_waittime == 0)
			sigma = 0; 
	
		cout<<"\n\n=============================SIMULATION SUMMARY===========================";				//Data set Summary OUTPUT
		cout<<"\n\n->Run Time: "<< current_time;
		cout<<"\n->Average Process Time: " <<sum_process/w.size();
		cout<<"\n->Average wait time for each Customer: "<<average_wait;
		cout<<"\n->Standard Deviation(Wait Time): "<< sigma ;
		cout<<"\n\n--------------------------------------------------------------------------\n\n";
	}
	else 
		cout<<"\n\nNumber of Customer does not match Process times--CHECK AGAIN";							//the case where the number of inputs in each file dont match
return 0;
}
