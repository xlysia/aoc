#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day15{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day15/day15sample")=="5");
            std::cout << solvedayp1("./2016/day15/day15") << std::endl;

            std::cout << "Part 2" << std::endl;
    //        assert (solvedayp2("./2016/day15/day15sample")=="-1");
            std::cout << solvedayp2("./2016/day15/day15") << std::endl;
        }


        bool canPass(const vector<pair<int,int>>& discs, int time){
            for(int i = 0; i < (int)discs.size(); i++){
                if((discs[i].second + time + i + 1) % discs[i].first != 0){
                    return false;
                }
            }
            return true;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            vector<pair<int,int>> discs;
            while(getline(cin,line)){
                std::istringstream iss(line);
                std::string s;
                int a,b;
                iss >> s >> s >> s >> a >> s >> s >> s >> s >> s >> s >> s >> b;
                
                discs.push_back({a,b});


            }

            int ans = 0;
            while(1){
                if(canPass(discs,ans)){
                    break;
                }
                ans++;
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            vector<pair<int,int>> discs;
            while(getline(cin,line)){
                std::istringstream iss(line);
                std::string s;
                int a,b;
                iss >> s >> s >> s >> a >> s >> s >> s >> s >> s >> s >> s >> b;
                
                discs.push_back({a,b});


            }
            discs.push_back({11,0});
            int ans = 0;
            while(1){
                if(canPass(discs,ans)){
                    break;
                }
                ans++;
            }

            return std::to_string(ans);
        }
    }
}

