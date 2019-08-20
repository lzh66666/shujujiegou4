#include <iostream>
#include <stdlib.h>
#include <string.h> 
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int Status; 

typedef struct{
	char *ch;    //���ǿմ����򰴴�������洢��������chΪNULL 
	int length;  //������ 
}HString;
 
Status StrAssign(HString &T,char *chars);   //����һ����ֵ���ڴ�����chars�Ĵ�T
Status StrPrint(HString T);                //�����
int Strlength(HString S);                  //���ĳ��� 
int StrCompare(HString S,HString T);       //�Ƚ������ַ����Ĵ�С 
Status ClearString(HString &S);            //������� 
Status Concat(HString &T,HString S1,HString S2);//�������ַ������� 
Status StrInsert(HString &S,int pos,HString T);//�������в����Ӵ� 
Status SubString(HString &Sub,HString S,int pos,int len); //ȡ�Ӵ� 
int index(HString S,HString T,int pos);      //�������е�һ�γ����Ӵ���λ�� 
Status replace(HString &S,HString T,HString V);  //ȡ�������е�ĳ���Ӵ� 
 
int main(int argc, char** argv) {
	HString S1,S2,T;
	char chars[1000],chars1[1000],chars2[1000],chars3[1000],chars4[1000],chars5[1000];
	int pos,len,n,i;
	T.ch=(char *)malloc(sizeof(char)); 
	S1.ch=(char *)malloc(sizeof(char)); 
	S2.ch=(char *)malloc(sizeof(char));
	/*
	printf("\n-------------------------\n");
	printf("�����봮chars���ַ�:\n");
	gets(chars);
	printf("����һ��ֵ���ڳ���chars�Ĵ�S1:\n"); 
	StrAssign(S1,chars);
	StrPrint(S1);
	
	printf("\n-------------------------\n");
	printf("�ٴ����봮chars���ַ�:\n");
	gets(chars1);
	printf("����һ��ֵ���ڳ���chars�Ĵ�S2:\n"); 
	StrAssign(S2,chars1);
	StrPrint(S2);
	
	printf("\n-------------------------\n");
	
	printf("S1��S2�ȽϺ�Ľ��Ϊ:"); 
	n=StrCompare(S1,S2);
	if(n>0)
	{
		printf("S1>S2\n");
	}
	else if(n==0)
	{
		printf("S1=S2\n");
	}
	else
	{
		printf("S1<S2\n");
	}
	
	printf("\n-------------------------\n");
	
	printf("S1��S2����֮���´�TΪ:\n");
	Concat(T,S1,S2);
	StrPrint(T);
	*/
	printf("\n-------------------------\n");
	gets(chars1);
	StrAssign(T,chars1);
	printf("������Ҫ����T�����ַ���:\n");
	gets(chars2);
	StrAssign(S1,chars2);
	printf("�������滻���ַ���:\n");
	gets(chars3);
	StrAssign(S2,chars3);
	replace(T,S1,S2);
	printf("T�����ַ���Ϊ:\n");
	StrPrint(T); 
		
	printf("\n-------------------------\n");
	/*	
	printf("������Ҫ��T�в������ַ���Sub:\n");
	gets(chars4);
	StrAssign(S1,chars4);
	StrPrint(S1); 
	printf("������ϣ�����ҵ�λ��:\n");
	scanf("%d",&i); 
	n=index(T,S1,i);
	if(n)
		printf("�ҵ��˲���λ��Ϊ��%dλ\n",n);
	else
		printf("T�е�%dλ֮��û�и��Ӵ�",i);
		
		
		
	printf("\n-------------------------\n");
	
	
	printf("������Ҫ��ȡT��λ�úͳ���:\n");
	scanf("%d%d",&pos,&len);
	SubString(S1,T,pos,len);
	printf("��ȡ�Ĵ�subΪ:\n");
	StrPrint(S1);
	
	printf("\n-------------------------\n");
	
	printf("�������в����ַ���:\n");
	printf("�������������в����λ��:\n");
	scanf("%d",&pos);
	printf("������Ҫ������ַ���:");
	gets(chars5);
	StrAssign(S1,chars5);
	StrInsert(T,pos,S1);
	StrPrint(T);
	printf("\n-------------------------\n");
	*/
	return 0;
}

Status StrAssign(HString &T,char *chars){
	
	int i=0,j;
	
	char *c=chars;
	if(T.ch)
		free(T.ch);
	for(i=0;*c;++i,++c); 
	if(!i)
	{
		T.ch=NULL;
		T.length=0;
	} 
	else
	{
		T.ch=(char *)malloc(i*sizeof(char));
		if(T.ch==NULL)
			exit(OVERFLOW);
		for(j=0;j<i;j++)
		{
			T.ch[j]=chars[j];
		}
		T.length=i;
	}
	
	return OK;
}


Status StrPrint(HString T)
{
	for(int i=0;i<T.length;i++)
	{
		printf("%c",T.ch[i]);
	} 
	printf("\n");
	return OK;
}

int Strlength(HString S)
{
	return S.length;
} 

int StrCompare(HString S,HString T)
{
	int i;
	for(i=0;i<S.length && i<T.length;++i)
	{
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
 } 

Status ClearString(HString &S)
{
	if(S.ch)
	{
		free(S.ch);
		S.ch=NULL;
	}
	S.length=0;
	return OK;
 } 
 
Status Concat(HString &T,HString S1,HString S2)
{
	int i;
 	if(T.ch)
 		free(T.ch);//�ͷžɿռ�
	T.ch=(char *)malloc((S1.length+S2.length)*sizeof(char));
	if(T.ch==NULL)
		exit(OVERFLOW);
	for(i=0;i<S1.length;i++)
	{
		T.ch[i]=S1.ch[i];
	}
	T.length=S1.length+S2.length;	
	for(i=0;i<S2.length;i++)
	{
		T.ch[S1.length+i]=S2.ch[i];
	}
	
	return OK; 
} 

Status StrInsert(HString &S,int pos,HString T)
{
	if(pos<1 || pos>S.length+1)
		return ERROR;
	if(T.length){
		S.ch=(char *)realloc(S.ch,(S.length+T.length)*sizeof(char *));
		if(!S.ch)
			exit(OVERFLOW);
		for(int i=S.length-1;i>=pos-1;--i)//Ϊ����T���ڳ��ռ� 
		{
			S.ch[i+T.length]=S.ch[i];
		}
		for(int i=0;i<=T.length-1;i++)
		{
			S.ch[pos-1+i]=T.ch[i];
		}
		S.length+=T.length; 
	}
	return OK;
 } 

Status SubString(HString &Sub,HString S,int pos,int len)
{
	if(pos<1 || pos>S.length ||len<0 || len>S.length-pos+1)
		return ERROR;
	if(Sub.ch)
		free(Sub.ch);		//�ͷžɿռ� 
	if(!len)
	{
		Sub.ch=NULL;
		Sub.length=0;		//���Ӵ� 
	}
	else					//�����Ӵ� 
	{
		Sub.ch=(char *)malloc(len*sizeof(char));
		for(int i=0;i<len;i++)
		{
		 	Sub.ch[i]=S.ch[pos-1+i];
		}
		Sub.length=len; 
	}
	return OK;
 } 

int index(HString S,HString T,int pos)
{
	int n,m,i;
	HString Sub;
	
	if(pos>0){
		n=Strlength(S);
		m=Strlength(T);
		i=pos;
	}
	Sub.ch=(char *)malloc(m*sizeof(char));
	while(i<=n-m+1){
		SubString(Sub,S,i,m);
		if(StrCompare(Sub,T)!=0)
			++i;
		else
			return i;		//�����Ӵ����Ӵ��е�λ�� 
	}
	return 0;
 } 



Status replace(HString &S,HString T,HString V)
{
	int n,m,i=1;
	HString Sub,news;
	int pos=1;
	n=S.length;
	m=T.length;
	news.ch=(char *)malloc(sizeof(char));
	news.length=0;
	Sub.ch=(char *)malloc(m*sizeof(char));
	while(pos<=n-m+1 && i)	//ѭ�� 
	{
		i=index(S,T,pos);	//��S�ж�λ�Ӵ�T��λ�� 
		if(i!=0)			//��λ�ɹ� 
		{
			SubString(Sub,S,pos,i-pos);//ȡS�б������Ӵ�
			Concat(news,news,Sub);//����
			Concat(news,news,V);
			pos=i+m;			//��һ�ζ�λ��λ�� 
		}
	}
	SubString(Sub,S,pos,n-pos+1);//ʣ�മ
	Concat(S,news,Sub); 
	return OK;
 } 
