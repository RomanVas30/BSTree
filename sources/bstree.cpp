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
    else return false;
}

Tree::Tree() : root {nullptr} {

};

auto Tree::insert(int value) -> void {
    add(root, value);
    return;
}

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

auto Tree::list(traversal_order order) -> void {
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

auto Tree::add(Node*& curr, int value) -> void {
    if (curr == nullptr)
        curr = new Node{value};
    else {
        if (curr->data < value) add(curr->right, value);
        if (curr->data > value) add(curr->left, value);
    }
}

auto Tree::print() -> void {
    print_(root, 0);
}

auto Tree::print_(Node* curr, int level) -> void {
    if (curr != nullptr) {
        if (curr->right != nullptr) {
            print_(curr->right, level + 1);
        }
        for (unsigned i = 0; i < level; ++i) std::cout << "  ";
        if (curr->data != root->data) {
            std::cout << "--";
        }
        std::cout << curr->data << std::endl;
        if (curr->left != nullptr) {
            print_(curr->left, level + 1);
        }
    }
}

auto Tree::add_element(int value) -> bool {
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

auto Tree::remove_element(int value) -> bool {
    if ((root->right == nullptr)&&(root->left == nullptr)) {
        delete root;
        root = nullptr;
        return true;
    }
    Node* curr = root;
    Node* parent = root;
    Node* parent_delete = root;
    while(1) {
        if(value == root->data) break;
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
    if((curr->left == nullptr)&&(curr->right == nullptr)) {
        if(curr->data > parent->data)
            parent->right = curr->right;
        else
            parent->left = curr->left;
        delete curr;
        curr = parent;
        return true;
    }
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

auto Tree::delete_Tree(Node* curr) -> void {
    if (curr->right != nullptr)
        delete_Tree(curr->right);
    if (curr->left != nullptr)
        delete_Tree(curr->left);
    delete curr;
    curr = nullptr;
}

Tree::~Tree() {
    if(root != nullptr)
        delete_Tree(root);
};

