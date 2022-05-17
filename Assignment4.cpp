#include <iostream>
using namespace std;
#define size 500

class HashEntry
{
    long int telephoneNo;
    string name;

public:
    explicit HashEntry(long int telephoneNo = 0, string name = "") : telephoneNo(telephoneNo), name(name)
    {
    }
    friend class HashTable;
};

class HashTable
{
    HashEntry hashArray[size];
    int elements;
    int hashFunction(long int key)
    {
        return key % size;
    }

public:
    HashTable()
    {
        elements = 0;
    }
    void Insert(long int key, string value)
    {
        if (elements == size)
        {
            cout << "Hash Table FULL" << endl;
            return;
        }
        int hashIndex = hashFunction(key);
        int hashIndexCopy = hashIndex;
        do
        {
            if (hashArray[hashIndex].telephoneNo == 0)
            {
                hashArray[hashIndex].telephoneNo = key;
                hashArray[hashIndex].name = value;
                elements++;
                break;
            }

            hashIndex = (hashIndex + 1) % size;

        } while (hashIndex != hashIndexCopy);
    }

    void InsertWithReplacement(long int key, string value)
    {
        if (elements == size)
        {
            cout << "Hash Table FULL" << endl;
            return;
        }
        int hashIndex = hashFunction(key);
        int hashIndexCopy = hashIndex;

        do
        {
            if (hashArray[hashIndex].telephoneNo == 0)
            {
                hashArray[hashIndex].telephoneNo = key;
                hashArray[hashIndex].name = value;
                elements++;
                break;
            }
            else
            {
                int hashIndexOfCollision = hashFunction(
                    hashArray[hashIndex].telephoneNo);
                if (hashIndex != hashIndexOfCollision && hashIndex == hashIndexCopy)
                {
                    long int keyCollision = hashArray[hashIndex].telephoneNo;
                    string valueCollsion = hashArray[hashIndex].name;

                    hashArray[hashIndex].telephoneNo = key;
                    hashArray[hashIndex].name = value;

                    InsertWithReplacement(keyCollision, valueCollsion);

                    break;
                }
                else
                {
                    hashIndex = (hashIndex + 1) % size;
                }
            }
        } while (hashIndex != hashIndexCopy);
    }

    void Display()
    {
        for (int i = 0; i < size; i++)
        {
            if (hashArray[i].telephoneNo != 0)
            {
                cout << i << "\t" << hashArray[i].telephoneNo << "\t"
                     << hashArray[i].name << endl;
            }
        }
    }
    void Search(long int key)
    {
        int count = 0;
        int hashIndex = hashFunction(key);
        int hashIndexCopy = hashIndex;
        do
        {
            if (hashArray[hashIndex].telephoneNo == key)
            {
                cout << "Found" << endl;
                cout << hashIndex << " " << hashArray[hashIndex].name << " "
                     << hashArray[hashIndex].telephoneNo << " Collisions: "
                     << count << endl;
                return;
            }
            hashIndex = (hashIndex + 1) % size;
            count++;

        } while (hashIndex != hashIndexCopy);

        cout << "Key NOT FOUND!" << endl;
    }
    void Update(long int key)
    {
        int hashIndex = hashFunction(key);
        int hashIndexCopy = hashIndex;
        do
        {
            if (hashArray[hashIndex].telephoneNo == key)
            {
                cout << "Found" << endl;
                cout << hashIndex << " " << hashArray[hashIndex].name << " "
                     << hashArray[hashIndex].telephoneNo << endl;
                cout << "Enter Name to be Updated: ";
                string nameUpdate;
                getline(cin, nameUpdate);
                hashArray[hashIndex].name = nameUpdate;
                cout << "Entry Updated" << endl;
                cout << hashIndex << " " << hashArray[hashIndex].telephoneNo
                     << " " << hashArray[hashIndex].name << endl;
                return;
            }
            hashIndex = (hashIndex + 1) % size;

        } while (hashIndex != hashIndexCopy);

        cout << "Key NOT FOUND!" << endl;
    }
};

int main()
{
    HashTable withReplacement;
    HashTable withoutReplacement;
    bool continueProgram = true;
    while (continueProgram)
    {
        cout << "Menu" << endl;
        cout << "1. Add Hash entry" << endl;
        cout << "2. Search Key" << endl;
        cout << "3. Update Value" << endl;
        cout << "4. Display" << endl;
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
            long int key;
            cin >> key;
            cout << "Enter value: ";
            string value = "";
            cin.ignore();
            cin.clear();
            getline(cin, value);
            withReplacement.InsertWithReplacement(key, value);
            withoutReplacement.Insert(key, value);
            cout << endl;
            break;
        }
            //		case 2: {
            //			cout << "Enter key: ";
            //			long int key;
            //			cin >> key;
            //			cout << "Enter value: ";
            //			string value = "";
            //			cin.ignore();
            //			cin.clear();
            //			getline(cin, value);
            //			withReplacement.InsertWithReplacement(key, value);
            //			cout << endl;
            //			break;
            //		}
        case 2:
        {
            cout << "Enter key: ";
            long int key;
            cin >> key;
            cout << "With Replacement Search " << endl;
            withReplacement.Search(key);
            cout << "Without Replacement Search" << endl;
            withoutReplacement.Search(key);
            break;
        }
        case 3:
        {
            cout << "Enter key: ";
            long int key;
            cin >> key;
            withReplacement.Update(key);
            withoutReplacement.Update(key);
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Without Replacement Table\n";
            cout << "Index\tKey\tValue\n";
            withoutReplacement.Display();
            cout << endl;
            cout << "With Replacement Table\n";
            cout << "Index\tKey\tValue\n";
            withReplacement.Display();
            cout << endl;
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