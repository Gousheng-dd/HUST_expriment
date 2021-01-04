#include<stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	void FUN1(void);
	void FUN2(void);
	void FUN3(void);
	void FUN4(void);
	void FUN5(void);
	void FUN6(void);
	void FUN7(void);
	void FUN8(void);
	extern char AUTH;
	extern char BNAME[10];
	extern int GOOD;
	extern char GOODNAME[10];
#ifdef __cplusplus
}
#endif



int main()
{
	int cmd,op=1;
	while (op)
	{
		printf("WELCOME!\nCurrent user name:");
		if (AUTH)
			printf("%s\n", BNAME);
		else
			printf("Customer\n");
		printf("Current browsing product name:");
		if (GOOD)
			printf("%s\n", GOODNAME);
		else
			printf("\n");
		printf("Please put in your command:\n");
		printf("1.LOGIN\t\t2.SEARCH GOODS\n");
		printf("3.ORDER GOODS\t\t4.CALCULATE POP\n");
		printf("5.RANK\t\t6.CHANGE INFORMATION\n");
		printf("7.CHANGE ENVIRONMENT\t\t8.PRINT CS\n9.QUIT\n");
		scanf("%d",&cmd);
		switch (cmd)
		{
		case 1:
			FUN1();
			break;
		case 2:
			FUN2();
			break;
		case 3:
			FUN3();
			break;
		case 4:
			FUN4();
			break;
		case 5:
			FUN5();
			break;
		case 6:
			FUN6();
			break;
		case 7:
			FUN7();
			break;
		case 8:
			FUN8();
			break;
		case 9:
			op = 0;
			break;
		default:
			printf("Please put in number form 1 to 9!\n");
			break;
		}
	}
	printf("Thanks for your use!\n");
	return 0;
}