#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <vector>

namespace aoc2015{
    namespace day7{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
           // assert (solvedayp1("./2015/input/day7sample")=="-3");
            std::cout << solvedayp1("./2015/input/day7") << std::endl;

            std::cout << "Part 2" << std::endl;
            // assert (solvedayp2("./2015/input/day7sample")=="-1");
             std::cout << solvedayp2("./2015/input/day7") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            std::map<std::string,std::bitset<16>> dict = {};
            std::vector<std::string> instructions;
            while(std::getline(std::cin,line)){
                instructions.push_back(line);
            }
            while(instructions.size()>0){
                line = *instructions.begin();
                size_t pos = 0;
                std::bitset<16> left = 0;
                std::bitset<16> right = 0;
                std::string p = "";
                bool bfillleft = false;
                bool bor = false;
                bool band = false;
                bool bfail = false;
                while ((pos = line.find(' ')) != std::string::npos) {
                    std::string token = line.substr(0, pos).c_str();

                    
                    line.erase(0, pos + 1);
                    
                    if(token == "NOT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        if(dict.find(token) == dict.end()){bfail = true;break;}
                        if(!bfillleft){left = ~dict[token];bfillleft=true;}
                        else right = ~dict[token];
                    }else if(token == "AND"){
                        band = true;
                    }else if(token == "OR"){
                        bor = true;
                    }else if(token == "RSHIFT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        left >>= atoi(token.c_str());
                    }else if(token == "LSHIFT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        left <<= atoi(token.c_str());
                    }else if(token=="->"){
                        if(bor)dict[line] = left | right;
                        else if(band) dict[line] = left & right;
                        else dict[line] = left;  
                    }else{
                        if(isdigit(token[0])){
                            if(!bfillleft){left = atoi(token.c_str());bfillleft=true;}
                            else right = atoi(token.c_str());
                        }else{
                            if(dict.find(token) == dict.end()){bfail = true;break;}
                            if(!bfillleft){left = dict[token];bfillleft=true;}
                            else right = dict[token];
                        }
                    }
                }
                if(bfail){
                    instructions.push_back(*instructions.begin());
                }
                instructions.erase(instructions.begin());
            }
            res = (int)(dict["a"].to_ulong());
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            std::map<std::string,std::bitset<16>> dict = {};
            std::vector<std::string> instructions;
            while(std::getline(std::cin,line)){
                instructions.push_back(line);
            }
            dict["b"] = 3176;//atoi(solvedayp1(p).c_str());
            while(instructions.size()>0){
                line = *instructions.begin();
                size_t pos = 0;
                std::bitset<16> left = 0;
                std::bitset<16> right = 0;
                std::string p = "";
                bool bfillleft = false;
                bool bor = false;
                bool band = false;
                bool bfail = false;
                while ((pos = line.find(' ')) != std::string::npos) {
                    std::string token = line.substr(0, pos).c_str();

                    
                    line.erase(0, pos + 1);
                    
                    if(token == "NOT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        if(dict.find(token) == dict.end()){bfail = true;break;}
                        if(!bfillleft){left = ~dict[token];bfillleft=true;}
                        else right = ~dict[token];
                    }else if(token == "AND"){
                        band = true;
                    }else if(token == "OR"){
                        bor = true;
                    }else if(token == "RSHIFT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        left >>= atoi(token.c_str());
                    }else if(token == "LSHIFT"){
                        pos = line.find(' ');
                        token = line.substr(0, pos).c_str();
                        line.erase(0, pos + 1);
                        left <<= atoi(token.c_str());
                    }else if(token=="->"){
                        if(line != "b"){
                            if(bor)dict[line] = left | right;
                            else if(band) dict[line] = left & right;
                            else dict[line] = left;  
                        }

                    }else{
                        if(isdigit(token[0])){
                            if(!bfillleft){left = atoi(token.c_str());bfillleft=true;}
                            else right = atoi(token.c_str());
                        }else{
                            if(dict.find(token) == dict.end()){bfail = true;break;}
                            if(!bfillleft){left = dict[token];bfillleft=true;}
                            else right = dict[token];
                        }
                    }
                }
                if(bfail){
                    instructions.push_back(*instructions.begin());
                }
                instructions.erase(instructions.begin());
            }
            res = (int)(dict["a"].to_ulong());
            return std::to_string(res);
        }
    }
}
