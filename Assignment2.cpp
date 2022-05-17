#include <bits/stdc++.h>
using namespace std;

class Node
{
    Node *left;
    Node *right;
    string value;
    string meaning;

public:
    Node(string value = "", string meaning = "") : value(value), meaning(meaning)
    {
        left = nullptr;
        right = nullptr;
    }
    friend class BST;
};

class BST
{

public:
    Node *root;
    bool isFound;
    int comparison = 0;
    BST()
    {
        root = nullptr;
    }

    Node *Insert(Node *p, string value, string meaning)
    {
        if (p == nullptr)
        {
            return new Node(value, meaning);
        }
        else if (p->value.compare(value) < 0)
        {
            p->right = Insert(p->right, value, meaning);
        }
        else if (p->value.compare(value) > 0)
        {
            p->left = Insert(p->left, value, meaning);
        }

        return p;
    }

    void create()
    {
        string value;
        string meaning;
        // bool loop = true;
        while (true)
        {

            cout << "Enter Word to add n dictionary else enter -C-" << endl;
            cin >> value;
            if (value.compare("-C-") == 0)
            {
                cout << "Created Dictionary Successfully" << endl;
                // loop = false;
                break;
            }
            else
            {
                cout << "Enter Meaning of : ";
                cin.ignore();
                getline(cin, meaning);
                if (this->root == nullptr)
                {
                    this->root = Insert(root, value, meaning);
                }
                else
                {
                    Insert(root, value, meaning);
                }
            }
        }
    }

    

    void reverseOrder(Node *p)
    {

        if (p)
        {
            reverseOrder(p->right);
            cout << p->value << " : " << p->meaning << endl;
            reverseOrder(p->left);
        }
    }

    void display()
    {
        cout << "DISPLAYING TREE" << endl;
        inorder(root);
        cout << "\n";
    }
    void inorder(Node *p)
    {
        if (p)
        {
            inorder(p->left);
            cout << p->value << ": " << p->meaning << endl;
            inorder(p->right);
        }
    }

    void search(Node *p, string key)
    {
        if (p)
        {
            auto x = p->value.compare(key);
            comparison++;
            if (x == 0)
            {
                cout << "Key Found : " << p->value<< endl;
                cout << "Meaning : " << p->meaning <<endl;
                cout << "Number of Comparisons :" << comparison << endl;
                isFound = true;
                return;
            }
            else if (x < 0)
            {
                search(p->right, key);
            }
            else if (x > 0)
            {
                search(p->left, key);
            }
        }
    }

    void replace(Node *p,string key)
    {
        if(p)
        {
            auto x = p->value.compare(key);
            if(x == 0)
            {
                cout<<"Word Found : "<<p->value<<" Meaning : "<<p->meaning<<endl;
                cout<<"Enter new Meaning to the Word : "<<p->value<<endl;
                string newMeanig;
                cin.ignore();
                getline(cin,newMeanig);
                p->meaning = newMeanig;
                isFound = true;
                return;
            }
            else if(x<0)
            {
                replace(p->right,key);
            }
            else if(x>0)
            {
                replace(p->left,key);
            }
        }

    }

    void update()
    
    {
        cout<<"Enter Word to update meaning"<<endl;
        string updateWord;
        cin>>updateWord;
        isFound = false;
        replace(root,updateWord);
        if(!isFound)
        {
            cout<<"No Key found"<<endl;
        }


    }

    void find()
    {
        cout << "Enter Word to Search" << endl;
        string key;
        cin >> key;
        isFound = false;
        comparison = 0;
        search(root, key);
        if (isFound == false)
        {
            cout << "No key found" << endl;
            cout << "No of Comparisons " << comparison << endl;
        }
    }

    Node *Delete(Node *p, string key)
    {
        if(p == nullptr)
        {
            return p;
        }

        else if(key.compare(p->value) < 0)
        {
            p->left = Delete(p->left,key);
        }
        else if(key.compare(p->value)>0)
        {
           p->right = Delete(p->right,key);
        }  

        else
        {
            if(p->left == nullptr)
            {
                auto temp = p->right;
                delete p;
                return temp;
            }
            else if(p->right == nullptr)
            {
                auto temp = p->left;
                delete p;
                return temp;
            }

            else if(p->right != nullptr && p->left != nullptr)
            {
                auto temp = minLeftChildNotNuLL(p->right);
                p->value = temp->value;
                p->meaning = temp->meaning;
                p->right = Delete(p->right,p->value);
            }
        } 
        return p;
    }

    Node *minLeftChildNotNuLL(Node *p)
    {
        Node *curr = p;
        while(curr->left != nullptr)
        {
            curr = curr ->left;
        }
        return curr;
    }
    void Delete()
    {
        cout<<"Enter Word to be deleted"<<endl;
        string key;
        cin>>key;
        isFound =false;
        search(root,key);
        if(!isFound)
        {
            cout<<"No Word Found"<<endl;
            cout<<"Comparisons : "<<comparison<<endl;
        }
        else
        {
            Delete(root,key);
            cout<<"Deleted Word Successfully : "<<key<<endl;
        }

    }
};

int main()
{
    BST bt;
    bt.create();
    bool loop = true;
    int choice;
    while (loop)
    {
        cout << "1.Inorder Traversal 2.Display 3.Search 4.Ascending and Descending order 5.Update 6.Delete 7.Exit " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            bt.inorder(bt.root);
            break;
        case 2:
            bt.display();
            break;
        case 3:
            bt.find();
            break;
        case 4:
            bt.display();
            bt.reverseOrder(bt.root);
            break;
        case 5:
            bt.update();
            break;
        case 6:
            bt.Delete();
            break;
        case 7:
            cout<<"I Love PICT..."<<endl;
            loop = false;
            exit(0);
            break;

        default:
            cout << "Enter Valid Choice" << endl;
            break;
        }
    }
}