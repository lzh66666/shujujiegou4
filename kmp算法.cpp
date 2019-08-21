#include <iostream>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define MAXSTRLEN 255//���ĳ�ʼ���� 

typedef char SString[MAXSTRLEN+1];//0�ŵ�Ԫ��Ŵ��ĳ��� 
typedef int Status;

void get_next(SString T,Status next[]);
Status StrAssign(SString T,char *chars);
void StrPrint(SString T);

int Index_KMP(SString S,SString T,Status pos);//�Ľ��� 
void get_nextval(SString T,Status nextval[]);//�Ľ�next���麯���� 


int main(int argc, char** argv) 
{
	char s[256],t[256];
	Status pos;
	SString S,T;
	
	printf("�������ַ���S��\n");
	gets(s);
	StrAssign(S,s);
//	printf("����ַ���S��\n");
//	StrPrint(S); 
	
	printf("�������ַ���T��\n"); 
	gets(t);
	StrAssign(T,t);
//	printf("����ַ���T��\n");
//	StrPrint(T);
	
	printf("������λ��(��pos���ַ�֮��):\n");
	scanf("%d",&pos);
	printf("ģʽ��T������S��λ��Ϊ%d\n",Index_KMP(S,T,pos));
	
/*	printf("�����봮T:\n");
	gets(s);
	StrAssign(T,s);
	
	int next[100];
//	ababaaababaa
	get_nextval(T,next);
	for(int i=1;i<=13;i++){
		printf("%d ",next[i]);
	}*/
	return 0;
}

Status StrAssign(SString T,char *chars)
{
	//����һ����ֵ����chars�Ĵ�T
	Status i;
	if(strlen(T)>MAXSTRLEN)
	{
		return ERROR;
	} 
	else
	{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++)
		{
			T[i]=*(chars+i-1);
		}
		return OK;
	}
} 
void StrPrint(SString T)
{
	//����ַ���T
	Status i;
	printf("%d ",T[0]);
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	} 
	printf("\n");
}

int Index_KMP(SString S,SString T,Status pos)
{
	//����ģʽ��T��next���麯����T������S�еĵ�pos���ַ�֮���λ��
	int nextval[100];
	int i=pos,j=1;
	get_nextval(T,nextval);
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j])//�����ȽϺ���ַ�ģʽ�������ƶ� 
		{
			++i;
			++j;
		}
		else
			j=nextval[j]; 
	} 
	if(j>T[0])
		return i-T[0];
	else
		return ERROR;
} 

void get_nextval(SString T,Status nextval[])//�Ľ�next���麯���� 
{
	//��ģʽ����T��next��������ֵ����������nextval��
	Status i=1,j; 
	nextval[1]=0;
	j=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			if(T[i]!=T[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}
		else
			j=nextval[j];
	}
}

