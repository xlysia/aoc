#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day5{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day5/day5sample")=="5");
            std::cout << solvedayp1("./2017/day5/day5") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day5/day5sample")=="10");
            std::cout << solvedayp2("./2017/day5/day5") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            vector<int> instructions;
            int val;

            while(std::cin >> val)instructions.push_back(val);
            int ans = 0;
            int i = 0;
            int n = instructions.size();
            while(i < n){
                i+= instructions[i]++;
                ans++;
            }
            return to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            vector<int> instructions;
            int val;

            while(std::cin >> val)instructions.push_back(val);
            int ans = 0;
            int i = 0;
            int n = instructions.size();
            while(i < n){
                int j = instructions[i]+i;
                if(instructions[i]>=3)instructions[i]--;
                else instructions[i]++;
                i = j;
                ans++;
            }
            return to_string(ans);
        }
    }
}

