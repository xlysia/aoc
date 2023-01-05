#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <map>
#include "./utils/cvutils.h"

namespace aoc2015{
    namespace day3{
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);

        std::map<char,Point> O = {
            {'<',Point(-1,0)},
            {'>',Point(1,0)},
            {'v',Point(0,1)},
            {'^',Point(0,-1)}
            };
        std::map<Point,int> visited;
        void run(){

            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day3/day3sample")=="2");
            std::cout << solvedayp1("./2015/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day3/day3sample")=="11");
            std::cout << solvedayp2("./2015/day3/day3") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res = 1;
            char c;
            visited.clear();
            Point pos(0,0);
            visited[pos] = 1;
            while(true){
                c='X';
                std::cin >> c;
                if(O.find(c) == O.end()){
                    break;
                }else{
                    pos += O[c];
                    if(visited.find(pos) == visited.end()){
                        res +=1;
                        visited[pos] = 1;
                    }else{
                        visited[pos] +=1;
                    }
                }
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res = 1;
            char c;
            visited.clear();
            Point pos[2] = {Point(0,0),Point(0,0)};

            visited[pos[0]] = 2;
            int idx = 0;
            while(true){
                c='X';
                std::cin >> c;
                if(O.find(c) == O.end()){
                    break;
                }else{
                    pos[idx%2] += O[c];
                    if(visited.find(pos[idx%2]) == visited.end()){
                        res +=1;
                        visited[pos[idx%2]] = 1;
                    }else{
                        visited[pos[idx%2]] +=1;
                    }
                }
                idx++;
            }
            return std::to_string(res);
        }
    }
}