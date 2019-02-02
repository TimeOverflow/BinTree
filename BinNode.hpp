//
// Created by zhang on 2019/1/25.
//

#ifndef BINTREE_BINNODE_HPP
#define BINTREE_BINNODE_HPP

#include <stack>
#include <queue>

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

    // different versions of PreTraverse
    template <typename VST>
    void travPre_R(BinNode<T>* x, VST& visit);  // Recursive PreTraverse
    template <typename VST>
    void travPre_Iter1(BinNode<T>* x, VST& visit);  //iterative PreTraverse, version--1
    template <typename VST>
    void travPre_Iter2(BinNode<T>* x, VST& visit);  //iterative PreTraverse, version--2
    template <typename VST>
    static void visitAlongLeftBranch(BinNode<T>* x, VST& visit, std::stack<BinNode<T>*>& s);


    template <typename VST>
    void travPost_R(BinNode<T>* x, VST& visit); // Recursive PostTraverse
    static void gotoHLVFL (std::stack<BinNode<T>*> &s);  //HLVFL: Highest Leaf Visible From Left
    template <typename VST>
    void travPost_Iter(BinNode<T>* x, VST &visit);

    // different versions of InorderTraverse
    template <typename VST>
    void travIn_R(BinNode<T>* x, VST& visit);   // Recursive InoderTraverse
    template <typename VST>
    void travIn_Iter1(BinNode<T>* x, VST& visit);  //iterative InorderTraverse, version--1
    template <typename VST>
    void travIn_Iter2(BinNode<T>* x, VST& visit);  //iterative InorderTraverse, version--2
    template <typename VST>
    void travIn_Iter3(BinNode<T>* x, VST& visit);  //iterative InorderTraverse, version--3
    template <typename VST>
    static void goAlongLeftBranch(BinNode<T>* x, std::stack<BinNode<T>*>& s)
    {
        while (x != nullptr)
        {
            s.push(x);
            x = x->lc;
        }
    }

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
    inline bool isRoot()  { return parent == nullptr; }

    inline bool isLChild()  { return ! isRoot() && (this == this->parent->lc); }

    inline bool isRChild()  { return ! isRoot() && (this == this->parent->rc); }
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
int BinNode<T>::size()
{
    int count = 1;
    if (lc != nullptr)
    {
        count += lc->size();
    }
    if (rc != nullptr)
    {
        count += rc->size();
    }
    return count;
}

template<typename T>
BinNode<T> *BinNode<T>::succ()
{
    BinNode<T>* su = this;
    if (su->hasRChild())
    {
        su = su->rc;
        while (su->lc != nullptr)
        {
            su = su->lc;
        }
    }
    else
    {
        while (su->isRChild())
        {
            su = su->parent;
        }
        su = su->parent;
    }
    return su;
}


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

template<typename T>
template<typename VST>
void BinNode<T>::travPre_Iter1(BinNode<T> *x, VST &visit)
{
    std::stack<BinNode<T>*> s;
    if (x != nullptr)
    {
        s.push(x);      //root node
    }
    while (! s.empty())
    {
        x = s.top();
        s.pop();
        visit(x->data);
        if (x->hasRChild())
        {
            s.push(x->rc);
        }
        if (x->hasLChild())
        {
            s.push(x->lc);
        }
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_Iter2(BinNode<T> *x, VST &visit)
{
    std::stack<BinNode<T>*> s;
    while (true)
    {
        goAlongLeftBranch(x, visit, s);
        if (s.empty()) break;
        x = s.top();
        s.pop();
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::visitAlongLeftBranch(BinNode<T> *x, VST &visit, std::stack<BinNode<T> *> &s)
{
    while (x != nullptr)
    {
        visit(x->data);
        if (x->rc != nullptr)
        {
            s.push(x->rc);
        }
        x = x->lc;
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_Iter1(BinNode<T> *x, VST &visit)
{
    std::stack<BinNode<T>*> s;
    while (true)
    {
        goAlongLeftBranch(x, s);
        if (s.empty()) break;
        x = s.top();
        s.pop();
        visit(x->data);
        x = x->rc;
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_Iter2(BinNode<T> *x, VST &visit)
{
    std::stack<BinNode<T>*> s;
    while (true)
    {
        if (x != nullptr)
        {
            s.push(x);
            x = x->lc;
        }
        else if (! s.empty())
        {
            x = s.top();
            s.pop();
            visit(x->data);
            x = x->rc;
        }
        else
        {
            break;
        }
    }

}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_Iter3(BinNode<T> *x, VST &visit)
{
    bool traceback = false;
    while (true)
    {
        if (!traceback && x->hasLChild())
        {
            x = x->lc;
        }
        else
        {
            visit(x->data);
            if (x->hasRChild())
            {
                x = x->rc;
                traceback = false;
            }
            else
            {
                x = x->succ();
                if (x == nullptr)
                {
                    break;
                }
                traceback = true;
            }
        }
    }
}

template<typename T>
void BinNode<T>::gotoHLVFL(std::stack<BinNode<T>*> &s)
{
    BinNode<T>* x = s.top();
    while (x != nullptr)
    {
        if (x->hasLChild())
        {
            if (x->hasRChild())
            {
                s.push(x->rc;)
            }
            s.push(x->lc);
        }
        else
        {
            s.push(x->rc);
        }
        x = s.top();
    }
    s.pop();
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_Iter(BinNode<T> *x, VST &visit)
{
    std::stack<BinNode<T>*> s;
    if (x != nullptr)
    {
        s.push(x);    //the root
    }
    while (!s.empty())
    {
        if (s.top() != x->parent)  // x must be brother of s.top()
        {
            gotoHLVFL(s);
        }
        x = s.top();
        s.pop();
        visit(x->data);
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit)
{
    std::queue<BinNode<T>*> q;
    q.push(this);
    while (!q.empty())
    {
        BinNode<T>* x = q.front();
        q.pop();
        visit(x->data);
        if (x->hasLChild())
        {
            q.push(x->lc);
        }
        if (x->hasRChild())
        {
            q.push(x->rc);
        }
    }
}


#endif //BINTREE_BINNODE_HPP
