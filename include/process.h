#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

  void Pid_setter(int id);
  void User_setter(std::string name);
  void Ram_setter(std::string ram);
  void Up_time_setter(long time);
  void Command_setter(std::string command);
  void Cpu_setter(float cpu_usage);

 private:
    int pid_{0};
    std::string user_{};
    std::string command_{};
    std::string Ram_{};
    
    float cpu_usage_{0.0};

    long int uptime_{0};
};

#endif