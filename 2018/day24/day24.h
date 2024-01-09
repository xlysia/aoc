#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

namespace aoc2018{
    namespace day24{

        vector<int> solvedayp1(std::string p,int boost);
        int solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day24/day24sample",0)[1]==5216);
            assert (solvedayp1("./2018/day24/day24sample",1570)[0]==51);

            std::cout << solvedayp1("./2018/day24/day24",0)[1] << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2018/day24/day24") << std::endl;
        }

        vector<int> solvedayp1(std::string p,int boost){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // parse input
            struct group{
                int units;
                int hp;
                unordered_set<string> weak;
                unordered_set<string> immune;
                int dmg;
                int team;
                int target;
                int attacker;
                std::string dmgtype;
                int initiative;
                int id;
            };

            vector<group> armies;
            int immune_system = 0;
            int infection = 0;
            for(int i = 0; i < 2;i++){
                getline(cin, line);
                while(line.length()>0 && cin.good()){
                    getline(cin, line);
                    if(line.length()==0) break;
                    
                    group g;
                    g.id = armies.size() - immune_system +1;
                    g.units = stoi(line.substr(0, line.find(" ")));
                    g.hp = stoi(line.substr(line.find("each with ")+10, line.find(" hit points")-line.find("each with ")-10));
                    string dmgstr = line.substr(line.find("does ")+5, line.find(" damage")-line.find("does ")-5);
                    stringstream dmgss(dmgstr);
                    dmgss >> g.dmg >> g.dmgtype;
                    g.dmg+=boost*!i;
                    int immunity = line.find("immune to ")+10;
                    int weakness = line.find("weak to ")+8;
                    if(line.find("immune to ")!=string::npos){
                        string immune = line.substr(line.find("immune to ")+10, line.find(");"[weakness>immunity])-line.find("immune to ")-10);
                        stringstream ss(immune);
                        string token;
                        while(ss.good()){
                            ss >> token;
                            if(token.back()==',') token.pop_back();
                            g.immune.insert(token);
                        }
                    }
                    if(line.find("weak to ")!=string::npos){
                        string weak = line.substr(line.find("weak to ")+8, line.find(";)"[weakness>immunity])-line.find("weak to ")-8);
                        stringstream ss(weak);
                        string token;
                        while(ss.good()){
                            ss >> token;
                            if(token.back()==',') token.pop_back();
                            g.weak.insert(token);
                        }
                    }
                    g.initiative = stoi(line.substr(line.find("initiative ")+11));
                    g.team = i;
                    g.target = -1;
                    g.attacker = -1;
                    armies.push_back(g);
                }
                if(!i) immune_system = armies.size();
                else infection = armies.size()-immune_system;
            }

            while(immune_system && infection){

                priority_queue<pair<int, group*>> maxheap;
                //pick targets. highest effective power, then initiative
                sort(armies.begin(), armies.end(), [](group a, group b){
                    if(a.units*a.dmg==b.units*b.dmg) return a.initiative>b.initiative;
                    return a.units*a.dmg>b.units*b.dmg;
                });
                
                for(group& g : armies){
                    // check target
                    int max_dmg = 0;
                    int max_ep = 0;
                    int max_init = 0;
                    g.target = -1;

                    for(size_t i = 0; i < armies.size(); i++){
                        if(armies[i].attacker!=-1) continue;
                        if(armies[i].team==g.team) continue;
                        int dmg = g.units*g.dmg;
                        if(armies[i].immune.find(g.dmgtype) != armies[i].immune.end())continue;
                        if(armies[i].weak.find(g.dmgtype) != armies[i].weak.end()) dmg*=2;
                        if(dmg>max_dmg){
                            max_dmg = dmg;
                            max_ep = armies[i].units*armies[i].dmg;
                            max_init = armies[i].initiative;
                            g.target = i;
                        }
                        else if(dmg==max_dmg){
                            if(armies[i].units*armies[i].dmg>max_ep){
                                max_dmg = dmg;
                                max_ep = armies[i].units*armies[i].dmg;
                                max_init = armies[i].initiative;
                                g.target = i;
                            }
                            else if(armies[i].units*armies[i].dmg==max_ep){
                                if(armies[i].initiative>max_init){
                                    max_dmg = dmg;
                                    max_ep = armies[i].units*armies[i].dmg;
                                    max_init = armies[i].initiative;
                                    g.target = i;
                                }
                            }
                        }
                    }
                    if(g.target!=-1) armies[g.target].attacker = g.id;
                    maxheap.push(make_pair(g.initiative, &g));
                    
                }

                
                bool kills = false;
                while(!maxheap.empty()){
                    group& g = *maxheap.top().second;
                    maxheap.pop();

                    if(g.target==-1) continue;
                    if(g.units<=0) continue;
                    int dmg = g.units*g.dmg;
                    if(armies[g.target].immune.find(g.dmgtype) != armies[g.target].immune.end()) dmg = 0;
                    if(armies[g.target].weak.find(g.dmgtype) != armies[g.target].weak.end()) dmg*=2;
                    

                //    printf("%s Group %d attacks defending group %d, killing %d units\n",g.team?"Infection":"Immune" , g.id, armies[g.target].id, dmg/armies[g.target].hp);
                    armies[g.target].units -= dmg/armies[g.target].hp;
                    if(dmg/armies[g.target].hp) kills = true;
                }

                for(int i = 0; i < (int)armies.size(); i++){
                    armies[i].attacker = -1;
                    armies[i].target = -1;
                    if(armies[i].units<=0){
                        if(!armies[i].team) immune_system--;
                        else infection--;
                        armies.erase(armies.begin()+i);
                        i--;
                    }
                }
                if(!kills) break;
            }
            
            vector<int> ans = {0,0};
            for(group g : armies){
                ans[g.team]+=g.units;
            }
            return ans;
        }

        int solvedayp2(std::string p){
            int ans = 0;
            int L = 0;
            int R = 100000;
            while(L <= R){
                int mid = (L+R)/2;
                auto vals = solvedayp1(p,mid);
                if(vals[1]!=0) L = mid+1;
                else{
                    R = mid-1;
                    ans = vals[0];
                }
            }

            return ans;
        }
    }
}

