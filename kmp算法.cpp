#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0 

#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN + 1];

typedef int Status;

Status StrAssign(SString &T,char *chars);  //���ɴ�  
Status Print(SString T);  //����� 
int index_KMP(SString S,SString T,int pos);
void get_next(SString T,int *next);

int main(int argc, char** argv) {
	SString S,T;
	int pos,i;
	char chars[1000],chars1[1000];
	
	printf("�����봮S:\n");
	gets(chars1);
	StrAssign(S,chars1);
	Print(S);
	
	printf("�����봮T:\n");
	gets(chars);
	StrAssign(T,chars);
	Print(T);
	
	printf("������Ҫ�صڼ�λ��ʼ����:\n");
	scanf("%d",&pos);
	i=index_KMP(S,T,pos);
	printf("�ڵ�%dλ",i);
	
	/*printf("�����봮T:\n");
	gets(chars);
	StrAssign(T,chars);
	Print(T);
	
	int next[100];
//	ababaaababaa
	get_next(T,next);
	for(int i=1;i<=12;i++){
		printf("%d ",next[i]);
	}*/
	
	return 0;
}

Status StrAssign(SString &T,char *chars)
{
	//����һ����ֵΪchars�Ĵ�T
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

Status Print(SString T)
{
	int i;
	printf("%d ",T[0]);
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	}
	printf("\n");
	return OK;
}

int index_KMP(SString S,SString T,int pos)
{
	int next[100];
	int i,j;
    i=pos,j=1;
    get_next(T,next);
	while(i<=S[0] && j<=T[0])
	{
		if(j==0 || S[i]==T[j])
		{
			++i;
			++j;
		}
		else
			j=next[j];
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}

void get_next(SString T,int *next)
{
	int i=1,j=0;
	next[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
		{
			j=next[j];
		}
	}
}
