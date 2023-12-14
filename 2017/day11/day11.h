#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day11{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day11/day11sample")=="3");
            std::cout << solvedayp1("./2017/day11/day11") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day11/day11") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            int q = 0,r = 0, s = 0;
            while(std::getline(std::cin,line,',')){
                if(line == "n"){
                    s++,r--;
                } else if (line == "ne"){
                    q++,r--;
                } else if (line == "se"){
                    q++,s--;
                } else if (line == "s"){
                    s--,r++;
                } else if (line == "sw"){
                    q--,r++;
                } else if (line == "nw"){
                    q--,s++;
                }
            }
            
            return std::to_string((abs(q)+abs(r)+abs(s))/2);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans = 0;
            int q = 0,r = 0, s = 0;
            while(std::getline(std::cin,line,',')){
                if(line == "n"){
                    s++,r--;
                } else if (line == "ne"){
                    q++,r--;
                } else if (line == "se"){
                    q++,s--;
                } else if (line == "s"){
                    s--,r++;
                } else if (line == "sw"){
                    q--,r++;
                } else if (line == "nw"){
                    q--,s++;
                }
                ans = std::max(ans,(abs(q)+abs(r)+abs(s))/2);
            }
            
            return std::to_string(ans);
        }
    }
}

