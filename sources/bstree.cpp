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

Tree::Tree() : root{nullptr} {};

auto Tree::empty() -> bool{
  if(root == nullptr)
  return true;
  else return false;
}

auto Tree::insert(int value) -> bool {
  add(root, value); 
  return true;
}

auto Tree::add(Node*& curr, int value) -> void {
  if (curr == nullptr)
    curr = new Node{value};
  else {
    if (curr->data < value) add(curr->right, value);
    if (curr->data > value) add(curr->left, value);
  }
}

auto Tree::print() -> void { print_(root, 0); }

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

auto Tree::delete_Tree(Node* curr) -> void{
      if (curr->right != nullptr)
        delete_Tree(curr->right);
      if (curr->left != nullptr)
        delete_Tree(curr->left);
      delete curr;
      curr = nullptr;
}

Tree::~Tree(){
  if(root != nullptr)
  delete_Tree(root);
};
