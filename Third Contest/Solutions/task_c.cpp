#include <vector>
#include <iostream>
#include <algorithm>

class DSU {
public:
    DSU (size_t n): parent(n, 0), rank(n, 0) {
        for (size_t i = 0; i < n; ++i)
            parent[i] = i;
    }

    void make_set(size_t v){
        parent[v] = v;
        rank[v] = 0;
    }

    size_t find_set(size_t v){
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(size_t x, size_t y){
        x = find_set(x);
        y = find_set(y);
        if (x != y){
            if (rank[x] < rank[y])
                std::swap(x,y);
            parent[y] = x;
            if (rank[x] == rank[y])
                ++rank[x];
        }
    }

private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
};

struct Root{
    Root(size_t beg, size_t en, size_t w): begin(beg), end(en), weight(w) {}
    size_t begin;
    size_t end;
    size_t weight;
};

bool operator < (const Root& lhs, const Root& rhs) {
    return lhs.weight < rhs.weight;
}

class NOGraph{
public:
    NOGraph(size_t n): vert_count(n){}

    void AddEdge(size_t from, size_t to, size_t weight) {
        edges.push_back({from, to, weight});
    }

    size_t get_vert () const {
        return vert_count;
    }

    std::vector<Root> GetAdjs() const {
        return edges;
    }

private:
    std::vector<Root> edges;
    size_t vert_count;
};

size_t MSTKruskal (const NOGraph& gr){
    size_t res = 0;
    DSU dsu (gr.get_vert());
    std::vector<Root> edges = gr.GetAdjs();

    std::sort(edges.begin(), edges.end());

    for (const Root& edge : edges){
        if (dsu.find_set(edge.begin) != dsu.find_set(edge.end)){
            res += edge.weight;
            dsu.union_set(edge.begin, edge.end);
        }
    }
    return res;
}

int main(){
    size_t n, m;
    size_t from, to, weight;
    std::cin >> n >> m;

    NOGraph gr(n);

    std::vector<size_t> cost(n);
    for(size_t i = 0; i < n; ++i)
        std::cin >> cost[i];

    size_t min = 0;
    long long minA = std::numeric_limits<long long>::max();
    for (size_t i = 0; i < n; ++i){
        if (minA > cost[i]){
            min = i;
            minA = cost[i];
        }
    }

    for (size_t i = 0; i < n; ++i){
        gr.AddEdge(i, min, cost[i]+ minA);
    }

    for (size_t i = 0; i < m; ++i){
        std::cin >> from >> to >> weight;
        gr.AddEdge(from - 1, to - 1, weight);
    }

    std::cout << MSTKruskal(gr);
    return 0;
}
