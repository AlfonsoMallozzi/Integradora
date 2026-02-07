#ifndef _NODEDLL_H_
#define _NODEDLL_H_

template <class T>
class NodeDLL {
private:
    T data;
    NodeDLL<T>* next;
    NodeDLL<T>* prev;

public:
    NodeDLL();
    NodeDLL(T value);

    // Getters (para poder usarlo desde main sin tocar privados)
    T& getData() { return data; }
    const T& getData() const { return data; }

    NodeDLL<T>* getNext() { return next; }
    const NodeDLL<T>* getNext() const { return next; }

    NodeDLL<T>* getPrev() { return prev; }
    const NodeDLL<T>* getPrev() const { return prev; }

    template<typename U>
    friend class DoublyLinkedList;
};

template <class T>
NodeDLL<T>::NodeDLL() : data{}, next{nullptr}, prev{nullptr} {}

template <class T>
NodeDLL<T>::NodeDLL(T value) : data{value}, next{nullptr}, prev{nullptr} {}

#endif
