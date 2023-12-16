#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day17{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day17/day17sample")=="638");
            std::cout << solvedayp1("./2017/day17/day17") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day17/day17") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int spin;
            cin >> spin;

            int pos = 0;
            vector<int> buffer = {0};

            for(int i = 1; i <= 2017; i++){
                pos = (pos + spin) % buffer.size();
                buffer.insert(buffer.begin() + pos + 1, i);
                pos++;
            }

            return std::to_string(buffer[pos+1]);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int spin;
            cin >> spin;

            int pos = 0;
            int ans = 0;
            for(int i = 1; i <= 50000000; i++){
                pos = (pos + spin) % i;
                if(++pos == 1)ans = i;
            }

            return std::to_string(ans);
        }
    }
}

