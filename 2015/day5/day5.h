#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>

namespace aoc2015{
    namespace day5{
        bool isnice(std::string s);
        bool isnice2(std::string s);
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day5/day5sample")=="2");
            std::cout << solvedayp1("./2015/day5/day5") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day5/day5sample2")=="2");
            std::cout << solvedayp2("./2015/day5/day5") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;

            while(std::getline(std::cin,line)){
                res+= isnice(line);
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;

            while(std::getline(std::cin,line)){
                res+= isnice2(line);
            }
            return std::to_string(res);
        }

        bool isnice(std::string s){
            int nbvowel = 0;
            for(char c : "aeiou")nbvowel+= std::count(s.begin(), s.end(), c);
            if(nbvowel < 3) return false;
            bool dinarow = false;
            for(char c : "abcdeifghijklmnopqrstuvwxyz"){
                std::string t = "";
                t.push_back(c);
                t.push_back(c);
                size_t found = s.find(t);
                dinarow|= found!=std::string::npos;
            }
            if(!dinarow)return false;
            bool check = false;
            for(auto c : {"ab","cd","pq","xy"})check|=s.find(c)!=std::string::npos;
            if(check)return false;
            return true;
        }

        bool isnice2(std::string s){
            bool c1 = false;
            for(int i = 0 ; i < (int)s.size()-2;i++){
                c1|=s[i]==s[i+2];
            }
            bool c2 = false;
            for(int i = 0 ; i < (int)s.size()-1;i++){
                c2|= s.substr(i+2,s.size()).find(s.substr(i,2))!=std::string::npos;
            }
            return c1 && c2;
        }
    }
}
