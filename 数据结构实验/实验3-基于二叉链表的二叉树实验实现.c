/* Bitree On Linked list Structure */
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define TREENUM 10
#define DEFLENGTH 100

typedef int status;
typedef char ElemType; //数据元素类型定义

typedef struct BiNode{  //二叉树（链式结构）的定义
	int key;
	ElemType data;
	struct BiNode *lchild,*rchild;
}BiNode,*BiTree;

typedef BiTree qElemType;
typedef struct qnode
{
    qElemType data;
    struct qnode *next;
}qnode;//队列元素

typedef struct
{
    qnode *front;
    qnode *rear;
}linkqueue;//队列

typedef BiTree sElemType;
typedef struct node
{
    sElemType data;
    struct node *next;
}mystack;//栈
int num,now;

status CreateBiTree(BiTree *T,ElemType *definition);
status CreateBiTreeWithKey(BiTree *T,FILE*fp);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree *T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTree LocateNode(BiTree T,int e);
status Assign(BiTree T,int e,ElemType value);
BiTree GetSibling(BiTree T,int e);
BiTree GetParent(BiTree T,int e);
status InsertNode(BiTree T,int e,int LR,BiNode *c);
status DeleteNode(BiTree *T,int e);
status Visit(BiTree T);
status PreOrderTraverse(BiTree T,status (*Visit)(BiTree));
status InOrderTraverse(BiTree T,status (*Visit)(BiTree));
status PostOrderTraverse(BiTree T,status(*Visit)(BiTree));
status LevelOrderTraverse(BiTree T,status(*Visit)(BiTree));
status ReadFile(BiTree *T,char *c);
status WriteFile(BiTree T,char *c);
status Initqueue(linkqueue *q);
status Enqueue(linkqueue *q,qElemType e);
status Dequeue(linkqueue *q,qElemType *e);
status queueempty(linkqueue q);
mystack *push(mystack** top,sElemType e);
mystack *pop(mystack** top,sElemType* c);
status stackempty(mystack *top);
/*--------------------------------------------*/

int main(void)
{
    status(*p)(BiTree);
    p=Visit;
    int op=1,i,t,treei=0,Len;
    BiTree bt[TREENUM],tem,tt;
    int e;
    status s;
    char c[100];
    for(i=0;i<TREENUM;i++)
        bt[i]=NULL;
    while(op){
	    system("cls");	printf("\n\n");
	    printf("      Menu for BiTree On Linked list Structure \n");
	    printf("请先进行操作17来选择您要处理的二叉树，否则默认为第一个二叉树\n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. CreateBiTree       10. DeleteNode\n");
	    printf("    	  2. DestroyBiTree      11. PreOrderTraverse\n");
	    printf("    	  3. ClearBiTree        12. InOrderTraverse \n");
	    printf("    	  4. BiTreeEmpty        13. PostOrderTraverse\n");
	    printf("    	  5. BiTreeDepth        14. LevelOrderTraverse\n");
	    printf("    	  6. LocateNode         15. ReadFile\n");
	    printf("    	  7. Assign             16. WriteFile\n");
	    printf("    	  8. GetSibling         17. ChooseBiTree\n");
	    printf("    	  9. InsertNode         0. Exit\n");
	    printf("-------------------------------------------------\n");
	    printf("    请选择你的操作[0~17]:");
	    scanf("%d",&op);
	    while(op<0||op>17)
        {
            printf("请输入正确的操作数范围[0~17]\n");
            scanf("%d",&op);
        }
        switch(op){
	        case 1:
		        //printf("\n---- CreateBiTree功能待实现！\n");
		        printf("请输入一行带空子树的二叉树前序遍历序列，回车键结束！\n");
		        getchar();
		        scanf("%s",c);
		        num=now=0;
		        s=CreateBiTree(&bt[treei],c);
		        if(s==OK) printf("二叉树%d创建成功！\n",treei+1);
                else
                    printf("二叉树%d创建失败！\n",treei+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyBiTree功能待实现！\n");
		        if(DestroyBiTree(&bt[treei])==INFEASTABLE)
                    printf("二叉树%d未创建！\n",treei+1);
                else
                    printf("二叉树%d成功销毁",treei+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----ClearBiTree功能待实现！\n");
		        if(ClearBiTree(&bt[treei])==INFEASTABLE)
                    printf("二叉树%d未创建！\n",treei+1);
                else
                    printf("二叉树%d成功清空！\n",treei+1);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----BiTreeEmpty功能待实现！\n");
		        s=BiTreeEmpty(bt[treei]);
                if(s==TRUE)
                    printf("二叉树%d为空！\n",treei+1);
                else
                    printf("二叉树%d非空！\n",treei+1);
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----BiTreeDepth功能待实现！\n");
                Len=BiTreeDepth(bt[treei]);
                if(Len==0)
                    printf("二叉树%d为空或未初始化！\n",treei+1);
                else
                    printf("二叉树%d的长度为%d!\n",treei+1,Len);
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----LocateNode功能待实现！\n");
		        printf("请输入你想查询的元素关键字！\n");
		        scanf("%d",&i);
		        tt=LocateNode(bt[treei],i);
		        if(tt==NULL)
                    printf("查找的元素不存在！\n");
                else
                {
                    printf("你查询的元素为：\n");
                    Visit(tt);
                }
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----Assign功能待实现！\n");
		        printf("请输入你想赋值的元素的关键字及内容！\n");
		        char value;
		        scanf("%d %c",&e,&value);
		        t=Assign(bt[treei],e,value);
                if(t==FALSE)
                    printf("你查询的元素在二叉树%d中不存在！\n",treei+1);
                else
                    printf("赋值成功！\n");
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----GetSibling功能待实现！\n");
		        printf("请输入你想查询的元素的关键字！\n");
		        scanf("%d",&e);
		        tt=GetSibling(bt[treei],e);
		        if(tt==NULL)
                    printf("你查询的元素的兄弟结点不存在！\n");
                else
                {
                    printf("你查询的关键字%d的结点的兄弟在表%d中的值为：",e,treei+1);
                    Visit(tt);
                }
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----InsertNode功能待实现！\n");
		        printf("请输入你想插入的元素的值！\n");
		        char v;
		        int pos,id;
		        getchar();
		        scanf("%c",&v);
		        printf("请输入你想插入的元素的父结点的关键字！\n");
		        scanf("%d",&e);
		        printf("请输入你想插入的元素的位置：0为左，1为右！\n");
		        scanf("%d",&pos);
		        while(pos!=0&&pos!=1)
                {
                    printf("请输入你想插入的元素的位置：0为左，1为右！\n");
                    scanf("%d",&pos);
                }
                printf("请输入你要插入结点的关键字！\n");
                scanf("%d",&id);
                tem=(BiTree)malloc(sizeof(BiNode));
                tem->data=v;
                tem->key=id;
                tem->lchild=NULL;
                tem->rchild=NULL;
		        s=InsertNode(bt[treei],e,pos,tem);
		        if(s==FALSE)
                    printf("结点%d在二叉树%d中不存在！\n",e,treei+1);
                else if(s==INFEASTABLE)
                    printf("插入结点的关键字已存在！插入失败！\n");
                else
                    printf("插入成功！\n");
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----DeleteNode功能待实现！\n");
		        printf("请输入你要删除的元素关键字！\n");
		        scanf("%d",&e);
		        s=DeleteNode(&bt[treei],e);
		        if(s==INFEASTABLE)
                    printf("关键字%d在二叉树%d不存在！\n",e,treei+1);
                else
                    printf("删除成功！\n");
                getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----PreOrderTraverse功能待实现！\n");
		        PreOrderTraverse(bt[treei],p);
                printf("前序遍历结束！\n");
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----InOrderTraverse功能待实现！\n");
                InOrderTraverse(bt[treei],p);
                printf("中序遍历结束！\n");
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----PostOrderTraverse功能待实现！\n");
                PostOrderTraverse(bt[treei],p);
                printf("后序遍历结束！\n");
		        getchar();getchar();
		        break;
            case 14:
                //printf("\n----LevelOrderTraverse功能待实现！\n");
                LevelOrderTraverse(bt[treei],p);
                printf("层序遍历结束！\n");
		        getchar();getchar();
		        break;
		    case 15:
                //printf("\n----ReadFile功能待实现！\n");
                printf("请输入要读入的文件名！\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&bt[treei],c);
		        if(s==ERROR)
                    printf("文件打开失败！\n");
                else
                    printf("文件读入成功！\n");
		        getchar();getchar();
		        break;
            case 16:
                //printf("\n----WriteFile功能待实现！\n");
		        printf("请输入要输出的文件名！\n");
                getchar();
                scanf("%s",c);
                s=WriteFile(bt[treei],c);
		        if(s==ERROR)
                    printf("文件打开失败！\n");
                else
                    printf("文件输出成功！\n");
		        getchar();getchar();
		        break;
            case 17:
                printf("请输入需要操作的二叉树序号，范围[1，%d]！\n",TREENUM);
		        scanf("%d",&i);
		        while(i<1||i>TREENUM)
                {
                    printf("请输入正确的范围[1，%d]！\n",TREENUM);
                    scanf("%d",&i);
                }
                printf("您已成功选择第%d个二叉树！\n",i);
                treei=i-1;
		        getchar();getchar();
		        break;

        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

/*
    函数名称：CreateBiTree
    函数功能：根据带空子树的二叉树前序遍历序列创建二叉树
    函数参数：二叉树T，带空子树的二叉树前序遍历序列definition，结点关键字num
    函数返回值：状态参数status
*/

status CreateBiTree(BiTree *T,ElemType *definition)
{
    if(definition[now]=='\0')
    {
        *T=NULL;
        return OK;
    }
    if(definition[now]=='#')
    {
        *T=NULL;
        now++;
        return OK;
    }
    else
    {
        *T=(BiTree)malloc(sizeof(BiNode));
        if(!*T)
            return OVERFLOW;
        (*T)->data=definition[now];
        num++;
        now++;
        (*T)->key=num;
        CreateBiTree(&((*T)->lchild),definition);
        CreateBiTree(&((*T)->rchild),definition);
    }
    return OK;
}

/*
    函数名称：CreateBiTreeWithKey
    函数功能：根据带空子树和关键字的二叉树前序遍历序列创建二叉树
    函数参数：二叉树T,带空子树和关键字的二叉树前序遍历序列
    函数返回值：状态参数status
*/

status CreateBiTreeWithKey(BiTree *T,FILE *fp)
{
    int id;
    ElemType x;
    if(fscanf(fp,"%d",&id)==EOF)
    {
        *T=NULL;
        return OK;
    }
    fscanf(fp," %c",&x);
    if(x=='#')
        (*T)=NULL;
    else
    {
        *T=(BiTree)malloc(sizeof(BiNode));
        if(!*T)
            return OVERFLOW;
        (*T)->data=x;
        (*T)->key=id;
        CreateBiTreeWithKey(&((*T)->lchild),fp);
        CreateBiTreeWithKey(&((*T)->rchild),fp);
    }
    return OK;
}
/*
    函数名称：DestroyBiTree
    函数功能：销毁二叉树T
    函数参数：二叉树地址
    函数返回值：状态参数status
*/

status DestroyBiTree(BiTree *T)
{
    if(!*T)
        return INFEASTABLE;
    if((*T)->lchild)
        DestroyBiTree(&((*T)->lchild));
    if((*T)->rchild)
        DestroyBiTree(&((*T)->rchild));
    free(*T);
    *T=NULL;
    return OK;
}

/*
    函数名称：ClearBiTree
    函数功能：清空二叉树T
    函数参数：二叉树T地址
    函数返回值：状态参数status
*/

status ClearBiTree(BiTree *T)
{
    if(!*T)
        return INFEASTABLE;
    if((*T)->lchild)
        ClearBiTree(&((*T)->lchild));
    if((*T)->rchild)
        ClearBiTree(&((*T)->rchild));
    free(*T);
    *T=NULL;
    return OK;
}

/*
    函数名称：BiTreeEmpty
    函数功能：判断二叉树T是否为空
    函数参数：二叉树T
    函数返回值：状态参数status
*/

status BiTreeEmpty(BiTree T)
{
    if(T==NULL)
        return TRUE;
    else
        return FALSE;
}

/*
    函数名称：BiTreeDepth
    函数功能：求二叉树深度
    函数参数：二叉树T
    函数返回值：深度
*/

int BiTreeDepth(BiTree T)
{
    if(T==NULL)
        return 0;
    int ldepth,rdepth;
    ldepth=BiTreeDepth(T->lchild);
    rdepth=BiTreeDepth(T->rchild);
    return 1+(ldepth>rdepth?ldepth:rdepth);
}

/*
    函数名称：LocateNode
    函数功能：查找结点
    函数参数：二叉树T，结点关键字e
    函数返回值：对应结点地址
*/

BiTree LocateNode(BiTree T,int e)
{
    if(!T)
        return NULL;
    static BiTree tem=NULL;
    if(T->key==e)
        return T;
    if(T->lchild)
    {
        tem=LocateNode(T->lchild,e);
        if(!tem)
        {
            if(T->rchild)
                return LocateNode(T->rchild,e);
            else
                return NULL;
        }
        else
            return tem;
    }
    else if(T->rchild)
    {
        return LocateNode(T->rchild,e);
    }
    return NULL;
}

/*
    函数名称：Assign
    函数功能：结点赋值
    函数参数：二叉树指针T，结点关键字e，待赋值value
    函数返回值：状态参数status
*/

status Assign(BiTree T,int e,ElemType value)
{
    if(!T)
        return INFEASTABLE;
    BiTree p=LocateNode(T,e);
    if(!p)
        return FALSE;
    p->data=value;
    return OK;
}

/*
    函数名称：GetSibling
    函数功能：获得兄弟结点
    函数参数：二叉树T，
    函数返回值：状态参数status
*/

BiTree GetSibling(BiTree T,int e)
{
    if(!T)
        return NULL;
    static BiTree tem=NULL;
    if(T->lchild&&T->lchild->key==e)
        return T->rchild;
    if(T->rchild&&T->rchild->key==e)
        return T->lchild;
    if(T->lchild)
    {
        tem=GetSibling(T->lchild,e);
        if(!tem)
        {
            if(T->rchild)
                return GetSibling(T->rchild,e);
            else
                return NULL;
        }
        else
            return tem;
    }
    else if(T->rchild)
    {
        return GetSibling(T->rchild,e);
    }
    return NULL;
}

/*
    函数名称：GetParent
    函数功能：获得父结点
    函数参数：二叉树T地址，关键字e
    函数返回值：e对应的结点的父结点的指针
*/
BiTree GetParent(BiTree T,int e)
{
    if(!T)
        return NULL;
    static BiTree tem=NULL;
    if(T->lchild&&T->lchild->key==e)
        return T;
    if(T->rchild&&T->rchild->key==e)
        return T;
    if(T->lchild)
    {
        tem=GetParent(T->lchild,e);
        if(!tem)
        {
            if(T->rchild)
                return GetParent(T->rchild,e);
            else
                return NULL;
        }
        else
            return tem;
    }
    else if(T->rchild)
    {
        return GetParent(T->rchild,e);
    }
    return NULL;
}

/*
    函数名称：InsertNode
    函数功能：插入结点
    函数参数：二叉树T地址，关键字e，插入位置LR，插入结点c
    函数返回值：状态参数status
*/

status InsertNode(BiTree T,int e,int LR,BiNode *c)
{
    if(LocateNode(T,c->key)!=NULL)
        return INFEASTABLE;
    BiTree p=LocateNode(T,e);
    if(!p)
        return FALSE;
    BiTree l=p->lchild,r=p->rchild;
    p->lchild=p->rchild=NULL;
    if(LR==0)
        p->lchild=c;
    else
        p->rchild=c;
    if(l&&r)
    {
        c->lchild=l;
        c->rchild=r;
    }
    else if(l)
    {
        c->rchild=l;
        c->lchild=NULL;
    }
    else if(r)
    {
        c->rchild=r;
        c->lchild=NULL;
    }
    return OK;
}

/*
    函数名称：DeleteNode
    函数功能：删除结点
    函数参数：二叉树T，待删除结点关键字e
    函数返回值：状态参数status
*/

status DeleteNode(BiTree *T,int e)
{
    BiTree p=LocateNode(*T,e);
    if(!p)
        return INFEASTABLE;
    BiTree l=p->lchild,r=p->rchild,f=GetParent(*T,e),tem;
    if(l&&r)
    {
        if(!f)
            *T=l;
        else if(f->lchild==p)
            f->lchild=l;
        else
            f->rchild=l;
        tem=l;
        while(tem->rchild!=NULL)
            tem=tem->rchild;
        tem->rchild=r;
    }
    else if(l&&!r)
    {
        if(!f)
            *T=l;
        else if(f->lchild==p)
            f->lchild=l;
        else
            f->rchild=l;
    }
    else if(!l&&r)
    {
        if(!f)
            *T=r;
        else if(f->lchild==p)
            f->lchild=r;
        else
            f->rchild=r;
    }
    else if(!l&&!r)
    {
        if(!f)
            *T=NULL;
        else if(f->lchild==p)
            f->lchild=NULL;
        else
            f->rchild=NULL;
    }
    free(p);
    return OK;
}

/*
    函数名称：Visit
    函数功能：访问结点
    函数参数：待访问的结点地址
    函数返回值：状态参量status
*/

status Visit(BiTree T)
{
    printf("%c ",T->data);
    return OK;
}

/*
    函数名称：PreOrderTraverse
    函数功能：前序遍历
    函数参数：二叉树T地址
    函数返回值：状态参数status
*/

status PreOrderTraverse(BiTree T,status (*Visit)(BiTree))
{
    BiTree p;
    mystack *s=NULL;
    p=T;
    while(p||!stackempty(s))
    {
        if(p)
        {
            Visit(p);
            s=push(&s,p->rchild);
            p=p->lchild;
        }
        else
            s=pop(&s,&p);
    }
    return OK;
}

/*
    函数名称：InOrderTraverse
    函数功能：中序遍历
    函数参数：二叉树地址
    函数返回值：状态参数status
*/

status InOrderTraverse(BiTree T,status (*Visit)(BiTree))
{
    if(T)
    {
        InOrderTraverse(T->lchild,Visit);
        Visit(T);
        InOrderTraverse(T->rchild,Visit);
    }
    return OK;
}
/*
    函数名称：PostOrderTraverse
    函数功能：后序遍历
    函数参数：二叉树地址
    函数返回值：状态参数status
*/

status PostOrderTraverse(BiTree T,status(*Visit)(BiTree))
{
    if(T)
    {
        PostOrderTraverse(T->lchild,Visit);
        PostOrderTraverse(T->rchild,Visit);
        Visit(T);
    }
    return OK;
}

/*
    函数名称：LevelOrderTraverse
    函数功能：层序遍历
    函数参数：二叉树地址
    函数返回值：状态参数status
*/

status LevelOrderTraverse(BiTree T,status(*Visit)(BiTree))
{
    linkqueue q;
    Initqueue(&q);
    BiTree p;
    if(T)
        Enqueue(&q,T);
    while(!queueempty(q))
    {
        Dequeue(&q,&p);
        Visit(p);
        if(p->lchild)
            Enqueue(&q,p->lchild);
        if(p->rchild)
            Enqueue(&q,p->rchild);
    }
    return OK;
}

/*
    函数名称：ReadFile
    函数功能：文件读入
    函数参数：二叉树地址，文件名
    函数返回值：状态参数status
*/

status ReadFile(BiTree *T,char *c)
{
    FILE *fp;
    if((fp=fopen(c,"r"))==NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    CreateBiTreeWithKey(T,fp);
    fclose(fp);
    return OK;
}

/*
    函数名称：WriteFile
    函数功能：文件写
    函数参数：线性表L地址
    函数返回值：状态参数status
*/

status WriteFile(BiTree T,char *c)
{
    FILE *fp;
    if ((fp=fopen(c,"w"))==NULL)
	{
	    printf("File open error\n ");
	    return ERROR;
	}
	BiTree p;
    mystack *s=NULL;
    p=T;
    while(p||!stackempty(s))
    {
        if(p)
        {
            fprintf(fp,"%d %c\n",p->key,p->data);
            s=push(&s,p->rchild);
            p=p->lchild;
        }
        else
        {
            s=pop(&s,&p);
            fprintf(fp,"-1 #\n");
        }
    }
    fprintf(fp,"-1 #\n");
    fclose(fp);
    return OK;
}

/*
    函数名称：Initqueue
    函数功能：初始化队列
    函数参数：队列q
    函数返回值：状态参数status
*/

status Initqueue(linkqueue *q)
{
    q->front=q->rear=(qnode *)malloc(sizeof(qnode));
    if(!q->front)return OVERFLOW;
    q->front->next=NULL;
    return OK;
}

/*
    函数名称：Enqueue
    函数功能：入队
    函数参数：队列q，待入队的元素值
    函数返回值：状态参数status
*/

status Enqueue(linkqueue *q,qElemType e)
{
    qnode *p=(qnode *)malloc(sizeof(qnode));
    if(!p)
        return OVERFLOW;
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return OK;
}

/*
    函数名称：Dequeue
    函数功能：出队
    函数参数：队列q
    函数返回值：状态参数status
*/

status Dequeue(linkqueue *q,qElemType *e)
{
    qnode *p;
    if(q->front==q->rear)
        return INFEASTABLE;
    p=q->front->next;
    *e=p->data;
    q->front->next=p->next;
    if(q->rear==p)
        q->rear=q->front;
    free(p);
    return OK;
}


/*
    函数名称：queueempty
    函数功能：判断队列是否为空
    函数参数：队列q
    函数返回值：状态参数status
*/

status queueempty(linkqueue q)
{
    if(q.front==q.rear)
        return TRUE;
    return FALSE;
}

/*
    函数名称：push
    函数功能：入栈
    函数参数：栈顶指针地址，待入栈元素值
    函数返回值：栈顶指针地址
*/

mystack *push(mystack **top,sElemType c)
{
    mystack *p=(mystack *)malloc(sizeof(mystack));
    p->data=c;
    p->next=*top;
    *top=p;
    return *top;
}

/*
    函数名称：pop
    函数功能：出栈
    函数参数：栈顶指针地址，存储出栈元素值的变量
    函数返回值：栈顶指针地址
*/

mystack *pop(mystack **top,sElemType *c)
{
    mystack *p;
    if(*top==NULL)
        return NULL;
    p=*top;
    (*c)=p->data;
    *top=(*top)->next;
    free(p);
    return *top;
}

/*
    函数名称：stackempty
    函数功能：判断栈是否为空
    函数参数：栈q
    函数返回值：状态参数status
*/

status stackempty(mystack *top)
{
    if(top==NULL)
        return TRUE;
    return FALSE;
}
