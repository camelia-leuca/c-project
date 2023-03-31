#pragma once
#include"Node.h"
#include<vector>
using namespace std;

template <class T>
class List {
private:
    Node<T>* head;
public:
    List()
    {
        head = nullptr;
    }

    // adds an elem to the linked list
    void add(T elem)
    {
        if (head==nullptr)
            head=new Node<T>(elem);
        else
        {
            Node<T>* p=head;
            while (p->next!=nullptr) 
                p=p->next;
            p->next=new Node<T>(elem);
        }
    }

    //removes an element from the linked list
    T remove(T elem)
    {
        Node<T>* node_to_delete = nullptr;
        T info_to_return;

        if (head != nullptr) // if the list is not empty
        { 
            if (head->info == elem)
            {
                node_to_delete = head;
                head = head->next; //head points to the next node
            }
            else
            {
                Node<T>* p = head->next;
                Node <T>* q = head;
                while (p != nullptr)
                    if (p->info == elem)
                    {
                        node_to_delete = p;
                        p = nullptr;
                    }
                    else
                    {
                        p = p->next;
                        q = q->next;
                    }
                if (node_to_delete != nullptr)
                    q->next = node_to_delete->next;
            }
        }
        if (node_to_delete != nullptr) // if the elem elem was found
        { 
            info_to_return = node_to_delete->info;
            delete node_to_delete;
            return info_to_return;
        }
        return T(); // elem does not exist in the list or the list is empty
    }

    //updates an element from the linked list
    void update(T elem, T updated_elem)
    {
        if (head != nullptr)// if the list is not empty
        {
            Node<T>* p = head;
            while (p != nullptr)
                if (p->info == elem)
                     p->info = updated_elem;
                else
                    p = p->next;
        }
    }

    //checks if a given element exists in the linked list
    bool exists(T elem)
    {
        if (head != nullptr)// if the list is not empty
        {
            Node<T>* p = head;
            while (p != nullptr)
                if (p->info == elem)
                    return true;
                else
                    p = p->next;
        }
        return false;
    }

    //returns all element from the linked list
    vector<T*> get_all()
    {
        vector<T*> elems;
        if (head == nullptr)
            return vector<T*>();
        else
        {
            Node<T>* p = head;
            while (p != nullptr)
            {
                T* pointer = &p->info;
                elems.push_back(pointer);
                p = p->next;
            }
            return elems;
        }
        return vector<T*>();
    }

    friend class User;
};
