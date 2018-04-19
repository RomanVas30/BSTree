enum col { BLUE, GREEN, WHITE, RED, CYAN };
namespace BSTree {
struct Node {
  int data;
  Node* left;
  Node* right;
};

class Tree {
  Node* root;

 public:
  Tree();
  auto insert(int value) -> bool;
  auto add(Node*&, int) -> void;
  auto print_(Node*, int) -> void;
  auto print() -> void;
  auto empty() -> bool;
  auto delete_Tree(Node* curr) -> void;
  ~Tree();
};
}

