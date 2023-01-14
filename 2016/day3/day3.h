#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace aoc2016{
    namespace day3{
        
        bool istriangle(int a, int b, int c){
            int t[3] = {a,b,c};
            std::sort(std::begin(t), std::end(t));
            return t[0]+t[1] > t[2];
        }

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (istriangle(5, 10, 25) == false);
            assert (istriangle(25, 5, 10) == false);
            std::cout << solvedayp1("./2016/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2016/day3/day3") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            while(std::getline(std::cin,line)){
                std::stringstream ss(line);
                int a,b,c;
                ss >> a >> b >> c;
                res+=istriangle(a,b,c);
            }


            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int res =  0;
            while(std::getline(std::cin,line)){
                std::string line2,line3;
                std::getline(std::cin,line2);
                std::getline(std::cin,line3);
                std::stringstream ss(line + " "+ line2 + " "+line3);
                int a,b,c,d,e,f,g,h,i;
                ss >> a >> d >> g >> b >> e >> h >> c >> f >> i;
                res+=(istriangle(a,b,c)+istriangle(d,e,f)+istriangle(g,h,i));
            }
            return std::to_string(res);
        }
    }
}

