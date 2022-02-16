#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using Vertex = std::size_t;

class IGraph {
public:
    virtual ~IGraph() {};
    virtual void AddEdge(Vertex from, Vertex to) = 0;
    virtual size_t get_size () const = 0;
    virtual std::vector<Vertex> GetAdj(Vertex vertex) const = 0;
};

class NonOrientionalListGraph : public IGraph {
public:
    NonOrientionalListGraph(size_t verticesCount) : graph (verticesCount) {}

    void AddEdge(Vertex from, Vertex to) override {
        graph.at(from).push_back(to);
        graph.at(to).push_back(from);
    }

    size_t get_size () const override {
        return graph.size();
    }

    std::vector<Vertex> GetAdj(Vertex vertex) const override {
        return graph.at(vertex);
    }
private:
    std::vector<std::vector<Vertex>> graph;
};


enum class Color{
    White,
    Grey,
    Black
};

std::vector<Vertex> Bfs (Vertex v, const NonOrientionalListGraph& gr){
    std::vector<Color> colors(gr.get_size(), Color::White);
    std::queue<Vertex> q;
    std::vector<Vertex> len(gr.get_size());

    len[v] = 0;
    colors[v] = Color::Grey;
    q.push(v);
    while (!q.empty()){
        Vertex top = q.front();
        q.pop();
        for (auto x : gr.GetAdj(top)){
            if (colors[x] == Color::White){
                q.push(x);
                colors[x] = Color::Grey;
                len[x] = len[top] + 1;
            }
        }
        colors[top] = Color::Black;
    }
    return len;
}

int FindWay (int leo, int mat, int milk, const NonOrientionalListGraph& gr){
    std::vector<std::vector<Vertex>> bfs_all;
    bfs_all.push_back(Bfs(leo, gr));
    bfs_all.push_back(Bfs(mat, gr));
    bfs_all.push_back(Bfs(milk, gr));
    int res = INT_MAX;

    for (int i = 0; i < gr.get_size(); ++i){
        int sum = bfs_all[0][i] + bfs_all[1][i] + bfs_all[2][i];
        if (sum < res)
            res = sum;
    }

    return res;
}

int main(){
    int n, k;
    Vertex from, to;
    Vertex leo, mat, milk;
    std::cin >> n >> k >> leo >> mat >> milk;
    NonOrientionalListGraph gr(n);

    for (int i = 0; i < k; ++i){
        std::cin >> from >> to;
        gr.AddEdge(from - 1, to - 1);
    }

    std::cout << FindWay(leo - 1, mat - 1, milk - 1, gr);
    return 0;
}
