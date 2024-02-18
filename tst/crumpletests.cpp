#include <CrumpleTree.hpp>
#include <catch2/catch_amalgamated.hpp>

namespace {
namespace proj4 = shindler::ics46::project4;

/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY.

*/

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
// readability-magic-numbers)
TEST_CASE("Tree:SimpleInsertAndFind:ExpectSingleInsertFound",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE(tree.contains(5));
}

TEST_CASE("Tree:DoubleInsert:ExpectFindSecondInsert",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE(tree.contains(10));
}

TEST_CASE("Tree:QuadInsert:ExpectFindFindTwoHopsAway",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE(tree.contains(12));
}

TEST_CASE("Tree:5Inserts:ExpectSize5", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE(tree.size() == 5);
}

// TEST_CASE("Tree:DoAPostOrder:ExpectCorrectPostorderTraversal",
//           "[Required][Basic][Insert][PostOrder]") {
//     proj4::CrumpleTree<int, std::string> tree;
//     tree.insert(5, "foo");
//     tree.insert(3, "sna");
//     tree.insert(10, "bar");
//     auto trav = tree.postOrder();
//     static const std::vector<int> expected = {3, 10, 5};
//     REQUIRE(trav == expected);
// }

// TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrect",
//           "[Required][Insert][Erase][Contains][Level]") {
//     proj4::CrumpleTree<int, std::string> tree;
//     tree.insert(20, "are");
//     tree.insert(19, "you");
//     tree.insert(18, "following");
//     tree.insert(12, "from");
//     tree.insert(9, "lecture?");
//     REQUIRE(tree.contains(20));
//     REQUIRE(tree.contains(19));
//     REQUIRE(tree.contains(18));
//     REQUIRE(tree.contains(12));
//     REQUIRE(tree.contains(9));
//     tree.remove(9);
//     tree.remove(18);
//     // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and
//     // remains at level 3.
//     REQUIRE(!tree.contains(9));
//     REQUIRE(!tree.contains(18));
//     REQUIRE(tree.level(20) == 1);
//     REQUIRE(tree.level(12) == 1);
//     REQUIRE(tree.level(19) == 3);
// }
// NOLINTEND

TEST_CASE("simpleLL",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(40, "40");
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==1);
    tree.insert(30, "30");
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==2);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    tree.insert(20, "20");
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==1);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    REQUIRE(tree.getleftedge(20)==1);
    REQUIRE(tree.getrightedge(20)==1);
    REQUIRE(tree.contains(40));
    REQUIRE(tree.contains(30));
    REQUIRE(tree.contains(20));
    REQUIRE(tree.getroot() == 30);
    REQUIRE(tree.level(30) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(40) == 1);
    REQUIRE(tree.size()==3);
}

TEST_CASE("simpleLR",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(50, "50");
    REQUIRE(tree.getleftedge(50)==1);
    REQUIRE(tree.getrightedge(50)==1);
    tree.insert(40, "40");
    REQUIRE(tree.getleftedge(50)==1);
    REQUIRE(tree.getrightedge(50)==2);
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==1);
    tree.insert(45, "45");
    REQUIRE(tree.getroot()==45);
    REQUIRE(tree.getleftedge(45)==1);
    REQUIRE(tree.getrightedge(45)==1);
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==1);
    REQUIRE(tree.getleftedge(50)==1);
    REQUIRE(tree.getrightedge(50)==1);
    REQUIRE(tree.contains(50));
    REQUIRE(tree.contains(40));
    REQUIRE(tree.contains(45));
    REQUIRE(tree.level(45) == 2);
    REQUIRE(tree.level(50) == 1);
    REQUIRE(tree.level(40) == 1);
    REQUIRE(tree.size()==3);
}

TEST_CASE("simpleRR",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "40");
    REQUIRE(tree.getleftedge(20)==1);
    REQUIRE(tree.getrightedge(20)==1);
    tree.insert(30, "30");
    REQUIRE(tree.getrightedge(20)==1);
    REQUIRE(tree.getleftedge(20)==2);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    tree.insert(40, "20");
    REQUIRE(tree.getleftedge(40)==1);
    REQUIRE(tree.getrightedge(40)==1);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    REQUIRE(tree.getleftedge(20)==1);
    REQUIRE(tree.getrightedge(20)==1);
    REQUIRE(tree.contains(40));
    REQUIRE(tree.contains(30));
    REQUIRE(tree.contains(20));
    REQUIRE(tree.getroot() == 30);
    REQUIRE(tree.level(30) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(40) == 1);
    REQUIRE(tree.size()==3);
}

TEST_CASE("simpleRL",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "50");
    REQUIRE(tree.getleftedge(20)==1);
    REQUIRE(tree.getrightedge(20)==1);
    tree.insert(30, "40");
    REQUIRE(tree.getrightedge(20)==1);
    REQUIRE(tree.getleftedge(20)==2);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    tree.insert(25, "45");
    REQUIRE(tree.getroot()==25);
    REQUIRE(tree.getleftedge(25)==1);
    REQUIRE(tree.getrightedge(25)==1);
    REQUIRE(tree.getleftedge(20)==1);
    REQUIRE(tree.getrightedge(20)==1);
    REQUIRE(tree.getleftedge(30)==1);
    REQUIRE(tree.getrightedge(30)==1);
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(30));
    REQUIRE(tree.contains(25));
    REQUIRE(tree.level(25) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(30) == 1);
    REQUIRE(tree.size()==3);
}



}  // namespace
