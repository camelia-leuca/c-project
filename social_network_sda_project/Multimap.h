#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class Key, class Value>
class Multimap
{
private:
    template <class K, class V>
    class Map_node
    {
    public:
        K key;
        V value;
        Map_node<K, V>* next;

        //creates a node for the multimap
        Map_node(K key, V value) : key(key), value(value)
        {
            this->next = nullptr; 
        }
    };

    template<class V>
    class List_node
    {
    public:
        V info;
        List_node<V>* next;

        //creates a node for a list
        List_node(V info, List_node<V>* next) : info(info), next(next) {}

        //creates a node for a list
        List_node(V info) : info(info)
        {
            next = nullptr;
        }
    };

    //searches the multimap for a given key
    Map_node<Key, List_node<Value>*>* search_adress(Key k)
    {
        if (this->size == 0) 
            return nullptr;

        Map_node<Key, List_node<Value>*>* p = first;
        while (p->next != nullptr)
        {
            if (p->key == k) 
                return p;
            p = p->next;
        }
        return p;
    }

    int size;
    Map_node<Key, List_node<Value>*>* first;

public:
    //creates a multimap
    Multimap()
    {
        this->first = nullptr;
        this->size = 0;
    }

    //adds a key and a value to the multimap
    void put(Key key, Value value)
    {
        Map_node<Key, List_node<Value>*>* poz = search_adress(key);

        if (poz == nullptr) 
        {
            this->first = new Map_node<Key, List_node<Value>*>(key, new List_node<Value>(value));
            this->size++;
        }
        else
        {
            if (poz->key == key)
            {
                List_node<Value>* node = new List_node<Value>(value, poz->value);
                poz->value = node;
            }
            else
            {
                poz->next = new Map_node<Key, List_node<Value>*>(key, new List_node<Value>(value));
                this->size++;
            }
        }
    }

    // removes a given key and its list of values from the multimap
    vector<Value> remove(Key key)
    {
        Map_node<Key, List_node<Value>*>* poz = search_adress(key);
        vector<Value> result;

        if (poz != nullptr && poz->key == key)
        {
            Map_node<Key, List_node<Value>*>* p = first;
            if (poz == first)
                this->first = poz->next;
            else
            {
                while (p->next != poz)
                    p = p->next;
                p->next = poz->next;
            };

            while (poz->value != nullptr)
            {
                List_node<Value>* node = poz->value;
                result.push_back(node->info);
                poz->value = node->next;
                delete node;
            }
            this->size--;
            delete poz;
        }
        return result;
    }

    //removes a value of a given key from the multimap
    Value remove(Key key, Value value)
    {
        Map_node<Key, List_node<Value>*>* poz = search_adress(key);

        if (poz != nullptr && poz->key == key && poz->value != nullptr)
        { 
            List_node<Value>* p = poz->value;
            List_node <Value>* q = nullptr;
            while (p != nullptr)
                if (p->info == value)
                {
                    if (q)
                        q->next = p->next;
                    else
                        poz->value = p->next;
                    p = nullptr;
                }
                else
                {
                    q = p;
                    p = p->next;
                }
            delete p;
        }
        return value;
    }

    //checks if a given key exists in the multimap
    bool exists(Key key)
    {
        if (this->size == 0)
            return false;

        Map_node<Key, List_node<Value>*>* p = first;
        while (p != nullptr)
        {
            if (p->key == key)
                return true;
            p = p->next;
        }
        return false;
    }

    //checks if a value of a given key exists in the multimap
    bool exists(Key key, Value value)
    {
        if (this->size == 0)
            return false;

        Map_node<Key, List_node<Value>*>* p = first;
        while (p != nullptr)
        {
            if (p->key == key)
            {
                List_node<Value>* node = p->value;
                while (node != nullptr)
                {
                    if (node->info == value)
                        return true;
                    node = node->next;
                }
            }
            p = p->next;
        }
        return false;
    }

    //reutrns all values from the multimap
    vector<Value> get_all(int repeat = 0)
    {
        if (this->size == 0)
            return vector<Value>();
        else
        {
            vector<Value> values;
            Map_node<Key, List_node<Value>*>* p = first;
            while (p != nullptr)
            {
                List_node<Value>* node;
                node = p->value;
                    while (node != nullptr)
                    {
                        if(repeat)
                            values.push_back(node->info);
                        else
                        {
                            typename vector<Value>::iterator it = find(values.begin(), values.end(), node->info);
                            if (it == values.end())
                                values.push_back(node->info);
                        }
                        node = node->next;
                    }
                p = p->next;
            }
            return values;
        }
        return vector<Value>();
    }
};