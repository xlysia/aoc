#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>

namespace aoc2020{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2020/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2020/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            std::vector<int> x;
            while(std::cin >> val){
                for(int v : x){
                    if(v + val == 2020)return std::to_string(v*val);
                }
                x.push_back(val);
            }
            return "-1";
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            long val;
            std::vector<long> x;
            while(std::cin >> val){
                for(int i = 0;i < (int)x.size()-1;i++){
                    for(int j = i+1 ; j < (int)x.size();j++){
                        if(x[i] + x[j] + val == 2020)return std::to_string(x[i]*x[j]*val);

                    }
                }
                x.push_back(val);
            }
            return "-1";
        }
    }
}

