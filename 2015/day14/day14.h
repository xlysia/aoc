#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day14{

        struct deer{
            std::string name;
            int speed;
            int wait;
            int duration;
            int distance = 0;
            int time = 0;
            int lastwait = 0;
            int score = 0;
            void travel(int s){
                int cycle = wait+duration;
                distance += (s/cycle)*speed*duration;
                s -= (s/cycle)*cycle;
                distance += speed*std::min(duration,s); 
            }
            void step(){
                if((this->time%(wait+duration))< duration){
                    distance += speed;
                }
                this->time++;
            }
        };

        std::vector<deer> deers;
        int time = 1000;
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            time = 1000;
            assert (solvedayp1("./2015/day14/day14sample")=="1120");
            time = 2503;
            std::cout << solvedayp1("./2015/day14/day14") << std::endl;

            std::cout << "Part 2" << std::endl;
            time = 1000;
            assert (solvedayp2("./2015/day14/day14sample")=="689");
            time = 2503;
            std::cout << solvedayp2("./2015/day14/day14") << std::endl;
        }
        void parse();

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res =  0;
            for(deer& d : deers){
                d.travel(time);
                res = std::max(res,d.distance);
            }

            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res =  0;
            for(int i = 0; i < time;i++){
                int res =  0;
                for(deer& d : deers){
                    d.step();
                    res = std::max(res,d.distance);
                }
                for(deer& d : deers){
                    if(d.distance == res)d.score++;
                }
            }
            res =  0;
            for(deer& d : deers){
                res = std::max(res,d.score);
            }
            return std::to_string(res);
        }

        void parse(){
            deers.clear();
            std::string line;
            while(std::getline(std::cin , line)){
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos).c_str());
                    line.erase(0, pos + 1);
                }
                deer d;
                d.name = x[0];
                d.speed = std::atoi(x[3].c_str());
                d.duration = std::atoi(x[6].c_str());
                d.wait = std::atoi(x.back().c_str());
                deers.push_back(d);
            }
            
        }
    }
}

