/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-03-27 16:25:42
* @Last Modified time: 2019-03-27 16:54:24
*/
#include<iostream>
#include<vector>
#include<stack>
#include<time.h>
using namespace std;

// 与递归快速排序中的partition函数相同，寻找切分点，同时调整元素位置
int Partiton(vector<int> &array, int low, int high){
    // 三数取中，避免取得最大值或者最小值
    int mid = low + (high- low)/2;
    if(array[low] > array[high])
        swap(array[low], array[high]);
    if(array[mid] > array[high])
        swap(array[mid], array[high]);
    if(array[mid] > array[low])
        swap(array[mid], array[low]);
    int pivot = array[low];

    // 执行交换
    while(low < high){
        while(low < high && array[high] >= pivot)
            high--;
        swap(array[low], array[high]);
        while(low < high && array[low] <= pivot)
            low++;
        swap(array[low], array[high]);
    }
    return low;
}

// 非递归快速排序
void QuickSort(vector<int> &array){
    if(array.size() <= 1) return ;

    stack<int> st; // 用栈保存每一个待排序子串的首尾元素下标
    int mid = Partiton(array, 0, array.size()-1);
    if(mid > 1){
        st.push(0);
        st.push(mid-1);
    }
    if(mid < array.size()-2){
        st.push(mid + 1);
        st.push(array.size()-1);
    }

    while(!st.empty()){
        int right = st.top();
        st.pop();
        int left = st.top();
        st.pop();
        mid = Partiton(array, left, right);
        if(left < mid-1){
            st.push(left);
            st.push(mid-1);
        }
        if(right > mid+1){
            st.push(mid+1);
            st.push(right);
        }
    }
}

// 生成随机数组，长度为num， 其中每个元素满足 min<= u <= max
vector<int> RAND(int min, int max, unsigned int num){
    vector<int> res;
    if(min > max) return res;

    srand(time(NULL));
    for(unsigned int i = 0; i < num; i++){
        int u = min + rand()%(max-min+1);
        res.push_back(u);
    }
    return res;
}

// 判断数组是否单调非减 ，若是，返回true
bool isOrder(vector<int> array){
    if(array.size() <= 1) return true;
    for(int i = 1; i < array.size(); i++){
        if(array[i] < array[i-1])
            return false;
    }
    return true;
}

// 打印数组array
void printArray(vector<int> array){
    for(auto &it : array)
        cout<<it<<" ";
    cout<<endl;
}

int main(int argc, char const *argv[]) {
    vector<int> array = RAND(0, 10, 20);
    printArray(array);
    QuickSort(array);
    printArray(array);
    if(isOrder(array)) cout<<"isSorted?: YES"<<endl;
    else cout<<"isSorted?: NO"<<endl;
    return 0;
}
