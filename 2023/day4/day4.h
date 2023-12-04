#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <cstring>

using namespace std;

namespace aoc2023{
    namespace day4{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day4/day4sample")=="13");
            std::cout << solvedayp1("./2023/day4/day4") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day4/day4sample")=="30");
            std::cout << solvedayp2("./2023/day4/day4") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans =  0;        
            int wins[100];

            while(getline(std::cin,line)){
                memset(wins,0,sizeof(wins));
                std::stringstream ss(line);
                std::string card;
                ss >> card >> card;
                std::string win_part;
                int sum = 0;
                getline(ss,win_part,'|');
                std::stringstream ss2(win_part);
                while(getline(ss2,win_part,' ')){
                    if(!win_part.empty())wins[stoi(win_part)]++;
                }
                getline(ss,card);
                std::stringstream ss3(card);
                while(getline(ss3,card,' ')){
                    if(card.empty())continue;
                    if(wins[stoi(card)]){
                        sum = sum < 1? 1 : sum*2;
                    }
                }
                ans += sum;
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
  std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans =  0;        
            int wins[100];
            vector<int> cards(300,0);
            int row = 0;
            while(getline(std::cin,line)){
                cards[row]++;
                ans += cards[row];
                memset(wins,0,sizeof(wins));
                std::stringstream ss(line);
                std::string card;
                ss >> card >> card;
                std::string win_part;
                int sum = 0;
                getline(ss,win_part,'|');
                std::stringstream ss2(win_part);
                while(getline(ss2,win_part,' ')){
                    if(!win_part.empty())wins[stoi(win_part)]++;
                }
                getline(ss,card);
                std::stringstream ss3(card);
                while(getline(ss3,card,' ')){
                    if(card.empty())continue;
                    if(wins[stoi(card)]){
                        sum++;
                    }
                }
                row++;
                for(int i = row;i< row+sum;i++){
                    cards[i] += cards[row-1];
                }
            }
            return std::to_string(ans);
        }
    }
}

