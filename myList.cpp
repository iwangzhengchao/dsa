#include<iostream>
#include<vector>
#include<stack>

using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node(int da):
        data(da), next(NULL){}
};

class List{
private:
    Node *head;
public:
    List(): head(NULL){}
    ~List(){
        delete head;
        cout<<"The list is deleted."<<endl;
    };
    int size(); // 链表长度
    bool isEmpty(); // 是否为空
    void printList(); // 打印链表
    void insert(int position, int value); // 指定位置插入
    void insertHead(int value); // 插入到最前
    void insertTail(int value); // 插入到最后
    int getValue(int position); // 查找指定位置的值
    int search(int value); // 查找指定元素的位置
    void update(int position, int value); // 更新指定位置的值
    int erase(int position); // 删除指定位置的节点
    void reverse(); // 反转链表
    //void clearList() // 清空链表
};

// 返回链表大小
int List::size(){
    Node *p = head;
    int index = 0;
    while(p != NULL){
        index++;
        p = p->next;
    }
    return index;
}

// 判断链表是否为空
bool List::isEmpty(){
    if(List::size() == 0)
        return true;
    else
        return false;
}

// 打印链表
void List::printList(){
    Node *p = head;
    while(p != NULL){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
    cout<<endl;
}

// 在position位置插入value
void List::insert(int position, int value){
    if(position<0 || position>List::size()){
        cout<<"position error, please check."<<endl;
        return ;
    }
    Node *s = new Node(value); // new node
    Node *p = head;
    if(head == NULL){ // isEmpty = true
        head = s;
    }
    else{ // isEmpty = false
        if(position == 0){
            s->next = p;
            head = s;
        }
        else{
            int index = 0;
            while(index != position-1){
                p = p->next;
                index++;
            }
            s->next = p->next;
            p->next = s;
        }
    }
    if (position == 0)
        cout<<"insert "<<value<<" at the first."<<endl;
    else if (position == List::size())
        cout<<"insert "<<value<<" at the tail."<<endl;
    else
        cout<<"insert "<<value<<" at position "<<position<<endl;
}

// 头部插入
void List::insertHead(int value){
    List::insert(0, value);
}

// 尾部插入
void List::insertTail(int value){
    List::insert(List::size(), value);
}

// 搜索数据value，并返回位置
int List::search(int value){
    Node *p = head;
    int index = 0;
    while(p != NULL && p->data != value){
        index++;
        p = p->next;
    }
    if(p == NULL){
        cout<<"the value is not in the list, please check."<<endl;
        return -1;
    }
    else{
        cout<<value<<" at position "<<index<<endl;
        return index;
    }
}

// 将position位置的数据更新为value
void List::update(int position, int value){
    if(position<0 || position>(List::size()-1)){
        cout<<"position error, please check."<<endl;
        return ;
    }
    Node *p = head;
    int index = 0;
    while(index != position){
        p = p->next;
        index++;
    }
    p->data = value;
    cout<<"update "<<value<<" at position "<<position<<endl;
}

// 删除position位置的数据，并返回
int List::erase(int position){
    if(position<0 || position>(List::size()-1)){
        cout<<"position error, please check."<<endl;
        return -1;
    }
    int res = List::getValue(position);
    Node *p = head;
    int index = 0;
    cout<<"erase data at position "<<position<<endl;
    if(position == 0){
        head = p->next;
        return res;
    }
    else{
        while(index != position-1){
            p = p->next;
            index++;
        }
        Node *temp = p->next;
        p->next = temp->next;
        return res;
    }
}

// 反转链表
void List::reverse(){
    if (head == NULL || head->next == NULL)
        return ;
    Node *prev = head;
    Node *cur = head->next;
    Node *temp = head->next->next;
    while(cur){
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    head->next = NULL; // 更新末尾元素的指针
    head = prev; // 更新头结点
    cout<<"reverse the list."<<endl;
}

// 返回position位置的数据
int List::getValue(int position){
    if(position<0 || position>(List::size()-1)){
        cout<<"position error, please check."<<endl;
        return -1;
    }
    Node *p = head;
    int index = 0;
    while(index != position){
        p = p->next;
        index++;
    }
    cout<<"position "<<position<<" is "<<p->data<<endl;
    return p->data;
}
/*
void List::clearList(){
    Node *p = head;
    while(p){
        Node *temp = p->next;
        delete p;
        p = temp;
    }
}
*/

int main() {
    List l1;
    l1.insertTail(6);l1.printList();
    l1.insertHead(7);l1.printList();
    l1.insert(1, 5);l1.printList();
    l1.insert(0, 16);l1.printList();
    l1.insert(2, 56);l1.printList();
    l1.insert(0, 169);l1.printList();
    l1.insert(6, 16);l1.printList();
    l1.search(16);
    l1.getValue(5);
    l1.update(1, 666);l1.printList();
    l1.erase(0);l1.printList();
    l1.reverse(); l1.printList();
    cout<<"The size of the list: "<<l1.size()<<endl;
    return 0;
}
