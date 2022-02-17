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

int ModDijkstra (const OrientalListGraph& gr, Vertex v, Vertex dst, int lim){
    std::vector<size_t> len (gr.get_size(), 0);
    std::vector<size_t> res (gr.get_size(), -1);
    std::priority_queue<std::pair<Vertex, size_t>> q;
    res[v] = 0;
    q.push({v,0});

    while (!q.empty()){
        auto curr = q.top();
        auto curr_len = len[curr.first] + 1;
        if (res[curr.first] == -1){
            return res[dst];
        }
        q.pop();

        for (auto& next : gr.GetAdj(curr.first)){ // next = std::pair<Vertex, size_t>
            if (curr.second + next.second < res[next.first] && curr_len <= lim){
                res[next.first] = curr.second + next.second;
                len[next.first] = curr_len;

                if (len[next.first] <= lim)
                    q.push({next.first, curr.second + next.second});
            }
        }
    }
    return res[dst];
}


int main(){
    int n, m, k, src, dst;
    Vertex from, to, w;
    std::cin >> n >> m >> k >> src >> dst;
    OrientalListGraph gr(n);

    for (int i = 0; i < m; ++i){
        std::cin >> from >> to >> w;
        gr.AddEdge(from - 1, to - 1, w);
    }

    std::cout << ModDijkstra(gr, src - 1, dst - 1, k);

    return 0;
}
