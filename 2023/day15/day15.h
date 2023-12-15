#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector> 
#include <unordered_map>
#include <algorithm>


using namespace std;

namespace aoc2023{
    namespace day15{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day15/day15sample")=="1320");
            std::cout << solvedayp1("./2023/day15/day15") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day15/day15sample")=="145");
            std::cout << solvedayp2("./2023/day15/day15") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans = 0;
            
            while(getline(cin,line,',')){
                int x = 0;
                for(char c : line){
                    x = (c+x)*17 % 256;
                }
                ans += x;
            }
            
            
            return std::to_string(ans);
        }

        int getKey(string& lens){
            int x = 0;
            for(char c : lens){
                x = (c+x)*17 % 256;
            }
            return x;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            unordered_map<string,int> values;
            vector<vector<string>> boxes = vector<vector<string>>(256,vector<string>());

            while(getline(cin,line,',')){
                string lens = "";
                for(char c : line){
                    if(c == '-' || c == '=')break;
                    lens += c;
                }
                int key = getKey(lens);

                auto it = find(boxes[key].begin(),boxes[key].end(),lens);
                if(line[lens.size()] == '-' && it != boxes[key].end() ){
                    boxes[key].erase(it);
                }
                if(line[lens.size()] == '='){
                    if(it == boxes[key].end())boxes[key].push_back(lens);
                    values[lens] = stoi(line.substr(lens.size()+1));
                }

            }

            int ans = 0;
            for(int i = 0; i < 256; i++){
                for(int j = 0; j < (int) boxes[i].size();j++){
                    ans += values[boxes[i][j]]*(j+1)*(i+1);
                }
            }

            return to_string(ans);
        }
    }
}

