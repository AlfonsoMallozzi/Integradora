#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <vector>
#include <stdexcept>


template <class T>
class MaxHeap {
private:
  std::vector<T> heap;

  // sube el elemento para mantener la propiedad del heap
  // complejidad O(log n)
  void heapifyUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;

      if (heap[index] > heap[parent]) {
        std::swap(heap[index], heap[parent]);
        index = parent;
      } else {
        break;
      }
    }
  }

  // baja el elemento para mantener la propiedad del heap
  // complejidad O(log n)
  void heapifyDown(int index) {
    int size = heap.size();

    while (true) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      int largest = index;

      if (left < size && heap[left] > heap[largest])
        largest = left;

      if (right < size && heap[right] > heap[largest])
        largest = right;

      if (largest != index) {
        std::swap(heap[index], heap[largest]);
        index = largest;
      } else {
        break;
      }
    }
  }

public:
  // constructor
  MaxHeap(int capacity = 0) {
    heap.reserve(capacity);
  }

  // inserta un elemento al heap
  // complejidad O(log n)
  void push(T value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
  }

  // elimina y regresa el elemento mayor
  // complejidad O(log n)
  T pop() {
    if (heap.empty()) {
      throw std::out_of_range("heap vacio");
    }

    T top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
      heapifyDown(0);
    }

    return top;
  }

  // regresa si el heap esta vacio
  bool empty() const {
    return heap.empty();
  }
};

#endif
