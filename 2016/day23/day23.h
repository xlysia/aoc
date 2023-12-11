#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace aoc2016{
    namespace day23{
        struct Instruction{
            std::string op;
            std::string x;
            std::string y;
        };

        int factorial(int n){
            if(n==0)return 1;
            return n*factorial(n-1);
        }

        std::string solvedayp1(std::string p, std::vector<int> table);
        void run(){
            std::vector<int> table = {7,0,0,0};
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day23/day23sample",table)=="3");

            int tmp = stoi(solvedayp1("./2016/day23/day23",table));
            std::cout << tmp << std::endl;

            std::cout << "Part 2" << std::endl;
            cout << factorial(12)+ tmp - factorial(7) << endl;
        }

        std::string solvedayp1(std::string p, std::vector<int> table){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            std::vector<Instruction> instructions;
            while(std::getline(std::cin, line)){
                Instruction i;
                std::vector<std::string> x;
                size_t pos;
                line.push_back(' ');
                while((pos=line.find(' '))!=std::string::npos){
                    x.push_back(line.substr(0,pos));
                    line.erase(0,pos+1);
                }
                i.op = x[0];
                i.x = x[1];
                if(x.size()>2)i.y = x[2];
                instructions.push_back(i);
            }
            int i = 0;
            while(i>-1 &&i < (int)instructions.size()){
                auto [op,x,y] = instructions[i];

                if(op == "cpy"){
                    if(x[0] <= 'd' && x[0] >= 'a'){
                        table[y[0]-'a'] = table[x[0]-'a'];
                    }else{
                        table[y[0]-'a'] = std::stoi(x);
                    }
                    i++;
                }else if(op=="inc"){
                    table[x[0]-'a']++;
                    i++;
                }else if(op=="dec"){
                    table[x[0]-'a']--;
                    i++;
                }else if(op =="jnz"){
                    if(x[0] <= 'd' && x[0] >= 'a'){
                        if(table[x[0]-'a']==0)i++;
                        else{
                            i+=std::stoi(y);
                        }
                    }else{
                        if(std::stoi(x)==0)i++;
                        else if(y[0] <= 'd' && y[0] >= 'a'){
                            i+=table[y[0]-'a'];
                        }else{
                            i+=std::stoi(y);
                        }
                    }
                }else if(op == "tgl"){
                    if(x[0] <= 'd' && x[0] >= 'a'){
                        int j = i+table[x[0]-'a'];
                        if(j < 0 || j >= (int)instructions.size()){
                            i++;
                            continue;
                        }
                        auto& [op,x,y] = instructions[j];
                        if(op == "inc"){
                            op = "dec";
                        }else if(op == "dec" || op == "tgl"){
                            op = "inc";
                        }else if(op == "jnz"){
                            op = "cpy";
                        }else if(op == "cpy"){
                            op = "jnz";
                        }
                        i++;
                    }else{
                        i++;
                    }
                }
            }
            return std::to_string(table[0]);
        }

    }
}

