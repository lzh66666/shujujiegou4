#include <stdlib.h>	
#include <stdio.h>		
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
 
//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
 
//ElemType��Ԫ������
typedef int ElemType;
 
//ElemType��Ԫ������
typedef char AtomType;
 
//Boolean�ǲ�������,��ֵ��TRUE��FALSE
typedef int Boolean;
 
//���Ķ���˳���ʾ
#define MAXSTRLEN 100
 
typedef unsigned char SString[MAXSTRLEN+1];			//0�ŵ�Ԫ��Ŵ��ĳ���
 
//����һ����ֵ����chars�Ĵ�T
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
 
//�ɴ�S���Ƶô�T
Status StrCopy(SString &T , SString S)
{
	int i;
	for(i = 0 ; i <= S[0] ; i++)
		T[i] = S[i];
	return OK;
}
 
//��SΪ�մ����򷵻�TRUE�����򷵻�FALSE
Status StrEmpty(SString S)
{
	if(S[0] == 0)
		return TRUE;
	else
		return FALSE;
}
 
//��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
int StrCompare(SString S , SString T)
{
	int i;
	for(i = 1 ; i <= S[0] && i <= T[0] ; i++)
		if(S[i] != T[i]) 
			return S[i] - T[i];
	return S[0]-T[0];
}
 
//����S��Ԫ�ظ���
int StrLength(SString S)
{
	return S[0];
}
 
//��S��Ϊ�մ�
Status ClearString(SString &S)
{
	S[0] = 0;		//���Ϊ0
	return OK;
}
 
//��T������S1��S2���Ӷ��ɵ��´�
Status Concat(SString &T , SString S1 , SString S2)
{
	int i;
	if(S1[0]+S2[0] <= MAXSTRLEN)
	{	//δ�ض�
		T[0] = S1[0]+S2[0];
		for(i = 1 ; i <= S1[0] ; i++)
			T[i] = S1[i];
		for(i = 1 ; i <= S2[0] ; i++)
			T[i+S1[0]] = S2[i];
		return TRUE;
	}
	else
	{	//�ض�S[2]
		for(i = 1 ; i <= S1[0] ; i++)
			T[i] = S1[i];
		for(i = 1 ; i <= (MAXSTRLEN-S1[0]) ; i++)
			T[i+S1[0]] = S2[i];
		T[0] = MAXSTRLEN;
		return OK;
	}
}
 
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
Status SubString(SString &Sub , SString S , int pos , int len)
{
	int i;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)
		return ERROR;
	for(i = 1 ; i <= len ; i++)
		Sub[i] = S[i+pos-1];	//ע��˴���S[i+pos-1]���ӵ�pos���ַ�
	Sub[0] = len;
	return OK;
}
 
//������S�д��ںʹ�Tֵ��ͬ���Ӵ����򷵻���������S�е�pos���ַ�֮���һ�γ��ֵ�λ�ã�������ֵΪ0
int Index(SString S , SString  T , int pos)
{
	int i , j;
	if(pos >= 1 || pos <= S[0])
	{
		i = pos;
		j = 1;
		while(i <= S[0] && j <= T[0])
		{
			if(S[i] == T[j])		//�����ȽϺ���ַ�
			{
				++i;
				++j;
			}
			else					//ָ��������¿�ʼƥ��
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
 
//�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
Status StrInsert(SString &S , int pos , SString T)
{
	int i;
	if(pos < 1 || pos > S[0]+1) return ERROR;
	if(S[0]+T[0] <= MAXSTRLEN)		//��ȫ����
	{
		for(i = S[0] ; i >= pos ; i--)
			S[i+T[0]] = S[i];
		for(i = pos ; i <= (pos+T[0]) ; i++)
			S[i] = T[i-pos+1];
		S[0] += T[0];
		return OK;
	}
	else		//���ֲ���
	{
		for(i = MAXSTRLEN ; i <= pos ; i--)
			S[i] = S[i-T[0]];
		for(i = pos ; i <= pos+T[0] ; i++)
			S[i] = T[i-pos+1];
		S[0] = MAXSTRLEN;
		return FALSE;
	}
}
 
//�Ӵ���ɾ����pos���ַ���ʼ�ĳ���Ϊlen���ַ�
Status StrDelete(SString &S , int pos , int len)
{
	int i;
	if(pos < 1 || pos > S[0]-len+1 || len < 0) return ERROR;
	for(i = pos+len ; i <= S[0] ; i++)
		S[i-len] = S[i];
	S[0] -= len;
	return OK;
}
 
//��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
Status Replace(SString &S , SString T , SString V)
{
	int i = 1;		//�Ӵ�S�ĵ�һ���ַ�����Ҵ�T
	if(StrEmpty(T)) return ERROR;
	do
	{
		i = Index(S , T , i);		//���iΪ����һ��i֮���ҵ����Ӵ�T��λ��
		if(i)			//��S�д��ڴ�T
		{
			StrDelete(S , i , StrLength(T));		//ɾ���ô�T
			StrInsert(S , i , V);					//��ԭ��T��λ�ò��봮V
			i += StrLength(V);						//�ڲ���Ĵ�V����������Ҵ�T
		}
	}while(i);
	return OK;
}
 
//����ַ���T�����
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
