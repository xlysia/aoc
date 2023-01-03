#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "all_headers.h"

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point start;
#define NOW high_resolution_clock::now()
#define TIME duration_cast<duration<double>>(NOW - start).count()

typedef void (*FnPtr)();

std::map<std::string,FnPtr> functional_map;

void init_map();

int main(int argc, char** argv)
{
  init_map();
  start = NOW;
  std::cout << "-------" << std::endl;
  std::string year(argv[1]);
  std::string day(argv[2]);
  functional_map[year+"_"+day]();
  std::cout << "-------" << std::endl;
  std::cout << TIME << std::endl;
}


void init_map(){ 
  functional_map["2015_1"]=aoc2015::day1::run;
  functional_map["2015_2"]=aoc2015::day2::run;
  functional_map["2015_3"]=aoc2015::day3::run;
}