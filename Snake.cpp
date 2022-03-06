#include<iostream>
#include<conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define ConsoleWidth 25
#define ConsoleHeight 25

void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void clrscr(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE hConsoleOut;
    COORD Home = {0,0};
    DWORD dummy;

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

    FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
    csbiInfo.dwCursorPosition.X = 0;
    csbiInfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

using namespace std;


struct ToaDo
{
    int x, y;
};

struct Snake
{
    ToaDo dot[50];
    int n;
    char tt;
};

struct HoaQua
{
    ToaDo td;
};

void KhoiTao(Snake &snake,HoaQua &hq)
{
    snake.n=1;
    snake.dot[0].x=0;
    snake.dot[0].y=0;
    snake.tt = 'd';
    hq.td.x= rand() % ConsoleWidth;
    hq.td.y= rand() % ConsoleHeight;
}

void HienThi(Snake snake, HoaQua hq)
{
    clrscr();
    TextColor(7);
    for(int i=0;i<ConsoleHeight;i++)
    {
        gotoxy(ConsoleWidth,i);
        putchar('|');
    }
    TextColor(5);
    gotoxy(hq.td.x,hq.td.y);
    putchar('*');
    TextColor(13);
    gotoxy(snake.dot[0].x,snake.dot[0].y);
    putchar(2);
    for(int i=1;i<snake.n;i++)
    {
        gotoxy(snake.dot[i].x,snake.dot[i].y);
        putchar('O');
    }
}

void DieuKhien(Snake &snake)
{
    //trang thai cua tung dot
    for(int i=snake.n-1;i>0;i--)
    {
        snake.dot[i]=snake.dot[i-1];
    }
    if(kbhit())
    {
        int key=_getch();
        //dieu khien cai dau ran
        if(key=='a' || key=='A')
        {
            snake.tt = 'l';
        }
        else
        {
            if(key=='w' || key=='W')
            {
                snake.tt = 'u';
            }
            else
            {
                if(key=='s' || key=='S')
                {
                    snake.tt = 'd';
                }
                else
                {
                    if(key=='d' || key=='D')
                    {
                        snake.tt = 'r';
                    }
                }
            }
        }
    }
    if(snake.tt == 'u') snake.dot[0].y--;
    else if(snake.tt == 'd') snake.dot[0].y++;
    else if(snake.tt == 'l') snake.dot[0].x--;
    else if(snake.tt == 'r') snake.dot[0].x++;
}

int Xuly(Snake &snake, HoaQua &hq, int &thoigian,int &diem)
{
    if(snake.dot[0].x < 0 || snake.dot[0].x >= ConsoleWidth || snake.dot[0].y < 0 || snake.dot[0].y >= ConsoleHeight)
    {
        return -1;
    }
    for(int i=1;i<snake.n;i++)
    {
        if(snake.dot[0].x==snake.dot[i].x && snake.dot[0].y==snake.dot[i].y)
        {
            return -1;
        }
    }
    if(snake.dot[0].x==hq.td.x && snake.dot[0].y==hq.td.y)
    {
        for(int i=snake.n;i>0;i--)

            snake.dot[i]=snake.dot[i-1];

        snake.n++;
        diem++;
        if(snake.tt == 'u') snake.dot[0].y--;
        else if(snake.tt == 'd') snake.dot[0].y++;
        else if(snake.tt == 'l') snake.dot[0].x--;
        else if(snake.tt == 'r') snake.dot[0].x++;

        hq.td.x= rand() % ConsoleWidth;
        hq.td.y= rand() % ConsoleHeight;
        if(thoigian>50)
        thoigian-=5;
    }
}

void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}

void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press a, s, d, w to control the snake!!! ";
	cout<<"\n\n Press 'a/A' to move left";
	cout<<"\n\n Press 'd/D' to move right";
	cout<<"\n\n Press 's/S' to move down";
	cout<<"\n\n Press 'w/W' to move up";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play()
{
    int ma;
    int thoigian=150;
    srand(time(NULL));
    int diem=0;
    HoaQua hq;
    Snake snake;
    KhoiTao(snake,hq);
    while(1)
    {
        //hien thi
        HienThi(snake,hq);
        gotoxy(35,2);
        cout<<"Press a, w, s, d to control the snake!!!";
        //dieu khien
        DieuKhien(snake);
        //xu ly
        ma=Xuly(snake, hq, thoigian, diem);
        gotoxy(35,5);
        cout<<"Diem: "<<diem;
        if(ma==-1) //thua
        {
            gameover();
            return;
        }
        //toc do game
        Sleep(thoigian);
    }
}
int main()
{
    do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- ";
		gotoxy(10,6); cout<<" |        Snake Game      | ";
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();

		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);

	}while(1);

	return 0;
}
