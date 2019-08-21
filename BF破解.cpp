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
	
	printf("�������ַ���S:\n");
	gets(chars1);
	StrAssign(S,chars1);
	printf("�������ַ���T:\n");
	gets(chars2);
	StrAssign(T,chars2);
	
	printf("�������ڵڼ����ַ���ʼ����:\n");
	scanf("%d",&pos);
	i=Index(S,T,pos);
	if(i) 
		printf("�ڵ�%dλ\n",i);
	else
		printf("����ƥ��!"); 
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

int Index(SString S,SString T,int pos){
	//�����Ӵ�T������S�е�pos���ַ�֮���λ��.��������,����ֵΪ0 
	int i=pos,j=1;
	while(i<=S[0] && j<=T[0])
	{
		if(S[i]==T[j]){		//�����ȽϺ���ַ� 
			i++;
			j++;
		}
		else{				//ָ����˲����¿�ʼƥ�� 
			i=i-j+2;		//i=i-(j-1)+1 
			j=1;
		}
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}
