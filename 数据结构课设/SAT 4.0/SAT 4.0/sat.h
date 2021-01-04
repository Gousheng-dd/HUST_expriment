#ifndef SAT_H_INCLUDED
#define SAT_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define MAXVARNUM 8000 //����Ԫ��Ŀ
#define MAXSENLENGTH 5000 //�Ӿ���󳤶�
#define MAXLEARNNUM 500 //�洢�����ѧϰ�Ӿ���Ŀ
#define MAXDIMNUM 8 //����������
#define MAXSENNUM 20000 //����Ӿ���Ŀ
#define INITIALNUM 15 //�ڶ�����һ����������������ϴ���6������������6�����ʵ�����

typedef int status;

typedef struct word
{
	int no; //��¼���ֵ���ż�����
	int pon; //��¼���ֶ�Ӧ��Ԫ�Ƿ�ֵ
	struct word *next;
}word;

typedef struct sen
{
	int num; //�Ӿ�������Ŀ
	int zeronum; //�Ӿ䲻����������Ŀ
	int onenum; //�Ӿ�������������Ŀ
	struct word *firstword; //ָ���Ӿ��һ������
	struct sen *nextsen; //ָ����һ�־�
}sen;

typedef struct senp
{
	int no; //��¼������Ԫ��ż�����
	struct sen *s; //ָ��ǰ�Ӿ�
	struct senp *next;
}senp;

typedef struct var
{
	int dec; //��¼��Ԫ���߲���
	int pre[MAXSENLENGTH]; //��¼����̺�ͼ�����Ϊ0�Ľ�����
	int prenum; //��¼pre���鳤��
	int vis; //��¼��Ԫ�Ƿ�ֵ
	struct senp *firstsen; //ָ������ñ�Ԫ�ĵ�һ���Ӿ�
	struct senp *tail; //��Զָ��ñ�Ԫ���һ���Ӿ�
	struct senp *tailini; //ָ��ѧϰ���Ӿ�ǰ���һ���Ӿ�
	int tim; //��¼��Ԫ�ܳ��ִ���
}var;

extern struct var vari[MAXVARNUM];
extern struct sen s;
extern sen *stail, *stailini;
extern int varnum, sennum, dealnum, re[MAXVARNUM], decnum, learnnum;//re����洢dpll���ս��������ֻ������֤cnf�����ı�Ԫȡֵ��������Ӱ�����ı�Ԫδ����
extern int cnf[MAXSENNUM][MAXVARNUM];//ÿ���׺�Ԫ�ش�����Ӿ��Ԫ����

extern status ReadFile(char* name, sen *s);
extern status dpll(sen s);
extern sen *Findsingle(sen s);
extern int select(sen s);
extern void bcp(sen s, sen l);
extern int satf(sen s);
extern sen *unsat(sen s);
extern void Back(sen s, int *bcpw, int bcpnum);
extern void Createnewsen(sen *s, int v);
extern void Deletesen(sen *s, int v);
extern void Deletesam(int *p, int *num);
extern void Genlearnedsen(sen s, sen l);
extern int Getbacknum(sen l);
extern status WriteFile(char* name, int ret, double total_t);
extern status WriteClause(char* name, sen s);
extern void Clearallsen(sen *s);
extern status InitialSudoku(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim);
extern status Gensudoku(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim);
extern status Transtocnf(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim);
extern status WritecnfFile(char sud[MAXDIMNUM + 1][MAXDIMNUM + 1], int dim, char* name);
extern status SolveSudoku(sen *s, int dim);
extern status PrintResult(int dim);
extern int cmp(const void *a, const void *b);

#endif // SAT_H_INCLUDED