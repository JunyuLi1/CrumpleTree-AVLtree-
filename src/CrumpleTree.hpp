#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
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
        bool exceute = false;
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
        if(node->leftChildren!=nullptr&&node->leftChildren->node_level!=node->node_level && 
           (node->node_level - node->leftedge)!=node->leftChildren->node_level){
            node->leftedge--;
            return node;
        }
        if(node->rightChildren!=nullptr&&node->rightChildren->node_level!=node->node_level && 
           (node->node_level - node->rightedge)!=node->rightChildren->node_level){
            node->rightedge--;
            return node;
        }
        if(node->leftChildren!=nullptr&&node->leftChildren->node_level==node->node_level)
        {
            node->rightedge++;
            exceute=true;
        }
        if(node->rightChildren!=nullptr&&node->rightChildren->node_level==node->node_level)
        {
            node->leftedge++;
            exceute=true;
        }
        //rebalanced
        if(node->rightedge>2) //left rising;
        {
            exceute=true;
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
            exceute=true;
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
        if(!exceute)
        {
            return node;
        }
        node->node_level++;
        return node;
    }
    Node * removehelper(Node*node, const K &key)
    {
        if(node->key == key) //如果succesor是leaf 结束，不是继续替换
        {
            if(node->rightChildren==nullptr && node->leftChildren==nullptr)
            {
                delete node;
                return nullptr;
            }
            if (node->rightChildren!=nullptr) { //inorder successor
                Node * inorderSuccessor = findsuccessor(node->rightChildren);
                std::swap(node->key,inorderSuccessor->key);
                std::swap(node->Value,inorderSuccessor->Value);
                while(inorderSuccessor->node_level!=1)
                {
                    Node * temp_node=inorderSuccessor;
                    inorderSuccessor=findsuccessor(inorderSuccessor->rightChildren);
                    std::swap(temp_node->key,inorderSuccessor->key);
                    std::swap(temp_node->Value,inorderSuccessor->Value);
                }
                node->rightChildren = removehelper(node->rightChildren, key); //start recursion
            }
            else { //inorder predecessor
                std::swap(node->key,node->leftChildren->key);
                std::swap(node->Value,node->leftChildren->Value);
                node-> leftChildren = removehelper(node->leftChildren, key);
            }
        }
        else if(key<node->key && node->leftChildren!=nullptr)
        {
            node->leftChildren=removehelper(node->leftChildren,key);
        }
        else{
            node->rightChildren=removehelper(node->rightChildren,key);
        }
        if(node->rightChildren==nullptr&&node->leftChildren==nullptr&&node->node_level!=1) //case 1B all
        {
            node->node_level=1;
            node->rightedge=1;
            node->leftedge=1;
        } // update edge
        if (node->leftChildren!=nullptr){
            node->leftedge = node->node_level - node->leftChildren->node_level;
            if (node->rightChildren == nullptr){
                node->rightedge = node->node_level - 0;
            }
        }
        if(node->rightChildren!=nullptr)
        {
            node->rightedge = node->node_level - node->rightChildren->node_level;
            if(node->leftChildren == nullptr)
            {
                node->leftedge = node->node_level - 0;
            }
        }
        if((node->leftedge==3 && node->rightedge ==2) || (node->rightedge==3 && node->leftedge==2)) //case 2 left and right
        {
            node->node_level--;
            node->leftedge--;
            node->rightedge--;
        }
        else if(node->leftedge==3 && node->rightedge==1 && node->rightChildren->leftedge ==1 && node->rightChildren->rightedge ==1)//case3 left
        {
            Node * newroot = node->rightChildren;
            node->leftedge =2;
            node->rightedge =1;
            node->node_level--;
            node->rightChildren = newroot->leftChildren;
            newroot->leftedge=1;
            newroot->rightedge=2;
            newroot->node_level++;
            newroot->leftChildren = node;
            node = newroot;
        }
        else if (node->rightedge==3 && node->leftedge ==1 && node->leftChildren->leftedge ==1 && node->leftChildren->rightedge ==1) { //case3 right
            Node * newroot = node->leftChildren;
            node->rightedge=2;
            node->leftedge=1;
            node->node_level--;
            node->leftChildren = newroot->rightChildren;
            newroot->leftedge=2;
            newroot->rightedge=1;
            newroot->node_level++;
            newroot->rightChildren = node;
            node = newroot;
        }
        else if (node->leftedge==3 && node->rightedge==1 && node->leftChildren!=nullptr && node->rightChildren->leftedge==2
                 && node->rightChildren->rightedge==1) { //4a left
            Node * newroot = node->rightChildren;
            node->leftedge=2;
            node->rightedge=2;
            node->node_level--;
            node->rightChildren = newroot->leftChildren;
            newroot->node_level++;
            newroot->leftedge =1;
            newroot->rightedge =2;
            newroot->leftChildren = node;
            node = newroot;
        }
        else if(node->rightedge==3 && node->leftedge==1 && node->rightChildren!=nullptr && node->leftChildren->rightedge==2
                && node->leftChildren->leftedge==1) //4a right
        {
            Node * newroot = node->leftChildren;
            node->rightedge=2;
            node->leftedge=2;
            node->node_level--;
            node->leftChildren = newroot->rightChildren;
            newroot->leftedge=2;
            newroot->rightedge=1;
            newroot->node_level++;
            newroot->rightChildren = node;
            node = newroot;
        }
        else if(node->leftedge==3 && node->rightedge==1 && node->leftChildren==nullptr && node->rightChildren->leftedge ==2
                && node->rightChildren->rightedge==1) //4b left
        {
            Node * newroot = node->rightChildren;
            node->node_level-=2;
            node->leftedge=1;
            node->rightedge=1;
            node->leftChildren = nullptr;
            node->rightChildren=nullptr;
            newroot->leftChildren=node;
            newroot->leftedge =1;
            newroot->rightedge=1;
            node = newroot;
        }
        else if(node->rightedge==3 && node->leftedge==1 && node->rightChildren==nullptr && node->leftChildren->leftedge ==1
                && node->leftChildren->rightedge==2) //4b left
        {
            Node * newroot = node->leftChildren;
            node->node_level-=2;
            node->leftedge=1;
            node->rightedge=1;
            node->leftChildren = nullptr;
            node->rightChildren=nullptr;
            newroot->rightChildren=node;
            newroot->leftedge =1;
            newroot->rightedge=1;
            node = newroot;
        }
        else if(node->leftedge ==3 && node->rightedge ==1 && node->rightChildren->leftedge==1 && node->rightChildren->rightedge ==2) //case 5 left
        {
            Node * rightchild = node->rightChildren;
            Node * newroot = rightchild->leftChildren;
            node->leftedge=1;
            node->rightedge = newroot->leftedge;
            node->node_level-=2;
            node->rightChildren = newroot->leftChildren;
            rightchild->leftedge = newroot->rightedge;
            rightchild->rightedge = 1;
            rightchild->node_level--;
            rightchild->leftChildren = newroot->rightChildren;
            newroot->leftChildren=node;
            newroot->rightChildren = rightchild;
            newroot->leftedge=2;
            newroot->rightedge=2;
            newroot->node_level+=2;
            node = newroot;
        }
        else if(node->rightedge ==3 && node->leftedge ==1 && node->leftChildren->leftedge==2 && node->leftChildren->rightedge ==1) //case 5right
        {
            Node * leftchild = node->leftChildren;
            Node * newroot = leftchild->rightChildren;
            node->leftedge=newroot->rightedge;
            node->rightedge = 1;
            node->node_level-=2;
            node->leftChildren = newroot->rightChildren;
            leftchild->leftedge = 1;
            leftchild->rightedge = newroot->leftedge;
            leftchild->node_level--;
            leftchild->rightChildren = newroot->leftChildren;
            newroot->leftChildren=leftchild;
            newroot->rightChildren = node;
            newroot->leftedge=2;
            newroot->rightedge=2;
            newroot->node_level+=2;
            node = newroot;
        }
        else if(node->leftedge==3 && node->rightedge==1 && node->rightChildren->leftedge==2 && node->rightChildren->rightedge==2)//case 6 left
        {
            node->leftedge=2;
            node->rightedge=1;
            node->node_level--;
            node->rightChildren->node_level--;
            node->rightChildren->leftedge=1;
            node->rightChildren->rightedge=1;
        }
        else if(node->rightedge==3 && node->leftedge==1 && node->leftChildren->leftedge==2 && node->leftChildren->rightedge==2)//case 6 right
        {
            node->leftedge=1;
            node->rightedge=2;
            node->node_level--;
            node->leftChildren->node_level--;
            node->leftChildren->leftedge=1;
            node->leftChildren->rightedge=1;
        }
        return node;
    }
    Node * findsuccessor(Node*node)
    {
        if(node->leftChildren==nullptr)
        {
            return node;
        }
        return findsuccessor(node->leftChildren);
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

};

template <typename K, typename V>
CrumpleTree<K, V>::CrumpleTree() {
    num_keys=0;
    root=nullptr;
}

template <typename K, typename V>
CrumpleTree<K, V>::~CrumpleTree() {
    //todo
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
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return tempNode->Value;
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
const V &CrumpleTree<K, V>::find(const K &key) const {
    Node * tempNode = root;
    while(tempNode!=nullptr)
    {
        if(key==tempNode->key)
        {
            return tempNode->Value;
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
    if(!contains(key))
    {
        return;
    }
    Node*currentNode = root;
    root = removehelper(currentNode,key);
    num_keys--;
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

}  // namespace shindler::ics46::project4

#endif
