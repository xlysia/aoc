#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2017/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);

            int res =  0;
            for(int i = 0; i < (int)line.size();i++){
                if(line[i]==line[(i+1)%(int)line.size()]){
                    res+=line[i]-'0';
                }
            }

            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);

            int res =  0;
            for(int i = 0; i < (int)line.size();i++){
                if(line[i]==line[(i+(int)line.size()/2)%(int)line.size()]){
                    res+=line[i]-'0';
                }
            }

            return std::to_string(res);
        }
    }
}

