//【例4.3】的算法：把串s中最先出现的子串"ab"改为"xyz"
#include "listring.cpp"
void Repl(LinkStrNode *&s)
{
	LinkStrNode *p=s->next,*q;
	int find=0;
	while (p->next!=NULL && find==0)	//查找'ab'子串
	{
		if (p->data=='a' && p->next->data=='b')   	//找到了ab子串
		{	
			p->data='x';p->next->data='z';			//替换为xyz
			q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
			q->data='y';q->next=p->next;p->next=q;
			find=1;
		}
		else p=p->next; 
	}
}
int main()
{
	LinkStrNode *s;
	StrAssign(s,"aabcabcd");
	printf("s:");DispStr(s);
	printf("ab->xyz\n");
	Repl(s);
	printf("s:");DispStr(s);
	return 1;
}
