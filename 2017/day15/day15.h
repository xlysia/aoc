#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day15{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day15/day15sample")=="588");
            std::cout << solvedayp1("./2017/day15/day15") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day15/day15sample")=="309");
            std::cout << solvedayp2("./2017/day15/day15") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);
            std::istringstream iss(line);
            long long a, b;
            std::string token;
            iss >> token >> token >> token >> token >> a;
            getline(std::cin, line);
            iss = std::istringstream(line);
            iss >> token >> token >> token >> token >> b;
            int div = 2147483647;
            int xa = 16807, xb = 48271;

            int ans =  0;

            for(int i = 0; i < 40000000; i++){
                a = (a * xa) % div;
                b = (b * xb) % div;
                if((a & 0xFFFF) == (b & 0xFFFF)) ans++;
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);
            std::istringstream iss(line);
            long long a, b;
            std::string token;
            iss >> token >> token >> token >> token >> a;
            getline(std::cin, line);
            iss = std::istringstream(line);
            iss >> token >> token >> token >> token >> b;
            int div = 2147483647;
            int xa = 16807, xb = 48271;

            int ans =  0;

            for(int i = 0; i < 5000000; i++){
                a = (a * xa) % div;
                while(a%4){a = (a * xa) % div;}
                b = (b * xb) % div;
                while(b%8){b = (b * xb) % div;}
                if((a & 0xFFFF) == (b & 0xFFFF)) ans++;
            }

            return std::to_string(ans);
        }
    }
}

