#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <cmath>
#include <vector>
#include <deque>

using namespace std;

namespace aoc2016{
    namespace day19{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day19/day19sample")=="3");
            std::cout << solvedayp1("./2016/day19/day19") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day19/day19sample")=="2");
            std::cout << solvedayp2("./2016/day19/day19") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int n;
            cin >> n;
            int ans = 2*(n - pow(2,floor(log2(n))))+1;
            return to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int n;
            cin >> n;
            
            deque<int> part1;
            deque<int> part2;

            for(int i = 0; i < n/2;i++)part1.push_back(i);
            for(int i = n/2;i<n;i++)part2.push_back(i);

            while(--n){
                if(part1.size()>part2.size())part1.pop_back();
                else part2.pop_front();

                // turn 
                part2.push_back(part1.front());
                part1.pop_front();
                part1.push_back(part2.front());
                part2.pop_front();
            }
            
            if(part2.size())return to_string(part2.front()+1);
            return std::to_string(part1.front()+1);
        }
    }
}

