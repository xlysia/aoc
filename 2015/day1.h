#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

std::string solvedayp1(std::string p);

std::string solvedayp2(std::string p);

namespace aoc2015{
    namespace day1{
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/input/day1sample")=="-3");
            std::cout << solvedayp1("./2015/input/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/input/day1sample")=="1");
            std::cout << solvedayp2("./2015/input/day1") << std::endl;
        }
    }
}

std::string solvedayp1(std::string p){
    std::ifstream in(p);
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf());
    std::string line;
    std::getline(std::cin,line);
    int res =  std::count(line.begin(), line.end(), '(') - std::count(line.begin(), line.end(), ')');
    return std::to_string(res);
}

std::string solvedayp2(std::string p){
    std::ifstream in(p);
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf());
    char c;
    int e = 0;
    int res = 0;
    while(e != -1){
        res+=1;
        std::cin >> c;
        e += (c==')')?-1:1;
    }
    return std::to_string(res);
}