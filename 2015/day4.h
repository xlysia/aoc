#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include "./utils/md5.h"

namespace aoc2015{
    namespace day4{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/input/day4sample")=="1048970");
            std::cout << solvedayp1("./2015/input/day4") << std::endl;

            std::cout << "Part 2" << std::endl;
           // assert (solvedayp2("./2015/input/day4sample")=="1048970");
            std::cout << solvedayp2("./2015/input/day4") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);
            int res =  0;
            while(1){
                std::string s = md5(line+std::to_string(res));
                if(s.substr(0,5) == "00000"){
                    break;
                }

                res++;
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);
            int res =  0;
            while(1){
                std::string s = md5(line+std::to_string(res));
                if(s.substr(0,6) == "000000"){
                    break;
                }

                res++;
            }
            return std::to_string(res);
        }
    }
}
