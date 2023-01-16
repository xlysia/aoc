#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

namespace aoc2016{
    namespace day12{
        std::map<char,int> table = {};
        std::string solveday(std::string p);
        void run(){

            for(char c = 'a' ; c <= 'd';c++)table[c]=0;
            std::cout << "Part 1" << std::endl;
            std::cout << solveday("./2016/day12/day12") << std::endl;
            for(char c = 'a' ; c <= 'd';c++)table[c]=0;
            table['c']=1;
            std::cout << "Part 2" << std::endl;
            std::cout << solveday("./2016/day12/day12") << std::endl;
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<std::string> instructions;
            while(std::getline(std::cin, line))instructions.push_back(line);
            int i = 0;
            while(i > -1 && i < (int)instructions.size()){
                line = instructions[i];
                std::vector<std::string> x;
                size_t pos;
                line.push_back(' ');
                while((pos=line.find(' '))!=std::string::npos){
                    x.push_back(line.substr(0,pos));
                    line.erase(0,pos+1);
                }
                if(x[0] == "cpy"){
                    if(x[1][0] <= '9' && x[1][0] >= '0'){
                        table[x[2][0]] = std::atoi(x[1].c_str());
                    }else{
                        table[x[2][0]] = table[x[1][0]];
                    }
                    i++;
                }else if(x[0]=="inc"){
                    table[x[1][0]]++;
                    i++;
                }else if(x[0]=="dec"){
                    table[x[1][0]]--;
                    i++;
                }else if(x[0]=="jnz"){
                    if(x[1][0] <= '9' && x[1][0] >= '0'){
                        if(std::atoi(x[1].c_str())==0)i++;
                        else i+=std::atoi(x[2].c_str());
                    }else{
                        if(table[x[1][0]]==0)i++;
                        else{
                            i+=std::atoi(x[2].c_str());
                        }
                    }

                }
            }
            return std::to_string(table['a']);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	    std::string line;
            int res = 0;
            return std::to_string(res);
        }
    }
}

