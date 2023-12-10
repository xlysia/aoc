#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

using namespace std;

namespace aoc2016{
    namespace day20{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day20/day20sample")=="3");
            std::cout << solvedayp1("./2016/day20/day20") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2016/day20/day20") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            priority_queue<pair<long long , long long>, vector<pair<long long , long long>>, greater<>> minHeap;
            
            while(cin.good()){
                getline(cin, line);
                // line is as A-B add [A,B] to intervals
                string token;
                stringstream ss(line);
                getline(ss,token,'-');
                long long a = stoll(token);
                getline(ss,token,'-');
                long long b = stoll(token);
                minHeap.push({a,b});
            }

            long long ans =  0;

            while(!minHeap.empty() && ans >= minHeap.top().first){
                ans = max(ans, minHeap.top().second+1);
                minHeap.pop();
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            priority_queue<pair<long long , long long>, vector<pair<long long , long long>>, greater<>> minHeap;
            
            while(cin.good()){
                getline(cin, line);
                // line is as A-B add [A,B] to intervals
                string token;
                stringstream ss(line);
                getline(ss,token,'-');
                long long a = stoll(token);
                getline(ss,token,'-');
                long long b = stoll(token);
                minHeap.push({a,b});
            }

            long long ans =  0;
            long long curr = 0;
            while(!minHeap.empty()){
                while(!minHeap.empty() && curr >= minHeap.top().first){
                    curr = max(curr, minHeap.top().second+1);
                    minHeap.pop();
                }
                if(!minHeap.empty()){
                    ans += minHeap.top().first - curr;
                    curr = max(curr,minHeap.top().second+1);
                    minHeap.pop();
                }else{
                    ans += 4294967296 - curr;
                }
            }

            return std::to_string(ans);
        }
    }
}

