#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System()
{
    operating_system = LinuxParser::OperatingSystem();
    kernel_name = LinuxParser::Kernel();
    Processor myprocessor;
    cpu_ = myprocessor;

}
Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { 

    std::vector<Process> current_processes = {};

    vector<int> pid_all = LinuxParser::Pids();
    for(auto itr:pid_all){
        Process temp_process;
        temp_process.Pid_setter(itr);
        string ram = LinuxParser::Ram(itr);
        temp_process.Ram_setter(ram);
        long time_passed = LinuxParser::UpTime(itr);
        temp_process.Up_time_setter(time_passed);
        temp_process.Command_setter(LinuxParser::Command(itr));
        temp_process.Cpu_setter(LinuxParser::CpuUtilization_process(itr));
        temp_process.User_setter(LinuxParser::User(itr));

        current_processes.push_back(temp_process);
    }

    std::sort(current_processes.begin(), current_processes.end());
    processes_ = current_processes;
    return processes_; }

std::string System::Kernel() { return kernel_name; }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return operating_system; }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }

// TODO: Return the number of seconds since the system started running