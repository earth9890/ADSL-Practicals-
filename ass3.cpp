#include<iostream>

using namespace std;

class node
{
    public:
    int data;
    node *left,*right;
    int lflag , rflag;

    node()
    {
        left = NULL;
        right = NULL;
        lflag =0;
        rflag =0;
    }

    node(int d)
    {
        left = NULL;
        right = NULL;
        lflag=rflag=0;
        data = d;
    }

};

class BST
{
    public:
    node *root,*head;

    BST()
    {
        root = NULL;
        head = new node(500);
        head ->left = head->right = head;
    }

    void insert(int);
    void inorder();
    void preorder();
};


void BST ::insert(int d)
{
    if(root == NULL)
    {
        root = new node(d);
        root->left = root->right =head;
        root->lflag = root->rflag =1;
        head ->left = root;
        head->lflag =1;
        cout<<"\n Inserted Successfully";
    }
    else
    {
        node *curr =root;
        while(curr!=NULL)
        {
            if(d < curr->data)
            {
                node *p = new node(d);
                if(curr->lflag == 1)
                {
                    p->left = curr->left;
                    curr->left = p;
                    p->lflag=1;
                    curr->lflag=0;
                    p->right = curr;
                    p->rflag = 1;
                    cout<<"\n Inserted Successfully ";
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }

            if(d > curr->data)
            {
                node *p = new node(d);
                if(curr->rflag == 1)
                {
                    p->right = curr->right;
                    curr->right =p;
                    p->rflag = 1;
                    curr->rflag =0;
                    p->left = curr;
                    p->lflag =1;
                    cout<<"\n Inserted Successfully ";
                    break;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
}

void BST ::inorder()
{
    node *p = root;

    while(p->lflag ==0)
    {
        p=p->left;
    }

    while (p!=head)
    {
        cout<<p->data<<" ";
        if(p->rflag==0)
        {
            p=p->right;
            while(p->lflag==0)
            {
                p=p->left;
            }
        }
        else
        {
            p=p->right;
        }
    }
}

void BST ::preorder()
{
    node *p = root;

    while(p!=head)
    {
        while(p->lflag ==0)
        {
            cout<<p->data<<" ";
            p=p->left;
        }

        cout<<p->data<<" ";
        while(p->rflag==1)
        {
            p=p->right;
            if(p == head)
            {
                return;
            }
        }
        p=p->right;
    }
}

int main()
{
    BST b;
    int ch,data;

    do
    {
       cout<<"\n 1.Insert";
       cout<<"\n 2.Inorder";
       cout<<"\n 3.Preorder";
       cout<<"\n Enter Choice : ";
       cin>>ch;

       switch (ch)
       {
       case 1: cout<<"\n Enter data : ";
                cin>>data;
                b.insert(data);
           break;

        case 2: cout<<"\n Inorder is :\n";
                b.inorder();
                break;

        case 3: cout<<"\n Preorder is :\n";
                b.preorder();
                break;
       
       default:
           break;
       }
    } while (ch!=0);
    
    return 0;
}