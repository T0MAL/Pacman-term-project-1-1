# include "iGraphics.h"
#include "limits.h"
#include "math.h"
#include "iostream"
#include "algorithm"
#include "bits/stdc++.h"
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
//function prototypes
void scatter(int targetx,int targety,int *posx,int *posy,int *x,int *y,int *velpx,int *velnx,int *velpy,int *velny);
void collitioncheck();
void initializedots();
int endcheck();
void highscore_check();
void drawTextBox()
{

	iSetColor(150, 150, 150);
	iRectangle(50, 250, 250, 30);
}
//mode initializations
int gameon,mainmenu=1,scoremenu,pausemenu,namemenu,gameoverscreen;
int gamescreen,deathanimation,pacdeathanimation,help,namescreen;
bool mainmenumusic=false;
bool gameonmusic=false;
bool deathmusic=false;
bool gameovermusic=false;
int soundon=1;

//pac initialization
int pacmanstartx,pacmanstarty,pacinitialposx,pacvel;
int pacposx;
int pacinitialposy;
int pacposy;
int pacvelnx,pacvelpy,pacvelny,pacvelpx;
int rightx,righty,upx,upy,leftx,lefty,downx,downy;
void initializepac(){
    pacmanstartx=9;pacmanstarty=5;pacinitialposx=pacmanstartx;pacvel=2;
    pacposx=pacinitialposx*30;
    pacinitialposy=pacmanstarty;
    pacposy=pacinitialposy*30;
    pacvelnx=pacvel,pacvelpy=0,pacvelny=0,pacvelpx=0;
}


//game modes
int scattermode=0,chasemode=1,gamestarted;
//int gamestarted;

//score and files
FILE *fp=NULL;
FILE *fp2=NULL;
FILE *fp3=NULL;
FILE *fp4=NULL;
FILE *fpp=NULL;
char highscore[100];
char highname[15];
int score;
char name[30];
int targetscore=700;
int life=3;
char sscore[10];
int ssscore[10];
char ssname[10][10];
char str[100], str2[100];
int len;
int mode;

//perks
struct fruits{
    int on,x,y,points,when,flag,flag2;
}cherry,strawberry,banana,apple;

void initializefruits(){
    cherry.x =9;
    cherry.y=9;
    cherry.when=0;
    cherry.on=0;
    cherry.points=100;
    cherry.flag2=0;
    cherry.flag=0;
    apple.on=0;
    apple.x=9;
    apple.y=17;
    apple.when=700;
    apple.points=200;
    apple.flag2=0;
    apple.flag=0;
    banana.on=0;
    banana.x=9;
    banana.y=5;
    banana.when=1100;
    banana.points=300;
    banana.flag2=0;
    banana.flag=0;
    strawberry.on=0;
    strawberry.x=9;
    strawberry.y=13;
    strawberry.when=1600;
    strawberry.points=300;
    strawberry.flag2=0;
    strawberry.flag=0;
    help=0;
}
struct perks{
    int x,y,on,when,time,howmuch,started,currentlife;
}key,candy;

void initializeperks(){
    key.x=17;
    key.y=17;
    key.on=0;
    key.when=1000;
    key.time=0;
    key.howmuch=10;
    key.started=0;
    key.currentlife=6;
    candy.x=1;
    candy.y=19;
    candy.on=0;
    candy.when=1500;
    candy.time=0;
    candy.howmuch=10;
    candy.started=0;
    candy.currentlife=6;
    }
//time
int timee=0;
int tt=20;
//ghost initialozation
int ghstvel=1,cyanvel=1;
struct ghost{
    int x,y,dpx,dpy,dnx,dny,posx,posy;
}red,pink,orange,cyan;
void initializeghost(){
    red.x=6;
    red.y=13;
    red.posx=red.x*30;
    red.posy=red.y*30;
    red.dpx=ghstvel;
    red.dpy=0;
    red.dnx=0;
    red.dny=0;
    cyan.x=6;
    cyan.y=11;
    cyan.posx=cyan.x*30;
    cyan.posy=cyan.y*30;
    cyan.dpx=0;
    cyan.dnx=0;
    cyan.dny=0;
    cyan.dpy=cyanvel;
    orange.x=9;
    orange.y=13;
    orange.posx=orange.x*30;
    orange.posy=orange.y*30;
    orange.dpx=0;
    orange.dnx=ghstvel;
    orange.dny=0;
    orange.dpy=0;
    pink.x=12;
    pink.y=12;
    pink.posx=pink.x*30;
    pink.posy=pink.y*30;
    pink.dpx=0;
    pink.dnx=0;
    pink.dny=ghstvel;
    pink.dpy=0;
}

//bmp initialization
char apples[]="images\\apple.bmp";
char strawberrys[]="images\\strawberry.bmp";
char bananas[]="images\\banana.bmp";
char cherrys[]="images\\cherry.bmp";
char eatingpacpicsu[3][30]={"images\\pdu1.bmp","images\\pdu2.bmp","images\\pdu3.bmp"};
char eatingpacpicsl[3][30]={"images\\pdl1.bmp","images\\pdl2.bmp","images\\pdl3.bmp"};
char eatingpacpicsd[3][30]={"images\\pdd1.bmp","images\\pdd2.bmp","images\\pdd3.bmp"};
char eatingpacpicsr[3][30]={"images\\pdr1.bmp","images\\pdr2.bmp","images\\pdr3.bmp"};
char redghostfigure[4][30]={"images\\r1-1.bmp","images\\r2-1.bmp","images\\r3-1.bmp","images\\r4-1.bmp"};
char cyanghostfigure[4][30]={"images\\b1-2.bmp","images\\b2-2.bmp","images\\b3-2.bmp","images\\b4-2.bmp"};
char orangeghostfigure[4][30]={"images\\o1-2.bmp","images\\o2-2.bmp","images\\o3-2.bmp","images\\o4-2.bmp"};
char pinkghostfigure[4][30]={"images\\pi1-2.bmp","images\\pi2-2.bmp","images\\pi3-2.bmp","images\\pi4-2.bmp"};
char death[6][40]={"images\\death\\pd5.bmp","images\\death\\pd6.bmp","images\\death\\pd7.bmp","images\\death\\pd8.bmp","images\\death\\pd9.bmp","images\\death\\pd10.bmp",};
int eatingpacpicsind=0,deathindex=0;

//maze and food
int dots[21][19]={0};
int maze[21][19]={
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
                                1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
                                1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
                                1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
                                1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
                                0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                                1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
                                0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                                1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
                                0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                                1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
                                1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
                                1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
                                1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,


                };

//ghost ai
void redchase(){
    scatter(pacinitialposx,pacinitialposy,&red.x,&red.y,&red.posx,&red.posy,&red.dpx,&red.dnx,&red.dpy,&red.dny);
}
void cyanchase(){
    if(cyan.x==0&&cyan.y==11&&cyan.dnx){
        cyan.posx=18*30;cyan.x=18;}
    if(cyan.x==18&&cyan.y==11&&cyan.dpx){
        cyan.posx=0;cyan.x=0;}
    cyan.posx+=cyan.dpx;
    cyan.posx-=cyan.dnx;
    cyan.posy+=cyan.dpy;
    cyan.posy-=cyan.dny;
    if(cyan.posx%30==0)
        cyan.x=cyan.posx/30;
    if(cyan.posy%30==0)
        cyan.y=cyan.posy/30;
    int tmp1=INT_MAX,tmp2=INT_MAX,tmp3=INT_MAX;
    if((cyan.dnx||cyan.dpx)&&maze[cyan.y-1][cyan.x]==1&&maze[cyan.y+1][cyan.x]==1&&cyan.posx%30==0&&cyan.posy%30==0){

    }
    else if(cyan.dnx&&cyan.posx%30==0&&cyan.posy%30==0){
        if(maze[cyan.y][cyan.x-1]==0){
            if(pacvelnx)
                tmp1=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp1=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx-4,2);
            else if(pacvelpy){
                tmp1=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x-1-pacinitialposx+4,2);
                printf("%d %d\n",pacinitialposx-4,pacinitialposy+4);
            }
            else if(pacvelny)
                tmp1=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x-1-pacinitialposx-4,2);
        }
         if(maze[cyan.y-1][cyan.x]==0){
            if(pacvelnx)
                tmp2=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp2=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp2=pow(cyan.y-1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelny)
                tmp2=pow(cyan.y-1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
         if(maze[cyan.y+1][cyan.x]==0){
             if(pacvelnx)
                tmp3=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp3=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp3=pow(cyan.y+1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelny)
                tmp3=pow(cyan.y+1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
        //int tmp=std::min(std::min(tmp1,tmp2),tmp3);
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            cyan.dnx=0;
            cyan.dny=cyanvel;
            cyan.dpx=0;
            cyan.dpy=0;
        }
        else if(tmp==tmp3&&cyan.posx%30==0&&cyan.posy%30==0){
            cyan.dnx=0;
            cyan.dny=0;
            cyan.dpx=0;
            cyan.dpy=cyanvel;
        }
    }
    else if(cyan.dpx&&cyan.posx%30==0&&cyan.posy%30==0){
        if(maze[cyan.y][cyan.x+1]==0){
            if(pacvelnx)
                tmp1=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp1=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp1=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelny)
                tmp1=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x+1-pacinitialposx-4,2);
        }
         if(maze[cyan.y-1][cyan.x]==0){
            if(pacvelnx)
                tmp2=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp2=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp2=pow(cyan.y-1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelny)
                tmp2=pow(cyan.y-1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
         if(maze[cyan.y+1][cyan.x]==0){
            if(pacvelnx)
                tmp3=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp3=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp3=pow(cyan.y+1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelny)
                tmp3=pow(cyan.y+1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            cyan.dnx=0;
            cyan.dny=cyanvel;
            cyan.dpx=0;
            cyan.dpy=0;
        }
        else if(tmp==tmp3){
            cyan.dnx=0;
            cyan.dny=0;
            cyan.dpx=0;
            cyan.dpy=cyanvel;
        }
    }
    else if(cyan.dpy&&cyan.posx%30==0&&cyan.posy%30==0){
        if(maze[cyan.y+1][cyan.x]==0){
            if(pacvelnx)
                tmp1=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp1=pow(cyan.y+1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp1=pow(cyan.y+1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
           else  if(pacvelny)
                tmp1=pow(cyan.y+1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
         if(maze[cyan.y][cyan.x+1]==0){
            if(pacvelnx)
                tmp2=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp2=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp2=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelny)
                tmp2=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x+1-pacinitialposx-4,2);
        }
         if(maze[cyan.y][cyan.x-1]==0){
            if(pacvelnx)
                tmp3=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp3=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx-4,2);
           else  if(pacvelpy)
                tmp3=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x-1-pacinitialposx+4,2);
            else if(pacvelny)
                tmp3=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x-1-pacinitialposx-4,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            cyan.dnx=0;
            cyan.dny=0;
            cyan.dpx=cyanvel;
            cyan.dpy=0;
        }
        else if(tmp==tmp3){
            cyan.dnx=cyanvel;
            cyan.dny=0;
            cyan.dpx=0;
            cyan.dpy=0;
        }
    }
    else if(cyan.dny&&cyan.posx%30==0&&cyan.posy%30==0){
        if(maze[cyan.y-1][cyan.x]==0){
            if(pacvelnx)
                tmp1=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp1=pow(cyan.y-1-pacinitialposy,2)+pow(cyan.x-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp1=pow(cyan.y-1-pacinitialposy-4,2)+pow(cyan.x-pacinitialposx+4,2);
            else if(pacvelny)
                tmp1=pow(cyan.y-1-pacinitialposy+4,2)+pow(cyan.x-pacinitialposx-4,2);
        }
         if(maze[cyan.y][cyan.x+1]==0){
            if(pacvelnx)
                tmp2=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp2=pow(cyan.y-pacinitialposy,2)+pow(cyan.x+1-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp2=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x+1-pacinitialposx+4,2);
            else if(pacvelny)
                tmp2=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x+1-pacinitialposx-4,2);
        }
         if(maze[cyan.y][cyan.x-1]==0){
             if(pacvelnx)
                tmp3=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx+4,2);
            else if(pacvelpx)
                tmp3=pow(cyan.y-pacinitialposy,2)+pow(cyan.x-1-pacinitialposx-4,2);
            else if(pacvelpy)
                tmp3=pow(cyan.y-pacinitialposy-4,2)+pow(cyan.x-1-pacinitialposx+4,2);
            else if(pacvelny)
                tmp3=pow(cyan.y-pacinitialposy+4,2)+pow(cyan.x-1-pacinitialposx-4,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            cyan.dnx=0;
            cyan.dny=0;
            cyan.dpx=cyanvel;
            cyan.dpy=0;
        }
        else if(tmp==tmp3){
            cyan.dnx=cyanvel;
            cyan.dny=0;
            cyan.dpx=0;
            cyan.dpy=0;
        }
    }
}
void orangechase(){

    int distance=pow(orange.x-pacinitialposx,2)+pow(orange.y-pacinitialposy,2);
    if(distance>=64){
        scatter(pacinitialposx,pacinitialposy,&orange.x,&orange.y,&orange.posx,&orange.posy,&orange.dpx,&orange.dnx,&orange.dpy,&orange.dny);}
    else{
        scatter(1,1,&orange.x,&orange.y,&orange.posx,&orange.posy,&orange.dpx,&orange.dnx,&orange.dpy,&orange.dny);
    }
}
void pinkchase(){
  if(pink.x==0&&pink.y==11&&pink.dnx){
        pink.posx=18*30;pink.x=18;}
    if(pink.x==18&&pink.y==11&&pink.dpx){
        pink.posx=0;pink.x=0;}
    pink.posx+=pink.dpx;
    pink.posx-=pink.dnx;
    pink.posy+=pink.dpy;
    pink.posy-=pink.dny;
    if(pink.posx%30==0)
        pink.x=pink.posx/30;
    if(pink.posy%30==0)
        pink.y=pink.posy/30;
    int tmp1=INT_MAX,tmp2=INT_MAX,tmp3=INT_MAX;
    if((pink.dnx||pink.dpx)&&maze[pink.y-1][pink.x]==1&&maze[pink.y+1][pink.x]==1&&pink.posx%30==0&&pink.posy%30==0){

    }
    else if(pink.dnx&&pink.posx%30==0&&pink.posy%30==0){
        if(maze[pink.y][pink.x-1]==0){
            if(pacvelnx)
                tmp1=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp1=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy){
                tmp1=pow(pink.y-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-1-pacinitialposx+2,2);}
            else if(pacvelny)
                tmp1=pow(pink.y-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-1-pacinitialposx-2,2);
        }
         if(maze[pink.y-1][pink.x]==0){
            if(pacvelnx)
                tmp2=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp2=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp2=pow(pink.y-1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2,2);
            else if(pacvelny)
                tmp2=pow(pink.y-1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2,2);
        }
         if(maze[pink.y+1][pink.x]==0){
             if(pacvelnx)
                tmp3=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp3=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp3=pow(pink.y+1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2,2);
            else if(pacvelny)
                tmp3=pow(pink.y+1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2,2);
        }
        //int tmp=std::min(std::min(tmp1,tmp2),tmp3);
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            pink.dnx=0;
            pink.dny=ghstvel;
            pink.dpx=0;
            pink.dpy=0;
        }
        else if(tmp==tmp3&&pink.posx%30==0&&pink.posy%30==0){
            pink.dnx=0;
            pink.dny=0;
            pink.dpx=0;
            pink.dpy=ghstvel;
        }
    }
    else if(pink.dpx&&pink.posx%30==0&&pink.posy%30==0){
        if(maze[pink.y][pink.x+1]==0){
            if(pacvelnx)
                tmp1=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp1=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp1=pow(pink.y-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp1=pow(pink.y-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y-1][pink.x]==0){
            if(pacvelnx)
                tmp2=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp2=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp2=pow(pink.y-1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp2=pow(pink.y-1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y+1][pink.x]==0){
            if(pacvelnx)
                tmp3=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp3=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp3=pow(pink.y+1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp3=pow(pink.y+1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            pink.dnx=0;
            pink.dny=ghstvel;
            pink.dpx=0;
            pink.dpy=0;
        }
        else if(tmp==tmp3){
            pink.dnx=0;
            pink.dny=0;
            pink.dpx=0;
            pink.dpy=ghstvel;
        }
    }
    else if(pink.dpy&&pink.posx%30==0&&pink.posy%30==0){
        if(maze[pink.y+1][pink.x]==0){
            if(pacvelnx)
                tmp1=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp1=pow(pink.y+1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp1=pow(pink.y+1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
           else  if(pacvelny)
                tmp1=pow(pink.y+1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y][pink.x+1]==0){
            if(pacvelnx)
                tmp2=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp2=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp2=pow(pink.y-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp2=pow(pink.y-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y][pink.x-1]==0){
            if(pacvelnx)
                tmp3=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx+2,2+(pacinitialposx+2-red.x));
            else if(pacvelpx)
                tmp3=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
           else  if(pacvelpy)
                tmp3=pow(pink.y-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp3=pow(pink.y-pacinitialposy+2,2)+pow(pink.x-1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            pink.dnx=0;
            pink.dny=0;
            pink.dpx=ghstvel;
            pink.dpy=0;
        }
        else if(tmp==tmp3){
            pink.dnx=ghstvel;
            pink.dny=0;
            pink.dpx=0;
            pink.dpy=0;
        }
    }
    else if(pink.dny&&pink.posx%30==0&&pink.posy%30==0){
        if(maze[pink.y-1][pink.x]==0){
            if(pacvelnx)
                tmp1=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp1=pow(pink.y-1-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp1=pow(pink.y-1-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp1=pow(pink.y-1-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y][pink.x+1]==0){
            if(pacvelnx)
                tmp2=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp2=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp2=pow(pink.y-pacinitialposy-2+(pacinitialposy-2-red.y),2)+pow(pink.x+1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp2=pow(pink.y-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x+1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
         if(maze[pink.y][pink.x-1]==0){
             if(pacvelnx)
                tmp3=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelpx)
                tmp3=pow(pink.y-pacinitialposy+pacinitialposy-red.y,2)+pow(pink.x-1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
            else if(pacvelpy)
                tmp3=pow(pink.y-pacinitialposy-2+(pacinitialposy+2-red.y),2)+pow(pink.x-1-pacinitialposx+2+(pacinitialposx+2-red.x),2);
            else if(pacvelny)
                tmp3=pow(pink.y-pacinitialposy+2+(pacinitialposy+2-red.y),2)+pow(pink.x-1-pacinitialposx-2+(pacinitialposx-2-red.x),2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            pink.dnx=0;
            pink.dny=0;
            pink.dpx=ghstvel;
            pink.dpy=0;
        }
        else if(tmp==tmp3){
            pink.dnx=ghstvel;
            pink.dny=0;
            pink.dpx=0;
            pink.dpy=0;
        }
    }
}
void iDraw()
{
    iClear();
    if(gamescreen){

    //place your drawing codes here
    iShowBMP(0,0,"images\\gmback.bmp");
    for(int i=0;i<21;i++){
        for(int j=0;j<19;j++){
            if(maze[i][j]==1){
                iSetColor (187, 0, 255);
                iFilledRectangle(j*30,i*30,30,30);
            }
            else if(maze[i][j]==0&&dots[i][j]==0){
                iSetColor(200,200,200);
                iFilledCircle(j*30+15,i*30+15,4);
            }
        }
    }
    if(soundon)
        iShowBMP2(400,650,"images\\soundon.bmp",0);
    else
        iShowBMP2(400,650,"images\\soundoff.bmp",0);
    if(key.started||candy.started){
        iSetColor(255,0,0);
        char temp1[3];
    char temp2[3];
        sprintf(temp1,"%d",key.time);
        sprintf(temp2,"%d",candy.time);
        if(key.started)
        iText(480,650,temp1);
        if(candy.started)
        iText(500,650,temp2);
    }
    iSetColor(0,0,255);
        iText(10,650,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100,650,sscore,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(170,650,"High Score:",GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(highscore,"%d",ssscore[0]);
        iText(300,650,highscore,GLUT_BITMAP_TIMES_ROMAN_24);
    if(life==3){
        iShowBMP2(510,650,"images\\pdr3.bmp",0);
        iShowBMP2(540,650,"images\\pdr3.bmp",0);}


    if(life==2){
        iShowBMP2(540,650,"images\\pdr3.bmp",0);}

    if(pacvelpy)
        iShowBMP2(pacposx,pacposy,eatingpacpicsu[eatingpacpicsind],0 );
    if(pacvelnx)
        iShowBMP2(pacposx,pacposy,eatingpacpicsl[eatingpacpicsind],0 );
    if(pacvelny)
        iShowBMP2(pacposx,pacposy,eatingpacpicsd[eatingpacpicsind],0 );
    if(pacvelpx)
        iShowBMP2(pacposx,pacposy,eatingpacpicsr[eatingpacpicsind],0 );
  // iCircle(x,y,r,100);
    if(red.dpx)
    iShowBMP2(red.posx,red.posy,redghostfigure[0],0);
    if(red.dpy)
    iShowBMP2(red.posx,red.posy,redghostfigure[1],0);
    if(red.dnx)
    iShowBMP2(red.posx,red.posy,redghostfigure[2],0);
    if(red.dny)
    iShowBMP2(red.posx,red.posy,redghostfigure[3],0);
    if(cyan.dpx)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[0],0);
    if(cyan.dpy)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[1],0);
    if(cyan.dnx)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[2],0);
    if(cyan.dny)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[3],0);
//    iSetColor(255,69,0);
//        iFilledRectangle(orange.posx,orange.posy,30,30);
    if(orange.dpx)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[0],0);
    if(orange.dpy)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[1],0);
    if(orange.dnx)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[2],0);
    if(orange.dny)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[3],0);
    //
    if(pink.dpx)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[0],0);
    if(pink.dpy)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[1],0);
    if(pink.dnx)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[2],0);
    if(pink.dny)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[3],0);
    if(cherry.on){
    iShowBMP2(cherry.x*30,cherry.y*30,cherrys,0);
    }
    if(apple.on){
    iShowBMP2(apple.x*30,apple.y*30,apples,0);
    }
    if(banana.on){
    iShowBMP2(banana.x*30,banana.y*30,bananas,0);
    }
    if(strawberry.on){
    iShowBMP2(strawberry.x*30,strawberry.y*30,strawberrys,0);
    }
    if(key.on==1)
        iShowBMP2(key.x*30,key.y*30,"images\\key.bmp",0);
    if(candy.on==1)
        iShowBMP2(candy.x*30,candy.y*30,"images\\candy.bmp",0);
    if(help==1)
    {
         if(gameonmusic){
        if(soundon)
        PlaySound("pacman_beginning.wav",NULL,SND_ASYNC);
        gameonmusic=false;
        }
        iSetColor(69,69,69);
        iFilledRectangle(0,0,250,690);
        iSetColor(255,255,255);
        iText(2,600," >>INSTRUCTIONS<<",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(2,550,"->Your target is to eat all ");
        iText(2,530,"the dots & maximize your score.");
        iText(2,510,"->Each dot gives 10 points and");
        iText(2,490,"fruits,appear frequently, ");
        iText(2,470,"will give some bonus score");
        iText(2,450,"->Use arrows to move pacman!");
        iText(2,430,"->Ghost's speed will increase.");
        iText(2,410,"gradually.MOVE FASTER!");
        iText(2,390,"->At first You'll have only");
        iText(2,370,"3 life");
        iText(2,350,"THERE ARE SOME PERKS");
        iText(2,330,"KEY can freeze ghosts for");
        iText(2,310,"10 secs.You'r FREE! ");
        iText(2,290,"CANDY can increase your speed");
        iText(2,270,"for 10 secs.You'r FLASH! ");
        iText(2,140,"Press SPACE to PAUSE/RESUME");
        iText(2,120,"Pause anytime to see again");
        iText(2,100,"Press arrows to start...");
    }
}
    else if(pacdeathanimation){
    if(deathindex==0)
        PlaySound("pacman_death.wav",NULL,SND_ASYNC);
        iShowBMP(0,0,"images\\gmback.bmp");
    for(int i=0;i<21;i++){
        for(int j=0;j<19;j++){
            if(maze[i][j]==1){
                iSetColor (187, 0, 255);
                iFilledRectangle(j*30,i*30,30,30);
            }
            else if(maze[i][j]==0&&dots[i][j]==0){
                iSetColor(200,200,200);
                iFilledCircle(j*30+15,i*30+15,4);
            }
        }
    }
     if(soundon)
        iShowBMP2(400,650,"images\\soundon.bmp",1);
    else
        iShowBMP2(400,650,"images\\soundoff.bmp",1);
    iSetColor(0,0,255);
        iText(10,650,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100,650,sscore,GLUT_BITMAP_TIMES_ROMAN_24);
    if(life==3){
        iShowBMP2(510,650,"images\\pdr3.bmp",0);
        iShowBMP2(540,650,"images\\pdr3.bmp",0);}

    if(life==2){
        iShowBMP2(540,650,"images\\pdr3.bmp",0);}
    if(red.dpx)
    iShowBMP2(red.posx,red.posy,redghostfigure[0],0);
    if(red.dpy)
    iShowBMP2(red.posx,red.posy,redghostfigure[1],0);
    if(red.dnx)
    iShowBMP2(red.posx,red.posy,redghostfigure[2],0);
    if(red.dny)
    iShowBMP2(red.posx,red.posy,redghostfigure[3],0);
    if(cyan.dpx)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[0],0);
    if(cyan.dpy)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[1],0);
    if(cyan.dnx)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[2],0);
    if(cyan.dny)
    iShowBMP2(cyan.posx,cyan.posy,cyanghostfigure[3],0);
//    iSetColor(255,69,0);
//        iFilledRectangle(orange.posx,orange.posy,30,30);
    if(orange.dpx)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[0],0);
    if(orange.dpy)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[1],0);
    if(orange.dnx)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[2],0);
    if(orange.dny)
    iShowBMP2(orange.posx,orange.posy,orangeghostfigure[3],0);
    //
    if(pink.dpx)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[0],0);
    if(pink.dpy)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[1],0);
    if(pink.dnx)
        iShowBMP2(pink.posx,pink.posy,pinkghostfigure[2],0);
    if(pink.dny)gameoverscreen=1-gameoverscreen;
            mainmenu=1-mainmenu;
    iShowBMP2(pink.posx,pink.posy,pinkghostfigure[3],0);
        iShowBMP2(pacposx,pacposy,death[deathindex++],0 );
        Sleep(200);
        if(deathindex==6){
                deathindex=0;
        initializeghost();
        initializepac();
        life--;
        pacdeathanimation=0;
        gamescreen=1;
}
    }
    else if(mainmenu){
//        if(soundon)
//            PlaySound("main.wav",NULL,SND_ASYNC);
        iShowBMP2(0,0,"images\\ggwp.bmp",0);
        iShowBMP(160,515,"images\\Pacmanmain.bmp");
        iShowBMP2(100,300,"images\\start.bmp",0);
        iShowBMP2(100,250,"images\\halloffame.bmp",0);
        iShowBMP2(100,200,"images\\exit.bmp",0);
        iShowBMP2(200,470,"images\\pacmanname.bmp",0);
        if(soundon)
        iShowBMP2(500,100,"images\\soundon.bmp",0);
    else
        iShowBMP2(500,100,"images\\soundoff.bmp",0);
    }
    else if(scoremenu){
        iShowBMP2(0,0,"images\\ggwp.bmp",0);
        iShowBMP2(400,100,"images\\mainmenu.bmp",0);
         fp=fopen("highscores.txt","r");
         fp2=fopen("names.txt","r");
         int xx=600;
    while(1){
        fgets(highscore,sizeof(highscore),fp);
         iText(350,xx,highscore,GLUT_BITMAP_TIMES_ROMAN_24);
        if(feof(fp))
            break;
        xx-=50;
    }
    xx=600;
     while(1){
        fgets(highname,sizeof(highname),fp2);
        if(feof(fp2))
            break;
        iText(150,xx,highname,GLUT_BITMAP_TIMES_ROMAN_24);
        xx-=50;
    }
    fclose(fp);
    fclose(fp2);
    }
    else if(pausemenu){
        iShowBMP2(0,0,"images\\gmback.bmp",0);
        iShowBMP2(300,400,"images\\resume.bmp",0);
        iShowBMP2(300,350,"images\\mainmenu.bmp",0);
        iShowBMP2(300,300,"images\\exit.bmp",0);
        iSetColor(255,255,255);
        iText(2,600," >>INSTRUCTIONS<<",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(2,550,"->Your target is to eat all ");
        iText(2,530,"the dots & maximize your score.");
        iText(2,510,"->Each dot gives 10 points and");
        iText(2,490,"fruits,appear frequently, ");
        iText(2,470,"will give some bonus score");
        iText(2,450,"->Use arrows to move pacman!");
        iText(2,430,"->Ghost's speed will increase.");
        iText(2,410,"gradually.MOVE FASTER!");
        iText(2,390,"->At first You'll have only");
        iText(2,370,"3 life");
        iText(2,350,"THERE ARE SOME PERKS");
        iText(2,330,"KEY can freeze ghosts for");
        iText(2,310,"10 secs.You'r FREE! ");
        iText(2,290,"CANDY can increase your speed");
        iText(2,270,"for 10 secs.You'r FLASH! ");
        iText(2,140,"Press SPACE to PAUSE/RESUME");
       // iText(2,120,"Pause anytime to see again");
        //iText(2,100,"Press arrows to start...");
    }
    else if(gameoverscreen){
        iShowBMP(0,0,"images\\plaincolor.bmp");
        iShowBMP(0,370,"images\\killerghost.bmp");
        iSetColor(rand()%255,rand()%255,rand()%255);
        iText(200,300,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,255,0);
        iText(200,250,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(280,250,sscore,GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(200,200,"images\\mainmenu.bmp",0);
        iShowBMP2(200,150,"images\\exit.bmp",0);
        iSetColor(255,255,255);
        if(score>ssscore[9])
            iText(400,300,"New record");
        }
        else if(namescreen){
            iShowBMP2(0,0,"images\\gmback.bmp",0);
            iText(50,300,"Type your name and ENTER",GLUT_BITMAP_TIMES_ROMAN_24);
            drawTextBox();
        	if(mode == 1)
        	{
        		iSetColor(255, 255, 255);
        		iText(55, 260, str);
        	}

        iText(10, 10, "Click to activate the box, enter to finish.");
        }
}


void iMouseMove(int mx, int my)
{

}
void iMouse(int button, int state, int mx, int my)
{
    if(gameoverscreen){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    	{
    		//place your codes here
    		if(mx >= 50 && mx <= 300 && my >= 250 && my <= 280 && mode == 0)
    		{
    			mode = 1;
    		}
    	}
    	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    	{
    		//place your codes here
    	}
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mainmenu){
           // printf("x:%d y:%d\n",mx,my);
          //
            if(mx>=100&&mx<=180&&my>=300&&my<=325){
                    life=3;
                mainmenu=0;
                namescreen=1;
                if(soundon)
                PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
            }
            else if(mx>=100&&mx<=280&&my>=250&&my<=275){
                mainmenu=1-mainmenu;
                scoremenu=1-scoremenu;
                if(soundon)
                PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
            }
            else if(mx>=100&&mx<=150&&my>=200&&my<=225){
//                if(gamestarted){
//                    pacmanstartx=pacinitialposx;
//                    pacmanstarty=pacinitialposy;
//                    fpp=fopen("save_game.txt","w");
//                    fprintf(fpp,"%d ",gamestarted);
//                    fprintf(fpp,"%d %d %d %d %d %d %d %d %d %d %d ",pacmanstartx,pacmanstarty,pacinitialposx,pacinitialposy,pacposx,pacposy,pacvel,pacvelnx,pacvelpy,pacvelny,pacvelpx);
//                    fprintf(fpp,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",ghstvel,cyanvel,red.x,red.y,red.posx,red.posy,red.dpx,red.dpy,red.dnx,red.dny
//                            ,cyan.x,cyan.y,cyan.posx,cyan.posy,cyan.dpx,cyan.dnx,cyan.dny,cyan.dpy,orange.x,orange.y,orange.posx,orange.posy,orange.dpx,orange.dnx,
//                            orange.dny,orange.dpy,pink.x,pink.y,pink.posx,pink.posy,pink.dpx,pink.dnx,pink.dny,pink.dpy);
//                }
//                fclose(fpp);
                if(soundon)
                PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
                exit(0);
            }

            else if(mx>=500&&mx<=530&&my>=100&&my<=130){
                    soundon=1-soundon;
            }
        }
        else if(scoremenu){
            if(mx>=400&&mx<=556&&my>=100&&my<=123){
                scoremenu=0;
                mainmenu=1;
                if(soundon)
                PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
            }
        }
//        else if(gamescreen&&gameon==0){
//            if(mx>=0&&mx<=570&&my>=0&&my<=680){
//                gameon=1-gameon;
//                help++;
//            }
//        }
        else if(gameoverscreen){
                fp4=fopen("names.txt","r");
                    for(int i=0;i<10;i++)
                        fscanf(fp4,"%s",ssname[i]);
                fclose(fp4);
                highscore_check();
                fp4=fopen("names.txt","w");
                for(int i=0;i<10;i++){
                    fprintf(fp4,"%s\n",ssname[i]);
                }
                fclose(fp4);
                fp3=fopen("highscores.txt","w");
                fprintf(fp3,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",ssscore[0],ssscore[1],ssscore[2],ssscore[3],ssscore[4],ssscore[5],ssscore[6],ssscore[7],ssscore[8],ssscore[9]);
                fclose(fp3);
        if(mx>=200&&mx<=355&&my>=200&&my<=223){
            gameoverscreen=0;
            mainmenu=1;
            life=3;
            score=0;
            if(soundon)
            PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
        }
        if(mx>=200&&mx<=300&&my>=150&&my<=175){
            exit(0);
        }
    }
    else if(pausemenu){
        if(mx>=300&&mx<=380&&my>=400&&my<=423){
            gamescreen=1;
            gameon=0;
            pausemenu=0;
            if(soundon)
            PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
        }
        else if(mx>=300&&mx<=456&&my>=350&&my<=373){
           pausemenu=0;
           mainmenu=1;
           if(soundon)
           PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
        }
        else if(mx>=300&&mx<=350&&my>=300&&my<=323){
            exit(0);
        }
    }
    else if(namescreen){
         if(mx>=100&&mx<=180&&my>=300&&my<=325){
                mainmenu=0;
                 ghstvel=1;
                 cyanvel=1;
                 initializeperks();
                 initializeghost();
                initializepac();
                initializefruits();
                initializedots();
                help=1;
                score=0;
                strcpy(sscore,"0");
                timee=0;
                namescreen=0;
                gamescreen=1;
                targetscore=750;
                if(soundon)
                PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
                }
            else if(mx >= 50 && mx <= 300 && my >= 250 && my <= 280 && mode == 0)
		{
			mode = 1;
		}
    }
    else if(gamescreen){
        if(mx>=400&&mx<=430&&my>=650&&my<=680){
            soundon=1-soundon;
            if(soundon)
            PlaySound("Menu-Button-Press-E-www.fesliyanstudios.com.wav",NULL,SND_ASYNC);
        }
    }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}

void iKeyboard(unsigned char key)
{
    //place your codes for other keys here
    if(key=='p')
        iPauseTimer(0);
    if(key=='o')
        iResumeTimer(0);
    if(key==' '&&gamescreen){
        gameon=0;
        pausemenu=1;
        gamescreen=0;
    }
     else if(key==' '&&pausemenu&&!gamescreen){
        gameon=0;
        pausemenu=0;
        gamescreen=1;
    }
    if(namescreen){
    int i;
	if(mode == 1)
	{
        if(key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			strcpy(name,str2);
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
            mainmenu=0;
                 ghstvel=1;
                 cyanvel=1;
                 initializeperks();
                 initializeghost();
                initializepac();
                initializefruits();
                life=3;
                initializedots();
                help=1;
                score=0;
                strcpy(sscore,"0");
                timee=0;
                namescreen=0;
                gamescreen=1;
                targetscore=750;
                gameonmusic=true;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}}
}

/*
             function iSpecialKeyboard() is called whenver user hits special keys like-
             function keys, home, end, pg up, pg down, arraows etc. you have to use
             appropriate constants to detect them. A list is:
             GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
             GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
             GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
             GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if(gameon){
    if(key ==GLUT_KEY_UP){
        if(pacvelpy){
          //  upx=pacinitialposx,upy=pacinitialposy+1;}
            pacvelpy=pacvel;pacvelny=0;pacvelpx=0;pacvelnx=0;}
        else if(pacvelny){
            pacvelpy=pacvel;pacvelny=0;pacvelpx=0;pacvelnx=0;}
         //  upx=pacinitialposx,upy=pacinitialposy-1;}
        else if(pacvelpx){
            for(int i=pacinitialposx;maze[pacinitialposy][i]!=1;i++){
                if(maze[pacinitialposy+1][i]==0){
                    upx=i;
                    upy=pacinitialposy;
                    break;}
            }
        }
        else if(pacvelnx){
            for(int i=pacinitialposx;maze[pacinitialposy][i]!=1;i--){
                if(maze[pacinitialposy+1][i]==0){
                    upx=i;
                    upy=pacinitialposy;
                    break;}
            }
        }
    }
    if(key==GLUT_KEY_DOWN){
        if(pacvelpy){
            pacvelpy=0;pacvelny=pacvel;pacvelpx=0;pacvelnx=0;}
           // downx=pacinitialposx,downy=pacinitialposy+1;}
        else if(pacvelny){
            pacvelpy=0;pacvelny=pacvel;pacvelpx=0;pacvelnx=0;}
           // downx=pacinitialposx,downy=pacinitialposy-1;}
        else if(pacvelpx){
            for(int i=pacinitialposx;maze[pacinitialposy][i]!=1;i++){
                if(maze[pacinitialposy-1][i]==0){
                    downx=i;
                    downy=pacinitialposy;
                    break;}
            }
        }
        else if(pacvelnx){
            for(int i=pacinitialposx;maze[pacinitialposy][i]!=1;i--){
                if(maze[pacinitialposy-1][i]==0){
                    downx=i;
                    downy=pacinitialposy;
                    break;}
            }
        }
    }
    if(key==GLUT_KEY_RIGHT){
        if(pacvelpx){
            pacvelpy=0;pacvelny=0;pacvelpx=pacvel;pacvelnx=0;}
        else if(pacvelnx){
            pacvelpy=0;pacvelny=0;pacvelpx=pacvel;pacvelnx=0;}
        else if(pacvelpy){
            for(int i=pacinitialposy;maze[i][pacinitialposx]!=1;i++){
                    printf("%d\n",maze[i][pacinitialposx+1]);
                if(maze[i][pacinitialposx+1]==0){
                    rightx=pacinitialposx;
                    righty=i;
                    break;}
            }
        }
        else if(pacvelny){
            for(int i=pacinitialposy;maze[i][pacinitialposx]!=1;i--){
                if(maze[i][pacinitialposx+1]==0){
                    rightx=pacinitialposx;
                    righty=i;
                   // break;
                  //  printf("%d %d\n",upx,upy);
                        break;
            }
        }
    }}
if(key==GLUT_KEY_LEFT){
    if(pacvelpx){
            pacvelpy=0;pacvelny=0;pacvelpx=0;pacvelnx=pacvel;}
        else if(pacvelnx){
            pacvelpy=0;pacvelny=0;pacvelpx=0;pacvelnx=pacvel;}
        else if(pacvelpy){
            for(int i=pacinitialposy;maze[i][pacinitialposx]!=1;i++){
                   // printf("%d\n",maze[i][pacinitialposx-1]);
                if(maze[i][pacinitialposx-1]==0){
                    leftx=pacinitialposx;
                    lefty=i;
                    break;}
            }
        }
        else if(pacvelny){
            for(int i=pacinitialposy;maze[i][pacinitialposx]!=1;i--){
                if(maze[i][pacinitialposx-1]==0){
                    leftx=pacinitialposx;
                    lefty=i;
                    break;
            }
        }
    }
    }}
    else if(gamescreen&&gameon==0){
            if(key==GLUT_KEY_LEFT||key==GLUT_KEY_RIGHT||key ==GLUT_KEY_UP||key==GLUT_KEY_DOWN){
                gameon=1-gameon;
                help++;
            }
        }
}

void gameengine(){
    if(score==2490){
        gamescreen=0;
        gameon=0;
        gameoverscreen=1;
    }
    if(life==0){
        gameoverscreen=1;
        gameon=0;
        gamescreen=0;
    }
    if(gameon){
    collitioncheck();
    if(pacinitialposx==18&&pacinitialposy==11&&pacvelpx){
        pacposx=0;pacinitialposx=0;}
    if(pacinitialposx==0&&pacinitialposy==11&&pacvelnx){
        pacposx=18*30;pacinitialposx=18;}
    if(pacposx%30==0&&pacposy%30==0&&dots[pacinitialposy][pacinitialposx]==0){
        dots[pacinitialposy][pacinitialposx]=1;
        score+=10;
        sprintf(sscore,"%d\n",score);
         if(soundon)
        PlaySound("pacman_chomp.wav",NULL,SND_ASYNC);
    }
    if(key.started==0){
    if(chasemode){
    redchase();
    orangechase();
    cyanchase();
    pinkchase();}
    else if(scattermode){
        scatter(17,19,&red.x,&red.y,&red.posx,&red.posy,&red.dpx,&red.dnx,&red.dpy,&red.dny);
        scatter(17,1,&pink.x,&pink.y,&pink.posx,&pink.posy,&pink.dpx,&pink.dnx,&pink.dpy,&pink.dny);
        scatter(1,19,&cyan.x,&cyan.y,&cyan.posx,&cyan.posy,&cyan.dpx,&cyan.dnx,&cyan.dpy,&cyan.dny);
         scatter(1,1,&orange.x,&orange.y,&orange.posx,&orange.posy,&orange.dpx,&orange.dnx,&orange.dpy,&orange.dny);
    }}

    if(pacinitialposx==18&&pacinitialposy==11&&pacvelpx){
        pacposx=0;pacinitialposx=0;}
    if(pacinitialposx==0&&pacinitialposy==11&&pacvelnx){
        pacposx=18*30;pacinitialposx=18;}
    if(timee==tt&&score<=2000){
        chasemode=1-chasemode;
        scattermode=1-scattermode;
        timee=0;
        if(tt==7)
            tt=20;
        else
            tt=7;
    }
    else if(score>2000)
        chasemode=1;
    if(key.on==0&&score>=key.when){
        key.on=1;
    }
    if(key.on==1&&key.x==pacinitialposx&&key.y==pacinitialposy){
        key.started=1;
        key.on=2;
        key.currentlife=life;//pacman_eatfruit
         if(soundon)
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);
    }
    if(key.started==1&&(key.time>=key.howmuch||key.currentlife!=life)){
        key.started=0;
        key.time=0;

        }
    if(candy.on==0&&score>=candy.when){
        candy.on=1;
    }
    if(candy.on==1&&candy.x==pacinitialposx&&candy.y==pacinitialposy){
        candy.started=1;
        pacvel++;
        candy.on=2;
        candy.currentlife=life;
        key.time=0;
        if(soundon)
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);
    }
    if(candy.started==1&&(candy.time>=candy.howmuch||candy.currentlife!=life)){
        candy.started=0;
        pacvel=2;}
    if(score>=targetscore){
        cyanvel=2;
        ghstvel=2;
        targetscore+=7000;
    }
    if(upx==pacinitialposx&&upy==pacinitialposy&&pacposx%30==0){
        pacvelpy=pacvel;
        pacvelnx=0;
        pacvelny=0;
        pacvelpx=0;
        upx=0;
        upy=0;
    }
        if(downx==pacinitialposx&&downy==pacinitialposy&&pacposx%30==0){
        pacvelpy=0;
        pacvelnx=0;
        pacvelny=pacvel;
        pacvelpx=0;
        downx=0;
        downy=0;
    }
        if(rightx==pacinitialposx&&righty==pacinitialposy&&pacposy%30==0){
        pacvelpy=0;
        pacvelnx=0;
        pacvelny=0;
        pacvelpx=pacvel;
        rightx=0;
        righty=0;
    }
    if(leftx==pacinitialposx&&lefty==pacinitialposy&&pacposy%30==0){
        pacvelpy=0;
        pacvelnx=pacvel;
        pacvelny=0;
        pacvelpx=0;
        leftx=0;
        lefty=0;
    }
    if(pacvelnx>0&&maze[pacinitialposy][pacinitialposx-1]==0){
      pacposx-=pacvelnx;
      if((pacposx)%30==0)
        pacinitialposx=((pacposx)/30);
    }
    else if(pacvelpx>0&&maze[pacinitialposy][pacinitialposx+1]==0){
        pacposx+=pacvelpx;
        if((pacposx)%30==0)
            pacinitialposx=((pacposx)/30);
    }
    else if(pacvelpy>0&&maze[pacinitialposy+1][pacinitialposx]==0){
        pacposy+=pacvelpy;
        if((pacposy)%30==0)
            pacinitialposy=((pacposy)/30);
    }
    else if(pacvelny>0&&maze[pacinitialposy-1][pacinitialposx]==0){
        pacposy-=pacvelny;
        if((pacposy)%30==0)
            pacinitialposy=((pacposy)/30);
    }
    else if(pacposx%30||pacposy%30){
        pacposx+=pacvelpx;
        pacposx-=pacvelnx;
        pacposy+=pacvelpy;
        pacposy-=pacvelny;
    }
    }
    if(score>cherry.when&&!cherry.flag&&score<=apple.when){
        cherry.on=1;
    }
    if(cherry.on&&cherry.x==pacinitialposx&&cherry.y==pacinitialposy&&!cherry.flag2){
        score+=cherry.points;
        cherry.on=0;
        cherry.flag=1;
        cherry.flag2=1;
         if(soundon)
        PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
    }
    if(score>strawberry.when&&!strawberry.flag){
        strawberry.on=1;
    }
    if(strawberry.on&&strawberry.x==pacinitialposx&&strawberry.y==pacinitialposy&&!strawberry.flag2){
        score+=strawberry.points;
        strawberry.on=0;
        strawberry.flag=1;
        strawberry.flag2=1;
         if(soundon)
        PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
    }
    if(score>banana.when&&!banana.flag){
        banana.on=1;
    }
    if(banana.on&&banana.x==pacinitialposx&&banana.y==pacinitialposy&&!banana.flag2){
        score+=banana.points;
        banana.on=0;
        banana.flag=1;
        banana.flag2=1;
         if(soundon)
        PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
    }
    if(score>apple.when&&!apple.flag){
        apple.on=1;
    }
    if(apple.on&&apple.x==pacinitialposx&&apple.y==pacinitialposy&&!apple.flag2){
        score+=apple.points;
        apple.on=0;
        apple.flag=1;
        apple.flag2=1;
         if(soundon)
        PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
    }

}
void eateranimation(){
    eatingpacpicsind++;
    if(eatingpacpicsind==3)
        eatingpacpicsind=0;
    //printf("y=%d x=%d \n",pacinitialposy,pacinitialposx);
    //printf("px= %d nx=%d py=%d ny=%d\n",pacvelpx,pacvelnx,pacvelpy,pacvelny);
}

void timechange(){
    if(gameon)
        timee+=1;
    if(key.started&&gameon)
        key.time++;
    if(candy.started&&gameon)
       candy.time++;
    printf("%d\n",key.time);
}
int main(){
    iSetTimer(1000,timechange);
    len = 0;
	mode = 0;
	str[0]= 0;
    fp3=fopen("highscores.txt","r");
    fscanf(fp3,"%d%d%d%d%d%d%d%d%d%d",&ssscore[0],&ssscore[1],&ssscore[2],&ssscore[3],&ssscore[4],&ssscore[5],&ssscore[6],&ssscore[7],&ssscore[8],&ssscore[9]);
    fclose(fp3);
    iSetTimer(5,gameengine);
    iSetTimer(300,eateranimation);
    iInitialize(570,680, "Pacman!");
    return 0;
}
void collitioncheck(){
    if((pacinitialposx==red.x&&pacinitialposy==red.y)||(pacinitialposx==cyan.x&&pacinitialposy==cyan.y)||(pacinitialposx==orange.x&&pacinitialposy==orange.y)||
       (pacinitialposx==pink.x&&pacinitialposy==pink.y)){
        gameon=0;
        pacdeathanimation=1;
        gamescreen=0;
    }
}

void scatter(int targetx,int targety,int *posx,int *posy,int *x,int *y,int *velpx,int *velnx,int *velpy,int *velny){
    if(*posx==0&&*posy==11&&*velnx){
        *x=18*30;*posx=18;}
    if(*posx==18&&*posy==11&&*velpx){
        *x=0;*posx=0;}
    *x+=*velpx;
    *x-=*velnx;
    *y+=*velpy;
    *y-=*velny;
    if(*x%30==0)
        *posx=*x/30;
    if(*y%30==0)
        *posy=*y/30;
    int tmp1=INT_MAX,tmp2=INT_MAX,tmp3=INT_MAX;
    if((*velnx||*velpx)&&maze[*posy-1][*posx]==1&&maze[*posy+1][*posx]==1&&*x%30==0&&*y%30==0){

    }
    	else if(*velnx&&*x%30==0&&*y%30==0){
        if(maze[*posy][*posx-1]==0){
            tmp1=pow(*posy-targety,2)+pow(*posx-1-targetx,2);
        }
         if(maze[*posy-1][*posx]==0){
            tmp2=pow(*posy-1-targety,2)+pow(*posx-targetx,2);
        }
         if(maze[*posy+1][*posx]==0){
            tmp3=pow(*posy+1-targety,2)+pow(*posx-targetx,2);
        }
        //int tmp=std::min(std::min(tmp1,tmp2),tmp3);
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            *velnx=0;
            *velny=ghstvel;
            *velpx=0;
            *velpy=0;
        }
        else if(tmp==tmp3&&*x%30==0&&*y%30==0){
            *velnx=0;
            *velny=0;
            *velpx=0;
            *velpy=ghstvel;
        }
    }
    else if(*velpx&&red.posx%30==0&&red.posy%30==0){
        if(maze[*posy][*posx+1]==0){
            tmp1=pow(*posy-targety,2)+pow(*posx+1-targetx,2);
        }
         if(maze[*posy-1][*posx]==0){
            tmp2=pow(*posy-1-targety,2)+pow(*posx-targetx,2);
        }
         if(maze[*posy+1][*posx]==0){
            tmp3=pow(*posy+1-targety,2)+pow(*posx-targetx,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            *velnx=0;
            *velny=ghstvel;
            *velpx=0;
            *velpy=0;
        }
        else if(tmp==tmp3){
            *velnx=0;
            *velny=0;
            *velpx=0;
            *velpy=ghstvel;
        }
    }
    else if(*velpy&&*x%30==0&&*y%30==0){
        if(maze[*posy+1][*posx]==0){
            tmp1=pow(*posy+1-targety,2)+pow(*posx-targetx,2);
        }
         if(maze[*posy][*posx+1]==0){
            tmp2=pow(*posy-targety,2)+pow(*posx+1-targetx,2);
        }
         if(maze[*posy][*posx-1]==0){
            tmp3=pow(*posy-targety,2)+pow(*posx-1-targetx,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            *velnx=0;
            *velny=0;
            *velpx=ghstvel;
            *velpy=0;
        }
        else if(tmp==tmp3){
            *velnx=ghstvel;
            *velny=0;
            *velpx=0;
            *velpy=0;
        }
    }
    else if(*velny&&*x%30==0&&*y%30==0){
        if(maze[*posy-1][*posx]==0){
            tmp1=pow(*posy-1-targety,2)+pow(*posx-targetx,2);
        }
         if(maze[*posy][*posx+1]==0){
            tmp2=pow(*posy-targety,2)+pow(*posx+1-targetx,2);
        }
         if(maze[*posy][*posx-1]==0){
            tmp3=pow(*posy-targety,2)+pow(*posx-1-targetx,2);
        }
        int tmp=(tmp1<=tmp2?tmp1:tmp2)<=tmp3?(tmp1<=tmp2?tmp1:tmp2):tmp3;
        if(tmp==tmp2){
            *velnx=0;
            *velny=0;
            *velpx=ghstvel;
            *velpy=0;
        }
        else if(tmp==tmp3){
            *velnx=ghstvel;
            *velny=0;
            *velpx=0;
            *velpy=0;
        }
    }
}
void initializedots(){
    for(int i=0;i<21;i++){
        for(int j=0;j<19;j++){
            dots[i][j]=0;
        }
    }
    dots[13][0]=1;dots[13][1]=1;dots[13][2]=1;dots[9][0]=1;dots[9][1]=1;dots[9][2]=1;dots[13][18]=1;dots[13][17]=1;dots[13][16]=1;dots[9][16]=1;dots[9][17]=1;dots[9][18]=1;
    for(int i=5;i<=13;i++){
        for(int j=14;j>7;j--){
        dots[j][i]=1;
        dots[j][i]=1;
        }
    }
}
void highscore_check(){
//    for(int i=0;i<10;i++){
//        if(i==0){
//        if(score>ssscore[i]){
//            for(int j=9;j>i;j++){
//                ssscore[j]=ssscore[j-1];
//                strcpy(ssname[j],name);
//            }
//            ssscore[i]=score;
//        }}
//        else{
//            if(score>ssscore[i]&&score<ssscore[i-1]){
//            for(int j=9;j>i;j++){
//                ssscore[j]=ssscore[j-1];
//                strcpy(ssname[j],name);
//            }
//            ssscore[i]=score;
//        }
//        }
//    }
    if(score>ssscore[0]){
            ssscore[9]=ssscore[8];
            strcpy(ssname[9],ssname[8]);
            ssscore[8]=ssscore[7];
            strcpy(ssname[8],ssname[7]);
            ssscore[7]=ssscore[6];
            strcpy(ssname[7],ssname[6]);
            ssscore[6]=ssscore[5];
            strcpy(ssname[6],ssname[5]);
            ssscore[5]=ssscore[4];
            strcpy(ssname[5],ssname[4]);
            ssscore[4]=ssscore[3];
            strcpy(ssname[4],ssname[3]);
            ssscore[3]=ssscore[2];
            strcpy(ssname[3],ssname[2]);
        ssscore[2]=ssscore[1];
        strcpy(ssname[2],ssname[1]);
        ssscore[1]=ssscore[0];
        strcpy(ssname[1],ssname[0]);
        ssscore[0]=score;
        strcpy(ssname[0],name);
    }
     else if(score>ssscore[1]&&score<=ssscore[0]){
        ssscore[9]=ssscore[8];strcpy(ssname[9],ssname[8]);
        ssscore[8]=ssscore[7];strcpy(ssname[8],ssname[7]);
        ssscore[7]=ssscore[6];strcpy(ssname[7],ssname[6]);
        ssscore[6]=ssscore[5];strcpy(ssname[6],ssname[5]);
        ssscore[5]=ssscore[4];strcpy(ssname[5],ssname[4]);
        ssscore[4]=ssscore[3];strcpy(ssname[4],ssname[3]);
        ssscore[3]=ssscore[2];strcpy(ssname[3],ssname[2]);
        ssscore[2]=ssscore[1];strcpy(ssname[2],ssname[1]);
        ssscore[1]=score;strcpy(ssname[1],name);
    }
    else if(score>ssscore[2]&&score<=ssscore[1]){
         ssscore[9]=ssscore[8];
            ssscore[8]=ssscore[7];
            ssscore[7]=ssscore[6];
            ssscore[6]=ssscore[5];
            ssscore[5]=ssscore[4];
            ssscore[4]=ssscore[3];
            ssscore[3]=ssscore[2];
            ssscore[2]=score;
        strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],ssname[6]);
        strcpy(ssname[6],ssname[5]);
        strcpy(ssname[5],ssname[4]);
        strcpy(ssname[4],ssname[3]);
        strcpy(ssname[3],ssname[2]);
        strcpy(ssname[2],name);

    }
    else if(score>ssscore[3]&&score<=ssscore[2]){
            ssscore[9]=ssscore[8];
            ssscore[8]=ssscore[7];
            ssscore[7]=ssscore[6];
            ssscore[6]=ssscore[5];
            ssscore[5]=ssscore[4];
            ssscore[4]=ssscore[3];
            ssscore[3]=score;
            strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],ssname[6]);
        strcpy(ssname[6],ssname[5]);
        strcpy(ssname[5],ssname[4]);
        strcpy(ssname[4],ssname[3]);
        strcpy(ssname[3],name);
    }
    else if(score>ssscore[4]&&score<=ssscore[3]){
         ssscore[9]=ssscore[8];
            ssscore[8]=ssscore[7];
            ssscore[7]=ssscore[6];
            ssscore[6]=ssscore[5];
            ssscore[5]=ssscore[4];
            ssscore[4]=score;
            strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],ssname[6]);
        strcpy(ssname[6],ssname[5]);
        strcpy(ssname[5],ssname[4]);
        strcpy(ssname[4],name);

    }
    else if(score>ssscore[5]&&score<=ssscore[4]){
         ssscore[9]=ssscore[8];
            ssscore[8]=ssscore[7];
            ssscore[7]=ssscore[6];
            ssscore[6]=ssscore[5];
            ssscore[5]=score;
            strcpy(ssname[9],ssname[8]);
            strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],ssname[6]);
        strcpy(ssname[6],ssname[5]);
        strcpy(ssname[5],name);

    }
    else if(score>ssscore[6]&&score<=ssscore[5]){
        ssscore[9]=ssscore[8];
        ssscore[8]=ssscore[7];
        ssscore[7]=ssscore[6];
        ssscore[6]=score;
        strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],ssname[6]);
        strcpy(ssname[6],name);
    }
    else if(score>ssscore[7]&&score<=ssscore[6]){
         ssscore[9]=ssscore[8];
            ssscore[8]=ssscore[7];
        ssscore[7]=score;
        strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],ssname[7]);
        strcpy(ssname[7],name);

    }
    else if(score>ssscore[8]&&score<=ssscore[7]){
         ssscore[9]=ssscore[8];
        ssscore[8]=score;
        strcpy(ssname[9],ssname[8]);
        strcpy(ssname[8],name);
    }
  else if(score>ssscore[9]&&score<=ssscore[8]){
         ssscore[9]=score;
          strcpy(ssname[9],name);
    }
}
