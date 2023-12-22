#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2021{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2021/day1/day1sample")=="7");
            std::cout << solvedayp1("./2021/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2021/day1/day1sample")=="5");
            std::cout << solvedayp2("./2021/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int prev,val;
            cin >> prev;
            int ans = 0;
            while(cin.good()){
                cin >> val;
                if(val>prev)ans++;
                prev = val;
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            
            int val;
            deque<int> q;
            int sum = 0;
            for(int i = 0; i < 3; i++){
                cin >> val;
                sum += val;
                q.push_back(val);
            }
            int ans = 0;
            while(cin.good()){
                cin >> val;
                if(sum < sum +val - q.front()) ans++;
                sum += val - q.front();
                q.pop_front();
                q.push_back(val);
            }
            return std::to_string(ans);
        }
    }
}

