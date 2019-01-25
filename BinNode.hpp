//
// Created by zhang on 2019/1/25.
//

#ifndef BINTREE_BINNODE_HPP
#define BINTREE_BINNODE_HPP

template <typename T>
class BinNode
{
public:
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;    //left child
    BinNode<T>* rc;    //right child
    int height;

public:
    //Constructors
    BinNode():
        parent(nullptr), lc(nullptr), rc(nullptr), height(0)
    {}

    explicit BinNode(T d, BinNode<T>* p = nullptr, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, int h = 0):
        data(d), parent(p), lc(l), rc(r), height(h)
    {}

    //operation interface
    int size();      //sum of ancestors of this node
    BinNode<T>* insertAsLC (const T & e);
    BinNode<T>* insertAsRC (const T & e);
    BinNode<T>* succ();

    //traverse
    template <typename VST> void travLevel (VST&);
    template <typename VST> void travPre (VST&);
    template <typename VST> void travIn (VST&);
    template <typename VST> void travPost (VST&);

    //boolean operation
    bool operator< (const BinNode& bn)
    {
        return data < bn.data;
    }
    bool operator== (const BinNode& bn)
    {
        return data == bn.data;
    }

    //properties
    bool isRoot()  { return parent == nullptr; }
    bool isLChild()  { return ! isRoot() && (this == this->parent->lc); }
    bool isRChild()  { return ! isRoot() && (this == this->parent->rc); }
    bool hasParent()  { return parent != nullptr; }
    bool hasLChild()  { return lc != nullptr; }
    bool hasRChild()  { return rc != nullptr; }
    bool hasChild()  { return hasLChild() || hasRChild(); }
    bool hasBothChild()  { return hasLChild() && hasRChild() };
    bool isLeaf()  { return ! hasChild(); }

    //relations
    BinNode<T>* sibling()
    {
        if ( isRoot() )
        { return nullptr; }
        else
        {
            if ( isLChild() )
            {
                return this->parent->rc;
            }
            else
            {
                return this->parent->lc;
            }
        }
    }

    BinNode<T>* uncle()
    {
        if ( isRoot() || parent->isRoot() )
        {
            return nullptr;
        }
        else
        {
            if (parent->isLChild())
            {
                return parent->parent->rc;
            }
            else
            {
                return parent->parent->lc;
            }
        }
    }
};

template<typename T>
BinNode<T> *BinNode<T>::insertAsLC(const T &e)
{
    auto* pl = new BinNode(e, this);
    if (this->hasLChild())
    {
        pl->lc = this->lc->lc;
        pl->rc = this->lc->rc;
        pl->height = this->lc->height;

        BinNode<T>* p = this->lc;
        this->lc = pl;
        delete p;
    }
    else
    {
        this->lc = pl;
    }
    return pl;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRC(const T &e)
{
    auto* rl = new BinNode(e, this);
    if (this->hasRChild())
    {
        rl->lc = this->rc->lc;
        rl->rc = this->rc->rc;
        rl->height = this->rc->height;

        BinNode<T>* p = this->rc;
        this->rc = rl;
        delete p;
    }
    else
    {
        this->rc = rl;
    }
    return rl;
}


#endif //BINTREE_BINNODE_HPP
