#include <vector>
#include <iostream>
#include <string>

void FloydWarshall(std::vector<std::vector<int>>& edges, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            for (int k = 0; k < n; ++k){
                if (edges[j][k] > edges[j][i] + edges[i][k])
                    edges[j][k] = edges[j][i] + edges[i][k];
            }
        }
    }
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
            if (str[j] == '0'){
                edges[i].push_back(inf);
            }
            else {
                edges[i].push_back(1);
            }
        }
    }

    FloydWarshall(edges, n);

    for (int i = 0; i < edges.size(); ++i){
        for (int j = 0; j < n; ++j){
            if (edges[i][j] < inf)
                std::cout << 1;
            else
                std::cout << 0;
        }
        std::cout << std::endl;
    }
    return 0;
}
