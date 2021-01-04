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
typedef char ElemType; //����Ԫ�����Ͷ���

typedef struct BiNode{  //����������ʽ�ṹ���Ķ���
	int key;
	ElemType data;
	struct BiNode *lchild,*rchild;
}BiNode,*BiTree;

typedef BiTree qElemType;
typedef struct qnode
{
    qElemType data;
    struct qnode *next;
}qnode;//����Ԫ��

typedef struct
{
    qnode *front;
    qnode *rear;
}linkqueue;//����

typedef BiTree sElemType;
typedef struct node
{
    sElemType data;
    struct node *next;
}mystack;//ջ
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
	    printf("���Ƚ��в���17��ѡ����Ҫ����Ķ�����������Ĭ��Ϊ��һ��������\n");
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
	    printf("    ��ѡ����Ĳ���[0~17]:");
	    scanf("%d",&op);
	    while(op<0||op>17)
        {
            printf("��������ȷ�Ĳ�������Χ[0~17]\n");
            scanf("%d",&op);
        }
        switch(op){
	        case 1:
		        //printf("\n---- CreateBiTree���ܴ�ʵ�֣�\n");
		        printf("������һ�д��������Ķ�����ǰ��������У��س���������\n");
		        getchar();
		        scanf("%s",c);
		        num=now=0;
		        s=CreateBiTree(&bt[treei],c);
		        if(s==OK) printf("������%d�����ɹ���\n",treei+1);
                else
                    printf("������%d����ʧ�ܣ�\n",treei+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyBiTree���ܴ�ʵ�֣�\n");
		        if(DestroyBiTree(&bt[treei])==INFEASTABLE)
                    printf("������%dδ������\n",treei+1);
                else
                    printf("������%d�ɹ�����",treei+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----ClearBiTree���ܴ�ʵ�֣�\n");
		        if(ClearBiTree(&bt[treei])==INFEASTABLE)
                    printf("������%dδ������\n",treei+1);
                else
                    printf("������%d�ɹ���գ�\n",treei+1);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----BiTreeEmpty���ܴ�ʵ�֣�\n");
		        s=BiTreeEmpty(bt[treei]);
                if(s==TRUE)
                    printf("������%dΪ�գ�\n",treei+1);
                else
                    printf("������%d�ǿգ�\n",treei+1);
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----BiTreeDepth���ܴ�ʵ�֣�\n");
                Len=BiTreeDepth(bt[treei]);
                if(Len==0)
                    printf("������%dΪ�ջ�δ��ʼ����\n",treei+1);
                else
                    printf("������%d�ĳ���Ϊ%d!\n",treei+1,Len);
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----LocateNode���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ�عؼ��֣�\n");
		        scanf("%d",&i);
		        tt=LocateNode(bt[treei],i);
		        if(tt==NULL)
                    printf("���ҵ�Ԫ�ز����ڣ�\n");
                else
                {
                    printf("���ѯ��Ԫ��Ϊ��\n");
                    Visit(tt);
                }
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----Assign���ܴ�ʵ�֣�\n");
		        printf("���������븳ֵ��Ԫ�صĹؼ��ּ����ݣ�\n");
		        char value;
		        scanf("%d %c",&e,&value);
		        t=Assign(bt[treei],e,value);
                if(t==FALSE)
                    printf("���ѯ��Ԫ���ڶ�����%d�в����ڣ�\n",treei+1);
                else
                    printf("��ֵ�ɹ���\n");
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----GetSibling���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ�صĹؼ��֣�\n");
		        scanf("%d",&e);
		        tt=GetSibling(bt[treei],e);
		        if(tt==NULL)
                    printf("���ѯ��Ԫ�ص��ֵܽ�㲻���ڣ�\n");
                else
                {
                    printf("���ѯ�Ĺؼ���%d�Ľ����ֵ��ڱ�%d�е�ֵΪ��",e,treei+1);
                    Visit(tt);
                }
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----InsertNode���ܴ�ʵ�֣�\n");
		        printf("��������������Ԫ�ص�ֵ��\n");
		        char v;
		        int pos,id;
		        getchar();
		        scanf("%c",&v);
		        printf("��������������Ԫ�صĸ����Ĺؼ��֣�\n");
		        scanf("%d",&e);
		        printf("��������������Ԫ�ص�λ�ã�0Ϊ��1Ϊ�ң�\n");
		        scanf("%d",&pos);
		        while(pos!=0&&pos!=1)
                {
                    printf("��������������Ԫ�ص�λ�ã�0Ϊ��1Ϊ�ң�\n");
                    scanf("%d",&pos);
                }
                printf("��������Ҫ������Ĺؼ��֣�\n");
                scanf("%d",&id);
                tem=(BiTree)malloc(sizeof(BiNode));
                tem->data=v;
                tem->key=id;
                tem->lchild=NULL;
                tem->rchild=NULL;
		        s=InsertNode(bt[treei],e,pos,tem);
		        if(s==FALSE)
                    printf("���%d�ڶ�����%d�в����ڣ�\n",e,treei+1);
                else if(s==INFEASTABLE)
                    printf("������Ĺؼ����Ѵ��ڣ�����ʧ�ܣ�\n");
                else
                    printf("����ɹ���\n");
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----DeleteNode���ܴ�ʵ�֣�\n");
		        printf("��������Ҫɾ����Ԫ�عؼ��֣�\n");
		        scanf("%d",&e);
		        s=DeleteNode(&bt[treei],e);
		        if(s==INFEASTABLE)
                    printf("�ؼ���%d�ڶ�����%d�����ڣ�\n",e,treei+1);
                else
                    printf("ɾ���ɹ���\n");
                getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----PreOrderTraverse���ܴ�ʵ�֣�\n");
		        PreOrderTraverse(bt[treei],p);
                printf("ǰ�����������\n");
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----InOrderTraverse���ܴ�ʵ�֣�\n");
                InOrderTraverse(bt[treei],p);
                printf("�������������\n");
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----PostOrderTraverse���ܴ�ʵ�֣�\n");
                PostOrderTraverse(bt[treei],p);
                printf("�������������\n");
		        getchar();getchar();
		        break;
            case 14:
                //printf("\n----LevelOrderTraverse���ܴ�ʵ�֣�\n");
                LevelOrderTraverse(bt[treei],p);
                printf("�������������\n");
		        getchar();getchar();
		        break;
		    case 15:
                //printf("\n----ReadFile���ܴ�ʵ�֣�\n");
                printf("������Ҫ������ļ�����\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&bt[treei],c);
		        if(s==ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else
                    printf("�ļ�����ɹ���\n");
		        getchar();getchar();
		        break;
            case 16:
                //printf("\n----WriteFile���ܴ�ʵ�֣�\n");
		        printf("������Ҫ������ļ�����\n");
                getchar();
                scanf("%s",c);
                s=WriteFile(bt[treei],c);
		        if(s==ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else
                    printf("�ļ�����ɹ���\n");
		        getchar();getchar();
		        break;
            case 17:
                printf("��������Ҫ�����Ķ�������ţ���Χ[1��%d]��\n",TREENUM);
		        scanf("%d",&i);
		        while(i<1||i>TREENUM)
                {
                    printf("��������ȷ�ķ�Χ[1��%d]��\n",TREENUM);
                    scanf("%d",&i);
                }
                printf("���ѳɹ�ѡ���%d����������\n",i);
                treei=i-1;
		        getchar();getchar();
		        break;

        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()

/*
    �������ƣ�CreateBiTree
    �������ܣ����ݴ��������Ķ�����ǰ��������д���������
    ����������������T�����������Ķ�����ǰ���������definition�����ؼ���num
    ��������ֵ��״̬����status
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
    �������ƣ�CreateBiTreeWithKey
    �������ܣ����ݴ��������͹ؼ��ֵĶ�����ǰ��������д���������
    ����������������T,���������͹ؼ��ֵĶ�����ǰ���������
    ��������ֵ��״̬����status
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
    �������ƣ�DestroyBiTree
    �������ܣ����ٶ�����T
    ������������������ַ
    ��������ֵ��״̬����status
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
    �������ƣ�ClearBiTree
    �������ܣ���ն�����T
    ����������������T��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�BiTreeEmpty
    �������ܣ��ж϶�����T�Ƿ�Ϊ��
    ����������������T
    ��������ֵ��״̬����status
*/

status BiTreeEmpty(BiTree T)
{
    if(T==NULL)
        return TRUE;
    else
        return FALSE;
}

/*
    �������ƣ�BiTreeDepth
    �������ܣ�����������
    ����������������T
    ��������ֵ�����
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
    �������ƣ�LocateNode
    �������ܣ����ҽ��
    ����������������T�����ؼ���e
    ��������ֵ����Ӧ����ַ
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
    �������ƣ�Assign
    �������ܣ���㸳ֵ
    ����������������ָ��T�����ؼ���e������ֵvalue
    ��������ֵ��״̬����status
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
    �������ƣ�GetSibling
    �������ܣ�����ֵܽ��
    ����������������T��
    ��������ֵ��״̬����status
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
    �������ƣ�GetParent
    �������ܣ���ø����
    ����������������T��ַ���ؼ���e
    ��������ֵ��e��Ӧ�Ľ��ĸ�����ָ��
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
    �������ƣ�InsertNode
    �������ܣ�������
    ����������������T��ַ���ؼ���e������λ��LR��������c
    ��������ֵ��״̬����status
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
    �������ƣ�DeleteNode
    �������ܣ�ɾ�����
    ����������������T����ɾ�����ؼ���e
    ��������ֵ��״̬����status
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
    �������ƣ�Visit
    �������ܣ����ʽ��
    ���������������ʵĽ���ַ
    ��������ֵ��״̬����status
*/

status Visit(BiTree T)
{
    printf("%c ",T->data);
    return OK;
}

/*
    �������ƣ�PreOrderTraverse
    �������ܣ�ǰ�����
    ����������������T��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�InOrderTraverse
    �������ܣ��������
    ������������������ַ
    ��������ֵ��״̬����status
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
    �������ƣ�PostOrderTraverse
    �������ܣ��������
    ������������������ַ
    ��������ֵ��״̬����status
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
    �������ƣ�LevelOrderTraverse
    �������ܣ��������
    ������������������ַ
    ��������ֵ��״̬����status
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
    �������ƣ�ReadFile
    �������ܣ��ļ�����
    ������������������ַ���ļ���
    ��������ֵ��״̬����status
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
    �������ƣ�WriteFile
    �������ܣ��ļ�д
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�Initqueue
    �������ܣ���ʼ������
    ��������������q
    ��������ֵ��״̬����status
*/

status Initqueue(linkqueue *q)
{
    q->front=q->rear=(qnode *)malloc(sizeof(qnode));
    if(!q->front)return OVERFLOW;
    q->front->next=NULL;
    return OK;
}

/*
    �������ƣ�Enqueue
    �������ܣ����
    ��������������q������ӵ�Ԫ��ֵ
    ��������ֵ��״̬����status
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
    �������ƣ�Dequeue
    �������ܣ�����
    ��������������q
    ��������ֵ��״̬����status
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
    �������ƣ�queueempty
    �������ܣ��ж϶����Ƿ�Ϊ��
    ��������������q
    ��������ֵ��״̬����status
*/

status queueempty(linkqueue q)
{
    if(q.front==q.rear)
        return TRUE;
    return FALSE;
}

/*
    �������ƣ�push
    �������ܣ���ջ
    ����������ջ��ָ���ַ������ջԪ��ֵ
    ��������ֵ��ջ��ָ���ַ
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
    �������ƣ�pop
    �������ܣ���ջ
    ����������ջ��ָ���ַ���洢��ջԪ��ֵ�ı���
    ��������ֵ��ջ��ָ���ַ
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
    �������ƣ�stackempty
    �������ܣ��ж�ջ�Ƿ�Ϊ��
    ����������ջq
    ��������ֵ��״̬����status
*/

status stackempty(mystack *top)
{
    if(top==NULL)
        return TRUE;
    return FALSE;
}
