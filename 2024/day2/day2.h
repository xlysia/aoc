#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2024{
    namespace day2{

        bool issafe(std::vector<int>& report){
            int level,sign;

            level = report[0];
            sign = report[1] > level ? 1 : -1;
            for(size_t i = 1; i < report.size(); i++){

                if(abs(report[i] - level) < 1 || abs(report[i] - level) > 3){
                    return false;
                }
                if((report[i] - level)/abs(report[i]-level) != sign){
                    return false;
                }
                level = report[i];
            }
            return true;
        }

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2024/day2/day2sample")=="2");
            std::cout << solvedayp1("./2024/day2/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2024/day2/day2sample")=="4");
            std::cout << solvedayp2("./2024/day2/day2") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int ans = 0;
            while(std::getline(std::cin, line)){
                std::stringstream ss(line);

                std::vector<int> report;
                int n;
                while(ss >> n){
                    report.push_back(n);
                }
                ans+= issafe(report);
            }


            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int ans = 0;

            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::vector<int> report;
                int n;
                while(ss >> n){
                    report.push_back(n);
                }
                
                if(issafe(report)){
                    ans++;
                    continue;
                }
                for(int i = 0; i < (int)report.size(); i++){
                    std::vector<int> r = report;
                    r.erase(r.begin()+i);
                    if(issafe(r)){
                        ans++;
                        break;
                    }
                }
            }

            return std::to_string(ans);
        }
    }
}

