#include <catch.hpp>
#include <sstream>
#include <string>
#include <fstream>

#include "bstree.hpp"
using namespace BSTree;

TEST_CASE("empty tree")
{
	Tree tree;
	REQUIRE( tree.exists() == true );
}

TEST_CASE("initializing tree nodes")
{
  Tree tree;
  for (unsigned int i = 1; i < 5; ++i)
  tree.insert(i);
  
  REQUIRE( tree.exists() == false );

}
/*
TEST_CASE("detour_pre")
{
  Tree tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);
  tree.insert(4);
  tree.insert(5);
	
  std::ofstream out("file.txt");
  out >> pre_detour_out(tree);
  out.close();
	
  std::string result;
  std::string text = "3 2 1 4 5 ";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("detour_in")
{
  Tree tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);
  tree.insert(4);
  tree.insert(5);
	
  std::ofstream out("file.txt");
  out >> tree.print(traversal_order::in);
  out.close();
	
  std::string result;
  std::string text = "1 2 3 4 5 ";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("detour_post")
{
  Tree tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);
  tree.insert(4);
  tree.insert(5);
	
  std::ofstream out("file.txt");
  out >> tree.print(traversal_order::post);
  out.close();
	
  std::string result;
  std::string text = "1 2 5 4 3 ";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}
    
*/
