#define _CRT_SECURE_NO_WARNINGS
#include "sat.h"

struct var vari[MAXVARNUM];
struct sen s;
sen *stail, *stailini;
int varnum, sennum, dealnum, re[MAXVARNUM], decnum, learnnum;//re����洢dpll���ս��������ֻ������֤cnf�����ı�Ԫȡֵ��������Ӱ�����ı�Ԫδ����
int cnf[MAXSENNUM][MAXVARNUM];//ÿ���׺�Ԫ�ش�����Ӿ��Ԫ����

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
		printf("     ��ѡ����Ҫ���������ݣ�\n");
		printf("-------------------------------------------------\n\n");
		printf("\t1.SAT\t2.Binary Puzzle\n");
		printf("\t0.Exit\n\n");
		printf("-------------------------------------------------\n\n");
		printf("\t��ѡ�����Ĳ���[0~2]:");
		scanf("%d", &op);
		while (op < 0 || op>2)
		{
			printf("��������ȷ�Ĳ�������Χ[0~2]\n");
			scanf("%d", &op);
		}
		switch (op)
		{
		case 1:
			printf("��������Ҫ��ȡ��cnf�ļ�����\n");
			scanf("%s", nam);
			st=ReadFile(nam, &s);
			while (st == ERROR)
			{
				printf("��������ȷ���ļ�����\n");
				scanf("%s", nam);
				st = ReadFile(nam, &s);
			}
			nl = strlen(nam);
			for (i = 0; i < nl - 4; i++)
				onam[i] = nam[i];
			onam[i] = '\0';
			strcat(onam, ".res");

			system("cls");	printf("\n\n");
			printf("     ��ѡ����Ҫ���������ݣ�\n");
			printf("-------------------------------------------------\n\n");
			printf("\t1.��ʽ����\t2.DPLL\n\n");
			printf("-------------------------------------------------\n\n");
			printf("\t��ѡ�����Ĳ���[1~2]:");
			scanf("%d", &sop);
			while (sop < 1 || sop>2)
			{
				printf("��������ȷ�Ĳ�������Χ[1~2]\n");
				scanf("%d", &sop);
			}
			if (sop == 1)
			{
				printf("������Ҫ������ļ�����\n");
				getchar();
				scanf("%s", clnam);
				st = WriteClause(clnam, s);
				if (st == ERROR)
					printf("�ļ���ʧ�ܣ�\n");
				else
					printf("�����������ɹ�!\n");
			}
			else
			{
				start_t = clock();
				int ret = dpll(s);
				end_t = clock();
				total_t = ((double)(end_t - start_t) / CLOCKS_PER_SEC) * 1000;
				st = WriteFile(onam, ret, total_t);
				if (st == ERROR)
					printf("�ļ���ʧ�ܣ�\n");
				else
					printf("DPLL�������ɹ�!\n");

			}
			Clearallsen(&s);
			getchar(); getchar();
			break;
		case 2:
			srand((unsigned)time(NULL));
			printf("������Ҫ��������������\n");
			scanf("%d", &dim);
			Gensudoku(sud, dim);
			system("cls");	printf("\n\n");
			printf("���������Ψһ�������������\n");
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
			printf("     ��ѡ����Ҫ���������ݣ�\n");
			printf("-------------------------------------------------\n\n");
			printf("\t1.ת��ΪCNF�ļ�\t2.DPLL�������\t3���벢�����������\n\n");
			printf("-------------------------------------------------\n\n");
			printf("\t��ѡ�����Ĳ���[1~3]:");
			scanf("%d", &sop);
			while (sop < 1 || sop>3)
			{
				printf("��������ȷ�Ĳ�������Χ[1~3]\n");
				scanf("%d", &sop);
			}
			if (sop == 1)
			{
				printf("������Ҫ������ļ�����\n");
				getchar();
				scanf("%s", nam);
				st = WritecnfFile(sud, dim, nam);
				if (st == ERROR)
					printf("�ļ���ʧ�ܣ�\n");
				else
					printf("��ӦCNF�ļ�����ɹ���\n");
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
				printf("����������������\n");
				scanf("%d", &dim);
				printf("�������������ݣ�\n");
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
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}
