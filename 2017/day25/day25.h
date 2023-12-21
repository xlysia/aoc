#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>

using namespace std;

namespace aoc2017{
    namespace day25{

        std::string solvedayp1(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day25/day25sample")=="3");
            std::cout << solvedayp1("./2017/day25/day25") << std::endl;
        
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            getline(cin,line);
            line.pop_back();
            int state = line.back() - 'A'; // initial state
            getline(cin,line);
            stringstream ss(line);
            uint N;
            ss >> line >> line >> line >> line >> line >> N;

            vector<vector<vector<int>>> turing;
           
            // parse states
            while(cin.good()){
                getline(cin,line);
                getline(cin,line);

                turing.push_back({{0,0,0},{0,0,0}});
                for(int i = 0; i <2;i++){
                    getline(cin,line);
                    for(int j = 0; j < 3;j++){
                        getline(cin,line);
                        line = line.substr(line.find_last_of(' ')+1);
                        line.pop_back();
                        if(isalpha(line.back())){
                            if(isupper(line[0]))turing.back()[i][j] = line.back()-'A';
                            else turing.back()[i][j] = line[0]=='r'?1:-1;
                        } 
                        else turing.back()[i][j] = line.back()-'0';
                    }
                }
            }

            int ans =  0;
            vector<bool> registers(N,false);
            int pos = N/2;
            
            while(N--){
                vector<int> turn = turing[state][registers[pos]];
                state = turn[2];
                ans += turn[0] - registers[pos];
                registers[pos] = turn[0];
                
                pos += turn[1];
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int ans = 0;
            return std::to_string(ans);
        }
    }
}

