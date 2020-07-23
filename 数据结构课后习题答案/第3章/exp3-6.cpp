//文件名:exp3-6.cpp
#include <stdio.h>
#include <malloc.h>
typedef struct qnode
{
    int data;					//病历号
    struct qnode *next;			//下一个节点指针
} QNode;						//链队节点类型
typedef struct  	
{
    QNode *front,*rear;
} QuType;						//声明链队类型
void Destroyqueue(QuType *&qu)	//释放链队
{
	QNode *pre,*p;
	pre=qu->front; 
	if (pre!=NULL)				//若链队不空
	{
		p=pre->next;
		while (p!=NULL)			//释放队中所有数据节点
		{
			free(pre);
			pre=p;
			p=p->next;
		}
		free(pre);
	}
	free(qu);					//释放链队节点
}
bool exist(QuType *qu,int no)	//队列中是否有no病历号的病人
{
	bool find=false;
	QNode *p=qu->front;
	while (p!=NULL && !find)
	{
		if (p->data==no)							
			find=true;
		else
			p=p->next;
	}
	return find;
}
void SeeDoctor()				//模拟病人看病的过程
{
    int sel,no;
	bool flag=true;
    QuType *qu;
    QNode *p;
    qu=(QuType *)malloc(sizeof(QuType));	//创建空队
    qu->front=qu->rear=NULL;
    while (flag) 							//循环执行
	{
       	printf(">1:排队 2:就诊 3:查看排队 4.不再排队,余下依次就诊 5:下班  请选择:");
		scanf("%d",&sel); 
		switch(sel) 
		{
		case 1:	printf("  输入病历号:");
			while (true)
			{	
				scanf("%d",&no);
				if (exist(qu,no))
					printf("  输入的病历号重复,重新输入:");
				else
					break;
			};
			p=(QNode *)malloc(sizeof(QNode));	//创建节点
			p->data=no;p->next=NULL;
			if (qu->rear==NULL)					//第一个病人排队
				qu->front=qu->rear=p;
			else
			{
				qu->rear->next=p; qu->rear=p;	//将p节点进队
			}
			break;
		case 2:	if (qu->front==NULL)				//队空
					printf("  没有排队的病人!\n");
			    else								//队不空
				{
					p=qu->front;
                   	printf("  >>病人%d就诊\n",p->data);
                   	if (qu->rear==p)			//只有一个病人排队的情况
						qu->front=qu->rear=NULL;
				   	else
					   	qu->front=p->next;
				   	free(p);
			   	}
               	break;
          case 3:if (qu->front==NULL)  			//队空
                   	printf("  没有排列的病人!\n");
			     else 							//队不空
				 {
					 p=qu->front;
					 printf("  >>排队病人:");
					 while (p!=NULL) 
					 {
						 printf("%d ",p->data);
						 p=p->next;
					 }
					 printf("\n");
				 }
				 break;
          case 4:if (qu->front==NULL)			//队空
                    printf("  >>没有排列的病人!\n");
			     else							//队不空
				 {
					 p=qu->front;
					 printf("  >>病人按以下顺序就诊:");
					 while (p!=NULL) 
					 {
						 printf("%d ",p->data);
						 p=p->next;
					 }
					 printf("\n");
				 }
				 Destroyqueue(qu);				//释放链队
				 flag=false;					//退出
				 break;
		  case 5:if (qu->front!=NULL)			//队不空
					printf("  请排队的病人明天就医!\n");

			     flag=false;					//退出
				 Destroyqueue(qu);				//释放链队
               	 break;
		}
    }
}
int main()
{
    SeeDoctor();
	return 1;
}
