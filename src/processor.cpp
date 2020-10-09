#include "processor.h"



stat_vars Processor::assign_values(stat_vars &in)
{
    std::vector<std::string> vals = LinuxParser::CpuUtilization();
    in.idle =  std::stof(vals[LinuxParser::CPUStates::kIdle_]);
    in.iowait = std::stof(vals[LinuxParser::CPUStates::kIOwait_]);
    in.user = std::stof(vals[LinuxParser::CPUStates::kUser_]);
    in.nice = std::stof(vals[LinuxParser::CPUStates::kNice_]);
    in.system = std::stof(vals[LinuxParser::CPUStates::kSystem_]);
    in.irq = std::stof(vals[LinuxParser::CPUStates::kIRQ_]);
    in.softirq = std::stof(vals[LinuxParser::CPUStates::kSoftIRQ_]);
    in.steal = std::stof(vals[LinuxParser::CPUStates::kSteal_]);

    return in;
}

float Processor::calculate_sum(float idle, float iowait){

    return ( idle + iowait);

}
float Processor::calculate_sum(float user, float nice, float system, float irq, float softirq, float steal){

    return (user+nice+system+irq+softirq+steal);
}


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    
    float PrevIdle = calculate_sum(prev.idle,prev.iowait);
    float PrevNonIdle = calculate_sum(prev.user , prev.nice, prev.system, prev.irq,prev.softirq,prev.steal);
    float PrevTotal = PrevIdle + PrevNonIdle;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    curr = assign_values(curr);

    float Idle = calculate_sum(curr.idle,curr.iowait);
    float NonIdle = calculate_sum(curr.user , curr.nice, curr.system, curr.irq,curr.softirq,curr.steal);
    float Total = Idle + NonIdle;

    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    float CPU_percent = (totald - idled)/totald;

    prev = curr;
    
    return CPU_percent; }