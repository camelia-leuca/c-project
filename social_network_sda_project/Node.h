template <typename T>
class List;

template <class T>
class Node {
private:
    T info;
    Node<T>* next;
public:
    //creates a node for a linked list
    Node(T info, Node<T>* next) : info(info), next(next) {}

    //creates a node for a linked list
    Node(T info) : info(info)
    {
        next = nullptr;
    }

    friend class List<T>;
};
