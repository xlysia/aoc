#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector> 
#include <algorithm>
#include <unordered_map>

namespace aoc2024{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2024/day1/day1sample")=="11");
            std::cout << solvedayp1("./2024/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2024/day1/day1sample")=="31");
            std::cout << solvedayp2("./2024/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            std::vector<int> list1;
            std::vector<int> list2;

            while(getline(std::cin, line)){
                int a,b;
                std::stringstream(line) >> a >> b;
                list1.push_back(a);
                list2.push_back(b);
            }

            std::sort(list1.begin(), list1.end());
            std::sort(list2.begin(), list2.end());

            int ans =  0;

            for(size_t i = 0; i < list1.size();i++)ans += abs(list1[i]-list2[i]);

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            std::unordered_map<int,int> map1;
            std::unordered_map<int,int> map2;

            while(getline(std::cin, line)){
                int a,b;
                std::stringstream(line) >> a >> b;
                map1[a]++;
                map2[b]++;
            }
            int ans = 0;

            for(auto a : map1){
                if(map2.find(a.first)!=map2.end())ans+=a.first*a.second*map2[a.first];
            }
            
            return std::to_string(ans);
        }
    }
}

