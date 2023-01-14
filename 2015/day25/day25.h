#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

namespace aoc2015{
    namespace day25{

        std::string solvedayp1(std::string p);

        int getIdx(int row, int column){
            return (row+column-1)*(row+column)/2 - row+1;
        }

        void run(){

            std::cout << "Part 1" << std::endl;
            assert (getIdx(3,1)==4);
            assert (getIdx(1,5)==15);
            assert (getIdx(2,3)==9);
            assert (getIdx(3,4)==19);
            assert (getIdx(4,2)==12);
            std::cout << solvedayp1("./2015/day25/day25") << std::endl;

        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int row,column;
            std::vector<int> x;
            long res = 0;

            std::string line;
            while (std::cin >> line) {
                if (std::stringstream(line) >> res)
                    x.push_back(res);
                line = "";
            }
            row = x[0];
            column = x[1];
            int index = getIdx(row,column);

            res = 20151125;
            for(int i = 2 ; i <= index;i++){
                res = (res*252533)%33554393;
            }
            return std::to_string(res);
        }
    }
}

