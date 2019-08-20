#include <iostream>
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
Status Concat(SString &T,SString S1,SString S2);   //�ַ������� 
Status SubString(SString &sub,SString S,int pos,int len);   //���Ӵ� 
Status Print(SString &T);  //����� 


int main(int argc, char** argv) {
	SString S1,S2,T;
	int n,pos,len;
	
	char chars1[MAXSTRLEN];
	char chars2[MAXSTRLEN];
	
	printf("�����봮S1:\n");
	gets(chars1);
	StrAssign(S1,chars1); 
	Print(S1);
	printf("�����봮S2:\n");
	gets(chars2);
	StrAssign(S2,chars2);
	Print(S2);
	printf("S1��S2���Ӻ���´�Ϊ:\n");
	Concat(T,S1,S2);
	Print(T);
	printf("�������ȡ��S1��λ�úͳ���:\n");
	scanf("%d%d",&pos,&len);
	SubString(T,S1,pos,len);
	Print(T); 
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

Status Print(SString &T)
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

Status Concat(SString &T,SString S1,SString S2)
{
	Status uncut;
	int i;
	if(S1[0]+S2[0]<=MAXSTRLEN)//δ�ض� 
	{
		for(i=1;i<=S1[0];i++)
		{
			T[i]=S1[i];
		}
		for(i=1;i<=S2[0];i++)
		{
			T[S1[0]+i]=S2[i];
		}
		T[0]=S1[0]+S2[0];
		uncut=TURE;
	}
	
	else if(S1[0]<MAXSTRLEN)//�ض� 
	{
		for(i=1;i<=S1[0];i++)
		{
			T[i]=S1[i];
		} 
		for(i=1;i<=MAXSTRLEN-S1[0];i++)
		{
			T[S1[0]+i]=S2[i];
		}
		T[0]=MAXSTRLEN;
		uncut=FALSE;
	}
	else				//�ض� 
	{
		for(i=0;i<=MAXSTRLEN;i++)
		{
			T[i]=S1[i];
		} 
		uncut=FALSE;
	}
	return uncut;
}

Status SubString(SString &Sub,SString S,int pos,int len)
{
	int i;
	if(pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1)
		return ERROR;
	for(i=1;i<=len;i++)
	{
		Sub[i]=S[pos-1+i];
	}
	Sub[0]=len;
	return OK;
}






