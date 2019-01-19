#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class BSTNode{
public:
	int data;
	BSTNode *left;
	BSTNode *right;
	BSTNode(int x):
	data(x), left(NULL), right(NULL){}
};

class BSTree{
public:
	BSTNode *root;
	BSTree():
	root(NULL){}
	~BSTree(){destory(root);}

	// 是否为空
	bool isEmpty();
	// 深度
	int depth(BSTNode *&proot);
	// 节点数
	int size(BSTNode *&proot);
	// 叶子节点数
	int leafsize(BSTNode *&proot);

	// 前序遍历
	void preOrder(BSTNode* &pRoot);
	// 中序遍历
	void inOrder(BSTNode* &pRoot);
	// 后序遍历
	void postOrder(BSTNode* &pRoot);
	// 层序遍历
	void levelOrder(BSTNode* &pRoot);

	// 查找
	bool search(int value);
	// 插入
	void insert(int value);
	// 删除
	void remove(int value);

	// 寻找前驱节点
	BSTNode* predecessor(int value);
	// 寻找后继节点
	BSTNode* successor(int value);

	// 最小值
	int minimum();
	// 最大值
	int maximum();

	// 销毁BST
	void destory(BSTNode *&proot);

private:
	// 获取value节点的地址
	BSTNode* getAddr(int value);
	// 获取value父节点的地址
	BSTNode* getParents(int value);
};

bool BSTree::isEmpty(){
	return root==NULL;
}

int BSTree::depth(BSTNode *&proot){
	if(proot == NULL)
		return 0;
	int left = depth(proot->left);
	int right = depth(proot->right);
	if(left > right)
		return left + 1;
	else
		return right + 1;
}

int BSTree::size(BSTNode *&proot){
	if(proot == NULL)
		return 0;
	int left = size(proot->left);
	int right = size(proot->right);
	return left + right + 1;
}

int BSTree::leafsize(BSTNode *&proot){
	if(proot == NULL)
		return 0;
	if(proot->left == NULL && proot->right == NULL)
		return 1;
	int leftLeaf = leafsize(proot->left);
	int rightLeaf = leafsize(proot->right);
	return leftLeaf + rightLeaf;
}

BSTNode* BSTree::getParents(int value){
	if(BSTree::search(value) == true){
		BSTNode* pRoot = root;
		BSTNode* parents; // 用于存储value节点的父节点
		while(pRoot->data!=value){
			parents = pRoot;
			if(pRoot->data > value)
				pRoot = pRoot->left;
			else
				pRoot = pRoot->right;
		}
		if(pRoot == root){
			//cout<<"the value is root of the tree, NO PARENTS."<<endl;
			return NULL;
		}
		else
			return parents;
	}
	else{
		cout<<"the value is not in the tree."<<endl;
		return NULL;
	}
}

BSTNode* BSTree::getAddr(int value){
	if(BSTree::search(value) == true){
		BSTNode* pRoot = root;
		while(pRoot->data!=value){
			if(pRoot->data > value)
				pRoot = pRoot->left;
			else
				pRoot = pRoot->right;
		}
		return pRoot;
	}
	else{
		cout<<"the value is not in the tree."<<endl;
		return NULL;
	}
}

// 若value不在树内或者value没有前驱，返回null，否则，返回前驱节点地址
BSTNode* BSTree::predecessor(int value){
	if(!search(value)){
		cout<<"the value is not in the tree."<<endl;
		return NULL;
	}
	else if(BSTree::minimum() == value){
		cout<<"节点"<<value<<"没有前驱节点"<<endl;
		return NULL;
	}
	else{
		BSTNode* pRoot = getAddr(value);// 用于存储value节点的地址
		BSTNode* parents = getParents(value); // 用于存储value的父节点地址
		// 含左子树的节点
		if(pRoot->left != NULL){
			BSTNode* pre = pRoot->left;
			while(pre->right != NULL){
				pre = pre->right;
			}
			return pre;
		}
		//没有左子树的节点
		else{
			if(parents->right == pRoot)
				return parents;
			else if(parents->left == pRoot){
				while(parents->data > value)
					parents = getParents(parents->data);
				return parents;
			}
		}
	}
}

// 若value不在树内或者value没有后继，返回null，否则，返回前后继节点地址
BSTNode* BSTree::successor(int value){
	if(!search(value)){
		cout<<"the value is not in the tree."<<endl;
		return NULL;
	}
	else if(BSTree::maximum() == value){
		cout<<"节点"<<value<<"没有后继节点"<<endl;
		return NULL;
	}
	else{
		BSTNode* pRoot = getAddr(value);// 用于存储value节点的地址
		BSTNode* parents = getParents(value); // 用于存储value的父节点地址
		// 含右子树的节点
		if(pRoot->right != NULL){
			BSTNode* pre = pRoot->right;
			while(pre->left != NULL){
				pre = pre->left;
			}
			return pre;
		}
		//没有右子树的节点
		else{
			if(parents->left == pRoot)
				return parents;
			else if(parents->right == pRoot){
				while(parents->data < value)
					parents = getParents(parents->data);
				return parents;
			}
		}
	}
}

int BSTree::minimum(){
	BSTNode* proot = root;
	while(proot->left != NULL){
		proot = proot->left;
	}
	return proot->data;
}

int BSTree::maximum(){
	BSTNode* proot = root;
	while(proot->right != NULL){
		proot = proot->right;
	}
	return proot->data;
}

/*
 *                         62
 *                       /    \
 *                     58      88
 *                     /       / \
 *                    47      73  99
 *                   /  \         /
 *                 35    51      93
 *                 / \   / \
 *               29  37 49 56
 *                   /     / \
 *                  36    48 50
 *
 * 删除节点的3种情况：
 * 1. 叶子节点
 * 		1.1 树只含有一个节点,删除叶子节点
 * 		1.2 树含有至少2个节点,删除叶子节点
 * 2. 仅有左或者右子树的节点
 *		2.1 仅有左子树的节点，删除根节点
 *		2.2 仅有左子树的节点，删除非根节点
 *		2.3 仅有右子树的节点，删除根节点
 *		2.4 仅有右子树的节点，删除非根节点
 * 3. 左右子树都有的节点
 *
 */

void BSTree::remove(int value){
	if(!search(value)){
		cout<<"the value is not in the tree. please check."<<endl;
		return ;
	}
	else{
		// 查找value节点
		BSTNode* pRoot = getAddr(value);// 用于存储value节点的地址
		BSTNode* parents = getParents(value); // 用于存储待删除节点的父节点
		// 删除value节点
		// 1.叶节点
		// 1.1 树只含有一个节点
		if(pRoot == root && pRoot->left == NULL && pRoot->right == NULL){
			root = NULL;
			free(pRoot);
		}
		// 1.2 树含有至少2个节点
		else if(pRoot != root && pRoot->left == NULL && pRoot->right == NULL){
			// 待删节点是父节点的右孩子
			if(parents->right != NULL && parents->right->data == value){
				parents->right = NULL;
				free(pRoot);
			}
			// 待删节点是父节点的左孩子
			else{
				parents->left = NULL;
				free(pRoot);
			}
		}
		// 2. 仅有左子树或右子树的节点
		// 2.1 仅有左子树，且删除根节点
		else if(pRoot == root && pRoot->left != NULL && pRoot->right == NULL){
			root = pRoot->left;
			free(pRoot);
		}
		// 2.2 仅有左子树的节点，删除非根节点
		else if(pRoot != root && pRoot->left != NULL && pRoot->right == NULL){
			// 待删节点是父节点的右孩子
			if(parents->right != NULL && parents->right->data == value){
				parents->right = pRoot->left;
				free(pRoot);
			}
			// 待删节点是父节点的左孩子
			else{
				parents->left = pRoot->left;
				free(pRoot);
			}
		}
		// 2.3 仅有右子树的节点，删除根节点
		else if(pRoot == root && pRoot->left == NULL && pRoot->right != NULL){
			root = pRoot->right;
			free(pRoot);
		}
		// 2.4 仅有右子树的节点， 删除非根节点
		else if(pRoot != root && pRoot->left == NULL && pRoot->right != NULL){
			// 待删节点是父节点的右孩子
			if(parents->right != NULL && parents->right->data == value){
				parents->right = pRoot->right;
				free(pRoot);
			}
			// 待删节点是父节点的左孩子
			else{
				parents->left = pRoot->right;
				free(pRoot);
			}
		}
		// 3. 左右子树都有的节点
		else{
			// 寻找待删除节点的直接前驱
			BSTNode* pre = predecessor(value);// pre存储直接前驱
			pRoot->data = pre->data;// 数据覆盖
			// 寻找直接前驱的左/右节点
			if(pre->right != NULL){
				BSTNode *pRootNext = pRoot->right;
				BSTNode *temp = pre->right;
				if(pre == pRootNext)
					pRoot->right = temp;
				else
					pRootNext->left = temp;
				free(pre);
			}
			else if(pre->left != NULL){
				BSTNode *pRootNext = pRoot->left;
				BSTNode *temp = pre->left;
				if(pre == pRootNext)
					pRoot->left = temp;
				else
					pRootNext->right = temp;
				free(pre);
			}
			else if(pre->left == NULL && pre->right == NULL){
				pRoot->left = NULL;
				free(pre);
			}
		}
	}
}


bool BSTree::search(int value){
	BSTNode* pRoot = root;
	while(pRoot!=NULL && pRoot->data!=value){
		if(pRoot->data > value)
			pRoot = pRoot->left;
		else
			pRoot = pRoot->right;
	}
	if(pRoot == NULL)
		return false;
	else
		return true;
}

void BSTree::insert(int value){
	// value节点已经存在
	if(BSTree::search(value) == true){
		cout<<"the value "<<value<<" in the tree already."<<endl;
		return ;
	}
	// value节点不存在
	else{
		BSTNode* pRoot = root;
		// 空树
		if(pRoot == NULL)
			root = new BSTNode(value);
		// 非空
		else{
			BSTNode* temp;
			while(pRoot!= NULL && pRoot->data!=value){
				temp = pRoot;
				if(pRoot->data > value)
					pRoot = pRoot->left;
				else
					pRoot = pRoot->right;
			}
			pRoot = temp;
			if(pRoot->data > value)
				pRoot->left = new BSTNode(value);
			else
				pRoot->right = new BSTNode(value);
		}
	}
	cout<<"the value "<<value<<" is inserted."<<endl;
}

void BSTree::preOrder(BSTNode* &pRoot){
	if(pRoot == NULL)
		return ;
	cout<<pRoot->data<<' ';
	preOrder(pRoot->left);
	preOrder(pRoot->right);
}

void BSTree::inOrder(BSTNode* &pRoot){
	if(pRoot == NULL)
		return ;
	inOrder(pRoot->left);
	cout<<pRoot->data<<' ';
	inOrder(pRoot->right);
}

void BSTree::postOrder(BSTNode* &pRoot){
	if(pRoot == NULL)
		return ;
	postOrder(pRoot->left);
	postOrder(pRoot->right);
	cout<<pRoot->data<<' ';
}

void BSTree::levelOrder(BSTNode *&pRoot){
	queue<BSTNode*> p;
	if(pRoot == NULL)
		return ;
	p.push(pRoot);
	while (!p.empty()){
		BSTNode *temp = p.front();
		cout<<temp->data<<' ';
		p.pop();
		if(temp->left)
			p.push(temp->left);
		if(temp->right)
			p.push(temp->right);
	}
}

void BSTree::destory(BSTNode *&proot){
    if (proot== NULL)
        return ;
    destory(proot->left);
    destory(proot->right);
    cout<<"free value "<<proot->data<<endl;
    free(proot);
    proot = NULL;
}


int main(int argc, char const *argv[])
{
	BSTree tree;
	int arr[] = {62, 58, 47, 35, 29,
				 37, 36, 51, 49, 48,
				 50, 56, 88, 73, 99, 93};
	for(int i=0; i<16; i++)
		tree.insert(arr[i]);

	cout<<"前序遍历: ";
	tree.preOrder(tree.root);
	cout<<endl;
	cout<<"中序遍历: ";
	tree.inOrder(tree.root);
	cout<<endl;
	cout<<"最小值: "<<tree.minimum()<<endl;
	cout<<"最大值: "<<tree.maximum()<<endl;

	cout<<"深度: "<<tree.depth(tree.root)<<endl;
	cout<<"节点数: "<<tree.size(tree.root)<<endl;
	cout<<"叶子节点数: "<<tree.leafsize(tree.root)<<endl;

	int index = 2;
	BSTNode *pre = tree.predecessor(arr[index]);
	if(pre != NULL)
		cout<<"节点"<<arr[index]<<"的前驱节点是"<<pre->data<<endl;

	BSTNode *suc = tree.successor(arr[index]);
	if(suc != NULL)
		cout<<"节点"<<arr[index]<<"的后继节点是"<<suc->data<<endl;

	cout<<"删除节点: "<<arr[index]<<endl;
	tree.remove(arr[index]);

	cout<<"前序遍历: ";
	tree.preOrder(tree.root);
	cout<<endl;
	cout<<"中序遍历: ";
	tree.inOrder(tree.root);
	cout<<endl;

	tree.destory(tree.root);
	return 0;
}
