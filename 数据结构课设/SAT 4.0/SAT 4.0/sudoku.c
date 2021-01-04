#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

/*
	函数名称:PrintResult
	函数功能：输出数独求解结果
	函数参数：dpll求解结果及相关数独
	函数返回值：算法执行状态参数
*/

status PrintResult(int dim)
{
	int i, j;
	qsort(re, dealnum, sizeof(int), cmp);
	for (i = 1; i <= dim; i++)
	{
		for (j = 1; j <= dim; j++)
		{
			if (re[(i - 1)*dim + j - 1] > 0)
				printf("| 1 ");
			else
				printf("| 0 ");
		}
		printf("|\n");
		if (i != dim)
		{
			for (j = 1; j <= dim; j++)
				printf("|---");
			printf("|\n");
		}
	}
	return OK;
}

/*
	函数名称:SolveSudoku
	函数功能：将数独的cnf解析并存入sat链表中，调用dpll求解
	函数参数：sat链表，数独解析结果
	函数返回值：算法执行状态参量
*/

status SolveSudoku(sen *s, int dim)
{
	int i, j, va, res;
	senp *p, *pt;
	sen *stem=NULL, *sp = s;
	word *w, *wp = NULL;
	sennum = cnf[0][0];
	varnum = cnf[0][1];
	memset(vari, 0, sizeof(vari));
	for (i = 1; i <= cnf[0][0]; i++)
	{
		wp = NULL;
		stem = (sen *)malloc((sizeof(sen)));
		stem->num = stem->zeronum = stem->onenum = 0;
		sp->nextsen = stem;
		sp = stem;
		stem->nextsen = NULL;
		for (j = 1; j <= cnf[i][0]; j++)//逐个读取当前子句文字，连成链表
		{
			if (cnf[i][j] < 0)
				va = -cnf[i][j];
			else
				va = cnf[i][j];
			w = (word *)malloc(sizeof(word));
			w->no = cnf[i][j];
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
			p->no = cnf[i][j];
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
		}
	}
	stailini = stail = stem;
	for (i = 1; i <= cnf[0][1]; i++)
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
	res = dpll(*s);//调用dpll求解数独
	if (res == 1)
		return OK;
	else
		return ERROR;
}

/*
	函数名称:WritecnfFile
	函数功能：将数独解析后的cnf结果输出到对应文件中
	函数参数：待解析的数独，存储文件名
	函数返回值：算法执行状态参量
*/

status WritecnfFile(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim, char* name)
{
	FILE *fp;
	int i, j;
	if ((fp = fopen(name, "w")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
	fprintf(fp, "c sudoku,order: %d\nc\n", dim);//输出数独阶数
	for (i = 1; i <= dim; i++)//输出数独
	{
		fprintf(fp, "c");
		for (j = 1; j <= dim; j++)
			fprintf(fp, "%c", sud[i][j]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "c\n");
	fprintf(fp, "p cnf %d %d\n", cnf[0][1], cnf[0][0]);//输出解析后变元数和子句数
	for (i = 1; i <= cnf[0][0]; i++)//输出解析后cnf各个子句
	{
		for (j = 1; j <= cnf[i][0]; j++)
			fprintf(fp, "%d ", cnf[i][j]);
		fprintf(fp, "0\n");
	}
	fclose(fp);
	return OK;
}

/*
	函数名称:Transtocnf
	函数功能：将数独结果解析为cnf
	函数参数：待解析数独
	函数返回值：算法执行状态参量
*/

status Transtocnf(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim)
{
	int i, j, k, l, clanum = 0;
	for (i = 1; i <= dim; i++)//处理已填单元
	{
		for (j = 1; j <= dim; j++)
		{
			if (sud[i][j] == '1')
			{
				clanum++;
				cnf[clanum][0] = 1;
				cnf[clanum][1] = (i - 1)*dim + j;
			}
			else if (sud[i][j] == '0')
			{
				clanum++;
				cnf[clanum][0] = 1;
				cnf[clanum][1] = -((i - 1)*dim + j);
			}
		}
	}
	for (i = 1; i <= dim; i++)//生成规则一：在每一行、每一列中不允许有连续的3个1或3个0出现
	{
		for (k = 1; k <= dim - 2; k++)
		{
			cnf[clanum + 1][0] = cnf[clanum + 2][0] = cnf[clanum + 3][0] = cnf[clanum + 4][0] = 3;
			for (j = k; j <= k + 2; j++)
			{
				cnf[clanum + 1][j - k + 1] = (i - 1)*dim + j;
				cnf[clanum + 2][j - k + 1] = -((i - 1)*dim + j);
				cnf[clanum + 3][j - k + 1] = (j - 1)*dim + i;
				cnf[clanum + 4][j - k + 1] = -((j - 1)*dim + i);
			}
			clanum += 4;
		}
	}
	for (l = 1; l <= dim; l++)//生成规则二：在每一行、每一列中1与0的个数相同
	{
		int a[MAXDIMNUM+1];
		for (i = 0; i < dim / 2 + 1; i++)
			a[i] = i + 1;
		while (a[0] <= (dim - dim / 2))//数组a为在dim中选dim/2+1个元素的不重复组合
		{
			for (; a[dim / 2] <= dim; a[dim / 2]++)
			{
				cnf[clanum + 1][0] = cnf[clanum + 2][0] = cnf[clanum + 3][0] = cnf[clanum + 4][0] = dim / 2 + 1;
				for (k = 0; k < dim / 2 + 1; k++)
				{
					cnf[clanum + 1][k + 1] = (a[k] - 1)*dim + l;
					cnf[clanum + 2][k + 1] = -((a[k] - 1)*dim + l);
					cnf[clanum + 3][k + 1] = (l - 1)*dim + a[k];
					cnf[clanum + 4][k + 1] = -((l - 1)*dim + a[k]);
				}
				clanum += 4;
			}
			for (j = dim / 2 + 1 - 2; j >= 0; j--)
			{
				a[j]++;
				if (a[j] <= (j + dim - dim / 2))
					break;
			}
			for (j++; j > 0 && j < dim / 2 + 1; j++)
				a[j] = a[j - 1] + 1;
		}
	}
	//nv1，nv2，nv3分别存储Tseytin变换引入新变元编号，事实证明nv1没用，但是有nv1让代码可读性增加就留下了
	int tot = dim * dim, j1, j2, nv1[3][MAXDIMNUM + 1][MAXDIMNUM + 1][MAXDIMNUM + 1][2], nv2[3][MAXDIMNUM + 1][MAXDIMNUM + 1][MAXDIMNUM + 1], nv3[3][MAXDIMNUM + 1][MAXDIMNUM + 1];
	for (j1 = 1; j1 < dim; j1++)//生成规则三：不存在重复的行与重复的列。
	{
		for (j2 = j1 + 1; j2 <= dim; j2++)
		{
			for (i = 1; i <= dim; i++)
			{
				//处理形如：15711=51^71
				nv1[1][j1][j2][i][1] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = (j1 - 1)*dim + i;
				cnf[clanum + 1][2] = -tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = (j2 - 1)*dim + i;
				cnf[clanum + 2][2] = -tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = -((j1 - 1)*dim + i);
				cnf[clanum + 3][2] = -((j2 - 1)*dim + i);
				cnf[clanum + 3][3] = tot;
				clanum += 3;
				//处理形如：15720=-52^-72
				nv1[1][j1][j2][i][0] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = -((j1 - 1)*dim + i);
				cnf[clanum + 1][2] = -tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = -((j2 - 1)*dim + i);
				cnf[clanum + 2][2] = -tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = (j1 - 1)*dim + i;
				cnf[clanum + 3][2] = (j2 - 1)*dim + i;
				cnf[clanum + 3][3] = tot;
				clanum += 3;
				//处理形如：1578=15781∨15780
				nv2[1][j1][j2][i] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = -(tot - 2);
				cnf[clanum + 1][2] = tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = -(tot - 1);
				cnf[clanum + 2][2] = tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = tot - 2;
				cnf[clanum + 3][2] = tot - 1;
				cnf[clanum + 3][3] = -tot;
				clanum += 3;
				//处理形如：25711=15^17
				nv1[2][j1][j2][i][1] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = (i - 1)*dim + j1;
				cnf[clanum + 1][2] = -tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = (i - 1)*dim + j2;
				cnf[clanum + 2][2] = -tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = -((i - 1)*dim + j1);
				cnf[clanum + 3][2] = -((i - 1)*dim + j2);
				cnf[clanum + 3][3] = tot;
				clanum += 3;
				//处理形如：25720=-25^-27
				nv1[2][j1][j2][i][0] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = -((i - 1)*dim + j1);
				cnf[clanum + 1][2] = -tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = -((i - 1)*dim + j2);
				cnf[clanum + 2][2] = -tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = (i - 1)*dim + j1;
				cnf[clanum + 3][2] = (i - 1)*dim + j2;
				cnf[clanum + 3][3] = tot;
				clanum += 3;
				//处理形如：1578=15781∨15780
				nv2[2][j1][j2][i] = (++tot);
				cnf[clanum + 1][0] = 2;
				cnf[clanum + 1][1] = -(tot - 2);
				cnf[clanum + 1][2] = tot;
				cnf[clanum + 2][0] = 2;
				cnf[clanum + 2][1] = -(tot - 1);
				cnf[clanum + 2][2] = tot;
				cnf[clanum + 3][0] = 3;
				cnf[clanum + 3][1] = tot - 2;
				cnf[clanum + 3][2] = tot - 1;
				cnf[clanum + 3][3] = -tot;
				clanum += 3;
			}
			//处理形如：157= ¬[1571∧1572∧…∧1578]
			nv3[1][j1][j2] = (++tot);
			clanum++;
			cnf[clanum][0] = dim + 1;
			cnf[clanum][1] = -tot;
			for (i = 1; i <= dim; i++)
			{
				cnf[clanum - i + 1][i + 1] = -nv2[1][j1][j2][i];
				clanum++;
				cnf[clanum][0] = 2;
				cnf[clanum][1] = nv2[1][j1][j2][i];
				cnf[clanum][2] = tot;
			}
			//处理形如：257= ¬[2571∧2572∧…∧2578]
			nv3[2][j1][j2] = (++tot);
			clanum++;
			cnf[clanum][0] = dim + 1;
			cnf[clanum][1] = -tot;
			for (i = 1; i <= dim; i++)
			{
				cnf[clanum - i + 1][i + 1] = -nv2[2][j1][j2][i];
				clanum++;
				cnf[clanum][0] = 2;
				cnf[clanum][1] = nv2[2][j1][j2][i];
				cnf[clanum][2] = tot;
			}
			clanum++;
			cnf[clanum][0] = 1;
			cnf[clanum][1] = nv3[1][j1][j2];
			clanum++;
			cnf[clanum][0] = 1;
			cnf[clanum][1] = nv3[2][j1][j2];
		}
	}
	cnf[0][0] = clanum;
	cnf[0][1] = tot;
	return OK;
}

/*
	函数名称:Clearallsen
	函数功能：及时释放malloc申请的内存
	函数参数：sat链表表头结点地址
	函数返回值：void
*/

void Clearallsen(sen *s)
{
	if (s->nextsen == NULL)
		return;
	sen *p = s->nextsen, *q;
	word *wp, *wq;
	senp *sp, *sq;
	int i;
	while (p)
	{
		wp = p->firstword;
		while (wp)
		{
			wq = wp;
			wp = wp->next;
			free(wq);
		}
		q = p;
		p = p->nextsen;
		free(q);
	}
	for (i = 1; i <= varnum; i++)
	{
		sp = vari[i].firstsen;
		while (sp)
		{
			sq = sp;
			sp = sp->next;
			free(sq);
		}
	}
	memset(vari, 0, sizeof(vari));
	memset(re, 0, sizeof(re));
	memset(cnf, 0, sizeof(cnf));
	dealnum = decnum = learnnum = 0;
	s->nextsen = NULL;
	//清，就硬清，之前用过的都逐个遍历清除
	return;
}

/*
	函数名称:InitialSudoku
	函数功能：基于 las - vegas算法先随机初始化几个位置的值
	函数参数：待初始化数独
	函数返回值：算法执行状态参数
*/

status InitialSudoku(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim)
{
	int i, j, tot = 0, t, k, num;
	for (i = 1; i <= dim; i++)
		for (j = 1; j <= dim; j++)
			sud[i][j] = '.';
	while (tot < INITIALNUM)
	{
		i = rand() % dim + 1;
		j = rand() % dim + 1;
		t = rand() % 2;
		if (sud[i][j] != '.')//已经填的不改了
			continue;
		//以下if提前防止随机的位置违反规则一
		if (i >= 3 && sud[i - 2][j] == sud[i - 1][j] && sud[i - 1][j] == t + '0')
			continue;
		if (i <= 7 && sud[i + 1][j] == sud[i + 2][j] && sud[i + 1][j] == t + '0')
			continue;
		if (i >= 2 && i <= 8 && sud[i - 1][j] == sud[i + 1][j] && sud[i + 1][j] == t + '0')
			continue;
		if (j >= 3 && sud[i][j - 2] == sud[i][j - 1] && sud[i][j - 1] == t + '0')
			continue;
		if (j <= 7 && sud[i][j + 1] == sud[i][j + 2] && sud[i][j + 1] == t + '0')
			continue;
		if (j >= 2 && j <= 8 && sud[i][j - 1] == sud[i][j + 1] && sud[i][j + 1] == t + '0')
			continue;
		//以下提前防止随机的位置违反规则二
		num = 0;
		for (k = 1; k <= dim; k++)
			if (sud[i][k] == t + '0')
				num++;
		if (num >= dim / 2)
			continue;
		num = 0;
		for (k = 1; k <= dim; k++)
			if (sud[k][j] == t + '0')
				num++;
		if (num >= dim / 2)
			continue;
		sud[i][j] = t + '0';
		tot++;
	}
	//当前数独求解为完整数独方便挖洞
	Transtocnf(sud, dim);
	return SolveSudoku(&s, dim);
}

/*
	函数名称:Gensudoku
	函数功能：基于挖洞法生成有唯一解的数独
	函数参数：待处理数独
	函数返回值：算法执行状态参量
*/

status Gensudoku(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim)
{
	int i, j;
	status st = InitialSudoku(sud, dim);
	while (st == ERROR)//基于 las - vegas算法生成终盘
	{
		Clearallsen(&s);
		st = InitialSudoku(sud, dim);
	}
	qsort(re, dealnum, sizeof(int), cmp);
	for (i = 1; i <= dim; i++)
	{
		for (j = 1; j <= dim; j++)
		{
			if (re[(i - 1)*dim + j - 1] > 0)
				sud[i][j] = '1';
			else
				sud[i][j] = '0';
		}
	}
	/*printf("*****\n");
	for (i=1;i<=dim;i++)
	{
		for(j=1;j<=dim;j++)
			printf("| %c ",sud[i][j]);
		printf("|\n");
		if (i!=dim)
		{
			for(j=1;j<=dim;j++)
				printf("|---");
			printf("|\n");
		}
	}*/
	Clearallsen(&s);
	for (i = 1; i <= dim; i++)//从上到下从左到右挖洞
	{
		for (j = 1; j <= dim; j++)
		{
			sud[i][j] = (!(sud[i][j] - '0')) + '0';//填入相反值，若有解则不唯一就不挖，否则说明有唯一解，挖
			Transtocnf(sud, dim);
			if (SolveSudoku(&s, dim))
			{
				Clearallsen(&s);
				sud[i][j] = (!(sud[i][j] - '0')) + '0';//不能挖就恢复
				continue;
			}
			Clearallsen(&s);
			sud[i][j] = '.';//挖
		}
	}
	Clearallsen(&s);
	return OK;
}
