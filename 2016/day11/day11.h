#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <unordered_set>
#include <cstring>

using namespace std;

namespace aoc2016{
    namespace day11{
        
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day11/day11sample")=="11");
            std::cout << solvedayp1("./2016/day11/day11") << std::endl;

            std::cout << "Part 2" << std::endl;
        //    assert (solvedayp2("./2016/day11/day11sample")=="-1");
            std::cout << solvedayp2("./2016/day11/day11") << std::endl;
        }

        int bfs(vector<vector<int>> objects, int nbFloors);
        
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int nbFloors = 0;        
            unordered_map<string,int> book;
            vector<vector<int>> objects(50,vector<int>(2,0));

            vector<vector<vector<int>>> floors(50,vector<vector<int>>(50,vector<int>(2,0)));
            int nbObjects = 0;
            while(getline(std::cin,line)){
                nbFloors++;
                stringstream ss(line);
                string word;
                while(word != "contains"){
                    ss >> word;
                }
                while(ss.peek() != EOF){
                    ss >> word;
                    if(word == "and" || word == "a" || word == "an")continue;
                    if(word == "nothing")break;
                    string typ;
                    auto it = word.find('-');
                    if(it == string::npos){
                        typ = "G";
                    }else{
                        word = word.substr(0,it);
                        typ = "M";
                    }
                    if(book.find(word) == book.end()){
                        book[word] = nbObjects++;
                    }
                    floors[nbFloors-1][book[word]][typ=="G"] = 1;
                    objects[book[word]][typ=="G"] = nbFloors-1;

                    ss >> word;
                }
            }

            objects.resize(nbObjects);

            int ans = bfs(objects,nbFloors);
            return std::to_string(ans);
        }

        bool isLegal(int e , vector<vector<int>>& objects){
            int n = objects.size();
            bool hasPoweredGen[50];
            memset(hasPoweredGen,0,sizeof(hasPoweredGen));
            for(int i = 0;i<n;i++){
                if(objects[i][0] == objects[i][1])hasPoweredGen[objects[i][1]] = true;
            }
  
            for(int i = 0;i<n;i++){
                if( hasPoweredGen[e] && objects[i][0] == e && objects[i][1]!=e)return false;
                if( hasPoweredGen[e+1] && objects[i][0] == e+1 && objects[i][1]!=e+1)return false;
                if( e>0 && hasPoweredGen[e-1] && objects[i][0] == e-1 && objects[i][1]!=e-1)return false;
            }
            
            return true;
        }

        bool isDone(vector<vector<int>>& objects,int nbFloors){
            int n = objects.size();
            for(int i = 0;i<n;i++){
                if(objects[i][0] != nbFloors-1 || objects[i][1] != nbFloors-1)return false;
            }
            return true;
        }

        long long getHash(int e, vector<vector<int>> objects){
            int n = objects.size();
            long long hash = 0;  
            sort(objects.begin(),objects.end());
            int mini = INT_MAX;
            for(int i = 0;i<n;i++){
                mini = min({objects[i][0],objects[i][1],mini});
                hash = hash*100 + objects[i][0]*10 + objects[i][1];
            }
            hash = hash*100 + e*10 + mini;
            return hash;
        }

        int bfs(vector<vector<int>> objects, int nbFloors){

            int depth = 0;

            unordered_set<int> memo;
            int n = objects.size();
            long long hash = getHash(0,objects);

            memo.insert(hash);

            queue<long long> queue;
            queue.push(hash);

            while(!queue.empty()){
                
                int s = queue.size();

                while(s--){

                    hash = queue.front();
                    queue.pop();

                    int minf = hash%10;
                    hash/=10;
                    int e = hash%10;
                    hash/=10;
                    
                    for(int i = 0;i<n;i++){
                        objects[i][1] = hash%10;
                        hash/=10;
                        objects[i][0] = hash%10;
                        hash/=10;
                    }

                    if(isDone(objects,nbFloors))return depth;

                    // can either go up or down carring 1 or 2 objects
                    // get 1 or 2 items from floor[e] and move up or down
                    bool moved2 = false;
                    for(int i = 0; i < n*2;i++){
                        int floor = objects[i/2][i%2];
                        if(floor != e)continue;

                        for(int j = i+1; j < n*2;j++){
                            int floor2 = objects[j/2][j%2];
                            if(floor2 != e)continue;

                            if(e < nbFloors-1){
                                objects[i/2][i%2]++;
                                objects[j/2][j%2]++;
                                if(isLegal(e,objects)){
                                    hash = getHash(e+1,objects);
                                    if(memo.find(hash) == memo.end()){
                                        queue.push(hash);
                                        moved2 = true;
                                        memo.insert(hash);
                                    }
                                }
                                objects[i/2][i%2]--;
                                objects[j/2][j%2]--;
                            }
                        }
                    }

                    if(moved2)continue;
                    
                    // get 1 item from floor[e] and move up or down
                    for(int i = 0; i < n*2;i++){
                        int floor = objects[i/2][i%2];
                        if(floor != e)continue;

                        if(e < nbFloors-1){
                            objects[i/2][i%2]++;
                            if(isLegal(e,objects)){
                                hash = getHash(e+1,objects);
                                if(memo.find(hash) == memo.end()){
                                    queue.push(hash);
                                    memo.insert(hash);
                                }
                            }
                            objects[i/2][i%2]--;
                        }

                        if(e > minf){
                            objects[i/2][i%2]--;
                            if(isLegal(e,objects)){
                                hash = getHash(e-1,objects);
                                if(memo.find(hash) == memo.end()){
                                    queue.push(hash);
                                    memo.insert(hash);
                                }
                            }
                            objects[i/2][i%2]++;
                        }
                    }
                }

                depth++;
            }

            return -1;
        }



        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int nbFloors = 0;        
            unordered_map<string,int> book;
            vector<vector<int>> objects(50,vector<int>(2,0));

            vector<vector<vector<int>>> floors(50,vector<vector<int>>(50,vector<int>(2,0)));
            int nbObjects = 2;
            while(getline(std::cin,line)){
                nbFloors++;
                stringstream ss(line);
                string word;
                while(word != "contains"){
                    ss >> word;
                }
                while(ss.peek() != EOF){
                    ss >> word;
                    if(word == "and" || word == "a" || word == "an")continue;
                    if(word == "nothing")break;
                    string typ;
                    auto it = word.find('-');
                    if(it == string::npos){
                        typ = "G";
                    }else{
                        word = word.substr(0,it);
                        typ = "M";
                    }
                    if(book.find(word) == book.end()){
                        book[word] = nbObjects++;
                    }
                    floors[nbFloors-1][book[word]][typ=="G"] = 1;
                    objects[book[word]][typ=="G"] = nbFloors-1;

                    ss >> word;
                }
            }

            objects.resize(nbObjects);

            int ans = bfs(objects,nbFloors);
            return std::to_string(ans);
        }
    }
}

