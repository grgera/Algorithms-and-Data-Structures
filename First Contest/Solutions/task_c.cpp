#include <iostream>
#include <vector>
#include <algorithm>

using Vertex = size_t;

enum class Color1{
    White,
    Black
};

class IGraph {
public:
    virtual ~IGraph() {};
    virtual void AddEdge (Vertex v1, Vertex v2) = 0;
    virtual std::vector<Vertex> GetAdj (Vertex v) const = 0;
    virtual size_t get_size () const = 0;
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

    void invertion();

private:
    std::vector<std::vector<Vertex>> adjList;
};

void OrientalListGraph::invertion() {
    std::vector<std::vector<Vertex>> inv_vect (get_size());
    for (Vertex i = 0; i < adjList.size(); ++i){
        for (auto j : adjList[i]){
            inv_vect[j].push_back(i);
        }
    }
    adjList = std::move(inv_vect);
}

void Dfs (std::vector<Color1>& colors, const OrientalListGraph& gr, Vertex v,
          std::vector<Vertex>& ans)
{
    colors[v] = Color1::Black;
    for (auto i : gr.GetAdj(v)){
        if (colors[i] == Color1::White)
            Dfs(colors, gr, i, ans);
    }
    ans.push_back(v);
}

std::vector<std::vector<Vertex>> GetSCC (const OrientalListGraph& gr){
    std::vector<std::vector<Vertex>> result;
    std::vector<Color1> colors (gr.get_size(), Color1::White);
    OrientalListGraph rev = gr;
    rev.invertion();
    std::vector<Vertex> revDfc;

    for (Vertex i = 0; i < colors.size(); ++i){
        if (colors[i] == Color1::White)
            Dfs(colors, rev, i, revDfc);
    }

    colors = std::vector<Color1> (gr.get_size(), Color1::White);

    for (; revDfc.size() > 0; revDfc.pop_back()){
        auto i = revDfc.back();
        if (colors[i] == Color1::White){
            std::vector<Vertex> Scc;
            Dfs(colors, gr, i, Scc);
            result.push_back(Scc);
        }
    }

    return result;
}

int kvartal (const OrientalListGraph& gr){
    std::vector<std::vector<Vertex>> res = GetSCC(gr);
    std::vector<Vertex> comp(gr.get_size());
    std::vector<bool> source(res.size(), false);
    std::vector<bool> stock(res.size(), false);
    size_t non_source = 0;
    size_t non_stock = 0;

    for (int i = 0; i < res.size(); ++i)
        for (int j = 0; j < res[i].size(); ++j)
            comp[res[i][j]] = i;

    if (res.size() == 1)
        return 0;

    for (int i = 0; i < gr.get_size(); ++i)
        for (size_t currentV : gr.GetAdj(i))
            if (comp[i] != comp[currentV]) {
                source[comp[i]] = true;
                stock[comp[currentV]] = true;
            }

    for (int i = 0; i < res.size(); ++i) {
        non_source += !source[i];
        non_stock += !stock[i];
    }

    return non_stock > non_source ? non_stock : non_source;
}

int main(){
    int n,m;
    std::cin >> n >> m;
    OrientalListGraph gr(n);
    Vertex from, to;

    for (int i = 0; i < m; ++i){
        std::cin >> from >> to;
        gr.AddEdge(from - 1, to - 1);
    }

    std::cout << kvartal(gr);
    return 0;
}
