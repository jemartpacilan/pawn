#include <graphics.h>
#include <iostream>
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

                if(color == COLOR(222,184,135)){
                    setcolor(COLOR(0,200,0));
                    setfillstyle(1, COLOR(0,200,0));
                }

                else if(color == COLOR(139,69,19)){
                    setcolor(COLOR(0,150,0));
                    setfillstyle(1, COLOR(0,150,0));
                }


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

        bool isToggled(){
            return toggled;
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
        int first_x, first_y;

    public:
        Square *square[8][8];
        int stat_table[8][8];

        Board(int square_length){
            this->square_length = square_length;
        }

        Board(){};

        void init(){
            int counterX = 0;
            int counterY = 0;
            bool first = true;
            for(int y = 0, posY = 2; y < 8; y++, posY++){
                for(int x = 0, posX = 6; x < 8; x++, posX++){
                    if(first){
                        first_x = posX * (square_length*2);
                        first_y = posY * (square_length*2);
                        first = false;
                    }
                    if(counterX%2 == 0)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(222,184,135));
                    else if(counterX%2 == 1)
                        square[x][y] = new Square(posX * (square_length*2), posY * (square_length*2), square_length, COLOR(139,69,19));

                    stat_table[x][y] = 0;
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

        int getFirstPosX(){
            return first_x;
        }

        int getFirstPosY(){
            return first_y;
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

        int findX(int id){
            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(stat_table[x][y] == id){
                        //currX = x;
                        return x;
                    }
                }
            }
        }

        int findY(int id){
            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(stat_table[x][y] == id){
                        //currY = y;
                        return y;
                    }
                }
            }
        }

        void findReset(int id){

            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    if(stat_table[x][y] == id){
                        stat_table[x][y] = 0;
                    }
                }
            }
        }

        void win(int player){

        }

        void checkMoves(int player, int x, int y){
            int currX = x;
            int currY = y;

            if(player == 1){
                //white perspective
                if(currX > 0){
                    if(stat_table[currX - 1][ currY - 1] < 0){
                        //can move here;

                        square[currX - 1][currY -1]->toggle();

                    }
                }

                if(currX < 7){
                    if(stat_table[currX + 1][ currY - 1] < 0){
                        //can move here;

                        square[currX + 1][ currY - 1]->toggle();
                    }
                }

                if(stat_table[currX][ currY - 1] == 0){
                    //can move here;

                    square[currX][ currY - 1]->toggle();
                }

                if(currY == 6 && stat_table[currX][currY - 1] == 0){
                    if(stat_table[currX][currY - 2] == 0){
                        //can move here;

                        square[currX][currY - 2]->toggle();
                    }
                }
            }

            if(player == 2){
                //black perspective
                if(currX > 0){
                    if(stat_table[currX - 1][currY + 1] > 0){
                        //can move here;

                        square[currX - 1][currY + 1]->toggle();

                    }
                }

                if(currX < 7){
                    if(stat_table[currX + 1][currY + 1] > 0){
                        //can move here;

                        square[currX + 1][currY + 1]->toggle();
                    }
                }

                if(stat_table[currX][currY + 1] == 0){
                    //can move here;

                    square[currX][currY + 1]->toggle();
                }

                if(currY == 1 && stat_table[currX][currY + 1] == 0){
                    if(stat_table[currX][currY + 2] == 0){
                        //can move here;

                        square[currX][currY + 2]->toggle();
                    }
                }
            }




        }

        bool canMove(int player, int x, int y){
            int currX = x;
            int currY = y;
            if(player == 1){
                //white perspective
                if(currX > 0){
                    if(stat_table[currX - 1][ currY - 1] < 0){

                       return true;

                    }
                }

                if(currX < 7){
                    if(stat_table[currX + 1][ currY - 1] < 0){

                        return true;
                    }
                }

                if(stat_table[currX][ currY - 1] == 0){
                    return true;
                }

                if(currY == 6 && stat_table[currX][currY - 1] == 0){
                    if(stat_table[currX][currY - 2] == 0){
                        return true;
                    }
                }
            }

            if(player == 2){
                //black perspective
                if(currX > 0){
                    if(stat_table[currX - 1][currY + 1] > 0){
                        return true;
                    }
                }

                if(currX < 7){
                    if(stat_table[currX + 1][currY + 1] > 0){
                        return true;
                    }
                }

                if(stat_table[currX][currY + 1] == 0){
                    return true;
                }

                if(currY == 1 && stat_table[currX][currY + 1] == 0){
                    if(stat_table[currX][currY + 2] == 0){
                        return true;
                    }
                }
            }

            return false;

        }

        void resetToggle(){
            for(int y = 0, posY = 1; y < 8; y++, posY++){
                for(int x = 0, posX = 1; x < 8; x++, posX++){
                    square[x][y]->untoggle();
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
