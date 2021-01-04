#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

struct var vari[MAXVARNUM];
struct sen s;
sen *stail, *stailini;
int varnum, sennum, dealnum, re[MAXVARNUM], decnum, learnnum;//re数组存储dpll最终结果，其中只包括保证cnf成立的变元取值，正负不影响结果的变元未包括
int cnf[MAXSENNUM][MAXVARNUM];//每行首号元素储存该子句变元个数

int main()
{
	clock_t start_t, end_t;
	double total_t;
	int nl, i, j, op = 1, sop, dim;
	char nam[200], onam[200], clnam[200], sud[MAXDIMNUM + 1][MAXDIMNUM + 1];
	status st;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("     请选择您要操作的内容：\n");
		printf("-------------------------------------------------\n\n");
		printf("\t1.SAT\t2.Binary Puzzle\n");
		printf("\t0.Exit\n\n");
		printf("-------------------------------------------------\n\n");
		printf("\t请选择您的操作[0~2]:");
		scanf("%d", &op);
		while (op < 0 || op>2)
		{
			printf("请输入正确的操作数范围[0~2]\n");
			scanf("%d", &op);
		}
		switch (op)
		{
		case 1:
			printf("请输入需要读取的cnf文件名：\n");
			scanf("%s", nam);
			st=ReadFile(nam, &s);
			while (st == ERROR)
			{
				printf("请输入正确的文件名：\n");
				scanf("%s", nam);
				st = ReadFile(nam, &s);
			}
			nl = strlen(nam);
			for (i = 0; i < nl - 4; i++)
				onam[i] = nam[i];
			onam[i] = '\0';
			strcat(onam, ".res");

			system("cls");	printf("\n\n");
			printf("     请选择您要操作的内容：\n");
			printf("-------------------------------------------------\n\n");
			printf("\t1.公式解析\t2.DPLL\n\n");
			printf("-------------------------------------------------\n\n");
			printf("\t请选择您的操作[1~2]:");
			scanf("%d", &sop);
			while (sop < 1 || sop>2)
			{
				printf("请输入正确的操作数范围[1~2]\n");
				scanf("%d", &sop);
			}
			if (sop == 1)
			{
				printf("请输入要输出的文件名！\n");
				getchar();
				scanf("%s", clnam);
				st = WriteClause(clnam, s);
				if (st == ERROR)
					printf("文件打开失败！\n");
				else
					printf("解析结果输出成功!\n");
			}
			else
			{
				start_t = clock();
				int ret = dpll(s);
				end_t = clock();
				total_t = ((double)(end_t - start_t) / CLOCKS_PER_SEC) * 1000;
				st = WriteFile(onam, ret, total_t);
				if (st == ERROR)
					printf("文件打开失败！\n");
				else
					printf("DPLL结果输出成功!\n");

			}
			Clearallsen(&s);
			getchar(); getchar();
			break;
		case 2:
			srand((unsigned)time(NULL));
			printf("请输入要生成数独阶数：\n");
			scanf("%d", &dim);
			Gensudoku(sud, dim);
			system("cls");	printf("\n\n");
			printf("已随机生成唯一解二进制数独：\n");
			for (i = 1; i <= dim; i++)
			{
				for (j = 1; j <= dim; j++)
					printf("| %c ", sud[i][j]);
				printf("|\n");
				if (i != dim)
				{
					for (j = 1; j <= dim; j++)
						printf("|---");
					printf("|\n");
				}
			}
			Transtocnf(sud, dim);
			printf("     请选择您要操作的内容：\n");
			printf("-------------------------------------------------\n\n");
			printf("\t1.转化为CNF文件\t2.DPLL求解数独\t3输入并求解已有数独\n\n");
			printf("-------------------------------------------------\n\n");
			printf("\t请选择您的操作[1~3]:");
			scanf("%d", &sop);
			while (sop < 1 || sop>3)
			{
				printf("请输入正确的操作数范围[1~3]\n");
				scanf("%d", &sop);
			}
			if (sop == 1)
			{
				printf("请输入要输出的文件名：\n");
				getchar();
				scanf("%s", nam);
				st = WritecnfFile(sud, dim, nam);
				if (st == ERROR)
					printf("文件打开失败！\n");
				else
					printf("对应CNF文件输出成功！\n");
			}
			else if(sop==2)
			{
				st = SolveSudoku(&s, dim);
				if (st == OK)
					PrintResult(dim);
				else
					printf("There is no result!\n");
			}
			else
			{
				printf("请输入数独阶数：\n");
				scanf("%d", &dim);
				printf("请输入数独内容：\n");
				getchar();
				for(i=1;i<=dim;i++)
				{
					for (j = 1; j <= dim; j++)
						scanf("%c", &sud[i][j]);
					getchar();
				}
				memset(cnf, 0, sizeof(cnf));
				Transtocnf(sud, dim);
				st = SolveSudoku(&s, dim);
				if (st == OK)
					PrintResult(dim);
				else
					printf("There is no result!\n");
			}
			Clearallsen(&s);
			getchar(); getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
	return 0;
}
