#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day8{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day8/day8sample")=="1");
            std::cout << solvedayp1("./2017/day8/day8") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day8/day8sample")=="10");
            std::cout << solvedayp2("./2017/day8/day8") << std::endl;
        }

        int getKey(std::string& token){
            int key = 0;
            for(char c : token){
                key *= 26;
                key += (c-'a');
            }
            return key;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            vector<int> registers(26*26*26,0);

            while(getline(std::cin, line)){
                std::istringstream iss(line);
                std::string token;
                iss >> token;
                int key = getKey(token);
                iss >> token;
                int op;
                iss >> op;
                op*=(token[0]=='i')?1:-1;
                iss >> token >> token;
                int key2 = getKey(token);
                iss >> token;
                int val;
                iss >> val;

                if(token == ">" && registers[key2] > val) registers[key] += op;
                if(token == "<" && registers[key2] < val) registers[key] += op;
                if(token == ">=" && registers[key2] >= val) registers[key] += op;
                if(token == "<=" && registers[key2] <= val) registers[key] += op;
                if(token == "==" && registers[key2] == val) registers[key] += op;
                if(token == "!=" && registers[key2] != val) registers[key] += op;
            }

            return std::to_string(*std::max_element(registers.begin(), registers.end()));
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            vector<int> registers(26*26*26,0);
            int ans = 0;
            while(getline(std::cin, line)){
                std::istringstream iss(line);
                std::string token;
                iss >> token;
                int key = getKey(token);
                iss >> token;
                int op;
                iss >> op;
                op*=(token[0]=='i')?1:-1;
                iss >> token >> token;
                int key2 = getKey(token);
                iss >> token;
                int val;
                iss >> val;

                if(token == ">" && registers[key2] > val) registers[key] += op;
                if(token == "<" && registers[key2] < val) registers[key] += op;
                if(token == ">=" && registers[key2] >= val) registers[key] += op;
                if(token == "<=" && registers[key2] <= val) registers[key] += op;
                if(token == "==" && registers[key2] == val) registers[key] += op;
                if(token == "!=" && registers[key2] != val) registers[key] += op;
                ans = std::max(ans, registers[key]);
            }

            return std::to_string(ans);
        }
    }
}

