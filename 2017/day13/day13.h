#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day13{

        int solvedayp1(std::string p,int delay);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day13/day13sample",0)==24);
            std::cout << solvedayp1("./2017/day13/day13",0) << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day13/day13sample")=="10");
            std::cout << solvedayp2("./2017/day13/day13") << std::endl;
        }

        int solvedayp1(std::string p,int delay){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<int> firewalls(100,0);
            
            while(std::getline(std::cin,line)){
                std::stringstream ss(line);
                std::string token;
                std::getline(ss,token,':');
                ss >> firewalls[std::stoi(token)];
            }


            int ans =  0;
            for(int i = 0; i < 100; i++){
                if(firewalls[i] == 0) continue;
                if((i+delay) % (2*(firewalls[i]-1)) == 0){
                    ans += i*firewalls[i];
                }
            }
            return ans;
        }

        bool getCaught(std::vector<int>& firewalls,int delay){
            for(int i = 0; i < 100; i++){
                if(firewalls[i] == 0) continue;
                if((i+delay) % (2*(firewalls[i]-1)) == 0){
                    return true;
                }
            }
            return false;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<int> firewalls(100,0);
            
            while(std::getline(std::cin,line)){
                std::stringstream ss(line);
                std::string token;
                std::getline(ss,token,':');
                ss >> firewalls[std::stoi(token)];
            }

            int N = 0;
            while(getCaught(firewalls,N++)){}
            
            return std::to_string(N-1);
        }
    }
}

