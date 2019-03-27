/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-03-27 16:04:30
* @Last Modified time: 2019-03-27 16:06:14
*/

#include<iostream>
#include<stack>
using namespace std;

class BstNode{
public:
	int val;
	BstNode* left;
	BstNode* right;
	BstNode(int x):
	val(x), left(NULL), right(NULL){};
};

class Bst{
public:
	BstNode* root;
	Bst():
	root(NULL){};
	void insert(int value);
	void preOrder(BstNode* root);
	void inOrder(BstNode* root);
	void postOrder(BstNode* root);
};

void Bst::insert(int value){
	// value节点已经存在
	if(0){
		cout<<"the value "<<value<<" in the tree already."<<endl;
		return ;
	}
	// value节点不存在
	else{
		BstNode* pRoot = root;
		// 空树
		if(pRoot == NULL)
			root = new BstNode(value);
		// 非空
		else{
			BstNode* temp;
			while(pRoot!= NULL && pRoot->val!=value){
				temp = pRoot;
				if(pRoot->val > value)
					pRoot = pRoot->left;
				else
					pRoot = pRoot->right;
			}
			pRoot = temp;
			if(pRoot->val > value)
				pRoot->left = new BstNode(value);
			else
				pRoot->right = new BstNode(value);
		}
	}
	cout<<"the value "<<value<<" is inserted."<<endl;
}

void Bst::preOrder(BstNode* root){
	if(root == NULL)
		return;
	cout<<root->val<<" ";
	preOrder(root->left);
	preOrder(root->right);
}

void Bst::inOrder(BstNode* root){
	if(root == NULL)
		return;
	inOrder(root->left);
	cout<<root->val<<" ";
	inOrder(root->right);
}

void Bst::postOrder(BstNode* root){
	if(root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	cout<<root->val<<" ";
}


int main(int argc, char const *argv[]) {
	Bst tree;
	int arr[] = {62, 58, 47, 35, 29,
				 37, 36, 51, 49, 48,
				 50, 56, 88, 73, 99, 93};
	for(int i=0; i<16; i++)
		tree.insert(arr[i]);
	cout<<endl<<"前序遍历: ";
	tree.preOrder(tree.root);

	cout<<endl<<"中序遍历: ";
	tree.inOrder(tree.root);

	cout<<endl<<"后序遍历: ";
	tree.postOrder(tree.root);
	return 0;
}
