#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

template <class T>

struct Node
{
    T info;
    Node<T> *m_left;
    Node<T> *m_right;
};

template <class T>
class BinarySearchTree
{
public:
    typedef void (*functionPointer)(T&);
    BinarySearchTree(const BinarySearchTree<T>& otherTree); //copy constructor
    BinarySearchTree(); //default constructor
    ~BinarySearchTree();

    /*Deep Copying Methods x 2 + 1*/

    //Finish BST without the function pointers

    void Insert(const T& item);
    bool Search(const T& target) const;
    void DeleteNode(const T& target);
    void InOrderTraversal(functionPointer funcPtr) const;
    void PreOrderTraversal(functionPointer funcPtr) const;
    void PostOrderTraversal(functionPointer funcPtr) const;
    void DeleteTree(); //remove the entire tree from memory

private:
    Node<T> *m_root;
    void Insert(Node<T>* newNode, Node<T>*& root);
    bool Search(Node<T>* root, const T& target) const;
    void DeleteNode(Node<T>*& root);
    void InOrderTraversal(Node<T>* root, functionPointer funcPtr) const;
    void PreOrderTraversal(Node<T>* root, functionPointer funcPtr) const;
    void PostOrderTraversal(Node<T>* root, functionPointer funcPtr) const;
    void CopyTree(Node<T>*& copyTree, Node<T>* otherTree);
    void destroy(Node<T>*& root); //to be called from destructor
    void DeleteTree(Node<T>*& root);
};

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& otherTree)
{
    if(otherTree.m_root == nullptr)
    {
        m_root = nullptr;
    }

    else
    {
        CopyTree(m_root, otherTree.m_root);
    }
}

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    m_root = nullptr;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    destroy(m_root);
}

template <class T>
void BinarySearchTree<T>::Insert(const T& item)
{
    Node<T> *newNode = new Node<T>;
    newNode->info = item;
    newNode->m_left = nullptr;
    newNode->m_right = nullptr;

    if(m_root == nullptr)
    {
        m_root = newNode;
    }

    else
    {
        Insert(newNode, m_root);
    }
}

template <class T>
void BinarySearchTree<T>::Insert(Node<T>* newNode, Node<T>*& root) //recursive
{
    if(root == nullptr)
    {
        root = newNode;
    }

    else if(newNode->info < root->info)
    {
        if(root->m_left == nullptr)
        {
            root->m_left = newNode;
        }

        else
        {
            Insert(newNode, root->m_left);
        }
    }

    else if(newNode->info > root->info)
    {
        if(root->m_right == nullptr)
        {
            root->m_right = newNode;
        }

        else
        {
            Insert(newNode, root->m_right);
        }
    }
}

template <class T>
bool BinarySearchTree<T>::Search(const T& target) const
{
    Node<T> *searchNode;
    bool found = false;

    if(m_root == nullptr)
    {
        found = false;
    }

    else
    {
        searchNode = m_root;

        while(searchNode != nullptr && !found)
        {
            if(searchNode->info == target)
            {
                found = true;
            }

            else if(searchNode->info > target)
            {
                searchNode = searchNode->m_left;
            }

            else
            {
                searchNode = searchNode->m_right;
            }
        }
    }
    return found;
}

template <class T>
bool BinarySearchTree<T>::Search(Node<T>* root, const T& target) const
{
    bool found = false;

    if(root == nullptr)
    {
        found = false;
    }

    else if(root->info == target)
    {
        found = true;
    }

    else if(target < root->info)
    {
        return Search(root->m_left, target);
    }

    else
    {
        return Search(root->m_right, target);
    }
}

template <class T>
void BinarySearchTree<T>::DeleteNode(const T& target)
{
    Node<T> *currentNode;
    Node<T> *nextNode;
    bool found = false;

    if(m_root == nullptr)
    {
        found = false;
    }

    else
    {
        currentNode = m_root;
        nextNode = m_root;

        while(currentNode != nullptr && !found)
        {
            if(currentNode->info == target)
            {
                found = true;
            }

            else
            {
                nextNode = currentNode;
                if(currentNode->info > target)
                {
                    currentNode = currentNode->m_left;
                }

                else
                {
                    currentNode = currentNode->m_right;
                }
            }
        }//end while

        if(currentNode == nullptr)
        {
            found = false;
        }

        else if(found)
        {
            if(currentNode == m_root)
            {
                DeleteNode(m_root);
            }

            else if(nextNode->info > target)
            {
                DeleteNode(nextNode->m_left);
            }

            else
            {
                DeleteNode(nextNode->m_right);
            }
        }//end if else

        else
        {
            found = false;
        }
    }//end else
}

template <class T>
void BinarySearchTree<T>::DeleteNode(Node<T>*& root)
{
    Node<T> *currentNode;
    Node<T> *nextNode;
    Node<T> *temp; //pointer to delete a node

    if(root == nullptr)
    {
        return false;
    }

    else if(root->m_left == nullptr && root->m_right == nullptr)
    {
        temp = root;
        root = nullptr;
        delete temp;
    }

    else if(root->m_left == nullptr)
    {
        temp = root;
        root = temp->m_right;
        delete temp;
    }

    else if(root->m_right == nullptr)
    {
        temp = root;
        root = temp->m_left;
        delete temp;
    }

    else
    {
        currentNode = root->m_left;
        nextNode = nullptr;

        while(currentNode->m_right != nullptr)
        {
            nextNode = currentNode;
            currentNode = currentNode->m_right;
        }

        root->info = currentNode->info;

        if(nextNode == nullptr)
        {
            root->m_left = currentNode->m_left;
        }

        else
        {
            nextNode->m_right = currentNode->m_left;
        }

        delete currentNode;
    }
}

template <class T>
void BinarySearchTree<T>::InOrderTraversal(functionPointer funcPtr) const
{
    InOrderTraversal(m_root, funcPtr);
}

template <class T>
void BinarySearchTree<T>::InOrderTraversal(Node<T>* root, functionPointer funcPtr) const
{
    if(root != nullptr)
    {
        InOrderTraversal(root->m_left, funcPtr);
        funcPtr(root->info);
        InOrderTraversal(root->m_right, funcPtr);
    }
}

template <class T>
void BinarySearchTree<T>::PreOrderTraversal(functionPointer funcPtr) const
{
    PreOrderTraversal(m_root, funcPtr);
}

template <class T>
void BinarySearchTree<T>::PreOrderTraversal(Node<T>* root, functionPointer funcPtr) const
{
    if(root != nullptr)
    {
        funcPtr(root->info);
        PreOrderTraversal(root->m_left, funcPtr);
        PreOrderTraversal(root->m_right, funcPtr);
    }
}

template <class T>
void BinarySearchTree<T>::PostOrderTraversal(functionPointer funcPtr) const
{
    PostOrderTraversal(m_root, funcPtr);
}

template <class T>
void BinarySearchTree<T>::PostOrderTraversal(Node<T>* root, functionPointer funcPtr) const
{
    if(root != nullptr)
    {
        PostOrderTraversal(root->m_left, funcPtr);
        PostOrderTraversal(root->m_right, funcPtr);
        funcPtr(root->info);
    }
}

template <class T>
void BinarySearchTree<T>::CopyTree(Node<T>*& copyTree, Node<T>* otherTree)
{
    if(otherTree == nullptr)
    {
        copyTree = nullptr;
    }

    else
    {
        copyTree = new Node<T>;
        copyTree->info = otherTree->info;
        CopyTree(copyTree->m_left, otherTree->m_left);
        CopyTree(copyTree->m_right, otherTree->m_right);
    }
}

template <class T>
void BinarySearchTree<T>::destroy(Node<T>*& root)
{
    if(root != nullptr)
    {
        destroy(root->m_left);
        destroy(root->m_right);
        delete root;
        root = nullptr;
    }
}

template <class T>
void BinarySearchTree<T>::DeleteTree()
{
    DeleteTree(m_root);
}

template <class T>
void BinarySearchTree<T>::DeleteTree(Node<T>*& root) //recursive
{
    if (root == nullptr)
    {
        return;
    }

    DeleteTree(root->m_left);
    DeleteTree(root->m_right);

    delete root;
    root = nullptr;
}

#endif // BINARYSEARCHTREE_H_INCLUDED
