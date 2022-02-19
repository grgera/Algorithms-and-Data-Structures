#include <vector>
#include <iostream>
#include <string>

void PrintCut (const std::vector<int>& best_cut, int n){
    std::vector<bool> check(n, true);

    for (int i = 0; i < best_cut.size(); ++i){
        std::cout << best_cut[i] + 1 << " ";
        check[best_cut[i]] = false;
    }
    std::cout << std::endl;
    for (int i = 0; i < n; ++i){
        if (check[i])
            std::cout << i + 1<< " ";
    }
}

void MinCut (std::vector<std::vector<int>>& edges, int n){
    int best_cost = -1;
    std::vector<int> best_cut;

    std::vector<std::vector<int>> v(n);
    for (int i = 0; i < n; ++i) {
        v[i].assign(1, i);
    }

    std::vector<int> w(n);
    std::vector<bool> exist(n, true);
    std::vector<bool> in_a(n);

    for (int ph = 0; ph < n -1; ++ph){
        in_a.assign(in_a.size(), false);
        w.assign(w.size(), 0);

        for (int it = 0, prev = 0; it < n - ph; ++it){
            int sel = -1;
            for (int i = 0; i < n; ++i){
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            }
            if (it == n - ph - 1){
                if (w[sel] < best_cost || best_cost == -1){
                    best_cost = w[sel];
                    best_cut = v[sel];
                }
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < n; ++i){
                    edges[prev][i] = edges[i][prev] += edges[sel][i];
                }
                exist[sel] = false;
            }
            else {
                in_a[sel] = true;
                for (int i = 0; i < n; ++i){
                    w[i] += edges[sel][i];
                }
                prev = sel;
            }
        }
    }
    PrintCut(best_cut, n);
}

int main(){
    int n;
    std::string str;
    int inf = INT_MAX;

    std::cin >> n;
    std::vector<std::vector<int>> edges(n);

    for (int i = 0; i < n; ++i){
        std::cin >> str;
        for (int j = 0; j < n; ++j){
            if (str[j] == '1'){
                edges[i].push_back(1);
            }
            else {
                edges[i].push_back(0);
            }
        }
    }

    MinCut(edges, n);
    return 0;
}
