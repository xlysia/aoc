#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

namespace aoc2023{
    namespace day22{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day22/day22sample")=="5");
            std::cout << solvedayp1("./2023/day22/day22") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day22/day22sample")=="7");
            std::cout << solvedayp2("./2023/day22/day22") << std::endl;
        }


        struct Brick{
            int x;
            int y;
            int z;
            int w, h, d;
            int id;
            // add a comp operator to sort bricks by z
            bool operator<(const Brick& rhs) const
            {
                return z < rhs.z;
            }

        };

        void draw(vector<vector<pair<int,int>>>& grid){
            int m =grid.size();
            int n = grid[0].size();
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    cout << char((grid[i][j].second%26) + 'A') << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            auto comp = [](const Brick& lhs, const Brick& rhs) { 
                return lhs.z > rhs.z;
            };
            priority_queue<Brick,vector<Brick>,decltype(comp)> bricks(comp);
            
            int minx = 0;
            int miny = 0;
            int maxx = 0;
            int maxy = 0;
            while (std::getline(std::cin, line)) {
                std::istringstream iss(line);
                // 4,6,74~4,6,76 to parse it represents both edges of the brick (4,6,74)x1 and (4,6,76)x2
                // therefore w = 4-4+1 = 1, h = 6-6+1 = 1, d = 76-74+1 = 3
                int x, y, z, w, h, d;
                char c;
                iss >> x >> c >> y >> c >> z >> c >> w >> c >> h >> c >> d;
                w = w-x+1;
                h = h-y+1;
                d = d-z+1;

                minx = std::min(minx, x);
                miny = std::min(miny, y);
                maxx = std::max(maxx, x+w);
                maxy = std::max(maxy, y+h);
                Brick b = {x,y,z,w,h,d,(int)bricks.size()};
                bricks.push(b);
            }

            // create a grid of bricks
            vector<vector<pair<int,int>>> grid(maxx, vector<pair<int,int>>(maxy, {0,-1}));// (curz, brickid)

            // graph of support
            // for each brick, find the bricks that are supporting it
            struct Node{
                int id;
                vector<Node*> above;
                vector<Node*> below;

                Node(int id):id(id){}
            };

            int n = bricks.size();

            Node* root = new Node(-1);
            vector<Node*> nodes(n, nullptr);
            for(int i = 0; i < n; i++){
                nodes[i] = new Node(i);
            }

            while(!bricks.empty()){
                Brick b = bricks.top();
              //  cout << b.id << " " << b.z << endl; 
                bricks.pop();
                // find ids of bricks that are supporting this brick
                int maxz = 0;
                set<int> supportedby;
                for(int i = b.x; i < b.x+b.w; i++){
                    for(int j = b.y; j < b.y+b.h; j++){
                        if(maxz <= grid[i][j].first){
                            if(maxz < grid[i][j].first)supportedby.clear();
                            supportedby.insert(grid[i][j].second);
                            maxz = grid[i][j].first;
                        }
                    }
                }
                // add the brick to the grid
                for(int i = b.x; i < b.x+b.w; i++){
                    for(int j = b.y; j < b.y+b.h; j++){
                        grid[i][j] = {maxz+b.d, b.id};
                    }
                }

            //    draw(grid);

                // add the brick to the graph
                for(int id : supportedby){
                    if(id == -1){
                        root->above.push_back(nodes[b.id]);
                    //    nodes[b.id]->below.push_back(root);
                        continue;
                    }
                    nodes[b.id]->below.push_back(nodes[id]);
                    nodes[id]->above.push_back(nodes[b.id]);
                }
            }

            int ans =  0;

            // check which bricks can be deleted without other bricks falling
            for(int i = 0; i < n; i++){
                // check if bricks above have more than one brick below
                bool canbedeleted = true;
                for(Node* n : nodes[i]->above){
                    if(n->below.size() < 2){
                        canbedeleted = false;
                        break;
                    }
                }
                if(canbedeleted){
                    ans++;
                }
            }

            return std::to_string(ans);
        }

        struct Node{
            int id;
            vector<Node*> above;
            vector<Node*> below;

            Node(int id):id(id){}
        };

        void dfs(Node* node , vector<bool>& fallen,int& ans){

            if(!fallen[node->id]){
                int standingBelow = 0;
                for(Node* child : node->below){
                    if(!fallen[child->id])standingBelow++;
                }
                if(standingBelow > 0){
                    return;
                }
            }

            if(!fallen[node->id]){
                ans++;
                fallen[node->id] = true;
            }
            for(Node* child : node->above){
                dfs(child,fallen,ans);
            }
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            auto comp = [](const Brick& lhs, const Brick& rhs) { 
                return lhs.z > rhs.z;
            };
            priority_queue<Brick,vector<Brick>,decltype(comp)> bricks(comp);
            
            int minx = 0;
            int miny = 0;
            int maxx = 0;
            int maxy = 0;
            while (std::getline(std::cin, line)) {
                std::istringstream iss(line);
                // 4,6,74~4,6,76 to parse it represents both edges of the brick (4,6,74)x1 and (4,6,76)x2
                // therefore w = 4-4+1 = 1, h = 6-6+1 = 1, d = 76-74+1 = 3
                int x, y, z, w, h, d;
                char c;
                iss >> x >> c >> y >> c >> z >> c >> w >> c >> h >> c >> d;
                w = w-x+1;
                h = h-y+1;
                d = d-z+1;

                minx = std::min(minx, x);
                miny = std::min(miny, y);
                maxx = std::max(maxx, x+w);
                maxy = std::max(maxy, y+h);
                Brick b = {x,y,z,w,h,d,(int)bricks.size()};
                bricks.push(b);
            }

            // create a grid of bricks
            vector<vector<pair<int,int>>> grid(maxx, vector<pair<int,int>>(maxy, {0,-1}));// (curz, brickid)

            // graph of support
            // for each brick, find the bricks that are supporting it

            int n = bricks.size();

            Node* root = new Node(-1);
            vector<Node*> nodes(n, nullptr);
            for(int i = 0; i < n; i++){
                nodes[i] = new Node(i);
            }

            while(!bricks.empty()){
                Brick b = bricks.top();
                bricks.pop();
                // find ids of bricks that are supporting this brick
                int maxz = 0;
                set<int> supportedby;
                for(int i = b.x; i < b.x+b.w; i++){
                    for(int j = b.y; j < b.y+b.h; j++){
                        if(maxz <= grid[i][j].first){
                            if(maxz < grid[i][j].first)supportedby.clear();
                            supportedby.insert(grid[i][j].second);
                            maxz = grid[i][j].first;
                        }
                    }
                }
                // add the brick to the grid
                for(int i = b.x; i < b.x+b.w; i++){
                    for(int j = b.y; j < b.y+b.h; j++){
                        grid[i][j] = {maxz+b.d, b.id};
                    }
                }

            //    draw(grid);

                // add the brick to the graph
                for(int id : supportedby){
                    if(id == -1){
                        root->above.push_back(nodes[b.id]);
                    //    nodes[b.id]->below.push_back(root);
                        continue;
                    }
                    nodes[b.id]->below.push_back(nodes[id]);
                    nodes[id]->above.push_back(nodes[b.id]);
                }
            }

            int ans =  0;

            // check which bricks can be deleted without other bricks falling
            for(int i = 0; i < n; i++){
                // how many bricks would fall if this brick is deleted
                vector<bool> fallen(n,false);
                fallen[i] = true;
                dfs(nodes[i],fallen,ans);
            }

            return std::to_string(ans);
        }
    }
}

