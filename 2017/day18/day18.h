#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day18{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day18/day18sample")=="4");
            std::cout << solvedayp1("./2017/day18/day18") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day18/day18") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            using instruction = tuple<string, string, string>;

            vector<instruction> instructions;
            while (getline(cin, line)) {
                stringstream ss(line);
                string op, x, y;
                ss >> op >> x >> y;
                instructions.emplace_back(op, x, y);
            }

            int N = instructions.size();

            int last_sound = 0;
            map<string, long long> registers;
            int ans =  0;
            int i = 0;
            while(i >= 0 && i < N) {
                auto [op, x, y] = instructions[i];
                if (op == "snd") {
                    last_sound = registers[x];
                } else if (op == "set") {
                    registers[x] = isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "add") {
                    registers[x] += isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "mul") {
                    registers[x] *= isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "mod") {
                    registers[x] %= isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "rcv") {
                    if (registers[x] != 0) {
                        ans = last_sound;
                        break;
                    }
                } else if (op == "jgz") {
                    if ((isalpha(x[0])?registers[x]:stoi(x)) > 0) {
                        i += isalpha(y[0]) ? registers[y] : stoi(y);
                        continue;
                    }
                }
                i++;
            }
            return std::to_string(ans);
        }

        bool loop(vector<tuple<string,string,string>>& instructions, map<string,long long>& registers, int& i ,queue<int>& snd,queue<int>& rcv){
            bool b = false; 
            int N = instructions.size();
    
            while(i >= 0 && i < N) {
                auto [op, x, y] = instructions[i];
                if (op == "snd") {
                    snd.push(isalpha(x[0])?registers[x]:stoi(x));
                } else if (op == "set") {
                    registers[x] = isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "add") {
                    registers[x] += isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "mul") {
                    registers[x] *= isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "mod") {
                    registers[x] %= isalpha(y[0]) ? registers[y] : stoll(y);
                } else if (op == "rcv") {
                    if(rcv.empty()){
                        return b;
                    }else{
                        registers[x] = rcv.front();
                        rcv.pop();
                    }
                } else if (op == "jgz") {
                    if ((isalpha(x[0])?registers[x]:stoi(x)) > 0) {
                        i += isalpha(y[0]) ? registers[y] : stoi(y);
                        b = true;
                        continue;
                    }
                }
                i++;
                b = true;
            }

            return b;
        }


        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            using instruction = tuple<string, string, string>;

            vector<instruction> instructions;
            while (getline(cin, line)) {
                stringstream ss(line);
                string op, x, y;
                ss >> op >> x >> y;
                instructions.emplace_back(op, x, y);
            }

            map<string, long long> registers1,registers2;
            registers1["p"] = 0;
            registers2["p"] = 1;
            long long ans =  0;
            int i1 = 0, i2 = 0;
            queue<int> q1, q2;
            bool b = true;
            int N = instructions.size();
            while(b){
                b = loop(instructions, registers1, i1 , q2, q1);
                if(i1 < 0 || i1 >= N) break;
                int tmp = q1.size();
                b |= loop(instructions, registers2, i2 , q1, q2);
                ans += q1.size() - tmp;
                if(i2 < 0 || i2 >= N) break;
            }
            
            return std::to_string(ans);
        }
    }
}

