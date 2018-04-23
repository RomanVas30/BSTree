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
        auto insert(int value) -> void;
        auto exists() -> bool;
        auto print_tree() -> void;
        auto remove(int value) -> bool;
        auto add_element(int value) -> bool;
        auto print(traversal_order order) -> void;
        ~Tree();
    };
}
