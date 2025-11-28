#include <graphics.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Vec {
    float x, y;
    Vec() : x(0), y(0) {}
    Vec(float X, float Y) : x(X), y(Y) {}
    Vec operator+(const Vec &o) const { return Vec(x+o.x, y+o.y); }
    Vec operator-(const Vec &o) const { return Vec(x-o.x, y-o.y); }
    Vec operator*(float s) const { return Vec(x*s, y*s); }
};

struct Circle {
    Vec pos;
    Vec vel;
    float r;
    int color;
};

int main(){
    int W = 800, H = 700;
    initwindow(W, H, "Collision Simulation");
    srand(time(0));

    const int N = 10;
    std::vector<Circle> C;
    C.reserve(N);

    // Inisialisasi lingkaran
    for (int i=0;i<N;i++){
        float r = 8 + rand()%12;
        float x = 50 + rand()%(W-100);
        float y = 50 + rand()%(H-100);
        float vx = (rand()%200 - 100)/30.0f;
        float vy = (rand()%200 - 100)/30.0f;
        
        Circle c;
        c.pos = Vec(x,y);
        c.vel = Vec(vx,vy);
        c.r = r;
        c.color = COLOR(rand()%255, rand()%255, rand()%255);
        C.push_back(c);
    }

    while (true){
        cleardevice();

        // Update posisi dan collision dengan dinding
        for (auto &c : C){
            c.pos.x += c.vel.x;
            c.pos.y += c.vel.y;
            
            // Bounce dari dinding
            if (c.pos.x - c.r < 0){ c.pos.x = c.r; c.vel.x *= -1; }
            if (c.pos.x + c.r > W){ c.pos.x = W - c.r; c.vel.x *= -1; }
            if (c.pos.y - c.r < 0){ c.pos.y = c.r; c.vel.y *= -1; }
            if (c.pos.y + c.r > H){ c.pos.y = H - c.r; c.vel.y *= -1; }
        }

        // Gambar lingkaran
        for (auto &c : C){
            setcolor(c.color);
            setfillstyle(SOLID_FILL, c.color);
            fillellipse(c.pos.x, c.pos.y, c.r, c.r);
        }

        delay(10);
    }

    return 0;
}