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
typedef char ElemType; //数据元素类型定义

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;

typedef struct VNode{  //头结点的定义
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
}qnode;//队列元素

typedef struct
{
    qnode *front;
    qnode *rear;
}linkqueue;//队列

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
	    printf("请先进行操作15来选择您要处理的线性表，否则默认为第一个线性表\n");
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
	    printf("    请选择你的操作[0~15]:");
	    scanf("%d",&op);
	    while(op<0||op>15)
        {
            printf("请输入正确的操作数范围[0~15]\n");
            scanf("%d",&op);
        }
        switch(op){
	        case 1:
		        //printf("\n----CreateCraph功能待实现！\n");
		        printf("请输入要创建的图的顶点个数：\n");
		        scanf("%d",&vnum);
		        g[graphi].vexnum=vnum;
		        printf("请输入要创建的图的顶点的关键字和数据域：\n");
		        for(i=1;i<=vnum;i++)
                    scanf("%d %s",&vv[i].key,&vv[i].data);
                printf("请输入要创建的图的弧数：\n");
                scanf("%d",&anum);
                g[graphi].arcnum=anum;
                printf("请输入要创建的图的弧，以位序对形式，形如1 2：\n");
                for(i=1;i<=anum;i++)
                    scanf("%d %d",&vr[i][0],&vr[i][1]);
		        s=CreateCraph(&g[graphi],vv,vr);
		        if(s==OK) printf("有向图%d创建成功！\n",graphi+1);
                else
                    printf("有向图%d创建失败！\n",graphi+1);
		        getchar();getchar();
		        break;
	        case 2:
		        //printf("\n----DestroyGraph功能待实现！\n");
		        if(DestroyGraph(&g[graphi])==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else
                    printf("有向图%d成功销毁",graphi+1);
		        getchar();getchar();
		        break;
	        case 3:
		        //printf("\n----LocateVex功能待实现！\n");
		        printf("请输入要查找的顶点关键字：\n");
		        scanf("%d",&u);
		        v=LocateVex(g[graphi],u);
		        if(v==-1)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(v==0)
                    printf("该关键字在有向图%d中不存在！\n",graphi+1);
                else
                    printf("您查找的关键字在有向图%d位序为%d",graphi+1,v);
                getchar();getchar();
		        break;
	        case 4:
		        //printf("\n----PutVex功能待实现！\n");
		        printf("请输入要赋值的顶点关键字：\n");
		        scanf("%d",&u);
		        getchar();
		        printf("请输入要修改的值：\n");
		        scanf("%c",&e);
		        s=PutVex(&g[graphi],u,e);
		        if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(s==ERROR)
                    printf("有向图%d中不存在关键字为%d的顶点！\n",graphi+1,u);
                else
                    printf("赋值成功！\n");
		        getchar();getchar();
		        break;
            case 5:
                //printf("\n----FirstAdjVex功能待实现！\n");
                printf("请输入要查询的顶点位序:\n");
                scanf("%d",&u);
                v=FirstAdjVex(g[graphi],u);
                if(v==-1)
                    printf("线性表%d未创建！\n",graphi+1);
                else if(v==-2)
                    printf("有向图%d中不存在位序为%d的顶点\n",graphi+1,u);
		        else if(v==0)
                    printf("你查找的顶点没有邻接点\n");
                else
                    printf("您查找的结点的第一个邻接点位序为%d\n",v);
		        getchar();getchar();
		        break;
            case 6:
		        //printf("\n----NextAdjVex功能待实现！\n");
		        printf("请输入你想查询的起点位序：\n");
		        scanf("%d",&v);
		        printf("请输入你想查询到的相对结点的位序：\n");
		        scanf("%d",&w);
		        u=NextAdjVex(g[graphi],v,w);
		        if(u==-1)
                    printf("有向图%d未创建\n",graphi+1);
		        else if(u==-2)
                    printf("有向图%d中不存在位序为%d的顶点！\n",graphi+1,v);
                else if(u==-3)
                    printf("位序为%d的顶点没有邻接点\n",v);
                else if(u==-4)
                    printf("顶点%d没有位序为%d的邻接点",v,w);
                else if(u==-5)
                    printf("顶点%d为顶点%d的最后一个邻接点",w,v);
                else
                    printf("顶点%d相对于顶点%d的下一个邻接顶点的位序为%d",v,w,u);
		        getchar();getchar();
		        break;
	        case 7:
		        //printf("\n----InsertVex功能待实现！\n");
		        printf("请输入你想插入的新顶点的关键字！\n");
		        scanf("%d",&u);
		        getchar();
		        printf("请输入你想插入的新顶点的数据域：\n");
		        scanf("%c",&e);
		        VNode *t=(VNode *)malloc(sizeof(VNode));
		        t->data=e;
		        t->key=u;
		        t->firstarc=NULL;
		        s=InsertVex(&g[graphi],*t);
                if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(s==ERROR)
                    printf("插入顶点的关键字在有向图%d中已经存在！\n",graphi+1);
                else
                    printf("插入成功\n");
		        getchar();getchar();
		        break;
	        case 8:
		        //printf("\n----DeleteVex功能待实现！\n");
		        printf("请输入你想删除结点的关键字！\n");
		        scanf("%d",&u);
		        s=DeleteVex(&g[graphi],u);
		        if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(s==ERROR)
                    printf("有向图%d中不存在关键字为%d的顶点！\n",graphi+1,u);
                else
                    printf("删除成功！\n");
                getchar();getchar();
		        break;
            case 9:
		        //printf("\n----InsertArc功能待实现！\n");
		        printf("请输入你想插入弧的起点和终点的位序！\n");
		        scanf("%d %d",&v,&w);
		        s=InsertArc(&g[graphi],v,w);
		        if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(s==ERROR)
                    printf("在有向图%d中不存在位序为%d或%d的顶点！\n",graphi+1,v,w);
                else if(s==FALSE)
                    printf("该弧已经存在！\n");
                else if(s==EQU)
                    printf("不能插入指向自身的弧！\n");
                else
                    printf("插入成功！\n");
		        getchar();getchar();
		        break;
	        case 10:
		        //printf("\n----DeleteArc功能待实现！\n");
		        printf("请输入你想删除弧的起点和终点的位序！\n");
		        scanf("%d %d",&v,&w);
		        s=DeleteArc(&g[graphi],v,w);
		        if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else if(s==ERROR)
                    printf("在有向图%d中不存在位序为%d或%d的顶点！\n",graphi+1,v,w);
                else if(s==FALSE)
                    printf("顶点%d与顶点%d之间没有弧!\n",v,w);
                else
                    printf("删除成功！\n");
		        getchar();getchar();
		        break;
	        case 11:
		        //printf("\n----DFSTraverse功能待实现！\n");
                s=DFSTraverse(g[graphi],p);
                if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else
                    printf("深度优先搜索遍历结束\n");
		        getchar();getchar();
		        break;
	        case 12:
                //printf("\n----BFSTraverse功能待实现！\n");
                s=BFSTraverse(g[graphi],p);
                if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
                else
                    printf("广度优先搜索遍历结束\n");
		        getchar();getchar();
		        break;
	        case 0:
                 break;
            case 13:
                //printf("\n----ReadFile功能待实现！\n");
                printf("请输入要读入的文件名！\n");
                getchar();
                scanf("%s",c);
                s=ReadFile(&g[graphi],c);
                if(s==ERROR)
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
                s=WriteFile(g[graphi],c);
                if(s==INFEASTABLE)
                    printf("有向图%d未创建！\n",graphi+1);
		        else if(s==ERROR)
                    printf("文件打开失败！\n");
                else
                    printf("文件输出成功！\n");
		        getchar();getchar();
		        break;
            case 15:
                printf("请输入需要操作的有向图序号，范围[1，%d]！\n",GRAPHNUM);
		        scanf("%d",&graphi);
		        while(graphi<1||graphi>GRAPHNUM)
                {
                    printf("请输入正确的范围[1，%d]！\n",GRAPHNUM);
                    scanf("%d",&graphi);
                }
                printf("您已成功选择第%d个有向图！\n",graphi);
                graphi=graphi-1;
		        getchar();getchar();

		        break;

        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

/*
    函数名称：CreateCraph
    函数功能：创建图
    函数参数：待创建的图，顶点集，弧集
    函数返回值：状态参量status
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
    函数名称：DestroyGraph
    函数功能：销毁图
    函数参数：待销毁的图
    函数返回值：状态参量status
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
    函数名称：LocateVex
    函数功能：查找顶点
    函数参数：有向图G，关键字u
    函数返回值：关键字为u的顶点位序
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
    函数名称：PutVex
    函数功能：顶点赋值
    函数参数：有向图G，关键字u，值value
    函数返回值：状态参量status
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
    函数名称：FirstAdjVex
    函数功能：获得第一邻接点
    函数参数：有向图G，顶点位序u
    函数返回值：u对应顶点的第一个邻接顶点位序
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
    函数名称：NextAdjVex
    函数功能：获得下一邻接点
    函数参数：有向图G，两顶点v，w位序
    函数返回值：v的（相对于w）下一个邻接顶点的位序
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
    函数名称：InsertVex
    函数功能：插入顶点
    函数参数：有向图G，新顶点v
    函数返回值：状态参量status
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
    函数名称：DeleteVex
    函数功能：删除顶点
    函数参数：有向图G，待删除顶点关键字v
    函数返回值：状态参量status
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
        if(G->vertices[i].key==v)//在头结点表中删除该结点
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
            for(j=i;j<G->vexnum;j++)//将删除结点后的结点全部向前移一位
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
        if(tem->adjvex==pos)//firstarc特殊处理
        {
            G->vertices[i].firstarc=tem->next;
            free(tem);
            (G->arcnum)--;
            tem=G->vertices[i].firstarc;
            while(tem)
            {
                if(tem->adjvex>pos)
                    --(tem->adjvex);//删除结点后的结点位序减一
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
                    --(tem->adjvex);//删除结点后的结点位序减一
                tpre=tem;
                tem=tem->next;
            }
        }
    }
    return OK;
}

/*
    函数名称：InsertArc
    函数功能：插入弧
    函数参数：有向图G，弧起点位序v，终点位序w
    函数返回值：状态参量status
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
    函数名称：DeleteArc
    函数功能：删除弧
    函数参数：有向图G，待删除的弧的起点位序v，终点位序w
    函数返回值：状态参量status
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
    函数名称：visit
    函数功能：访问顶点
    函数参数：顶点v
    函数返回值：状态参量status
*/

status visit(VNode v)
{
    printf("%c",v.data);
    return OK;
}

/*
    函数名称：DFSTraverse
    函数功能：深度优先搜索遍历
    函数参数：有向图G
    函数返回值：状态参量status
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
    函数名称：BFSTraverse
    函数功能：广度优先搜索遍历
    函数参数：有向图G
    函数返回值：状态参量status
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
    函数名称：ReadFile
    函数功能：文件读入
    函数参数：有向图G，文件名
    函数返回值：状态参量status
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
    函数名称：WriteFile
    函数功能：文件存储
    函数参数：有向图G，文件名
    函数返回值：状态参量status
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
