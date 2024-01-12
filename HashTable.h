#pragma once
#include "AVLTree.h"


template <class T>
class HashTable
{
private:
	const static int INTERNAL_LIMIT = 2147483647;
	size_t table_size;
	AVLTree<T>* table;

	size_t hash(T& value)
	{
		string str = value;
		int base = 2 * 26 + 12;
		long long sum = 0;

		int n = INTERNAL_LIMIT;
		for (int i = 0; i < str.size(); i++)
		{
			int k;
			if (islower(str[i]))
				k = str[i] - 'a';
			else if (isupper(str[i]))
				k = str[i] - 'A';
			else if (isdigit(str[i]))
				k = str[i] - '0';
			else
				k = str[i] - '.';

			sum = (sum * base + k) % n;
		}
		return sum;
	}

public:
	HashTable(size_t ts = 26) : table_size(ts)
	{
		table = new AVLTree<T>[table_size];
	}

	~HashTable()
	{
		delete[] table;
	}

	size_t getTableSize()
	{
		return table_size;
	}

	bool insert(T value)
	{
		size_t idx = hash(value) % table_size;
		return table[idx].insert_value(value);	
	}

	bool remove(T value)
	{
		size_t idx = hash(value) % table_size;
		return table[idx].delete_value(value);
	}

	T* operator[](T value)
	{
		size_t idx = hash(value) % table_size;
		return &table[idx].search(value)->data;
	}

	AVLTree<T>& operator[](size_t idx)
	{
		return table[idx];
	}

	bool search(T value)
	{
		size_t idx = hash(value) % table_size;
		return table[idx].exist(value);
	}

	void print_all()
	{
		for (int i = 0; i < table_size; i++)
		{
			cout << "Hash " << i << " : ";
			table[i].print_inorder();
			cout << endl;
		}
	}
};