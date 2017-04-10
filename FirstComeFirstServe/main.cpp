
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>


using namespace std;
const int num = 5;

struct Process 
{
    string name;
    int arrival_time;
    int burst_time;
   
};

void file_open(ifstream& input);

void create_process_user(Process process[], int num);

void create_process_file(ifstream& input, Process process[]);

void process_simulation (Process process[], int num);


int main() {
    
    ifstream input_f;
    srand(time(NULL));
    int process_num = 0;
    
    cout << "Process Simulation from User Input" << endl;
    
    //ask user for how many process
    cout << "Please Enter How Many Process You Would Like to Have: " << endl;
    cin >> process_num;
    
    //creates an array of struct that will now hold the data of each process
    Process *process_2 = new Process[process_num];
    
    //create each process assigning it with different arrival times and burst time
    create_process_user(process_2, process_num);

    //caluculates the waittime and turnaround time of the process execution
    //and prints out results
    process_simulation(process_2, process_num);
    
    cout << endl << "Process Simulation from Input File" << endl << endl;
   
    //opens file
    file_open(input_f);
        
    //creates an array of struct that will now hold the data of each process 
    //from file input
    Process *process_1 = new Process[num];
    
    //reads data from file and will update process_1 array with data
    create_process_file(input_f, process_1);
    
    //close file
    input_f.close();
    
    //caluculates the wait-time and turnaround time of the process execution
    //and prints out results
    process_simulation(process_1, num);
   
    return 0;
}

void file_open(ifstream& input){
    
    input.open("process.txt");
    
    if(input.fail()) {
        cout << "Input File Did not Load " << endl;
        exit(1);
    }  
}

void create_process_user(Process process[], int num){
    for(int x = 0; x < num; x++) {
        process[x].arrival_time = x;
        process[x].burst_time =  rand() % 15 + 1;
    }
}

void create_process_file(ifstream& input, Process process[]){
    
    Process *p = new Process[num];
    int min = 0, temp = 0;
    
    //gets input from file
    for(int x = 0; x < num; x++) {
        
        input >> process[x].name;
        input >> process[x].arrival_time;
        input >> process[x].burst_time;   
        
    }
    
    //simple bubblesort to order process based on arrival time.
    for(int y = 1; y < num; y++) {
        
        for(int z = 0; z < num - 1; z++){
            
            if(process[z].arrival_time > process[z+1].arrival_time) {
                p[0] = process[z];
                process[z] = process [z+1];
                process[z+1] = p[0];
               
            }
        }
    }
      
}

void process_simulation (Process process[], int num) {
    
    int wait_time = 0, turn_around = 0;
    
    //calculates and prints results
     for (int y = 0; y < num; y++) {
        
        cout << "Process " << y+1 << ": ";
        
        turn_around = (turn_around + process[y].burst_time);
        
        cout << "Arrival Time: " << process[y].arrival_time << " | " 
             << "Burst Time: " << process[y].burst_time << " | " 
             << "Wait Time: " << wait_time << "s | " 
             << "Turnaround Time: " << (turn_around - process[y].arrival_time) 
             << "s " << endl << endl;
        
        wait_time = wait_time + process[y].burst_time;
        
    }
}