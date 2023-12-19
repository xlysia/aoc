#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

namespace aoc2023{
    namespace day19{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day19/day19sample")=="19114");
            std::cout << solvedayp1("./2023/day19/day19") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day19/day19sample")=="167409079868000");
            std::cout << solvedayp2("./2023/day19/day19") << std::endl;
        }
            struct Rule{
                char c;
                char type;
                std::string move;
                int val;
            };
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int ans =  0;

            unordered_map<string , vector<Rule>> book;
            while(std::getline(std::cin, line)){
                if(line=="")
                    break;  

                // parse rule name
                string rule_name = line.substr(0, line.find("{"));
                line = line.substr(line.find("{")+1);
                line.pop_back();
                // parse rules
                vector<Rule> rules;
                stringstream ss(line);
                while(getline(ss,line,',')){
                    
                    Rule r;
                    auto it = line.find(":");
                    if(it!=string::npos){
                        r.c = line[0];
                        r.type = line[1];
                        line = line.substr(2);
                        r.val = stoi(line.substr(0, line.find(":")));
                        r.move = line.substr(line.find(":")+1);
                        rules.push_back(r);
                    }else{
                        r.type = 'E';
                        r.move = line;
                        rules.push_back(r);
                    }
                    

                }
                book[rule_name] = rules;
            }

            while(std::getline(std::cin, line)){
                // prse into dictionsary
                unordered_map<char, int> item;
                line = line.substr(1);
                line.pop_back();
                stringstream ss(line);
                while(getline(ss,line,',')){
                    char key = line[0];
                    int val = stoi(line.substr(2));
                    item[key] = val;
                }

                // run rules
                string workflow = "in";
                while(workflow != "A" && workflow != "R"){

                    for(Rule r: book[workflow]){
                        if(r.type=='<'){
                            if(item[r.c] < r.val){
                                workflow = r.move;
                                break;
                            }
                        }else if(r.type=='>'){
                            if(item[r.c] > r.val){
                                workflow = r.move;
                                break;
                            }
                        }else if(r.type=='E'){
                            workflow = r.move;
                            break;
                        }
                    }
                }

                if(workflow == "A" ){
                    ans += item['x'] + item['m'] + item['a'] + item['s'];
                }
            }

            return std::to_string(ans);
        }

        struct Item{
            int xmin;
            int xmax;
            int mmin;
            int mmax;
            int amin;
            int amax;
            int smin;
            int smax;
        };
        long long dfs(unordered_map<string,vector<Rule>>& book , Item item, string workflow){
            if(workflow == "R")return 0;
            if(workflow == "A"){
                return (long long)(item.xmax-item.xmin+1)*(long long)(item.mmax-item.mmin+1)*(long long)(item.amax - item.amin+1)*(long long)(item.smax-item.smin+1);
            }
            long long ans = 0;

            for(Rule r : book[workflow]){
                if(r.type == '<'){
                    if(r.c == 'x'){
                        Item new_item = item;
                        new_item.xmax = min(new_item.xmax, r.val-1);
                        if(new_item.xmax < new_item.xmin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.xmin = max(item.xmin, r.val);
                        if(item.xmin > item.xmax)break;
                    }else if(r.c == 'm'){
                        Item new_item = item;
                        new_item.mmax = min(new_item.mmax, r.val-1);
                        if(new_item.mmax < new_item.mmin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.mmin = max(item.mmin, r.val);
                        if(item.mmin > item.mmax)break;
                    }else if(r.c == 'a'){
                        Item new_item = item;
                        new_item.amax = min(new_item.amax, r.val-1);
                        if(new_item.amax < new_item.amin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.amin = max(item.amin, r.val);
                        if(item.amin > item.amax)break;
                    }else if(r.c == 's'){
                        Item new_item = item;
                        new_item.smax = min(new_item.smax, r.val-1);
                        if(new_item.smax < new_item.smin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.smin = max(item.smin, r.val);
                        if(item.smin > item.smax)break;
                    }
                }else if(r.type == '>'){
                    if(r.c == 'x'){
                        Item new_item = item;
                        new_item.xmin = max(new_item.xmin, r.val+1);
                        if(new_item.xmax < new_item.xmin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.xmax = min(item.xmax, r.val);
                        if(item.xmin > item.xmax)break;
                    }else if(r.c == 'm'){
                        Item new_item = item;
                        new_item.mmin = max(new_item.mmin, r.val+1);
                        if(new_item.mmax < new_item.mmin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.mmax = min(item.mmax, r.val);
                        if(item.mmin > item.mmax)break;
                    }else if(r.c == 'a'){
                        Item new_item = item;
                        new_item.amin = max(new_item.amin, r.val+1);
                        if(new_item.amax < new_item.amin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.amax = min(item.amax, r.val);
                        if( item.amin > item.amax)break;
                    }else if(r.c == 's'){
                        Item new_item = item;
                        new_item.smin = max(new_item.smin, r.val+1);
                        if(new_item.smax < new_item.smin)continue;
                        ans += dfs(book, new_item, r.move);
                        item.smax = min(item.smax, r.val);
                        if(item.smin > item.smax)break;
                    }
                }else if(r.type == 'E'){
                    ans += dfs(book, item, r.move);
                }
            }

            return ans;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            unordered_map<string , vector<Rule>> book;
            while(std::getline(std::cin, line)){
                if(line=="")
                    break;  

                // parse rule name
                string rule_name = line.substr(0, line.find("{"));
                line = line.substr(line.find("{")+1);
                line.pop_back();
                // parse rules
                vector<Rule> rules;
                stringstream ss(line);
                while(getline(ss,line,',')){
                    
                    Rule r;
                    auto it = line.find(":");
                    if(it!=string::npos){
                        r.c = line[0];
                        r.type = line[1];
                        line = line.substr(2);
                        r.val = stoi(line.substr(0, line.find(":")));
                        r.move = line.substr(line.find(":")+1);
                        rules.push_back(r);
                    }else{
                        r.type = 'E';
                        r.move = line;
                        rules.push_back(r);
                    }
                    

                }
                book[rule_name] = rules;
            }

            Item item = {1,4000,1,4000,1,4000,1,4000};

            long long ans = dfs(book, item, "in"); 
            return std::to_string(ans);
        }
    }
}

