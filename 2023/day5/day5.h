#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <queue>

using namespace std;

namespace aoc2023{
    namespace day5{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day5/day5sample")=="35");
            std::cout << solvedayp1("./2023/day5/day5") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day5/day5sample")=="46");
            std::cout << solvedayp2("./2023/day5/day5") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            string token;
            vector<long long> seeds;

            getline(cin, token, '\n');

            stringstream ss(token);
            ss >> token;
            getline(ss, token, ' ');
            while(ss.peek() != EOF){
                seeds.emplace_back();
                ss >> seeds.back();
            }
            getline(cin, token, '\n');
            sort(seeds.begin(), seeds.end());
            
            while(getline(cin, token, '\n')){

                // get lines
                vector<vector<long long>> intervals;
                while(getline(cin, token, '\n')){
                    if(token.empty())break;
                    stringstream sspart(token);
                    
                    intervals.push_back({0,0,0});
                    sspart >> intervals.back()[2];
                    sspart >> intervals.back()[0];
                    sspart >> intervals.back()[1];
                    intervals.back()[1] += intervals.back()[0];
                }
                sort(intervals.begin(), intervals.end(), [](vector<long long> a, vector<long long> b){return a[0] < b[0];});    
                int i = 0;
                for(int j = 0; j < (int)intervals.size();j++){
                    while(i < (int)seeds.size() && seeds[i] < intervals[j][0])i++;
                    while(i < (int)seeds.size() && seeds[i] >= intervals[j][0] && seeds[i] < intervals[j][1]){
                        seeds[i] = intervals[j][2] + (seeds[i] - intervals[j][0]);
                        i++;
                    }
                    if(i == (int)seeds.size())break;
                }
                sort(seeds.begin(), seeds.end());
            }

            int res =  *min_element(seeds.begin(), seeds.end());
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            string token;
            queue<pair<long long,long long>> seeds;

            getline(cin, token, '\n');

            stringstream ss(token);
            ss >> token;
            getline(ss, token, ' ');
            while(ss.peek() != EOF){
                long long a,r;
                ss >> a >> r;
                seeds.push({a,r});
            }
            getline(cin, token, '\n');
            long long ans = LLONG_MAX;
            while(getline(cin, token, '\n')){
                ans = LLONG_MAX;
                // get lines
                vector<vector<long long>> intervals;
                while(getline(cin, token, '\n')){
                    if(token.empty())break;
                    stringstream sspart(token);
                    
                    intervals.push_back({0,0,0});
                    sspart >> intervals.back()[2];
                    sspart >> intervals.back()[0];
                    sspart >> intervals.back()[1];
                    intervals.back()[1] += intervals.back()[0];
                }
                sort(intervals.begin(), intervals.end(), [](vector<long long> a, vector<long long> b){return a[0] < b[0];});    
                
                int s = seeds.size();
                while(s--){
                    auto [a,r] = seeds.front();
                    seeds.pop();
                    for(int j = 0; j < (int)intervals.size();j++){
                        if(a + r < intervals[j][0]){
                            seeds.push({a,r});
                            ans = min(ans, a);
                            continue;
                        }
                        if(a+r > intervals[j][0] && a < intervals[j][1]){
                            // push whats out of overlap left
                            if(a<intervals[j][0]){
                                seeds.push({a,min(r,intervals[j][0] - a)});
                                ans = min(ans, a);
                                a = intervals[j][0];
                                r = r - (intervals[j][0] - a);

                            }

                            if(a+r >= intervals[j][1]){
                                seeds.push({intervals[j][2] +a - intervals[j][0],intervals[j][1] - a});
                                ans = min(ans,intervals[j][2] +a - intervals[j][0]);
                                r = r - (intervals[j][1] - a);
                                a = intervals[j][1];
                            }else{
                                seeds.push({intervals[j][2] +a - intervals[j][0],r});
                                ans = min(ans, intervals[j][2] +a - intervals[j][0]);
                                r = 0;
                                break;
                            }
                        }
                    }
                    if(r>0){
                        seeds.push({a,r});
                        ans = min(ans, a);
                    }
                }
            }
            return std::to_string(ans);
        }
    }
}

