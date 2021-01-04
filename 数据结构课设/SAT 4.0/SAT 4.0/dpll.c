#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

int cmp(const void *a, const void *b)
{
	return (abs(*(int *)a) - abs(*(int *)b));
}

/*
	函数名称:WriteFile
	函数功能：将dpll最后结果输出到相应文件中
	函数参数：输出文件名，dpll函数执行结果，算法执行时间
	函数返回值：算法执行状态参量
*/

status WriteFile(char* name, int ret, double total_t)
{
	FILE *fp;
	int i;
	if ((fp = fopen(name, "w")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
	if (ret == 1)
	{
		qsort(re, dealnum, sizeof(int), cmp);
		fprintf(fp, "s 1\nv ");
		for (i = 0; i < dealnum; i++)//只输出对cnf求解必要的变元取值，可正可负变量不输出
			fprintf(fp, "%d ", re[i]);
		fprintf(fp, "\n");
	}
	else
		fprintf(fp, "0\n");
	fprintf(fp, "t %f ms\n", total_t);
	fclose(fp);
	return OK;
}

/*
	函数名称:Findsingle
	函数功能：寻找当前sat链表中的单变元子句或单元子句
	函数参数：sat链表
	函数返回值：sat链表中的单子句或单元子句的位置或空指针
*/

sen *Findsingle(sen s)
{
	sen *p = s.nextsen;
	while (p)
	{
		if (p->onenum)//不是已满足子句
		{
			p = p->nextsen;
			continue;
		}
		if (p->num == p->zeronum)//不是不可能满足子句
		{
			p = p->nextsen;
			continue;
		}
		if (p->num - p->zeronum == 1)//为单元子句
			return p;
		p = p->nextsen;
	}
	return NULL;
}

/*
	函数名称:select
	函数功能：选择下一赋值变元（基于JW算法）
	函数参数：sat链表
	函数返回值：所选变元序号及正负
*/

int select(sen s)
{
	int i, ans = 0;
	double tem, res = 0, posnum=0, negnum=0;
	senp *p;
	for (i = 1; i <= varnum; i++)
	{
		if (vari[i].vis)
			continue;
		tem = 0;
		p = vari[i].firstsen;
		if (!p)
			continue;
		while (p)
		{
			if (p->s->onenum)
			{
				p = p->next;
				continue;
			}
			tem += pow(2.0, -(double)(p->s->num - p->s->zeronum));//基于JW算法，计算每个变元权值
			p = p->next;
		}
		if (tem > res)
		{
			ans = i;
			res = tem;
		}
	}
	//计算所筛选变元的较优符号
	p = vari[ans].firstsen;
	while (p)
	{
		if (p->no == ans)
			posnum += pow(2.0, -(double)(p->s->num - p->s->zeronum));
		else
			negnum += pow(2.0, -(double)(p->s->num - p->s->zeronum));
		p = p->next;
	}
	if (posnum > negnum)
		return ans;
	else
		return -ans;
}

/*
	函数名称:bcp
	函数功能：布尔约束传播过程
	函数参数：sat链表，新确定值的变元
	函数返回值：void
*/

void bcp(sen s, sen l)
{
	int num, wo, i = 0;
	word *w = l.firstword;
	while (w->pon)//在单元子句中寻找未赋值的文字
		w = w->next;
	num = w->no;
	if (num < 0)
		wo = -num;
	else
		wo = num;
	vari[wo].vis = 1;
	senp *p = vari[wo].firstsen;
	while (p)//在当前变元的子句链表中逐个运用单子句原则化简
	{
		w = p->s->firstword;
		while (w)
		{
			if (w->no == num && w->pon == 0)
			{
				p->s->onenum++;
				w->pon = 1;
				i++;
			}
			else if (w->no == -num && w->pon == 0)
			{
				p->s->zeronum++;
				w->pon = 1;
				i++;
			}
			w = w->next;
		}
		p = p->next;
	}
	//printf("%d %d\n",num,i);
	return;
}

/*
	函数名称:satf
	函数功能：判断当前是否已满足
	函数参数：sat链表
	函数返回值：若满足则返回1否则返回0
*/

int satf(sen s)
{
	sen *p = s.nextsen;
	while (p!=stail->nextsen)
	{
		if (p->onenum == 0)
			return 0;
		p = p->nextsen;
	}
	return 1;
}

/*
	函数名称:unsatf
	函数功能：判断当前是否存在冲突子句
	函数参数：sat链表
	函数返回值：冲突子句位置
*/

sen *unsat(sen s)
{
	sen *p = s.nextsen;
	while (p)
	{
		if (p->zeronum == p->num)
		{
			/*word *w=p->firstword;
			while(w)
			{
				printf("%d ",w->no);
				w=w->next;
			}
			printf("0\n");*/
			return p;
		}

		p = p->nextsen;
	}
	return NULL;
}

/*
	函数名称:Back
	函数功能：回溯时将最近一次赋值带来的影响消除，恢复到赋值之前状态
	函数参数：sat链表，本次赋值后进行过布尔约束传播化简的变元序号表
	函数返回值：void
*/

void Back(sen s, int *bcpw, int bcpnum)
{
	int i, num;
	senp *p;
	word *w;
	for (i = bcpnum - 1; i >= 0; i--)
	{
		dealnum--;
		if (bcpw[i] < 0)
			num = -bcpw[i];
		else
			num = bcpw[i];
		vari[num].vis = 0;
		memset(vari[num].pre, 0, sizeof(int)*vari[num].prenum);//清除蕴含图中受当前赋值结点影响的变元的记录
		vari[num].prenum = 0;
		p = vari[num].firstsen;
		while (p)
		{
			w = p->s->firstword;
			while (w)
			{
				if (w->no == bcpw[i]&&w->pon==1)
				{
					p->s->onenum--;
					w->pon = 0;
				}
				else if (w->no == -bcpw[i]&&w->pon==1)
				{
					p->s->zeronum--;
					w->pon = 0;
				}
				w = w->next;
			}
			p = p->next;
		}
	}
	return;
}

/*
	函数名称:Createnewsen
	函数功能：将变元赋值转化为引入一个只有该变元的单子句存入sat链表
	函数参数：sat链表，待赋值变元
	函数返回值：void
*/

void Createnewsen(sen *s, int v)
{
	sen *newsen = (sen *)malloc(sizeof(sen));
	word *newword = (word *)malloc(sizeof(word));
	newword->next = NULL;
	newword->no = v;
	newword->pon = 0;
	newsen->firstword = newword;
	newsen->onenum = 0;
	newsen->zeronum = 0;
	newsen->num = 1;
	newsen->nextsen = s->nextsen;//连接到sat链表表头结点后，方便之后删除
	s->nextsen = newsen;
	senp *newsenp = (senp *)malloc(sizeof(senp));
	newsenp->no = v;
	newsenp->s = newsen;
	newsenp->next = vari[abs(v)].firstsen;
	vari[abs(v)].firstsen = newsenp;//连接为v变元子句链表第一个结点，方便之后删除
	vari[abs(v)].tim++;
	return;
}

/*
	函数名称:Deletesen
	函数功能：删除上次赋值添加的单子句
	函数参数：sat链表，变元v
	函数返回值：void
*/

void Deletesen(sen *s, int v)
{
	sen *p = s->nextsen;
	word *w = p->firstword;
	senp *sp = vari[abs(v)].firstsen;
	s->nextsen = s->nextsen->nextsen;
	free(p);
	free(w);
	vari[abs(v)].firstsen = sp->next;
	free(sp);
	vari[abs(v)].tim--;
	return;
}

/*
	函数名称:Deletesam
	函数功能：将数组中相同元素删除
	函数参数：数组p，数组长度
	函数返回值：void
*/

void Deletesam(int *p, int *num)
{
	qsort(p, *num, sizeof(int), cmp);
	int i = (*num) - 2, j, tem = p[(*num) - 1];
	while (i >= 0)
	{
		if (p[i] == tem)
		{
			for (j = i; j < (*num) - 1; j++)//后面元素前移覆盖重复元素
				p[j] = p[j + 1];
			(*num)--;
		}
		tem = p[i];
		i--;
	}
	return;
}

/*
	函数名称:Genlearnedsen
	函数功能：基于蕴含图进行冲突子句学习
	函数参数：sat链表，冲突子句
	函数返回值：void
*/

void Genlearnedsen(sen s, sen l)
{

	learnnum++;
	sen *newsen = (sen *)malloc(sizeof(sen));
	newsen->firstword = NULL;
	newsen->nextsen = NULL;
	newsen->onenum = 0;
	word *w = l.firstword, *wp = NULL;
	int lnum = 0, i, te[MAXSENLENGTH];
	while (w)//从冲突子句各个元素向上寻找蕴含图中入度为0的结点
	{
		for (i = 0; i < vari[abs(w->no)].prenum; i++)
		{
			te[lnum] = vari[abs(w->no)].pre[i];
			lnum++;
		}
		w = w->next;
	}
	Deletesam(te, &lnum);//除重
	/*for(i=0;i<lnum;i++)
		printf("%d ",te[i]);
	printf("\n");*/
	newsen->num = newsen->zeronum = lnum;//将学习子句初始设定为冲突子句，方便back函数统一处理
	for (i = 0; i < lnum; i++)
	{
		w = (word *)malloc(sizeof(word));
		w->no = -te[i];//各个结点取反存入学习子句中
		w->pon = 1;
		w->next = NULL;
		if (wp == NULL)
			newsen->firstword = w;
		else
			wp->next = w;
		wp = w;
		senp *p = (senp *)malloc(sizeof(senp));
		p->no = w->no;
		p->s = newsen;
		p->next = NULL;
		vari[abs(w->no)].tail->next = p;//tail指针后移，tialini不动，两者之间为学习子句
		vari[abs(w->no)].tail = p;
		vari[abs(w->no)].tim++;
	}
	stail->nextsen = newsen;
	stail = newsen;//stail指针后移，stialini不动，两者之间为学习子句

	if (learnnum > MAXLEARNNUM)//学习子句更新，只保存最近MAXLEARNNUM个
	{
		//printf("%d\n",MAXLEARNNUM);
		sen *l = stailini->nextsen;
		stailini->nextsen = stailini->nextsen->nextsen;
		w = l->firstword;
		while (w)
		{
			senp *p = vari[abs(w->no)].tailini->next;
			vari[abs(w->no)].tailini->next = vari[abs(w->no)].tailini->next->next;
			if (vari[abs(w->no)].tailini->next == NULL)//处理当前只有一个子句释放当前子句后，tail和tailini连接丢失情况
				vari[abs(w->no)].tail = vari[abs(w->no)].tailini;//tail回到tailini
			vari[abs(w->no)].tim--;
			free(p);
			word *wd = w;
			w = w->next;
			free(wd);
		}
		free(l);
		learnnum--;
	}
	/*printf("learn(%d)   ",learnnum);
	w=newsen->firstword;
	while(w)
	{
		printf("%d ",w->no);
		w=w->next;
	}
	printf("\n");*/
	return;
}

/*
	函数名称:Getbacknum
	函数功能：非时序回溯，确定回溯层数
	函数参数：冲突子句
	函数返回值：回溯层数
*/

int Getbacknum(sen l)
{
	//printf("conflict ");
	word *w = l.firstword;
	int maxnum = 0, i;
	//int tak;
	while (w)//逐个寻找蕴含图中入度为0的结点的最大决策层数
	{
		for (i = 0; i < vari[abs(w->no)].prenum; i++)
		{
			if (vari[abs(vari[abs(w->no)].pre[i])].dec > maxnum)
			{
				maxnum = vari[abs(vari[abs(w->no)].pre[i])].dec;
				//tak=abs(vari[abs(w->no)].pre[i]);
			}
		}
		//printf("%d(%d) ",w->no,vari[abs(w->no)].prenum);
		w = w->next;
	}
	//printf("back  maxnum:%d,decnum:%d,%d(%d)\n",maxnum,decnum,maxnum-decnum,tak);
	return maxnum - decnum;
}

/*
	函数名称:dpll
	函数功能：dpll算法主体部分
	函数参数：sat链表
	函数返回值：算法执行状态参量
*/

status dpll(sen s)
{
	sen *l = Findsingle(s);//先寻找一个单元子句或单子句进行布尔约束传播
	int bcpw[MAXSENNUM], bcpnum = 0, num;
	while (l)
	{
		word *w = l->firstword;
		while (w->pon)
			w = w->next;
		num = w->no;
		bcpw[bcpnum] = num;//存储此次赋值影响到的变元方便Back处理
		bcpnum++;
		bcp(s, *l);//进行布尔约束传播
		re[dealnum] = num;//存储当前赋值
		//printf("put %d(%d)\n",num,dealnum);
		dealnum++;
		//while循环开始存储蕴含图中与该变元有关入度为0结点
		w = l->firstword;
		while (w)
		{
			if (w->no == num || w->no == -num)
			{
				w = w->next;
				continue;
			}
			else if (vari[abs(w->no)].dec)//存入新的入度为0的结点
			{
				vari[abs(num)].pre[vari[abs(num)].prenum] = vari[abs(w->no)].pre[0];
				vari[abs(num)].prenum++;
			}
			else if (vari[abs(w->no)].prenum)//继承指向当前结点的pre表
			{
				int i;
				for (i = 0; i < vari[abs(w->no)].prenum; i++)
					vari[abs(num)].pre[vari[abs(num)].prenum + i] = vari[abs(w->no)].pre[i];
				vari[abs(num)].prenum += i;
			}
			w = w->next;
		}
		Deletesam(vari[abs(num)].pre, &(vari[abs(num)].prenum));//除重
		/*int j;
		printf("///%d///",vari[abs(num)].prenum);
		for(j=0;j<vari[abs(num)].prenum;j++)
			printf("%d ",vari[abs(num)].pre[j]);
		printf("\n");*/
		if (satf(s))
			return TRUE;
		else
		{
			l = unsat(s);
			if (dealnum == varnum || l)
			{
				/*if (l == NULL)
				{
					Back(s, bcpw, bcpnum);
					return FALSE;
				}*/
				int ba = Getbacknum(*l);//非时序回溯
				Genlearnedsen(s, *l);//冲突学习
				Back(s, bcpw, bcpnum);//消除此次赋值的影响，恢复到此次赋值前状态
				return ba;
			}
		}
		l = Findsingle(s);
	}
	int v = select(s);//选取新变元进行赋值
	if (v)
	{
		Createnewsen(&s, v);
		//printf("*****%d*****\n",v);
		decnum++;
		vari[abs(v)].dec = decnum;//将新赋值变元记录为蕴含图中入度为0的结点
		vari[abs(v)].pre[0] = v;
		vari[abs(v)].prenum = 1;
		int ret = dpll(s);
		if (ret == 1)
			return TRUE;
		else if (ret != 0)//配合非时序回溯回溯至相关层数
		{
			Deletesen(&s, v);
			decnum--;
			vari[abs(v)].dec = 0;
			Back(s, bcpw, bcpnum);
			return ret + 1;
		}
		Deletesen(&s, v);
		decnum--;
		vari[abs(v)].dec = 0;
		Createnewsen(&s, -v);
		//printf("*****%d*****\n",-v);
		decnum++;
		vari[abs(v)].dec = decnum;
		vari[abs(v)].pre[0] = -v;
		vari[abs(v)].prenum = 1;
		ret = dpll(s);
		if (ret == 1)
			return TRUE;
		else if (ret != 0)//配合非时序回溯回溯至相关层数
		{
			Deletesen(&s, -v);
			decnum--;
			vari[abs(v)].dec = 0;
			Back(s, bcpw, bcpnum);
			return ret + 1;
		}
		Deletesen(&s, -v);
		decnum--;
		vari[abs(-v)].dec = 0;
	}
	Back(s, bcpw, bcpnum);
	return FALSE;
}
