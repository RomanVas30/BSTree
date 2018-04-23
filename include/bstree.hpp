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
        auto add(Node*&, int) -> void;
        auto print_(Node*, int) -> void;
        auto print() -> void;
        auto empty() -> bool;
        auto add_element(int value) -> bool;
        auto remove_element(int value) -> bool;
        auto delete_Tree(Node* curr) -> void;
        auto list (traversal_order order) -> void;
        ~Tree();
    };
}
