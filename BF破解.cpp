#include <iostream>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define MAXSTRLEN 225

typedef int Status;
typedef unsigned char SString[MAXSTRLEN+1];

Status StrAssign(SString &T,char *chars);
int Index(SString S,SString T,int pos); 

int main(int argc, char** argv) {
	SString S,T;
	int pos,i;
	char chars1[1000],chars2[1000];
	
	printf("请输入字符串S:\n");
	gets(chars1);
	StrAssign(S,chars1);
	printf("请输入字符串T:\n");
	gets(chars2);
	StrAssign(T,chars2);
	
	printf("请输入在第几个字符开始查找:\n");
	scanf("%d",&pos);
	i=Index(S,T,pos);
	if(i) 
		printf("在第%d位\n",i);
	else
		printf("不能匹配!"); 
	return 0;
}

Status StrAssign(SString &T,char *chars)
{
	//生成一个其值为chars的串T
	if(strlen(chars) > MAXSTRLEN)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for(int i = 1; i <= T[0]; ++i)
		{
			T[i] = chars[i-1];
		}
	}
	return OK;
}

int Index(SString S,SString T,int pos){
	//返回子串T在主串S中第pos个字符之后的位置.若不存在,则函数值为0 
	int i=pos,j=1;
	while(i<=S[0] && j<=T[0])
	{
		if(S[i]==T[j]){		//继续比较后继字符 
			i++;
			j++;
		}
		else{				//指针后退并重新开始匹配 
			i=i-j+2;		//i=i-(j-1)+1 
			j=1;
		}
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}
