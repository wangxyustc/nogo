#include<stdio.h >
#include<time.h>
#include<stdlib.h> 
#define user 1
#define computer -1
void str_qi(int challengetable[][9], int kongtable[][9], int qitable[][9], int x, int y, int hb);
void Print(int table[][9]);
int overarea(int row, int column);
void userplay();
void computerplay();
int kill(int row, int column, int role);
int maybekilled(int row, int column, int role);
void restart(int array[][9]);
int goqi;
int winlose;
int challengetable[9][9] = { 0 };
int qitable[9][9] = { 0 };
int kongtable[9][9] = { 0 };
int main()
{
	printf("开始游戏请按s，退出游戏请其他键\n");
	if (getchar() != 's')
	{
		printf("您已退出游戏");
		getchar();
		getchar();
	}
	else
	{
        printf("游戏开始，中途提出请按q\n");
        winlose = 0;
		Print(challengetable);
       while (winlose==0)
        {
            userplay();
            if (winlose == 0)
            {
                computerplay();
            }
            else {
                break;
            }
        }
       if (winlose == 1)
       {
           printf("你赢了");
       }
       else {
           printf("你输了");
       }
        getchar();
        getchar();
	}
	return 0;

}
void restart(int array[][9])
{
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            array[i][j] = 0;
        }
    }
}
int kill(int row, int column,int role)
{
    goqi = 0;
    str_qi(challengetable, kongtable, qitable, row, column, role);
    restart(kongtable);
    restart(qitable);
    if (goqi > 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
int maybekilled(int row, int column, int role)
{
    if (challengetable[row - 1][column] == -role || challengetable[row + 1][column] == -role || challengetable[row][column - 1] == -role || challengetable[row][column + 1] == -role)
    {
        goqi = 0;
        if (challengetable[row - 1][column] == -role && row >= 1)
        {
            str_qi(challengetable, kongtable, qitable, row - 1, column, -role);
            restart(kongtable);
            restart(qitable);
            if (goqi != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        if (challengetable[row + 1][column] == -role && row <= 7)
        {
            str_qi(challengetable, kongtable, qitable, row + 1, column, -role);
            restart(kongtable);
            restart(qitable);
            if (goqi != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        if (challengetable[row][column - 1] == -role && column >= 1)
        {
            str_qi(challengetable, kongtable, qitable, row, column - 1, -role);
            restart(kongtable);
            restart(qitable);
            if (goqi != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        if (challengetable[row][column + 1] == -role && column <= 7)
        {
            str_qi(challengetable, kongtable, qitable, row, column + 1, -role);
            restart(kongtable);
            restart(qitable);
            if (goqi != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    else
    {
        return 0;
    }
}
void computerplay()
{
    srand((int)time(NULL));
    int x = rand() % 9;
    int y = rand() % 9;
    while (challengetable[x][y]!=0)
    {
        x = rand() % 9;
        y = rand() % 9;
    }
    challengetable[x][y] = -1;
    Print(challengetable);
    if (kill(x , y , -1))
    {
        winlose = 2;
    }
    else if(maybekilled(x, y, -1))
    {
        winlose = 1;
    }
    else
    {
        winlose = 0;
    }

}
void userplay()
{
    int x, y;
    printf("请输入对应的棋子坐标(x,y)");
    scanf("%d,%d", &x, &y);
    while(overarea(x-1, y-1)|| challengetable[x - 1][y - 1] != 0)
    {
        if (overarea(x - 1, y - 1))
        {
            printf("请输入范围内的棋子坐标(x,y)(1<=x<=9;1<=y<=9)");
            scanf("%d,%d", &x, &y);
        }
        if (challengetable[x - 1][y - 1] != 0)
        {
            printf("请输入空位的棋子坐标(x,y)");
            scanf("%d,%d", &x, &y);
        }

    }
    challengetable[x-1][y-1] = 1;
    Print(challengetable);
    if (kill(x - 1, y - 1, 1))
    {
        winlose = 1;
    }
    else if (maybekilled(x - 1, y - 1, 1))
    {
        winlose = 2;
    }
    else {
        winlose = 0;
    }

}
int overarea(int row,int column)
{
	if (row >= 9 || column >= 9||row<0||column<0)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}
void Print(int table[][9]) {
	for (int i = 0;i<9;i++)
	{
		for (int j = 0;j<9;j++)
		{
			printf("%4d", table[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}
void str_qi(int challengetable[][9], int kongtable[][9], int qitable[][9], int x, int y, int hb)
{
    qitable[x][y] = 1; 
    if (x + 1 <= 8)
    {
        if ((challengetable[x + 1][y] == 0) && (kongtable[x + 1][y] == 0))
        {
            goqi++; 
            kongtable[x + 1][y] = 1; 
        }
        else if ((challengetable[x + 1][y] == hb) && (qitable[x + 1][y] == 0))
        {
            str_qi(challengetable, kongtable, qitable, x + 1, y, hb); 
        }
    }
    if (x - 1 >= 0) 
    {
        if ((challengetable[x - 1][y] == 0) && (kongtable[x - 1][y] == 0))
            
        {
            goqi++; 
            kongtable[x - 1][y] = 1; 
        }
        else if ((challengetable[x - 1][y] == hb) && (qitable[x - 1][y] == 0))
            
        {
            str_qi(challengetable, kongtable, qitable, x - 1, y, hb); 
        }
    }
    if (y - 1 >= 0)
    {
        if ((challengetable[x][y - 1] == 0) && (kongtable[x][y - 1] == 0))
            
        {
            goqi++; 
            kongtable[x][y - 1] = 1; 
        }
        else if ((challengetable[x][y - 1] == hb) && (qitable[x][y - 1] == 0))
            
        {
            str_qi(challengetable, kongtable, qitable, x, y - 1, hb); 
        }
    }
    if (y + 1 <= 8)
    {
        if ((challengetable[x][y + 1] == 0) && (kongtable[x][y + 1] == 0))
            
        {
            goqi++; 
            kongtable[x][y + 1] = 1; 
        }
        else if ((challengetable[x][y + 1] == hb) && (qitable[x][y + 1] == 0))
            
        {
            str_qi(challengetable, kongtable, qitable, x, y + 1, hb); 
        }
    }
}