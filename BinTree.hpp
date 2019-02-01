//
// Created by zhang on 2019/1/26.
//

#ifndef BINTREE_BINTREE_HPP
#define BINTREE_BINTREE_HPP

#include "BinNode.hpp"

int max (int x, int y)
{
    return x > y ? x : y;
}

template <typename bt>
int statue(BinNode<bt>* p)
{
    return p != nullptr ? p->height : -1;
}

template <typename T>
class BinTree
{
protected:
    int _size;
    BinNode<T>* _root;

    virtual int updateHeight (BinNode<T>* x)
    {
        return x->height = max( statue(x->lc), statue(x->rc) ) + 1;
    }

    void updateHeightAbove (BinNode<T>* x)
    {
        while (x != nullptr)
        {
            updateHeight(x);
            x = x->parent;
        }
    }

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

    BinNode<T>* insertAsRoot (const T& e);  // insert data e to an empty binary tree
    BinNode<T>* insertAsLC (BinNode<T>* x, const T& e);  // insert e as lc of x
    BinNode<T>* insertAsRC (BinNode<T>* x, const T& e);
    BinNode<T>* attachAsLSubtree (BinNode<T>* x, BinTree<T>* & st);
    BinNode<T>* attachAsRSubtree (BinNode<T>* x, BinTree<T>* & st);
    // int remove (BinNode<T>* x);  // delete subtree rooted by x, return the size of this subtree

    /* delete subtree x from the current tree, and transfer it to an independenet tree*/
    BinTree<T>* secede (BinNode<T>* x);

    // traverse
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

template<typename T>
BinNode<T> *BinTree<T>::insertAsRoot(const T &e)
{
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsLC(BinNode<T> *x, const T &e)
{
    ++_size;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRC(BinNode<T> *x, const T &e)
{
    ++_size;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsLSubtree(BinNode<T> *x, BinTree<T>* & st)
{
    x->lc = st->_root;
    x->lc->parent = x;
    _size += st->_size;
    updateHeightAbove(x);
    return x;
}

template<typename T>
BinNode<T> *BinTree<T>::attachAsRSubtree(BinNode<T> *x, BinTree<T> *&st)
{
    x->rc = st->_root;
    x->rc->parent = x;
    -_size += st->_size;
    updateHeightAbove(x);
    return x;
}

template<typename T>
BinTree<T> *BinTree<T>::secede(BinNode<T>* x)
{
    x->fromParent() = nullptr;
    updateHeightAbove(x->parent);
    BinTree<T>* s = new BinTree<T>;
    s->_root = x;
    x->parent = nullptr;
    s->_size = x->size();
    _size -= s->_size;
    return s;
}



#endif //BINTREE_BINTREE_HPP
