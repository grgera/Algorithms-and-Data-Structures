#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using Vertex = size_t;

class IGraph {
public:
    virtual ~IGraph() {};
    virtual void AddEdge (Vertex v1, Vertex v2, size_t weight) = 0;
    virtual std::vector<std::pair<Vertex, size_t>> GetAdj (Vertex v) const = 0;
    virtual size_t get_size () const = 0;
};

class OrientalListGraph: public IGraph {
public:
    OrientalListGraph (size_t verticesCount): adjList (verticesCount) {}

    void AddEdge (Vertex from, Vertex to, size_t weight) override {
        adjList.at(from).push_back({to, weight});
    }

    std::vector<std::pair<Vertex, size_t>> GetAdj (Vertex v) const override {
        return adjList.at(v);
    }

    size_t get_size () const override {
        return adjList.size();
    }

private:
    std::vector<std::vector<std::pair<Vertex, size_t>>> adjList;
};

std::pair<Vertex, Vertex> GetNewAdj(Vertex v, Vertex m){
    return {(v + 1) % m, (v * v + 1) % m};
}


int FindWay1(int a, int b, Vertex m, Vertex src, Vertex dst){
    std::vector<size_t> res (m, -1);
    std::priority_queue<Vertex> q;
    res[src] = 0;
    q.push(src);

    while (!q.empty()){
        Vertex curr = q.top();
        std::pair<Vertex, Vertex> x = GetNewAdj(curr, m);
        q.pop();

        if (res[x.first] == -1 || res[curr] + a < res[x.first]){
            q.push(x.first);
            res[x.first] = res[curr] + a;
        }

        if(res[x.second] == -1 || res[curr] + b < res[x.second]){
            q.push(x.second);
            res[x.second] = res[curr] + b;
        }
    }
    return res[dst];
}


int main(){
    int a,b;
    Vertex m, src, dst;
    std::cin >> a >> b >> m >> src >> dst;

    std::cout << FindWay1(a, b, m, src, dst);

    return 0;
}