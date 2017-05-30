#include <graphics.h>
#include <iostream>
#include "Pawn.h"
#include "Player.h"
#include "Board.h"

using namespace std;


bool checkCollision(int x1, int y1, int x2, int y2, int half_length){
//This method accepts the origin of the mouse x1, y1
//and the origin of the square x2, y2
//var field indicates the space that the enemy inhabits:
//x-f, y-f   x+f,y-f|
//                  |
//      x,y         |
//                  |
//x-f, y+f   x+f,y-f|
//This method returns true if x1,y1 is inside the 'field'

    if(x1 > x2 - half_length && x1 < x2 + half_length){
        if(y1 > y2 - half_length && y1 < y2 + half_length){
            return true;
        }
    }

    return false;
}

bool game(){

    static const int BOARD_SIZE = getmaxx()/40;

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

    bool gameInstance = true;

    while(gameInstance){

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        b->draw();

        if(p1->isMoving()){

            int clickedPawn;

            if(!clicking){
                if(ismouseclick(WM_LBUTTONDOWN)){

                    for(int i = 0; i < 8; i++){

                        int currX = b->findX(p1->p[i]->getid());
                        int currY = b->findY(p1->p[i]->getid());

                        if(checkCollision(mousex(), mousey(), p1->p[i]->getX(), p1->p[i]->getY(), BOARD_SIZE) && b->canMove(1, currX, currY)){
                            clickedPawn = i;
                            clicking = true;


                            b->findReset(p1->p[i]->getid());

                            b->checkMoves(1, currX, currY);
                            if (!p1->p[clickedPawn]->alive){
                                clicking = false;
                            }
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
                                if(b->square[x][y]->isToggled()){
                                    p1->p[clickedPawn]->translate(b->square[x][y]->getX(),b->square[x][y]->getY());
                                    clicking = false;


                                    if(b->stat_table[x][y] < 0 ){
                                        cout<<"here"<<endl;
                                        p2->p[(b->stat_table[x][y] * -1) - 1]->translate(100 + (b->stat_table[x][y] * -1) * 30, 800);
                                        p2->p[(b->stat_table[x][y] * -1) - 1]->Die();
                                    }



                                    b->stat_table[x][y] = p1->p[clickedPawn]->getid();
                                    b->print();

                                    if(y == 0){
                                        gameInstance = false;
                                        return gameInstance;
                                    }

                                    b->resetToggle();

                                    p1->stop();
                                    p2->move();
                                }


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

                        int currX = b->findX(p2->p[i]->getid());
                        int currY = b->findY(p2->p[i]->getid());

                        if(checkCollision(mousex(), mousey(), p2->p[i]->getX(), p2->p[i]->getY(), BOARD_SIZE) && b->canMove(2, currX, currY)){
                            clickedPawn = i;
                            clicking = true;
                            b->findReset(p2->p[i]->getid());

                            b->checkMoves(2, currX, currY);
                            if (!p2->p[clickedPawn]->alive){
                                clicking = false;
                            }
                        }

                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                }
            }

            if(clicking){
                if(p2->p[clickedPawn]->alive == true){
                    p2->p[clickedPawn]->translate(mousex(),mousey());
                    if(ismouseclick(WM_LBUTTONDOWN)){
                        for(int y = 0; y < 8; y++){
                            for(int x = 0; x < 8; x++){
                                if(checkCollision(b->square[x][y]->getX(), b->square[x][y]->getY(), mousex(), mousey(), BOARD_SIZE)){
                                    if(b->square[x][y]->isToggled()){
                                        p2->p[clickedPawn]->translate(b->square[x][y]->getX(),b->square[x][y]->getY());
                                        clicking = false;

                                        if(b->stat_table[x][y] > 0 ){
                                            cout<<"here"<<endl;
                                            p1->p[(b->stat_table[x][y]) - 1]->translate(100 + (b->stat_table[x][y]) * 30, 300);
                                            p1->p[(b->stat_table[x][y]) - 1]->Die();
                                        }



                                        b->stat_table[x][y] = p2->p[clickedPawn]->getid();
                                        b->print();

                                        if(y == 7){

                                            gameInstance = false;
                                            return gameInstance;
                                        }

                                        b->resetToggle();

                                        p2->stop();
                                        p1->move();
                                    }
                                }
                            }
                        }
                    }

                    clearmouseclick(WM_LBUTTONDOWN);
                }
            }
        }
        p1->draw();
        p2->draw();

        page = 1 - page;
        delay(24);

    }

    return gameInstance;
}

int main(){

    //if you're running on a smaller resolution monitor,
    //change to 1366 x 768
    static const int X_RES = 1920;
    static const int Y_RES = 1080;

    initwindow(X_RES, Y_RES, "Pawn Wars");

    while(game());

    while(!kbhit()){
        delay(200);
    }
    return 0;
}
