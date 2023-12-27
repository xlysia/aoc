#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

namespace aoc2018{
    namespace day12{

        std::string solvedayp1(std::string p,long long N);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day12/day12sample",20)=="325");
            std::cout << solvedayp1("./2018/day12/day12",20) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp1("./2018/day12/day12",50000000000) << std::endl;
        }

        std::string solvedayp1(std::string p,long long N){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            getline(std::cin,line);
            std::string init =line.substr(15);
            getline(std::cin,line);
            unordered_map<std::string,char> rules;
            unordered_set<std::string> extendLeft;
            unordered_set<std::string> extendRight;

            while(getline(std::cin,line)){
                std::stringstream ss(line);
                std::string key;
                ss >> key;
                ss >> line;
                char val;
                ss >> val;
                rules[key] = val;
                if(val=='#'){
                    if(key.substr(0,3) == string(3,'.'))extendLeft.insert(key.substr(3,2));
                    if(key.substr(2,3) == string(3,'.'))extendRight.insert(key.substr(0,2));
                }
            }
            long long turn = 0;

            long long extend = 0;

            while(turn++<N){
                std::string next = init;
                 
                string key = ".." + init.substr(0,3);
                if(rules.find(key)!=rules.end()){
                    next[0] = rules[key];
                }else{
                    next[0] = '.';
                }
                key = "." + init.substr(0,4);
                if(rules.find(key)!=rules.end()){
                    next[1] = rules[key];
                }else{
                    next[1] = '.';
                }

                key = init.substr(init.size()-3,3) + "..";
                if(rules.find(key)!=rules.end()){
                    next[init.size()-1] = rules[key];
                }else{
                    next[init.size()-1] = '.';
                }
                key = init.substr(init.size()-4,4) + ".";
                if(rules.find(key)!=rules.end()){
                    next[init.size()-2] = rules[key];
                }else{
                    next[init.size()-2] = '.';
                }

                for(int i=2;i<(int)init.size()-2;i++){
                    std::string key = init.substr(i-2,5);
                    if(rules.find(key)!=rules.end()){
                        next[i] = rules[key];
                    }else{
                        next[i] = '.';
                    }
                }

                if(extendLeft.find(init.substr(0,2))!=extendLeft.end()){
                    next.insert(next.begin(),'#');
                    extend++;
                }
                if(extendRight.find(init.substr(init.size()-2,2))!=extendRight.end()){
                    next.push_back('#');
                }
                int firstPlant = next.find('#');
                int lastPlant = next.rfind('#');
                next = next.substr(firstPlant,lastPlant-firstPlant+1);
                extend -= firstPlant;
                if(init == next){
                    long long ans = 0;
                    long long k = 0;
                    for(int i=0;i<(int)init.size();i++){
                        if(init[i]=='#'){
                            ans += i-extend;
                            k++;
                        }
                    }

                    return std::to_string(ans + (N-turn)*firstPlant*k);
                }
                init = next;
            }

            long long ans =  0;
            
            for(int i=0;i<(int)init.size();i++){
                if(init[i]=='#'){
                    ans += i-extend;
                }
            }
            return std::to_string(ans);
        }
    }
}

