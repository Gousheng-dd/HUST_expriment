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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //���Ա���ʽ�ṹ���Ķ���
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
	    printf("���Ƚ��в���15��ѡ����Ҫ��������Ա�����Ĭ��Ϊ��һ�����Ա�\n");
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
	    printf("    ��ѡ����Ĳ���[0~15]:");
	    scanf("%d",&op);
	    while(op<0||op>15)
        {
            printf("��������ȷ�Ĳ�������Χ[0~15]\n");
            scanf("%d",&op);
        }
        switch(op){
	        case 1:
		        //printf("\n----IntiList���ܴ�ʵ�֣�\n");
		        s=InitList(&l[listi]);
		        if(s==OK) printf("���Ա�%d�����ɹ���\n",listi+1);
                else if(s==INFEASTABLE)
                    printf("���Ա�%d�Ѿ������������ظ�������\n",listi+1);
                else
                    printf("���Ա�%d����ʧ�ܣ�\n",listi+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyList���ܴ�ʵ�֣�\n");
		        if(DestroyList(&l[listi])==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����Ϊ�գ�\n",listi+1);
                else
                    printf("���Ա�%d�ɹ�����",listi+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----ClearList���ܴ�ʵ�֣�\n");
		        if(ClearList(&l[listi])==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ�����Ѿ�Ϊ�գ�\n",listi+1);
                else
                    printf("���Ա�%d�ɹ���գ�\n",listi+1);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
		        s=ListEmpty(l[listi]);
		        if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(s==TRUE)
                    printf("���Ա�%dΪ�գ�\n",listi+1);
                else
                    printf("���Ա�%d�ǿգ�\n",listi+1);
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----ListLength���ܴ�ʵ�֣�\n");
                if(ListLength(l[listi])==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else
                    printf("���Ա�%d�ĳ���Ϊ%d!\n",listi+1,ListLength(l[listi]));
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----GetElem���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ��λ�ã�\n��Χ��1��%d!\n",ListLength(l[listi]));
		        scanf("%d",&i);
		        s=GetElem(l[listi],i,&e);
		        if(s==ERROR)
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",ListLength(l[listi]));
		        if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(s==OK)
                    printf("���Ա�%d��%d��Ԫ�ص�ֵΪ��%d\n",listi+1,i,e);
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ�ص�ֵ��\n");
		        scanf("%d",&e);
		        t=LocateElem(l[listi],e,p);
                if(t==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(t!=0)
                    printf("���ѯ��ֵ%d��һ�γ��������Ա�%d��%d��λ�ã�\n",e,listi+1,t);
                else
                    printf("���ѯ��ֵ%d�ڱ�%d�в����ڣ�\n",e,listi+1);
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----PriorElem���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ�ص�ֵ��\n");
		        scanf("%d",&e);
		        s=PriorElem(l[listi],e,&t,p);
		        if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(s==OK)
                    printf("�����Ա�%d�е�һ�������ѯ��ֵ%dƥ���Ԫ�ص�ǰ��Ϊ%d��\n",listi+1,e,t);
                else
                    printf("���ѯ��ֵ%d��ǰ���ڱ�%d�в����ڣ�\n",e,listi+1);
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----NextElem���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ��Ԫ�ص�ֵ��\n");
		        scanf("%d",&e);
		        s=NextElem(l[listi],e,&t,p);
		        if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(s==OK)
                    printf("�����Ա�%d�е�һ�������ѯ��ֵ%dƥ���Ԫ�صĺ��Ϊ%d��\n",listi+1,e,t);
                else
                    printf("���ѯ��ֵ%d�ĺ���ڱ�%d�в����ڣ�\n",e,listi+1);
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----ListInsert���ܴ�ʵ�֣�\n");
		        printf("��������Ҫ�����Ԫ�أ�\n");
		        scanf("%d",&e);
                printf("��������Ҫ�����λ�ã���Χ����1��%d\n",ListLength(l[listi])+1);
                scanf("%d",&i);
		        s=ListInsert(&l[listi],i,e);
		        while(s==ERROR)
                {
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",ListLength(l[listi])+1);
                    scanf("%d",&i);
                    s=ListInsert(&l[listi],i,e);
                }
		        if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
                else if(s==OVERFLOW)
                    printf("�ڴ�������\n");
                else
                    printf("�����Ա�%d����ɹ���\n",listi+1);
                getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----ListDelete���ܴ�ʵ�֣�\n");
		        printf("��������Ҫɾ����λ�ã���Χ����1��%d\n",ListLength(l[listi]));
		        scanf("%d",&i);
                s=ListDelete(&l[listi],i,&e);
		        while(s==ERROR)
                {
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",ListLength(l[listi]));
                    scanf("%d",&i);
                    s=ListDelete(&l[listi],i,&e);
                }
                if(s==INFEASTABLE&&ListLength(l[listi])==0)
                    printf("���Ա�%dΪ�ջ�δ��ʼ����\n",listi+1);
                else
                    printf("ɾ���ɹ���ɾ����Ԫ��ֵΪ��%d\n",e);
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----ListTraverse���ܴ�ʵ�֣�\n");
                s=ListTraverse(l[listi]);
		        if(!s) printf("���Ա�%d�ǿձ�\n",listi+1);
		        else if(s==INFEASTABLE)
                    printf("���Ա�%dδ��ʼ����\n",listi+1);
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----ReadFile���ܴ�ʵ�֣�\n");
                printf("������Ҫ������ļ�����\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&l[listi],c);
                if(s==INFEASTABLE)
                    printf("���Ա�δ��ʼ����\n");
		        else if(s==ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else
                    printf("�ļ�����ɹ���\n");
		        getchar();getchar();
		        break;
            case 14:
                //printf("\n----WriteFile���ܴ�ʵ�֣�\n");
		        printf("������Ҫ������ļ�����\n");
                getchar();
                scanf("%s",c);
                s=WriteFile(l[listi],c);
                if(s==INFEASTABLE)
                    printf("���Ա�δ��ʼ����\n");
		        else if(s==ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else
                    printf("�ļ�����ɹ���\n");
		        getchar();getchar();
		        break;
            case 15:
                printf("��������Ҫ���������Ա���ţ���Χ[1��%d]��\n",LISTNUM);
		        scanf("%d",&i);
		        while(i<1||i>LISTNUM)
                {
                    printf("��������ȷ�ķ�Χ[1��%d]��\n",LISTNUM);
                    scanf("%d",&i);
                }
                printf("���ѳɹ�ѡ���%d�����Ա�\n",i);
                listi=i-1;
		        getchar();getchar();

		        break;

        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()

/*
    ��������:InitList
    �������ܣ�����һ���յ����Ա�
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�DestroyList
    �������ܣ��������Ա�L
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�ClearList
    �������ܣ�������Ա�L
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
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
    �������ƣ�ListEmpty
    �������ܣ��ж����Ա�L�Ƿ�Ϊ��
    �������������Ա�L
    ��������ֵ��״̬����status
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
    �������ƣ�ListLength
    �������ܣ������Ա�L��
    �������������Ա�L
    ��������ֵ��int�Ͳ���
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
    ��������:GetElem
    �������ܣ���e����L�е�i������Ԫ�ص�ֵ
    �������������Ա�L����ȡ����λ��i,ȡ��Ԫ��ֵ����λ��e
    ��������ֵ��״̬����status
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
    �������ƣ�LocateElem
    �������ܣ����Ҳ��������Ա�L�е�һ����e�����ϵcompare������ϵ������Ԫ�ص�λ��
    �������������Ա�L��ElemType e��compare����ָ��
    ��������ֵ����e�����ϵcompare������ϵ������Ԫ�ص�λ��
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
    �������ƣ�compare
    �������ܣ��Ƚ�ElemType���ͱ���a��b
    ����������ElemType a��ElemType b
    ��������ֵ��״̬����status
*/
status compare(ElemType a,ElemType b)
{
    if(a==b)
        return TRUE;
    else
        return FALSE;
}

/*
    �������ƣ�PriorElem
    �������ܣ�����ֵ�͸���ֵ��ͬ�ĵ�һ���ڵ��ǰ��
    �������������Ա�L������ѯ��ֵcue������ǰ���ڵ�ı���ָ�룬compare����ָ��
    ��������ֵ��״̬����status
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
    �������ƣ�NextElem
    �������ܣ�Ѱ��ֵΪ����ֵ�ĵ�һ���ڵ�ĺ��
    �������������Ա�L������ѯ��ֵcue�������̽ڵ�ֵ�ı�����ָ�룬compare����ָ��
    ��������ֵ��״̬����status
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
    �������ƣ�ListInsert
    �������ܣ���L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
    �������������Ա�L������λ��i������Ԫ��e
    ��������ֵ��״̬����status
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
    �������ƣ�ListDelete
    �������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ
    �������������Ա�L��ɾ��Ԫ��λ��i,�洢ɾ��ֵ������ָ��
    ��������ֵ��״̬����status
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
    �������ƣ�ListTraverse
    �������ܣ������������Ա�
    �������������Ա�L
    ��������ֵ��״̬����status
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
    �������ƣ�ReadFile
    �������ܣ����ļ��ж�ȡ���ݲ��洢�����Ա���
    �������������Ա�L�ĵ�ַ���ļ���ַ
    ��������ֵ��״̬����status
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
    �������ƣ�WriteFile
    �������ܣ������Ա�L�е����ݴ������ļ���
    �������������Ա�L���ļ���ַ
    ��������ֵ��״̬����status
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
