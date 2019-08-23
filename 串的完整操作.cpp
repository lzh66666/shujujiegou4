#include <stdlib.h>	
#include <stdio.h>		
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
 
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;
 
//ElemType是元素类型
typedef int ElemType;
 
//ElemType是元素类型
typedef char AtomType;
 
//Boolean是布尔类型,其值是TRUE或FALSE
typedef int Boolean;
 
//串的定长顺序表示
#define MAXSTRLEN 100
 
typedef unsigned char SString[MAXSTRLEN+1];			//0号单元存放串的长度
 
//生成一个其值等于chars的串T
Status StrAssign(SString &T , char *chars)
{
	int i;
	if(strlen(chars) > MAXSTRLEN) 
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for(i = 1 ; i <= T[0] ; i++)
			T[i] = *(chars+i-1);
		return OK;
	}
}
 
//由串S复制得串T
Status StrCopy(SString &T , SString S)
{
	int i;
	for(i = 0 ; i <= S[0] ; i++)
		T[i] = S[i];
	return OK;
}
 
//若S为空串，则返回TRUE，否则返回FALSE
Status StrEmpty(SString S)
{
	if(S[0] == 0)
		return TRUE;
	else
		return FALSE;
}
 
//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
int StrCompare(SString S , SString T)
{
	int i;
	for(i = 1 ; i <= S[0] && i <= T[0] ; i++)
		if(S[i] != T[i]) 
			return S[i] - T[i];
	return S[0]-T[0];
}
 
//返回S的元素个数
int StrLength(SString S)
{
	return S[0];
}
 
//将S清为空串
Status ClearString(SString &S)
{
	S[0] = 0;		//令串长为0
	return OK;
}
 
//用T返回由S1和S2连接而成的新串
Status Concat(SString &T , SString S1 , SString S2)
{
	int i;
	if(S1[0]+S2[0] <= MAXSTRLEN)
	{	//未截断
		T[0] = S1[0]+S2[0];
		for(i = 1 ; i <= S1[0] ; i++)
			T[i] = S1[i];
		for(i = 1 ; i <= S2[0] ; i++)
			T[i+S1[0]] = S2[i];
		return TRUE;
	}
	else
	{	//截断S[2]
		for(i = 1 ; i <= S1[0] ; i++)
			T[i] = S1[i];
		for(i = 1 ; i <= (MAXSTRLEN-S1[0]) ; i++)
			T[i+S1[0]] = S2[i];
		T[0] = MAXSTRLEN;
		return OK;
	}
}
 
//用Sub返回串S的第pos个字符起长度为len的子串
Status SubString(SString &Sub , SString S , int pos , int len)
{
	int i;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)
		return ERROR;
	for(i = 1 ; i <= len ; i++)
		Sub[i] = S[i+pos-1];	//注意此处是S[i+pos-1]，从第pos个字符
	Sub[0] = len;
	return OK;
}
 
//若主串S中存在和串T值相同的子串，则返回它在主串S中第pos个字符之后第一次出现的位置；否则函数值为0
int Index(SString S , SString  T , int pos)
{
	int i , j;
	if(pos >= 1 || pos <= S[0])
	{
		i = pos;
		j = 1;
		while(i <= S[0] && j <= T[0])
		{
			if(S[i] == T[j])		//继续比较后继字符
			{
				++i;
				++j;
			}
			else					//指针后退重新开始匹配
			{
				i = i-j+2;
				j = 1;
			}
		}
		if(j > T[0])
			return i - T[0];
		else
			return 0;
	}
	else
		return 0;
}
 
void get_next(SString T , int next[])
{
	int i = 1,j = 0 ;
	next[1] = 0;
	while(i < T[0])
	{
		if(j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
 
void get_nextval(SString T , int next[])
{
	int i = 1 , j = 0;
	next[1] = 0;
	while(i < T[0])
	{
		if(j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			if(T[i] != T[j]) next[i] = j;
			else next[i] = next[j];
		}
		else j = next[j];
	}
}
int Index_KMP(SString S , SString T , int pos)
{
	int next[100];
	int i = pos , j = 1;
	get_nextval(T,next);
	while(i <= S[0] && j <= T[0])
	{
		if(j == 0 || S[i] == T[j]) {++i; ++j;}
		else j = next[j];
	}
	if(j > T[0]) return i - T[0];
	else return 0;
}
 
//在串S的第pos个字符之前插入串T
Status StrInsert(SString &S , int pos , SString T)
{
	int i;
	if(pos < 1 || pos > S[0]+1) return ERROR;
	if(S[0]+T[0] <= MAXSTRLEN)		//完全插入
	{
		for(i = S[0] ; i >= pos ; i--)
			S[i+T[0]] = S[i];
		for(i = pos ; i <= (pos+T[0]) ; i++)
			S[i] = T[i-pos+1];
		S[0] += T[0];
		return OK;
	}
	else		//部分插入
	{
		for(i = MAXSTRLEN ; i <= pos ; i--)
			S[i] = S[i-T[0]];
		for(i = pos ; i <= pos+T[0] ; i++)
			S[i] = T[i-pos+1];
		S[0] = MAXSTRLEN;
		return FALSE;
	}
}
 
//从串中删除第pos个字符开始的长度为len的字符
Status StrDelete(SString &S , int pos , int len)
{
	int i;
	if(pos < 1 || pos > S[0]-len+1 || len < 0) return ERROR;
	for(i = pos+len ; i <= S[0] ; i++)
		S[i-len] = S[i];
	S[0] -= len;
	return OK;
}
 
//用V替换主串S中出现的所有与T相等的不重叠的子串
Status Replace(SString &S , SString T , SString V)
{
	int i = 1;		//从串S的第一个字符起查找串T
	if(StrEmpty(T)) return ERROR;
	do
	{
		i = Index(S , T , i);		//结果i为从上一个i之后找到的子串T的位置
		if(i)			//串S中存在串T
		{
			StrDelete(S , i , StrLength(T));		//删除该串T
			StrInsert(S , i , V);					//在原串T的位置插入串V
			i += StrLength(V);						//在插入的串V后面继续查找串T
		}
	}while(i);
	return OK;
}
 
//输出字符串T。另加
 void StrPrint(SString T)
 {
   int i;
   for(i=1;i<=T[0];i++)
     printf("%c",T[i]);
   printf("\n");
 }
 
 int main (int argc,char**argv){
 	
 	return 0;
 }
