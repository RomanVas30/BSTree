#include <fstream>
#include <initializer_list>
#include <cstddef>

enum col { BLUE, GREEN, WHITE, RED, CYAN };
namespace BSTree {
    enum class traversal_order {pre, in, post};
    struct Node {
        int data;
        Node* left;
        Node* right;
    };

    class Tree {
        Node* root;
        public:
        Tree();
        Tree(std::initializer_list<int> list);
        Tree(Tree& tree);
        auto empty() -> bool;
        auto insert(int value) -> void;
        auto print_tree() -> void;
        auto exists(int value) -> bool;
        auto remove(int value) -> bool;
        auto add_element(int value) -> bool;
        auto print(traversal_order order) -> void;
        auto save(const std::string& path) -> bool;
        auto load(const std::string& path) -> bool;
        auto friend operator<<(std::ostream&,const Tree&) -> std::ostream&;
        auto operator=(Tree&) -> Tree&;
        ~Tree();
    };
}
