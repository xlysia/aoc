#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <unordered_map>

using namespace std;

namespace aoc2023{
    namespace day18{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day18/day18sample")=="62");
            std::cout << solvedayp1("./2023/day18/day18") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day18/day18sample")=="952408144115");
            std::cout << solvedayp2("./2023/day18/day18") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            unordered_map<char,pair<int,int>> dirs{{'U',{-1,0}},{'D',{1,0}},{'R',{0,1}},{'L',{0,-1}}};

            int ans =  0;
            int perim = 0;

            int x = 0;
            int y = 0;
            int xprev = -1,yprev = -1;
            
            while(getline(cin, line)){
                stringstream iss(line);
                char dir;
                int val;
                string color;
                iss >> dir >> val >> color;

                int ox = dirs[dir].first;
                int oy = dirs[dir].second;

                xprev = x;
                yprev = y;
                x += ox*val;
                y += oy*val;

                perim+=val;

                ans += (x+xprev)*(y-yprev);
            }

            ans = (abs(ans) + perim)/2+1;

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            pair<int,int> dirs[4] = {{0,1},{1,0},{0,-1},{-1,0}};

            long long ans =  0;
            long long perim = 0;

            long long  x = 0;
            long long  y = 0;
            long long  xprev = -1,yprev = -1;
            
            while(getline(cin, line)){
                stringstream iss(line);
                char dir;
                int val;
                string color;
                iss >> dir >> val >> color;

                // hexa to decimal
                color.pop_back();
                dir = color.back();
                color = color.substr(2,color.size()-3);
                val = stoi(color, nullptr, 16);
                
                int ox = dirs[dir-'0'].first;
                int oy = dirs[dir-'0'].second;

                xprev = x;
                yprev = y;
                x += ox*val;
                y += oy*val;

                perim+=val;

                ans += (x+xprev)*(y-yprev);
            }

            ans = (abs(ans) + perim)/2+1;

            return std::to_string(ans);
        }
    }
}

