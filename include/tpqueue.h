// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head;

public:
    TPQueue() : head(nullptr) {}
    ~TPQueue();

    void push(const T& elem);
    T pop();
    bool isEmpty() const { return head == nullptr; }
};

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void TPQueue<T>::push(const T& elem) {
    Node* newNode = new Node(elem);
    if (head == nullptr || elem.prior > head->data.prior) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr && current->data.prior >= elem.prior) {
            prev = current;
            current = current->next;
        }
        prev->next = newNode;
        newNode->next = current;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    return data;
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
