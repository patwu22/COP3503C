#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node *prev = nullptr;
        Node *next = nullptr;
    };

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned int numLL = 0;

public:
    // Behaviors
    void PrintForward() const
    {
        Node *ptr = head;
        while (ptr != nullptr)
        {
            cout << ptr->data << endl;
            ptr = ptr->next;
        }
    }

    void PrintReverse() const
    {
        Node *ptr = tail;
        while (ptr != nullptr)
        {
            cout << ptr->data << endl;
            ptr = ptr->prev;
        }
    }

    void PrintForwardRecursive(const Node *node) const
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PrintForwardRecursive(node->next);
        }
    }

    void PrintReverseRecursive(const Node *node) const
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PrintReverseRecursive(node->prev);
        }
    }

    // Accessors
    unsigned int NodeCount() const
    {
        return numLL;
    }

    void FindAll(vector<Node *> &outData, const T &value) const
    {
        Node *ptr = head;
        while (ptr != nullptr)
        {
            if (ptr->data == value)
                outData.push_back(ptr);
            ptr = ptr->next;
        }
    }

    Node *Find(const T &data) const
    {
        Node *ptr = head;
        while (ptr != nullptr)
        {
            if (ptr->data == data)
                return ptr;
            ptr = ptr->next;
        }
        return nullptr;
    }

    Node *GetNode(unsigned int index) const
    {
        Node *ptr = head;
        if (index >= numLL)
            throw out_of_range("Index is out of range!");
        for (unsigned int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
        return ptr;
    }

    Node *Head() const
    {
        return head;
    }

    Node *Tail() const
    {
        return tail;
    }

    // Insertion
    void AddHead(const T &data)
    {
        Node *ptr = new Node;
        ptr->data = data;
        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;
        if (tail == nullptr)
            tail = ptr;
        head = ptr;
        numLL++;
    }

    void AddTail(const T &data)
    {
        Node *ptr = new Node;
        ptr->data = data;
        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;
        if (head == nullptr)
            head = ptr;
        tail = ptr;
        numLL++;
    }

    void AddNodesHead(const T *data, unsigned int count)
    {
        Node *ptr = nullptr;
        for (unsigned int i = count; i > 0; i--)
        {
            ptr = new Node;
            ptr->data = data[i - 1];
            ptr->next = head;
            if (head != nullptr)
                head->prev = ptr;
            if (tail == nullptr)
                tail = ptr;
            head = ptr;
            numLL++;
        }
    }

    void AddNodesTail(const T *data, unsigned int count)
    {
        Node *ptr = nullptr;
        for (unsigned int i = 0; i < count; i++)
        {
            ptr = new Node;
            ptr->data = data[i];
            ptr->prev = tail;
            if (tail != nullptr)
                tail->next = ptr;
            if (head == nullptr)
                head = ptr;
            tail = ptr;
            numLL++;
        }
    }

    void InsertAfter(Node *node, const T &data)
    {
        if (node->next == nullptr)
        {
            AddTail(data);
        }
        else
        {
            Node *ptr = new Node;
            ptr->data = data;
            ptr->prev = node;
            ptr->next = node->next;
            node->next = ptr;
            ptr->next->prev = ptr;
            numLL++;
        }
    }

    void InsertBefore(Node *node, const T &data)
    {
        if (node->prev == nullptr)
        {
            AddHead(data);
        }
        else
        {
            Node *ptr = new Node;
            ptr->data = data;
            ptr->next = node;
            ptr->prev = node->prev;
            node->prev = ptr;
            ptr->prev->next = ptr;
            numLL++;
        }
    }

    void InsertAt(const T &data, unsigned int index)
    {
        if (index == numLL)
        {
            AddTail(data);
        }
        else
        {
            InsertBefore(GetNode(index), data);
        }
    }

    // Removal
    bool RemoveHead()
    {
        if (head == nullptr)
            return false;
        if (head->next == nullptr)
        {
            Clear();
            return true;
        }
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        numLL--;
        return true;
    }

    bool RemoveTail()
    {
        if (tail == nullptr)
            return false;
        if (tail->prev == nullptr)
        {
            Clear();
            return true;
        }
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        numLL--;
        return true;
    }

    unsigned int Remove(const T &data)
    {
        unsigned int count = 0;
        Node *ptr = head;
        for (unsigned int i = 1; i <= numLL; i++)
        {
            if (ptr->data == data)
            {
                ptr = ptr->next;
                RemoveAt(i - 1);
                count++;
                i--;
            }
            else
            {
                ptr = ptr->next;
            }
        }
        return count;
    }

    bool RemoveAt(unsigned int index)
    {
        if (index == 0)
        {
            RemoveHead();
            return true;
        }
        if (index == numLL - 1)
        {
            RemoveTail();
            return true;
        }
        if (index >= numLL)
            return false;
        Node *ptr = GetNode(index);
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        numLL--;
        return true;
    }

    void Clear()
    {
        Node *ptr = nullptr;
        while (head != nullptr)
        {
            ptr = head->next;
            delete head;
            head = ptr;
        }
        numLL = 0;
        tail = nullptr;
    }

    // Operators
    T &operator[](unsigned int index)
    {
        return GetNode(index)->data;
    }

    bool operator==(const LinkedList<T> &rhs) const
    {
        if (numLL != rhs.numLL)
            return false;
        Node *ptr1 = head;
        Node *ptr2 = rhs.head;
        while (ptr1 != nullptr && ptr2 != nullptr)
        {
            if (ptr1->data != ptr2->data)
                return false;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return true;
    }

    LinkedList<T> &operator=(const LinkedList<T> &rhs)
    {
        Clear();
        numLL = rhs.numLL;
        Node *ptr = rhs.head;
        while (ptr != nullptr)
        {
            AddTail(ptr->data);
            ptr = ptr->next;
        }
        return *this;
    }

    // Construction
    LinkedList() {}

    LinkedList(const LinkedList<T> &list)
    {
        Clear();
        numLL = list.numLL;
        Node *ptr = list.head;
        while (ptr != nullptr)
        {
            AddTail(ptr->data);
            ptr = ptr->next;
        }
    }

    ~LinkedList()
    {
        Clear();
    }
};
