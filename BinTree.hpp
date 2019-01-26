//
// Created by zhang on 2019/1/26.
//

#ifndef BINTREE_BINTREE_HPP
#define BINTREE_BINTREE_HPP

#include "BinNode.hpp"

template <typename T>
class BinTree
{
protected:
    int _size;
    BinNode<T>* _root;
    virtual int updateHeight (BinNode<T>* x);
    void updateHeightAbove (BinNode<T>* x);

public:
    BinTree():
        _size(0), _root(nullptr)
    {}
    ~BinTree()
    {
        if (_size > 0)
        {
            remove(_root);
        }
    }

    int size() const
    {
        return _size;
    }
    bool isEmpty() const
    {
        return _root == nullptr;
    }
    BinNode<T>* root() const
    {
        return _root;
    }
    BinNode<T>* insertAsRoot (const T& e);
    BinNode<T>* insertAsLC (BinNode<T>* x, const T& e);
    BinNode<T>* insertAsRC (BinNode<T>* x, const T& e);
    BinNode<T>* attachAsLSubtree (BinNode<T>* x, BinTree<T>* & st);
    BinNode<T>* attachAsRSubtree (BinNode<T>* x, BinTree<T>* & st);
    int remove (BinNode<T>* x);  //delete subtree rooted by x, return the size of this subtree
    //delete subtree x from the current tree, and transfer it to an independenet tree
    BinTree<T>* secede (BinNode<T>* x);

    //traverse
    template <typename VST>
    void travLevel (VST & visit)
    {
        if (_root != nullptr)
        {
            _root->travLevel(visit);
        }
    }
    template <typename VST>
    void travPre (VST & visit)
    {
        if (_root != nullptr)
        {
            _root->travPre(visit);
        }
    }
    template <typename VST>
    void travIn (VST & visit)
    {
        if (_root != nullptr)
        {
            _root->travIn(visit);
        }
    }
    template <typename VST>
    void travPost (VST & visit)
    {
        if (_root != nullptr)
        {
            _root->travPost(visit);
        }
    }

    // boolean operation
    bool operator< (const BinTree<T>& t)
    {
        return !isEmpty() && !t.isEmpty() && (*_root) < *(t._root);
    }
    bool operator== (const BinTree<T>& t)
    {
        return !isEmpty() && !t.isEmpty() && (_root == t._root);
    }

};


#endif //BINTREE_BINTREE_HPP
