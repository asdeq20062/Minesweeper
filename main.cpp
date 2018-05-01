#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

void SetColor(int color){
HANDLE hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole,color);
}
char map1[9][9];
char map_hide[9][9]={
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'},
{'#','#','#','#','#','#','#','#','#'}};
bool gameover=false;
bool gamewin=false;



int bomb_count(int i,int j){
    int c=0;
    if (j+1<9 && map1[i][j+1]=='@'){ //Right
        c++;
    }
    if (j-1>-1 &&map1[i][j-1]=='@'){ //Left
        c++;
    }
    if (i-1>-1 &&map1[i-1][j]=='@'){ //Up
        c++;
    }
    if (i+1<9 &&map1[i+1][j]=='@'){ //Down
        c++;
    }
    if (i-1>-1 && j-1>-1 &&map1[i-1][j-1]=='@'){ //Up left
        c++;
    }
    if (i-1>-1&& j+1<9 &&map1[i-1][j+1]=='@'){ //Up right
        c++;
    }
    if (i+1<9 && j-1>-1 &&map1[i+1][j-1]=='@'){ //Down left
        c++;
    }
    if (i+1<9 && j+1<9 &&map1[i+1][j+1]=='@'){ //Down right
        c++;
    }
    char b =(char)(c+48);
    if(b=='0')
        b='-';
    return b;
}

void initial(){
    for(int i=0;i<10;i++){ //initial hidden map
        for (int j=0;j<10;j++){
            map_hide[i][j]='#';
        }
    }
    for (int i=1;i<=10;i++){ //Location of bomb
        int ran1=rand()%10;
        int ran2=rand()%10;
        if (map1[ran1][ran2]!='@')
            map1[ran1][ran2]='@';
        else
            i--;
    }
    for (int x=0;x<10;x++){ //Location of number
        for(int y=0;y<10;y++){
            if (map1[x][y]!='@'){
                map1[x][y]=bomb_count(x,y);
            }
        }
    }
}

void spread(int x, int y){
    if (map_hide[x][y]=='-')
        return;
    if (map1[x][y]=='-' && x>=0 && x<9 && y<9 && y>=0){
        map_hide[x][y]=map1[x][y];
        spread(x-1,y); //up
        spread(x+1,y); //down
        spread(x,y+1); //right
        spread(x,y-1); //left
        }
    else if (map1[x][y]!='-' && x>=0 && x<9 && y<9 && y>=0){
        map_hide[x][y]=map1[x][y];
        }
    }


void draw(int x, int y){
    SetColor(12);
    cout<<"   1 2 3 4 5 6 7 8 9"<<endl;
    SetColor(10);
    for(int a=0;a<9;a++){  //hidden map
        SetColor(12);
        cout<<a+1<<" ";
        SetColor(10);
        for(int b=0;b<9;b++){
            if(a==x&&b==y){
                map_hide[a][b]=map1[a][b];
                SetColor(12);
                cout<<"|";
                SetColor(10);
                cout<<map_hide[a][b];
            }
            else{
                SetColor(12);
                cout<<"|";
                SetColor(10);
                cout<<map_hide[a][b];
            }
        }
        SetColor(12);
        cout<<"| "<<a+1<<endl;
        cout<<"  -------------------"<<endl;
        SetColor(10);
    }
    SetColor(12);
    cout<<"   1 2 3 4 5 6 7 8 9"<<endl;
    SetColor(10);
//    for(int a=0;a<9;a++){  //real map for test
//        for(int b=0;b<9;b++){
//            cout<<map1[a][b];
//        }
//       cout<<endl;
//    }
}

void if_gameover(int x, int y){
    if(map1[x][y]=='@'){
        gameover=true;
        cout<<"Game Over!"<<endl;
        system("pause");
    }
}
void win(){
    int left_num=0;
    int bomb_num=0;
    for (int x=0; x<9; x++){
        for (int y=0; y<9; y++){
            if(map_hide[x][y]=='#')
                left_num++;
            if(map_hide[x][y]=='@')
                bomb_num++;
        }
    }
    if(left_num<=10 && bomb_num==0){
        gamewin=true;
        cout<<"You win the game!"<<endl;
        system("pause");
        }
}

int main()
{
    system("title ½ò¦a¹p");
    //system("color 71");
    srand(time(0));
    int x=-1;
    int y=-1;
    initial();
    while(!gameover && !gamewin){
        system("cls");
        draw(x-1,y-1);
        if_gameover(x-1,y-1);
        win();
        if (gameover==false&&gamewin==false){
            cout<<"Please input the y coordinate: "<<endl;
            cin>>x;
            cout<<"Please input the x coordinate: "<<endl;
            cin>>y;
            spread(x-1,y-1);
        }
    }
    return 0;
}
