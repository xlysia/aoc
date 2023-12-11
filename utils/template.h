#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day4{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/input/day4sample")=="-3");
            std::cout << solvedayp1("./2015/input/day4") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/input/day4sample")=="-1");
            std::cout << solvedayp2("./2015/input/day4") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);
            int ans =  0;
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int ans = 0;
            return std::to_string(ans);
        }
    }
}
