#include <iostream>
#define size 500
using namespace std;

class Node
{
    string key;
    string value;
    Node *next;

public:
    Node(string key = "", string value = "") : key(key), value(value), next(nullptr) {}
    friend class LinkedList;
};

class LinkedList
{
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void Insert(string key, string value)
    {
        Node *newNode = new Node(key, value);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = tail->next;
        }
    }
    void Display()
    {
        Node *ptr = head;
        while (ptr != nullptr)
        {
            cout << ptr->key << "\t" << ptr->value << "\n";
            ptr = ptr->next;
        }
    }
    void Delete(string key)
    {
        Node *ptr = head;
        if (ptr->key == key)
        {
            if (head == tail)
            {
                head = tail = nullptr;
                delete ptr;
                return;
            }
            head = head->next;
            delete ptr;
            return;
        }
        Node *follow = ptr;
        while (ptr->key != key || ptr == nullptr)
        {
            follow = ptr;
            ptr = ptr->next;
        }
        follow->next = ptr->next;
        if (ptr == tail)
        {
            tail = follow;
        }
        delete ptr;
        return;
    }
    void Update(string key, string value)
    {
        Node *ptr = head;
        while (ptr->key != key)
        {
            ptr = ptr->next;
        }
        ptr->value = value;
    }
    bool Search(string key)
    {
        Node *ptr = head;
        int comparisions = 1;
        if (head == nullptr)
        {
            cout << "Not Found!" << endl;
            return false;
        }
        while (ptr != nullptr && ptr->key != key)
        {
            ptr = ptr->next;
            comparisions++;
        }
        if (ptr == nullptr)
        {
            cout << "Not Found"
                 << " No of comparisions: " << comparisions << endl;
            return false;
        }
        else
        {
            cout << "Found"
                 << " No of comparisions: " << comparisions << endl;

            cout << ptr->key << "\t" << ptr->value << endl;
            return true;
        }
    }
    bool empty()
    {
        return head == nullptr ? true : false;
    }
};

class HashTable
{
    LinkedList hashEntry[size];
    int elements;

public:
    HashTable() : elements(0){};
    int hashFunction(string key)
    {
        int hashValue = 0;
        for (auto i : key)
        {
            hashValue += int(i);
        }
        cout << "Hash Value for " << key << " is " << hashValue << endl;
        return hashValue % size;
    }

    void Insert(string key, string value)
    {
        int hashValue = hashFunction(key);
        if (hashEntry[hashValue].Search(key))
        {
            cout << "Key already present! " << endl;
        }
        else
        {
            hashEntry[hashValue].Insert(key, value);
            cout << "Element Added Successfully!" << endl;
        }
    }

    void Display()
    {
        for (size_t i = 0; i < size; i++)
        {
            if (!hashEntry[i].empty())
            {
                cout << "HashValue = " << i << endl;
                hashEntry[i].Display();
                cout << endl;
            }
        }
    }

    void Delete(string key)
    {
        int hashValue = hashFunction(key);
        if (hashEntry[hashValue].Search(key))
        {
            hashEntry[hashValue].Delete(key);
            cout << "Delete Successful!" << endl;
        }
    }

    void Search(string key)
    {
        int hashValue = hashFunction(key);
        hashEntry[hashValue].Search(key);
        cout << endl;
    }
};

int main()
{
    HashTable t1;
    bool continueProgram = true;
    while (continueProgram)
    {
        cout << "Menu" << endl;
        cout << "1. Add Hash entry" << endl;
        cout << "2. Search Key" << endl;
        cout << "3. Display" << endl;
        cout << "4. Delete" << endl;
        cout << "-1 End" << endl;
        cout << "Choose operations u want to perform? ";
        int choice = 0;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter key: ";
            string key = "";
            cin.clear();
            cin.ignore();
            getline(cin, key);
            cout << "Enter value: ";
            string value = "";
            getline(cin, value);
            t1.Insert(key, value);
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Enter key: ";
            string key = "";
            cin.clear();
            cin.ignore();
            getline(cin, key);
            t1.Search(key);
            break;
        }
        case 3:
        {
            t1.Display();
            break;
        }
        case 4:
        {
            cout << "Enter key: ";
            string key = "";
            cin.clear();
            cin.ignore();
            getline(cin, key);
            t1.Delete(key);
            break;
        }
        case -1:
        {
            continueProgram = false;
            break;
        }
        default:
        {
            cout << "INVALID CHOICE" << endl;
            break;
        }
            cout << endl;
        }
    }
    return 0;
}