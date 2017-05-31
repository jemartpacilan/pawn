#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>


class SplashScreen{

    public:
        SplashScreen(){};

        void welcome_splashscreen(){
            int page = 1;
            while(!kbhit()){
                Pawn *p = new Pawn (getmaxx()/2, getmaxy()/2, 100, WHITE, 1);
                Pawn *arr[10];
                p->draw();
                settextstyle(6,0,30);
                outtextxy(getmaxx()/2 - 400, getmaxy()/2 - 25,"PAWN");
                outtextxy(getmaxx()/2 + 50, getmaxy()/2 - 25,"WARS");
                setactivepage(page);
                setvisualpage(1 - page);
                cleardevice();
                page = 1 - page;
            }
        }

        bool gameOver(int winner){
            int menu = 3;
            setactivepage(menu);
            setvisualpage(menu);
            cleardevice();
            settextstyle(6, 0, 50);
            int midx = getmaxx() / 2;

            int midy = getmaxy() / 2;



            /* move the CP to the center of the screen */

            moveto(midx - 200, midy);
        //    settextjustify(1920,1080);


            //char *c = "Game Over";

            /* output text starting at the CP */

            if(winner == 1)
                outtext("PLAYER 1 WINS");
            else
                outtext("PLAYER 2 WINS");

            settextstyle(6, 0, 50);
            moveto(midx - 200, midy + 150);
            outtext("Press ENTER to play again");
            moveto(midx - 200, midy + 300);
            outtext("ESC to exit");

            bool screenInstance = true;
            while(screenInstance){
                if (GetAsyncKeyState(VK_ESCAPE)){
                        screenInstance = false;
                        return false;
                }
                if (GetAsyncKeyState(VK_RETURN)){
                        screenInstance = false;
                        return true;
                }
            }
        }
};
