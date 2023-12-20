#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day23{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2017/day23/day23") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day23/day23") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int registers[8] = {0,0,0,0,0,0,0,0};
            int i = 0;
            
            using instruction = tuple<string, string, string>;

            vector<instruction> instructions;
            while (getline(cin, line)) {
                stringstream ss(line);
                string op, x, y;
                ss >> op >> x >> y;
                instructions.emplace_back(op, x, y);
            }

            int N = instructions.size();
            int ans = 0;
            while(i>-1 && i < N){
                auto [op, x, y] = instructions[i];
                if(op == "set"){
                    if(isalpha(y[0])) registers[x[0]-'a'] = registers[y[0]-'a'];
                    else registers[x[0]-'a'] = stoi(y);
                }else if(op == "sub"){
                    if(isalpha(y[0])) registers[x[0]-'a'] -= registers[y[0]-'a'];
                    else registers[x[0]-'a'] -= stoi(y);
                }else if(op == "mul"){
                    if(isalpha(y[0])) registers[x[0]-'a'] *= registers[y[0]-'a'];
                    else registers[x[0]-'a'] *= stoi(y);
                    ans++;
                }else if(op == "jnz"){
                    if(isalpha(x[0])){
                        if(registers[x[0]-'a'] != 0){
                            if(isalpha(y[0])) i += registers[y[0]-'a']-1;
                            else i += stoi(y)-1;
                        }
                    }else{
                        if(stoi(x) != 0){
                            if(isalpha(y[0])) i += registers[y[0]-'a']-1;
                            else i += stoi(y)-1;
                        }
                    }
                }
                i++;
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){            
            // get pattern by running the program
            // and looking at the values of b
            // and c when the program starts
            // we see loops :) and figuring the pattern


            int mini = sqrt(stoi(solvedayp1(p)))+2;            
            mini = 100 * mini + 100000;
    
            int ans = 0;
            for(int i = mini; i <= mini+17000; i+=17){
                bool isPrime = true;
                for(int j = 2; j*j <= i; j++){
                    if(i%j == 0){
                        isPrime = false;
                        break;
                    }
                }
                if(!isPrime) ans++;
            }

            return std::to_string(ans);
        }
    }
}

