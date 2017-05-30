#include <graphics.h>
#include "Pawn.h"
using namespace std;

//This method accepts the origin of the mouse x1, y1
//and the origin of the square x2, y2
//var field indicates the space that the enemy inhabits:
//x-f, y-f   x+f,y-f|
//                  |
//      x,y         |
//                  |
//x-f, y+f   x+f,y-f|
//This method returns true if x1,y1 is inside the 'field'
bool checkCollision(int x1, int y1, int x2, int y2, int half_length){

   // int field = 70;
    if(x1 > x2 - half_length && x1 < x2 + half_length){
        if(y1 > y2 - half_length && y1 < y2 + half_length){
            return true;
        }
    }

    return false;
}

class Square{
    private:
        int x, y, half_length, color;
    public:
        Square(){};
        Square(int x, int y, int half_length, int color){
            this->x = x;
            this->y = y;
            this->half_length = half_length;
            this->color = color;
        }

        void draw(){
            int sqr[] = {

                            x - half_length, y - half_length,
                            x - half_length, y + half_length,
                            x + half_length, y + half_length,
                            x + half_length, y - half_length

            };

            setcolor(color);
            setfillstyle(1, color);
            fillpoly(4, sqr);
        }

        int getX(){
            return x;
        }

        int getY(){
            return y;
        }
};
/*
class Board{
    private:
        int x, y;
        WSquare *w;
        BSquare *b;

    public:
        Board(){
            this->w = new WSquare(x,y);
            this->b = new BSquare(x,y);
        }

        void draw(){
           // line(100,50,100,450);
           // line(100,50,500,50);
        }
}*/

class Board{
    private:
        int x, y;
        int square_length;

    public:
        Square *square[8][8];

        Board(int x, int y){
//            this->w = new WSquare(x,y);
//            this->b = new BSquare(x,y);

        }

        Board(int square_length){

            this->square_length = square_length;

        }

        Board(){};

        void draw(){
            int counterX = 0;
            int counterY = 0;
            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(counterX%2 == 0)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(222,184,135));
                    else if(counterX%2 == 1)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(139,69,19));

                    square[x][y]->draw();
                    counterX++;
                }
                counterY++;
                if(counterY%2 == 0)
                    counterX = 0;
                else
                    counterX = 1;
            }
        }
};

int main(){

    //if you're running on a smaller resolution monitor,
    //change to 1366 x 768
    static const int X_RES = 1920;
    static const int Y_RES = 1080;

    initwindow(X_RES, Y_RES, "Space Invader");

    static const int BOARD_SIZE = getmaxx()/50;


    Board *b = new Board(BOARD_SIZE);
    b->draw();
    int x, y;
    Pawn *p = new Pawn(BOARD_SIZE*2, BOARD_SIZE*2, BOARD_SIZE, WHITE);
    p->draw();

    bool clicking = false;

    int page = 0;
    while(true){

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        b->draw();
        p->draw();

        if(!clicking){
            if(ismouseclick(WM_LBUTTONDOWN)){

                if(checkCollision(mousex(), mousey(), p->getX(), p->getY(), BOARD_SIZE)){
                    clicking = true;
                }

                clearmouseclick(WM_LBUTTONDOWN);


            }
        }

        if(clicking){

            p->translate(mousex(),mousey());
            if(ismouseclick(WM_LBUTTONDOWN)){
                /*if(checkCollision(mousex(), mousey(), mousex(), mousey(), BOARD_SIZE)){
                    clicking = false;
                }
                clicking = false;*/
                for(int y = 0; y < 8; y++){
                    for(int x = 0; x < 8; x++){
                        if(checkCollision(b->square[x][y]->getX(), b->square[x][y]->getY(), mousex(), mousey(), BOARD_SIZE)){
                            p->translate(b->square[x][y]->getX(),b->square[x][y]->getY());
                            clicking = false;
                        }
                    }
                }
            }

            clearmouseclick(WM_LBUTTONDOWN);


        }

        page = 1 - page;
        delay(24);

    }

//    while (!ismouseclick(WM_LBUTTONDOWN))
  //      getmouseclick(WM_LBUTTONDOWN, x, y);
/*
    while(!ismouseclick(WM_LBUTTONUP)){
        p->draw();
        delay(100);
        if(ismouseclick(WM_MOUSEMOVE)){
            getmouseclick(WM_MOUSEMOVE, x, y);
            cleardevice();
            b->draw();
            p->translate(x,y);
            p->draw();
            delay(100);
        }
    }*/
   // Pawn *p = new Pawn(100, 100, 50, LIGHTBLUE);
   // p->draw();
  //  Square *s = new Square(200,200,200,WHITE);
   // s->draw();
    while(!kbhit()){
        delay(200);
    }
    return 0;
}
