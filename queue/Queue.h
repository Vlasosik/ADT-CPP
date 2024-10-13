#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
    struct Node {
        T element;
        Node *previous;
        Node *next;

        explicit Node(const T &element, Node *previous = nullptr, Node *next = nullptr): element(element),
            previous(previous), next(next) {
        }
    };

    int size = 0;
    Node *head;
    Node *tail;

    void Copy(Queue &other);

    void Move(Queue &other);

    void Clear();

public:
    // --- Constructors ---
    Queue();

    Queue(const Queue &other);

    Queue(Queue &&other) noexcept;

    // --- Destructors ---
    ~Queue();

    // --- Overload operators ---
    Queue &operator=(const Queue &other);

    Queue &operator=(Queue &&other) noexcept;

    // --- Added method ---
    void Push(const T &value);

    // --- Find method ---
    T Front();

    T Back();

    // --- Remove method ---
    void Pop();

    // --- Check size method ---
    [[nodiscard]] int Size() const;

    // --- Swap method ---
    void Swap(Queue &other);

    bool IsEmpty();

    void Show() const;
};

template<typename T>
void Queue<T>::Copy(Queue &other) {
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
void Queue<T>::Move(Queue &other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
void Queue<T>::Clear() {
    while (head != nullptr) {
        const Node *current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {
}

template<typename T>
Queue<T>::Queue(const Queue &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
}

template<typename T>
Queue<T>::Queue(Queue &&other) noexcept {
    if (this != &other) {
        Clear();
        Move(other);
    }
}

template<typename T>
Queue<T>::~Queue() {
    Clear();
}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue &other) {
    if (this != &other) {
        Clear();
        Copy(other);
    }
    return *this;
}

template<typename T>
Queue<T> &Queue<T>::operator=(Queue &&other) noexcept {
    if (this != &other) {
        Clear();
        Move(other);
    }
    return *this;
}

template<typename T>
void Queue<T>::Push(const T &value) {
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
T Queue<T>::Front() {
    return head->element;
}

template<typename T>
T Queue<T>::Back() {
    return tail->element;
}

template<typename T>
void Queue<T>::Pop() {
    if (head == nullptr) {
        return;
    }
    const Node *temp = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
}

template<typename T>
int Queue<T>::Size() const {
    return size;
}

template<typename T>
void Queue<T>::Swap(Queue &other) {
    Node *temp = head;
    head = other.head;
    other.head = temp;

    temp = tail;
    tail = other.tail;
    other.tail = temp;

    std::swap(this->size, other.size);
}

template<typename T>
bool Queue<T>::IsEmpty() {
    return head == nullptr;
}

template<typename T>
void Queue<T>::Show() const {
    Node *current = head;
    while (current != nullptr) {
        std::cout << current->element << " ";
        current = current->next;
    }
}
#endif //QUEUE_H
