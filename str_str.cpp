/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-01-18 11:20:11
* @Last Modified time: 2019-01-23 14:34:20
*/
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;

/**
 * 方法1. 暴力求kmp* 方法2. KMP_next
 * 方法3. Sunday
 */

/**
 * brute_force description:
 * 暴力求解，在字符串s中匹配字符串p
 * @param  t [text, 文本串]
 * @param  p [pattern, 模式串]
 * @return   [若s含有p, 则返回第一个匹配的位置，否则，返回-1]
 */
int brute_force(string t, string p){
	int t_size = t.length();
	int p_size = p.length();
	if(t_size == p_size && t_size == 0)
		return 0;
	if(t_size < p_size)
		return -1;

	int head = 0;
	int i = head;
	int j = 0;
	while(i < t_size && j < p_size){
		if(t[i] == p[j]){
			i++;
			j++;
			if(j == p_size && i <= t_size)
				return head;
		}
		else{
			head++;
			i = head;
			j = 0;
		}
	}
	return -1;
}

// 暴力求解的另一种写法
int brute_force2(string t, string p){
	int t_size = t.length();
	int p_size = p.length();

	if(t_size == p_size && t_size == 0)
		return 0;
	if(t_size < p_size)
		return -1;

	int i, j;
	for(i = 0, j = 0; i < t_size && j < p_size; i++){
		if(t[i] == p[j]){
			j++;
		}
		else{
			i -= j;
			j = 0;
		}
	}
	if(j == p_size) // 找到匹配
		return i - j;
	else // 为找到匹配
		return -1;
}

/**
 * ParticalMatchTable description：
 * 对字符串p生成next数组
 * @param p    [pattern string]
 * @param next [next数组]
 */
void ParticalMatchTable(string p, int next[]){
	int i = 0;
	int j = -1;
	next[0] = -1;

	while(i < p.length()){
		if(j == -1 || p[i] == p[j]){
			i++;
			j++;
			next[i] = j;
		}
		else{
			j = next[j];
		}
	}
}

/**
 * kmp algorithm based on next
 * kmp_next algorithm
 * @param  t [text string]
 * @param  p [pattern string]
 * @return   [若s含有p, 则返回第一个匹配的位置，否则，返回-1]
 */
int kmp_next(string t, string p){
	int t_size = t.length();
	int p_size = p.length();
	int next[p_size];
	ParticalMatchTable(p, next);

	int i = 0;
	int j = 0;
	while(i < t_size && j < p_size){
		if(j == -1 || t[i] == p[j]){
			i++;
			j++;
		}
		else{
			j = next[j];
		}
	}
	if(j == p_size)
		return i-j;
	else
		return -1;
}

/*kmp algorithm based on dfa */
int kmp_dfa(string t, string p){
	int row = 256;
	int col = p.length();

	// 动态分配数组并初始化
    int** dfa = new int*[row];
	for(int i = 0; i < row; i++)
		dfa[i] = new int[col];
	for(int i = 0 ; i < row ; i++)
		for(int j = 0; j < col; j++)
			dfa[i][j] = 0;

	// 计算dfa
	dfa[p[0]][0] = 1;
	for (int j = 1, x = 0; j < col; ++j) {
		for (int i = 0; i < row; ++i)
			dfa[i][j] = dfa[i][x];
		dfa[p[j]][j] = j + 1;
		x = dfa[p[j]][x];
	}

	//	kmp algo
	int i, j;
	int t_size = t.length();
	int p_size = p.length();
	for (i = 0, j = 0; i < t_size && j < p_size; i++){
	      j = dfa[t[i]][j];
	}
	if(j == p_size)
		return i-j;
	else
		return -1;
}

/**
 * [Sunday description]
 * @param  t [description]
 * @param  p [description]
 * @return   [description]
 */
int Sunday(string t, string p){
	int t_size = t.length();
	int p_size = p.length();
	if(p_size == t_size && t_size == 0)
		return 0;
	if(p_size < 0 || t_size < 0)
		return -1;

	int i = 0;
	int j = 0;
	int k;
	int m = p_size;
	while(i < t_size){
		if(t[i] != p[j]){
			for(k = p_size-1; k >= 0; --k){
				if(p[k] == t[m])
					break;
			}
			i = m - k;
			j = 0;
			m = i + p_size;
		}
		else{
			i++;
			j++;
			if(j == p_size)
				return i-j;
		}
	}
	return -1;
}

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[])
{
	string t = "bbc abcdab abcdabcdabde";
	string p = "abcdabd";
	// brute force
	cout<<"brute_force : "<<brute_force(t, p)<<endl;
	// kmp_next
	cout<<"kmp_next : "<<kmp_next(t, p)<<endl;
	// kmp_dfa
	cout<<"kmp_dfa : "<<kmp_dfa(t, p)<<endl;
	// Sunday
	cout<<"Sunday : "<<Sunday(t, p)<<endl;
    cout<<endl;
	return 0;
}
