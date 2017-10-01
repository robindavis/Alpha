//===================header Files===============================
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
//====================Global Variables=========================
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

char file_output[2000];

unsigned int highscore=0,points=0;

int user_x=57,user_y=24;

char enemy_symbol='+';
int enemy_perline=1,enemy_color=10;
int enemy_cor_x[2675],enemy_cor_y[2675],e_cor_x[2675],e_cor_y[2675],temp_cor_x[115],temp_cor_y[115];
int k1=0,k2=0;

int misile_x=2,misile_y=2,misile_action=0,misile_symbol='#',misile_color=12;

int game_engine_state=1,misile_state=1;
unsigned int game_engine_time,misile_time;
//=================Functions====================
//--------Graphic Functions--------------
void gotoxy(int x,int y)
{COORD obj;obj.X=x;obj.Y=y;SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),obj);}

void box(int x1,int y1,int x2,int y2)
{int i1;for(i1=x1;i1<=x2;i1++){gotoxy(i1,y1);printf("%c",(char)(461));gotoxy(i1,y2);printf("%c",(char)(461));}for(i1=y1;i1<=y2;i1++){gotoxy(x1,i1);printf("%c",(char)(442));gotoxy(x2,i1);printf("%c",(char)(442));}gotoxy(x1,y2);printf("%c",(char)(456));gotoxy(x1,y1);printf("%c",(char)(457));gotoxy(x2,y2);printf("%c",(char)(444));gotoxy(x2,y1);printf("%c",(char)(443));}

void console_title(char a[])
{SetConsoleTitle(a);}

void alertbox(char title[],char data[])
{MessageBox(NULL,data,title,MB_OK);}

void textcolor(int color)
{WORD wColor;HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);CONSOLE_SCREEN_BUFFER_INFO csbi;if(GetConsoleScreenBufferInfo(hStdOut,&csbi)){wColor=(csbi.wAttributes & 0xF0)+(color & 0x0F);SetConsoleTextAttribute(hStdOut,wColor);}return;}

void  hidecursor()
{HANDLE consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);CONSOLE_CURSOR_INFO info;info.dwSize=100;info.bVisible=FALSE;SetConsoleCursorInfo(consoleHandle,&info);}

void game_all_window_clean()
{int i1,j1;for(i1=2;i1<117;i1++)for(j1=2;j1<30;j1++){gotoxy(i1,j1);printf(" ");}}

void game_textbox_clean()
{int i1,j1;for(i1=2;i1<117;i1++)for(j1=25;j1<30;j1++){gotoxy(i1,j1);printf(" ");}}

void game_custom_clean(int x1,int y1,int x2,int y2)
{int i1,j1;for(i1=x1;i1<=x2;i1++)for(j1=y1;j1<=y2;j1++){gotoxy(i1,j1);printf(" ");}}
//------------End Graphic Function--------------
//------------Time Function---------------------
int mili()
{clock_t t;unsigned int a;t=clock();a=t;return a;}

int time_count(int f1_time,int f2_time,int *cur_time,int *state)
{unsigned int res=-1,diff=-1;diff=(mili()-*cur_time);if(*state==1){if(diff>=f1_time){*state=2;*cur_time=mili();res=1;}else res=0;}else if(*state==2){if(diff>f2_time){*state=1;*cur_time=mili();res=2;}else res=0;}return res;}
//-------------End Time Functions----------------
//-------------Sound Functions------------
void sound(char a[])
{if(strcmp(a,"attack")==0){Beep(750,25);}
else if(strcmp(a,"crash")==0){Beep(1200,25);Beep(500,25);Beep(1200,25);}}
//-------------End Sound Functions----------------
//------------File Management Functions--------------------
void file_handling(char file[],char mode[],char data[])
{int ch;int i1=0;FILE *obj;obj=fopen(file,mode);if(strcmp(mode,"w")==0){while(data[i1]!='\0'){putc(data[i1],obj);i1++;}}if(strcmp(mode,"r")==0){while(!feof(obj)){ch=getc(obj);file_output[i1]=ch;i1++;}file_output[i1-1]='\0';}if(strcmp(mode,"a")==0){while(data[i1]!='\0'){putc(data[i1],obj);i1++;}}fclose(obj);}

int file_present(char a[])
{FILE *obj;obj=fopen(a,"r");if(obj=='\0'){return 0;}else {return 1;}}
//------------End File Management Functions--------------------
//------------General Game Functions-------------------
void enemy_show()
{int i1;for(i1=0;i1<k1;i1++){textcolor(enemy_color);gotoxy(enemy_cor_x[i1],enemy_cor_y[i1]);printf("%c",enemy_symbol);}}

void enemy_hide()
{int i1;for(i1=0;i1<k1;i1++){gotoxy(enemy_cor_x[i1],enemy_cor_y[i1]);printf(" ");}}

void temp_generator()
{int j1;for(j1=0;j1<enemy_perline;j1++){int i1;i1=rand()%115+2;temp_cor_x[k2]=i1;temp_cor_y[k2]=2;k2++;}}

void  top_to_down()
{time_t t;
int res=0,i1,j1,temp1=0;
res=time_count(8,240,&game_engine_time,&game_engine_state);

if(res==1)
{enemy_show();
temp_generator();}

if(res==2)
{k2--;
enemy_hide();
for(i1=0;i1<k1;i1++)
{if(k2>=0)
{e_cor_x[i1]=temp_cor_x[i1];
e_cor_y[i1]=temp_cor_y[i1];
k2--;}
else
{e_cor_x[i1]=enemy_cor_x[temp1];
e_cor_y[i1]=enemy_cor_y[temp1]+1;
temp1++;}}
k2++;
for(i1=0;i1<k1;i1++)
{enemy_cor_x[i1]=e_cor_x[i1];
enemy_cor_y[i1]=e_cor_y[i1];}}

}
//------------End General Game Functions---------------
//------------N.O.V.A Space Patrol Game Functions-----------------------------------

void game_initialize()
{
time_t t;
int i1,j1,k=0,l1;
char temp[200];

//Initializing Graphics
console_title("N.O.V.A Space Patrol");
hidecursor();
box(1,1,117,30);
if(file_present("nova.report")){alertbox("N.O.V.A Space Patrol","Welcome back Soldier!");file_handling("nova.report","r","");for(i1=0;i1<strlen(file_output);i1++){if(file_output[i1-1]=='='&&file_output[i1-2]=='1'&&file_output[i1-3]=='H'){for(j1=i1;file_output[j1]!=']';j1++){temp[k]=file_output[j1];k++;}}}temp[k]='\0';}else {highscore=0;file_handling("nova.report","w","[I=1][H1=0]");alertbox("N.O.V.A Space Patrol","Welcome to the \"N.O.V.A Space Patrol\"!\nWe are very happy to find a talented and skill full pilot for joining our army forces against the space pirates. Lets Rock!.");}
for(i1=2;i1<117;i1++){box(2,25,i1,29);if(i1!=116)game_custom_clean(i1,26,i1,28);}
alertbox("Game Controls","Controls:\nMoving UP--W,w,Up Arrow,8\nMoving Down--S,s,Down Arrow,2\nMoving Left--A,a,Left Arrow,4\nMoving Right--D,d,Right Arrow,6\nMoving Diagonally in 4 Directions--7,9,1,3\nShooting--5\nQuit-Q,q\n");
gotoxy(user_x,user_y);textcolor(11);printf("A");
textcolor(11);gotoxy(3,26);printf("Score:%d",points);
textcolor(12);highscore=atoi(temp);gotoxy(3,27);printf("Highscore: %d",highscore);

//Initialize Variables
srand((unsigned)time(&t));
for(j1=2;j1<=24;j1++){for(l1=1;l1<=enemy_perline;l1++){u:i1=rand()%115+2;enemy_cor_x[k1]=i1;if(user_x==enemy_cor_x[k1]){goto u;}enemy_cor_y[k1]=j1;k1++;}}
game_engine_state=1;game_engine_time=mili();
}

void game_engine()
{top_to_down();}

void game_monitor()
{char ch,temp1[200],temp2[200];
int i1,res=0;
//----------Key Stroke Monitoring Code Start----------------
while(kbhit())
{ch=getch();
if(ch=='q'||ch=='Q'){if(points>highscore){strcpy(temp1,"");strcat(temp1,"[I=1][H1=");itoa(points,temp2,10);strcat(temp1,temp2);strcat(temp1,"]");file_handling("nova.report","w",temp1);}exit(0);}
else if(ch==UP||ch=='w'||ch=='W'||ch=='8'){if(user_y!=2){gotoxy(user_x,user_y);printf(" ");user_y--;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch==DOWN||ch=='s'||ch=='S'||ch=='2'){if(user_y!=24){gotoxy(user_x,user_y);printf(" ");user_y++;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch==LEFT||ch=='a'||ch=='A'||ch=='4'){if(user_x!=2){gotoxy(user_x,user_y);printf(" ");user_x--;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch==RIGHT||ch=='d'||ch=='D'||ch=='6'){if(user_x!=116){gotoxy(user_x,user_y);printf(" ");user_x++;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch=='7'){if(user_y!=2&&user_x!=2){gotoxy(user_x,user_y);printf(" ");user_y--;user_x--;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch=='9'){if(user_y!=2&&user_x!=116){gotoxy(user_x,user_y);printf(" ");user_y--;user_x++;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch=='1'){if(user_y!=24&&user_x!=2){gotoxy(user_x,user_y);printf(" ");user_y++;user_x--;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch=='3'){if(user_y!=24&&user_x!=116){gotoxy(user_x,user_y);printf(" ");user_y++;user_x++;gotoxy(user_x,user_y);textcolor(11);printf("A");}}
else if(ch=='5'){sound("attack");if(misile_y==1)misile_y=2;gotoxy(misile_x,misile_y);printf(" ");misile_action=1;misile_x=user_x;misile_y=user_y-1;misile_time=mili();misile_state=1;}
}
//---------Key Stroke Monitoring Code End--------------
//---------------Misile Code Start----------------
if(misile_action==1)
{
res=time_count(5,2,&misile_time,&misile_state);
if(res==1)
{
textcolor(misile_color);
gotoxy(misile_x,misile_y);printf(" ");
for(i1=0;i1<k1;i1++)
{if(misile_x!=enemy_cor_x[i1]&&misile_y!=enemy_cor_y[i1]){}}
for(i1=0;i1<k1;i1++)
{if(misile_x==enemy_cor_x[i1]&&misile_y==enemy_cor_y[i1]){points++;textcolor(11);gotoxy(3,26);printf("Score:%d",points);if(points>highscore){textcolor(12);gotoxy(3,27);printf("Highscore: %d",points);}gotoxy(enemy_cor_x[i1],enemy_cor_y[i1]);printf(" ");enemy_cor_x[i1]=e_cor_x[0];enemy_cor_y[i1]=e_cor_y[0];misile_action=0;}}
misile_y--;
if(misile_y==1){misile_action=0;}
if(misile_action!=0)
{gotoxy(misile_x,misile_y);printf("%c",misile_symbol);}
}

if(res==2)
{}
}
//-----------Misile Code  End----------------
//---------------Crash Code Start---------------
for(i1=0;i1<k1;i1++)
{if(user_x==enemy_cor_x[i1]&&user_y==enemy_cor_y[i1]){sound("crash");alertbox("SpaceCraft Crashed!! :(","Game Over!\nBest of Luck next time!");if(points>highscore){strcpy(temp1,"");strcat(temp1,"[I=1][H1=");itoa(points,temp2,10);strcat(temp1,temp2);strcat(temp1,"]");file_handling("nova.report","w",temp1);}exit(0);}}
//---------------Crash Code  End---------------
}
//--------------End N.O.V.A Space Patrol Game Functions-----------------
/*==================================================
Graphic Functions:
1) gotoxy(x,y); <-No Dependancy
2) box(x1,y1,x2,y2); <-gotoxy();
3) console_title(""); <-No Dependanccy
4) alertbox("",""); <--No Dependancy
5) textcolor(x); <--No Dependancy
6) hidecursor(); <--No Dependancy
7) game_all_window_clean(); <--gotoxy(), Game Border Hard-Coded
8) game_custom_clean(); <--gotoxy(), Game Border Hard-Coded
9) game_textbox_clean(); <--gotoxy(), Game Border Hard-Coded

Time Functions:
1) time=mili(); <--No Dependancy, Function Name not proper
2) time_count(f1_tim,f2_time,&cur_time,&state); <---mili()

Sound Functions:
1) sound(); <--No Dependancy, Function Tweeking Required

File Management Functions:
1) file_handling("","",""); <---No Depandancy, Global variable "file_output" required
2) state=file_present("");,---No Dependancy, State=1:file present or Sate=0:file not present

General Game Functions:
1) enemy_show(); <--gotoxy()
2) enemy_hide(); <--gotoxy()
3) temp_generator(); <--No Dependancy
1) top_to_down(); <--srand needed to be initialized only once before calling this function again and again

N.O.V.A Space Patrol Game Functions:
1) game_initialize(); <--
2) game_engine(); <--
3) game_monitor(); <--

==================================================*/
int main()
{
game_initialize();
q:
game_engine();
game_monitor();
goto q;

return 0;}



//==================================================
