#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day6{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void init();
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day6/day6sample")=="easter");
            std::cout << solvedayp1("./2016/day6/day6") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day6/day6sample")=="advent");
            std::cout << solvedayp2("./2016/day6/day6") << std::endl;
        }

        std::map<char,int*> dict = {};

        void init(bool b){
            dict.clear();
            for(char c ='a'; c <= 'z';c++){
                dict[c] = new int[8];
                for(int i = 0;i < 8;i++){
                    dict[c][i] = b*999999;
                }
            }
        }

        std::string parse(){
            std::string line;
            while(std::getline(std::cin , line)){
                for(int i = 0; i < (int)line.size();i++){
                    dict[line[i]][i] = (dict[line[i]][i]+1)%999999;
                }
            }
            return line;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            init(false);
            std::string res = parse();
            for(auto item : dict){
                for(int i =0;i < (int)res.size();i++){
                    if(item.second[i] > dict[res[i]][i]){
                        res.replace(i,1,std::string(1,item.first));
                    }
                }
            }
            return res;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            init(true);
            std::string res = parse();
            for(auto item : dict){
                for(int i =0;i < (int)res.size();i++){
                    if(item.second[i] < dict[res[i]][i]){
                        res.replace(i,1,std::string(1,item.first));
                    }
                }
            }
            return res;
        }
    }
}

