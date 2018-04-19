#include <catch.hpp>
#include <sstream>

#include "bstree.hpp"
using namespace BSTree;

TEST_CASE("empty tree")
{
	Tree tree;
	REQUIRE( tree.empty() == true );
}

TEST_CASE("initializing tree nodes")
{
	Tree tree;
  for (unsigned int i = 1; i < 5; ++i)
  tree.insert(i);
  
  REQUIRE( tree.empty() == false );

}
