#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <regex>
#include <string>

namespace aoc2024{
    namespace day3{

        std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
        std::regex do_pattern(R"(do\(\))");
        std::regex dont_pattern(R"(don't\(\))");
        std::regex combined_pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2024/day3/day3sample")=="161");
            std::cout << solvedayp1("./2024/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2024/day3/day3sample2")=="48");
            std::cout << solvedayp2("./2024/day3/day3") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::smatch matches;
            long long ans = 0;


            while(std::getline(std::cin, line)){
                auto begin = std::sregex_iterator(line.begin(), line.end(), mul_pattern);
                auto end = std::sregex_iterator();

                for (std::sregex_iterator i = begin; i != end; ++i) {
                    matches = *i;
                    int x = std::stoi(matches[1].str());
                    int y = std::stoi(matches[2].str());
                    ans += x * y;
                }
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            std::smatch matches;
            long long ans = 0;

            bool mul_enabled = true;

            while(std::getline(std::cin, line)){
                    
                auto begin = std::sregex_iterator(line.begin(), line.end(), combined_pattern);
                auto end = std::sregex_iterator();

                for (std::sregex_iterator i = begin; i != end; ++i) {
                    matches = *i;
                    std::string match_str = matches.str();
                    if (std::regex_match(match_str, do_pattern)) {
                        mul_enabled = true;
                    } else if (std::regex_match(match_str, dont_pattern)) {
                        mul_enabled = false;
                    } else if (mul_enabled && std::regex_match(match_str, mul_pattern)) {
                        int x = std::stoi(matches[1].str());
                        int y = std::stoi(matches[2].str());
                        ans += x * y;
                    }
                }
            }

            return std::to_string(ans);
        }
    }
}

