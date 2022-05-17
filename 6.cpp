#include <iostream>
using namespace std;

struct Node
{
    string landmark = "";
    Node *next = NULL;
    Node *below = NULL;
    Node *original = NULL;
    bool isVisited = false;
};

class Stack
{
    int top = -1;
    int size;

public:
    Node **stack;
    Stack(int size)
    {
        stack = new Node *[size];
        this->size = size;
    }
    Node *getTop()
    {
        return stack[top];
    }
    void push(Node *element)
    {
        stack[++top] = element;
    }
    Node *pop()
    {
        return stack[top--];
    }
    bool isEmpty()
    {
        return top == -1;
    }
};

class Queue
{
    int rear = -1, front = -1;
    int size;
    Node **queue;

public:
    Queue(int size)
    {
        queue = new Node *[size];
        this->size = size;
    }

    void enQueue(Node *ele)
    {
        rear += 1;
        if (front == -1)
        {
            front += 1;
        }
        queue[rear] = ele;
    }

    Node *deQueue()
    {
        Node *temp = queue[front];
        // delete queue[front];
        ++front;
        if (front > rear)
        {
            front = -1;
            rear = -1;
        }
        return temp;
    }

    bool isEmpty()
    {
        if (front > rear || front == -1 || rear == -1)
        {
            return true;
        }
        return false;
    }

    void printQueue();
};

void Queue::printQueue()
{
    cout << "\n=============================================\n";
    for (int i = front; i <= rear; i++)
    {
        Node *temp = queue[i];
        cout << "\t" << temp->landmark;
    }
    cout << "\n=============================================\n";
}
class Graph
{
    Node *adjacencyList = NULL;
    int size;
    Stack *s;
    Queue *q;

public:
    Graph(int size)
    {
        this->size = size;
        adjacencyList = new Node[size];
        s = new Stack(size);
        q = new Queue(size);
    }
    void makeAllUnVisited(Node *current)
    {
        while (current != NULL)
        {
            current->isVisited = false;
            current = current->below;
        }
    }

    void exploreAdjacents(Node *current)
    {
        while (current->next != NULL)
        {
            current = current->next;
            if (!current->original->isVisited)
            {
                current = current->original;
                cout << "\t" << current->landmark;
                s->push(current);
                current->isVisited = true;
                return;
            }
        }
    }

    void bfs()
    {
        Node *current = adjacencyList;
        q->enQueue(current);
        current->isVisited = true;

        cout << "\n=============================================\n";

        while (!q->isEmpty())
        {
            Node *popped = q->deQueue();
            cout << "\t" << popped->landmark;

            popped = popped->next;
            while (popped != NULL)
            {
                if (!popped->original->isVisited)
                {
                    q->enQueue(popped->original);
                    popped->original->isVisited = true;
                }
                popped = popped->next;
            }
        }
    }

    void dfs()
    {
        Node *current = adjacencyList;
        bool isDone = false;
        while (!isDone)
        {
            if (current->next == NULL)
            {
                isDone = true;
            }
            if (!current->isVisited)
            {
                s->push(current);
                cout << "\t" << current->landmark;
                current->isVisited = true;
            }
            bool isUpdated = false;
            while (current->next != NULL)
            {
                if (current->next->original->isVisited)
                {
                    current = current->next;
                    continue;
                }
                current = current->next->original;
                isUpdated = true;
                break;
            }
            if (!isUpdated)
            {
                isDone = true;
            }
        }
        cout << "\n==========DFS==========\n";
        while (!s->isEmpty())
        {
            Node *current = s->getTop();
            exploreAdjacents(current);
            current = s->pop();
            //            cout<<"\t"<<current->landmark;
        }
        makeAllUnVisited(adjacencyList);
    }

    void insertNode()
    {
        cout << "\nEnter Landmark: ";
        string landmark;
        cin >> landmark;
        Node *current = adjacencyList;
        Node *newLandmark = new Node;
        newLandmark->landmark = landmark;
        newLandmark->below = NULL;
        if (adjacencyList->landmark == "")
        {
            adjacencyList = newLandmark;
            // cout<<"\nFOUND NULL";
            return;
        }
        while (current->below != NULL)
        {
            current = current->below;
        }
        current->below = newLandmark;
    }
    void createEdge()
    {
        string landmark1, landmark2;
        cout << "\nEnter Landmark 1: ";
        cin >> landmark1;
        cout << "\nEnter Landkark 2:";
        cin >> landmark2;
        Node *l1Transport = adjacencyList, *l2Transport = adjacencyList;
        // cout<<"\n==========="<<adjacencyList->landmark;
        if (l1Transport->landmark != landmark1)
        {
            while (l1Transport->below != NULL)
            {
                l1Transport = l1Transport->below;
                if (l1Transport->landmark == landmark1)
                {
                    break;
                }
            }
        }
        if (l2Transport->landmark != landmark2)
        {
            while (l2Transport->below != NULL)
            {
                l2Transport = l2Transport->below;
                if (l2Transport->landmark == landmark2)
                {
                    break;
                }
            }
        }
        if (l1Transport->landmark != landmark1)
        {
            cout << "\n"
                 << landmark1 << " does not exist.";
            return;
        }
        if (l2Transport->landmark != landmark2)
        {
            cout << "\n"
                 << landmark2 << " does not exist.";
            return;
        }
        Node *temp1 = l1Transport, *temp2 = l2Transport;
        while (l1Transport->next != NULL)
        {
            if (l1Transport->landmark == landmark2)
            {
                break;
            }
            l1Transport = l1Transport->next;
        }
        while (l2Transport->next != NULL)
        {
            if (l2Transport->landmark == landmark1)
            {
                break;
            }
            l2Transport = l2Transport->next;
        }

        if (l1Transport->landmark == landmark2 and l2Transport->landmark == landmark1)
        {
            cout << "\n Edge Already exists";
            return;
        }
        Node *l1Link = new Node, *l2Link = new Node;
        l1Link->landmark = landmark2;
        l1Link->original = temp2;
        l2Link->landmark = landmark1;
        l2Link->original = temp1;

        l1Transport->next = l1Link;
        l2Transport->next = l2Link;
    }

    void printGraph()
    {
        cout << "\n----------------------------------------------\n";
        Node *current = adjacencyList;
        while (current != NULL)
        {
            Node *horizontalTransport = current;
            while (horizontalTransport != NULL)
            {
                cout << "| " << horizontalTransport->landmark << " |->";
                if (horizontalTransport->original)
                {
                    cout << "(" << horizontalTransport->original->landmark << ")";
                }
                horizontalTransport = horizontalTransport->next;
            }
            current = current->below;
            cout << "NULL\n";
        }
    }

    void printMenu()
    {
        cout << "\n=============================================";
        cout << "\n1. DFS";
        cout << "\n2. BFS";
        cout << "\n3. Print Graph (in adjacency list)";
        cout << "\n4. Insert Node";
        cout << "\n5. Create Edge";
        cout << "\n6. Exit";
        cout << "\n==============================================";
    }

    void exec()
    {
        for (int i = 0; i < size; i++)
        {
            insertNode();
        }
        char ch = 'y';
        cout << "\n------------Enter Edges------------";
        while (ch == 'y')
        {
            createEdge();
            cout << "\nDo you wanna continue? (y/n): ";
            cin >> ch;
        }

        bool isExit = false;
        while (!isExit)
        {
            printMenu();
            cout << "\nEnter your choice: ";
            int ch;
            cin >> ch;
            switch (ch)
            {
            case 1:
                dfs();
                break;
            case 2:
                bfs();
                break;
            case 3:
                printGraph();
                break;
            case 4:
                insertNode();
                break;
            case 5:
                createEdge();
                break;
            case 6:
                isExit = true;
                break;
            default:
                cout << "\nInvalid Choice!!!";
            }
        }
    }
};
int main()
{
    cout << "\nEnter Initial number of nodes: ";
    int size;
    cin >> size;
    Graph g(size);
    g.exec();
    return 0;
}