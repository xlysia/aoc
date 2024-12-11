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

std::map<std::string,FnPtr> functional_map =
{
  {"2024_3",aoc2024::day3::run},
  {"2024_2",aoc2024::day2::run},
  {"2024_1",aoc2024::day1::run},

};

int main(int argc, char** argv)
{
  start = NOW;
  std::cout << "-------" << std::endl;
  std::string year(argv[1]);
  std::string day(argv[2]);
  functional_map[year+"_"+day]();
  std::cout << "-------" << std::endl;
  std::cout << TIME << std::endl;
}