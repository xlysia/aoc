#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2018{
    namespace day4{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day4/day4sample")=="240");
            std::cout << solvedayp1("./2018/day4/day4") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day4/day4sample")=="4455");
            std::cout << solvedayp2("./2018/day4/day4") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            unordered_map<int,int> guards;
            unordered_map<int,vector<int>> naps;
            int maxi = 0;
            vector<string> lines;
            while (std::getline(std::cin, line)) {
                lines.push_back(line);
            }

            sort(lines.begin(),lines.end());
            for(auto line:lines){
                std::istringstream iss(line);
                std::string s,minutes,key;
                iss >> s >> minutes >> key;
                int guard;
                int start;
                if (key=="Guard"){
                    iss >>  s;
                    guard = stoi(s.substr(1)); 
                    if (guards.find(guard)==guards.end()){
                        guards[guard] = 0;
                        naps[guard] = vector<int>(60,0);
                    }
                }
                else if (key=="falls"){
                    start = stoi(minutes.substr(3,2));
                }
                else if (key=="wakes"){
                    int end = stoi(minutes.substr(3,2));
                    guards[guard] += end-start;
                    for(int i=start;i<end;i++){
                        naps[guard][i]++;
                    }
                    if( guards[guard] > guards[maxi]){
                        maxi = guard;
                    }
                }
                else{
                    std::cout << "ERROR" << std::endl;
                }
            }
            int minute = 0;
            for(int i=0;i<60;i++){
                if (naps[maxi][i]>naps[maxi][minute]){
                    minute = i;
                }
            }
            return std::to_string(maxi*minute);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            map<int,vector<int>> naps;

            vector<string> lines;
            while (std::getline(std::cin, line)) {
                lines.push_back(line);
            }

            int guard;

            sort(lines.begin(),lines.end());
            for(auto line:lines){
                std::istringstream iss(line);
                std::string s,minutes,key;
                iss >> s >> minutes >> key;
                int start;
                if (key=="Guard"){
                    iss >>  s;
                    guard = stoi(s.substr(1)); 
                    if (naps.find(guard)==naps.end()){
                        naps[guard] = vector<int>(60,0);
                    }
                }
                else if (key=="falls"){
                    start = stoi(minutes.substr(3,2));
                }
                else if (key=="wakes"){
                    int end = stoi(minutes.substr(3,2));
                    for(int i=start;i<end;i++){
                        naps[guard][i]++;
                    }
                }
                else{
                    std::cout << "ERROR" << std::endl;
                }
            }

            
            int maxinap = 0;
            for(auto nap:naps){
                for(int i=0;i<60;i++){
                    if (nap.second[i]>naps[guard][maxinap]){
                        guard = nap.first;
                        maxinap = i;
                    }
                }
            }

            return std::to_string(guard*maxinap);
        }
    }
}

