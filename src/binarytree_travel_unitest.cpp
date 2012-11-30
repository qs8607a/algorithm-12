#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#include "binarytree.h"

class BinaryTreeTravelTest : public ::testing::Test {
public:
	slib::BstNode<std::string>* root;

	virtual void SetUp() {
		root=slib::BstNode<std::string>::newNode("+");
		slib::BstNode<std::string>* node2=slib::BstNode<std::string>::newNode("*");
		slib::BstNode<std::string>* node3=slib::BstNode<std::string>::newNode("*");
		slib::BstNode<std::string>* node4=slib::BstNode<std::string>::newNode("/");
		slib::BstNode<std::string>* node5=slib::BstNode<std::string>::newNode("A");
		slib::BstNode<std::string>* node17=slib::BstNode<std::string>::newNode("E");
		slib::BstNode<std::string>* node14=slib::BstNode<std::string>::newNode("D");
		slib::BstNode<std::string>* node11=slib::BstNode<std::string>::newNode("C");
		slib::BstNode<std::string>* node8=slib::BstNode<std::string>::newNode("B");

		root->left=node2;
		root->right=node17;
		node2->left=node3;
		node2->right=node14;
		node3->left=node4;
		node3->right=node11;
		node4->left=node5;
		node4->right=node8;
		
	}
	virtual void TearDown() {}
};

TEST_F(BinaryTreeTravelTest, inorder) {
	slib::BstNode<std::string>::inOrderTravel(root);
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}
