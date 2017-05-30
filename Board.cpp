#include <graphics.h>
#include <iostream>
#include "Pawn.h"
#include "Player.h"

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
        bool toggled;
    public:
        Square(){};
        Square(int x, int y, int half_length, int color){
            this->x = x;
            this->y = y;
            this->half_length = half_length;
            this->color = color;
            this->toggled = false;
        }

        void draw(){
            int sqr[] = {

                            x - half_length, y - half_length,
                            x - half_length, y + half_length,
                            x + half_length, y + half_length,
                            x + half_length, y - half_length

            };

            if(toggled){
                setcolor(LIGHTGREEN);
                setfillstyle(1, LIGHTGREEN);
            }
            else{
                setcolor(color);
                setfillstyle(1, color);
            }

            fillpoly(4, sqr);
        }

        void toggle(){
            toggled = true;
        }

        void untoggle(){
            toggled = false;
        }

        int getX(){
            return x;
        }

        int getY(){
            return y;
        }
};

class Board{
    private:
        int x, y;
        int square_length;

    public:
        Square *square[8][8];
        int stat_table[8][8];

        Board(int x, int y){

        }

        Board(int square_length){

            this->square_length = square_length;

        }

        Board(){};

      /*  void init(){


        }*/

        void init(){
            int counterX = 0;
            int counterY = 0;

            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(counterX%2 == 0)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(222,184,135));
                    else if(counterX%2 == 1)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(139,69,19));

                    stat_table[x][y] = 0;
                   // square[x][y]->draw();
                    counterX++;
                }
                counterY++;
                if(counterY%2 == 0)
                    counterX = 0;
                else
                    counterX = 1;
            }

            initPawn();


        }

        void print(){
            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    cout<<"\t"<<stat_table[x][y];
                }

                cout<<endl;
            }

        }

        void initPawn(){
            for(int x = 0, y1 = 6, y2 = 1; x < 8; x++ ){

                stat_table[x][y1] = x + 1;
                stat_table[x][y2] = -x - 1;
            }
        }

        void findReset(int id){

            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(stat_table[x][y] == id)
                        stat_table[x][y] = 0;
                }
            }

        }

        void draw(){

            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    square[x][y]->draw();
                }
            }

        }
};


int main(){

    //if you're running on a smaller resolution monitor,
    //change to 1366 x 768
    static const int X_RES = 1920;
    static const int Y_RES = 1080;

    initwindow(X_RES, Y_RES, "Pawn Wars");

    static const int BOARD_SIZE = getmaxx()/50;

    Board *b = new Board(BOARD_SIZE);

    Player1 *p1 = new Player1();
    Player2 *p2 = new Player2();

    b->init();
    b->draw();

    int x, y;

    bool clicking = false;

    p1->init(b->square[0][6]->getX(), b->square[0][6]->getY(), BOARD_SIZE);
    p2->init(b->square[0][1]->getX(), b->square[0][1]->getY(), BOARD_SIZE);

    p1->move();

    int page = 0;
    while(true){

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        b->draw();
        p1->draw();
        p2->draw();

        if(p1->isMoving()){

            int clickedPawn;

            if(!clicking){
                if(ismouseclick(WM_LBUTTONDOWN)){

                    for(int i = 0; i < 8; i++){
                        if(checkCollision(mousex(), mousey(), p1->p[i]->getX(), p1->p[i]->getY(), BOARD_SIZE)){
                            cout<<"P1 Clicked"<<endl;
                            clickedPawn = i;
                            clicking = true;

                            b->findReset(p1->p[i]->getid());
                        }

                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                }
            }

            if(clicking){

                p1->p[clickedPawn]->translate(mousex(),mousey());
                if(ismouseclick(WM_LBUTTONDOWN)){
                    for(int y = 0; y < 8; y++){
                        for(int x = 0; x < 8; x++){
                            if(checkCollision(b->square[x][y]->getX(), b->square[x][y]->getY(), mousex(), mousey(), BOARD_SIZE)){
                                p1->p[clickedPawn]->translate(b->square[x][y]->getX(),b->square[x][y]->getY());
                                clicking = false;

                                b->stat_table[x][y] = p1->p[clickedPawn]->getid();
                                b->print();
                                p1->stop();
                                p2->move();
                            }
                        }
                    }
                }

                clearmouseclick(WM_LBUTTONDOWN);


            }
        }
        else if(p2->isMoving()){
            int clickedPawn;

            if(!clicking){
                if(ismouseclick(WM_LBUTTONDOWN)){

                    for(int i = 0; i < 8; i++){
                        if(checkCollision(mousex(), mousey(), p2->p[i]->getX(), p2->p[i]->getY(), BOARD_SIZE)){
                            cout<<"P1 Clicked"<<endl;
                            clickedPawn = i;
                            clicking = true;

                            b->findReset(p2->p[i]->getid());
                        }

                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                }
            }

            if(clicking){

                p2->p[clickedPawn]->translate(mousex(),mousey());
                if(ismouseclick(WM_LBUTTONDOWN)){
                    for(int y = 0; y < 8; y++){
                        for(int x = 0; x < 8; x++){
                            if(checkCollision(b->square[x][y]->getX(), b->square[x][y]->getY(), mousex(), mousey(), BOARD_SIZE)){
                                p2->p[clickedPawn]->translate(b->square[x][y]->getX(),b->square[x][y]->getY());
                                clicking = false;

                                b->stat_table[x][y] = p2->p[clickedPawn]->getid();
                                b->print();

                                p2->stop();
                                p1->move();
                            }
                        }
                    }
                }

                clearmouseclick(WM_LBUTTONDOWN);


            }
        }

        page = 1 - page;
        delay(24);

    }

    while(!kbhit()){
        delay(200);
    }
    return 0;
}
