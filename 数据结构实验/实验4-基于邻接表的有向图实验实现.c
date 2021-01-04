#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -3
#define INFEASTABLE -1
#define OVERFLOW -2
#define EQU -4
#define GRAPHNUM 10
#define MAX_VERTEX_NUM 100

typedef int status;
typedef char ElemType; //����Ԫ�����Ͷ���

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;

typedef struct VNode{  //ͷ���Ķ���
	int key;
	ElemType data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM+1];

typedef struct ALGraph{
    AdjList vertices;
    int vexnum;
    int arcnum;
}ALGraph;

typedef struct invnode{
    int key;
    ElemType data;
}invnode;

typedef VNode qElemType;
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

ALGraph g[10];
int visited[MAX_VERTEX_NUM+1];
/*--------------------------------------------*/
status CreateCraph(ALGraph *G,invnode *V,int VR[][2]);
status DestroyGraph(ALGraph *G);
int LocateVex(ALGraph G,int u);
status PutVex (ALGraph *G,int u,ElemType value);
int FirstAdjVex(ALGraph G,int u);
int NextAdjVex(ALGraph G,int v,int w);
status InsertVex(ALGraph *G,VNode v);
status DeleteVex(ALGraph *G,int v);
status InsertArc(ALGraph *G,int v,int w);
status DeleteArc(ALGraph *G,int v,int w);
status visit(VNode v);
status DFSTraverse(ALGraph G,status (*visit)(VNode));
void DFS(ALGraph G,int v);
status BFSTraverse(ALGraph G,status (*visit)(VNode));
status ReadFile(ALGraph *G,char *name);
status WriteFile(ALGraph G,char *name);
status Initqueue(linkqueue *q);
status Enqueue(linkqueue *q,qElemType e);
status Dequeue(linkqueue *q,qElemType *e);
status queueempty(linkqueue q);

int main(void)
{
    status(*p)(VNode);
    p=visit;
    invnode vv[100];
    int vr[200][2];
    int op=1,graphi=0,i,vnum,anum,u,v,w;
    ElemType e;
    status s;
    char c[100];
    while(op){
	    system("cls");	printf("\n\n");
	    printf("      Menu for Graph \n");
	    printf("���Ƚ��в���15��ѡ����Ҫ��������Ա�����Ĭ��Ϊ��һ�����Ա�\n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. CreateCraph     9. InsertArc\n");
	    printf("    	  2. DestroyGraph    10. DeleteArc\n");
	    printf("    	  3. LocateVex       11. DFSTraverse \n");
	    printf("    	  4. PutVex          12. BFSTraverse\n");
	    printf("    	  5. FirstAdjVex     13. ReadFile\n");
	    printf("    	  6. NextAdjVex      14. WriteFile\n");
	    printf("    	  7. InsertVex       15. ChooseGraph\n");
	    printf("    	  8. DeleteVex       0. Exit\n");
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
		        //printf("\n----CreateCraph���ܴ�ʵ�֣�\n");
		        printf("������Ҫ������ͼ�Ķ��������\n");
		        scanf("%d",&vnum);
		        g[graphi].vexnum=vnum;
		        printf("������Ҫ������ͼ�Ķ���Ĺؼ��ֺ�������\n");
		        for(i=1;i<=vnum;i++)
                    scanf("%d %s",&vv[i].key,&vv[i].data);
                printf("������Ҫ������ͼ�Ļ�����\n");
                scanf("%d",&anum);
                g[graphi].arcnum=anum;
                printf("������Ҫ������ͼ�Ļ�����λ�����ʽ������1 2��\n");
                for(i=1;i<=anum;i++)
                    scanf("%d %d",&vr[i][0],&vr[i][1]);
		        s=CreateCraph(&g[graphi],vv,vr);
		        if(s==OK) printf("����ͼ%d�����ɹ���\n",graphi+1);
                else
                    printf("����ͼ%d����ʧ�ܣ�\n",graphi+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyGraph���ܴ�ʵ�֣�\n");
		        if(DestroyGraph(&g[graphi])==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else
                    printf("����ͼ%d�ɹ�����",graphi+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----LocateVex���ܴ�ʵ�֣�\n");
		        printf("������Ҫ���ҵĶ���ؼ��֣�\n");
		        scanf("%d",&u);
		        v=LocateVex(g[graphi],u);
		        if(v==-1)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(v==0)
                    printf("�ùؼ���������ͼ%d�в����ڣ�\n",graphi+1);
                else
                    printf("�����ҵĹؼ���������ͼ%dλ��Ϊ%d",graphi+1,v);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----PutVex���ܴ�ʵ�֣�\n");
		        printf("������Ҫ��ֵ�Ķ���ؼ��֣�\n");
		        scanf("%d",&u);
		        getchar();
		        printf("������Ҫ�޸ĵ�ֵ��\n");
		        scanf("%c",&e);
		        s=PutVex(&g[graphi],u,e);
		        if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(s==ERROR)
                    printf("����ͼ%d�в����ڹؼ���Ϊ%d�Ķ��㣡\n",graphi+1,u);
                else
                    printf("��ֵ�ɹ���\n");
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----FirstAdjVex���ܴ�ʵ�֣�\n");
                printf("������Ҫ��ѯ�Ķ���λ��:\n");
                scanf("%d",&u);
                v=FirstAdjVex(g[graphi],u);
                if(v==-1)
                    printf("���Ա�%dδ������\n",graphi+1);
                else if(v==-2)
                    printf("����ͼ%d�в�����λ��Ϊ%d�Ķ���\n",graphi+1,u);
		        else if(v==0)
                    printf("����ҵĶ���û���ڽӵ�\n");
                else
                    printf("�����ҵĽ��ĵ�һ���ڽӵ�λ��Ϊ%d\n",v);
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----NextAdjVex���ܴ�ʵ�֣�\n");
		        printf("�����������ѯ�����λ��\n");
		        scanf("%d",&v);
		        printf("�����������ѯ������Խ���λ��\n");
		        scanf("%d",&w);
		        u=NextAdjVex(g[graphi],v,w);
		        if(u==-1)
                    printf("����ͼ%dδ����\n",graphi+1);
		        else if(u==-2)
                    printf("����ͼ%d�в�����λ��Ϊ%d�Ķ��㣡\n",graphi+1,v);
                else if(u==-3)
                    printf("λ��Ϊ%d�Ķ���û���ڽӵ�\n",v);
                else if(u==-4)
                    printf("����%dû��λ��Ϊ%d���ڽӵ�",v,w);
                else if(u==-5)
                    printf("����%dΪ����%d�����һ���ڽӵ�",w,v);
                else
                    printf("����%d����ڶ���%d����һ���ڽӶ����λ��Ϊ%d",v,w,u);
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----InsertVex���ܴ�ʵ�֣�\n");
		        printf("���������������¶���Ĺؼ��֣�\n");
		        scanf("%d",&u);
		        getchar();
		        printf("���������������¶����������\n");
		        scanf("%c",&e);
		        VNode *t=(VNode *)malloc(sizeof(VNode));
		        t->data=e;
		        t->key=u;
		        t->firstarc=NULL;
		        s=InsertVex(&g[graphi],*t);
                if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(s==ERROR)
                    printf("���붥��Ĺؼ���������ͼ%d���Ѿ����ڣ�\n",graphi+1);
                else
                    printf("����ɹ�\n");
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----DeleteVex���ܴ�ʵ�֣�\n");
		        printf("����������ɾ�����Ĺؼ��֣�\n");
		        scanf("%d",&u);
		        s=DeleteVex(&g[graphi],u);
		        if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(s==ERROR)
                    printf("����ͼ%d�в����ڹؼ���Ϊ%d�Ķ��㣡\n",graphi+1,u);
                else
                    printf("ɾ���ɹ���\n");
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----InsertArc���ܴ�ʵ�֣�\n");
		        printf("������������뻡�������յ��λ��\n");
		        scanf("%d %d",&v,&w);
		        s=InsertArc(&g[graphi],v,w);
		        if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(s==ERROR)
                    printf("������ͼ%d�в�����λ��Ϊ%d��%d�Ķ��㣡\n",graphi+1,v,w);
                else if(s==FALSE)
                    printf("�û��Ѿ����ڣ�\n");
                else if(s==EQU)
                    printf("���ܲ���ָ������Ļ���\n");
                else
                    printf("����ɹ���\n");
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----DeleteArc���ܴ�ʵ�֣�\n");
		        printf("����������ɾ�����������յ��λ��\n");
		        scanf("%d %d",&v,&w);
		        s=DeleteArc(&g[graphi],v,w);
		        if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else if(s==ERROR)
                    printf("������ͼ%d�в�����λ��Ϊ%d��%d�Ķ��㣡\n",graphi+1,v,w);
                else if(s==FALSE)
                    printf("����%d�붥��%d֮��û�л�!\n",v,w);
                else
                    printf("ɾ���ɹ���\n");
		        getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----DFSTraverse���ܴ�ʵ�֣�\n");
                s=DFSTraverse(g[graphi],p);
                if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else
                    printf("�������������������\n");
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----BFSTraverse���ܴ�ʵ�֣�\n");
                s=BFSTraverse(g[graphi],p);
                if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
                else
                    printf("�������������������\n");
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----ReadFile���ܴ�ʵ�֣�\n");
                printf("������Ҫ������ļ�����\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&g[graphi],c);
                if(s==ERROR)
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
                s=WriteFile(g[graphi],c);
                if(s==INFEASTABLE)
                    printf("����ͼ%dδ������\n",graphi+1);
		        else if(s==ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else
                    printf("�ļ�����ɹ���\n");
		        getchar();getchar();
		        break;
            case 15:
                printf("��������Ҫ����������ͼ��ţ���Χ[1��%d]��\n",GRAPHNUM);
		        scanf("%d",&graphi);
		        while(graphi<1||graphi>GRAPHNUM)
                {
                    printf("��������ȷ�ķ�Χ[1��%d]��\n",GRAPHNUM);
                    scanf("%d",&graphi);
                }
                printf("���ѳɹ�ѡ���%d������ͼ��\n",graphi);
                graphi=graphi-1;
		        getchar();getchar();

		        break;

        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()

/*
    �������ƣ�CreateCraph
    �������ܣ�����ͼ
    ������������������ͼ�����㼯������
    ��������ֵ��״̬����status
*/

status CreateCraph(ALGraph *G,invnode *V,int VR[][2])
{
    int i;
    ArcNode *tem[G->vexnum+1];
    for(i=1;i<=G->vexnum;i++)
    {
        G->vertices[i].key=V[i].key;
        G->vertices[i].data=V[i].data;
        G->vertices[i].firstarc=NULL;
        tem[i]=NULL;
    }
    for(i=1;i<=G->arcnum;i++)
    {
        ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex=VR[i][1];
        p->next=NULL;
        if(!p)
            return OVERFLOW;
        if(G->vertices[VR[i][0]].firstarc==NULL)
            G->vertices[VR[i][0]].firstarc=p;
        else
            tem[VR[i][0]]->next=p;
        tem[VR[i][0]]=p;
    }
    return OK;
}

/*
    �������ƣ�DestroyGraph
    �������ܣ�����ͼ
    ���������������ٵ�ͼ
    ��������ֵ��״̬����status
*/

status DestroyGraph(ALGraph *G)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    int i;
    ArcNode *tem,*tnext;
    for(i=1;i<=G->vexnum;i++)
    {
        tem=G->vertices[i].firstarc;
        G->vertices[i].firstarc=NULL;
        if(!tem)
        {
            G->vertices[i].data='\0';
            G->vertices[i].key=0;
            continue;
        }
        tnext=tem->next;
        while(tem!=NULL)
        {
            free(tem);
            tem=tnext;
            if(tem)
                tnext=tem->next;
            else
                tnext=NULL;
        }
        G->vertices[i].data='\0';
        G->vertices[i].key=0;
    }
    G->arcnum=0;
    G->vexnum=0;
    return OK;
}

/*
    �������ƣ�LocateVex
    �������ܣ����Ҷ���
    ��������������ͼG���ؼ���u
    ��������ֵ���ؼ���Ϊu�Ķ���λ��
*/

int LocateVex(ALGraph G,int u)
{
    if(!(G.arcnum)&&!(G.vexnum))
        return -1;
    int i;
    for(i=1;i<=G.vexnum;i++)
        if(G.vertices[i].key==u)
            return i;
    return 0;
}

/*
    �������ƣ�PutVex
    �������ܣ����㸳ֵ
    ��������������ͼG���ؼ���u��ֵvalue
    ��������ֵ��״̬����status
*/

status PutVex (ALGraph *G,int u,ElemType value)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    int p=LocateVex(*G,u);
    if(!p)
        return ERROR;
    G->vertices[p].data=value;
    return OK;
}

/*
    �������ƣ�FirstAdjVex
    �������ܣ���õ�һ�ڽӵ�
    ��������������ͼG������λ��u
    ��������ֵ��u��Ӧ����ĵ�һ���ڽӶ���λ��
*/

int FirstAdjVex(ALGraph G,int u)
{
    if(!(G.arcnum)&&!(G.vexnum))
        return -1;
    if(u<=0||u>G.vexnum)
        return -2;
    if(G.vertices[u].firstarc)
        return G.vertices[u].firstarc->adjvex;
    return 0;
}

/*
    �������ƣ�NextAdjVex
    �������ܣ������һ�ڽӵ�
    ��������������ͼG��������v��wλ��
    ��������ֵ��v�ģ������w����һ���ڽӶ����λ��
*/

int NextAdjVex(ALGraph G,int v,int w)
{
    if(!(G.arcnum)&&!(G.vexnum))
        return -1;
    if(v<=0||v>G.vexnum)
        return -2;
    if(!G.vertices[v].firstarc)
        return -3;
    ArcNode *tem=G.vertices[v].firstarc;
    while(tem)
    {
        if(tem->adjvex==w)
            break;
        tem=tem->next;
    }
    if(!tem)
        return -4;
    if(tem->adjvex==w&&tem->next==NULL)
        return -5;
    return tem->next->adjvex;
}

/*
    �������ƣ�InsertVex
    �������ܣ����붥��
    ��������������ͼG���¶���v
    ��������ֵ��״̬����status
*/

status InsertVex(ALGraph *G,VNode v)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    if(LocateVex(*G,v.key))
        return ERROR;
    G->vexnum++;
    G->vertices[G->vexnum]=v;
    return OK;
}

/*
    �������ƣ�DeleteVex
    �������ܣ�ɾ������
    ��������������ͼG����ɾ������ؼ���v
    ��������ֵ��״̬����status
*/

status DeleteVex(ALGraph *G,int v)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    if(!LocateVex(*G,v))
        return ERROR;
    int i,j,pos=LocateVex(*G,v);
    ArcNode *tem,*tnext,*tpre;
    for(i=1;i<=G->vexnum;i++)
    {
        if(G->vertices[i].key==v)//��ͷ������ɾ���ý��
        {
            tem=G->vertices[i].firstarc;
            G->vertices[i].firstarc=NULL;
            if(tem)
            {
                tnext=tem->next;
                while(tem!=NULL)
                {
                    free(tem);
                    (G->arcnum)--;
                    tem=tnext;
                    if(tem)
                        tnext=tem->next;
                    else
                        tnext=NULL;
                }
            }
            for(j=i;j<G->vexnum;j++)//��ɾ������Ľ��ȫ����ǰ��һλ
                G->vertices[j]=G->vertices[j+1];
            G->vertices[G->vexnum].data='\0';
            G->vertices[G->vexnum].firstarc=NULL;
            G->vertices[G->vexnum].key=0;
            (G->vexnum)--;
            i--;
            continue;
        }
        tem=G->vertices[i].firstarc;
        if(!tem)
            continue;
        if(tem->adjvex==pos)//firstarc���⴦��
        {
            G->vertices[i].firstarc=tem->next;
            free(tem);
            (G->arcnum)--;
            tem=G->vertices[i].firstarc;
            while(tem)
            {
                if(tem->adjvex>pos)
                    --(tem->adjvex);//ɾ������Ľ��λ���һ
                tem=tem->next;
            }
        }
        else
        {
            if(tem->adjvex>pos)
                --(tem->adjvex);
            tpre=tem;
            tem=tem->next;
            while(tem)
            {
                if(tem->adjvex==pos)
                {
                    tpre->next=tem->next;
                    free(tem);
                    (G->arcnum)--;
                }
                else if(tem->adjvex>pos)
                    --(tem->adjvex);//ɾ������Ľ��λ���һ
                tpre=tem;
                tem=tem->next;
            }
        }
    }
    return OK;
}

/*
    �������ƣ�InsertArc
    �������ܣ����뻡
    ��������������ͼG�������λ��v���յ�λ��w
    ��������ֵ��״̬����status
*/

status InsertArc(ALGraph *G,int v,int w)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    if(v<=0||v>G->vexnum||w<=0||w>G->vexnum)
        return ERROR;
    if(v==w)
        return EQU;
    ArcNode *tem=G->vertices[v].firstarc;
    while(tem)
    {
        if(tem->adjvex==w)
            return FALSE;
        tem=tem->next;
    }
    ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
    if(!p)
        return OVERFLOW;
    p->adjvex=w;
    p->next=NULL;
    (G->arcnum)++;
    tem=G->vertices[v].firstarc;
    if(!tem)
    {
        G->vertices[v].firstarc=p;
        return OK;
    }
    while(tem->next)
        tem=tem->next;
    tem->next=p;
    return OK;
}

/*
    �������ƣ�DeleteArc
    �������ܣ�ɾ����
    ��������������ͼG����ɾ���Ļ������λ��v���յ�λ��w
    ��������ֵ��״̬����status
*/

status DeleteArc(ALGraph *G,int v,int w)
{
    if(!(G->arcnum)&&!(G->vexnum))
        return INFEASTABLE;
    if(v<=0||v>G->vexnum||w<=0||w>G->vexnum)
        return ERROR;
    ArcNode *tem=G->vertices[v].firstarc,*tpre;
    if(!tem)
        return FALSE;
    if(tem->adjvex==w)
    {
        G->vertices[v].firstarc=tem->next;
        free(tem);
        (G->arcnum)--;
        return OK;
    }
    tpre=tem;
    tem=tem->next;
    while(tem)
    {
        if(tem->adjvex==w)
        {
            tpre->next=tem->next;
            free(tem);
            (G->arcnum)--;
            return OK;
        }
        tpre=tem;
        tem=tem->next;
    }
    return FALSE;
}

/*
    �������ƣ�visit
    �������ܣ����ʶ���
    ��������������v
    ��������ֵ��״̬����status
*/

status visit(VNode v)
{
    printf("%c",v.data);
    return OK;
}

/*
    �������ƣ�DFSTraverse
    �������ܣ����������������
    ��������������ͼG
    ��������ֵ��״̬����status
*/

status DFSTraverse(ALGraph G,status (*visit)(VNode))
{
    if(!(G.arcnum)&&!(G.vexnum))
        return INFEASTABLE;
    int i;
    for(i=1;i<=G.vexnum;i++)
        visited[i]=0;
    for(i=1;i<=G.vexnum;i++)
        if(!visited[i])
            DFS(G,i);

    return OK;
}

void DFS(ALGraph G,int v)
{
    visited[v]=1;
    VNode V=G.vertices[v];
    visit(V);
    int i;
    for(i=FirstAdjVex(G,v);i>0;i=NextAdjVex(G,v,i))
        if(!visited[i])
            DFS(G,i);
}

/*
    �������ƣ�BFSTraverse
    �������ܣ����������������
    ��������������ͼG
    ��������ֵ��״̬����status
*/

status BFSTraverse(ALGraph G,status (*visit)(VNode))
{
    if(!(G.arcnum)&&!(G.vexnum))
        return INFEASTABLE;
    int i,j,t;
    VNode V,u,w;
    for(i=1;i<=G.vexnum;i++)
        visited[i]=0;
    linkqueue q;
    Initqueue(&q);
    for(i=1;i<=G.vexnum;i++)
        if(!visited[i])
        {
            visited[i]=1;
            V=G.vertices[i];
            visit(V);
            Enqueue(&q,V);
            while(!queueempty(q))
            {
                Dequeue(&q,&u);
                t=LocateVex(G,u.key);
                for(j=FirstAdjVex(G,t);j>0;j=NextAdjVex(G,t,j))
                    if(!visited[j])
                    {
                        visited[j]=1;
                        w=G.vertices[j];
                        visit(w);
                        Enqueue(&q,w);
                    }
            }
        }
    return OK;
}

/*
    �������ƣ�ReadFile
    �������ܣ��ļ�����
    ��������������ͼG���ļ���
    ��������ֵ��״̬����status
*/

status ReadFile(ALGraph *G,char *name)
{
    FILE *fp;
    if((fp=fopen(name,"r"))==NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    int vn,i,an,vr[200][2];
    fscanf(fp,"%d",&vn);
    G->vexnum=vn;
    invnode v[vn+1];
    for(i=1;i<=vn;i++)
        fscanf(fp,"%d %s",&v[i].key,&v[i].data);
    fscanf(fp,"%d",&an);
    G->arcnum=an;
    for(i=1;i<=an;i++)
        fscanf(fp,"%d %d",&vr[i][0],&vr[i][1]);
    CreateCraph(G,v,vr);
    fclose(fp);
    return OK;
}

/*
    �������ƣ�WriteFile
    �������ܣ��ļ��洢
    ��������������ͼG���ļ���
    ��������ֵ��״̬����status
*/

status WriteFile(ALGraph G,char *name)
{
    FILE *fp;
    int i;
    ArcNode *p;
    if ((fp=fopen(name,"w"))==NULL)
	{
	    printf("File open error\n ");
	    return ERROR;
	}
	fprintf(fp,"%d\n",G.vexnum);
	for(i=1;i<=G.vexnum;i++)
        fprintf(fp,"%d %c\n",G.vertices[i].key,G.vertices[i].data);
    fprintf(fp,"%d\n",G.arcnum);
    for(i=1;i<=G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            fprintf(fp,"%d %d\n",i,p->adjvex);
            p=p->next;
        }
    }
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
