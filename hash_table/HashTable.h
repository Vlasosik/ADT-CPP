#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<vector>
#include<memory>
/**
 * Implementation of the Abstract Data Type (ADT) "Hash Table".
 *
 * The HashTable class provides basic operations for working with a hash table:
 *
 * Constructors:
 *  - HashTable(size_t table_size = 16, float load_factor = 0.75): Initializes a hash table with a specified size and load factor.
 *  - HashTable(const HashTable &other): Copy constructor, creates a deep copy of another hash table.
 *  - HashTable(HashTable &&other) noexcept: Move constructor, transfers ownership of resources from another hash table.
 *
 * Destructor:
 *  - ~HashTable(): Destroys the hash table and deallocates all dynamically allocated nodes.
 *
 * Overloaded Operators:
 *  - HashTable& operator=(const HashTable &other): Copy assignment operator, deep copies another hash table.
 *  - HashTable& operator=(HashTable &&other) noexcept: Move assignment operator, transfers ownership from another hash table.
 *
 * Public Methods:
 *  - void Insert(const Key &key, const Value &value): Inserts a key-value pair into the hash table, handling collisions as needed.
 *  - Value &Get(const Key &key): Retrieves the value associated with the specified key. Throws an exception if the key is not found.
 *  - void Remove(const Key &key): Removes the specified key and its associated value from the hash table, if it exists.
 *  - void Clear(): Removes all key-value pairs from the hash table, effectively clearing it.
 *  - bool ContainsKey(const Key &key): Returns true if the hash table contains the specified key, false otherwise.
 *  - [[nodiscard]] bool IsEmpty() const: Returns true if the hash table is empty, false otherwise.
 *  - [[nodiscard]] size_t Size() const: Returns the number of key-value pairs in the hash table.
 *  - void Resize(size_t newSize): Resizes the hash table to a new size, which can be larger or smaller.
 *
 * Private Methods:
 *  - int HashFunction(const Key &key) const: Computes the hash code for a given key, determining its index in the hash table.
 *  - void CopyBuckets(const HashTable &hash_table): Copies the elements from another hash table into this one.
 *
 * Time Complexity:
 *  - Insert: O(1) on average, O(n) in the worst case (due to collisions).
 *  - Get: O(1) on average, O(n) in the worst case (if many collisions occur).
 *  - Remove: O(1) on average, O(n) in the worst case.
 *  - Clear: O(n) - Each key-value pair is visited and deleted.
 *  - ContainsKey: O(1) on average, O(n) in the worst case.
 *  - IsEmpty: O(1) - Simply checks if the count of elements is zero.
 *  - Size: O(1) - Returns the stored count of key-value pairs.
 *
 * Features:
 * - The Hash Table uses a hash function to map keys to indices, providing efficient access to values.
 * - The load factor determines when to resize the hash table to maintain performance as elements are added.
 * - Collision resolution is handled through chaining with linked lists, allowing multiple values to be stored at the same index.
 * - Provides a dynamic and efficient way to store and retrieve key-value pairs with average constant time complexity for operations.
 *
 * @author Vlas Pototskyi
 */
template<typename Key, typename Value>
class HashTable {
    struct Node {
        Key key;
        Value value;
        std::unique_ptr<Node> next;

        Node(Key key, Value value, std::unique_ptr<Node> next)
            : key(key), value(value), next(std::move(next)) {
        }
    };

    std::vector<std::unique_ptr<Node> > buckets;
    size_t table_size;
    size_t element_count;
    float load_refactor = 0.75;

    void CopyBuckets(const HashTable &hash_table);

public:
    // --- Constructors ---
    explicit HashTable(size_t table_size = 16, float load_factor = 0.75);

    HashTable(const HashTable &other);

    HashTable(HashTable &&other) noexcept;


    // --- Overload operators ---
    HashTable &operator=(const HashTable &other);

    HashTable &operator=(HashTable &&other) noexcept;

    // --- Destructors ---
    ~HashTable();

    // Get Hash Function for Index
    [[nodiscard]] int HashFunction(const Key &key) const;

    // --- Add element ---
    void Insert(const Key &key, const Value &value);

    // --- Get element ---
    Value &Get(const Key &key);

    // --- Remove element ---
    void Remove(Key &key);

    void Clear();

    // --- Find element ---
    bool ContainsKey(const Key &key);

    [[nodiscard]] bool IsEmpty() const;

    // --- Get size ---
    [[nodiscard]] size_t Size() const;

    // --- Change size in hash table ---
    void Resize();

    // --- Show hash table value ---
    void Show() const;
};

template<typename Key, typename Value>
void HashTable<Key, Value>::CopyBuckets(const HashTable &hash_table) {
    for (int i = 0; i < hash_table.table_size; ++i) {
        Node *current = hash_table.buckets[i].get();
        Node *previous = nullptr;
        while (current != nullptr) {
            auto newNode = std::make_unique<Node>(current->key, current->value, nullptr);
            if (previous == nullptr) {
                buckets[i] = std::move(newNode);
            } else {
                previous->next = std::move(newNode);
            }
            previous = previous == nullptr ? hash_table.buckets[i].get() : previous->next.get();
            current = current->next.get();
        }
    }
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t table_size, const float load_factor)
    : table_size(table_size), element_count(0), load_refactor(load_factor) {
    buckets.resize(table_size);
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &other)
    : buckets(other.table_size), table_size(other.table_size), element_count(other.element_count),
      load_refactor(other.load_refactor) {
    CopyBuckets(other);
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(HashTable &&other) noexcept
    : buckets(std::move(other.buckets)),
      table_size(other.table_size),
      element_count(other.element_count),
      load_refactor(other.load_refactor) {
    other.table_size = 0;
    other.element_count = 0;
    other.load_refactor = 0.0;
}

template<typename Key, typename Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(const HashTable &other) {
    if (this != &other) {
        Clear();
        table_size = other.table_size;
        element_count = other.element_count;
        load_refactor = other.load_refactor;
        CopyBuckets(other);
    }
    return *this;
}

template<typename Key, typename Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(HashTable &&other) noexcept {
    if (this != &other) {
        Clear();
        buckets = std::move(other.buckets);
        table_size = other.table_size;
        element_count = other.element_count;
        load_refactor = other.load_refactor;

        other.table_size = 0;
        other.element_count = 0;
        other.load_refactor = 0.0f;
        other.buckets.clear();
    }
    return *this;
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
    Clear();
}

template<typename Key, typename Value>
int HashTable<Key, Value>::HashFunction(const Key &key) const {
    std::hash<Key> hash;
    return hash(key) % table_size;
}

// add check
template<typename Key, typename Value>
void HashTable<Key, Value>::Insert(const Key &key, const Value &value) {
    if (element_count >= table_size * load_refactor) {
        Resize();
    }
    int hash = HashFunction(key);
    auto &bucket = buckets[hash];
    Node *current = bucket.get();

    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next.get();
    }

    auto newNode = std::make_unique<Node>(key, value, std::move(bucket));
    bucket = std::move(newNode);
    ++element_count;
}

template<typename Key, typename Value>
Value &HashTable<Key, Value>::Get(const Key &key) {
    int hash = HashFunction(key);
    auto &bucket = buckets[hash];
    Node *current = bucket.get();
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next.get();
    }
    throw std::out_of_range("Incorrect key index!\n");
}

template<typename Key, typename Value>
void HashTable<Key, Value>::Remove(Key &key) {
    int hash = HashFunction(key);
    auto &bucket = buckets[hash];
    Node *current = bucket.get();
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                bucket = std::move(current->next);
            } else {
                previous->next = std::move(current->next);
            }
            --element_count;
            return;
        }
        previous = current;
        current = current->next.get();
    }
    throw std::out_of_range("No such key exists!\n");
}

template<typename Key, typename Value>
void HashTable<Key, Value>::Clear() {
    buckets.clear();
    element_count = 0;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::ContainsKey(const Key &key) {
    int hash = HashFunction(key);
    auto &bucket = buckets[hash];
    Node *current = bucket.get();
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next.get();
    }
    return false;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::IsEmpty() const {
    return element_count == 0;
}

template<typename Key, typename Value>
size_t HashTable<Key, Value>::Size() const {
    return element_count;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::Resize() {
    size_t new_size = table_size * 2;
    std::vector<std::unique_ptr<Node> > new_buckets(new_size);
    for (auto &bucket: buckets) {
        while (bucket) {
            auto current = std::move(bucket);
            bucket = std::move(current->next);
            size_t new_index = HashFunction(current->key);
            current->next = std::move(new_buckets[new_index]);
            new_buckets[new_index] = std::move(current);
        }
    }
    buckets = std::move(new_buckets);
    table_size = new_size;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::Show() const {
    for (int i = 0; i < table_size; ++i) {
        Node *current = buckets[i].get();
        std::cout << "Bucket number: " << i << ": ";
        while (current != nullptr) {
            std::cout << "[" << current->key << ", " << current->value << "] -> ";
            current = current->next.get();
        }
        std::cout << "nullptr" << std::endl;
    }
}


#endif //HASHTABLE_H
