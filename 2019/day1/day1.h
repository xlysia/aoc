#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2019{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2019/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2019/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            int res = 0;
            while(std::cin >> val){
                res += (val/3)-2;
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            int res = 0;
            while(std::cin >> val){
                
                while(val>0){
                    val = std::max(0,(val/3)-2);
                    res+=val;
                }
            }
            return std::to_string(res);
        }
    }
}

