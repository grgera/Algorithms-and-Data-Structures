#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using Vertex = std::size_t;

class IGraph {
public:
    virtual ~IGraph() {};
    virtual void AddEdge(Vertex from, Vertex to) = 0;
    virtual size_t get_size () const = 0;
    virtual std::vector<Vertex> GetAdj(Vertex vertex) const = 0;
};

class OrientalListGraph: public IGraph {
public:
    OrientalListGraph (size_t verticesCount): adjList (verticesCount) {}

    void AddEdge (Vertex from, Vertex to) override {
        adjList.at(from).push_back(to);
    }

    std::vector<Vertex> GetAdj (Vertex v) const override {
        return adjList.at(v);
    }

    size_t get_size () const override {
        return adjList.size();
    }
private:
    std::vector<std::vector<Vertex>> adjList;
};

enum class Color{
    White,
    Grey,
    Black
};

void OrDFS(Vertex V, const OrientalListGraph& graph, std::vector<Color>& colors,
           std::vector<Vertex>& result, bool& flag){
    std::stack<Vertex> st;
    colors[V] = Color::Grey;

    for (auto x : graph.GetAdj(V)){
        if (colors[x] == Color::White){
            OrDFS(x, graph, colors, result, flag);
        }
        else if (colors[x] == Color::Grey){
            flag = 0;
            return;
        }
    }

    colors[V] = Color::Black;
    result.push_back(V);
}

std::vector<Vertex> OrTopologicalSort (OrientalListGraph& graph){
    std::vector<Color> colors(graph.get_size(), Color::White);
    std::vector<Vertex> result;
    bool flag = true;

    for (Vertex i = 0; i < graph.get_size(); ++i) {
        if (colors[i] == Color::White) {
            OrDFS(i, graph, colors, result, flag);
        }
    }

    if (flag) {
        std::reverse(result.begin(), result.end());
        return result;
    } else
        return {};
}

int main(){
    Vertex n;
    size_t m;
    Vertex k,t;
    std::cin >> n >> m;
    OrientalListGraph gr(n);

    for (auto i = 0; i < m; ++i){
        std::cin >> k >> t;
        gr.AddEdge(k,t);
    }

    auto res = OrTopologicalSort(gr);

    if (res.size() == 0){
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" << std::endl;
        for (auto x : res)
            std::cout << x << " ";
    }
    return 0;
}
