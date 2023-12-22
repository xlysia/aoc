#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits.h>

using namespace std;

namespace aoc2018{
    namespace day7{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p,int workers=5, int basetime=60);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day7/day7sample")=="CABDFE");
            std::cout << solvedayp1("./2018/day7/day7") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day7/day7sample",2,0)=="15");
            std::cout << solvedayp2("./2018/day7/day7") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
        
            unordered_map<char,vector<char>> adjs;
            vector<bool> processed(26,true);
            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::string s, keynode, nextnode;
                ss >> s >> keynode >> s >> s >> s >> s >> s >> nextnode;
                adjs[nextnode[0]].push_back(keynode[0]);
                processed[keynode[0]-'A'] = false;
                processed[nextnode[0]-'A'] = false;
            }
            string ans = "";

            while(ans.size() != adjs.size()){
                for(int i=0; i<26; i++){
                    if(!processed[i]){
                        bool allprocessed = true;
                        for(char& c : adjs[i+'A']){
                            if(!processed[c-'A']){allprocessed = false;break;}
                        }
                        if(allprocessed){
                            ans.push_back(i+'A');
                            processed[i] = true;
                            break;
                        }
                    }
                }
            }

            return ans;
        }

        std::string solvedayp2(std::string p,int workers, int basetime){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;

            unordered_map<char,vector<char>> adjs;
            vector<int> processed(26,-1);
            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::string s, keynode, nextnode;
                ss >> s >> keynode >> s >> s >> s >> s >> s >> nextnode;
                adjs[nextnode[0]].push_back(keynode[0]);
                if(adjs.find(keynode[0]) == adjs.end()){
                    adjs[keynode[0]] = vector<char>();
                }
            }
            for(int i = 0; i<26; i++){
                if(adjs.find(i+'A') == adjs.end()){
                    processed[i] = 0;
                }
            }
            priority_queue<int,vector<int>,greater<int>> minheap;
            for(int i = 0; i<workers; i++){
                minheap.push(0);
            }
            int ans = 0;
            int N = 0;
            while(N != (int)adjs.size()){
                priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> toprocess;
                for(int i=0; i<26; i++){
                    if(processed[i]>-1)continue;

                    bool allprocessed = true;
                    int time = 0;
                    for(char& c : adjs[i+'A']){
                        if(processed[c-'A']<0){allprocessed = false;break;}
                        time = max(time,processed[c-'A']);
                    }
                    if(allprocessed){
                        toprocess.push(make_pair(time,i));
                        N++;
                    }
                }

                while(!toprocess.empty()){
                    pair<int,int> p = toprocess.top();
                    toprocess.pop();
                    int time = p.first;
                    int i = p.second;
                    if(minheap.top() > time){
                        time = minheap.top();
                    }
                    minheap.pop();
                    time += basetime + i + 1;
                    minheap.push(time);
                    processed[i] = time;
                    ans = max(ans,time);
                }
            }

            return std::to_string(ans);
        }
    }
}

