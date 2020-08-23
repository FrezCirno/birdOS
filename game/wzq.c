#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <conio.h>

#define ROW 100
#define COL 100

int hhh,lll;
void menu()
{
	printf("*******************************\n");
	printf("****  ��ӭ������������Ϸ�� ****\n");
	printf("****      1.������Ϸ       ****\n");
	printf("****      0.�˳���Ϸ       ****\n");
	printf("*******************************\n");
	printf("������0��1:");
	return;
}

//��ʼ��
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
	return;
}

//��ӡ���� 
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		printf("  %d ", i + 1); 
	}
	printf("\n");
	printf("|");
	for (j = 0; j < col; j++)
	{
		printf("---|"); 
	}
	printf("\n");

	for (i = 0; i < row; i++)
	{
		printf("|");
		for (j = 0; j < col; j++)
		{
			printf(" %c |", board[i][j]); 
		}
		printf(" %d ", i + 1); 
		printf("\n");
		printf("|");
		for (j = 0; j < col; j++)
		{
			printf("---|"); 
		}
		printf("\n");
	}
	return;
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("������:>\n");
	while (1)
	{
		x = rand() % row;
		y = rand() % col;

		if (board[x][y] == ' ')
		{
			board[x][y] = '0';
			break;
		}
		else
		{
			continue;
		}
	}
	return;
}


void PlayerMove(char board[ROW][COL], int row, int col��int,int fd_stdin,int fd_stdout)
{
	int x = 0;
	int y = 0;

	printf("�����:>\n");
	printf("����������(%d,%d): >", row, col)
	while (1)
	{
		//scanf("%d %d", &x, &y);
		read(fd_stdin, row, 3);
		read(fd_stdin, col, 3);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
	 		{
				board[x - 1][y - 1] = 'x';
				break;
			}
	
			else
			{
				printf("�������Ѿ���ռ��\n");
				printf("����������:>");
				continue;
			}
		}

		else
		{
			printf("����Ƿ�\n");
			printf("����������:>");
			continue;
		}
	}
	return;
}

int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}

	return 1;
}

//�ж���Ӯ
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col - 4; j++)
		{
			if (board[i][j] == board[i][j + 1]
				&& board[i][j + 1] == board[i][j + 2]
				&& board[i][j + 2] == board[i][j + 3]
				&& board[i][j + 3] == board[i][j + 4]
				&& board[i][j] != ' ')
			{
				return board[i][j];
			}
		}
	}

	// ��������������һ�ߣ�Ӯ�Ҳ���
	for (j = 0; j < col; j++)
	{
		for (i = 0; i < row - 4; i++)
		{
			if (board[i][j] == board[i + 1][j]
				&& board[i + 1][j] == board[i + 2][j]
				&& board[i + 2][j] == board[i + 3][j]
				&& board[i + 3][j] == board[i + 4][j]
				&& board[i][j] != ' ')
			{
				return board[i][j];
			}
		}
	}

	// б������������һ�ߣ�Ӯ�Ҳ���
	for (i = 0; i < row - 4; i++)
	{
		if (board[i][i] == board[i + 1][i + 1]
			&& board[i + 1][i + 1] == board[i + 2][i + 2]
			&& board[i + 2][i + 2] == board[i + 3][i + 3]
			&& board[i + 3][i + 3] == board[i + 4][i + 4]
			&& board[i][i] != ' ')
		{
			return board[i][i];
		}

		if (board[i][i + 4] == board[i + 1][i + 3]
			&& board[i + 1][i + 3] == board[i + 2][i + 2]
			&& board[i + 2][i + 2] == board[i + 3][i + 1]
			&& board[i + 3][i + 1] == board[i + 4][i]
			&& board[i][i + 4] != ' ')
		{
			return board[i][i + 4];
		}
	}

	//��Ϸƽ��
	if (IsFull(board, row, col))
	{
		return 'p';
	}

	//��Ϸ����
	return ' ';

}
void game(int fd_stdin, int fd_stdout)
{
	srand((unsigned int)time(NULL));
	printf("����������Ҫ�����̴�С����������100����");
	//scanf("%d", &hhh);
	//scanf("%d", &lll);
	read(fd_stdin, hhh, 3);
	read(fd_stdin, lll, 3);
	int ret = 0;
	char board[ROW][COL] = { 0 };
	InitBoard(board, hhh, lll);

	// ����
	while (1)
	{
		ComputerMove(board,hhh, lll); //������
		ret = IsWin(board, hhh, lll);
		if (ret != ' ')
		{
			break;
		}
		clear(); //�������Ż�����
		DisplayBoard(board, hhh, lll); //��ӡ����
		printf("\n");
		PlayerMove(board, hhh, lll,fd_stdin, fd_stdout); //�����
		ret = IsWin(board, hhh, lll);
		if (ret != ' ')
		{
			break;
		}
		DisplayBoard(board, hhh, lll); //��ӡ����
		printf("\n");
	}
	clear();
	// �ж���Ӯ��ƽ��
	if (ret == 'p')
	{
		printf("ƽ��!\n");
		DisplayBoard(board, hhh,lll); //��ӡ����
	}
	else if (ret == 'x')
	{
		printf("���Ӯ!\n");
		DisplayBoard(board, hhh, lll); //��ӡ����
	}
	else if (ret == '0')
	{
		printf("����Ӯ!\n");
		DisplayBoard(board,hhh, lll); //��ӡ����
	}
	printf("�������������\n");
	
	return;
}
int runWZQ(int fd_stdin, int fd_stdout) {
	hhh = ROW; lll = COL;
	int input = 0;
	do
	{
		clear();
		menu();
		//scanf("%d", &input);
		read(fd_stdin, input, 1);
		switch (input)
		{
		case 1:
			game(fd_stdin, fd_stdout);
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������\n");
		}
	} while (input);
	return;
}