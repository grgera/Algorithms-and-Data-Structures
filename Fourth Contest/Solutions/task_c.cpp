#include <iostream>
#include <vector>

class LcaSearch {
public:
    LcaSearch (const std::vector<size_t>& upper) {
        V = upper.size() + 1;
        log = 1;
        timer = 0;

        while ((1ull << log) <= V)
            ++log;

        Adj.resize(V);
        tin.resize(V, 0);
        tout.resize(V, 0);
        up.resize(V, std::vector<size_t>(log + 1));

        for (int i = 0; i < V - 1; ++i)
            Adj[upper[i]].emplace_back(i + 1);

        dfs(0);
    }

    size_t lca (size_t first, size_t second) {
        if (ancestor(first, second))
            return first;

        if (ancestor(second, first))
            return second;

        for (long vertex = log; vertex >= 0; --vertex)
            if (!ancestor(up[first][vertex], second))
                first = up[first][vertex];

        return up[first][0];
    }

private:
    std::vector<std::vector<size_t>> Adj, up;
    std::vector<size_t> tin, tout;
    size_t V, log, timer;

    void dfs (size_t vertex, size_t parent = 0) {
        tin[vertex] = ++timer;
        up[vertex][0] = parent;

        for (size_t i = 0; i < log; ++i)
            up[vertex][i + 1] = up[up[vertex][i]][i];

        for (auto &to : Adj[vertex])
            if (to != parent)
                dfs(to, vertex);

        tout[vertex] = ++timer;
    }

    bool ancestor(size_t a, size_t b) const {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }
};

int main() {
    size_t n, m;
    size_t a1, a2, x, y, z;
    size_t v = 0, sum = 0;
    std::cin >> n >> m;

    std::vector<size_t> upper(n - 1);
    for (const auto& ancestor : upper)
        std::cin >> ancestor;

    LcaSearch tree = upper;

    std::cin >> a1 >> a2 >> x >> y >> z;
    for (int i = 0; i < m; ++i) {
        v = tree.lca((a1 + v) % n, a2);
        sum += v;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }

    std::cout << sum + 1;
    return 0;
}
