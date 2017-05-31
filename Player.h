#include <time.h>

class Timer{
    private:
        unsigned long begTime;
        int elapsedTime;
        int remTime;
        int freezeTime;
        bool isPaused;
    public:

        Timer(){
            begTime = clock();
            freezeTime = 0;
            elapsedTime = 0;
            freezeTime = 0;
            isPaused = true;
        }

        unsigned long currentTime(){
            remTime = (180 - ((clock() - begTime)/1000)) + elapsedTime;
            return remTime;

        }

        unsigned long frozeTime(){
            return freezeTime;
        }

        void pause(){
            isPaused = true;
            freezeTime = (180 - ((clock() - begTime)/1000));
        }

        void resume(){
            isPaused = false;
            elapsedTime = freezeTime - remTime;
        }

        bool idle(){
            return isPaused;
        }

        bool isTimeout(unsigned long seconds) {
			return seconds >= currentTime();
		}



};

class Player{
    private:

    public:
        bool isActive;
        Timer *t;

        Player(){

            isActive = false;
            t = new Timer();
        };

        Pawn *p[8];

        void draw(){
            for(int i = 0; i < 8; i++){
                p[i]->draw();
            }
        }

        void move(){
            t->resume();
            isActive = true;
        }

        void stop(){
            t->pause();
            isActive = false;
        }

        bool isMoving(){
            return isActive;
        }
};

class Player1:public Player{
    public:

        Player1(){};

        void init(int startx, int starty, int BOARD_SIZE){
            for(int i = 0; i < 8; i++, startx += (BOARD_SIZE*2)){
                p[i] = new Pawn(startx, starty, BOARD_SIZE, WHITE, i+1);
            }
        }
};

class Player2:public Player{
    public:

        Player2(){};

        void init(int startx, int starty, int BOARD_SIZE){
            for(int i = 0; i < 8; i++, startx += (BOARD_SIZE*2)){
                p[i] = new Pawn(startx, starty, BOARD_SIZE, COLOR(50,50,50), -i-1);
            }
        }

};
