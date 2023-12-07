#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day16{

        std::string solvedayp1(std::string p,int disksize);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day16/day16sample",20)=="01100");
            std::cout << solvedayp1("./2016/day16/day16",272) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp1("./2016/day16/day16",35651584) << std::endl;
        }

        std::string solvedayp1(std::string p, int disksize){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string key;

            getline(std::cin, key);

            while((int)key.size() < disksize){
                std::string b = key;
                std::reverse(b.begin(), b.end());
                for(int i = 0; i < (int)b.size(); i++){
                    b[i] = b[i] == '0' ? '1' : '0';
                }
                key.append("0" + b);
            }
            key = key.substr(0, disksize);

            while((int)key.size() % 2 == 0){
                std::string checksum = "";
                for(int i = 0; i < (int)key.size(); i+=2)checksum.push_back( key[i] == key[i+1]?'1':'0');
                key = checksum;
            }
            return key;
        }
    }
}

