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
#define MAXVARNUM 8000 //最大变元数目
#define MAXSENLENGTH 5000 //子句最大长度
#define MAXLEARNNUM 500 //存储的最大学习子句数目
#define MAXDIMNUM 8 //数独最大阶数
#define MAXSENNUM 20000 //最大子句数目
#define INITIALNUM 15 //挖洞法第一步随机填入个数，配合大于6阶数独，低于6阶需适当降低

typedef int status;

typedef struct word
{
	int no; //记录文字的序号及正负
	int pon; //记录文字对应变元是否赋值
	struct word *next;
}word;

typedef struct sen
{
	int num; //子句文字数目
	int zeronum; //子句不满足文字数目
	int onenum; //子句已满足文字数目
	struct word *firstword; //指向子句第一个文字
	struct sen *nextsen; //指向下一字句
}sen;

typedef struct senp
{
	int no; //记录所属变元序号及正负
	struct sen *s; //指向当前子句
	struct senp *next;
}senp;

typedef struct var
{
	int dec; //记录变元决策层数
	int pre[MAXSENLENGTH]; //记录相关蕴含图中入度为0的结点序号
	int prenum; //记录pre数组长度
	int vis; //记录变元是否赋值
	struct senp *firstsen; //指向包含该变元的第一个子句
	struct senp *tail; //永远指向该变元最后一个子句
	struct senp *tailini; //指向学习新子句前最后一个子句
	int tim; //记录变元总出现次数
}var;

extern struct var vari[MAXVARNUM];
extern struct sen s;
extern sen *stail, *stailini;
extern int varnum, sennum, dealnum, re[MAXVARNUM], decnum, learnnum;//re数组存储dpll最终结果，其中只包括保证cnf成立的变元取值，正负不影响结果的变元未包括
extern int cnf[MAXSENNUM][MAXVARNUM];//每行首号元素储存该子句变元个数

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