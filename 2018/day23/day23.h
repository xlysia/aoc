#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <queue>

using namespace std;

namespace aoc2018{
    namespace day23{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day23/day23sample")=="7");
            std::cout << solvedayp1("./2018/day23/day23") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day23/day23sample2")=="36");
            std::cout << solvedayp2("./2018/day23/day23") << std::endl;
        }

        using ll  = long long;
        struct nanobot{
            ll x, y, z, r;
        };

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<nanobot> bots;
            nanobot strongest = {0, 0, 0, 0};

            while(getline(std::cin, line)){
                std::istringstream iss(line);
                ll x, y, z, r;
                // use sscanf line type is pos=<6539287,36211810,15289561>, r=71253179
                sscanf(line.c_str(), "pos=<%lld,%lld,%lld>, r=%lld", &x, &y, &z, &r);
            
                if(strongest.r < r){
                    strongest = {x, y, z, r};
                }
                bots.push_back({x, y, z, r});
            }

            int ans = 0;
            for(auto b : bots){
                if(abs(strongest.x - b.x) + abs(strongest.y - b.y) + abs(strongest.z - b.z) <= strongest.r){
                    ans++;
                }
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            vector<nanobot> bots;

            ll minx = 1000000000, miny = 1000000000, minz = 1000000000;
            ll maxx = -1000000000, maxy = -1000000000, maxz = -1000000000;

            while(getline(std::cin, line)){
                std::istringstream iss(line);
                ll x, y, z, r;
                // use sscanf line type is pos=<6539287,36211810,15289561>, r=71253179
                sscanf(line.c_str(), "pos=<%lld,%lld,%lld>, r=%lld", &x, &y, &z, &r);
                bots.push_back({x, y, z, r});

                minx = min(minx, x);
                miny = min(miny, y);
                minz = min(minz, z);
                maxx = max(maxx, x);
                maxy = max(maxy, y);
                maxz = max(maxz, z);
            }

            // using priority_queue. Start with the box with the most possible bots in range then divide it into 8 boxes until the box size is 1.
            struct box{
                ll x,y,z,w,h,d;
                int botsInRange;
                ll dist;
                bool operator<(const box& b) const{
                    if(botsInRange == b.botsInRange){
                        return dist < b.dist;
                    }
                    return botsInRange < b.botsInRange;
                }
                box(ll x, ll y, ll z, ll w, ll h, ll d, int botsInRange, ll dist) : x(x), y(y), z(z), w(w), h(h), d(d), botsInRange(botsInRange), dist(dist) {}
                box() : x(0), y(0), z(0), w(0), h(0), d(0), botsInRange(0), dist(0) {}
                box(ll x, ll y, ll z, ll w, ll h, ll d) : x(x), y(y), z(z), w(w), h(h), d(d), botsInRange(0), dist(x+w/2 + y+h/2 + z+d/2) {}
            };

            priority_queue<box,vector<box>> maxHeap;
            maxHeap.push(box(minx, miny, minz, maxx-minx, maxy-miny, maxz-minz));

            while(!maxHeap.empty()){
                box b = maxHeap.top();
                maxHeap.pop();

                if(b.w == 0 && b.h == 0 && b.d == 0){
                    return std::to_string(b.x + b.y + b.z);
                }

                ll midx = b.x + b.w/2;
                ll midy = b.y + b.h/2;
                ll midz = b.z + b.d/2;

                vector<box> boxes;
                boxes.push_back({b.x, b.y, b.z, b.w/2, b.h/2, b.d/2});
                boxes.push_back({midx, b.y, b.z, b.w/2, b.h/2, b.d/2});
                boxes.push_back({b.x, midy, b.z, b.w/2, b.h/2, b.d/2});
                boxes.push_back({midx, midy, b.z, b.w/2, b.h/2, b.d/2});
                boxes.push_back({b.x, b.y, midz, b.w/2, b.h/2, b.d/2});
                boxes.push_back({midx, b.y, midz, b.w/2, b.h/2, b.d/2});
                boxes.push_back({b.x, midy, midz, b.w/2, b.h/2, b.d/2});
                boxes.push_back({midx, midy, midz, b.w/2, b.h/2, b.d/2});

                for(auto& box : boxes){
                    for(auto& bot : bots){
                        //sphere intersect box
                        ll dx = abs(bot.x - max(box.x, min(bot.x, box.x + box.w)));
                        ll dy = abs(bot.y - max(box.y, min(bot.y, box.y + box.h)));
                        ll dz = abs(bot.z - max(box.z, min(bot.z, box.z + box.d)));
                        ll dist = dx + dy + dz;
                        if(dist <= bot.r){
                            box.botsInRange++;
                        }
                    }
                }

                for(auto& box : boxes){
                    if(box.botsInRange < 1)continue;
                    maxHeap.push(box);
                }
            }

            return "not found";
        }
    }
}

