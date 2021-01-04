/* Linear Table On Linked list Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define LISTNUM 10

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //线性表（链式结构）的定义
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

status InitList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType *e);
int LocateElem(LinkList L,ElemType e,status(*compare)(ElemType,ElemType));
status PriorElem(LinkList L,ElemType cue,ElemType *pre,status(*compare)(ElemType,ElemType));
status NextElem(LinkList L,ElemType cue,ElemType *next,status(*compare)(ElemType,ElemType));
status ListInsert(LinkList *L,int i,ElemType e);
status ListDelete(LinkList *L,int i,ElemType *e);
status ListTraverse(LinkList L);
status compare(ElemType a,ElemType b);
status ReadFile(LinkList *L,char *c);
status WriteFile(LinkList L,char *c);
/*--------------------------------------------*/

int main(void)
{
    status(*p)(ElemType,ElemType);
    p=compare;
    int op=1,i,t,listi=0;
    LinkList l[LISTNUM];
    ElemType e;
    status s;
    char c[100];
    for(i=0;i<LISTNUM;i++)
        l[i]=NULL;
    while(op){
	    system("cls");	printf("\n\n");
	    printf("      Menu for Linear Table On Linked list Structure \n");
	    printf("请先进行操作15来选择您要处理的线性表，否则默认为第一个线性表\n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. InitList       7. LocateElem\n");
	    printf("    	  2. DestroyList    8. PriorElem\n");
	    printf("    	  3. ClearList       9. NextElem \n");
	    printf("    	  4. ListEmpty     10. ListInsert\n");
	    printf("    	  5. ListLength     11. ListDelete\n");
	    printf("    	  6. GetElem       12. ListTraverse\n");
	    printf("    	  13. ReadFile       14. WriteFile\n");
	    printf("    	  15. ChooseList       0. Exit\n");
	    printf("-------------------------------------------------\n");
	    printf("    请选择你的操作[0~15]:");
	    scanf("%d",&op);
	    while(op<0||op>15)
        {
            printf("请输入正确的操作数范围[0~15]\n");
            scanf("%d",&op);
        }
        switch(op){
	        case 1:
		        //printf("\n----IntiList功能待实现！\n");
		        s=InitList(&l[listi]);
		        if(s==OK) printf("线性表%d创建成功！\n",listi+1);
                else if(s==INFEASTABLE)
                    printf("线性表%d已经创建，请勿重复创建！\n",listi+1);
                else
                    printf("线性表%d创建失败！\n",listi+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyList功能待实现！\n");
		        if(DestroyList(&l[listi])==INFEASTABLE)
                    printf("线性表%d未初始化或为空！\n",listi+1);
                else
                    printf("线性表%d成功销毁",listi+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----ClearList功能待实现！\n");
		        if(ClearList(&l[listi])==INFEASTABLE)
                    printf("线性表%d未初始化或已经为空！\n",listi+1);
                else
                    printf("线性表%d成功清空！\n",listi+1);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----ListEmpty功能待实现！\n");
		        s=ListEmpty(l[listi]);
		        if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(s==TRUE)
                    printf("线性表%d为空！\n",listi+1);
                else
                    printf("线性表%d非空！\n",listi+1);
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----ListLength功能待实现！\n");
                if(ListLength(l[listi])==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else
                    printf("线性表%d的长度为%d!\n",listi+1,ListLength(l[listi]));
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----GetElem功能待实现！\n");
		        printf("请输入你想查询的元素位置！\n范围从1到%d!\n",ListLength(l[listi]));
		        scanf("%d",&i);
		        s=GetElem(l[listi],i,&e);
		        if(s==ERROR)
                    printf("请输入正确的位置值!范围：从1到%d\n",ListLength(l[listi]));
		        if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(s==OK)
                    printf("线性表%d第%d个元素的值为：%d\n",listi+1,i,e);
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----LocateElem功能待实现！\n");
		        printf("请输入你想查询的元素的值！\n");
		        scanf("%d",&e);
		        t=LocateElem(l[listi],e,p);
                if(t==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(t!=0)
                    printf("你查询的值%d第一次出现在线性表%d第%d个位置！\n",e,listi+1,t);
                else
                    printf("你查询的值%d在表%d中不存在！\n",e,listi+1);
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----PriorElem功能待实现！\n");
		        printf("请输入你想查询的元素的值！\n");
		        scanf("%d",&e);
		        s=PriorElem(l[listi],e,&t,p);
		        if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(s==OK)
                    printf("在线性表%d中第一个与你查询的值%d匹配的元素的前驱为%d！\n",listi+1,e,t);
                else
                    printf("你查询的值%d的前驱在表%d中不存在！\n",e,listi+1);
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----NextElem功能待实现！\n");
		        printf("请输入你想查询的元素的值！\n");
		        scanf("%d",&e);
		        s=NextElem(l[listi],e,&t,p);
		        if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(s==OK)
                    printf("在线性表%d中第一个与你查询的值%d匹配的元素的后继为%d！\n",listi+1,e,t);
                else
                    printf("你查询的值%d的后继在表%d中不存在！\n",e,listi+1);
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----ListInsert功能待实现！\n");
		        printf("请输入你要插入的元素！\n");
		        scanf("%d",&e);
                printf("请输入你要插入的位置！范围：从1到%d\n",ListLength(l[listi])+1);
                scanf("%d",&i);
		        s=ListInsert(&l[listi],i,e);
		        while(s==ERROR)
                {
                    printf("请输入正确的位置值!范围：从1到%d\n",ListLength(l[listi])+1);
                    scanf("%d",&i);
                    s=ListInsert(&l[listi],i,e);
                }
		        if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
                else if(s==OVERFLOW)
                    printf("内存已满！\n");
                else
                    printf("在线性表%d插入成功！\n",listi+1);
                getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----ListDelete功能待实现！\n");
		        printf("请输入你要删除的位置！范围：从1到%d\n",ListLength(l[listi]));
		        scanf("%d",&i);
                s=ListDelete(&l[listi],i,&e);
		        while(s==ERROR)
                {
                    printf("请输入正确的位置值!范围：从1到%d\n",ListLength(l[listi]));
                    scanf("%d",&i);
                    s=ListDelete(&l[listi],i,&e);
                }
                if(s==INFEASTABLE&&ListLength(l[listi])==0)
                    printf("线性表%d为空或未初始化！\n",listi+1);
                else
                    printf("删除成功！删除的元素值为：%d\n",e);
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----ListTraverse功能待实现！\n");
                s=ListTraverse(l[listi]);
		        if(!s) printf("线性表%d是空表！\n",listi+1);
		        else if(s==INFEASTABLE)
                    printf("线性表%d未初始化！\n",listi+1);
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----ReadFile功能待实现！\n");
                printf("请输入要读入的文件名！\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&l[listi],c);
                if(s==INFEASTABLE)
                    printf("线性表未初始化！\n");
		        else if(s==ERROR)
                    printf("文件打开失败！\n");
                else
                    printf("文件读入成功！\n");
		        getchar();getchar();
		        break;
            case 14:
                //printf("\n----WriteFile功能待实现！\n");
		        printf("请输入要输出的文件名！\n");
                getchar();
                scanf("%s",c);
                s=WriteFile(l[listi],c);
                if(s==INFEASTABLE)
                    printf("线性表未初始化！\n");
		        else if(s==ERROR)
                    printf("文件打开失败！\n");
                else
                    printf("文件输出成功！\n");
		        getchar();getchar();
		        break;
            case 15:
                printf("请输入需要操作的线性表序号，范围[1，%d]！\n",LISTNUM);
		        scanf("%d",&i);
		        while(i<1||i>LISTNUM)
                {
                    printf("请输入正确的范围[1，%d]！\n",LISTNUM);
                    scanf("%d",&i);
                }
                printf("您已成功选择第%d个线性表！\n",i);
                listi=i-1;
		        getchar();getchar();

		        break;

        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

/*
    函数名称:InitList
    函数功能：构造一个空的线性表
    函数参数：线性表L地址
    函数返回值：状态参数status
*/
status InitList(LinkList *L)
{
	if(*L!=NULL)
        return INFEASTABLE;
	*L=(LinkList)malloc(sizeof(LNode));
	if(*L==NULL)
        return OVERFLOW;
	(*L)->next=NULL;
	return OK;
}

/*
    函数名称：DestroyList
    函数功能：销毁线性表L
    函数参数：线性表L地址
    函数返回值：状态参数status
*/
status DestroyList(LinkList *L)
{
    if(*L==NULL)
        return INFEASTABLE;
    LinkList p,q;
    p=*L;
    q=p->next;
    while(q!=NULL)
    {
        free(p);
        p=q;
        q=q->next;
    }
    free(p);
    *L=NULL;
    return OK;
}

/*
    函数名称：ClearList
    函数功能：清空线性表L
    函数参数：线性表L地址
    函数返回值：状态参数status
*/
status ClearList(LinkList *L)
{
    if(*L==NULL)
        return INFEASTABLE;
    LinkList p,q;
    if((*L)->next==NULL)
        return OK;
    p=(*L)->next;
    q=p->next;
    while(q!=NULL)
    {
        free(p);
        p=q;
        q=q->next;
    }
    free(p);
    (*L)->next=NULL;
    return OK;
}

/*
    函数名称：ListEmpty
    函数功能：判定线性表L是否为空
    函数参数：线性表L
    函数返回值：状态参数status
*/
status ListEmpty(LinkList L)
{
    if(L==NULL)
        return INFEASTABLE;
    if(L->next==NULL)
        return TRUE;
    return FALSE;
}

/*
    函数名称：ListLength
    函数功能：求线性表L表长
    函数参数：线性表L
    函数返回值：int型参数
*/
int ListLength(LinkList L)
{
    int length=0;
    if(L==NULL)
        return INFEASTABLE;
    LinkList p=L->next;
    while(p)
    {
        length++;
        p=p->next;
    }
    return length;
}

/*
    函数名称:GetElem
    函数功能：用e返回L中第i个数据元素的值
    函数参数：线性表L，待取数据位置i,取得元素值储存位置e
    函数返回值：状态参数status
*/
status GetElem(LinkList L,int i,ElemType *e)
{
    if(L==NULL)
        return INFEASTABLE;
    if(i<=0||i>ListLength(L))
        return ERROR;
    LinkList p=L;
    while(i)
    {
        p=p->next;
        i--;
    }
    *e=p->data;
    return OK;
}

/*
    函数名称：LocateElem
    函数功能：查找并返回线性表L中第一个与e满足关系compare（）关系的数据元素的位序
    函数参数：线性表L，ElemType e，compare函数指针
    函数返回值：与e满足关系compare（）关系的数据元素的位序
*/
int LocateElem(LinkList L,ElemType e,status(*compare)(ElemType,ElemType))
{
    int i=0;
    if(L==NULL)
        return INFEASTABLE;
    LinkList p=L;
    while(p!=NULL)
    {
        p=p->next;
        i++;
        if(p&&compare(p->data,e)==TRUE)
            return i;
    }
    return 0;
}

/*
    函数名称：compare
    函数功能：比较ElemType类型变量a和b
    函数参数：ElemType a和ElemType b
    函数返回值：状态参量status
*/
status compare(ElemType a,ElemType b)
{
    if(a==b)
        return TRUE;
    else
        return FALSE;
}

/*
    函数名称：PriorElem
    函数功能：查找值和给定值相同的第一个节点的前驱
    函数参数：线性表L，待查询的值cue，储存前驱节点的变量指针，compare函数指针
    函数返回值：状态参量status
*/
status PriorElem(LinkList L,ElemType cue,ElemType *pre,status(*compare)(ElemType,ElemType))
{
    if(L==NULL)
        return INFEASTABLE;
    LinkList p,q;
    q=L;
    p=L->next;
    while(p!=NULL&&p->next!=NULL&&compare(p->next->data,cue)==FALSE)
    {
        p=p->next;
        q=q->next;
    }
    if(p!=NULL&&p->next==NULL)
    {
        if(compare(p->data,cue))
        {
            *pre=q->data;
            return OK;
        }
    }
    if(p!=NULL&&p->next!=NULL)
    {
        *pre=p->data;
        return OK;
    }
    return FALSE;
}

/*
    函数名称：NextElem
    函数功能：寻找值为给定值的第一个节点的后继
    函数参数：线性表L，待查询的值cue，储存后继节点值的变量的指针，compare函数指针
    函数返回值：状态参数status
*/
status NextElem(LinkList L,ElemType cue,ElemType *next,status(*compare)(ElemType,ElemType))
{
    if(L==NULL)
        return INFEASTABLE;
    LinkList p=L->next;
    while(p&&p->next!=NULL&&compare(p->data,cue)==FALSE)
        p=p->next;
    if(p&&p->next!=NULL)
    {
        *next=p->next->data;
        return OK;
    }
    return FALSE;
}

/*
    函数名称：ListInsert
    函数功能：在L的第i个位置之前插入新的数据元素e
    函数参数：线性表L，插入位置i，插入元素e
    函数返回值：状态参数status
*/
status ListInsert(LinkList *L,int i,ElemType e)
{
    if(*L==NULL)
        return INFEASTABLE;
    if(i<1||i>ListLength(*L)+1)
        return ERROR;
    i-=1;
    LinkList p=*L,q=p->next,t;
    while(i)
    {
        p=p->next;
        q=q->next;
        i--;
    }
    t=(LinkList)malloc(sizeof(LNode));
    if(!t)
        return OVERFLOW;
    t->data=e;
    p->next=t;
    t->next=q;
    return OK;
}

/*
    函数名称：ListDelete
    函数功能：删除L的第i个数据元素，用e返回其值
    函数参数：线性表L，删除元素位置i,存储删除值变量的指针
    函数返回值：状态参量status
*/
status ListDelete(LinkList *L,int i,ElemType *e)
{
    if(*L==NULL||(*L)->next==NULL)
        return INFEASTABLE;
    if(i<1||i>ListLength(*L))
        return ERROR;
    i-=1;
    LinkList p=*L,q=(*L)->next;
    while(i)
    {
        p=p->next;
        q=q->next;
        i--;
    }
    *e=q->data;
    p->next=q->next;
    free(q);
    return OK;
}

/*
    函数名称：ListTraverse
    函数功能：遍历整个线性表
    函数参数：线性表L
    函数返回值：状态参数status
*/
status ListTraverse(LinkList L)
{
    int i=0;
    if(L==NULL)
        return INFEASTABLE;
    LinkList p=L;
    printf("\n-----------all elements -----------------------\n");
    while(p->next!=NULL)
    {
        p=p->next;
        printf("%d ",p->data);
        i++;
    }
    printf("\n------------------ end ------------------------\n");
    return i;
}

/*
    函数名称：ReadFile
    函数功能：从文件中读取数据并存储在线性表中
    函数参数：线性表L的地址，文件地址
    函数返回值：状态参数status
*/
status ReadFile(LinkList *L,char *c)
{
    if(*L==NULL)
        return INFEASTABLE;
    FILE *fp;
    if((fp=fopen(c,"r"))==NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    LinkList tail=*L,t;
    ElemType e;
    while(fscanf(fp,"%d",&e)!=EOF)
    {
        t=(LinkList)malloc(sizeof(LNode));
        if(!t)
        {
            fclose(fp);
            return OVERFLOW;
        }
        t->data=e;
        t->next=NULL;
        tail->next=t;
        tail=tail->next;
    }
    fclose(fp);
    return OK;
}

/*
    函数名称：WriteFile
    函数功能：将线性表L中的数据储存在文件中
    函数参数：线性表L，文件地址
    函数返回值：状态参数status
*/
status WriteFile(LinkList L,char *c)
{
    if(L==NULL)
        return INFEASTABLE;
    FILE *fp;
    if ((fp=fopen(c,"w"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}
	LinkList p=L;
    while(p->next!=NULL)
    {
        p=p->next;
        fprintf(fp,"%d ",p->data);
    }
    fprintf(fp,"\n");
    fclose(fp);
    return OK;
}
