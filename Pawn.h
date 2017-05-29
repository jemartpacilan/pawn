#include <graphics.h>

using namespace std;
/*class Triangle{
private:
    int x, y, t[6], half_length, color;
public:
    Triangle(int x, int y, int half_length, int color){
        this->x = x;
        this->y = y;
        this->half_length = half_length;
        this->color = color;
    }

    void draw(){
        t = {
            x, y - (half_length * 0.2),
            x - (half_length * 0.6), y + (half_length * 0.9),
            x + (half_length * 0.6), y + (half_length * 0.9)
        };
        setcolor(color);
        setfillstyle(1, color);
        fillpoly(3, t);
    }
};*/

class Triangle{
private:
    int x, y, t[6], half_length, color;
    int xmin, ymin, xmax, ymax;
public:
    Triangle(int xmin, int ymin, int xmax, int ymax, int color){
        this->x = x;
        this->y = y;
        this->xmin = xmin;
        this->ymin = ymin;
        this->xmax = xmax;
        this->ymax = ymax;
        this->color = color;
    }

    void draw(){
        t = {
            xmax, ymax,
            xmin, ymax,
            xmin, ymin
        };
        setcolor(color);
        setfillstyle(1, color);
        fillpoly(3, t);
    }
};
/*class Rect{
private:
    int x, y, r[8], half_length, color;
public:
    Rect(int x, int y, int half_length, int color){
        this->x = x;
        this->y = y;
        this->half_length = half_length;
        this->color = color;
    }


    void draw(){
        r = {
            x - (half_length * 0.65), y + (half_length * 0.7),
            x + (half_length * 0.65), y + (half_length * 0.7),
            x + (half_length * 0.65), y + (half_length * 0.9),
            x - (half_length * 0.65), y + (half_length * 0.9)
        };
        setcolor(color);
        setfillstyle(1, color);
        fillpoly(4, r);
    }
};
*/

class Rect{
private:
    int x, y, r[8], half_length, color;
    int xmin,ymin,xmax,ymax;
public:
    Rect(int xmin, int ymin, int xmax, int ymax, int color){
        this->xmin = xmin;
        this->ymin = ymin;
        this->xmax = xmax;
        this->ymax = ymax;
        this->color = color;
    }


    void draw(){
        r = {
            xmin, ymin,
            xmin, ymax,
            xmax, ymax,
            xmax, ymin
        };
        setcolor(color);
        setfillstyle(1, color);
        fillpoly(4, r);
    }
};

class Pawn{
private:
    int x, y, half_length, r, color;
    Rect *r2, *r1;
    Triangle *t1,*t2;
public:
    Pawn(int x, int y, int half_length, int color){
        this->x = x;
        this->y = y;
        this->half_length = half_length;
        this->color = color;
        this->r1 = new Rect(x - (half_length * 0.35), y, x + (half_length * 0.35), y + (half_length * 0.1), color);
        this->r2 = new Rect(x - (half_length * 0.65), y + (half_length * 0.7), x + (half_length * 0.65), y + (half_length * 0.9), color);
        this->t1 = new Triangle(x,y - (half_length * 0.2),x - (half_length * 0.6),y + (half_length * 0.9),BLUE);
        this->t2 = new Triangle(x,y - (half_length * 0.2),x + (half_length * 0.6),y + (half_length * 0.9),color);
    }

    void draw(){
        t1->draw();
        t2->draw();
     //  setcolor(LIGHTBLUE);
  //      arc(x,y-(half_length*0.3), 90, 270,half_length*0.40);
    //    line(x,y-((half_length*0.80)),x,y+(half_length*0.3));

      //  floodfill(x,y-(half_length*0.4),color);

        fillellipse(x,y-(half_length*0.3),half_length*0.40,half_length*0.40);

        /*for(int i =  0; i < 20; i++){
            arc(x,y-(half_length*0.3), 90, 270,(half_length*0.40) - i);
        }*/
        setcolor(BLUE);
        setfillstyle(1, BLUE);
        pieslice(x,y-(half_length*0.3), 90, 270,(half_length*0.40));


        floodfill(x - (half_length*0.30),y-(half_length*0.3),BLUE);
        r1->draw();
        r2->draw();


    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }
};
