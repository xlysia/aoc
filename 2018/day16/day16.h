#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2018{
    namespace day16{

        void solveday(std::string p);
        void run(){
            solveday("./2018/day16/day16");
        }

        void solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);


            typedef void (*opcodes)(vector<int>& regs, vector<int>& op);
            vector<opcodes> operands ={
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] + regs[op[2]];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] + op[2];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] * regs[op[2]];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] * op[2];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] & regs[op[2]];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] & op[2];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] | regs[op[2]];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]] | op[2];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = regs[op[1]];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = op[1];},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (op[1] > regs[op[2]]) ? 1 : 0;},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (regs[op[1]] > op[2]) ? 1 : 0;},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (regs[op[1]] > regs[op[2]]) ? 1 : 0;},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (op[1] == regs[op[2]]) ? 1 : 0;},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (regs[op[1]] == op[2]) ? 1 : 0;},
                [](vector<int>& regs, vector<int>& op){regs[op[3]] = (regs[op[1]] == regs[op[2]]);}
            };

            int p1 =  0;
            set<int> initset;
            vector<bool> settled(operands.size(), false);
            for(size_t i = 0; i < operands.size(); i++){
                initset.insert(i);     
            }

            vector<set<int>> possible(operands.size(), initset);
            
            while(!line.empty()){
                std::istringstream iss(line);
                vector<int> before = {0,0,0,0};
                vector<int> after = {0,0,0,0};
                vector<int> op = {0,0,0,0};
                char c;
                iss >> line >> c >> before[0] >> c >> before[1] >> c >> before[2] >> c >> before[3];
                getline(std::cin, line);
                iss = std::istringstream(line);
                iss >> op[0] >> op[1] >> op[2] >> op[3];
                getline(std::cin, line);
                iss = std::istringstream(line);
                iss >> line >> c >> after[0] >> c >> after[1] >> c >> after[2] >> c >> after[3];
                getline(std::cin, line);
                getline(std::cin, line);
            
                int count = 0;
                for(size_t i = 0; i < operands.size(); i++){
                    vector<int> regs = {before[0], before[1], before[2], before[3]};
                    operands[i](regs, op);
                    if(regs == after){
                        count++;
                    }else{
                        if(possible[op[0]].find(i) != possible[op[0]].end()){
                            possible[op[0]].erase(i);
                        }
                    }
                }
                if(count >= 3)p1++;
            }
            cout << "Part 1: " << std::to_string(p1) << endl;

            int N = operands.size();
            while(N){
                for(int i = 0; i < (int)operands.size(); i++){
                    if(possible[i].size() == 1){
                        if(settled[*possible[i].begin()] == true)continue;
                        settled[*possible[i].begin()] = true;
                        N--;
                    }else{
                        for(auto it = possible[i].begin(); it != possible[i].end(); it++){
                            if(settled[*it] == true){
                                possible[i].erase(it);
                                it--;
                            }
                        }
                    }
                    
                }
            }
            
            getline(std::cin, line);

            vector<int> regs = {0,0,0,0};
            while(getline(std::cin, line)){
                std::istringstream iss(line);
                vector<int> op = {0,0,0,0};
                iss >> op[0] >> op[1] >> op[2] >> op[3];
                operands[*possible[op[0]].begin()](regs, op);
            }

            cout << "Part 2: " << regs[0] << endl;
        }
    }
}

