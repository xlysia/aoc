#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <cmath>

namespace aoc2015{
    namespace day20{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day20/day20sample")=="6");
            std::cout << solvedayp1("./2015/day20/day20") << std::endl;

            std::cout << "Part 2" << std::endl;
//            assert (solvedayp2("./2015/day20/day20sample")=="-1");
            std::cout << solvedayp2("./2015/day20/day20") << std::endl;
        }

        int explore(int goal){
            const int W = goal/10 + 1;
            int *houses =  new int[W];
            for(int i=0;i < W ; i++){
                houses[i] = 0;
            }
            for (int i = 1; i < W; i++){
                for (int h = i; h < W; h+=i)houses[h] += i * 10;
            }           
            for (int h = 1; h < W; h++){
                if (houses[h] > goal) { return h; }
            }
            return -99;
        }
        
        int explore2(int goal){
            const int W = goal/11 + 1;
            int *houses =  new int[W];
            for(int i=0;i < W ; i++){
                houses[i] = 0;
            }
            for (int i = 1; i < W; i++){
                for (int h = i,n=0; h < W && n < 50; h+=i,n++)houses[h] += i * 11;
            }           
            for (int h = 1; h < W; h++){
                if (houses[h] > goal) { return h; }
            }

            return -99;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int goal;
            std::cin >> goal;
            int res =  explore(goal);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int goal;
            std::cin >> goal;
            int res =  explore2(goal);
            return std::to_string(res);
        }
    }
}

