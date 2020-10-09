#include "ncurses_display.h"
#include "system.h"
#include <iostream>
// #include "linux_parser.h"

int main() {
  System system;
  system.UpTime();
  // std::cout<<system.Cpu().Utilization();
 //   LinuxParser::UpTime();
NCursesDisplay::Display(system);
}