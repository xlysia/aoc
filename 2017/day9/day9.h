#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day9{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day9/day9sample")=="9");
            std::cout << solvedayp1("./2017/day9/day9") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day9/day9") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            char c;
            
            int groups = 0;
            bool isgarbage = false;
            int ans = 0;
            while(cin.good()){
                cin >> c;
                if(c == '!'){
                    cin >> c;
                    continue;
                }

                if(isgarbage){
                    if(c == '>'){
                        isgarbage = false;
                    }
                    continue;
                }else{
                    if(c == '<'){
                        isgarbage = true;
                        continue;
                    }else if(c == '{'){
                        groups++;
                        ans += groups;
                    }else if(c == '}'){
                        groups--;
                    }
                }
                

            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            char c;
            
            int groups = 0;
            bool isgarbage = false;
            int ans = 0;
            while(cin.good()){
                cin >> c;
                if(c == '!'){
                    cin >> c;
                    continue;
                }

                if(isgarbage){
                    if(c == '>'){
                        isgarbage = false;
                    }else{
                        ans++;
                    }
                    continue;
                }else{
                    if(c == '<'){
                        isgarbage = true;
                        continue;
                    }else if(c == '{'){
                        groups++;
                    }else if(c == '}'){
                        groups--;
                    }
                }
                

            }
            return std::to_string(ans);
        }
    }
}

