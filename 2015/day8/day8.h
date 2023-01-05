#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day8{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day8/day8sample")=="12");
            std::cout << solvedayp1("./2015/day8/day8") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day8/day8sample")=="19");
            std::cout << solvedayp2("./2015/day8/day8") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            int resn = 0;

            while(std::getline(std::cin,line)){
                res += line.size();
                int idx = 1;
                int n = 0;
                while(idx < (int)line.size()-1){
                    char c = line[idx];
                    if(c=='\\'){
                        idx++;
                        c = line[idx];
                        if(c=='x'){
                            idx+=2;
                        }
                    }
                    n++;
                    idx++;
                }
                resn+=n;
            }
            return std::to_string(res-resn);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;

            while(std::getline(std::cin,line)){
                res += 2 + count(line.begin(),line.end(),'"')+ count(line.begin(),line.end(),'\\');
            }
            return std::to_string(res);
        }
    }
}

