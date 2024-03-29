#pragma once
#include <iostream>
#include <cassert>
#include <queue>
#include "user.h"
using namespace std;


template <class T>
class AVLTree
{
private:
	struct BinaryNode
	{
		T data{ };
		int height{ };
		BinaryNode* left{ nullptr };
		BinaryNode* right{ nullptr };

		BinaryNode(T d) : data(d)
		{ }

		int ch_height(BinaryNode* node) // child height
		{
			if (!node)
				return -1;			// -1 for null
			return node->height;	// 0 for leaf
		}
		int update_height() // call in end of insert function
		{
			return height = 1 + max(ch_height(left), ch_height(right));
		}
		int balance_factor()
		{
			return ch_height(left) - ch_height(right);
		}

		friend std::ostream& operator<<(std::ostream& os, const BinaryNode& node)
		{
			os << node.data;
			return os;
		}
	};

	BinaryNode* root{nullptr};

	///////////////////////////
	BinaryNode* search(T& target, BinaryNode* node) 
	{
		if (!node)
			return nullptr;

		if (target == node->data)
			return node;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode* right_rotation(BinaryNode* Q) 
	{
		//cout << "right_rotation " << Q->data << "\n";
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) 
	{
		//cout << "left_rotation " << P->data << "\n";
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}

	BinaryNode* balance(BinaryNode* node)
	{
		if (node->balance_factor() == 2) { 			// Left
			if (node->left->balance_factor() == -1)	// Left Right?
				node->left = left_rotation(node->left);	// To Left Left

			node = right_rotation(node);	// Balance Left Left
		}
		else if (node->balance_factor() == -2) { //right			if (node->right->balance_factor() == 1)
				node->right = right_rotation(node->right);

			node = left_rotation(node);
		}
		return node;
	}

	BinaryNode* insert_node(T target, BinaryNode* node) 
	{
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target);
			else
				node->left = insert_node(target, node->left);
		}
		else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target);
			else
				node->right = insert_node(target, node->right);
		}
		node->update_height();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur)
	{
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(T target, BinaryNode* node)
	{
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else 
		{
			BinaryNode* tmp = node;

			if (!node->left && !node->right)	// case 1: no child
				node = nullptr;
			else if (!node->right) 	// case 2: has left only
				node = node->left;		// connect with child
			else if (!node->left)	// case 2: has right only
				node = node->right;
			else // 2 children: Use successor
			{
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data;	// copy & go delete
				node->right = delete_node(node->data, node->right);
				tmp = nullptr;	// Don't delete me. Successor will be deleted
			}
			if (tmp)
				delete tmp;
		}
		if (node)
		{
			node->update_height();
			node = balance(node);
		}
		return node;
	}

	bool is_bst(BinaryNode* node)
	{
		bool left_bst = !node->left || node->data > node->left->data && is_bst(node->left);

		if (!left_bst)
			return false;

		bool right_bst = !node->right || node->data < node->right->data && is_bst(node->right);
		return right_bst;
	}

	void verify()
	{
		assert(abs(root->balance_factor()) <= 1);
		assert(is_bst(root));
	}

	void print_inorder(BinaryNode* node)
	{
		if (!node) return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}

	BinaryNode* get_node_recursive(size_t& num, BinaryNode* node) const
	{
		if (!node)
			return nullptr;

		// Visit the current node
		if (num == 0)
			return node;
		
		num--;

		// Traverse left subtree
		BinaryNode* left = get_node_recursive(num, node->left);
		if (left)
			return left;

		// Traverse right subtree
		return get_node_recursive(num, node->right);
	}

	size_t count_nodes(BinaryNode* node) const
	{
		if (!node)
			return 0;
		return 1 + count_nodes(node->left) + count_nodes(node->right);
	}

public:
	~AVLTree()
	{
		delete root;
	}
	bool insert_value(T target) 
	{
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);

		verify();
		return true;
	}

	bool delete_value(T target) 
	{
		if (root) {
			root = delete_node(target, root);
			verify();
			return true;
		}
		return false;
	}

	BinaryNode* search(T target) 
	{
		return search(target, root);
	}

	bool exist(T& target)
	{
		if (search(target, root))
			return true;
		return false;
	}

	BinaryNode& operator[](size_t num) const
	{
		if (num >= count())
			throw out_of_range("Index out of range");

		//size_t count = 0; // Initialize count to 0
		return *get_node_recursive(num, root);
	}

	size_t count() const
	{
		return count_nodes(root);
	}

	void print_inorder() 
	{
		print_inorder(root);
	}

	void level_order_traversal() 
	{
		if (!root)
			return;

		cout << "******************\n";
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) 
		{
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) 
			{
				BinaryNode* cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}
};
