/* Linear Table On Sequence Structure */
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
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

status InitList(SqList *L);
status DestroyList(SqList *L);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType *e);
int LocateElem(SqList L,ElemType e,status(*compare)(ElemType,ElemType));
status PriorElem(SqList L,ElemType cue,ElemType *pre,status(*compare)(ElemType,ElemType));
status NextElem(SqList L,ElemType cue,ElemType *next,status(*compare)(ElemType,ElemType));
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L,int i,ElemType *e);
status ListTraverse(SqList L);
status compare(ElemType a,ElemType b);
status ReadFile(SqList *L,char *c);
status WriteFile(SqList L,char *c);
/*--------------------------------------------*/

int main(void)
{
    status(*p)(ElemType,ElemType);
    p=compare;
    int op=1,i,t,listi=0;
    SqList l[LISTNUM];
    ElemType e;
    status s;
    char c[100];
    for(i=0;i<LISTNUM;i++)
    {
        l[i].elem=NULL;
        l[i].length=0;
        l[i].listsize=0;
    }
    while(op){
	    system("cls");	printf("\n\n");
	    printf("      Menu for Linear Table On Sequence Structure \n");
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
		        printf("�����������ѯ��Ԫ��λ�ã�\n��Χ��1��%d!\n",l[listi].length);
		        scanf("%d",&i);
		        s=GetElem(l[listi],i,&e);
		        while(s==ERROR)
                {
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",l[listi].length);
                    scanf("%d",&i);
                    s=GetElem(l[listi],i,&e);
                }
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
                printf("��������Ҫ�����λ�ã���Χ����1��%d\n",l[listi].length+1);
                scanf("%d",&i);
		        s=ListInsert(&l[listi],i,e);
		        while(s==ERROR)
                {
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",l[listi].length+1);
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
		        printf("��������Ҫɾ����λ�ã���Χ����1��%d\n",l[listi].length);
		        scanf("%d",&i);
                s=ListDelete(&l[listi],i,&e);
		        while(s==ERROR)
                {
                    printf("��������ȷ��λ��ֵ!��Χ����1��%d\n",l[listi].length);
                    scanf("%d",&i);
                    s=ListDelete(&l[listi],i,&e);
                }
                if(s==INFEASTABLE&&l[listi].length==0)
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
status InitList(SqList *L)
{
	if(L->elem)
        return INFEASTABLE;
	L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) exit(OVERFLOW);
	    L->length=0;
    L->listsize=LIST_INIT_SIZE;
	return OK;
}

/*
    �������ƣ�DestroyList
    �������ܣ��������Ա�L
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
*/
status DestroyList(SqList *L)
{
    if(!L->elem)
        return INFEASTABLE;
    free(L->elem);
    L->elem=NULL;
    L->length=0;
    L->listsize=0;
    return OK;
}

/*
    �������ƣ�ClearList
    �������ܣ�������Ա�L
    �������������Ա�L��ַ
    ��������ֵ��״̬����status
*/
status ClearList(SqList *L)
{
    if(!L->elem)
        return INFEASTABLE;
    L->length=0;
    return OK;
}

/*
    �������ƣ�ListEmpty
    �������ܣ��ж����Ա�L�Ƿ�Ϊ��
    �������������Ա�L
    ��������ֵ��״̬����status
*/
status ListEmpty(SqList L)
{
    if(!L.elem)
        return INFEASTABLE;
    if(L.length==0)
        return TRUE;
    return FALSE;
}

/*
    �������ƣ�ListLength
    �������ܣ������Ա�L��
    �������������Ա�L
    ��������ֵ��int�Ͳ���
*/
int ListLength(SqList L)
{
    if(!L.elem)
        return INFEASTABLE;
    return L.length;
}

/*
    ��������:GetElem
    �������ܣ���e����L�е�i������Ԫ�ص�ֵ
    �������������Ա�L����ȡ����λ��i,ȡ��Ԫ��ֵ����λ��e
    ��������ֵ��״̬����status
*/
status GetElem(SqList L,int i,ElemType *e)
{
    if(!L.elem)
        return INFEASTABLE;
    if(i<=0||i>L.length)
        return ERROR;
    *e=L.elem[i-1];
    return OK;
}

/*
    �������ƣ�LocateElem
    �������ܣ����Ҳ��������Ա�L�е�һ����e�����ϵcompare������ϵ������Ԫ�ص�λ��
    �������������Ա�L��ElemType e��compare����ָ��
    ��������ֵ����e�����ϵcompare������ϵ������Ԫ�ص�λ��
*/
int LocateElem(SqList L,ElemType e,status(*compare)(ElemType,ElemType))
{
    if(!L.elem)
        return INFEASTABLE;
    int i;
    for(i=0;i<L.length;i++)
        if(compare(e,L.elem[i]))
            return i+1;
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
status PriorElem(SqList L,ElemType cue,ElemType *pre,status(*compare)(ElemType,ElemType))
{
    if(!L.elem)
        return INFEASTABLE;
    int i;
    for(i=0;i<L.length;i++)
    {
        if(compare(cue,L.elem[i])&&i!=0)
        {
            *pre=L.elem[i-1];
            return OK;
        }
    }
    return FALSE;
}

/*
    �������ƣ�NextElem
    �������ܣ�Ѱ��ֵΪ����ֵ�ĵ�һ���ڵ�ĺ��
    �������������Ա�L������ѯ��ֵcue�������̽ڵ�ֵ�ı�����ָ�룬compare����ָ��
    ��������ֵ��״̬����status
*/
status NextElem(SqList L,ElemType cue,ElemType *next,status(*compare)(ElemType,ElemType))
{
    if(!L.elem)
        return INFEASTABLE;
    int i;
    for(i=0;i<L.length;i++)
    {
        if(compare(cue,L.elem[i])&&i!=L.length-1)
        {
            *next=L.elem[i+1];
            return OK;
        }
    }
    return FALSE;
}

/*
    �������ƣ�ListInsert
    �������ܣ���L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
    �������������Ա�L������λ��i������Ԫ��e
    ��������ֵ��״̬����status
*/
status ListInsert(SqList *L,int i,ElemType e)
{
    if(!L->elem)
        return INFEASTABLE;
    if(i<1||i>L->length+1)
        return ERROR;
    i-=1;
    int j;
    if(L->length==L->listsize)
    {
        ElemType *newbase;
        newbase=(ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            return OVERFLOW;
        L->elem=newbase;
        L->listsize+=LISTINCREMENT;
    }
    for(j=L->length-1;j>=i;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i]=e;
    L->length++;
    return OK;
}

/*
    �������ƣ�ListDelete
    �������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ
    �������������Ա�L��ɾ��Ԫ��λ��i,�洢ɾ��ֵ������ָ��
    ��������ֵ��״̬����status
*/
status ListDelete(SqList *L,int i,ElemType *e)
{
    if(!L->elem||L->length==0)
        return INFEASTABLE;
    if(i<1||i>L->length)
        return ERROR;
    i-=1;
    int j;
    *e=L->elem[i];
    for(j=i;j<L->length-1;j++)
        L->elem[j]=L->elem[j+1];
    L->length--;
    return OK;
}

/*
    �������ƣ�ListTraverse
    �������ܣ������������Ա�
    �������������Ա�L
    ��������ֵ��״̬����status
*/
status ListTraverse(SqList L)
{
    if(!L.elem)
        return INFEASTABLE;
    int i;
    printf("\n-----------all elements -----------------------\n");
    for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}

/*
    �������ƣ�ReadFile
    �������ܣ����ļ��ж�ȡ���ݲ��洢�����Ա���
    �������������Ա�L�ĵ�ַ���ļ���ַ
    ��������ֵ��״̬����status
*/
status ReadFile(SqList *L,char *c)
{
    if(!L->elem)
        return INFEASTABLE;
    FILE *fp;
    L->length=0;
    if((fp=fopen(c,"r"))==NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    while(fscanf(fp,"%d",&L->elem[L->length])!=EOF)
    {
        if(L->length+1==L->listsize)
        {
            ElemType *newbase;
            newbase=(ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
            if(!newbase)
                return OVERFLOW;
            L->elem=newbase;
            L->listsize+=LISTINCREMENT;
        }
        L->length++;
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
status WriteFile(SqList L,char *c)
{
    if(!L.elem)
        return INFEASTABLE;
    FILE *fp;
    int i=0;
    if ((fp=fopen(c,"w"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}
    while(i<L.length)
        fprintf(fp,"%d ",L.elem[i++]);
    fclose(fp);
    return OK;
}
