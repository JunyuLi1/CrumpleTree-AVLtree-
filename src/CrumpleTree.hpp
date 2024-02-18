#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace shindler::ics46::project4 {

class ElementNotFoundException : public std::runtime_error {
   public:
    explicit ElementNotFoundException(const std::string &err)
        : std::runtime_error(err) {}
};

template <typename K, typename V>
class CrumpleTree {
   private:
    // fill in private member data here
    // If you need to declare private functions, do so here too.
    struct Node{
        K key;
        V Value;
        Node * leftChildren;
        Node * rightChildren;
        unsigned node_level;
        unsigned leftedge;
        unsigned rightedge;
        Node(K key_val, V value_val):key(key_val),Value(value_val),leftChildren(nullptr),rightChildren(nullptr),node_level(1),leftedge(1),rightedge(1){}
    };
    size_t num_keys;
    Node * root;
    Node * inserthelper(Node*node,const K &key,const V &value)//
    {
        if(node==nullptr)
        {
            node = new Node(key,value);
            return node;
        }
        if(key<node->key)
        {
            node->leftChildren=inserthelper(node->leftChildren,key,value);
        }
        else {
            node->rightChildren=inserthelper(node->rightChildren,key,value);
        }
        if(node->leftChildren!=nullptr&&node->leftChildren->node_level==node->node_level)
        {
            node->rightedge++;
        }
        if(node->rightChildren!=nullptr&&node->rightChildren->node_level==node->node_level)
        {
            node->leftedge++;
        }
        //rebalanced
        if(node->rightedge>2) //left rising;
        {
            if(node->leftChildren->rightChildren==nullptr)
            {
               node = leftrising(node);
            }
            else {
                node->leftChildren = leftmovedown(node->leftChildren);
                node = rightmovedown(node);
            }
        }
        node->node_level++;
        return node;
    }
    Node * leftmovedown(Node*root)
    {
        Node * newroot = root->rightChildren;
        Node * temp_left = newroot->leftChildren;
        //
        if(newroot->node_level==1)
        {
            newroot->node_level++;
            newroot->leftedge++;
        }
        newroot->leftChildren=root;
        root->rightChildren = temp_left;
        root->node_level--;
        root->leftedge-=2;
        return newroot;
    }
    Node * leftrising(Node * root)
    {
        Node * newroot = root->leftChildren;
        Node * temp_right = newroot->rightChildren;
        newroot->rightChildren = root;
        newroot->node_level--;
        root->leftChildren = temp_right;
        root->node_level--;
        root->rightedge-=2;
        newroot->rightedge--;
        return newroot;
    }
   public:
    CrumpleTree();

    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.
    //	CrumpleTree(const CrumpleTree & st);
    //	CrumpleTree & operator=(const CrumpleTree & st);
    // You do not need to implement these
    CrumpleTree(const CrumpleTree &) = delete;
    CrumpleTree(CrumpleTree &&) = delete;
    CrumpleTree &operator=(const CrumpleTree &) = delete;
    CrumpleTree &operator=(CrumpleTree &&) = delete;

    // The destructor is required.
    ~CrumpleTree();

    // size() returns the number of distinct keys in the tree.
    [[nodiscard]] size_t size() const noexcept;

    // isEmpty() returns true if and only if the tree has no values in it.
    [[nodiscard]] bool empty() const noexcept;

    // contains() returns true if and only if there
    //  is a (key, value) pair in the tree
    //	that has the given key as its key.
    bool contains(const K &key) const noexcept;

    // returns the level on which the node with this key resides.
    // If !contains(k), this will throw an ElementNotFoundException
    unsigned level(const K &key) const;

    // find returns the value associated with the given key
    // If !contains(k), this will throw an ElementNotFoundException
    // There needs to be a version for const and non-const CrumpleTrees.
    V &find(const K &key);
    const V &find(const K &key) const;

    // Inserts the given key-value pair into
    // the tree and performs the balancing operation(s)
    // if needed as described in lecture.
    // If the key already exists in the tree,
    // you may do as you please (no test cases in
    // the grading script will deal with this situation)
    void insert(const K &key, const V &value);

    // Deletes the given key from the tree
    // and performs the balancing operation(s) if needed.
    // If the key does not exist in the tree,
    // do not modify the tree.
    void remove(const K &key);

    // The following three functions all return
    // the set of keys in the tree as a standard vector.
    // Each returns them in a different order.
    [[nodiscard]] std::vector<K> inOrder() const;
    [[nodiscard]] std::vector<K> preOrder() const;
    [[nodiscard]] std::vector<K> postOrder() const;

    unsigned getrightedge(const K&key);
    unsigned getleftedge(const K&key);
    K&getroot();
};

template <typename K, typename V>
CrumpleTree<K, V>::CrumpleTree() {
    num_keys=0;
    root=nullptr;
}

template <typename K, typename V>
CrumpleTree<K, V>::~CrumpleTree() {
    // TODO: Implement this
}

template <typename K, typename V>
size_t CrumpleTree<K, V>::size() const noexcept {
    return num_keys;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::empty() const noexcept {
    return num_keys == 0;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::contains(const K &key) const noexcept {
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return true;
        }
        if(key<tempNode->key)
        {
            tempNode=tempNode->leftChildren;
        }
        else {
            tempNode=tempNode->rightChildren;
        }
    }
    return false;
}

template <typename K, typename V>
unsigned CrumpleTree<K, V>::level(const K &key) const {
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return tempNode->node_level;
        }
        if(key<tempNode->key)
        {
            tempNode=tempNode->leftChildren;
        }
        else {
            tempNode=tempNode->rightChildren;
        }
    }
    throw ElementNotFoundException("No such key");
}

template <typename K, typename V>
V &CrumpleTree<K, V>::find(const K &key) {
    // TODO: Implement this
    V tmp;
    return tmp;
}

template <typename K, typename V>
const V &CrumpleTree<K, V>::find(const K &key) const {
    // TODO: Implement this
    V tmp;
    return tmp;
}

template <typename K, typename V>
void CrumpleTree<K, V>::insert(const K &key, const V &value) {
    if(root==nullptr)
    {
        root=new Node(key,value);
    }
    else{
        Node * currentNode = root;
        root = inserthelper(currentNode, key, value);
    }
    num_keys++;
}

template <typename K, typename V>
void CrumpleTree<K, V>::remove(const K &key) {
    // TODO: Implement this
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::inOrder() const {
    // TODO: Implement this
    return {};
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::preOrder() const {
    // TODO: Implement this
    return {};
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::postOrder() const {
    // TODO: Implement this
    return {};
}
template <typename K, typename V>
unsigned CrumpleTree<K, V>::getrightedge(const K&key)
{
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return tempNode->rightedge;
        }
        if(key<tempNode->key)
        {
            tempNode=tempNode->leftChildren;
        }
        else {
            tempNode=tempNode->rightChildren;
        }
    }
}

template <typename K, typename V>
unsigned CrumpleTree<K, V>::getleftedge(const K&key)
{
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return tempNode->leftedge;
        }
        if(key<tempNode->key)
        {
            tempNode=tempNode->leftChildren;
        }
        else {
            tempNode=tempNode->rightChildren;
        }
    }
}

template <typename K, typename V>
K &CrumpleTree<K, V>::getroot() {
    return root->key;
}

}  // namespace shindler::ics46::project4

#endif
