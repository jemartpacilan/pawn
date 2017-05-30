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
    void translateTri(int x, int y){
			this->xmin += x;
			this->xmax += x;
			this->ymin += y;
			this->ymax += y;
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

    void translateRect(int x, int y){
			this->xmin += x;
			this->xmax += x;
			this->ymin += y;
			this->ymax += y;
		}
};

class Pawn{
private:
    int x, y, half_length, r, color, shadow_color;
    Rect *r2, *r1;
    Triangle *t1,*t2;
public:
    Pawn(int x, int y, int half_length, int color){
        this->x = x;
        this->y = y;
        this->half_length = half_length;
        this->color = color;
        if(color == WHITE)
            this->shadow_color = LIGHTGRAY;
        if(color == COLOR(50,50,50))
            this->shadow_color = BLACK;
        this->r1 = new Rect(x - (half_length * 0.35), y, x + (half_length * 0.35), y + (half_length * 0.1), color);
        this->r2 = new Rect(x - (half_length * 0.65), y + (half_length * 0.7), x + (half_length * 0.65), y + (half_length * 0.9), color);
        this->t1 = new Triangle(x,y - (half_length * 0.2),x - (half_length * 0.6),y + (half_length * 0.9),shadow_color);
        this->t2 = new Triangle(x,y - (half_length * 0.2),x + (half_length * 0.6),y + (half_length * 0.9),color);
    }

    void draw(){
        t1->draw();
        t2->draw();


        fillellipse(x,y-(half_length*0.3),half_length*0.40,half_length*0.40);

        setcolor(shadow_color);
        setfillstyle(1, shadow_color);
        pieslice(x,y-(half_length*0.3), 90, 270,(half_length*0.40));


        floodfill(x - (half_length*0.30),y-(half_length*0.3),shadow_color);
        r1->draw();
        r2->draw();


    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void translate(int h, int v){

        h -= x;
        v -= y;

        t1->translateTri(h,v);
        t2->translateTri(h,v);
        r1->translateRect(h,v);
        r2->translateRect(h,v);
        x+=h;
        y+=v;
    }
};
