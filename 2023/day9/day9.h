#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2023{
    namespace day9{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day9/day9sample")=="114");
            std::cout << solvedayp1("./2023/day9/day9") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day9/day9sample")=="2");
            std::cout << solvedayp2("./2023/day9/day9") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans =  0;

            while(getline(std::cin, line)){
                std::stringstream ss(line);
                
                vector<int> values;
                bool allzeroes = true;
                while(ss.good()){
                    values.emplace_back();
                    ss >> values.back();
                    if(values.back() != 0) allzeroes = false;
                }
                
                int n = values.size();
                int j = 0;
                while(!allzeroes){
                    allzeroes = true;
                    j++;
                    for(int i = 0; i < n-j;i++){
                        values[i] = values[i+1]-values[i];
                        if(values[i] != 0) allzeroes = false;
                    }
                }
                ans += accumulate(values.begin(), values.end(), 0);

            }


            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans =  0;

            while(getline(std::cin, line)){
                std::stringstream ss(line);
                
                vector<int> values;
                bool allzeroes = true;
                while(ss.good()){
                    values.emplace_back();
                    ss >> values.back();
                    if(values.back() != 0) allzeroes = false;
                }
                
                int n = values.size();
                int j = 0;
                while(!allzeroes){
                    allzeroes = true;
                    j++;
                    for(int i = n-1; i >= j;i--){
                        values[i] = values[i]-values[i-1];
                        if(values[i] != 0) allzeroes = false;
                    }
                }
                int tmp = 0;
                for(int i = n-2; i >= 0; i--){
                    tmp = values[i] - tmp;
                }
                ans += tmp;
            }


            return std::to_string(ans);
        }
    }
}

