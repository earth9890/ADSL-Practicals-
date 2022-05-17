#include <iostream>
using namespace std;
#define MAX 50

class node
{
    int data;
    node *lc;
    node *rc;

public:
    node()
    {
        // cout<<"Default constructor of node is called \n";
        data = 0;
        lc = rc = NULL;
    }
    node(int d)
    {
        data = d;
        lc = rc = NULL;
    }

    friend class tree;
    friend class Stack;
};

class Stack
{
public:
    int topEle;
    node *s[MAX];
    Stack() { topEle = -1; }
    void push(node *ele)
    {
        s[++topEle] = ele;
    }

    node *pop()
    {
        node *x;
        if (topEle == -1)
        {
            cout << "Stack empty \n";
            return NULL;
        }
        else
        {
            x = s[topEle];
            topEle--;
            return x;
        }
    }
    node *top()
    {
        return s[topEle];
    }

    bool isEmpty()
    {
        return (topEle < 0);
    }

    void display()
    {
        while (!isEmpty())
        {
            node *t = pop();
            cout << "\t" << t->data;
        }
    }
};

class tree
{
    Stack s1;

public:
    node *root;
    tree()
    {
        // cout<<"Default constructor of tree is called \n";
        root = NULL;
    }

    void operator=(tree &);
    node *create();
    // node * insert(node *p,int x);
    void inorder_rec(node *t);
    void preorder_rec(node *t);
    void postorder_rec(node *t);
    void inorder_nonrec(node *);
    void preorder_nonrec(node *);
    void postorder_nonrec(node *);
    void delete_tree(node *);
    void internal_nodes(node *);
    void leaf_nodes(node *);
    node *mirror(node *);
    node *copytree(node *t);
    void show()
    {
        inorder_nonrec(root);
        preorder_nonrec(root);
        postorder_nonrec(root);
    }
    void ln()
    {
        leaf_nodes(root);
    }
    void in()
    {
        internal_nodes(root);
    }
    void dt()
    {
        delete_tree(root);
        cout << "Tree Deleted Successfully\n";
    }
    node *setRoot(node *p)
    {
        root = p;
        return root;
    }
    void mirrortree()
    {

        node *n = mirror(root);
        inorder_rec(n);
        cout << endl;
    }
    void inorder()
    {
        inorder_nonrec(root);
    }
};
void tree ::operator=(tree &t1)
{
    root = copytree(t1.root);
}
node *tree::copytree(node *t1)
{
    node *n1 = NULL;
    if (t1 != NULL)
    {
        n1 = new node();

        n1->data = t1->data;
        n1->lc = copytree(t1->lc);
        n1->rc = copytree(t1->rc);
    }
    return n1;
}
void tree ::preorder_nonrec(node *t)
{
    cout << "Pre order NonRec Display of Binary Tree\n";
    Stack s;
    s.push(t);
    while (!s.isEmpty())
    {
        t = s.pop();
        cout << "\t" << t->data;
        if (t->rc != NULL)
        {
            s.push(t->rc);
        }
        if (t->lc != NULL)
        {
            s.push(t->lc);
        }
    }
    cout << endl;
}
void tree::inorder_nonrec(node *t)
{
    cout << "Inorder NonRec Display of Binary Tree\n";

    Stack s;
    while (t != NULL)
    {

        s.push(t);
        t = t->lc;
    }
    while (!s.isEmpty())
    {
        t = s.pop();
        cout << "\t" << t->data;
        t = t->rc;
        while (t != NULL)
        {

            s.push(t);
            t = t->lc;
        }
    }
    cout << endl;
}

void tree ::postorder_nonrec(node *t)
{
    cout << "Postorder NonRec Display of Binary Tree\n";
    Stack s1, s2;
    s1.push(t);
    while (!s1.isEmpty())
    {
        t = s1.pop();
        s2.push(t);
        if (t->lc != NULL)
            s1.push(t->lc);
        if (t->rc != NULL)
            s1.push(t->rc);
    }

    s2.display();
    cout << endl;
}
void tree::inorder_rec(node *t)
{
    if (t != NULL)
    {
        inorder_rec(t->lc);
        cout << t->data << "\t";
        inorder_rec(t->rc);
    }
}

void tree::preorder_rec(node *t)
{
    if (t != NULL)
    {
        cout << t->data << "\t";
        preorder_rec(t->lc);
        preorder_rec(t->rc);
    }
}

void tree::postorder_rec(node *t)
{
    if (t != NULL)
    {
        postorder_rec(t->lc);
        postorder_rec(t->rc);
        cout << t->data << "\t";
    }
}

node *tree::create()
{
    int x;
    cout << "Enter the data or -1 to stop \n";
    cin >> x;
    if (x == -1)
    {
        return NULL;
    }
    else
    {
        node *p = new node;
        p->data = x;
        cout << "Enter the left child of " << x << endl;
        p->lc = create();
        cout << "Enter the Right child of " << x << endl;
        p->rc = create();
        return p;
    }
}
void tree::delete_tree(node *t)
{
    if (t != NULL)
    {
        delete_tree(t->lc);
        delete_tree(t->rc);
        delete t;
    }
}
void tree::leaf_nodes(node *t)
{
    if (t == NULL)
        return;
    if (t->lc == NULL && t->rc == NULL)
    {
        cout << t->data << " ";
        return;
    }
    if (t->lc != NULL)
    {
        leaf_nodes(t->lc);
    }
    if (t->rc != NULL)
    {
        leaf_nodes(t->rc);
    }
}
void tree::internal_nodes(node *t)
{

    if (t != NULL)
    {
        if (t->lc != NULL || t->rc != NULL)
        {
            cout << t->data << " ";
        }
        if (t->lc != NULL)
            
        internal_nodes(t->lc);
        if (t->rc != NULL)
            
        internal_nodes(t->rc);
    }
}
node *tree::mirror(node *t)
{
    node *p = NULL;
    if (t != NULL)
    {
        p = new node();
        p->data = t->data;
        p->lc = mirror(t->rc);
        p->rc = mirror(t->lc);
    }
    // inorder_rec(p);
    return p;
}

int main()
{
    int ch, c;
    node *p, *q;
    Stack s1, s2;
    tree y, t1, t2, t3;
    do
    {
        cout << "Enter Choice\n1.Create and Traversal\n2.Leaf Nodes\n3.Internal Nodes\n4.Mirror of Tree\n5.Deletion of Tree\n6.Copy of tree\n";
        cin >> c;
        switch (c)
        {
        case 1:
        {
            cout << "Creating Binary Tree\n";
            p = y.create(); // public root, tree t1; t1.root=create()
            y.setRoot(p);
            cout << "\nInorder Display of Binary Tree\n";
            y.inorder_rec(p); // inorder_rec(t1.getroot())
            cout << "\nPreorder Display of Binary Tree\n";
            y.preorder_rec(p);
            cout << "\nPostorder Display of Binary Tree\n";
            y.postorder_rec(p);
            break;
        }

        case 2:
            y.ln();
            break;
        case 3:
            y.in();
            break;
        case 4:
            y.mirrortree();
            break;
        case 5:
            y.dt();
            break;
        case 6:
            t1 = y;
            cout << "Copying Tree\n";
            t1.inorder();
            break;
        }
    } while (0 < c < 8);

    return 0;
}