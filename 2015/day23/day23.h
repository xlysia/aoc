#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day23{

        struct instruction{
            std::string name;
            std::string r;
            int offset = 0;
        };
        std::vector<instruction> book;
        std::map<std::string,int> res;

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day23/day23sample")=="2");
            std::cout << solvedayp1("./2015/day23/day23") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2015/day23/day23") << std::endl;
        }

        void parse(){
            book.clear();
            res.clear();
            std::string line;
            while(std::getline(std::cin,line)){
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos).c_str());
                    line.erase(0, pos + 1);
                }
                x.push_back(line);

                instruction o;
                o.name = x[0];
                if(o.name != "jmp"){
                    o.r = x[1].substr(0,1);
                    res[o.r] = 0;
                    if(x.size()>2){
                        o.offset = std::atoi(x[2].c_str());
                    }
                }else{
                    o.offset = std::atoi(x[1].c_str());          
                }

                book.push_back(o);
            }
        }

        void explore(){
            int idx = 0;
            while(idx > -1 && idx <(int)book.size()){
                instruction o = book[idx];
                if(o.name == "inc"){
                    res[o.r]++;
                    idx++;
                }else if(o.name == "hlf"){
                    res[o.r]/=2;
                    idx++;  
                }else if(o.name == "tpl"){
                    res[o.r]*=3;
                    idx++;                 
                }else if(o.name == "jmp"){
                    idx+=o.offset;                 
                }else if(o.name == "jie"){
                    idx += ((res[o.r]%2)?1:o.offset);
                }else if(o.name == "jio"){
                    idx += ((res[o.r]==1)?o.offset:1);
                }
            }
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            explore();
            return std::to_string(res["b"]);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            res["a"]=1;
            explore();
            return std::to_string(res["b"]);
        }
    }
}

