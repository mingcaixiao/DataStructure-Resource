//¡¾Àı5.1¡¿µÄËã·¨£ºÇón!µÄµİ¹éËã·¨
#include <stdio.h>
int fun(int n)
{
	if (n==1) 					//Óï¾ä1
		return(1);				//Óï¾ä2
	else 						//Óï¾ä3
		return(fun(n-1)*n);		//Óï¾ä4
}
int main()
{
	printf("10!=%d\n",fun(10));
	return 1;
}