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

TEST_CASE("Tree:DoAPostOrder:ExpectCorrectPostorderTraversal",
          "[Required][Basic][Insert][PostOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    static const std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:inorder",
          "[Required][Basic][Insert][PostOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(40, "foo");
    tree.insert(20, "sna");
    tree.insert(60, "bar");
    tree.insert(3, "bar");
    tree.insert(25, "bar");
    tree.insert(15, "bar");
    tree.insert(1, "bar");
    tree.insert(44, "bar");
    auto trav = tree.inOrder();
    static const std::vector<int> expected = {1,3,15,20,25,40,44,60};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrect",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(12));
    REQUIRE(tree.contains(9));
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and
    // remains at level 3.
    REQUIRE(!tree.contains(9));
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(12) == 1);
    REQUIRE(tree.level(19) == 3);
}
// NOLINTEND

TEST_CASE("find test",
          "[Required][Basic][Insert][Contains]") {
    
    proj4::CrumpleTree<int, int> tree;
    const proj4::CrumpleTree<int, int> & treeRef= tree;
    tree.insert(1, 2);
    REQUIRE(treeRef.find(1)==2);
}

TEST_CASE("simpleswap",
          "[Required][Basic][Insert][Contains]") {
    
    proj4::CrumpleTree<int, int> tree;
    tree.insert(20, 20);
    tree.insert(50, 50);
    tree.insert(10, 10);
    tree.insert(1, 1);
    tree.insert(5, 5);
    tree.insert(9, 9);
    tree.insert(25, 25);
    tree.insert(23, 23);
    REQUIRE(tree.size()==8);
    tree.remove(10);
    REQUIRE(tree.size()==7);
    REQUIRE(tree.level(20)==4);
    REQUIRE(tree.level(25)==3);
    REQUIRE(tree.level(5)==2);
    REQUIRE(tree.level(1)==1);
    REQUIRE(tree.level(9)==1);
    REQUIRE(tree.level(23)==1);
    REQUIRE(tree.level(50)==1);
    REQUIRE(tree.find(20)==20);
    REQUIRE(tree.find(23)==23);
    REQUIRE_FALSE(tree.contains(10));
}

TEST_CASE("simple4left",
          "[Required][Basic][Insert][Contains]") {
    
    proj4::CrumpleTree<int, int> tree;
    tree.insert(20, 20);
    tree.insert(2, 2);
    tree.insert(50, 50);
    tree.insert(1, 1);
    tree.insert(10, 10);
    tree.insert(45, 45);
    tree.insert(55, 55);
    tree.insert(60, 60);
    REQUIRE(tree.size()==8);
    tree.remove(1);
    tree.remove(10);
    REQUIRE(tree.size()==6);
    REQUIRE(tree.level(50)==4);
    REQUIRE(tree.level(20)==3);
    REQUIRE(tree.level(55)==2);
    REQUIRE(tree.level(2)==1);
    REQUIRE(tree.level(45)==1);
    REQUIRE(tree.level(60)==1);
    REQUIRE_FALSE(tree.contains(1));
    REQUIRE_FALSE(tree.contains(10));
}

TEST_CASE("simple5right",
          "[Required][Basic][Insert][Contains]") {
    
    proj4::CrumpleTree<int, int> tree;
    tree.insert(20, 20);
    tree.insert(2, 2);
    tree.insert(50, 50);
    tree.insert(1, 1);
    tree.insert(10, 10);
    tree.insert(45, 45);
    tree.insert(55, 55);
    tree.insert(60, 60);
    REQUIRE(tree.size()==8);
    tree.remove(60);
    tree.remove(55);
    tree.insert(5, 5);
    tree.remove(45);
    REQUIRE(tree.size()==6);
    REQUIRE(tree.level(10)==4);
    REQUIRE(tree.level(2)==2);
    REQUIRE(tree.level(20)==2);
    REQUIRE(tree.level(1)==1);
    REQUIRE(tree.level(5)==1);
    REQUIRE(tree.level(50)==1);
    REQUIRE_FALSE(tree.contains(60));
    REQUIRE_FALSE(tree.contains(55));
    REQUIRE_FALSE(tree.contains(45));
}

TEST_CASE("remove_condition_2",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "in");
    tree.insert(17, "in");
    tree.insert(21, "in");
    tree.insert(7, "in");
    tree.insert(15, "in");
    tree.insert(31, "in");
    tree.remove(19);
    tree.remove(7);
    tree.remove(15);
    REQUIRE(tree.size() == 5);
}

TEST_CASE("removeonlyroot",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.remove(20);
    REQUIRE(tree.size() == 0);
}

TEST_CASE("remove_condition_3_l",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(40, "40");
    tree.insert(19, "19");
    tree.insert(20, "20");
    tree.insert(51, "51");
    tree.insert(2, "2");
    tree.insert(9, "9");
    tree.insert(1, "1");
    tree.insert(18, "18");
    tree.insert(17, "17");
    REQUIRE(tree.contains(9));
    tree.remove(1);
    tree.remove(2);
    REQUIRE(tree.level(20)==4);
    REQUIRE(tree.level(18)==3);
    REQUIRE(tree.level(9)==2);
    REQUIRE(tree.level(40)==2);
    REQUIRE(tree.level(17)==1);
    REQUIRE(tree.level(19)==1);
    REQUIRE(tree.level(51)==1);
    REQUIRE(tree.size() == 7);
}

TEST_CASE("remove_condition_3_r",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(40, "40");
    tree.insert(19, "19");
    tree.insert(20, "20");
    tree.insert(51, "51");
    tree.insert(2, "2");
    tree.insert(9, "9");
    tree.insert(1, "1");
    tree.insert(38, "38");
    tree.insert(39, "39");
    tree.insert(53, "53");
    tree.insert(52, "52");
    tree.remove(39);
    tree.remove(38);
    REQUIRE(tree.level(20)==4);
    REQUIRE(tree.level(52)==3);
    REQUIRE(tree.level(9)==3);
    REQUIRE(tree.level(40)==2);
    REQUIRE(tree.level(2)==2);
    REQUIRE(tree.level(1)==1);
    REQUIRE(tree.level(19)==1);
    REQUIRE(tree.level(51)==1);
    REQUIRE(tree.level(53)==1);
    REQUIRE(tree.size() == 9);
}

TEST_CASE("remove_condition_4A_r",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "20");
    tree.insert(2, "2");
    tree.insert(50, "50");
    tree.insert(45, "45");
    tree.insert(60, "60");
    tree.insert(1, "1");
    tree.insert(10, "10");
    tree.insert(5, "5");
    tree.insert(0, "0");
    tree.remove(5);
    tree.remove(45);
    tree.remove(60); 
    REQUIRE(tree.level(2)==4);
    REQUIRE(tree.level(20)==3);
    REQUIRE(tree.level(1)==2);
    REQUIRE(tree.level(0)==1);
    REQUIRE(tree.level(10)==1);
    REQUIRE(tree.level(50)==1);
    REQUIRE(tree.size() == 6);
}

TEST_CASE("remove_condition_4B_l",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "20");
    tree.insert(2, "2");
    tree.insert(50, "50");
    tree.insert(1, "1");
    tree.insert(10, "10");
    tree.insert(45, "45");
    tree.insert(55, "55");
    tree.insert(60, "60");
    tree.remove(45);
    tree.remove(1);
    tree.remove(10);
    tree.remove(50);
    tree.remove(2);
    REQUIRE(tree.level(55)==2);
    REQUIRE(tree.level(20)==1);
    REQUIRE(tree.level(60)==1);
    REQUIRE(tree.size() == 3);
}

TEST_CASE("simple6left",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "20");
    tree.insert(50, "50");
    tree.insert(10, "10");
    tree.insert(1, "1");
    tree.insert(5, "5");
    tree.insert(9, "45");
    tree.insert(25, "25");
    tree.insert(23, "23");
    tree.remove(23);
    tree.remove(1);
    tree.remove(9);
    tree.remove(5);
    REQUIRE(tree.level(25)==3);
    REQUIRE(tree.level(10)==2);
    REQUIRE(tree.level(20)==1);
    REQUIRE(tree.level(50)==1);
    REQUIRE(tree.size() == 4);
}

TEST_CASE("condition6left",
          "[Required][Basic][Insert][Contains]") {
    
    proj4::CrumpleTree<int, int> tree;
    tree.insert(19, 19);
    tree.insert(18, 18);
    tree.insert(40, 40);
    tree.insert(30, 30);
    tree.insert(41, 41);
    tree.insert(29, 29);
    tree.insert(31, 31);
    tree.remove(18);
    tree.remove(29);
    tree.insert(32, 32);
    tree.insert(42, 42);
    tree.remove(42);
    tree.remove(19);
    REQUIRE(tree.size()==5);
    REQUIRE(tree.level(31)==3);
    REQUIRE(tree.level(40)==2);
    REQUIRE(tree.level(30)==1);
    REQUIRE(tree.level(32)==1);
    REQUIRE(tree.level(41)==1);
}

}  // namespace
