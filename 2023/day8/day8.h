#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <unordered_set>
#include <numeric>

using namespace std;

namespace aoc2023{
    namespace day8{

        class Node{
            public:
                string name;
                Node* left;
                Node* right;
                Node(string n, Node* l, Node* r): name(n), left(l), right(r){}
        };

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day8/day8sample")=="6");
            std::cout << solvedayp1("./2023/day8/day8") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day8/day8p2sample")=="6");
            std::cout << solvedayp2("./2023/day8/day8") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);
            
            string moves = line;
            int n = moves.size();
            getline(std::cin, line);

            unordered_map<string,Node*> nodes;


            while(std::cin.peek() != EOF){
                getline(std::cin, line);
                //line form is  AAA = (BBB, BBB)
                string name;
                name = line.substr(0,3);
                string left = line.substr(7,3);
                string right = line.substr(12,3);
                if(nodes.find(left) == nodes.end())
                    nodes[left] = new Node(left, nullptr, nullptr);
                if(nodes.find(right) == nodes.end()) 
                    nodes[right] = new Node(right, nullptr, nullptr);   
                if(nodes.find(name) == nodes.end())
                    nodes[name] = new Node(name, nodes[left], nodes[right]);
                else{
                    nodes[name]->left = nodes[left];
                    nodes[name]->right = nodes[right];
                }
            }

            Node* node = nodes["AAA"];
            int move = 0;

            while(node->name != "ZZZ"){;
                node = moves[move++%n] == 'L' ? node->left : node->right;
            }
            return std::to_string(move);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);
            
            string moves = line;
            int n = moves.size();
            getline(std::cin, line);

            unordered_map<string,Node*> nodes;
            vector<string> curr;


            while(std::cin.peek() != EOF){
                getline(std::cin, line);
                //line form is  AAA = (BBB, BBB)
                string name;
                name = line.substr(0,3);
                
                if(name.back()=='A'){
                    curr.push_back(name);
                }

                string left = line.substr(7,3);
                string right = line.substr(12,3);
                if(nodes.find(left) == nodes.end())
                    nodes[left] = new Node(left, nullptr, nullptr);
                if(nodes.find(right) == nodes.end()) 
                    nodes[right] = new Node(right, nullptr, nullptr);   
                if(nodes.find(name) == nodes.end())
                    nodes[name] = new Node(name, nodes[left], nodes[right]);
                else{
                    nodes[name]->left = nodes[left];
                    nodes[name]->right = nodes[right];
                }
            }

            int move = 0;

            vector<unordered_map<string,int>> visited;
            int i = 0;
            vector<int> cycles;
            visited.emplace_back();
            while(i<(int)curr.size()){
                curr[i] = moves[move%n] == 'L'?nodes[curr[i]]->left->name:nodes[curr[i]]->right->name;
                move++;
                if(curr[i].back()== 'Z'){
                    string key = curr[i]+to_string(move%n);
                    if(visited.back().find(key) != visited.back().end()){
                        cycles.push_back(move-visited.back()[key]);
                        
                        // cout << "cycle found for " << i<<" at key " << key<<" "<< move-visited.back()[key];
                        // for(auto [k,v]:visited.back()){
                        //     cout << "(" <<k << " ," << v << " )";
                        // }
                        // cout << endl;
                        i++;
                        move = 0;
                        
                    }
                    else{
                        visited.back()[key] = move;
                    }
                }
            }
            long long ans = 1;
            for(int i = 0; i < (int)cycles.size(); i++){
                ans = std::lcm(ans, (long long)cycles[i]);
            }
            return std::to_string(ans);
        }
    }
}

