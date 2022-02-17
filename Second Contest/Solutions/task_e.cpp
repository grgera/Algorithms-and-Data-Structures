#include <iostream>
#include <vector>

struct Edge {
    Edge(int from, int to, long double mult, long double com):
        from{from}, to{to}, multipier{mult}, comission{com} {};

    int from;
    int to;
    long double multipier;
    long double comission;
};

std::string Charge(int n, std::vector<Edge> &edges, int start, long double v) {
    std::vector<long double> d(n);
    d[start] = v;
    int x = 0;

    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < edges.size(); ++j) {
            if (d[edges[j].to] < (d[edges[j].from] - edges[j].comission) * edges[j].multipier) {
                d[edges[j].to] = (d[edges[j].from] - edges[j].comission) * edges[j].multipier;
                x = edges[j].to;
            }
        }
    }

    if (x != -1) {
        return "YES";
    } else {
        return "NO";
    }
}

int main() {
    int n, m, start;
    long double v;
    std::cin >> n >> m >> start >> v;
    std::vector<Edge> edges;

    for (size_t i = 0; i < m; ++i) {
        int from, to;
        long double RAB, CAB, RBA, CBA;
        std::cin >> from >> to;
        std::cin >> RAB >> CAB >> RBA >> CBA;
        edges.push_back(Edge(from - 1, to - 1, RAB, CAB));
        edges.push_back(Edge(to - 1, from - 1, RBA, CBA));
    }

    std::cout << Charge(n, edges, start - 1, v);

    return 0;
}
