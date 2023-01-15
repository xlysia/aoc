#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day2{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2017/day2/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day2/day2") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;

            while(std::getline(std::cin,line)){
                int a = 0;
                int b = 9999999;
                int val;
                std::stringstream ss(line);
                while(ss >> val){
                    a = std::max(a,val);
                    b = std::min(b,val);
                }
                res += (a-b);
            }

            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int res =  0;

            while(std::getline(std::cin,line)){
                std::vector<int> x;
                int val;
                std::stringstream ss(line);
                while(ss >> val){
                    bool b = false;
                    for(int i : x){
                        if(i%val == 0){res+=i/val;break;b=true;}
                        else if(val%i == 0){res+=val/i;break;b=true;}
                    }
                    if(b)break;
                    x.push_back(val);
                }
            }
            return std::to_string(res);
        }
    }
}

