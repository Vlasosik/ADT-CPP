#ifndef LIST_H
#define LIST_H
#include <iostream>

/*
* Implementation of the Abstract Data Type (ADT) "Forward List" (singly linked list).
*
* The ForwardList class provides basic operations for working with a singly linked list:
*
* Methods:
*  - void PushFront(const T &value): Adds an element to the front of the list.
*  - void PushBack(const T &value): Adds an element to the end of the list.
*  - void PopFront(): Removes the first element from the list.
*  - void PopBack(): Removes the last element from the list.
*  - void Erase(const T &value): Removes the first element from the list that equals the specified value.
*  - void Clear(): Clears the list (removes all elements).
*  - bool Find(const T &value): Returns true if the list contains an element with the specified value.
*  - [[nodiscard]] int Size() const: Returns the number of elements in the list.
*  - bool IsEmpty(): Returns true if the list is empty.
*
* Features:
* - The singly linked list supports only forward access, so some operations (e.g., PopBack) may be less efficient.
*
* @author Vlas Pototskyi
*/


template<typename T>
class ForwardList {
    struct Node {
        Node *next;
        T element;

        explicit Node(const T &elem, Node *nextNode = nullptr) : next(nextNode), element(elem) {
        }
    };

    Node *head;
    Node *tail;
    int size;

    void Copy(const ForwardList &other);

    /*
    * Iterator class for the ForwardList.
    *
    * This inner class provides an iterator for the ForwardList, allowing
    * traversal of the elements in the list.
    *
    * Methods:
    *  - explicit Iterator(Node *node): Constructs an iterator pointing to the specified node.
    *  - bool operator!=(const Iterator &other) const: Compares two iterators for inequality.
    *  - Iterator &operator++(): Advances the iterator to the next node and returns the updated iterator.
    *  - Iterator operator++(int): Advances the iterator to the next node and returns the original iterator (post-increment).
    *  - T operator*(): Dereferences the iterator to access the value of the current node.
    */
public:
    class Iterator {
        Node *node;

    public:
        explicit Iterator(Node *node);

        bool operator!=(const Iterator &other) const;

        Iterator &operator++();

        Iterator operator++(int);

        T &operator*();

        T *operator->();
    };

    // --- Constructors ---
    ForwardList();

    ForwardList(const ForwardList &other);

    ForwardList(ForwardList &&other) noexcept;

    // --- Destructors ---
    ~ForwardList();

    // --- Overload operators ---
    ForwardList &operator=(const ForwardList &other);

    ForwardList &operator=(ForwardList &&other) noexcept;

    // --- Insert methods ---
    void PushFront(const T &value);

    void PushBack(const T &value);

    // --- Remove methods ---
    void PopFront();

    void PopBack();

    void Erase(const T &value);

    void Clear();

    // --- Find methods ---
    bool Find(const T &value);

    // --- Check size methods ---
    [[nodiscard]] int Size() const;

    // --- Iterators methods ---
    Iterator Begin();

    Iterator End();

    bool IsEmpty();
};

template<typename T>
void ForwardList<T>::Copy(const ForwardList &other) {
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }
    head = new Node{other.head->element, nullptr};
    Node *current = head;
    Node *otherCurrent = other.head;
    while (otherCurrent->next != nullptr) {
        current->next = new Node{otherCurrent->next->element, nullptr};
        current = current->next;
        otherCurrent = otherCurrent->next;
    }
}


template<typename T>
ForwardList<T>::Iterator::Iterator(Node *node) : node(node) {
}

template<typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator &other) const {
    return node != other.node;
}

template<typename T>
typename ForwardList<T>::Iterator &ForwardList<T>::Iterator::operator++() {
    node = node->next;
    return *this;
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::Iterator::operator++(int) {
    Node *temp(*this);
    node = node->next;
    return *temp;
}

template<typename T>
T &ForwardList<T>::Iterator::operator*() {
    return node->element;
}

template<typename T>
T *ForwardList<T>::Iterator::operator->() {
    return &node->element;
}

template<typename T>
ForwardList<T>::ForwardList() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList &other) : head(nullptr), size(other.size) {
    Clear();
    Copy(other);
}

template<typename T>
ForwardList<T>::ForwardList(ForwardList &&other) noexcept : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T>
ForwardList<T>::~ForwardList() {
    Clear();
}

template<typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
    return *this;
}

template<typename T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList &&other) noexcept {
    if (this != &other) {
        Clear();
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

template<typename T>
void ForwardList<T>::PushFront(const T &value) {
    if (head == nullptr) {
        head = new Node{value, nullptr};
    } else {
        Node *newNode = new Node{value, head};
        head = newNode;
    }
    size++;
}

template<typename T>
void ForwardList<T>::PushBack(const T &value) {
    Node *newNode = new Node(value, nullptr);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void ForwardList<T>::PopFront() {
    if (head == nullptr) {
        return;
    }
    const Node *current = head;
    head = head->next;
    delete current;

    size--;
}

template<typename T>
void ForwardList<T>::PopBack() {
    if (head == nullptr) {
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node *current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        tail = current;
    }
    size--;
}

template<typename T>
void ForwardList<T>::Erase(const T &value) {
    Node *previous = nullptr;
    Node *current = head;
    while (current != nullptr) {
        if (current->element == value) {
            if (previous == nullptr) {
                head = head->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
            } else {
                previous->next = current->next;
                if (current == tail) {
                    tail = previous;
                }
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template<typename T>
void ForwardList<T>::Clear() {
    if (head == nullptr) {
        return;
    }
    while (head != nullptr) {
        const Node *current = head;
        head = head->next;
        delete current;
    }
    size = 0;
}

template<typename T>
bool ForwardList<T>::Find(const T &value) {
    Node *current = head;
    while (current != nullptr) {
        if (current->element == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
int ForwardList<T>::Size() const {
    return size;
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::Begin() {
    Iterator iterator(head);
    return iterator;
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::End() {
    Iterator iterator(tail);
    return iterator;
}

template<typename T>
bool ForwardList<T>::IsEmpty() {
    return head == nullptr;
}
#endif
