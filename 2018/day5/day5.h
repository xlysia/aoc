#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <stack>
#include <string>

using namespace std;

namespace aoc2018{
    namespace day5{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day5/day5sample")=="10");
            std::cout << solvedayp1("./2018/day5/day5") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day5/day5sample")=="4");
            std::cout << solvedayp2("./2018/day5/day5") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            char c;
            stack<char> stack;
            while(cin >> c){
                
                if(!stack.empty() && abs(stack.top()-c)==32){
                    stack.pop();
                }else{
                    stack.push(c);
                }
            }
            return std::to_string(stack.size());
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            char c;
            vector<stack<char>> stacks(26,stack<char>());
            vector<bool> seen(26,false);
            while(cin >> c){
                seen[tolower(c)-'a'] = true;
                for(int i = 0;i < 26;i++){
                    if(i == tolower(c)-'a')continue;
                    if(!stacks[i].empty() && abs(stacks[i].top()-c)==32){
                        stacks[i].pop();
                    }else{
                        stacks[i].push(c);
                    }
                }
            }
            int ans = INT_MAX;
            for(int i = 0;i < 26;i++){
                if(!seen[i])continue;
                if((int)stacks[i].size() < ans){
                    ans = stacks[i].size();
                }
            }
            return std::to_string(ans);
        }
    }
}

