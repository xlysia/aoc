#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2023{
    namespace day7{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day7/day7sample")=="6440");
            std::cout << solvedayp1("./2023/day7/day7") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day7/day7sample")=="5905");
            std::cout << solvedayp2("./2023/day7/day7") << std::endl;
        }



        string eval(const std::string& hand){
            map<char,long long> book;
            string suit = "";
            map<char,char> score = {{'2','2'},{'3','3'},{'4','4'},{'5','5'},{'6','6'},{'7','7'},{'8','8'},{'9','9'},{'T','A'},{'J','B'},{'Q','C'},{'K','D'},{'A','E'}};
            for(char c : hand){
                book[score[c]]++;
                suit.push_back(score[c]);
            }
            priority_queue<int> pq;
            for(auto it : book){
                pq.push(it.second);
            }
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();

            

            if(a == 5)return "6"+suit;
            else if(a == 4)return "5"+suit;
            else if(a == 3 && b == 2)return "4"+suit;
            else if(a == 3)return "3"+suit;
            else if(a == 2 && b == 2)return "2"+suit;
            else if(a == 2)return"1"+suit;
            return "0"+suit;
        }

        string eval2(const std::string& hand){
            map<char,long long> book;
            string suit = "";
            map<char,char> score = {{'J','1'},{'2','2'},{'3','3'},{'4','4'},{'5','5'},{'6','6'},{'7','7'},{'8','8'},{'9','9'},{'T','A'},{'Q','C'},{'K','D'},{'A','E'}};
            for(char c : hand){
                book[score[c]]++;
                suit.push_back(score[c]);
            }
            priority_queue<int> pq;
            int J = book['1'];
            for(auto it : book){
                if(it.first == '1')continue;
                pq.push(it.second);
            }
            
            int a = pq.empty()? J:pq.top() + J;
            if(!pq.empty())pq.pop();
            int b = pq.empty()?0:pq.top();
            

            if(a == 5)return "6"+suit;
            else if(a == 4)return "5"+suit;
            else if(a == 3 && b == 2)return "4"+suit;
            else if(a == 3)return "3"+suit;
            else if(a == 2 && b == 2)return "2"+suit;
            else if(a == 2)return"1"+suit;
            return "0"+suit;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            vector<tuple<string,string,long long>> hands;
            while(std::getline(std::cin, line)){
                std::istringstream iss(line);
                std::string hand;
                long long bet;

                iss >> hand >> bet;
                hands.push_back({eval(hand),hand,bet});
            }

            sort(hands.begin(),hands.end());


            long long ans = 0;
            for(int i = 0; i < (int)hands.size(); i++){
               // cout << a << " " << b << " " << c << endl;
                ans += get<2>(hands[i])*(i+1);
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            vector<tuple<string,string,long long>> hands;
            while(std::getline(std::cin, line)){
                std::istringstream iss(line);
                std::string hand;
                long long bet;

                iss >> hand >> bet;
                hands.push_back({eval2(hand),hand,bet});
            }

            sort(hands.begin(),hands.end());


            long long ans = 0;
            for(int i = 0; i < (int)hands.size(); i++){
                ans +=  get<2>(hands[i])*(i+1);
            }

            return std::to_string(ans);
        }
    }
}

