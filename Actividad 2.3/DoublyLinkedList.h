#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_

#include <utility>   // std::swap
#include <fstream>   // para guardar archivos
#include "NodeDLL.h"

template <class T>
class DoublyLinkedList {
private:
    NodeDLL<T>* head;
    NodeDLL<T>* tail;
    int numElements;

    //quick sort pero por apuntadores
    NodeDLL<T>* partition(NodeDLL<T>* low, NodeDLL<T>* high,
                          long long& comparaciones, long long& swaps);
    void quickSort(NodeDLL<T>* low, NodeDLL<T>* high,
                   long long& comparaciones, long long& swaps);

    //merge sort
    NodeDLL<T>* split(NodeDLL<T>* h);
    NodeDLL<T>* merge(NodeDLL<T>* first, NodeDLL<T>* second,
                      long long& comparaciones, long long& movimientos);
    NodeDLL<T>* mergeSort(NodeDLL<T>* node,
                          long long& comparaciones, long long& movimientos);

    //busqueda binaria
    NodeDLL<T>* middleNode(NodeDLL<T>* start, NodeDLL<T>* end) const;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

    void addLast(T value);
    int getNumElements() const;

    NodeDLL<T>* getHead() const;
    NodeDLL<T>* getTail() const;

    //ordenamientos
    void sortQuick(long long& comparaciones, long long& swaps);
    void sortMerge(long long& comparaciones, long long& movimientos);

    // Aquí guarda toda la lista a archivo
    void saveToFile(const std::string& filename) const;

    // Búsquedas tipo lower/upper bound (con apuntadores)
    NodeDLL<T>* lowerBound(const T& clave) const;          // primer nodo >= clave
    NodeDLL<T>* upperBoundLastLE(const T& clave) const;    // ultimo nodo <= clave
    bool existsExact(const T& clave) const;
};

//constructor y destructor

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), numElements(0) {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    NodeDLL<T>* p = head;
    while (p) {
        NodeDLL<T>* nxt = p->next;
        delete p;
        p = nxt;
    }
    head = tail = nullptr;
    numElements = 0;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), numElements(0) {
    NodeDLL<T>* p = other.head;
    while (p) {
        addLast(p->data);
        p = p->next;
    }
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this == &other) return *this;

    // limpiar actual
    NodeDLL<T>* p = head;
    while (p) {
        NodeDLL<T>* nxt = p->next;
        delete p;
        p = nxt;
    }
    head = tail = nullptr;
    numElements = 0;

    // copiar
    p = other.head;
    while (p) {
        addLast(p->data);
        p = p->next;
    }
    return *this;
}

//operaciones de la lista doblemente ligada 

template <class T>
void DoublyLinkedList<T>::addLast(T value) {
    NodeDLL<T>* node = new NodeDLL<T>(value);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    numElements++;
}

template <class T>
int DoublyLinkedList<T>::getNumElements() const {
    return numElements;
}

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::getHead() const { return head; }

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::getTail() const { return tail; }

//guardar a archivo

template <class T>
void DoublyLinkedList<T>::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;

    NodeDLL<T>* p = head;
    while (p) {
        out << p->data.toString() << "\n";
        p = p->next;
    }
    out.close();
}

//quick sort

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::partition(NodeDLL<T>* low, NodeDLL<T>* high,
                                           long long& comparaciones, long long& swaps) {
    T pivot = high->data;
    NodeDLL<T>* i = low->prev;

    for (NodeDLL<T>* j = low; j != high; j = j->next) {
        comparaciones++;
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
            swaps++;
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    swaps++;
    return i;
}

template <class T>
void DoublyLinkedList<T>::quickSort(NodeDLL<T>* low, NodeDLL<T>* high,
                                    long long& comparaciones, long long& swaps) {
    if (high && low != high && low != high->next) {
        NodeDLL<T>* p = partition(low, high, comparaciones, swaps);
        quickSort(low, p->prev, comparaciones, swaps);
        quickSort(p->next, high, comparaciones, swaps);
    }
}

template <class T>
void DoublyLinkedList<T>::sortQuick(long long& comparaciones, long long& swaps) {
    comparaciones = 0;
    swaps = 0;
    if (!head || head == tail) return;
    quickSort(head, tail, comparaciones, swaps);
}

//merge sort

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::split(NodeDLL<T>* h) {
    NodeDLL<T>* fast = h;
    NodeDLL<T>* slow = h;

    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    NodeDLL<T>* temp = slow->next;
    slow->next = nullptr;
    if (temp) temp->prev = nullptr;
    return temp;
}

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::merge(NodeDLL<T>* first, NodeDLL<T>* second,
                                       long long& comparaciones, long long& movimientos) {
    if (!first) return second;
    if (!second) return first;

    comparaciones++;
    if (first->data <= second->data) {
        first->next = merge(first->next, second, comparaciones, movimientos);
        if (first->next) first->next->prev = first;
        first->prev = nullptr;
        movimientos++;
        return first;
    } else {
        second->next = merge(first, second->next, comparaciones, movimientos);
        if (second->next) second->next->prev = second;
        second->prev = nullptr;
        movimientos++;
        return second;
    }
}

template <class T>
NodeDLL<T>* DoublyLinkedList<T>::mergeSort(NodeDLL<T>* node,
                                          long long& comparaciones, long long& movimientos) {
    if (!node || !node->next) return node;

    NodeDLL<T>* second = split(node);

    node = mergeSort(node, comparaciones, movimientos);
    second = mergeSort(second, comparaciones, movimientos);

    return merge(node, second, comparaciones, movimientos);
}

template <class T>
void DoublyLinkedList<T>::sortMerge(long long& comparaciones, long long& movimientos) {
    comparaciones = 0;
    movimientos = 0;
    if (!head || !head->next) return;

    head = mergeSort(head, comparaciones, movimientos);

    // arreglar tail
    tail = head;
    while (tail->next) tail = tail->next;
}



// medio entre start y end (end EXCLUSIVO)
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::middleNode(NodeDLL<T>* start, NodeDLL<T>* end) const {
    if (!start) return nullptr;
    NodeDLL<T>* slow = start;
    NodeDLL<T>* fast = start;

    while (fast != end && fast->next != end) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// primer nodo >= clave
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::lowerBound(const T& clave) const {
    NodeDLL<T>* start = head;
    NodeDLL<T>* end = nullptr;   // exclusivo
    NodeDLL<T>* ans = nullptr;

    while (start != end) {
        NodeDLL<T>* mid = middleNode(start, end);
        if (!mid) break;

        if (!(mid->data < clave)) { // mid >= clave
            ans = mid;
            end = mid;
        } else {
            start = mid->next;
        }
    }
    return ans;
}

// ultimo nodo <= clave
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::upperBoundLastLE(const T& clave) const {
    NodeDLL<T>* start = head;
    NodeDLL<T>* end = nullptr;
    NodeDLL<T>* ans = nullptr;

    while (start != end) {
        NodeDLL<T>* mid = middleNode(start, end);
        if (!mid) break;

        if (mid->data <= clave) {
            ans = mid;
            start = mid->next;
        } else {
            end = mid;
        }
    }
    return ans;
}

template <class T>
bool DoublyLinkedList<T>::existsExact(const T& clave) const {
    NodeDLL<T>* n = lowerBound(clave);
    if (!n) return false;
    return n->data.getFechaClave() == clave.getFechaClave();
}

#endif // _DOUBLYLINKEDLIST_H_
