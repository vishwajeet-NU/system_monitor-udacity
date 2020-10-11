#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    
    
    return cpu_usage_ ; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return Ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

bool Process::operator<(Process const& a) const { 
    
    // return(stol(Ram_) > stol(a.Ram_)); 
    return(cpu_usage_ > a.cpu_usage_); 
    
    }

void Process::Pid_setter(int id){
    pid_ = id;

}
void Process::User_setter(string name){
    user_ = name;
}

void Process::Ram_setter(std::string ram ){
    long fltram; 

    if(ram.size()>0) fltram = stol(ram)/1023;
    else fltram = 0;
        
    Ram_ = to_string(fltram);

}

void Process::Up_time_setter(long time){

    uptime_ = time;
}

void Process::Command_setter(std::string command){
    command_ = command;
}

void Process::Cpu_setter(float cpu_usage){
    cpu_usage_ = cpu_usage;
}


