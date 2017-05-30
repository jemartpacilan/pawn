
class Player{
    private:
    public:

        Player(){};

        Pawn *p[8];

        void draw(){
            for(int i = 0; i < 8; i++){
                p[i]->draw();
            }
        }
};

class Player1:public Player{
    public:

        Player1(){};

        void init(int startx, int starty, int BOARD_SIZE){

            for(int i = 0; i < 8; i++, startx += (BOARD_SIZE*2)){
                p[i] = new Pawn(startx, starty, BOARD_SIZE, WHITE);
            }

        }
};

class Player2:public Player{
    public:

        Player2(){};

        void init(int startx, int starty, int BOARD_SIZE){

            for(int i = 0; i < 8; i++, startx += (BOARD_SIZE*2)){
                p[i] = new Pawn(startx, starty, BOARD_SIZE, COLOR(50,50,50));
            }

        }

};
