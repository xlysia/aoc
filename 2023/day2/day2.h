#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <unordered_map>

namespace aoc2023{
    namespace day2{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day2/day2sample")=="8");
            std::cout << solvedayp1("./2023/day2/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day2/day2sample")=="2286");
            std::cout << solvedayp2("./2023/day2/day2") << std::endl;
        }

        bool isvalid(unordered_map<std::string,int>& bag, unordered_map<std::string,int>& hand){
            if(hand["red"]>bag["red"] || hand["green"]>bag["green"] || hand["blue"]>bag["blue"]){
                return false;
            }
            return true;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            
            unordered_map<std::string,int> bag{{"red",12},{"green",13},{"blue",14}};

            while(getline(std::cin,line)){
                // line is of form Game 1: 5 red, 1 green; 6 red, 3 blue; 9 red; 1 blue, 1 green;
                // parse GameId, then each round sep by ; then each roll sep by ,
                std::stringstream ss(line);
                std::string gameid;
                getline(ss,gameid,':');
                // split gameid to keep only number
                gameid = gameid.substr(5);
                std::string round;
                unordered_map<std::string,int> hand{{"red",0},{"green",0},{"blue",0}};
                while(getline(ss,round,';')){
                    std::stringstream ss2(round);
                    std::string roll;
                    while(getline(ss2,roll,',')){
                        // roll is of form 5 red
                        std::stringstream ss3(roll);
                        int num;
                        string color;
                        ss3 >> num >> color;
                        hand[color] = max(num,hand[color]);
                    }
                }
                if(isvalid(bag,hand)){
                    res+=stoi(gameid);
                }
            }

            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            
            while(getline(std::cin,line)){
                // line is of form Game 1: 5 red, 1 green; 6 red, 3 blue; 9 red; 1 blue, 1 green;
                // parse GameId, then each round sep by ; then each roll sep by ,
                std::stringstream ss(line);
                std::string gameid;
                getline(ss,gameid,':');
                // split gameid to keep only number
                gameid = gameid.substr(5);
                std::string round;
                unordered_map<std::string,int> hand{{"red",0},{"green",0},{"blue",0}};
                while(getline(ss,round,';')){
                    std::stringstream ss2(round);
                    std::string roll;
                    while(getline(ss2,roll,',')){
                        // roll is of form 5 red
                        std::stringstream ss3(roll);
                        int num;
                        string color;
                        ss3 >> num >> color;
                        hand[color] = max(num,hand[color]);
                    }
                }
                res += hand["red"]*hand["green"]*hand["blue"];
            }

            return std::to_string(res);
        }
    }
}

