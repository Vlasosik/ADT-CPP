#ifndef STACK_H
#define STACK_H
/**
* Implementation of the Abstract Data Type (ADT) "Stack" using a doubly linked list.
*
* The Stack class provides basic operations for working with a stack:
*
* Methods:
*  - void Push(const T &value): Adds an element to the top of the stack.
*  - void Pop(): Removes the top element from the stack.
*  - [[nodiscard]] T &Top(): Returns a reference to the top element in the stack.
*  - [[nodiscard]] bool IsEmpty() const: Returns true if the stack is empty.
*  - [[nodiscard]] int Size() const: Returns the number of elements in the stack.
*  - void Clear(): Clears the stack (removes all elements).
*  - void Show() const: Displays the elements in the stack.
*
* Features:
* - The stack is implemented using a doubly linked list, allowing efficient insertion and removal of elements from the top.
* - The stack supports copy and move semantics (copy constructor, move constructor, copy assignment, move assignment).
* - The stack automatically manages memory allocation and deallocation, ensuring no memory leaks.
*
* Time complexity:
* - Push: O(1)
* - Pop: O(1)
* - Top: O(1)
* - Size: O(1)
* - Clear: O(n)
*
* Notes:
* - The stack operates on a Last In, First Out (LIFO) principle, meaning the last element added is the first to be removed.
* - The doubly linked list structure allows for future extensions, such as implementing a deque or other list-based structures.
*
* @author Vlas Pototskyi
*/
template<typename T>
class Stack {
    struct Node {
        T element;
        Node *previous;
        Node *next;

        explicit Node(const T &element, Node *previous = nullptr, Node *next = nullptr): element(element),
            previous(previous), next(next) {
        }
    };

    Node *head;
    Node *tail;
    T size;

    void Copy(const Node &other);

    void Move(Node &other);

public:
    // --- Constructors ---
    Stack();

    Stack(const Stack &other);

    Stack(Stack &&other) noexcept;

    // --- Destructors ---
    ~Stack();

    // --- Overload operators ---
    Stack &operator=(const Stack &other);

    Stack &operator=(Stack &&other) noexcept;


    // --- Added method ---
    void Push(const T &value);

    // --- Find method ---
    T Top();

    // --- Remove method ---
    void Pop();

    void Clear();

    // --- Check size method ---
    [[nodiscard]] T &Size();

    bool IsEmpty();

    void Show() const;
};

template<typename T>
void Stack<T>::Copy(const Node &other) {
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
void Stack<T>::Move(Node &other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
Stack<T>::Stack() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
Stack<T>::Stack(const Stack &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
}

template<typename T>
Stack<T>::Stack(Stack &&other) noexcept {
    Move(other);
}

template<typename T>
Stack<T>::~Stack() {
    Clear();
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
    return *this;
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack &&other) noexcept {
    if (this != &other) {
        Clear();
        Move(other);
    }
    return *this;
}


template<typename T>
void Stack<T>::Push(const T &value) {
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
T Stack<T>::Top() {
    if (tail == nullptr) {
        return -1;
    }
    return tail->element;
}

template<typename T>
void Stack<T>::Pop() {
    if (head == nullptr) {
        tail = head;
        return;
    }
    const Node *current = tail;
    tail = tail->previous;
    tail != nullptr ? tail->next = nullptr : head = nullptr;
    delete current;
    --size;
}

template<typename T>
void Stack<T>::Clear() {
    while (head != nullptr) {
        const Node *current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
T &Stack<T>::Size() {
    return size;
}

template<typename T>
bool Stack<T>::IsEmpty() {
    return head == nullptr;
}

template<typename T>
void Stack<T>::Show() const {
    Node *current = head;
    while (current != nullptr) {
        std::cout << current->element << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif //STACK_H
