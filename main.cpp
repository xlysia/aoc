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
  {"2023_23",aoc2023::day23::run},
  {"2018_7",aoc2018::day7::run},
  {"2018_6",aoc2018::day6::run},
  {"2022_1",aoc2022::day1::run},
  {"2021_1",aoc2021::day1::run},
  {"2023_22",aoc2023::day22::run},
  {"2018_5",aoc2018::day5::run},
  {"2018_4",aoc2018::day4::run},
  {"2023_21",aoc2023::day21::run},
  {"2017_25",aoc2017::day25::run},
  {"2017_24",aoc2017::day24::run},
  {"2023_20",aoc2023::day20::run},
  {"2017_23",aoc2017::day23::run},
  {"2017_22",aoc2017::day22::run},
  {"2023_19",aoc2023::day19::run},
  {"2023_18",aoc2023::day18::run},
  {"2017_21",aoc2017::day21::run},
  {"2017_20",aoc2017::day20::run},
  {"2023_17",aoc2023::day17::run},
  {"2017_19",aoc2017::day19::run},
  {"2017_18",aoc2017::day18::run},
  {"2017_17",aoc2017::day17::run},
  {"2017_16",aoc2017::day16::run},
  {"2023_16",aoc2023::day16::run},
  {"2017_15",aoc2017::day15::run},
  {"2017_14",aoc2017::day14::run},
  {"2017_13",aoc2017::day13::run},
  {"2017_12",aoc2017::day12::run},
  {"2023_15",aoc2023::day15::run},
  {"2017_11",aoc2017::day11::run},
  {"2017_10",aoc2017::day10::run},
  {"2017_9",aoc2017::day9::run},
  {"2017_8",aoc2017::day8::run},
  {"2017_7",aoc2017::day7::run},
  {"2017_6",aoc2017::day6::run},
  {"2023_14",aoc2023::day14::run},
  {"2023_13",aoc2023::day13::run},
  {"2017_5",aoc2017::day5::run},
  {"2017_4",aoc2017::day4::run},
  {"2023_12",aoc2023::day12::run},
  {"2016_25",aoc2016::day25::run},
  {"2016_24",aoc2016::day24::run},
  {"2016_23",aoc2016::day23::run},
  {"2016_22",aoc2016::day22::run},
  {"2023_11",aoc2023::day11::run},
  {"2016_21",aoc2016::day21::run},
  {"2023_10",aoc2023::day10::run},
  {"2016_20",aoc2016::day20::run},
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