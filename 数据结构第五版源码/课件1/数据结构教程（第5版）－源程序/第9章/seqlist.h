#include <stdio.h>
#define MAXL 100		//最大长度
typedef int KeyType;	//定义关键字类型为int
typedef char InfoType;

typedef struct
{	KeyType key;		//关键字项
	InfoType data;		//其他数据项，类型为InfoType
} RecType;				//查找元素的类型
