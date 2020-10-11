#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, system, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> system >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() { 
  
  float MemTotal{0.0}, MemFree{0.0};
  std::ifstream file(kProcDirectory + kMeminfoFilename);
  string line,key,value;
  while(file){
      std::getline(file,line);
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stream(line);
      while(stream){
        stream >> key >> value;
        if(key == "MemTotal") MemTotal = stof(value); 
        if(key == "MemFree") MemFree = stof(value);
      }
      
    }
  return 1.0 - (MemFree/(MemTotal)); }

long LinuxParser::UpTime() { 

  long time{0};
  string line,uptime,idle;
  std::ifstream file(kProcDirectory+kUptimeFilename);
  std::getline(file,line);  
  std::istringstream stream(line);
  stream >> uptime >> idle;
  time = stol(uptime) ;
  return time; 

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }



vector<string> LinuxParser::CpuUtilization() { 

  std::ifstream file(kProcDirectory + kStatFilename);
  std::string line,name,next;

  vector<string> out;

  while(file){
    std::getline(file,line);
    std::istringstream linestream(line);
    linestream >> name;
    if(name == "cpu")
    {
      while(linestream >> next){
        out.push_back(next);

      }
    }
    }

  return out; }


int LinuxParser::TotalProcesses() { 
  
  int total_processes{0};
  string line,key,value;
  std::ifstream file(kProcDirectory+kStatFilename);
  while(file){
      std::getline(file,line);  
      std::istringstream stream(line);
      while(stream)
      {
        stream >> key >> value;
        if(key == "processes") total_processes = stoi(value);
      }
  }

  return total_processes; }


int LinuxParser::RunningProcesses() {

  int running_processes{0};
  string line,key,value;
  std::ifstream file(kProcDirectory+kStatFilename);
  while(file){
      std::getline(file,line);  
      std::istringstream stream(line);
      while(stream)
      {
        stream >> key >> value;
        if(key == "procs_running") running_processes = stoi(value);
      }
  }
    return running_processes;
 }



string LinuxParser::Command(int pid) { 
  
   std::ifstream file(kProcDirectory+ to_string(pid)+ kCmdlineFilename);
   string command{};
   while(file.is_open()){

     file >> command;
     file.close();
   }
    return command; 
   }


string LinuxParser::Ram(int pid ) {

    string ram{},line,key,value;
    std::ifstream file(kProcDirectory+to_string(pid)+kStatusFilename);
    while(file){
        std::getline(file,line);
        std::istringstream stream(line);
        stream >> key >> value;
        if(key == "VmSize:") ram = value;
    }
  
   return ram; }


string LinuxParser::Uid(int pid) { 

    string uid, line,key,value;
    std::ifstream file(kProcDirectory+to_string(pid)+kStatusFilename);
    while(file){
        std::getline(file,line);
        std::istringstream stream(line);
        stream >> key >> value;
        if(key == "Uid:") uid = value;
    }
  
  return uid; }


string LinuxParser::User(int pid) { 

    string uid = Uid(pid);
    string user{}, line;
    std::ifstream file(kPasswordPath);

    int count = 0;

    while(file){
        std::getline(file,line);

        string tempuser,value;
        for(unsigned int i=0; i<line.size();i++){
          
            if(line[i]==':') count++;            
            if(count<1) tempuser.push_back(line[i]);
            if(count==2){
              i++;
              while(line[i]!=':'){
                value.push_back(line[i]);
                i++;              
              }
              count =0;
              break;
            }
          }
          if(value == uid){
            user = tempuser;
            break;
          }        
        
      }  
  return user; }


long LinuxParser::UpTime(int pid) { 
  
    long uptime{0};
    long start_time{0};
    vector<string> all_strings;
    string line,next;
    std::ifstream file(kProcDirectory+to_string(pid)+kStatFilename);
    while(file){
      std::getline(file,line);
      std::istringstream linestream(line);
      while(linestream >> next){
        all_strings.push_back(next);
      }
    }

  start_time = stol(all_strings[all_strings.size()-31]) / sysconf(_SC_CLK_TCK) ;
  long curr_time = UpTime();
  uptime = curr_time - start_time;
  return uptime; }


float LinuxParser::CpuUtilization_process(int pid){

    long utime{0}, stime{0}, cutime{0}, cstime{0};
    long start_time{0};

    vector<string> all_strings;
    string line,next;
    std::ifstream file(kProcDirectory+to_string(pid)+kStatFilename);
    while(file){
      std::getline(file,line);
      std::istringstream linestream(line);
      while(linestream >> next){
        all_strings.push_back(next);
      }
    }

  int size = all_strings.size(); 
  start_time = stol(all_strings[size-31]) / sysconf(_SC_CLK_TCK) ;
  utime = stol(all_strings[size-39]);
  stime = stol(all_strings[size-38]);
  cutime = stol(all_strings[size-37]);
  cstime = stol(all_strings[size-36]);

  float total_time = utime + stime + cutime + cstime;


  long curr_time = UpTime();
  float seconds = curr_time - start_time;

  if(seconds == 0) return 0.0;
  float cpu_usage = (total_time/sysconf(_SC_CLK_TCK)/seconds);

  return cpu_usage; }


