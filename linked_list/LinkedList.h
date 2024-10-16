#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/**
* Implementation of the Abstract Data Type (ADT) "Doubly Linked List".
*
* The LinkedList class provides basic operations for working with a doubly linked list:
*
* Methods:
*  - void PushFront(const T &value): Adds an element to the front of the list.
*  - void PushBack(const T &value): Adds an element to the end of the list.
*  - void Insert(int index, const T &value): Inserts an element at the specified index.
*  - void PopFront(): Removes the first element from the list.
*  - void PopBack(): Removes the last element from the list.
*  - void Remove(const T &value): Removes the first element that equals the specified value from the list.
*  - void Clear(): Clears the list (removes all elements).
*  - [[nodiscard]] int Size() const: Returns the number of elements in the list.
*  - bool IsEmpty(): Returns true if the list is empty.
*  - bool IsFind(const T &value): Returns true if the list contains an element with the specified value.
*  - T &Front(): Returns a reference to the first element in the list.
*  - T &Back(): Returns a reference to the last element in the list.
*  - Iterator Begin(): Returns an iterator to the first element in the list.
*  - Iterator End(): Returns an iterator to the last element in the list.
*
* Time complexity (Doubly Linked List):
*  - PushFront: O(1) - Directly modifies head pointer, no need to traverse the list.
*  - PushBack: O(1) - Directly modifies tail pointer, unlike singly linked list which needs traversal.
*  - Insert: O(n) - Needs to traverse to the specific index.
*  - PopFront: O(1) - Removes the first element by directly updating head pointer.
*  - PopBack: O(1) - Removes the last element by directly updating tail pointer.
*  - Remove: O(n) - Must search the list to find and remove the element.
*  - Clear: O(n) - Must traverse the entire list and delete each element.
*  - Size: O(1) - If size is stored as a member variable; otherwise O(n) if it needs to be calculated.
*  - IsEmpty: O(1) - Checks if the head is null.
*  - IsFind: O(n) - Needs to search the list to find the element.
*  - Front: O(1) - Returns the first element (head).
*  - Back: O(1) - Returns the last element (tail).
*
* Features:
* - The doubly linked list supports both forward and backward traversal, allowing efficient removal and insertion at both ends.
* - The list automatically manages memory allocation and deallocation, ensuring no memory leaks.
* - The list supports copy and move semantics (copy constructor, move constructor, copy assignment, move assignment).
*
* @author Vlas Pototskyi
*/
template<typename T>
class LinkedList {
    struct Node {
        T element;
        Node *previous;
        Node *next;

        explicit Node(const T &element, Node *previous = nullptr, Node *next = nullptr): element(element),
            previous(previous),
            next(next) {
        }
    };

    Node *head;
    Node *tail;
    T size;

    void Copy(const LinkedList &other);

    void Move(LinkedList &other);

    void PopHead();

    void PopTail();

    /*
    * Iterator class:
    * - Iterator: Allows forward and backward traversal through the list. Provides overloaded operators for incrementing (++), decrementing (--),
    *   dereferencing (*), and accessing members (->).
    *   - bool operator!=(const Iterator &other) const: Checks if two iterators point to different nodes.
    *   - Iterator &operator++(): Advances the iterator to the next element in the list.
    *   - Iterator operator++(int): Advances the iterator and returns a copy of the previous iterator.
    *   - Iterator &operator--(): Moves the iterator to the previous element in the list.
    *   - Iterator operator--(int): Moves the iterator to the previous element and returns a copy of the previous iterator.
    *   - T &operator*(): Dereferences the iterator to access the value stored in the current node.
    *   - T *operator->(): Provides access to the members of the stored object.
    *
    */
public:
    class Iterator {
        Node *node;

    public:
        explicit Iterator(Node *node);

        bool operator!=(const Iterator &other) const;

        bool operator==(const Iterator &other) const;

        Iterator &operator++();

        Iterator operator++(int);

        Iterator &operator--();

        Iterator operator--(int);

        T &operator*();

        T *operator->();
    };

    // --- Constructors ---
    LinkedList();

    LinkedList(const LinkedList &other);

    LinkedList(LinkedList &&other) noexcept;

    // --- Overload operators ---
    LinkedList &operator=(const LinkedList &other);

    LinkedList &operator=(LinkedList &&other) noexcept;

    // --- Insert methods ---
    void PushFront(const T &value);

    void PushBack(const T &value);

    void Insert(int index, const T &value);

    // --- Remove methods ---
    void PopFront();

    void PopBack();

    void Remove(const T &value);

    void Clear();

    // --- Check size methods ---
    [[nodiscard]] int Size() const;

    bool IsEmpty();

    // --- Find Methods ---
    bool IsFind(const T &value);

    T &Front();

    T &Back();

    Iterator Begin();

    Iterator End();


    // --- Destructor ---
    ~LinkedList();
};

template<typename T>
void LinkedList<T>::Copy(const LinkedList &other) {
    if (other.head == nullptr) {
        head = tail = nullptr;
        return;
    }
    head = new Node{other.head->element, nullptr, nullptr};
    Node *current = head;
    Node *otherCurrent = head->next;
    while (otherCurrent != nullptr) {
        current->next = new Node{otherCurrent->next->element, nullptr, nullptr};
        current = current->next;
        otherCurrent = otherCurrent->next;
    }
}

template<typename T>
void LinkedList<T>::Move(LinkedList &other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
void LinkedList<T>::Clear() {
    if (head == nullptr) {
        return;
    }
    while (head != nullptr) {
        const Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
void LinkedList<T>::PopHead() {
    const Node *temp = head;
    head = head->next;
    head->previous = nullptr;
    delete temp;
}

template<typename T>
void LinkedList<T>::PopTail() {
    const Node *current = tail;
    tail = tail->previous;
    tail->next = nullptr;
    delete current;
}

template<typename T>
LinkedList<T>::Iterator::Iterator(Node *node) : node(node) {
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator &other) const {
    return node != other.node;
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator &other) const {
    return node == other.node;
}

template<typename T>
int LinkedList<T>::Size() const {
    return size;
}

template<typename T>
bool LinkedList<T>::IsEmpty() {
    return head == nullptr;
}

template<typename T>
bool LinkedList<T>::IsFind(const T &value) {
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
T &LinkedList<T>::Front() {
    return head->element;
}

template<typename T>
T &LinkedList<T>::Back() {
    return tail->element;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Begin() {
    return Iterator(head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::End() {
    return Iterator(tail);
}


template<typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++() {
    node = node->next;
    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    Node *temp = (*this);
    node = node->next;
    return *temp;
}

template<typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator--() {
    node = node->previous;
    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
    Node *temp = (*this);
    node = node->previous;
    return *temp;
}

template<typename T>
T &LinkedList<T>::Iterator::operator*() {
    return node->element;
}

template<typename T>
T *LinkedList<T>::Iterator::operator->() {
    return &node->element;
}


template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other): head(other.head), tail(other.tail), size(other.size) {
    Clear();
    Copy(other);
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other) noexcept {
    Move(other);
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
    return *this;
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &&other) noexcept {
    if (this != &other) {
        Clear();
        Move(other);
    }
    return *this;
}

template<typename T>
void LinkedList<T>::PushFront(const T &value) {
    if (size == 0) {
        head = new Node{value, nullptr, nullptr};
        tail = head;
    } else {
        head = new Node{value, nullptr, head};
        head->next->previous = head;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::PushBack(const T &value) {
    if (size == 0) {
        head = new Node{value, nullptr, nullptr};
        tail = head;
    } else {
        tail->next = new Node{value, tail, nullptr};
        tail = tail->next;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::Insert(int index, const T &value) {
    if (index < 0 || index > size) {
        std::cerr << "Invalid index!\n";
        return;
    }
    if (head == nullptr) {
        head = new Node{value, nullptr, nullptr};
        tail = head;
    } else if (index == 0) {
        head = new Node{value, nullptr, head};
        head->next->previous = head;
    } else if (index == size) {
        tail->next = new Node{value, tail, nullptr};
        tail = tail->next;
    } else {
        Node *current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node *newNode = new Node{value, current, current->next};
        current->next->previous = newNode;
        current->next = newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::PopFront() {
    if (head == nullptr) {
        tail = head;
        return;
    }
    PopHead();
    --size;
}

template<typename T>
void LinkedList<T>::PopBack() {
    if (head == nullptr) {
        tail = head;
        return;
    }
    PopTail();
    --size;
}

template<typename T>
void LinkedList<T>::Remove(const T &value) {
    Node *current = head;
    while (current != nullptr) {
        if (current->element == value) {
            if (head == current) {
                if (size == 1) {
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    PopHead();
                }
            } else if (tail == current) {
                PopTail();
            } else {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
            }
            --size;
            return;
        }
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}
#endif
