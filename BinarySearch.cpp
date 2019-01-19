#include<iostream>
#include<vector>
using namespace std;

bool BinarySearch(vector<int> &array, int target){
	int low = 0;
	int high = array.size()-1;
	while(low <= high){
		int mid = low + (high - low)/2;
		if(array[mid] == target)
			return true;
		else if(array[mid] > target)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	vector<int> a = {2, 3, 4, 6, 8, 10, 14, 17, 28, 29, 30, 34};
	int target = 10;
	cout<<BinarySearch(a, target)<<endl;
	return 0;
}
