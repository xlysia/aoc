#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

namespace aoc2015{
    namespace day9{
        int nidx = 0;

        class Link{
            public:
                std::string dest;
                int cost;
                Link():dest("error"),cost(0){}
                Link(std::string _d,int _c):dest(_d),cost(_c){}
        };

        class Node{
            public:
                std::string name;
                std::vector<Link> links = {};
                int id = 0;
                Node():name("noname"){}
                Node(std::string _s):name(_s){id = nidx++;}
        };
        std::map<std::string,Node> roadmap;
        class Path{
            public:
            int value = 0;
            int cost = 0;
            std::string endp = "";
            Path(){}
            Path(std::string s){value += (1<<roadmap[s].id);endp = s;}
            bool Go(Link l){
                if(value & ( 1 << roadmap[l.dest].id)) return false;
                value += ( 1 << roadmap[l.dest].id);
                cost += l.cost;
                endp = l.dest;
                return true;
            }
        };

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day9/day9sample")=="605");
            std::cout << solvedayp1("./2015/day9/day9") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day9/day9sample")=="982");
            std::cout << solvedayp2("./2015/day9/day9") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res = 999999;
            roadmap.clear();
            nidx = 0;
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                pos = line.find(" to ");
                std::string left = line.substr(0, pos).c_str();
                line.erase(0, pos + 4);
                pos = line.find(" = ");
                std::string right = line.substr(0, pos).c_str();
                line.erase(0, pos + 3);
                int cost = std::atoi(line.c_str());

                if(roadmap.find(left) == roadmap.end())roadmap[left]=Node(left);
                if(roadmap.find(right) == roadmap.end())roadmap[right]=Node(right);
                roadmap[left].links.push_back(Link(right,cost));
                roadmap[right].links.push_back(Link(left,cost));
            }
            std::vector<Path> queue;
            for(auto it : roadmap){
                queue.push_back(it.first);
            }
            while(queue.size() > 0){
                Path p = queue.back();
                queue.pop_back();
                Path c = Path(p);
                for(Link l : roadmap[p.endp].links){
                    p = c;
                    if(p.Go(l)){
                        if(p.value == (1 << nidx)-1){
                            res = std::min(res,p.cost);
                        }else{
                            queue.push_back(p);
                        }
                    }
                }
            }

            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res = 0;
            roadmap.clear();
            nidx = 0;
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                pos = line.find(" to ");
                std::string left = line.substr(0, pos).c_str();
                line.erase(0, pos + 4);
                pos = line.find(" = ");
                std::string right = line.substr(0, pos).c_str();
                line.erase(0, pos + 3);
                int cost = std::atoi(line.c_str());

                if(roadmap.find(left) == roadmap.end())roadmap[left]=Node(left);
                if(roadmap.find(right) == roadmap.end())roadmap[right]=Node(right);
                roadmap[left].links.push_back(Link(right,cost));
                roadmap[right].links.push_back(Link(left,cost));
            }
            std::vector<Path> queue;
            for(auto it : roadmap){
                queue.push_back(it.first);
            }
            while(queue.size() > 0){
                Path p = queue.back();
                queue.pop_back();
                Path c = Path(p);
                for(Link l : roadmap[p.endp].links){
                    p = c;
                    if(p.Go(l)){
                        if(p.value == (1 << nidx)-1){
                            res = std::max(res,p.cost);
                        }else{
                            queue.push_back(p);
                        }
                    }
                }
            }

            return std::to_string(res);
        }
    }
}

