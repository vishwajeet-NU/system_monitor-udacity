#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <chrono>
#include <thread>
#include "linux_parser.h"
#include <iostream>
struct stat_vars{
float idle{0.0}, iowait{0.0}, user{0.0},nice{0.0},system{0.0},irq{0.0},softirq{0.0},steal{0.0};

};


class Processor {
 public:
 Processor()
 {
    prev = assign_values(prev);

 }
  float Utilization();  // TODO: See src/processor.cpp
  float calculate_sum(float idle, float iowait);
  float calculate_sum(float user, float nice, float system, float irq, float softirq, float steal);

  stat_vars assign_values(stat_vars &in);
  // TODO: Declare any necessary private members
 private:
    stat_vars prev;
    stat_vars curr;

};

#endif