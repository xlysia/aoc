#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <algorithm>
#include <numeric>


namespace aoc2023{
    namespace day20{

        std::string solvedayp1(std::string p, int buttonPresses);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day20/day20sample",1000)=="32000000");
            assert (solvedayp1("./2023/day20/day20sample2",1000)=="11687500");
            std::cout << solvedayp1("./2023/day20/day20",1000) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2023/day20/day20") << std::endl;
        }

        struct module{
            int id;
            char type;
            std::vector<std::string> nexts;
            std::map<std::string,bool> ins;

            std::unordered_map<string,int> memo = {};
            long long cycle = 0;

        };

        std::string solvedayp1(std::string p , int buttonPresses){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // 
            // parse this line into unorderedmap 
            int id = 0;
            unordered_map<string, module> graph;

            while (getline(cin, line)) {
                istringstream iss(line);
                string key,token;
                iss >> key >> token;
                char type = 'B';
                if(!isalpha(key[0])){
                    type = key[0];
                    key = key.substr(1);
                }
                if(graph.find(key)==graph.end()){
                    graph[key] = {id++,type, {},{},{},false}; 
                }else{
                    graph[key].type = type;
                }
               // state to low
                while(iss >> token){
                    if(token.back()==',')token.pop_back();
                    graph[key].nexts.push_back(token);
                    if(graph.find(token)==graph.end()){
                        graph[token] = {id++,' ',{},{},{},false};
                    }
                    graph[token].ins[key] = false;
                }
            }

            vector<bool> registers(id,false);

            unordered_map<vector<bool>, tuple<int,int,int>> visited;
            visited[registers] = {0,0,0};
            long long lows = 0;
            long long highs = 0;
            int cycle = 0;
            int N = 0;
            while(N++ < 1000){
                // send low pulse to broadcaster
                queue<tuple<string,bool,string>> q;
                q.push({"broadcaster",false , "button"});

                while(!q.empty()){
                    auto [node, pulse,from] = q.front();
                    q.pop();
                    graph[node].ins[from] = pulse;


                    if(pulse)highs++;
                    else lows++;

                    if(graph[node].type=='B'){
                        for(auto next : graph[node].nexts){
                            q.push({next, pulse,node});
                        }
                    }else if(graph[node].type=='%'){
                        // flipflop
                        if(pulse)continue;

                        if(registers[graph[node].id]){
                            registers[graph[node].id] = false;
                            for(auto next : graph[node].nexts){
                                q.push({next, false,node});
                            }
                        }else{
                            registers[graph[node].id] = true;
                            for(auto next : graph[node].nexts){
                                q.push({next, true,node});
                            }
                        }
                    }else if(graph[node].type=='&'){
                        // and
                        registers[graph[node].id] = pulse;
                        bool all = true;
                        for(auto ini : graph[node].ins){
                            if(!ini.second){
                                all = false;
                                break;
                            }
                        }
                        if(all){
                            for(auto next : graph[node].nexts){
                                q.push({next, false,node});
                            }
                        }else{
                            for(auto next : graph[node].nexts){
                                q.push({next, true,node});
                            }
                        }
                    }
                }

                if(!cycle && visited.find(registers)!=visited.end()){
                    // found cycle
                    auto [l,h,turn] = visited[registers];
                    cycle = N - turn;
                    int inc = (1000 - N) / cycle;
                    N += inc * cycle;
                    lows += inc * (lows - l);
                    highs += inc * (highs - h);
                }
            }

            long long ans =  lows*highs;
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans = 0;
            // 
            // Trick is to see the rx is out of a cConjunction module which is link to 4 others which are themselves singled linked to cunjuntors
            // so we can simulate the whole thing and find the cycle for each parts then get the lcm of all cycles
            //  input is nicely set so that cycles starts at 0 for all parts.
            int id = 0;
            unordered_map<string, module> graph;

            while (getline(cin, line)) {
                istringstream iss(line);
                string key,token;
                iss >> key >> token;
                char type = 'B';
                if(!isalpha(key[0])){
                    type = key[0];
                    key = key.substr(1);
                }
                if(graph.find(key)==graph.end()){
                    graph[key] = {id++,type, {},{},{},false}; 
                }else{
                    graph[key].type = type;
                }
               // state to low
                while(iss >> token){
                    if(token.back()==',')token.pop_back();
                    graph[key].nexts.push_back(token);
                    if(graph.find(token)==graph.end()){
                        graph[token] = {id++,' ',{},{},{},false};
                    }
                    graph[token].ins[key] = false;
                }
            }

            vector<bool> registers(id,false);

            unordered_map<vector<bool>, tuple<int,int,int>> visited;
            visited[registers] = {0,0,0};

            int N = 0;
            while(ans == 0){
                N++;
            
                // send low pulse to broadcaster
                queue<tuple<string,bool,string>> q;
                q.push({"broadcaster",false , "button"});

                while(!q.empty()){
                    auto [node, pulse,from] = q.front();
                    q.pop();
                    graph[node].ins[from] = pulse;

                    if(graph[node].type=='B'){
                        for(auto next : graph[node].nexts){
                            q.push({next, pulse,node});
                        }
                    }else if(graph[node].type=='%'){
                        // flipflop
                        if(pulse)continue;

                        if(registers[graph[node].id]){
                            registers[graph[node].id] = false;
                            for(auto next : graph[node].nexts){
                                q.push({next, false,node});
                            }
                        }else{
                            registers[graph[node].id] = true;
                            for(auto next : graph[node].nexts){
                                q.push({next, true,node});
                            }
                        }
                    }else if(graph[node].type=='&'){
                        // and
                        registers[graph[node].id] = pulse;
                        bool all = true;
                        for(auto ini : graph[node].ins){
                            if(!ini.second){
                                all = false;
                                break;
                            }
                        }

                        if(node == "df"){
                            bool cyclefound = true;
                            for(auto ini : graph[node].ins){
                                if(graph[ini.first].cycle == 0){
                                    cyclefound = false;
                                    break;
                                }
                            }
                            if(cyclefound){
                                long long cycle = 1;
                                for(auto ini : graph[node].ins){
                                    cycle = lcm(cycle,graph[ini.first].cycle);
                                }
                                return to_string(cycle);
                            }
                        }

                        if(all){
                            for(auto next : graph[node].nexts){
                                q.push({next, false,node});
                            }
                        }else{

                            // check for cycle
                            if(!graph[node].cycle){
                                string key = "";
                                for(auto ini : graph[node].ins){
                                    key += to_string(ini.second);
                                }
                                if(graph[node].memo.find(key)!=graph[node].memo.end()){
                                    auto turn = graph[node].memo[key];
                                    graph[node].cycle = N - turn;
                                 //   cout << "cycle found " << node << " : " << graph[node].cycle << " started at " << turn << endl;
                                }else{
                                    graph[node].memo[key] = N;
                                }
                            }

                            for(auto next : graph[node].nexts){
                                q.push({next, true,node});
                            }
                        }
                    }
                }

            }

            return "NOT FOUND";
        }
    }
}

