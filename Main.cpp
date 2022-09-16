#include <windows.h>#include <iostream>
int WIDTH=120;int HEIGHT=20;struct Entity {    int x, y, length;    char character;    bool loss=false;    Entity(int tx, int ty, int tlength, char charact) : x(tx), y(ty), length(tlength), character(charact)  {}    static void addEntity(char* array, Entity e) {        for(int i=e.y; i<e.y+e.length; i++) {            array[(i-(e.length/2))*WIDTH+e.x]=e.character;        }    }};void clear(char* disp) {    for(int i=0; i<120*20; i++) {        disp[i] = ' ';    }    disp[0]='+';
    disp[119]='+';
    disp[19*120]='+';
    disp[19*120+119]='+';    for(int i=1; i<119; i++) {        disp[i] = '-';
        disp[19*120+i] = '-';    }    for(int i=1; i<19; i++) {        disp[i*120] = '|';
        disp[i*120+119] = '|';    }}int main() {    char screen[120*20] = {' '};    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;    Entity paddle_left(1, 10, 5, '|');
    Entity paddle_right(118, 10, 5, '|');
    Entity ball(60, 10, 1, 'O');    int deltaX=1, deltaY=1;    bool loss=false;    while(!loss) {        if(GetAsyncKeyState(0x26)&&paddle_right.y-(paddle_right.length/2)>1) {paddle_right.y--;}
        if(GetAsyncKeyState(0x28)&&paddle_right.y+(paddle_right.length/2)<18) {paddle_right.y++;}
        if(GetAsyncKeyState(0x57)&&paddle_left.y-(paddle_left.length/2)>1) {paddle_left.y--;}
        if(GetAsyncKeyState(0x53)&&paddle_left.y+(paddle_left.length/2)<18) {paddle_left.y++;}        ball.x+=deltaX;        ball.y+=deltaY;        if(ball.x==1||ball.x==118) {            if((ball.y<paddle_right.y+(paddle_right.length/2)&&ball.y>paddle_right.y-(paddle_right.length/2))||(ball.y<paddle_left.y+(paddle_left.length/2)&&ball.y>paddle_left.y-(paddle_left.length/2))) {                deltaX*=-1;            }            else {                if(ball.x==1) {paddle_left.loss=true;}                else if(ball.x==118) {paddle_right.loss=true;}                loss=true;            }        }        else {Entity::addEntity(&screen[0], ball);}        if(ball.y==1) {deltaY*=-1;}
        if(ball.y==18) {deltaY*=-1;}        Entity::addEntity(&screen[0], paddle_left);
        Entity::addEntity(&screen[0], paddle_right);
        WriteConsoleOutputCharacterA(hConsole, screen, 120*20, { 0,0 }, &dwBytesWritten);        clear(&screen[0]);        Sleep(50);    }    clear(&screen[0]);    if(paddle_right.loss) {        std::string str = "Left Won Feels GoodRight Lost Feels Bad";        for(int i=10, mod=0; i<10+str.length(); i++) {
            if(i==29) {mod=61;}
            screen[120*10+i+mod] = str[i-10];
        }
    }    else if(paddle_left.loss) {        std::string str = "Left Lost Feels BadRight Won Feels Good";        for(int i=10, mod=0; i<10+str.length(); i++) {            if(i==29) {mod=61;}            screen[120*10+i+mod] = str[i-10];        }    }    WriteConsoleOutputCharacterA(hConsole, screen, 120*20, { 0,0 }, &dwBytesWritten);
    while(!GetAsyncKeyState(0x0D)) {}}