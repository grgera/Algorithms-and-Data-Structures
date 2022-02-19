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

enum class Color{
    White,
    Grey,
    Black
};

std::vector<size_t> PrimasAlgo (const NonOrientionalListGraph& gr, Vertex v){
    std::vector<Color> colors (gr.get_size(), Color::White);
    std::vector<size_t> prev (gr.get_size(), -1);
    std::vector<size_t> key (gr.get_size(), -1);
    std::priority_queue<std::pair<size_t, Vertex>, std::vector<std::pair<size_t, Vertex>>,
            std::greater<std::pair<size_t, Vertex>>> q;

    key[v] = 0;
    q.push({0,v});

    int res = 0;
    while (!q.empty()){
        auto curr = q.top();
        q.pop();

        if (colors[curr.second] == Color::White && prev[v] != -1){
            res += key[v];
        }

        colors[curr.second] = Color::Black;
        for (auto& next : gr.GetAdj(curr.second)){
            if (colors[next.first] == Color::White && key[next.first] > next.second){
                key[next.first] = next.second;
                prev[next.first] = curr.second;
                q.push({key[next.first], next.first});
            }
        }
    }
    return key;
}

int main(){
    size_t n, m;
    double from, to, w;
    std::cin >> n >> m;
    NonOrientionalListGraph gr(n);

    for (int i = 0; i < m; ++i){
        std::cin >> from >> to >> w;
        gr.AddEdge(from - 1, to - 1, w);
    }

    int res = 0;
    auto key_vect = PrimasAlgo(gr, 0);
    for (auto& r : key_vect)
        res += r;

    std::cout << res;

    return 0;
}
