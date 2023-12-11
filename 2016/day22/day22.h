#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <utils/cvutils.h>


namespace aoc2016{
    namespace day22{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2016/day22/day22") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day22/day22sample")=="7");
            std::cout << solvedayp2("./2016/day22/day22") << std::endl;
        }

        struct Node{
            int x;
            int y;
            int used;
            int avail;
        };

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            /*
            root@ebhq-gridcenter# df -h
Filesystem              Size  Used  Avail  Use%
/dev/grid/node-x0-y0     87T   71T    16T   81%
/dev/grid/node-x0-y1     93T   72T    21T   77%
/dev/grid/node-x0-y2     87T   67T    20T   77%
                parse file using a struct with x,y,used,avail
            */

            getline(cin, line); // skip first 2 lines
            getline(cin, line);
            vector<vector<Node>> grid(50, vector<Node>(50));
            int m= 0,n=0;
            while(cin.good()){
                std::getline(cin, line);
                std::istringstream iss(line);
                std::string token;
                iss >> token;// get rid of /dev/grid/node-x
                // token = /dev/grid/node-x0-y0
                // extract 0, 0 
                int x = std::stoi(token.substr(16, token.find("-y")-16));
                int y = std::stoi(token.substr(token.find("-y")+2));

                iss >> token; // get rid of size
                iss >> token; // get rid of used
                int used = std::stoi(token.substr(0, token.find("T")));
                iss >> token; // get rid of avail
                int avail = std::stoi(token.substr(0, token.find("T")));
                grid[x][y] = {x, y, used, avail};
                m = max(m, x+1);
                n = max(n, y+1);
            }

            int ans =  0;
            
            for(int k1 = 0;k1 < m*n;k1++){

                if(grid[k1/n][k1%n].used == 0) continue;
                for(int k2 = 0;k2 < m*n;k2++){
                    if(k1 == k2) continue;
                    if(grid[k1/n][k1%n].used <= grid[k2/n][k2%n].avail){
                        ans++;
                    }
                }
            }

            return std::to_string(ans);
        }

        int bfs(pair<int,int>& start, pair<int,int>& goal, vector<vector<char>>& board, pair<int,int> dir[4]){
            int m = board.size();
            int n = board[0].size();
            int ans = 0;
            queue<pair<int,int>> q;
            q.push(start);
            bool visited[m][n];
            memset(visited, false, sizeof(visited));
            visited[start.first][start.second] = true;
        //   setPixel(start.first,start.second,cv::Vec3b(0,120,255));
            while(!q.empty()){
                int size = q.size();
                while(size--){
                    auto [i,j] = q.front();
                    q.pop();

                    for(int k = 0;k < 4;k++){
                        auto [x,y] = dir[k];
                        x+= i,y+=j;
                        if(x < 0 || x >= m || y < 0 || y >= n) continue;
                        if(board[x][y] == '#' || board[x][y] == 'G' || visited[x][y]) continue;
                        if(goal.first == x && goal.second == y){
                            // resize(10);
                            // showResize("Day 22",0);
                            return ans+1;
                        }
                        // setPixel(start.first,start.second,cv::Vec3b(0,120,255));
                        // resize(10);
                        // showResize("Day 22",0);
                        visited[x][y] = true;
                        q.push({x,y});
                    }
                }
                ans++;
            }

            return 9999;
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            /*
            root@ebhq-gridcenter# df -h
Filesystem              Size  Used  Avail  Use%
/dev/grid/node-x0-y0     87T   71T    16T   81%
/dev/grid/node-x0-y1     93T   72T    21T   77%
/dev/grid/node-x0-y2     87T   67T    20T   77%
                parse file using a struct with x,y,used,avail
            */

            getline(cin, line); // skip first 2 lines
            getline(cin, line);
            vector<vector<Node>> grid(50, vector<Node>(50));
            int m= 0,n=0;
            while(cin.good()){
                std::getline(cin, line);
                std::istringstream iss(line);
                std::string token;
                iss >> token;// get rid of /dev/grid/node-x
                // token = /dev/grid/node-x0-y0
                // extract 0, 0 
                int x = std::stoi(token.substr(16, token.find("-y")-16));
                int y = std::stoi(token.substr(token.find("-y")+2));

                iss >> token; // get rid of size
                iss >> token; // get rid of used
                int used = std::stoi(token.substr(0, token.find("T")));
                iss >> token; // get rid of avail
                int avail = std::stoi(token.substr(0, token.find("T")));
                grid[x][y] = {x, y, used, avail};
                m = max(m, x+1);
                n = max(n, y+1);
            }

            int ans = 0;
            pair<int,int> dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};

            vector<vector<char>> board(m, vector<char>(n,'#'));
            pair<int,int> empty;
            
            newBackgroundFrame(cv::Size(m,n),cv::Scalar(0,0,0));

            for(int i = 0; i < m;i++){
                for(int j = 0;j < n;j++){
                    if(grid[i][j].used == 0){
                        empty = {i,j};
                        board[i][j] = '.';
                        setBackgroundPixel(i,j,cv::Vec3b(255,255,255));
                        continue;
                    }
                    for(auto [x,y] : dir){
                        x+=i,y+=j;
                        if(x<0 || x>=m || y<0 || y>=n) continue;
                        if(grid[i][j].used <= grid[x][y].avail + grid[x][y].used && grid[i][j].used < 200){
                            board[i][j] = '.';
                            setBackgroundPixel(i,j,cv::Vec3b(255,255,255));
                            break;
                        }
                    }
                }
            }

            board[m-1][0] = 'G';
            int k = m;


            newFrame(cv::Size(m,n),cv::Scalar(0,0,0));
            resize(10);
            showResize("Day 22",1000);
            while(--k){
                newFrame(cv::Size(m,n),cv::Scalar(0,0,0));
                pair<int,int> goal = {k-1,0};

                int tmp = bfs(empty, goal, board,dir)+1;
                ans += tmp;
                empty = {k,0};
                board[k][0] = '.';
                board[k-1][0] = 'G';
            }

            return to_string(ans);
        }
    }
}

