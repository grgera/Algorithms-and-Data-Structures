#include <vector>
#include <algorithm>
#include <iostream>

const int min = -1000000000;

class SegmentTree{
public:
    SegmentTree(int n, std::vector<int> v){
        a = v;
        tree.resize(4*n, -1);
        tmp.resize(4*n, 0);
        kol = n;
    }

    void build(int v, int l, int r){
        if (l == r - 1){
            tree[v] = a[l];
            return;
        }

        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        tree[v] = std::max(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void push(int v){
        if (tmp[v] != 0){

            if (2 * v + 1 < tmp.size())
                tmp[2 * v + 1] += tmp[v];
            if (2 * v + 2 < tmp.size())
                tmp[2 * v + 2] += tmp[v];

            tree[v] += tmp[v];
            tmp[v] = 0;
        }
    }

    int LocMax(int v, int l, int r, int askl, int askr){
        if (l >= askr || r <= askl){
            return min;
        }

        push(v);

        if (l >= askl && r <= askr){
            return tree[v];
        }

        int m = (l + r) / 2;
        return std::max(LocMax(2 * v + 1, l, m, askl, askr), LocMax(2 * v + 2, m, r, askl, askr));
    }

    void change(int v, int l, int r, int askl, int askr, int val){
        if (l >= askr || r <= askl){
            return;
        }

        if (l >= askl && r <= askr){
            tmp[v] += val;
            return;
        }

        push(v);

        int m = (l + r) / 2;
        change(2 * v + 1, l, m, askl, askr, val);
        change(2 * v + 2, m, r, askl, askr, val);
        tree[v] = std::max(tree[2 * v + 1] + tmp[2 * v + 1], tree[2 * v + 2] + tmp[2 * v + 2]);
    }

private:
    std::vector<int> a;
    std::vector<int> tree;
    std::vector<int> tmp;
    int kol;
};

int main(){
    int n, tmp, siz, it;
    int from, to, kol;
    std::cin >> n;
    std::vector<int> a(n - 1);

    for (int i = 0; i < n - 1; ++i){
        std::cin >> tmp;
        a[i] = tmp;
    }

    SegmentTree t(n, a);
    t.build(0, 0, n);

    std::vector<int> r;
    std::cin >> siz >> it;
    for (int i = 0; i < it; ++i){
        std::cin >> from >> to >> kol;
        int res = t.LocMax(0, 0, n, from, to);
        if (res + kol > siz){
            r.push_back(i);
        }
        else {
            t.change(0, 0, n, from, to, kol);
        }
    }

    for (const auto& x : r)
        std::cout << x << " ";

    return 0;
}
