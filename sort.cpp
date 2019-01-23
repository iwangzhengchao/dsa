/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-01-19 10:18:36
* @Last Modified time: 2019-01-23 14:34:48
*/
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<time.h>
#include<algorithm>
using namespace std;

// isOrder description:判断数组array是否有序(单调非减)
void isOrder(vector<int> array){
	for(int i = 1; i < array.size(); i++){
		if(array[i] < array[i-1]){
			cout<<"False"<<endl;
			return ;
		}
	}
	cout<<"True"<<endl;
	return ;
}

//生成num个介于min与max之间的整数，包含min, max
vector<int> RandArray(int min, int max, int num){
	vector<int> randArray;
    srand(time(NULL));
	for(int i = 0; i < num; i++){
	    int u = min + rand() % (max-min+1);
	    randArray.push_back(u);
	}
	return randArray;
}

int Partition(vector<int> &array, int low, int high){
	int mid = low + (high - low) / 2;
	if(array[low] > array[high])
		swap(array[low], array[high]);
	if(array[mid] > array[high])
		swap(array[mid], array[high]);
	if(array[mid] > array[low])
		swap(array[mid], array[high]);

	int pivot = array[low];
	while(low < high){
		while(low < high && array[high] >= pivot)
			high--;
		array[low] = array[high];
		while(low < high && array[low] <= pivot)
			low++;
		array[high] = array[low];
	}
	array[low] = pivot;
	return low;
}

// 快速排序
void QuickSort(vector<int> &array, int low, int high){
	if(low < high){
		int pivot = Partition(array, low, high);
		QuickSort(array, low, pivot-1);
		QuickSort(array, pivot+1, high);
	}

}
// 堆调整
void HeapAdjust(vector<int> &array, int start, int end){
	int dad = start;
	int son = 2 * dad + 1;
	while(son <= end){
		if(son + 1 <= end && array[son + 1] >= array[son])
			son += 1;
		if(array[dad] >= array[son])
			return ;
		else{
			swap(array[dad], array[son]);
			dad = son;
			son = 2  * dad + 1;
		}
	}
}

// 堆排序
void HeapSort(std::vector<int> &array){
	for(int i = array.size()/2-1; i >= 0; i--){
		HeapAdjust(array, i, array.size()-1);
	}
	for(int j = array.size()-1; j >= 0; j--){
		swap(array[j], array[0]);
		HeapAdjust(array, 0, j-1);
	}
}

// 归并排序
void MergeSort(vector<int> &array){
	int len = array.size();
	vector<int> tmp(len);

	for(int seg = 1; seg <= len; seg *= 2){
		for(int start = 0; start <= len; start += 2 * seg){
			int low = start;
			int mid = min(start+seg-1, len-1);
			int high = min(start+2*seg-1, len-1);

			for(int k = low; k <= high; ++k)
				tmp[k] = array[k];

			int i = low;
			int j = mid + 1;
			int idx = low;
			while(idx <= high){
				if(j > high)
					array[idx++] = tmp[i++];
				else if(i > mid)
					array[idx++] = tmp[j++];
				else if(tmp[i] <= tmp[j])
					array[idx++] = tmp[i++];
				else
					array[idx++] = tmp[j++];
			}
		}
	}
}

// 冒泡排序
void BubbleSort(vector<int> &array){
	for(int i = 0; i < array.size(); i++){
		for(int j = array.size()-1; j > i; j--){
			if(array[j] <= array[j-1])
				swap(array[j], array[j-1]);
		}
	}
}

// 选择排序
void SelectSort(std::vector<int> &array){
	for(int i = 0; i < array.size(); i++){
		int idx = i;
		for(int j=i+1; j < array.size(); j++){
			if(array[j] < array[idx])
				idx = j;
		}
		swap(array[i], array[idx]);
	}
}

// 插入排序
void InsertSort(vector<int> &array){
	if(array.size() <= 1)
		return ;

	for(int i = 1; i < array.size(); ++i){
		if(array[i] < array[i-1]){
			int j = i;
			int tmp = array[i];
			while(j >= 1 && array[j-1] > tmp){
				array[j] = array[j-1];
				--j;
			}
			array[j] = tmp;
		}
	}
}

// 希尔排序
void ShellSort(vector<int> &array){
    int h = 1;
    // 递增序列 1, 4, 13, 40, ...
    while(h < array.size()/3)
        h = 3 * h + 1;

    while(h >= 1){
        for(int i = h; i < array.size(); i++){
            for(int j = i; j >= h; j -= h){
                if(array[j] < array[j-h])
                    swap(array[j], array[j-h]);
            }
        }
        h = h / 3;
    }
}

// main
int main(int argc, char const *argv[]) {
	vector<int> array = RandArray(0, 1000, 200000);
    clock_t start = clock();
	// QuickSort(array, 0, array.size()-1);
	// HeapSort(array);
	// MergeSort(array);
	// BubbleSort(array);
	// SelectSort(array);
	// InsertSort(array);
	// ShellSort(array);
    clock_t end = clock();
    cout << "Sorting time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec" << endl;
	isOrder(array);
	// for(auto it:array)
	// 	cout<<it<<' ';
	cout<<endl;
	return 0;
}
