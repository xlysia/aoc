#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

namespace aoc2018{
    namespace day19{

        std::string solveday(std::string p,int reg0=0);

        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solveday("./2018/day19/day19sample",0)=="6");
            std::cout << solveday("./2018/day19/day19",0) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solveday("./2018/day19/day19",1) << std::endl;
        }

        std::string solveday(std::string p,int reg0){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<int> reg(6,0);
            reg[0] = reg0;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int ip;
            ss >> line >> ip;

            std::vector<std::pair<std::string, std::vector<int>>> program;
            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::string op;
                ss >> op;
                std::vector<int> args(3,0);
                ss >> args[0] >> args[1] >> args[2];
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
            while(ptr>=0 && ptr < (int)program.size()){
                /*
                    reg[2] = 1;
                    reg[1] = reg[3];
                    reg[1] = reg[5] == reg[1];
                    reg[4] += reg[1];

                    reg[0] += reg[3];
                    reg[2]++;
                    reg[1] = reg[2] > reg[5];
                    reg[4] += reg[1];
                */
                if(ptr == 3 && reg[3] != 0){
                    int ans = 0;
                    for(int i = 0; i < reg[5]; i++){
                        if(reg[5] % (i+1) == 0){
                            ans += i+1;
                        }
                    }
                    return std::to_string(ans);
                }

                reg[ip] = ptr;
                auto op = program[ptr];
                ops[op.first](op.second[0], op.second[1], op.second[2], reg);
                ptr = reg[ip];
                ptr++;
            }
            return std::to_string(reg[0]);
        }
    }
}

