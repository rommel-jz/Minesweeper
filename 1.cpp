//0.8版本
//通过类与结构体来完成
#include<iostream>
#include<vector>
#include<graphics.h>

#define ROW 10
#define COL 10
using namespace std;
struct Cell {
	bool IsMine=0;
	int SurroundMine=0;
	bool IsOpen=0;
	bool IsMark=0;
};
class MineMap {
private:
	int countreveal = 0;
	int mines;
	vector<vector<Cell>> grids;
	IMAGE img[15];
public:
	MineMap(int m) :mines(m) {
		grids.resize(ROW, vector<Cell>(COL));
		loadimage(&img[0], L"0.bmp", 50, 50);//自己储存的图片
		loadimage(&img[1], L"1.bmp", 50, 50);
		loadimage(&img[2], L"2.bmp", 50, 50);
		loadimage(&img[3], L"3.bmp", 50, 50);
		loadimage(&img[4], L"4.bmp", 50, 50);
		loadimage(&img[5], L"5.bmp", 50, 50);
		loadimage(&img[6], L"6.bmp", 50, 50);
		loadimage(&img[7], L"7.bmp", 50, 50);
		loadimage(&img[8], L"8.bmp", 50, 50);
		loadimage(&img[9], L"9.bmp", 50, 50);
		loadimage(&img[10], L"10.bmp", 50, 50);
		loadimage(&img[11], L"11.bmp", 50, 50);
		loadimage(&img[12], L"12.bmp", 50, 50);
		loadimage(&img[13], L"13.bmp", 300, 150);
		loadimage(&img[14], L"14.bmp", 300, 150);

	}
	void reset() {
		countreveal = 0;
		for (auto& a : grids) {
			for (auto& b : a) {
				b.IsMark = 0;
				b.IsMine = 0;
				b.IsOpen = 0;
				b.SurroundMine = 0;
			}
		}
	}
	void PlaceMines() {
		srand(time(0));
		int places = 0;
		while (places < mines) {
			int x = rand() % ROW;
			int y = rand() % COL;
			if (grids[x][y].IsMine == 0) {
				places++;
				grids[x][y].IsMine = true;
			}
		}
	}
	void CaculateMines() {
	
		int dx[] = { -1,-1,-1,0,1,1,1,0 };
		int dy[] = { -1,0,1,1,1,0,-1,-1 };
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				grids[i][j].SurroundMine = 0;
				for (int k = 0; k < 8; k++) {
					if ((i + dx[k]) >= 0 && (i + dx[k]) < ROW && (j + dy[k]) >= 0
						&& (j + dy[k]) < COL && grids[i + dx[k]][j + dy[k]].IsMine == true)
					{
						grids[i][j].SurroundMine++;
					}
				}
			}
		}
	}
	void reveal(int x,int y) {
		if (x < 0 || x>=ROW || y < 0 || y>=COL
			|| grids[x][y].IsMark || grids[x][y].IsOpen)return;
		grids[x][y].IsOpen = true;
		countreveal++;
		if (grids[x][y].SurroundMine == 0&&grids[x][y].IsMine==0) {
			for (int dx = -1; dx < 2; dx++) {
				for (int dy = -1; dy < 2; dy++) {
					reveal(x + dx, y + dy);
				}
			}
		}
	}
	void display() {
		
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (grids[i][j].IsOpen) {
					if (grids[i][j].IsMine) {
						putimage(j * 50, i * 50, &img[11]);
					}
					else putimage(j * 50, i * 50, &img[grids[i][j].SurroundMine]);
				}
				else {
					if (grids[i][j].IsMark) putimage(j * 50, i * 50, &img[10]);
					else  putimage(j * 50, i * 50, &img[9]);
				}
			}
		}
	}
	void boom() {
		for ( auto& a : grids) {
			for ( auto& b : a) {
				b.IsOpen = true;
			}
		}
	}
	void Mark(int x, int y) {
		if (x < 0 || x>ROW || y < 0 || y>COL || grids[x][y].IsOpen)return;
		grids[x][y].IsMark = !grids[x][y].IsMark;
	}
	
	int CheckWin(int x,int y){
		if (grids[x][y].IsMine&&grids[x][y].IsOpen)return 0;
		int count = 0;
		
		if (countreveal == COL * ROW - mines) {
			return 1;
		}
		else return -1;
	}
	void win() {
		putimage(100, 50, &img[13]);
		
	}
	void lose() {
		putimage(100, 50, &img[14]);

	}


};
int main() {
	MineMap game(10);
	initgraph(500, 500, NULL);
	MOUSEMSG msg;
	do {
		cleardevice();
		game.reset();
		game.PlaceMines();
		game.CaculateMines();
		game.display();
		while (true) {
			msg = GetMouseMsg();
			int px = msg.x/50;
			int py = msg.y/50;
			
			if (msg.uMsg == WM_LBUTTONDOWN) {
				game.reveal(py,px);
				cleardevice();
				game.display();
				if (game.CheckWin(py, px)==1) {
					game.boom();
					cleardevice();
					game.display();
					game.win();
					Sleep(2000);
					break;
				}
				else if (game.CheckWin(py, px) == 0) {
					game.boom();
					cleardevice();
					game.display();
					game.lose();
					Sleep(2000);
					break;
				}
			}
			else if (msg.uMsg == WM_RBUTTONDOWN) {
				game.Mark(py, px);
				cleardevice();
				game.display();

			}
		}

	} while (1);
	return 0;
}




//2025.2.8
