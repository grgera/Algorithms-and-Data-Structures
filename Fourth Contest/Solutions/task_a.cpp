#include <iostream>
#include <vector>
#include <algorithm>

class SparceTable{
public:
    SparceTable(int n): v(n), logs(n+1), kol{n} {}

    void AddVect (std::vector<int>& v){
        logs[1] = 0;
        for (int i = 2; i <= kol; ++i){
            logs[i] = logs[i >> 1] + 1;
        }
        st.resize(logs[kol] + 1, std::vector<std::pair<int, int>>(kol));
        for (int i = 0; i < kol; ++i){
            st[0][i] = {v[i], i};
        }
        for (int level = 1; (1 << level) <= kol; ++level){
            for (int i = 0; i + (1 << level) <= kol; ++i){
                st[level][i] = std::min(st[level - 1][i], st[level - 1][i + (1 << (level -1))]);
            }
        }
    }

    std::pair<int, int> RMQ (int l, int r){
        if (r < l) {
            return {INT_MAX, -1};
        }
        int len = r - l + 1;
        int level = logs[len];
        return std::min(st[level][l], st[level][r - (1 << level) + 1]);
    }

    int SecondStat (int l, int r){
        std::pair<int, int> min = RMQ(l,r);
        std::pair<int, int> min_left = RMQ(l, min.second - 1);
        std::pair<int, int> min_right = RMQ(min.second + 1, r);
        return std::min(min_left.first, min_right.first);
    }


private:
    std::vector<std::vector<std::pair<int, int>>> st;
    std::vector<int> logs;
    std::vector<int> v;
    int kol;
};


int main(){
    int n, m, a;
    int l, r;
    std::cin >> n >> m;
    std::vector<int> v;
    for (int i = 0; i < n; ++i){
        std::cin >> a;
        v.push_back(a);
    }

    SparceTable st(n);
    st.AddVect(v);
    for (int i = 0; i < m; ++i){
        std::cin >> l >> r;
        std::cout << st.SecondStat(l - 1, r -1) << std::endl;
    }

    return 0;
}
