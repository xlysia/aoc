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
  {"2023_9",aoc2023::day9::run},
  {"2016_19",aoc2016::day19::run},
  {"2023_8",aoc2023::day8::run},
  {"2016_18",aoc2016::day18::run},
  {"2016_17",aoc2016::day17::run},
  {"2016_16",aoc2016::day16::run},
  {"2016_15",aoc2016::day15::run},
  {"2023_7",aoc2023::day7::run},
  {"2016_14",aoc2016::day14::run},
  {"2016_13",aoc2016::day13::run},
  {"2023_6",aoc2023::day6::run},
  {"2023_5",aoc2023::day5::run},
  {"2023_4",aoc2023::day4::run},
  {"2023_3",aoc2023::day3::run},
  {"2023_2",aoc2023::day2::run},
  {"2023_1",aoc2023::day1::run},
  {"2020_1",aoc2020::day1::run},
  {"2016_12",aoc2016::day12::run},
  {"2019_1",aoc2019::day1::run},
  {"2018_3",aoc2018::day3::run},
  {"2018_2",aoc2018::day2::run},
  {"2018_1",aoc2018::day1::run},
  {"2017_3",aoc2017::day3::run},
  {"2017_2",aoc2017::day2::run},
  {"2017_1",aoc2017::day1::run},
  {"2016_11",aoc2016::day11::run},
  {"2016_10",aoc2016::day10::run},
  {"2016_9",aoc2016::day9::run},
  {"2016_8",aoc2016::day8::run},
  {"2016_7",aoc2016::day7::run},
  {"2016_6",aoc2016::day6::run},
  {"2016_5",aoc2016::day5::run},
  {"2016_4",aoc2016::day4::run},
  {"2016_3",aoc2016::day3::run},
  {"2016_2",aoc2016::day2::run},
  {"2016_1",aoc2016::day1::run},
  {"2015_25",aoc2015::day25::run},
  {"2015_24",aoc2015::day24::run},
  {"2015_23",aoc2015::day23::run},
  {"2015_22",aoc2015::day22::run},
  {"2015_21",aoc2015::day21::run},
  {"2015_20",aoc2015::day20::run},
  {"2015_19",aoc2015::day19::run},
  {"2015_18",aoc2015::day18::run},
  {"2015_17",aoc2015::day17::run},
  {"2015_16",aoc2015::day16::run},
  {"2015_15",aoc2015::day15::run},
  {"2015_14",aoc2015::day14::run},
  {"2015_13",aoc2015::day13::run},
  {"2015_12",aoc2015::day12::run},
  {"2015_11",aoc2015::day11::run},
  {"2015_10",aoc2015::day10::run},
  {"2015_9",aoc2015::day9::run},
  {"2015_8",aoc2015::day8::run},
  {"2015_7",aoc2015::day7::run},
  {"2015_6",aoc2015::day6::run},
  {"2015_5",aoc2015::day5::run},
  {"2015_4",aoc2015::day4::run},
  {"2015_3",aoc2015::day3::run},
  {"2015_2",aoc2015::day2::run},
  {"2015_1",aoc2015::day1::run},
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