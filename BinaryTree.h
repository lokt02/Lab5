//
// Created by lokt0 on 22.05.2021.
//

#ifndef LAB5_BINARYTREE_H
#define LAB5_BINARYTREE_H

template<class T>
class Tree{
protected:
    class Node {
    public:
        explicit Node(T key) : key(key), height(1){}
        Node(const Node& node){
            if(&node == nullptr)
                throw std::range_error("Node cant be created from null");
            key = node.key;
            height = node.height;
            if(node.left) left = new Node(*node.left);
            if(node.right) right = new Node(*node.right);
        }
        explicit Node(Node* node){
            if(node){
               key = node->key;
               height = node->height;
               if(node->left) left = new Node(node->left);
                if(node->right) right = new Node(node->right);
            }
        }
        Node():Node(nullptr){};

        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
    };
private:
    void DestroyNode(Node* node) {
        if (node) {
            if(node->left) DestroyNode(node->left);
            if(node->right) DestroyNode(node->right);
            delete node;
        }
    }

    int height(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    Node *RightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        // Return new root
        return x;
    }
    Node *LeftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        // Return new root
        return y;
    }
    int GetBalance(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* FindMin(Node* node)
    {
        while(node->left != NULL) node = node->left;
        return node;
    }
protected:
    Node* root;

    template<class T1>
    void Mapping(T1(*mapper)(T), Node* node, Tree<T>* tree){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        // auto temp = mapper(node->key);
        tree->Append(mapper(node->key));
        // node->key = temp;
        if (node->left) Mapping(mapper, node->left, tree);
        if (node->right) Mapping(mapper, node->right, tree);
    }

    void Mapping(std::function<T(T)> const & mapper, Node* node, Tree<T>* tree){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        // auto temp = mapper(node->key);
        if(node) {
            tree->Append(mapper(node->key));
            // node->key = temp;
            if (node->left) Mapping(mapper, node->left, tree);
            if (node->right) Mapping(mapper, node->right, tree);
        }
    }

    void WherePath(bool(*predicate)(T), Node* node, Tree<T> *tree){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        if(predicate(node->key)) tree->Append(node->key);
        if(node->left) WherePath(predicate, node->left, tree);
        if(node->right) WherePath(predicate, node->right, tree);
    }

    T ReducePath(T(*reducer)(T, T), T const& c, Node* node){
        if(node){
            T res = reducer(node->key, c);
            res = ReducePath(reducer, res, node->left);
            res = ReducePath(reducer, res, node->right);
            return res;
        }
        return c;
    }
public:
    Tree(){
        root = nullptr;
    }

    explicit Tree(T rootKey){
        root = new Node(rootKey);
    }

    Tree(std::initializer_list<T> items):Tree(){
        for(T item : items){
            Append(item);
        }
    }

    explicit Tree(const Node &root){
        this->root = new Node(root);
    }
    explicit Tree(Node *root){
        this->root = new Node(root);
    }

    Tree(const Tree &tree): Tree(){
        if(tree.root != nullptr) root = new Node(*tree.root);
    }

    explicit Tree(Tree<T>* tree): Tree(){
        if(tree != nullptr && tree->root != nullptr) root = new Node(tree->root);
    }

    ~Tree(){
        DestroyNode(root);
    }

    void Append(T key){
        if(&key == nullptr){
            throw std::range_error("You cant append NULL");
        }
        root = Insert(root, key);
    }

    Node* Insert(Node* node, T key)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL)
            return(new Node(key));

        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
                               height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = GetBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return RightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return LeftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }
    Node* Remove(T key){
        if(&key == nullptr || !root){
            throw std::range_error("You cant remove NULL");
        }
        return Delete(&root, key);
    }
    Node* Delete(Node **node, T key) {
        if(*node == nullptr) return *node;
        else if(key < (*node)->key) (*node)->left = Delete(&(*node)->left, key);
        else if (key > (*node)->key) (*node)->right = Delete(&(*node)->right, key);
            // Wohoo... I found you, Get ready to be deleted
        else {
            // Case 1:  No child
            if((*node)->left == nullptr && (*node)->right == nullptr) {
                delete *node;
                *node = nullptr;
            }
                //Case 2: One child
            else if((*node)->left == NULL) {
                struct Node *temp = *node;
                *node = (*node)->right;
                delete temp;
            }
            else if((*node)->right == NULL) {
                struct Node *temp = *node;
                *node = (*node)->left;
                delete temp;
            }
                // case 3: 2 children
            else {
                Node *temp = FindMin((*node)->right);
                (*node)->key = temp->key;
                (*node)->right = Delete(&(*node)->right, temp->key);
            }
        }
        return *node;
    }

    bool Search(T key){
        if(&key == nullptr || !root){
            throw std::range_error("You cant search NULL");
        }
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(key < node.key){
                current = &node.left;
            }
            else{
                if(key > node.key){
                    current = &node.right;
                }
                else{
                    return (*current)->key == key;
                }
            }
        }
        return false;
    }

    T* GetValue(T key){
        if(&key == nullptr || !root){
            throw std::range_error("You cant search NULL");
        }
        Node* current = root;
        while (current){
            Node& node = *current;
            if(key < node.key){
                current = node.left;
            }
            else{
                if(key > node.key){
                    current = node.right;
                }
                else{
                    if(node.key == key)
                        return &(node.key);
                }
            }
        }
        // throw std::range_error("This key does not exists in tree");
        return nullptr;
    }

    Node* SearchNode(T key){
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(key < node.key){
                current = &node.left;
            }
            else{
                if(key > node.key){
                    current = &node.right;
                }
                else{
                    return (*current);
                }
            }
        }
        return nullptr;
    }

    Tree<T> SubTree(T key){
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(key < node.key){
                current = &node.left;
            }
            else{
                if(key > node.key){
                    current = &node.right;
                }
                else{
                    return Tree(**current);
                }
            }
        }
        return Tree();
    }

    bool SearchSubTree(const Tree& tree){
        if(&tree == nullptr || tree.root == nullptr) return false;
        Node** current = &root;
        T key = tree.root->key;
        while (*current){
            Node& node = **current;
            if(key < node.key){
                current = &node.left;
            }
            else{
                if(key > node.key){
                    current = &node.right;
                }
                else{
                    bool a1 = false;
                    if((*current)->right != nullptr && tree.root->right != nullptr)
                        a1 = tree.root->right->key == (*current)->right->key;
                    else if((*current)->right == nullptr && tree.root->right == nullptr)
                        a1 = true;

                    bool a2 = false;
                    if((*current)->left != nullptr && tree.root->left != nullptr)
                        a2 = tree.root->left->key == (*current)->left->key;
                    else if((*current)->left == nullptr && tree.root->left == nullptr)
                        a2 = true;

                    bool result = key == (*current)->key && a1 && a2;

                    return result;
                }
            }
        }
        return false;
    }

    template<class T1>
    Tree<T1> Map(T1(*mapper)(T)){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Tree<T1> newTree = Tree<T1>();
        Mapping(mapper, this->root, &newTree);
        return newTree;
    }

    Tree<T> Map(std::function<T(T)> const & mapper){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Tree<T> newTree = Tree<T>();
        Mapping(mapper, this->root, &newTree);
        return newTree;
    }
    Tree<T> Where(bool(*predicate)(T)){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Tree<T> newTree = Tree<T>();
        WherePath(predicate, this->root, &newTree);
        return newTree;
    }
    Tree<T> Where(std::function<bool(T)> const & predicate){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Tree<T> newTree = Tree<T>();
        WherePath(predicate, this->root, &newTree);
        return newTree;
    }
    T Reduce(T(*reducer)(T, T), T const &c){
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = ReducePath(reducer, c, root);
        return res;
    }
    T Reduce(std::function<T(T, T)> const & reducer, T const &c){
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = ReducePath(reducer, c, root);
        return res;
    }

    Tree<T> &operator=(const Tree<T> &tree){
        if(&tree != this && tree.root != nullptr) {
            DestroyNode(root);
            root = new Node(tree.root);
        }
        return *this;
    }

    void PreOrder(Node *node, int ctr)
    {
        if(node != nullptr)
        {
            std::string brackets[] = {"{", "}", "(", ")", "[", "]"};
            std::cout << brackets[ctr] << node->key << " ";
            PreOrder(node->left, (ctr + 2) % 6);
            PreOrder(node->right, (ctr + 4) % 6);
            std::cout << brackets[ctr + 1];
        }
    }
    void Output(){
        PreOrder(root, 0);
        std::cout << "\n";
    }
};

#endif //LAB5_BINARYTREE_H
