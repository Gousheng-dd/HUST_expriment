#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

int cmp(const void *a, const void *b)
{
	return (abs(*(int *)a) - abs(*(int *)b));
}

/*
	��������:WriteFile
	�������ܣ���dpll������������Ӧ�ļ���
	��������������ļ�����dpll����ִ�н�����㷨ִ��ʱ��
	��������ֵ���㷨ִ��״̬����
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
		for (i = 0; i < dealnum; i++)//ֻ�����cnf����Ҫ�ı�Ԫȡֵ�������ɸ����������
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
	��������:Findsingle
	�������ܣ�Ѱ�ҵ�ǰsat�����еĵ���Ԫ�Ӿ��Ԫ�Ӿ�
	����������sat����
	��������ֵ��sat�����еĵ��Ӿ��Ԫ�Ӿ��λ�û��ָ��
*/

sen *Findsingle(sen s)
{
	sen *p = s.nextsen;
	while (p)
	{
		if (p->onenum)//�����������Ӿ�
		{
			p = p->nextsen;
			continue;
		}
		if (p->num == p->zeronum)//���ǲ����������Ӿ�
		{
			p = p->nextsen;
			continue;
		}
		if (p->num - p->zeronum == 1)//Ϊ��Ԫ�Ӿ�
			return p;
		p = p->nextsen;
	}
	return NULL;
}

/*
	��������:select
	�������ܣ�ѡ����һ��ֵ��Ԫ������JW�㷨��
	����������sat����
	��������ֵ����ѡ��Ԫ��ż�����
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
			tem += pow(2.0, -(double)(p->s->num - p->s->zeronum));//����JW�㷨������ÿ����ԪȨֵ
			p = p->next;
		}
		if (tem > res)
		{
			ans = i;
			res = tem;
		}
	}
	//������ɸѡ��Ԫ�Ľ��ŷ���
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
	��������:bcp
	�������ܣ�����Լ����������
	����������sat������ȷ��ֵ�ı�Ԫ
	��������ֵ��void
*/

void bcp(sen s, sen l)
{
	int num, wo, i = 0;
	word *w = l.firstword;
	while (w->pon)//�ڵ�Ԫ�Ӿ���Ѱ��δ��ֵ������
		w = w->next;
	num = w->no;
	if (num < 0)
		wo = -num;
	else
		wo = num;
	vari[wo].vis = 1;
	senp *p = vari[wo].firstsen;
	while (p)//�ڵ�ǰ��Ԫ���Ӿ�������������õ��Ӿ�ԭ�򻯼�
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
	��������:satf
	�������ܣ��жϵ�ǰ�Ƿ�������
	����������sat����
	��������ֵ���������򷵻�1���򷵻�0
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
	��������:unsatf
	�������ܣ��жϵ�ǰ�Ƿ���ڳ�ͻ�Ӿ�
	����������sat����
	��������ֵ����ͻ�Ӿ�λ��
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
	��������:Back
	�������ܣ�����ʱ�����һ�θ�ֵ������Ӱ���������ָ�����ֵ֮ǰ״̬
	����������sat�������θ�ֵ����й�����Լ����������ı�Ԫ��ű�
	��������ֵ��void
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
		memset(vari[num].pre, 0, sizeof(int)*vari[num].prenum);//����̺�ͼ���ܵ�ǰ��ֵ���Ӱ��ı�Ԫ�ļ�¼
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
	��������:Createnewsen
	�������ܣ�����Ԫ��ֵת��Ϊ����һ��ֻ�иñ�Ԫ�ĵ��Ӿ����sat����
	����������sat��������ֵ��Ԫ
	��������ֵ��void
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
	newsen->nextsen = s->nextsen;//���ӵ�sat�����ͷ���󣬷���֮��ɾ��
	s->nextsen = newsen;
	senp *newsenp = (senp *)malloc(sizeof(senp));
	newsenp->no = v;
	newsenp->s = newsen;
	newsenp->next = vari[abs(v)].firstsen;
	vari[abs(v)].firstsen = newsenp;//����Ϊv��Ԫ�Ӿ������һ����㣬����֮��ɾ��
	vari[abs(v)].tim++;
	return;
}

/*
	��������:Deletesen
	�������ܣ�ɾ���ϴθ�ֵ��ӵĵ��Ӿ�
	����������sat������Ԫv
	��������ֵ��void
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
	��������:Deletesam
	�������ܣ�����������ͬԪ��ɾ��
	��������������p�����鳤��
	��������ֵ��void
*/

void Deletesam(int *p, int *num)
{
	qsort(p, *num, sizeof(int), cmp);
	int i = (*num) - 2, j, tem = p[(*num) - 1];
	while (i >= 0)
	{
		if (p[i] == tem)
		{
			for (j = i; j < (*num) - 1; j++)//����Ԫ��ǰ�Ƹ����ظ�Ԫ��
				p[j] = p[j + 1];
			(*num)--;
		}
		tem = p[i];
		i--;
	}
	return;
}

/*
	��������:Genlearnedsen
	�������ܣ������̺�ͼ���г�ͻ�Ӿ�ѧϰ
	����������sat������ͻ�Ӿ�
	��������ֵ��void
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
	while (w)//�ӳ�ͻ�Ӿ����Ԫ������Ѱ���̺�ͼ�����Ϊ0�Ľ��
	{
		for (i = 0; i < vari[abs(w->no)].prenum; i++)
		{
			te[lnum] = vari[abs(w->no)].pre[i];
			lnum++;
		}
		w = w->next;
	}
	Deletesam(te, &lnum);//����
	/*for(i=0;i<lnum;i++)
		printf("%d ",te[i]);
	printf("\n");*/
	newsen->num = newsen->zeronum = lnum;//��ѧϰ�Ӿ��ʼ�趨Ϊ��ͻ�Ӿ䣬����back����ͳһ����
	for (i = 0; i < lnum; i++)
	{
		w = (word *)malloc(sizeof(word));
		w->no = -te[i];//�������ȡ������ѧϰ�Ӿ���
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
		vari[abs(w->no)].tail->next = p;//tailָ����ƣ�tialini����������֮��Ϊѧϰ�Ӿ�
		vari[abs(w->no)].tail = p;
		vari[abs(w->no)].tim++;
	}
	stail->nextsen = newsen;
	stail = newsen;//stailָ����ƣ�stialini����������֮��Ϊѧϰ�Ӿ�

	if (learnnum > MAXLEARNNUM)//ѧϰ�Ӿ���£�ֻ�������MAXLEARNNUM��
	{
		//printf("%d\n",MAXLEARNNUM);
		sen *l = stailini->nextsen;
		stailini->nextsen = stailini->nextsen->nextsen;
		w = l->firstword;
		while (w)
		{
			senp *p = vari[abs(w->no)].tailini->next;
			vari[abs(w->no)].tailini->next = vari[abs(w->no)].tailini->next->next;
			if (vari[abs(w->no)].tailini->next == NULL)//����ǰֻ��һ���Ӿ��ͷŵ�ǰ�Ӿ��tail��tailini���Ӷ�ʧ���
				vari[abs(w->no)].tail = vari[abs(w->no)].tailini;//tail�ص�tailini
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
	��������:Getbacknum
	�������ܣ���ʱ����ݣ�ȷ�����ݲ���
	������������ͻ�Ӿ�
	��������ֵ�����ݲ���
*/

int Getbacknum(sen l)
{
	//printf("conflict ");
	word *w = l.firstword;
	int maxnum = 0, i;
	//int tak;
	while (w)//���Ѱ���̺�ͼ�����Ϊ0�Ľ��������߲���
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
	��������:dpll
	�������ܣ�dpll�㷨���岿��
	����������sat����
	��������ֵ���㷨ִ��״̬����
*/

status dpll(sen s)
{
	sen *l = Findsingle(s);//��Ѱ��һ����Ԫ�Ӿ���Ӿ���в���Լ������
	int bcpw[MAXSENNUM], bcpnum = 0, num;
	while (l)
	{
		word *w = l->firstword;
		while (w->pon)
			w = w->next;
		num = w->no;
		bcpw[bcpnum] = num;//�洢�˴θ�ֵӰ�쵽�ı�Ԫ����Back����
		bcpnum++;
		bcp(s, *l);//���в���Լ������
		re[dealnum] = num;//�洢��ǰ��ֵ
		//printf("put %d(%d)\n",num,dealnum);
		dealnum++;
		//whileѭ����ʼ�洢�̺�ͼ����ñ�Ԫ�й����Ϊ0���
		w = l->firstword;
		while (w)
		{
			if (w->no == num || w->no == -num)
			{
				w = w->next;
				continue;
			}
			else if (vari[abs(w->no)].dec)//�����µ����Ϊ0�Ľ��
			{
				vari[abs(num)].pre[vari[abs(num)].prenum] = vari[abs(w->no)].pre[0];
				vari[abs(num)].prenum++;
			}
			else if (vari[abs(w->no)].prenum)//�̳�ָ��ǰ����pre��
			{
				int i;
				for (i = 0; i < vari[abs(w->no)].prenum; i++)
					vari[abs(num)].pre[vari[abs(num)].prenum + i] = vari[abs(w->no)].pre[i];
				vari[abs(num)].prenum += i;
			}
			w = w->next;
		}
		Deletesam(vari[abs(num)].pre, &(vari[abs(num)].prenum));//����
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
				int ba = Getbacknum(*l);//��ʱ�����
				Genlearnedsen(s, *l);//��ͻѧϰ
				Back(s, bcpw, bcpnum);//�����˴θ�ֵ��Ӱ�죬�ָ����˴θ�ֵǰ״̬
				return ba;
			}
		}
		l = Findsingle(s);
	}
	int v = select(s);//ѡȡ�±�Ԫ���и�ֵ
	if (v)
	{
		Createnewsen(&s, v);
		//printf("*****%d*****\n",v);
		decnum++;
		vari[abs(v)].dec = decnum;//���¸�ֵ��Ԫ��¼Ϊ�̺�ͼ�����Ϊ0�Ľ��
		vari[abs(v)].pre[0] = v;
		vari[abs(v)].prenum = 1;
		int ret = dpll(s);
		if (ret == 1)
			return TRUE;
		else if (ret != 0)//��Ϸ�ʱ����ݻ�������ز���
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
		else if (ret != 0)//��Ϸ�ʱ����ݻ�������ز���
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
