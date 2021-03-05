 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <wctype.h>
void text_color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void goto_xy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
COORD get_curent_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
    return cbsi.dwCursorPosition;
}
int input(double *total){
	int check;
	fflush(stdin);
	check = scanf("%lf", total);
	return check;
}
bool is_wrong_condition(double total, int check_format){
	bool check = false;
	
	if(check_format == 1){
		check = false;
	}else check = true;
	
	if(total > (int)total){
		check = true;
	}
	
	if(total < 2 || total > 12){
		check = true;
	}
	
	return check;
}

void draw_dice(int x, int col, int row){

	int r;
	char*o="O";
	r = x-1;
	char i = o [r<1];
	char j = o [r<3]; 
	char k = o [r<5];
	goto_xy(col, row);
	printf("--%d--", x);
	goto_xy(col, 1+row);
	printf("|%c %c|", i, j);
	goto_xy(col, 2+row);
	printf("|%c%c%c|", k, o[r&1], k);
	goto_xy(col, 3+row);
	printf("|%c %c|", j, i);
	goto_xy(col, 4+row);
	printf("-----");
}


int main(int argc, char *argv[]){
	char key_exit;
	COORD position;
	srand(time(NULL));
	do{
		int x, y, count = 0, check_format;
		double total;
		system("cls");
		system("color 2");
		printf("Dice Thrower\n====================\nTotal sought: ");
		do{
			check_format = input(&total);
		}while(is_wrong_condition(total, check_format) && printf("Total must be integer in range[2, 12]\n"));
		
		do{
			position = get_curent_pos();
			x = rand()%6 + 1;
			y = rand()%6 + 1;
			text_color(x+y);
			Sleep(800 - total + count);
			draw_dice(x, 50, position.Y),
			draw_dice(y, 60, position.Y);
			goto_xy(position.X ,position.Y);
			printf("Result of throw: %d:\n",++count);
					
		}while(x+y != total);
		printf("\nYou got your total in %d throws!\n", count);
		printf("Do you want to continue(y = yes, n = no): ");
		do{
			fflush(stdin);
			key_exit = getchar();
		}while(key_exit != 'n' && key_exit != 'y' && printf("Enter (y or n): "));
	}while(key_exit == 'y');
	
	
	
	
}
