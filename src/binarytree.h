#pragma once

#include <stdlib.h>

namespace slib{
	template <typename T>
	class Node {
		T data;
		Node* next;
		Node* prev;
		Node* parent;
		/** the first children */
		Node* children;
	};

	template <typename T>
	class BstNode {
	public:
		T data;
		/** left child node */
		BstNode* left;
		/** right child node */
		BstNode* right;

		static BstNode* newNode(T value){
			BstNode* ret=new BstNode();
			ret->data=value;
			ret->left=NULL;
			ret->right=NULL;
			return ret;
		}

		static void inOrderTravel(BstNode* node){	
			if(node==NULL)
					return;
			std::vector<BstNode*> stack;
			while(true){				
				for(;node;node=node->left)
					stack.push_back(node);
				if(stack.empty()) break;
				node=stack.back();
				stack.pop_back();
				std::cout<<node->data<<" ";
				node = node->right;
			}
		}

		/**
		* @param node 
		*
		*/
		static BstNode* insertIntoBST(BstNode* node,T data){
			/** If the tree is empty */
			if(node == NULL){
				/** just create a node and return. This node is the root of the tree */
				return newNode(data);
			} else {
				if(data <= node->data)
					node->left = insert(node->left,data);
				else 
					node->right = insert(node->left,data);
				return node;
			}
		}
	};  

	void build123();
};