#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <map>
namespace aoc2018{
    namespace day2{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2018/day2/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2018/day2/day2") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res_two = 0;
            int res_three = 0;
            while(std::getline(std::cin,line)){
                std::map<char,int> d = {};
                for(char c = 'a'; c <= 'z';c++)d[c]=0;
                for(char c : line){d[c]++;}
                int b = 0;
                for(auto e : d){
                    if(e.second==2 && (b&1)==0){res_two++;b|=1;}
                    if(e.second==3 && (b&2)==0){res_three++;b|=2;}
                }
            }
            return std::to_string(res_two*res_three);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::vector<std::string> boxes={};
            std::string line;
            while(std::getline(std::cin,line))boxes.push_back(line);
            
            for(int i = 0; i < (int)boxes.size();i++){
                for(int j = i+1; j < (int)boxes.size();j++){
                    std::string res = "";
                    for(int k = 0;k < (int)boxes[0].size();k++){
                        if(boxes[i][k] == boxes[j][k]){
                            res.push_back(boxes[i][k]);
                        }
                        if(res.size() == boxes[0].size()-1){
                            return res;
                        }
                    }
                }
            }

            return "fail";
        }
    }
}

