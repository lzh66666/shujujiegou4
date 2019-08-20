#include <iostream>
#include <stdlib.h>
#include <string.h> 
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int Status; 

typedef struct{
	char *ch;    //若是空串，则按串长分配存储区，否则ch为NULL 
	int length;  //串长度 
}HString;
 
Status StrAssign(HString &T,char *chars);   //生成一个其值等于串常量chars的串T
Status StrPrint(HString T);                //输出串
int Strlength(HString S);                  //串的长度 
int StrCompare(HString S,HString T);       //比较两个字符串的大小 
Status ClearString(HString &S);            //将串清空 
Status Concat(HString &T,HString S1,HString S2);//将两个字符串连接 
Status StrInsert(HString &S,int pos,HString T);//在主串中插入子串 
Status SubString(HString &Sub,HString S,int pos,int len); //取子串 
int index(HString S,HString T,int pos);      //求主串中第一次出现子串的位置 
Status replace(HString &S,HString T,HString V);  //取代主串中的某个子串 
 
int main(int argc, char** argv) {
	HString S1,S2,T;
	char chars[1000],chars1[1000],chars2[1000],chars3[1000],chars4[1000],chars5[1000];
	int pos,len,n,i;
	T.ch=(char *)malloc(sizeof(char)); 
	S1.ch=(char *)malloc(sizeof(char)); 
	S2.ch=(char *)malloc(sizeof(char));
	/*
	printf("\n-------------------------\n");
	printf("请输入串chars的字符:\n");
	gets(chars);
	printf("生成一个值等于常量chars的串S1:\n"); 
	StrAssign(S1,chars);
	StrPrint(S1);
	
	printf("\n-------------------------\n");
	printf("再次输入串chars的字符:\n");
	gets(chars1);
	printf("生成一个值等于常量chars的串S2:\n"); 
	StrAssign(S2,chars1);
	StrPrint(S2);
	
	printf("\n-------------------------\n");
	
	printf("S1和S2比较后的结果为:"); 
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
	
	printf("S1和S2连接之后新串T为:\n");
	Concat(T,S1,S2);
	StrPrint(T);
	*/
	printf("\n-------------------------\n");
	gets(chars1);
	StrAssign(T,chars1);
	printf("请输入要代替T的子字符串:\n");
	gets(chars2);
	StrAssign(S1,chars2);
	printf("请输入替换的字符串:\n");
	gets(chars3);
	StrAssign(S2,chars3);
	replace(T,S1,S2);
	printf("T的新字符串为:\n");
	StrPrint(T); 
		
	printf("\n-------------------------\n");
	/*	
	printf("请输入要在T中查找新字符串Sub:\n");
	gets(chars4);
	StrAssign(S1,chars4);
	StrPrint(S1); 
	printf("输入你希望查找的位置:\n");
	scanf("%d",&i); 
	n=index(T,S1,i);
	if(n)
		printf("找到了并且位置为第%d位\n",n);
	else
		printf("T中第%d位之后没有该子串",i);
		
		
		
	printf("\n-------------------------\n");
	
	
	printf("请输入要截取T的位置和长度:\n");
	scanf("%d%d",&pos,&len);
	SubString(S1,T,pos,len);
	printf("截取的串sub为:\n");
	StrPrint(S1);
	
	printf("\n-------------------------\n");
	
	printf("在主串中插入字符串:\n");
	printf("请输入在主串中插入的位置:\n");
	scanf("%d",&pos);
	printf("请输入要插入的字符串:");
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
 		free(T.ch);//释放旧空间
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
		for(int i=S.length-1;i>=pos-1;--i)//为插入T而腾出空间 
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
		free(Sub.ch);		//释放旧空间 
	if(!len)
	{
		Sub.ch=NULL;
		Sub.length=0;		//空子串 
	}
	else					//完整子串 
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
			return i;		//返回子串在子串中的位置 
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
	while(pos<=n-m+1 && i)	//循环 
	{
		i=index(S,T,pos);	//在S中定位子串T的位置 
		if(i!=0)			//定位成功 
		{
			SubString(Sub,S,pos,i-pos);//取S中保留的子串
			Concat(news,news,Sub);//连接
			Concat(news,news,V);
			pos=i+m;			//下一次定位的位置 
		}
	}
	SubString(Sub,S,pos,n-pos+1);//剩余串
	Concat(S,news,Sub); 
	return OK;
 } 
