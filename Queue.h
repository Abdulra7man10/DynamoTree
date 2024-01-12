#pragma once
#include <iostream>
#include <cstddef> // for size_t
#include <cmath>
#include <vector>
using namespace std;

template <class T>
class Queue {
    size_t size;
    size_t front;
    size_t rear;
    T* data;

public:
    Queue(size_t s = 10) : size(s), front(0), rear(0) {
        data = new T[size];
    }

    Queue(const Queue& other) : size(other.size), front(other.front), rear(other.rear) {
        data = new T[size];
        for (size_t i = front; i != rear; i = (i + 1) % size) {
            data[i] = other.data[i];
        }
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] data;

            size = other.size;
            front = other.front;
            rear = other.rear;

            data = new T[size];
            for (size_t i = front; i != rear; i = (i + 1) % size) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Queue()
    {
        delete[] data;
    }

    bool isFull() const {
        return (rear + 1) % size == front;
    }

    bool isEmpty() const {
        return rear == front;
    }

    void enQueue(const T& val) {
        if (isFull()) {
            resize();
        }
        data[rear] = val;
        rear = (rear + 1) % size;

    }

    T deQueue() {
        if (isEmpty()) {
            cout << endl << "No element to delete." << endl;
            return T(-1);
        }
        T value = data[front];
        front = (front + 1) % size;
        return value;
    }

    void Display() const 
    {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        for (size_t i = front; i != rear; i = (i + 1) % size) {
            cout << *data[i] << " ";
        }

        cout << endl;
    }

    /*ostream& operator<<(std::ostream& os, const Queue<T>& q) {
        if (q.isEmpty()) {
            os << "Queue is empty.";
            return os;
        }

        for (size_t i = q.front; i != q.rear; i = (i + 1) % q.size) {
            os << q.data[i] << " ";
        }

        return os;
    }*/

    bool search(const T& val) const {
        for (size_t i = front; i != rear; i = (i + 1) % size) {
            if (data[i] == val)
                return true;
        }
        return false;
    }

    T& operator[](size_t index) {
        if (index >= 0 && index < size)
            return data[(front + index) % size];
        else
            throw out_of_range("Index out of range");
    }

    size_t getRear() const {
        return (rear - 1 + size) % size; // Adjust rear to match 0-based indexing
    }

    size_t getFront() const {
        return front;
    }

    void resize() {
        size_t newSize = size * 2;
        T* newData = new T[newSize];

        size_t j = 0;
        for (size_t i = front; i != rear; i = (i + 1) % size) {
            newData[j++] = data[i];
        }

        front = 0;
        rear = j;
        size = newSize;

        delete[] data;
        data = newData;
    }

    int getSize()
    {
        return abs(static_cast<int>(rear-front));
    }
};