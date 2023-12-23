#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>

using namespace std;

namespace aoc2018{
    namespace day9{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            
            assert (solvedayp1("./2018/day9/day9sample")=="8317");
            std::cout << solvedayp1("./2018/day9/day9") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2018/day9/day9") << std::endl;
        }

        void rotate(deque<long long>& deq, int d) 
        { 
            // Push first d elements 
            // from last to the beginning 
            if(d > 0) 
            { 
                for (int i = 0; i < d; i++) { 
                    deq.push_front(deq.back()); 
                    deq.pop_back(); 
                } 
            }else if(d < 0) 
            { 
                // Push last d elements 
                // from the beginning to the end 
                for (int i = 0; i < -d; i++) { 
                    deq.push_back(deq.front()); 
                    deq.pop_front(); 
                } 
            }
        } 

        long long solve(int players, int lastmarble){
            deque<long long> circle;
            vector<long long> scores = vector<long long>(players, 0);
            
            circle.push_back(0);

            for(int m = 1; m <= lastmarble; m++) {
                if (m % 23) {
                    rotate(circle,-1);
                    circle.push_back(m);
                } else {
                    rotate(circle,7);
                    scores[m % players] += m + circle.back();
                    circle.pop_back();
                    rotate(circle,-1);
                }
            }

            return *max_element(scores.begin(), scores.end());
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // 459 players; last marble is worth 72103 points
            int players, lastmarble;
            std::cin >> players >> line >> line >> line >> line >> line >> lastmarble >> line;

            return std::to_string(solve(players, lastmarble));
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // 459 players; last marble is worth 72103 points
            int players, lastmarble;
            std::cin >> players >> line >> line >> line >> line >> line >> lastmarble >> line;

            return std::to_string(solve(players, lastmarble * 100));
        }
    }
}

