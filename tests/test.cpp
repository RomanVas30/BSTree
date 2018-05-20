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
TEST_CASE("initializer_list")
{
  Tree tree = {3, 2, 4, 1, 5};
	
  std::ofstream out("file.txt");
  tree.save("file.txt");
  out.close();
  
  std::string result;
  std::string text = "3 2 1 4 5";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("add_element_false")
{
  Tree tree = {3, 2, 4, 1, 5};
  tree.insert(4);
  
  std::ofstream out("file.txt");
  tree.save("file.txt");
  out.close();
  
  std::string result;
  std::string text = "3 2 1 4 5";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("add_element_true")
{
  Tree tree = {3, 2, 4, 1, 5};
  tree.insert(6);
  
  std::ofstream out("file.txt");
  tree.save("file.txt");
  out.close();
  
  std::string result;
  std::string text = "3 2 1 4 5 6";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("delete_element_false")
{
  Tree tree = {3, 2, 4, 1, 5};
  tree.remove(6);
  
  std::ofstream out("file.txt");
  tree.save("file.txt");
  out.close();
  
  std::string result;
  std::string text = "3 2 1 4 5";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}

TEST_CASE("add_element_false")
{
  Tree tree = {3, 2, 4, 1, 5};
  tree.remove(4);
  
  std::ofstream out("file.txt");
  tree.save("file.txt");
  out.close();
  
  std::string result;
  std::string text = "3 2 1 5";
  std::ifstream in("file.txt");
  getline(in, result);
  
  REQUIRE(result == text);
}
