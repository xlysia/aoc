#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace aoc2017{
    namespace day6{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day6/day6sample")=="5");
            std::cout << solvedayp1("./2017/day6/day6") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day6/day6sample")=="4");
            std::cout << solvedayp2("./2017/day6/day6") << std::endl;
        }

        string getKey(vector<int>& banks){
            string key = "";
            for(int i = 0; i < (int)banks.size(); i++){
                key.append(to_string(banks[i])+" ");
            }
            return key;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            vector<int> banks;
            while(cin.good()){
                cin >> val;
                banks.push_back(val);
            }



            unordered_set<string> seen;
            seen.insert(getKey(banks));
            int K = banks.size();
            while(1){
                
                auto it = max_element(banks.begin(), banks.end());
                int idx = it-banks.begin();
                
                int d = (*it)/K;
                int r = (*it)-d*K;
                banks[idx] = 0;
                for(int i = 1; i <= K; i++){
                    banks[(i +idx)% K] += d + (i <= r ? 1 : 0); 
                }
                if(seen.find(getKey(banks)) != seen.end()){
                    break;
                }
                seen.insert(getKey(banks));
            }   
            return std::to_string(seen.size());
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int val;
            vector<int> banks;
            while(cin.good()){
                cin >> val;
                banks.push_back(val);
            }



            unordered_map<string,int> seen;
            seen[getKey(banks)] = 0;
            int K = banks.size();
            int N = 0;
            while(N++<1e9){
                
                auto it = max_element(banks.begin(), banks.end());
                int idx = it-banks.begin();
                
                int d = (*it)/K;
                int r = (*it)-d*K;
                banks[idx] = 0;
                for(int i = 1; i <= K; i++){
                    banks[(i +idx)% K] += d + (i <= r ? 1 : 0); 
                }
                if(seen.find(getKey(banks)) != seen.end()){
                    return to_string(N-seen[getKey(banks)]);
                }
                seen[getKey(banks)] = N;
            }   
            return "NOTDEF";
        }
    }
}

