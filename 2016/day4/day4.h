#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day4{

        struct room{
            std::string name = "";
            std::map<char,int> dict = {};
            std::string checksum;
            int id;
        };

        std::string decypher(room r);
        std::string solvedayp1(std::string p);
        void run(){
            std::cout << "Part 1&2" << std::endl;
            assert (decypher({"qzmt zixmtkozy ivhz",{},"",343})=="very encrypted name");
            assert (solvedayp1("./2016/day4/day4sample")=="1514");
            std::cout << solvedayp1("./2016/day4/day4") << std::endl;
        }
  
        std::vector<room> HQ;

        void parse(){
            HQ.clear();
            std::string line;
            while(std::getline(std::cin,line)){
                size_t pos;
                room r;
                while((pos = line.find("-")) != std::string::npos){
                    r.name += line.substr(0,pos) + " ";
                    for(char c : line.substr(0,pos)){
                        if(r.dict.find(c) == r.dict.end()){
                            r.dict[c]=0;
                        }
                        r.dict[c]++;
                    }
                    line.erase(0,pos+1);
                }
                r.name.pop_back();
                std::stringstream ss(line);
                ss >> r.id;
                ss >> line;
                r.checksum = line.substr(1,line.size());
                r.checksum.pop_back();
                HQ.push_back(r);
            }
        }


        bool isdecoy(room r){
            std::vector<std::pair<char, int>> pairs;
            for (auto itr = r.dict.begin(); itr != r.dict.end(); ++itr)
                pairs.push_back(*itr);

            sort(pairs.begin(), pairs.end(), [=](std::pair<char, int>& a, std::pair<char, int>& b)
            {
                return (a.second > b.second) || (a.second==b.second && a.first < b.first);
            });

            std::string s="";
            for(int i = 0; i < 5;i++){
                s.push_back(pairs[i].first);
            }
            return r.checksum != s;
        }

        std::string decypher(room r){
            std::string res = "";
            for(char c : r.name){
                if(c == ' ')res.push_back(c);
                else res.push_back(char(((c+r.id-'a')%26)+'a'));
            }
            return res;
        }

        int explore(){
            int res = 0;
            for(room r : HQ){
                if(!isdecoy(r)){
                    res += r.id;
                    if(decypher(r) == "northpole object storage")
                        std::cout << decypher(r) << " " << r.id << std::endl; 
                }

            }
            return res;
        }
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            return std::to_string(explore());
        }
    }
}

