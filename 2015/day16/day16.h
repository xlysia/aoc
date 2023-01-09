#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <map>

namespace aoc2015{
    namespace day16{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
           // assert (solvedayp1("./2015/day16/day16sample")=="-3");
            std::cout << solvedayp1("./2015/day16/day16") << std::endl;

            std::cout << "Part 2" << std::endl;
          //  assert (solvedayp2("./2015/day16/day16sample")=="-1");
            std::cout << solvedayp2("./2015/day16/day16") << std::endl;
        }

        std::map<std::string,int> dna;
        
        struct Sue{
            int id;
            std::map<std::string,int> known;
            bool isMatching(){
                for(auto it : known){
                    if(dna[it.first] != it.second)return false;
                }
                return true;
            }
            bool isMatching2(){
                for(auto it : known){
                    if(it.first == "cats" || it.first == "trees"){
                        if(dna[it.first] >= it.second) return false;
                    }
                    else if(it.first == "pomeranians" || it.first == "goldfish"){
                        if(dna[it.first] <= it.second) return false;
                    }
                    else if(dna[it.first] != it.second)return false;
                }
                return true;
            }
        };
        std::vector<Sue> sues;
        void parseRule(){
            std::ifstream in("./2015/day16/rule");
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            dna.clear();
            while(std::getline(std::cin,line)){
                size_t pos;
                std::string comp = "";
                pos = line.find(": ");
                comp = line.substr(0, pos);
                line = line.erase(0, pos + 2);
                dna[comp] = std::atoi(line.c_str());
            }
        }

        void parse(){
            sues.clear();
            int i = 1;
            std::string line;
            while(std::getline(std::cin,line)){
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos-1).c_str());
                    line.erase(0, pos + 1);
                }
                x.push_back(line);
                
                Sue sue;
                sue.id = i;
                for(int i = 2 ; i < (int)x.size()-1;i+=2 )
                {
                    sue.known[x[i]] = std::atoi(x[i+1].c_str());
                }
                sues.push_back(sue);
                i++;
            }
        }
        std::string solvedayp1(std::string p){
            parseRule();
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            for(Sue& s : sues){
                if(s.isMatching())return std::to_string(s.id);
            }
            return std::to_string(-1);
        }

        std::string solvedayp2(std::string p){
            parseRule();
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            for(Sue& s : sues){
                if(s.isMatching2())return std::to_string(s.id);
            }
            return std::to_string(-1);
        }
    }
}

