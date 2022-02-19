#include <vector>
#include <iostream>
#include <algorithm>

class DSU {
public:
    DSU (int n): parent(n, 0), rank(n, 0) {
        for (int i = 0; i < n; ++i)
              parent[i] = i;
    }

    void make_set(int v){
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v){
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int x, int y){
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
    std::vector<int> parent;
    std::vector<int> rank;
};

struct Root{
    int begin;
    int end;
    int weight;
};

bool operator < (const Root& lhs, const Root& rhs) {
    return lhs.weight < rhs.weight;
}

class NOGraph{
public:
    NOGraph(int n): vert_count(n){}

    void AddEdge(int from, int to, int weight) {
        edges.push_back({from, to, weight});
        edges.push_back({to, from, weight});
    }

    int get_vert () const {
        return vert_count;
    }

    std::vector<Root> GetAdjs() const {
        return edges;
    }

private:
    std::vector<Root> edges;
    int vert_count = 0;
};

int MSTKruskal (const NOGraph& gr){
    int res = 0;
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
    int n, m;
    int from, to, weight;
    std::cin >> n >> m;
    NOGraph gr(n);

    for (int i = 0; i < m; ++i){
        std::cin >> from >> to >> weight;
        gr.AddEdge(from - 1, to - 1, weight);
    }

    std::cout << MSTKruskal(gr);

    return 0;
}
