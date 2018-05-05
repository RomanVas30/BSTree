#include "bstree.hpp"
#include <iostream>
using namespace BSTree;

auto change_color(int c) -> void {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    switch (c) {
    case BLUE:  // blue color
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "\033[34m";
#endif
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
#endif
        break;
    case GREEN:  // green
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "\033[32m";
#endif
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
#endif
        break;
    case WHITE:  // white
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "\033[39;49m";
#endif
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
#endif
        break;
    case RED:  // red
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "\033[31m";
#endif
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
#endif
        break;
    case CYAN:
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "\033[36m";
#endif
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
#endif
    }
}

auto Tree::empty() -> bool {
    if(root == nullptr)
        return true;
    return false;
}

Tree::Tree() : root {nullptr} {

};

auto swap(Tree& tree, Node* curr) -> void {
    tree.insert(curr->data);
    std::cout << curr->data << std::endl;
    if (curr->left != nullptr)
        swap(tree, curr->left);
    if (curr->right != nullptr)
        swap(tree, curr->right);
}

Tree::Tree(Tree& tree) {
    root = nullptr;
    swap(*this, tree.root);
}

auto add(Node*& curr, int value) -> void {
    if (curr == nullptr)
        curr = new Node{value, nullptr, nullptr};
    else {
        if (curr->data < value) add(curr->right, value);
        if (curr->data > value) add(curr->left, value);
    }
}

auto Tree::insert(int value) -> void {
    add(root, value);
    return;
}

Tree::Tree(std::initializer_list<int> list) {
    root = nullptr;
    for (auto x:list) {
        insert(x);
    }
};

//DETOUR{

auto pre_detour(Node* curr) -> void {
    if (curr != nullptr) {
        std::cout << curr->data << " ";
        pre_detour(curr->left);
        pre_detour(curr->right);
    }
    else return;
}

auto in_detour(Node* curr) -> void {
    if (curr != nullptr) {
        in_detour(curr->left);
        std::cout << curr->data << " ";
        in_detour(curr->right);
    }
    else return;
}

auto post_detour(Node* curr) -> void {
    if (curr != nullptr) {
        post_detour(curr->left);
        post_detour(curr->right);
        std::cout << curr->data << " ";
    }
    else return;
}

//}

auto Tree::print(traversal_order order) -> void {
    Node* curr = root;
    switch (order) {
    case traversal_order::pre: {
        pre_detour(curr);
    }
    break;

    case traversal_order::in: {
        in_detour(curr);
    }
    break;

    case traversal_order::post: {
        post_detour(curr);
    }
    break;
    }
}

auto print_(Node* curr, int level, int root_data) -> void {
    if (curr != nullptr) {
        if (curr->right != nullptr) {
            print_(curr->right, level + 1, root_data);
        }
        for (unsigned i = 0; i < level; ++i) std::cout << "   ";
        if (curr->data != root_data) {
            std::cout << "--";
        }
        std::cout << curr->data << std::endl;
        if (curr->left != nullptr) {
            print_(curr->left, level + 1, root_data);
        }
    }
}

auto Tree::print_tree() -> void {
    print_(root, 0, root->data);
}

auto Tree::add_element(int value) -> bool {
    if (root == nullptr) {
        add(root, value);
        return true;
    }
    Node* curr = root;
    Node* parent = curr;
    while(curr != nullptr) {
        parent = curr;
        if (curr->data != value) {
            if (curr->data > value)
                curr = curr->left;
            else curr = curr->right;
        }
        else return false;
    }
    add(parent, value);
    return true;
}

auto Tree::remove(int value) -> bool {
    //Проверка наличия потомков у корня
    if ((root->right == nullptr)&&(root->left == nullptr)) {
        delete root;
        root = nullptr;
        return true;
    }
    Node* curr = root;
    Node* parent = root;
    Node* parent_delete = root;
    //Проверка наличия элемента в дереве
    while(1) {
        if(value == root->data) break; //Проверка корня
        if ((value >= curr->data)&&(curr->right != nullptr)) {
            parent = curr;
            curr = curr->right;
            if (curr->data == value) break;
        }
        else {
            if(curr->left != nullptr) {
                parent = curr;
                curr = curr->left;
                if (curr->data == value) break;
            }
            else return false;
        }
    }

    //Элемент не имеет потомков
    if((curr->left == nullptr)&&(curr->right == nullptr)) {
        if(curr->data > parent->data)
            parent->right = curr->right;
        else
            parent->left = curr->left;
        delete curr;
        curr = parent;
        return true;
    }
    //Элемент находится в середине дерева
    parent_delete = curr;
    parent = curr;
    if(curr->right != nullptr) {
        curr = curr->right;
        while(1) {
            if (curr->left != nullptr) {
                parent_delete = curr;
                curr = curr->left;
            }
            else {
                if(parent->data == parent_delete->data)
                    parent_delete->right = curr->right;
                if(parent->data != parent_delete->data)
                    parent_delete->left = curr->right;
                parent->data = curr->data;
                delete curr;
                curr = nullptr;
                return true;
            }
        }
    }
    else {
        curr = curr->left;
        while(1) {
            if(curr->right != nullptr) {
                parent_delete = curr;
                curr = curr->right;
            }
            else {
                if(parent->data == parent_delete->data)
                    parent_delete->left = curr->left;
                if(parent->data != parent_delete->data)
                    parent_delete->right = curr->left;
                parent->data = curr->data;
                delete curr;
                curr = nullptr;
                return true;
            }
        }
    }
}

auto delete_Tree(Node* curr) -> void {
    if (curr->right != nullptr)
        delete_Tree(curr->right);
    if (curr->left != nullptr)
        delete_Tree(curr->left);
    delete curr;
    curr = nullptr;
}

//DETOUR_OUT{

auto pre_detour_out(Node* curr, std::ostream &stream) -> void {
    if (curr != nullptr) {
        stream << curr->data << " ";
        pre_detour_out(curr->left, stream);
        pre_detour_out(curr->right, stream);
    }
    else return;
}

//}

auto Tree::save(const std::string& path) -> bool {
    std::ifstream stream(path);
    if (stream) {
        std::cout << "Файл уже существует, перезаписать ? (Да|Нет): " << std::endl;
        std::string answer;
        std::cin >> answer;
        if (answer == "Да") {
            stream.close();
            std::ofstream stream1(path);
            pre_detour_out(root, stream1);
            stream1.close();
            return true;
        }
        else return false;
    }
    stream.close();
    std::ofstream stream2(path);
    pre_detour_out(root, stream2);
    stream2.close();
    return true;
}

auto Tree::load(const std::string& path) -> bool {
    std::ifstream stream(path);
    if (stream) {
        delete_Tree(root);
        int val;
        stream >> val;
        while(stream) {
            this->insert(val);
            stream >> val;
        }
        return true;
    }
    else return false;
}

auto Tree::exists(int value) -> bool {
    if (value == root->data) return true;
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->data == value)
            return true;
        if (curr->data > value)
            curr = curr->left;
        else curr = curr->right;
    }
    return false;
}

namespace BSTree {

    auto operator<<(std::ostream& stream,const Tree& tree) -> std::ostream& {
        Node *curr= tree.root;
        pre_detour_out(curr, stream);
        return stream;
    }

}

auto Tree::operator=(Tree& tree) -> Tree& {
    delete_Tree(root);
    swap(*this, tree.root);
    return *this;
};

Tree::~Tree() {
    if(root != nullptr)
        delete_Tree(root);
};

