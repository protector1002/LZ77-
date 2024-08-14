#pragma once
#include<iostream>
#include<string>
//用来重命名要在工程中用到的类型和定义常量
using std::cout;
using std::endl;
using std::cin;
using std::string;
 
typedef unsigned char uch;
typedef unsigned short ush;
typedef unsigned long long ull;
//加上static防止多个文件同时包含而导致变量重复定义
static const int MAX_ATHCH = 258;//最大匹配长度
static const int MIN_MATCH = 3;//最小匹配长度
 
static const ush WSIZE = 32 * 1024;//窗口大小
 
static const ush MIN_LOOKAHEAD = MIN_MATCH + MAX_ATHCH + 1;//先行缓冲区至少要预留长度
static const ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;//查找缓冲区最大距离：向左侧查找的最远距离。