/*
* @Author: z.c.wang
* @Email:  iwangzhengchao@gmail.com
* @Date:   2019-01-18 11:20:11
* @Last Modified time: 2019-01-18 20:12:17
*/
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;

/**
 * 方法1. 暴力求解
 * 方法2. KMP
 * 方法3. Sunday
 */

/**
 * str_str description:
 * 暴力求解，在字符串s中匹配字符串p
 * @param  t [text, 长串]
 * @param  p [pattern, 模式串]
 * @return   [若s含有p, 则返回第一个匹配的位置，否则，返回-1]
 */
int str_str(string t, string p){
	int t_size = t.length();
	int p_size = p.length();
	if(t_size ==p_size && t_size == 0)
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
 * [KMP description]
 * KMP algorithm
 * @param  t [text string]
 * @param  p [pattern string]
 * @return   [若s含有p, 则返回第一个匹配的位置，否则，返回-1]
 */
int KMP(string t, string p){
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
	string s = "bbc abcdab abcdabcdabde";
	string p = "abcdabd";
	// 朴素匹配
	cout<<"position : "<<str_str(s, p)<<endl;
	// KMP
	cout<<"KMP :"<<KMP(s, p)<<endl;
	// Sunday
	cout<<"Sunday :"<<Sunday(s, p)<<endl;
    cout<<endl;
	return 0;
}
