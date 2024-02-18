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
            node->rightedge--;
            Node * newroot = node->leftChildren;
            if (node->leftChildren->rightedge==2) { //case3 left rising
                Node * temp_right = newroot->rightChildren;
                newroot->rightChildren = node;
                newroot->node_level--;
                node->leftChildren = temp_right;
                node->node_level--;
                node->rightedge--;
                newroot->rightedge--;
                node = newroot;
            }
            else
            {
                if(node->leftChildren->leftedge==1) //case 4 left rising
                {
                    Node * temp_right = newroot->rightChildren;
                    newroot->rightChildren = node;
                    newroot->leftedge++;
                    node->leftChildren = temp_right;
                    node = newroot;
                }
                else { //case 5 left rising
                    newroot=newroot->rightChildren;
                    Node * nodeleftchilde = node->leftChildren;
                    nodeleftchilde->node_level--;
                    nodeleftchilde->rightChildren=newroot->leftChildren;
                    nodeleftchilde->leftedge--;
                    nodeleftchilde->rightedge=newroot->leftedge;
                    node->node_level--;
                    node->leftChildren=newroot->rightChildren;
                    node->rightedge--;
                    node->leftedge=newroot->rightedge;
                    newroot->leftChildren=nodeleftchilde;
                    newroot->rightChildren=node;
                    newroot->leftedge=1;
                    newroot->rightedge=1;
                    node=newroot;
                }
            }
        }
        if(node->leftedge>2) {
            node->leftedge--;
            Node * newroot = node->rightChildren;
            if(node->rightChildren->leftedge==2){ //case 3 right rising
                Node * temp_left = newroot->leftChildren;
                newroot->leftChildren = node;
                newroot->node_level--;
                node->rightChildren = temp_left;
                node->node_level--;
                node->leftedge--;
                newroot->leftedge--;
                node = newroot;
            }
            else {
                if(node->rightChildren->rightedge==1){ //case 4 right rising
                    Node * temp_left = newroot->leftChildren;
                    newroot->leftChildren = node;
                    newroot->rightedge++;
                    node->rightChildren = temp_left;
                    node = newroot;
                }
                else { //case 5 right rising.
                    newroot=newroot->leftChildren;
                    Node * noderightchild = node->rightChildren;
                    noderightchild->node_level--;
                    noderightchild->leftChildren=newroot->rightChildren;
                    noderightchild->rightedge--;
                    noderightchild->leftedge=newroot->rightedge;
                    node->node_level--;
                    node->rightChildren=newroot->leftChildren;
                    node->leftedge--;
                    node->rightedge=newroot->leftedge;
                    newroot->leftChildren=node;
                    newroot->rightChildren=noderightchild;
                    newroot->leftedge=1;
                    newroot->rightedge=1;
                    node=newroot;
                }
            }
        }
        node->node_level++;
        return node;
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
