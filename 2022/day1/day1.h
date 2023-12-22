#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2022{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2022/day1/day1sample")=="24000");
            std::cout << solvedayp1("./2022/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2022/day1/day1sample")=="45000");
            std::cout << solvedayp2("./2022/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int sum = 0;
            int ans = 0;
            while(std::getline(std::cin,line)){
                if(line.size()==0){
                    ans = max(sum,ans);
                    sum = 0;
                }
                else{
                    sum += std::stoi(line);
                }
            }
            ans = max(sum,ans);

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int sum = 0;
            int ans = 0;

            priority_queue<int,vector<int>,greater<int>> minheap;

            while(std::getline(std::cin,line)){
                if(line.size()==0){
                    minheap.push(sum);
                    if(minheap.size()>3){
                        minheap.pop();
                    }
                    sum = 0;
                }
                else{
                    sum += std::stoi(line);
                }
            }
            minheap.push(sum);
            if(minheap.size()>3){
                minheap.pop();
            }
            while(!minheap.empty()){
                ans += minheap.top();
                minheap.pop();
            }
            return to_string(ans);
        }
    }
}

