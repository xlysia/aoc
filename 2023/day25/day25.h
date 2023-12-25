#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <map>

#include "utils/karger.h"

using namespace std;  

namespace aoc2023{
    namespace day25{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day25/day25sample")=="54");
            std::cout << solvedayp1("./2023/day25/day25") << std::endl;

        }
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            std::map<string, int> book;
            vector<vector<int>> adj;
            int E = 0;
            while (getline(cin, line)) {
                stringstream ss(line);
                string key;
                ss >> key;
                key.pop_back();
                if(book.find(key)==book.end()){
                    book[key] = book.size();
                    adj.push_back(vector<int>());
                }
                while(ss >> line){
                    if(book.find(line)==book.end()){
                        book[line] = book.size();
                        adj.push_back(vector<int>());
                    }
                    adj[book[key]].push_back(book[line]);
                    E++;
//                    adj[book[line]].push_back(book[key]);
                }
            }

            int V = adj.size();  // Number of vertices in graph
              // Number of edges in graph
            struct Graph* graph = createGraph(V, E);
            int k = 0;
            for(int i=0; i<(int)adj.size(); i++){
                for(int j=0; j<(int)adj[i].size(); j++){
                    graph->edge[k].src = i;
                    graph->edge[k].dest = adj[i][j];
                    k++;
                }
            }

            while(1){
                auto [s1,s2] = kargerMinCut(graph);
                if(s1 * s2 != V-1){
                    cout << "FOUND A RESULT " << s1*s2 << " group sizes: " << s1 << " " << s2 << endl;
                    return to_string(s1*s2);
                }
            }

            return "FAILED";
        }
    }
}

