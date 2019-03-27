/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-03-27 16:06:44
* @Last Modified time: 2019-03-27 16:08:13
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
	void preOrder_without_rec(BstNode* root);
	void inOrder_without_rec(BstNode* root);
	void postOrder_without_rec(BstNode* root);
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

void Bst::preOrder_without_rec(BstNode* root){
	if(root == NULL) return ;
	BstNode* p = root;
	stack<BstNode*> st;
	while(p!=NULL || !st.empty()){
		while(p){
			st.push(p);
			cout<<p->val<<" ";
			p = p->left;
		}
		if(!st.empty()){
			p = st.top();
			st.pop();
			p = p->right;
		}
	}
}

void Bst::inOrder_without_rec(BstNode* root){
	if(root == NULL) return ;
	stack<BstNode*> st;
	BstNode* p = root;
	while(p!=NULL || !st.empty()){
		while(p){
			st.push(p);
			p = p->left;
		}
		if(!st.empty()){
			p = st.top();
			cout<<p->val<<" ";
			st.pop();
			p = p->right;
		}
	}
}

void Bst::postOrder_without_rec(BstNode* root){
	if(root == NULL) return ;
	stack<BstNode*> st;
	BstNode* pCur = root;
	BstNode* pLast = NULL;

	while(pCur){
		st.push(pCur);
		pCur = pCur->left;
	}
	while(!st.empty()){
		pCur = st.top();
		st.pop();
		if(pCur->right == NULL || pCur->right == pLast){
			cout<<pCur->val<<" ";
			pLast = pCur;
		}
		else{
			st.push(pCur);
			pCur = pCur->right;
			while(pCur){
				st.push(pCur);
				pCur = pCur->left;
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	Bst tree;
	int arr[] = {62, 58, 47, 35, 29,
				 37, 36, 51, 49, 48,
				 50, 56, 88, 73, 99, 93};
	for(int i=0; i<16; i++)
		tree.insert(arr[i]);
	cout<<endl<<"前序遍历: ";
	tree.preOrder_without_rec(tree.root);

	cout<<endl<<"中序遍历: ";
	tree.inOrder_without_rec(tree.root);

	cout<<endl<<"后序遍历: ";
	tree.postOrder_without_rec(tree.root);
	return 0;
}
