#include <iostream>
#include <vector>
#include <queue>

using Vertex = std::size_t;

class IGraph {
public:
    virtual ~IGraph() {};
    virtual void AddEdge(Vertex from, Vertex to, double weight) = 0;
    virtual size_t get_size () const = 0;
    virtual std::vector<std::pair<Vertex, double>> GetAdj(Vertex vertex) const = 0;
};

class NonOrientionalListGraph : public IGraph {
public:
    NonOrientionalListGraph(size_t verticesCount) : graph (verticesCount) {}

    void AddEdge(Vertex from, Vertex to, double weight) override {
        graph.at(from).push_back({to, weight});
        graph.at(to).push_back({from, weight});
    }

    size_t get_size () const override {
        return graph.size();
    }

    std::vector<std::pair<Vertex, double>> GetAdj(Vertex vertex) const override {
        return graph.at(vertex);
    }
private:
    std::vector<std::vector<std::pair<Vertex, double>>> graph;
};

double ModDijkstra (const NonOrientionalListGraph& gr, size_t src, size_t dst){
    std::vector<double> res (gr.get_size(), -1);
    std::priority_queue<std::pair<Vertex, double>> q;
    res[src] = 1.0;
    q.push({src, 1});
    while (!q.empty()){
        auto curr = q.top();

        if (curr.second < res[curr.first])
            continue;

        q.pop();
        for (auto& next : gr.GetAdj(curr.first)){
            if (res[next.first] == -1 ||curr.second * next.second > res[next.first]){
                q.push({next.first, curr.second * next.second});
                res[next.first] = curr.second * next.second;
            }
        }
    }
    return 1.0 - res[dst];
}

int main(){
    size_t n, m, src, dst;
    double from, to, w;
    std::cin >> n >> m >> src >> dst;
    NonOrientionalListGraph gr(n);
    for (int i = 0; i < m; ++i){
        std::cin >> from >> to >> w;
        gr.AddEdge(from - 1, to - 1, 1 - w/100);
    }

    std::cout << ModDijkstra(gr, src - 1, dst - 1);

    return 0;
}