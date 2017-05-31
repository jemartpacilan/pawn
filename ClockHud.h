#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>

class ClockHud{

    public:

        ClockHud(){};

        void draw(unsigned long currentTime, int posX, int posY){

            moveto(posX, posY);
            //settextjustify(1920,1080);
            settextstyle(2, 0, 40);
            setcolor(COLOR(255,255,255));

            unsigned long minutes = currentTime/60;
            unsigned long seconds = currentTime%60;

            char buff[4];
            char buff2[4];

            memset(buff,0,4);
            sprintf(buff, "%d", minutes);

            char *m = buff;

            memset(buff2,0,4);
            sprintf(buff2, "%d", seconds);

            char *s = buff2;


            outtext(m);

            outtext(":");
            outtext(s);

        }
};
