#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>

namespace aoc2018{
    namespace day21{

        std::string solveday(std::string p);
        void run(){
            std::cout << "Part 1 & 2" << std::endl;
            std::cout << solveday("./2018/day21/day21") << std::endl;
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
                        vector<int> reg(6,0);
            reg[0] = 0;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int ip;
            ss >> line >> ip;
            int keyip = -1;
            std::vector<std::pair<std::string, std::vector<int>>> program;
            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::string op;
                ss >> op;
                std::vector<int> args(3,0);
                ss >> args[0] >> args[1] >> args[2];
                if(op == "eqrr" && args[1] == 0) keyip = args[0];
                program.push_back(std::make_pair(op, args));
            }

            unordered_map<std::string, std::function<void(int, int, int, vector<int>&)>> ops;
            ops["addr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] + reg[b];};
            ops["addi"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] + b;};  
            ops["mulr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] * reg[b];};
            ops["muli"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] * b;};
            ops["banr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] & reg[b];};
            ops["bani"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] & b;};
            ops["borr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] | reg[b];};
            ops["bori"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] | b;};
            ops["setr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a];};
            ops["seti"] = [](int a, int b, int c, vector<int>& reg){reg[c] = a;};
            ops["gtir"] = [](int a, int b, int c, vector<int>& reg){reg[c] = a > reg[b];};
            ops["gtri"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] > b;};
            ops["gtrr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] > reg[b];};
            ops["eqir"] = [](int a, int b, int c, vector<int>& reg){reg[c] = a == reg[b];};
            ops["eqri"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] == b;};
            ops["eqrr"] = [](int a, int b, int c, vector<int>& reg){reg[c] = reg[a] == reg[b];};

            int ptr =  0;
            int p1 = 0, p2 = 0;
            unordered_set<int> seen;

            while(ptr>=0 && ptr < (int)program.size()){
                /*
                    reg[4] = 123;
                    while(true){
                        reg[4] &= 456;
                        if(reg[4] == 72) break;

                        reg[4] = 0;
                        do{
                            reg[5] = reg[4] | 65536;
                            reg[4] = 678134;
                            while(true){
                                reg[3] = reg[5] & 255;
                                reg[4] += reg[3];
                                reg[4] &= 16777215;
                                reg[4] *= 65899;
                                reg[4] &= 16777215;
                                if(256 > reg[5]) break;
                                reg[3] = 0;
                                do{
                                    reg[2] = reg[3] + 1;
                                    reg[2] *= 256;
                                    reg[2] = reg[2] > reg[5];
                                    if(reg[2] == 1) break;
                                    reg[3]++;
                                }while(true);
                                reg[5] = reg[3];
                            }
                            if(reg[4] == reg[0]) return;
                        }while(true);
                    
                    }
                    

                */

                reg[ip] = ptr;
                auto op = program[ptr];
                if(ptr == 28){
                    if(!p1)p1 = reg[keyip];
                    if(seen.find(reg[keyip]) != seen.end()){
                        return std::to_string(p1) + " " + std::to_string(p2);
                    }else{
                        seen.insert(reg[keyip]);
                        p2 = reg[keyip];
                    }
                }
                
                ops[op.first](op.second[0], op.second[1], op.second[2], reg);
                ptr = reg[ip];
                ptr++;
            }

            return "NOT FOUND";
        }
    }
}

