#pragma once
#include <stdexcept>
#include <string>
template <typename T>
class ABQ
{
	unsigned int _capacity;
	unsigned int _size = 0;
	unsigned int _scalar = 2;
	T* array;
public:
	ABQ() {
		_capacity = 1;
		array = new T[_capacity];
	}
	ABQ(int capacity) {
		_capacity = capacity;
		array = new T[_capacity];
	}

	ABQ(const ABQ& c) {
		_capacity = c._capacity;
		_size = c._size;
		_scalar = c._scalar;

		delete[] array;
		array = new T[_capacity];
		for (int i = 0; i < _size; i++) {
			array[i] = c.array[i];
		}
	}

	ABQ& operator=(const ABQ& c) {
		_capacity = c._capacity;
		_size = c._size;
		_scalar = c._scalar;

		delete[] array;
		array = new T[_capacity];
		for (int i = 0; i < _size; i++) {
			array[i] = c.array[i];
		}

		return *this;
	}

	~ABQ() {
		delete[] array;
	}

	void enqueue(T data) {
		if (_size == _capacity) {
			_capacity *= _scalar;
			T* n_array = new T[_capacity];
			for (unsigned int i = 0; i < _size; i++) {
				n_array[i] = array[i];
			}
			delete[] array;
			array = n_array;
		}
		array[_size] = data;
		_size += 1;
	}
	//Add a new item to end of the queue and resizes if necessary.

	T dequeue() {
		if (_size == 0) {
			throw std::runtime_error("Queue is empty!");
		}

		_size -= 1;
		T out = array[0];
		if (_size * _scalar < _capacity) {
			_capacity /= _scalar;
		}
		T* n_array = new T[_capacity];
		for (unsigned int i = 0; i < _size; i++) {
			n_array[i] = array[i + 1];
		}
		delete[] array;
		array = n_array;
		return out;
	}
	//Remove the item at front of the queue, resizes if necessary, and return the value removed. Throws a runtime_error if the queue is empty.

	T peek() {
		if (_size == 0) {
			throw std::runtime_error("Queue is empty!");
		}

		return array[0];
	}
	//Return the value of the item at the top of the stack, without removing it. Throws a runtime_error if the stack is empty.

	unsigned int getSize() {
		return _size;
	}
	//Returns the current number of items in the ABQ.

	unsigned int getMaxCapacity() {
		return _capacity;
	}
	//Returns the current max capacity of the ABQ.

	T* getData() {
		return array;
	}
	//Returns the array representing the stack.
};
