#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<stdint.h>
#include<ctype.h>

# define LEN sizeof(struct Lnode)

typedef struct list
{
    char data[80];//80�ַ�Ϊ1�У�1��һ���ڵ�
    int line[80];//��
    int row;//��
    struct list *next;
} list,*linklist;


typedef struct stack
{
    int data;
    struct stack* next;
}stack,*linkstack;


linkstack push(linkstack s,int data1);
linkstack pop(linkstack s,int data1);

int search(char *s,char *t,int x[10]);
void replace(char *s,char *t,char *t1);//���ַ���s���ҵ��ַ���t��Ȼ����t0�滻t;
int judege(char *s);
void BF(char *s,char *t);
void delet(linklist L,char* ch);

void insert1(linklist L,int row,int line,char *ch);
void insert0(int x,char *s,char *t);//���ַ���s�ģ�λ�ò������


void print(linklist L)//80�ַ�Ϊ1�У�1��һ���ڵ�
{
    int len,i=0;
    while(L)
    {
        printf("��%d�У�",L->row);
        while(i<strlen(L->data))
        {
            printf("%c",L->data[i]);
            i++;
        }
        printf("\n");
        L=L->next;
        i=0;
    }
}


linklist create()
{
    int i=0,j,line,t;
    char express[80]="\0";
    
    linklist head,r,p;
    head=(linklist)malloc(sizeof(list));
    head->next=NULL;
    
    printf("(����quit�˳�)\n");

    fflush(stdin);
    head->row=i;
    
    printf("��%d��:",head->row);
    gets(express);
    
    strcpy(head->data,express);
    
    for(line=0; line<strlen(express); line++)
    {
        head->line[line]=line;
    }
    r=head;
    
    while(1)
    {
        i++;
        p=(linklist)malloc(sizeof(list));//Ϊ�½ڵ㿪�ٿռ�
        
        printf("��%d��:",i);
        gets(express);
        
        for(line=0; line<strlen(express); line++)
            p->line[line]=line;
        
        strcpy(p->data,express);
        p->row=i;
        
        if(strcmp(express,"quit")==0) 
			break;
        p->next=NULL;
        r->next=p;
        r=p;
    }
    return head;
}

void count(linklist L)
{
    int Chinese=0;
    int lowcase=0;
    int capital=0;
    int punction=0;
    int space=0;
    int i=0,num=0;
    while(L)
    {
        while(i<strlen(L->data))
        {
            if(isdigit(L->data[i]))//isdigit
            {
                num++;
            }
            else if(isupper(L->data[i]))
            {
                capital++;
            }
            else if(islower(L->data[i]))
            {
                lowcase++;
            }
            else if(ispunct(L->data[i]))
            {
                punction++;
            }
            else if(L->data[i]==32)
            {
                space++;
            }
            else if((uint8_t)L->data[i]>127)//
            {
                Chinese++;
            }
            i++;
        }
        L=L->next;
        i=0;


    }
    printf("���ָ���Ϊ�� %d\n",Chinese/2);
    printf("���ָ���Ϊ�� %d\n",num);
    printf("�ո����Ϊ�� %d\n",space);
    printf("�����Ÿ���Ϊ�� %d\n",punction);
    printf("Сд��ĸ����Ϊ�� %d\n",lowcase);
    printf("��д��ĸ����Ϊ�� %d\n",capital);


}


int main(int argc,char**argv){
    int n1[10];
    
    int c,c1,end,line1,row1,m=0,m1=0,n=0,coun=0,n0=0,count1=0;
    char ch[80],ch1[80],x[80],x1[80],x2[80];


    linklist L,L1,position,L2,L3,L4,L5;
    L1=NULL;
    printf("\t\t        ----------->       \n");
    printf("\t\t        |�ı��༭��|       \n");
    printf("\t\t       <-----------        \n");
    printf("\t\t           1.��ʼ          \n");
    printf("\t\t           2.�˳�          \n");
    printf("��ѡ���ܣ�\n");
    while(scanf("%d",&c)==1)
    {
        printf("\t\t|**************���ܲ˵�**************|\n");
        printf("\t\t            0.�˳�                    \n");
        printf("\t\t            1.д�ı�                  \n");
        printf("\t\t            2.�ı�����ͳ��            \n");
        printf("\t\t            3.�ı����ݲ���            \n");
        printf("\t\t            4.�ı�����ɾ��            \n");
        printf("\t\t            5.�ı����ݲ���            \n");
        printf("\t\t            6.�滻����                \n");
        printf("\t\t|*************************************|\n");
        printf("��ѡ��\n");
        while(scanf("%d",&c1)!=0)
        {
            switch(c1)
            {
            case 0:
                return 0;
                break;
            case 1:
                printf("�������ĵ�");
                L1= create();
                printf("�����\n");
                print(L1);
                break;
            case 2:
                count(L1);
                break;
            case 3:
                printf("����������ҵ��ַ������ַ���:");
                scanf("%s",ch);
                L2=L1;
                while(L2)
                {
                    n=search(L2->data,ch,n1);
                    if(n>0)
                    {
                        int i;
                        for(i=0; i<n; i++)
                        {
                            printf("������%d��,��%d��\n",L2->row,n1[i]);
                        }
                    }
                    coun=coun+n;
                    L2=L2->next;
                }
                if(coun==0)
					printf("���޴���Ϣ\n");
                else
                    printf("������%d��",coun);
                break;
            case 4:
                printf("��������ɾ�����ַ������ַ���:");
                scanf("%s",ch1);
                printf("ɾ��ǰ:"); 
                print(L1);
                printf("ɾ����:");
                delet(L1,ch1);
                break;
            case 5:
                printf("�������������ַ������ַ���:");
                scanf("%s",x);
                printf("����������������������: ");
                scanf("%d %d",&row1,&line1);
                m=0;
                L3=L1;
                while(L3)
                {
                    while(m<=strlen(L3->data))
                    {
                        if((L3->line[m]==line1)&&(L3->row==row1))
                        {
                            insert0(L3->line[m],L3->data,x);
                            break;
                        }
                        m++;
                    }
                    L3=L3->next;
                    m=0;
                }
                break;
            case 6:
                printf("��������ҵ�����\n");//ɾ������
                scanf("%s",x1);
                L4=L1;
                L5=L1;
                
                while(L4)
                {
                    n0=search(L4->data,x1,n1);
                    count1=count1+n0;
                    L4=L4->next;
                }
                if(count==0) 
					printf("���޴���Ϣ\n");
                else
                {
                    printf("������%d��",count1);
                    printf("�������滻����\n");
                    scanf("%s",x2);
                    
                    while(L5)
                    {
                        replace(L5->data,x1,x2);
                        L5=L5->next;
                    }
                    
                    printf("�滻��\n");
                    print(L1);
                }
                break;
            }
        }
    }
    return 0;
}

void BF(char *s,char *t)
{
    int i=0,j=0,t1,t2;
    
    int slen=strlen(s);
    int tlen=strlen(t);
    
    while(i<slen)
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
            if(j==tlen)
            {
                for(t1=0; t1<tlen; t1++)
                {
                    for(t2=(i-tlen)+1; t2<=slen-1; t2++)
                    {
                        s[t2-1]=s[t2];
                    }
                }
                s[slen-tlen]='\0';
                slen=strlen(s);
                i=0;
                j=0;
            }
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
}

void replace(char *s,char *t,char *t1)//��sλ����t1���滻t
{
    int i,j=0,m=0,n=0;
    int x[10];
    
    j=search(s,t,x);
    BF(s,t);
    
    m=strlen(t);
    n=strlen(t1);
    
    for(i=0; i<j; i++)
    {
        if(i==0)
            insert0(x[i],s,t1);
        else
            insert0(x[i]+n-m,s,t1);
    }
}


void insert0(int x,char *s,char *t)//���ַ���s�ģ�λ�ò������
{
	printf("����ǰ:%s",s);
    int i,j,m;
    i=strlen(s);
    for(m=0; m<strlen(t); m++)
    {
        for(j=i; j>=x-1; j--)
            s[j+1]=s[j];
        s[x++]=t[m];
        ++i;
    }
    printf("�����:%s",s);
}

void delet(linklist L,char* ch)
{
    int m1=0;
    int m2=2;
    int m3=3;
    while(L)
    {
        BF(L->data,ch);
        printf("��%d�У�%s\n",L->row,L->data);
        L=L->next;
    }
}

int search(char *s,char *t,int x[10]){//BF�㷨��
    int i=0,j=0,t1,t2,num=0;
    
    int slen=strlen(s);
    int tlen=strlen(t);
    
    while(i<slen)
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
            if(j==tlen)
            {
                printf("%s��%s ��%dλ��\n",t,s,i-tlen);
                x[num]=i-tlen;
                num++;
            }
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    return num;
}

linkstack push(linkstack s,int data1){
    linkstack p;
    p=(linkstack)malloc(sizeof(stack));
    p->data=data1;
    p->next=s;
    s=p;
    return s;
}

linkstack pop(linkstack s,int data1){
    linkstack p;
    if(s==NULL) 
		return NULL;
    data1=s->data;
    p=s;
    s=s->next;
    free(p);
    return s;
}

int gettop(linkstack s,int data1){
    if(s!=NULL)
        return s->data;
}
