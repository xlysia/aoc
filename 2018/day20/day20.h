#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <complex>
#include <stack>
#include <queue>

using namespace std;

namespace aoc2018{
    namespace day20{
        using coord = complex<int>;

        struct Node{
            coord pos;
            Node* n;
            Node* s;
            Node* e;
            Node* w;

            Node(){
                pos = {0,0};
                n = nullptr;
                s = nullptr;
                e = nullptr;
                w = nullptr;
            }
            Node(int x, int y){
                pos = {x,y};
                n = nullptr;
                s = nullptr;
                e = nullptr;
                w = nullptr;
            }
        };
        

        std::string solveday(std::string p);
        std::string solveday(std::string p);
        void run(){
            std::cout << "Part 1 & 2" << std::endl;
            assert (solveday("./2018/day20/day20sample")=="31 0");
            assert (solveday("./2018/day20/day20sample2")=="23 0");
            assert (solveday("./2018/day20/day20sample3")=="3 0");
            assert (solveday("./2018/day20/day20sample4")=="10 0");
            assert (solveday("./2018/day20/day20sample5")=="18 0");
            std::cout << solveday("./2018/day20/day20") << std::endl;
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::cin.ignore(1);
            getline(std::cin, line);
            line.pop_back();

            struct hash{
                size_t operator()(const coord& c) const{
                    return std::hash<int>()(c.real()) ^ std::hash<int>()(c.imag());
                }
            };

            unordered_map<coord, Node*,hash> board;

            Node* root = new Node();
            Node* current = root;

            board[current->pos] = current;

            stack<coord> stack;

            for(char c : line){
                if(c == '('){
                    stack.push(current->pos);
                }else if(c == ')'){
                    stack.pop();
                }else if(c == '|'){
                    current = board[stack.top()];
                }else{
                    Node* next = nullptr;
                    if(c == 'N'){
                        if(board.find(current->pos + coord(0,-1)) == board.end()){
                            next = new Node(current->pos.real(), current->pos.imag()-1);
                            board[next->pos] = next;
                        }else{
                            next = board[current->pos + coord(0,-1)];
                        }
                        current->n = next;
                        next->s = current;
                    }else if(c == 'S'){
                        if(board.find(current->pos + coord(0,1)) == board.end()){
                            next = new Node(current->pos.real(), current->pos.imag()+1);
                            board[next->pos] = next;
                        }else{
                            next = board[current->pos + coord(0,1)];
                        }
                        current->s = next;
                        next->n = current;
                    }else if(c == 'E'){
                        if(board.find(current->pos + coord(1,0)) == board.end()){
                            next = new Node(current->pos.real()+1, current->pos.imag());
                            board[next->pos] = next;
                        }else{
                            next = board[current->pos + coord(1,0)];
                        }
                        current->e = next;
                        next->w = current;
                    }else if(c == 'W'){
                        if(board.find(current->pos + coord(-1,0)) == board.end()){
                            next = new Node(current->pos.real()-1, current->pos.imag());
                            board[next->pos] = next;
                        }else{
                            next = board[current->pos + coord(-1,0)];
                        }
                        current->w = next;
                        next->e = current;
                    }
                    current = next;
                }
            }

            int ans =  0;
            int ans2 = 0;

            // bfs to find the furthest room
            queue<Node*> q;
            q.push(root);
            unordered_set<Node*> visited;
            visited.insert(root);
            while(!q.empty()){
                int s = q.size();
                ans++;
                while(s--){
                    Node* n = q.front();
                    q.pop();
                    if(n->n != nullptr && visited.find(n->n) == visited.end()){
                        q.push(n->n);
                        visited.insert(n->n);
                        if(ans >= 1000)ans2++;
                    }
                    if(n->s != nullptr && visited.find(n->s) == visited.end()){
                        q.push(n->s);
                        visited.insert(n->s);
                        if(ans >= 1000)ans2++;
                    }
                    if(n->e != nullptr && visited.find(n->e) == visited.end()){
                        q.push(n->e);
                        visited.insert(n->e);
                        if(ans >= 1000)ans2++;
                    }
                    if(n->w != nullptr && visited.find(n->w) == visited.end()){
                        q.push(n->w);
                        visited.insert(n->w);
                        if(ans >= 1000)ans2++;
                    }

                }
            }
        

            return std::to_string(ans-1) + " " + std::to_string(ans2);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int ans = 0;
            return std::to_string(ans);
        }
    }
}

