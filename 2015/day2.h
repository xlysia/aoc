#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day2{
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        int getSF(int w,int l, int h);
        int getRibbon(std::vector<int> x);
        void run(){

            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/input/day2sample")=="101");
            std::cout << solvedayp1("./2015/input/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/input/day2sample")=="48");
            std::cout << solvedayp2("./2015/input/day2") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::vector<int> x;
            int res = 0;
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                x.clear();
                while ((pos = line.find('x')) != std::string::npos) {
                    x.push_back(std::atoi(line.substr(0, pos).c_str()));
                    line.erase(0, pos + 1);
                }
                x.push_back(std::atoi(line.c_str()));
                res += getSF(x[0],x[1],x[2]);
            }


            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::vector<int> x;
            int res = 0;
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                x.clear();
                while ((pos = line.find('x')) != std::string::npos) {
                    x.push_back(std::atoi(line.substr(0, pos).c_str()));
                    line.erase(0, pos + 1);
                }
                x.push_back(std::atoi(line.c_str()));
                res += getRibbon(x);
            }


            return std::to_string(res);
        }

        int getSF(int w,int l, int h){
            int a = w*l;
            int b = w*h;
            int c = l*h;
            int res = 2*(a+b+c)+std::min({a,b,c});
            return res;
        }

        int getRibbon(std::vector<int> x){
            int res = x[0]*x[1]*x[2];
            std::sort(x.begin(),x.end());
            res += 2*(x[0]+x[1]);
            return res;
        }
    }
}