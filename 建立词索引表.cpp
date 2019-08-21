#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxBookNum 1000   // 假设只对1000本书建立索引表
#define MaxKeyNum  2500   // 索引表的最大容量
#define MaxLineNum 500    // 书目串的最大长度
#define MaxWordNum 10     // 词表的最大容量
 
// 书目类型的定义
typedef struct Book {
	char id[10] ;   // 书号
	char name[MaxLineNum] ; // 书名
}Book;

//书目表的定义
typedef struct BookList{
	Book book[MaxBookNum] ;     // 存储书目的表
	int  number ;               // 书目数量
}BookList ;
 
// 关键字索引对应的书目id
typedef struct IdIndex{
	char id[10] ;
	struct IdIndex * next ;
} IdIndex ;
 
// 索引类型定义
typedef struct BookIndex{
	char index[50] ;
	IdIndex * head ;
} BookIndex ;
 
 
// 索引表
typedef struct BookIndexList{
	BookIndex bookindex[MaxKeyNum] ;  // 索引项存储信息
	int number;                      // 索引项的书目
}BookIndexList;
	
 
// 词表
typedef struct WordList {
	char Word[MaxWordNum][20] ;
	int number ;
} WordList ;
 
// 关键字表
typedef struct KeyWordList{
	char keyword[20][20] ;
	int number ; 
} KeyWord ;

void GetWordInfo( WordList * wordlist ){
	int i = 0 ;
	char str[1000] ;
 
	// 打开文件
	FILE * pf = fopen("word.txt","r+") ;
	if( pf == NULL )
	{
		printf("打开文件word.txt失败!\n") ;
		exit(0) ;
	}
 
	// 读取文件中的内容
	while( feof(pf) != EOF )
	{
		if( fgets( str , 1000 , pf ) )
		{
			strcpy( wordlist->Word[i] , str ) ;
 
			if( wordlist->Word[i][strlen(wordlist->Word[i])-1] == '\n' )
			{
				wordlist->Word[i][strlen(wordlist->Word[i])-1] = '\0' ;   // 去掉每个词最后的换行符
			}
			i++ ;
		}
		else
		{
			break ;
		}
	}
	wordlist->number = i ;    // 词表的长度
}
 
// 从文件中读入书目串
void GetBookInfo( BookList * booklist ){
	int i = 0 ;
	int j = 0 ;
	int count = 0 ;
	int k = 0 ;
	char str[1000] = { '\0' } ;
 
	// 打开文件
	FILE * pf = fopen( "bookinfo.txt" , "r+" ) ;
	if( pf == NULL )
	{
		printf("打开文件失败!\n") ;
		exit(0) ;
	}
 
	// 读取文件中的内容
	while( feof( pf ) != EOF )
	{
		if( fgets( str , 1000 , pf ) )
		{
			if( str[strlen(str)-1] == '\n' )
			{
				str[strlen(str)-1] = '\0' ;   // 去掉读取的一条书目字符串最后的一个换行符
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
	booklist->number = i ;  // 书目的数量
}
 
// 系统初始化
void InitSystem( BookList * booklist , WordList * wordlist ){
	// 从文件bookinfo.txt中读取书目信息
    GetBookInfo( booklist ) ;
 
	// 从文件word.txt中读取词表信息
	GetWordInfo( wordlist ) ;
 
	printf("书目信息:\n") ;
 
	for( int i = 0 ; i < booklist->number ; i++ )
	{
		printf("%s	%s\n", booklist->book[i].id , booklist->book[i].name ) ;
	}
 
	printf("词表信息:\n") ;
 
	for(int i = 0 ; i < wordlist->number ; i++ )
	{
		printf("%s\n" , wordlist->Word[i]) ;
	}
}
 
// 将一个书目名进行分割
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
 
// 判断一个单词是否为关键字
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
 
// 将一个书目名按照词表过滤得到该书目名的关键字表
void GetBookKey( KeyWordList * keyword , WordList * wordlist , KeyWordList * lastkeyword ){
	int i = 0 ;
	lastkeyword->number = 0 ;   // 初始化关键字表的书目
 
	for( i = 0 ; i < keyword->number ; i++ )
	{
		if( is_Key( keyword->keyword[i] , wordlist) )  //  判断当前字符串是否为关键字
		{
			strcpy( lastkeyword->keyword[lastkeyword->number++] , keyword->keyword[i] ) ;
		}
	}
}
 
// 判断索引表中是否存在某个关键字
// 若存在，返回该索引项的下标；否则返回-1
int key_is_found( BookIndexList * bookindexlist , char * key ){
	for( int i = 0; i < bookindexlist->number; i++ )
	{
		if( strcmp( key , bookindexlist->bookindex[i].index ) == 0 )
			return i;
	}
	return -1 ;
}
 
//初始化索引表
void InitBookIndexList( BookIndexList * bookindexlist ){
	bookindexlist->number = 0 ;
}
 
 
// 将一条书目信息插入索引表
void HandleOneBookToIndexList( Book * book , KeyWordList * lastkeyword , BookIndexList * bookindexlist , WordList * wordlist ){
	KeyWordList keywordlist ;
 
	CutBookName( book , &keywordlist ) ;      // 将书目信息进行分词
	GetBookKey( &keywordlist , wordlist , lastkeyword ) ;   // 将分词得到的单词进行过滤得到该书目的关键字
 
	for( int i = 0 ; i < lastkeyword->number ; i++ )
	{
		int pos = key_is_found( bookindexlist , lastkeyword->keyword[i] ) ;
		if( pos >= 0 )   // 该关键字在索引表中存在
		{
			IdIndex * idindex = (IdIndex*)malloc(sizeof(IdIndex)) ;
			if( !idindex )
			{
				printf("申请内存失败!\n") ;
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
			// 初始化该关键字的索引列表
			bookindexlist->bookindex[bookindexlist->number].head = ( IdIndex *)malloc(sizeof(IdIndex)) ;
			if( !bookindexlist->bookindex[bookindexlist->number].head )
			{
				printf("申请内存失败!") ;
				exit(0) ;
			}
			bookindexlist->bookindex[bookindexlist->number].head->next = NULL ;
 
			IdIndex * idindex2 = (IdIndex*)malloc(sizeof(IdIndex)) ;
			if( !idindex2 )
			{
				printf("申请内存失败!\n") ;
				exit(0) ;
			}
			idindex2->next = NULL ;
 
			strcpy( idindex2->id , book->id ) ;
			strcpy( bookindexlist->bookindex[bookindexlist->number].index , lastkeyword->keyword[i] ) ;
 
			bookindexlist->bookindex[bookindexlist->number].head->next = idindex2 ;  // 第一次插入
			bookindexlist->number++ ;
		}
	}
}
 
// 将两个索引项交换位置
void SwapIndexItem( BookIndex * bookindex1 , BookIndex * bookindex2 ){
	BookIndex  tmp ;
	tmp = *bookindex1 ;
	*bookindex1 = *bookindex2 ;
	*bookindex2 = tmp ;
}
 
// 将词索引表中的索引项的关键字中的首字母大写变为小写
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
 
 
// 将生成的词索引表按照字典序进行排序
void SortByKey( BookIndexList * bookindexlist ){
	int k = 0 ;
	for( int i = 0 ; i < bookindexlist->number - 1 ; i++ )
	{
		for( int j = i + 1 ; j < bookindexlist->number ; j++ )
		{
			k = 0 ;  // 初始化
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
 
 
// 创建词索引表
void CreateIndexList( BookList * booklist , KeyWordList * lastkeyword , BookIndexList * bookindexlist , WordList * wordlist ){
	// 遍历每一个索引项
	for( int i = 0 ; i < booklist->number ; i++ )
	{
		HandleOneBookToIndexList( &booklist->book[i] , lastkeyword , bookindexlist , wordlist ) ;
	}
 
    // 将索引项中的关键字的首字母大写变为小写
	exchange( bookindexlist ) ;
 
	// 根据索引项关键字的首字母进行排序
	SortByKey( bookindexlist ) ;
 
	printf("生成的词索引表:\n") ;
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
 
	BookIndexList bookindexlist ;  // 词索引表
 
	InitSystem( &booklist , &wordlist ) ;   // 初始化系统
 
	InitBookIndexList( &bookindexlist ) ;   // 初始化词索引表
 
	CreateIndexList( &booklist , &lastkeyword , &bookindexlist , &wordlist ) ;  // 创建词索引表
 
	return 0 ;
}

