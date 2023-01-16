#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <map>

namespace aoc2018{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2018/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2018/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            int res =  0;
            while(std::cin >> val){
                res += val;      
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::map<int,int> visited = {};
            visited[0]=1;
            int res =  0;
            while(1){
                std::ifstream in(p);
                std::cin.rdbuf(in.rdbuf());
                int val;
                while(std::cin >> val){
                    res += val;
                    if(visited.find(res) == visited.end())visited[res]=0;
                    visited[res]++;
                    if(visited[res]>1)return std::to_string(res);
                }
            }

            return std::to_string(res);
        }
    }
}

