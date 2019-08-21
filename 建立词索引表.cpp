#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxBookNum 1000   // ����ֻ��1000���齨��������
#define MaxKeyNum  2500   // ��������������
#define MaxLineNum 500    // ��Ŀ������󳤶�
#define MaxWordNum 10     // �ʱ���������
 
// ��Ŀ���͵Ķ���
typedef struct Book {
	char id[10] ;   // ���
	char name[MaxLineNum] ; // ����
}Book;

//��Ŀ��Ķ���
typedef struct BookList{
	Book book[MaxBookNum] ;     // �洢��Ŀ�ı�
	int  number ;               // ��Ŀ����
}BookList ;
 
// �ؼ���������Ӧ����Ŀid
typedef struct IdIndex{
	char id[10] ;
	struct IdIndex * next ;
} IdIndex ;
 
// �������Ͷ���
typedef struct BookIndex{
	char index[50] ;
	IdIndex * head ;
} BookIndex ;
 
 
// ������
typedef struct BookIndexList{
	BookIndex bookindex[MaxKeyNum] ;  // ������洢��Ϣ
	int number;                      // ���������Ŀ
}BookIndexList;
	
 
// �ʱ�
typedef struct WordList {
	char Word[MaxWordNum][20] ;
	int number ;
} WordList ;
 
// �ؼ��ֱ�
typedef struct KeyWordList{
	char keyword[20][20] ;
	int number ; 
} KeyWord ;

void GetWordInfo( WordList * wordlist ){
	int i = 0 ;
	char str[1000] ;
 
	// ���ļ�
	FILE * pf = fopen("word.txt","r+") ;
	if( pf == NULL )
	{
		printf("���ļ�word.txtʧ��!\n") ;
		exit(0) ;
	}
 
	// ��ȡ�ļ��е�����
	while( feof(pf) != EOF )
	{
		if( fgets( str , 1000 , pf ) )
		{
			strcpy( wordlist->Word[i] , str ) ;
 
			if( wordlist->Word[i][strlen(wordlist->Word[i])-1] == '\n' )
			{
				wordlist->Word[i][strlen(wordlist->Word[i])-1] = '\0' ;   // ȥ��ÿ�������Ļ��з�
			}
			i++ ;
		}
		else
		{
			break ;
		}
	}
	wordlist->number = i ;    // �ʱ�ĳ���
}
 
// ���ļ��ж�����Ŀ��
void GetBookInfo( BookList * booklist ){
	int i = 0 ;
	int j = 0 ;
	int count = 0 ;
	int k = 0 ;
	char str[1000] = { '\0' } ;
 
	// ���ļ�
	FILE * pf = fopen( "bookinfo.txt" , "r+" ) ;
	if( pf == NULL )
	{
		printf("���ļ�ʧ��!\n") ;
		exit(0) ;
	}
 
	// ��ȡ�ļ��е�����
	while( feof( pf ) != EOF )
	{
		if( fgets( str , 1000 , pf ) )
		{
			if( str[strlen(str)-1] == '\n' )
			{
				str[strlen(str)-1] = '\0' ;   // ȥ����ȡ��һ����Ŀ�ַ�������һ�����з�
			}
 
			while( str[j] != ' ' )
			{
				booklist->book[i].id[j] = str[j] ;
				j++ ;
			}
			booklist->book[i].id[j] = '\0' ;
			count = j + 1 ;
 
			while( str[count] != '\0' )
			{
				booklist->book[i].name[k++] = str[count++] ;
			}
			booklist->book[i].name[k] = '\0' ;
 
			i++ ;
			j = 0 ;
			k = 0 ;
			strcpy( str , "" ) ;
		}
		else
		{
			break ;
		}
	}
	booklist->number = i ;  // ��Ŀ������
}
 
// ϵͳ��ʼ��
void InitSystem( BookList * booklist , WordList * wordlist ){
	// ���ļ�bookinfo.txt�ж�ȡ��Ŀ��Ϣ
    GetBookInfo( booklist ) ;
 
	// ���ļ�word.txt�ж�ȡ�ʱ���Ϣ
	GetWordInfo( wordlist ) ;
 
	printf("��Ŀ��Ϣ:\n") ;
 
	for( int i = 0 ; i < booklist->number ; i++ )
	{
		printf("%s	%s\n", booklist->book[i].id , booklist->book[i].name ) ;
	}
 
	printf("�ʱ���Ϣ:\n") ;
 
	for(int i = 0 ; i < wordlist->number ; i++ )
	{
		printf("%s\n" , wordlist->Word[i]) ;
	}
}
 
// ��һ����Ŀ�����зָ�
void CutBookName( Book * book , KeyWordList * keywordlist ) {
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;
 
	while( book->name[i] != '\0' )
	{
		if( book->name[i] == ' ' )
		{
			keywordlist->keyword[j][k] = '\0' ;
			k = 0 ;
			j++ ;
			i++ ;
			continue ;
		}
		keywordlist->keyword[j][k++] = book->name[i++] ;
	}
	keywordlist->keyword[j++][k] = '\0' ;
	keywordlist->number = j ;
}
 
// �ж�һ�������Ƿ�Ϊ�ؼ���
bool is_Key( char * word , WordList * wordlist ){
	int i = 0 ;
	for( i = 0 ; i < wordlist->number ; i++ )
	{
		if( strcmp( wordlist->Word[i] , word ) == 0 )
		{
			return false ;
		}
	}
	return true ;
}
 
// ��һ����Ŀ�����մʱ���˵õ�����Ŀ���Ĺؼ��ֱ�
void GetBookKey( KeyWordList * keyword , WordList * wordlist , KeyWordList * lastkeyword ){
	int i = 0 ;
	lastkeyword->number = 0 ;   // ��ʼ���ؼ��ֱ����Ŀ
 
	for( i = 0 ; i < keyword->number ; i++ )
	{
		if( is_Key( keyword->keyword[i] , wordlist) )  //  �жϵ�ǰ�ַ����Ƿ�Ϊ�ؼ���
		{
			strcpy( lastkeyword->keyword[lastkeyword->number++] , keyword->keyword[i] ) ;
		}
	}
}
 
// �ж����������Ƿ����ĳ���ؼ���
// �����ڣ����ظ���������±ꣻ���򷵻�-1
int key_is_found( BookIndexList * bookindexlist , char * key ){
	for( int i = 0; i < bookindexlist->number; i++ )
	{
		if( strcmp( key , bookindexlist->bookindex[i].index ) == 0 )
			return i;
	}
	return -1 ;
}
 
//��ʼ��������
void InitBookIndexList( BookIndexList * bookindexlist ){
	bookindexlist->number = 0 ;
}
 
 
// ��һ����Ŀ��Ϣ����������
void HandleOneBookToIndexList( Book * book , KeyWordList * lastkeyword , BookIndexList * bookindexlist , WordList * wordlist ){
	KeyWordList keywordlist ;
 
	CutBookName( book , &keywordlist ) ;      // ����Ŀ��Ϣ���зִ�
	GetBookKey( &keywordlist , wordlist , lastkeyword ) ;   // ���ִʵõ��ĵ��ʽ��й��˵õ�����Ŀ�Ĺؼ���
 
	for( int i = 0 ; i < lastkeyword->number ; i++ )
	{
		int pos = key_is_found( bookindexlist , lastkeyword->keyword[i] ) ;
		if( pos >= 0 )   // �ùؼ������������д���
		{
			IdIndex * idindex = (IdIndex*)malloc(sizeof(IdIndex)) ;
			if( !idindex )
			{
				printf("�����ڴ�ʧ��!\n") ;
				exit(0) ;
			}
			idindex->next = NULL ;
			strcpy( idindex->id , book->id ) ;
 
			IdIndex * tmp = bookindexlist->bookindex[pos].head->next ;
			bookindexlist->bookindex[pos].head->next = idindex ;
			idindex->next = tmp ;
		}
		else
		{
			// ��ʼ���ùؼ��ֵ������б�
			bookindexlist->bookindex[bookindexlist->number].head = ( IdIndex *)malloc(sizeof(IdIndex)) ;
			if( !bookindexlist->bookindex[bookindexlist->number].head )
			{
				printf("�����ڴ�ʧ��!") ;
				exit(0) ;
			}
			bookindexlist->bookindex[bookindexlist->number].head->next = NULL ;
 
			IdIndex * idindex2 = (IdIndex*)malloc(sizeof(IdIndex)) ;
			if( !idindex2 )
			{
				printf("�����ڴ�ʧ��!\n") ;
				exit(0) ;
			}
			idindex2->next = NULL ;
 
			strcpy( idindex2->id , book->id ) ;
			strcpy( bookindexlist->bookindex[bookindexlist->number].index , lastkeyword->keyword[i] ) ;
 
			bookindexlist->bookindex[bookindexlist->number].head->next = idindex2 ;  // ��һ�β���
			bookindexlist->number++ ;
		}
	}
}
 
// �������������λ��
void SwapIndexItem( BookIndex * bookindex1 , BookIndex * bookindex2 ){
	BookIndex  tmp ;
	tmp = *bookindex1 ;
	*bookindex1 = *bookindex2 ;
	*bookindex2 = tmp ;
}
 
// �����������е�������Ĺؼ����е�����ĸ��д��ΪСд
void exchange( BookIndexList * bookindexlist )
{
	for( int i = 0 ; i < bookindexlist->number ; i++ )
	{
		if( bookindexlist->bookindex[i].index[0] <= 'Z' )
		{
			bookindexlist->bookindex[i].index[0] = char( int(bookindexlist->bookindex[i].index[0] ) + 32 ) ;
		}
	}
}
 
 
// �����ɵĴ����������ֵ����������
void SortByKey( BookIndexList * bookindexlist ){
	int k = 0 ;
	for( int i = 0 ; i < bookindexlist->number - 1 ; i++ )
	{
		for( int j = i + 1 ; j < bookindexlist->number ; j++ )
		{
			k = 0 ;  // ��ʼ��
			while( 1 )
			{
				if( bookindexlist->bookindex[i].index[k] > bookindexlist->bookindex[j].index[k] )
				{
					SwapIndexItem( &bookindexlist->bookindex[i] , &bookindexlist->bookindex[j] ) ;
					break ;
				}
				else if( bookindexlist->bookindex[i].index[k] == bookindexlist->bookindex[j].index[k] )
				{
					k++ ;
				}
				else
				{
					break ;
				}
			}
		}
	}
}
 
 
// ������������
void CreateIndexList( BookList * booklist , KeyWordList * lastkeyword , BookIndexList * bookindexlist , WordList * wordlist ){
	// ����ÿһ��������
	for( int i = 0 ; i < booklist->number ; i++ )
	{
		HandleOneBookToIndexList( &booklist->book[i] , lastkeyword , bookindexlist , wordlist ) ;
	}
 
    // ���������еĹؼ��ֵ�����ĸ��д��ΪСд
	exchange( bookindexlist ) ;
 
	// ����������ؼ��ֵ�����ĸ��������
	SortByKey( bookindexlist ) ;
 
	printf("���ɵĴ�������:\n") ;
	for(int i = 0 ; i < bookindexlist->number ; i++ )
	{
		printf("%s	" , bookindexlist->bookindex[i].index ) ;
 
		IdIndex * p  = bookindexlist->bookindex[i].head->next ;
 
		while( p != NULL )
		{
			printf("%s " , p->id ) ;
			p = p->next ;
		}
		printf("\n") ;
	}
}


int main(int argc,char **argv){
	BookList booklist ;
	WordList wordlist ;
 
	KeyWordList lastkeyword ;
 
	BookIndexList bookindexlist ;  // ��������
 
	InitSystem( &booklist , &wordlist ) ;   // ��ʼ��ϵͳ
 
	InitBookIndexList( &bookindexlist ) ;   // ��ʼ����������
 
	CreateIndexList( &booklist , &lastkeyword , &bookindexlist , &wordlist ) ;  // ������������
 
	return 0 ;
}

