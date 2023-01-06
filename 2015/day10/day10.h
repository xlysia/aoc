#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day10{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day10/day10sample")=="6");
            std::cout << solvedayp1("./2015/day10/day10") << std::endl;

            std::cout << "Part 2" << std::endl;
         //   assert (solvedayp2("./2015/day10/day10sample")=="-1");
            std::cout << solvedayp2("./2015/day10/day10p2") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            int value,n;
            std::cin >> value >> n;
            std::string s = std::to_string(value);
            while(n-- > 0){
                char d = s[0];
                int count = 0;
                std::string nextval = "";
                for(char c : s){
                    if(d == c)count++;
                    else{
                        nextval += std::to_string(count);
                        nextval.push_back(d);
                        d = c;
                        count = 1;
                    }
                }
                nextval += std::to_string(count);
                nextval.push_back(s[s.size()-1]);
                s = nextval;
                res = s.size();
            }
            
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            return solvedayp1(p);
        }
    }
}

