#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day4{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2017/day4/day4") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day4/day4") << std::endl;
        }

        bool isValid(std::string& s){
            std::istringstream iss(s);
            std::string word;
            std::unordered_set<std::string> book;
            while(iss >> word){
                if(book.find(word) != book.end()){
                    return false;
                }
                book.insert(word);
            }
            return true;
        }

        bool isValid2(std::string& s){
            std::istringstream iss(s);
            std::string word;
            std::unordered_set<std::string> book;
            while(iss >> word){
                sort(word.begin(), word.end());
                if(book.find(word) != book.end()){
                    return false;
                }
                book.insert(word);
            }
            return true;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans = 0;
            while(getline(std::cin, line)){
                ans += isValid(line);
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans = 0;
            while(getline(std::cin, line)){
                ans += isValid2(line);
            }
            return std::to_string(ans);
        }
    }
}

