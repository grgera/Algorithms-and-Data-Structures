#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class ImplicitTreap{
public:
    ImplicitTreap(): _root(nullptr) {}

    void insert(size_t position, const std::string& value){
        Node* current = new Node(value);
        std::pair<Node*, Node*> ans = split(_root, position);
        Node* right = merge(current, ans.second);
        _root = merge(ans.first, right);
    }

    void remove(size_t position){
        std::pair<Node*, Node*> ans1 = split(_root, position);
        std::pair<Node*, Node*> ans2 = split(ans1.second, 1);
        delete ans2.first;
        _root = merge(ans1.first, ans2.second);
    }

    std::string get(size_t position) const{
        size_t l;
        Node* node = _root;
        do {
            l = (node->left != nullptr)?(node->left->treeSize):0;
            if (l == position)
                break;
            if (position < l) {
                node = node->left;
            }
            else {
                position -= l + 1;
                node = node->right;
            }
        } while (true);
        return node->value;
    }

private:
    struct Node {
        Node(const std::string& value): value(value), priority(rand())
          , left(nullptr), right(nullptr)
          , treeSize(1) {}

        void fix(){
            treeSize = 1;
            if (left != nullptr)
                treeSize += left->treeSize;
            if (right != nullptr)
                treeSize += right->treeSize;
        }

        size_t treeSize;
        int priority;
        std::string value;

        Node* left;
        Node* right;
    };

private:
    std::pair<Node*, Node*> split(Node* node, size_t position){
        if (node == nullptr)
            return std::pair<Node*, Node*>(nullptr, nullptr);

        size_t l = (node->left != nullptr)? (node->left->treeSize) : 0;
        if (l >= position) {
            std::pair<Node*, Node*> ans = split(node->left, position);
            node->left = ans.second;
            node->fix();
            return std::make_pair(ans.first, node);
        }
        else {
            std::pair<Node*, Node*> ans = split(node->right, position - l - 1);
            node->right = ans.first;
            node->fix();
            return std::make_pair(node, ans.second);
        }
    }

    Node* merge(Node* node1, Node* node2) {
        if (node2 == nullptr)
            return node1;
        if (node1 == nullptr)
            return node2;
        if (node1->priority > node2->priority) {
            node1->right = merge(node1->right, node2);
            node1->fix();
            return node1;
        }
        else {
            node2->left = merge(node1, node2->left);
            node2->fix();
            return node2;
        }
    }
    Node* _root;
};

int main() {
    size_t n = 0;
    std::cin >> n;
    ImplicitTreap stringArray;
    std::vector<std::string> ans;

    for (size_t i = 0; i < n; i++) {
        char cmd;
        std::cin >> cmd;

        if (cmd == '+') {
            size_t position = 0;
            std::string val = "";
            std::cin >> position >> val;
            stringArray.insert(position, val);
        }
        else if (cmd == '-'){
            size_t from;
            size_t to;
            std::cin >> from >> to;
            for (int i = from; i <= to; ++i) {
                stringArray.remove(from);
            }
        }
        else {
            size_t position = 0;
            std::cin >> position;
            ans.push_back(stringArray.get(position));
        }
    }

    for (const auto& x : ans) {
        std::cout << x << std::endl;
    }

    return 0;
}
