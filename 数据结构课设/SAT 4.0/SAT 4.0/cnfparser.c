#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

/*
	函数名称:ReadFile
	函数功能：将文件中的cnf算例解析并存储到s中
	函数参数：指向储存cnf文件名的指针name，sat链表表头结点地址
	函数返回值：算法执行状态参量
*/

status ReadFile(char *name, sen *s)
{
	char c, t[200];
	int wo, i, va;
	senp *p, *pt;
	sen *stem=NULL, *sp = s;
	word *w, *wp = NULL;
	FILE *fp;
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("File open error\n");
		return ERROR;
	}
	sennum = 0;
	fscanf(fp, "%c", &c);
	while (c == 'c')
	{
		fgets(t, 1000, fp);
		fscanf(fp, "%c", &c);
	}
	fscanf(fp, " cnf");
	fscanf(fp, "%d %d", &varnum, &sennum);
	for (i = 0; i < sennum; i++)
	{
		wp = NULL;
		stem = (sen *)malloc((sizeof(sen)));
		stem->num = stem->zeronum = stem->onenum = 0;
		sp->nextsen = stem;
		sp = stem;
		stem->nextsen = NULL;
		fscanf(fp, "%d", &wo);
		while (wo != 0)//逐个读取当前子句文字，连成链表
		{
			if (wo < 0)
				va = -wo;
			else
				va = wo;
			w = (word *)malloc(sizeof(word));
			w->no = wo;
			w->pon = 0;
			w->next = NULL;
			if (wp == NULL)
				stem->firstword = w;
			else
				wp->next = w;
			wp = w;
			stem->num++;
			//按照读入先后顺序将该子句连在当前文字的链表中
			p = (senp *)malloc(sizeof(senp));
			p->no = wo;
			p->s = stem;
			p->next = NULL;
			(vari[va].tim)++;
			if (vari[va].tim == 1)
				vari[va].firstsen = p;
			else
			{
				pt = vari[va].firstsen;
				while (pt->next != NULL)
					pt = pt->next;
				pt->next = p;
			}
			fscanf(fp, "%d", &wo);
		}
	}
	stailini = stail = stem;
	for (i = 1; i <= varnum; i++)
	{
		p = vari[i].firstsen;
		if (!p)
			vari[i].tail = NULL;
		else
		{
			while (p->next)
				p = p->next;
			vari[i].tail = vari[i].tailini = p;
		}
	}
	fclose(fp);
	return OK;
}

/*
	函数名称:WriteClause
	函数功能：将解析的cnf结果输出到相应文件中
	函数参数：输出文件名，sat链表s
	函数返回值：算法执行状态参量
*/

status WriteClause(char* name, sen s)
{
	FILE *fp;
	if ((fp = fopen(name, "w")) == NULL)
	{
		fprintf(fp, "File open error\n ");
		return ERROR;
	}
	fprintf(fp,"c\np cnf %d %d\n", varnum, sennum);
	sen *p = s.nextsen;
	word *w;
	while (p)
	{
		w = p->firstword;
		while (w)
		{
			fprintf(fp, "%d ", w->no);
			w = w->next;
		}
		fprintf(fp, "0\n");
		p = p->nextsen;
	}
	fclose(fp);
	return OK;
}
