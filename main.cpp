#include <graphics.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

struct Vec {
    float x, y;
    Vec() : x(0), y(0) {}
    Vec(float X, float Y) : x(X), y(Y) {}
    Vec operator-(const Vec &o) const { return Vec(x-o.x, y-o.y); }
};

struct Circle {
    Vec pos;
    Vec vel;
    float r;
    int color;
};

// QUADTREE
const int CELL_SIZE = 120;
int GRID_W, GRID_H;
vector<vector<vector<int>>> grid;

void clearGrid() {
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
            grid[y][x].clear();
}

void insertToGrid(const vector<Circle> &C) {
    clearGrid();
    for (int i = 0; i < C.size(); i++) {
        int cx = (int)(C[i].pos.x / CELL_SIZE);
        int cy = (int)(C[i].pos.y / CELL_SIZE);
        if (cx >= 0 && cx < GRID_W && cy >= 0 && cy < GRID_H)
            grid[cy][cx].push_back(i);
    }
}

int checkCollisionsGrid(vector<Circle> &C) {
    int checks = 0;
    for (int gy = 0; gy < GRID_H; gy++) {
        for (int gx = 0; gx < GRID_W; gx++) {
            auto &bucket = grid[gy][gx];
            int n = bucket.size();
            if (n <= 1) continue;

            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    checks++;
                    int a = bucket[i];
                    int b = bucket[j];

                    Vec d = C[b].pos - C[a].pos;
                    float dist2 = d.x*d.x + d.y*d.y;
                    float rsum = C[a].r + C[b].r;

                    if (dist2 <= rsum * rsum) {
                        swap(C[a].vel, C[b].vel);
                    }
                }
            }
        }
    }
    return checks;
}

// BRUTE FORCE
int checkCollisionsBrute(vector<Circle> &C) {
    int checks = 0;
    int n = C.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            checks++;
            Vec d = C[j].pos - C[i].pos;
            float dist2 = d.x*d.x + d.y*d.y;
            float rsum = C[i].r + C[j].r;

            if (dist2 <= rsum * rsum) {
                swap(C[i].vel, C[j].vel);
            }
        }
    }
    return checks;
}

int main() {
    int W = 800, H = 700;
    initwindow(W, H, "Collision Simulation");
    srand(time(0));

    GRID_W = W / CELL_SIZE + 1;
    GRID_H = H / CELL_SIZE + 1;
    grid.resize(GRID_H, vector<vector<int>>(GRID_W));

    const int N = 800;
    vector<Circle> C;
    C.reserve(N);

    for (int i = 0; i < N; i++){
        float r = 13;
        float x = rand() % W;
        float y = rand() % H;
        float vx = (rand()%200 - 100)/30.0f;
        float vy = (rand()%200 - 100)/30.0f;

        Circle c;
        c.pos = Vec(x,y);
        c.vel = Vec(vx,vy);
        c.r = r;
        c.color = COLOR(rand()%200+55, rand()%200+55, rand()%200+55);
        C.push_back(c);
    }

    bool useGrid = true;
    int gridChecks = 0;
    int bruteChecks = 0;

    while (true){
        cleardevice();

        // Update posisi
        for (auto &c : C){
            c.pos.x += c.vel.x;
            c.pos.y += c.vel.y;

            if (c.pos.x - c.r < 0) { c.pos.x = c.r; c.vel.x *= -1; }
            if (c.pos.x + c.r > W) { c.pos.x = W - c.r; c.vel.x *= -1; }
            if (c.pos.y - c.r < 0) { c.pos.y = c.r; c.vel.y *= -1; }
            if (c.pos.y + c.r > H) { c.pos.y = H - c.r; c.vel.y *= -1; }
        }

        //Cek kolisi
        if (useGrid) {
            insertToGrid(C);
            gridChecks = checkCollisionsGrid(C);
        } else {
            bruteChecks = checkCollisionsBrute(C);
        }

        // Gambar
        for (auto &c : C){
            setcolor(c.color);
            setfillstyle(SOLID_FILL, c.color);
            fillellipse(c.pos.x, c.pos.y, c.r, c.r);
        }

        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        
        stringstream ss;
        ss << "Algoritma: " << (useGrid ? "Quadtree" : "Brute Force");
        outtextxy(10, 10, (char*)ss.str().c_str());
        
        stringstream cc;
        cc << "Berapa kali cek: " << (useGrid ? gridChecks : bruteChecks);
        outtextxy(10, 40, (char*)cc.str().c_str());

        swapbuffers();
        delay(10);

        // Toggle dengan spacebar
        if (kbhit()) {
            char ch = getch();
            if (ch == ' ') {
                useGrid = !useGrid;
            }
        }
    }

    return 0;
}
