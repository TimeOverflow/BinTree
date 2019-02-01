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

    /*
     * The following functions are all traverse operations,
     * which includes level, pre, inoder and post.
     */
    template <typename VST> void travLevel (VST&);

    template <typename VST> void travPre (VST& visit)
    {
        travPre_R(this, visit);
    }
    template <typename VST> void travIn (VST& visit)
    {
        travIn_R(this, visit);
    }
    template <typename VST> void travPost (VST& visit)
    {
        travPost_R(this, visit);
    }

    template <typename VST>
    void travPre_R(BinNode<T>* x, VST& visit);  // Recursive PreTraverse

    template <typename VST>
    void travPost_R(BinNode<T>* x, VST& visit); // Recursive PostTraverse

    template <typename VST>
    void travIn_R(BinNode<T>* x, VST& visit);   // Recursive InoderTraverse

    /*
     * The end of declarations of traverse functions.
     */

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
    BinNode<T>* fromParent()
    {
        if (isRoot())
        {
            return this;
        }
        else
        {
            if (isLChild())
            {
                return parent->lc;
            }
            else
            {
                return parent->rc;
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

template <typename T>
template <typename VST>
void BinNode<T>::travPre_R(BinNode<T> *x, VST &visit)  //Recursive PreTraverse
{
    if (x == nullptr)
    {
        return;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_R(BinNode<T> *x, VST &visit)
{
    if (x == nullptr)
    {
        return;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_R(BinNode<T> *x, VST &visit)
{
    if (x == nullptr)
    {
        return;
    }
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}


#endif //BINTREE_BINNODE_HPP
