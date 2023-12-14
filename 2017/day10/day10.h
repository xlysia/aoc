#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day10{

        std::string solvedayp1(std::string p,int w);
        void solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day10/day10sample",5)=="12");
            std::cout << solvedayp1("./2017/day10/day10",256) << std::endl;

            std::cout << "Part 2" << std::endl;
            solvedayp2("./2017/day10/day10sample2");
            solvedayp2("./2017/day10/day10");
        }

        void knot(vector<int>& values, int K, int idx){
            int N = values.size();
            int end = idx+K;
            if (end > N){
                vector<int> tmp = vector<int>(values.begin()+idx,values.end());
                tmp.insert(tmp.end(),values.begin(),values.begin()+end-N);
                std::reverse(tmp.begin(),tmp.end());
                for (int i=0;i<K;i++){
                    values[(idx+i)%N] = tmp[i];
                }
            } else {
                std::reverse(values.begin()+idx,values.begin()+end);
            }
        }

        std::string solvedayp1(std::string p, int w){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int K;
            string line;
            // range from 1 to w
            vector<int> values = vector<int>(w);
            std::iota(values.begin(), values.end(), 0);
            int idx = 0;
            int skip = 0;
            while(getline(cin,line,',')){
                K = stoi(line);
                knot(values,K,idx);
                idx = (idx+K+skip++)%w;
            }

            return std::to_string(values[0]*values[1]);
        }

        void solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            string line;
            // range from 1 to w
            vector<int> values = vector<int>(256);
            std::iota(values.begin(), values.end(), 0);
            int idx = 0;
            int skip = 0;
    
            vector<int> lengths;
            getline(cin,line);
            for(char c : line){
                lengths.push_back(c);
            }
            vector<int> vector2 = {17, 31, 73, 47, 23};
            lengths.insert( lengths.end(), vector2.begin(), vector2.end() );
            for(int i = 0; i < 64; ++i){
                for(int K : lengths){
                    knot(values,K,idx);
                    idx = (idx+K+skip++)%256;
                }
            }

            for(int i = 0; i < 16; ++i){
                int x = 0;
                for(int j = 0; j < 16; ++j){
                    x ^= values[i*16+j];
                }
                if(x < 16) std::cout << "0";
                std::cout << std::hex << x;
            }
            std::cout << std::endl;
        }
    }
}

