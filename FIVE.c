#pragma once

#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"SDL_image.lib")
//���뾲̬���ӿ�

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH		530
#define SCREEN_HEIGHT		570
#define SCREEN_BPP			32
#define TIME_DELAY			10
#define COLORKEY_R			200
#define COLORKEY_G			0
#define COLORKEY_B			200
#define BUTTON_WIDTH		120
#define BUTTON_HEIGHT		40
#define BUTTON1_X			(SCREEN_WIDTH / 6 - BUTTON_WIDTH / 2) 
#define BUTTON1_Y			(SCREEN_HEIGHT - BUTTON_HEIGHT)
#define BUTTON2_X			(SCREEN_WIDTH / 6 * 3 - BUTTON_WIDTH / 2) 
#define BUTTON2_Y			(SCREEN_HEIGHT - BUTTON_HEIGHT)
#define BUTTON3_X			(SCREEN_WIDTH / 6 * 5 - BUTTON_WIDTH / 2) 
#define BUTTON3_Y			(SCREEN_HEIGHT - BUTTON_HEIGHT)
#define BUTTON_STATUS		3

#define	DIST_MOVE			15
#define SQUARE_POS			20
#define SQUARE_WIDTH		35
#define PIECE_WIDTH			33
#define TOTAL_LINE			15
#define TOTAL_PIECE			(TOTAL_LINE) * (TOTAL_LINE)
#define TOTAL_DIRECTION		4
#define TOTAL_STYLE			17
#define TOTAL_JUDGE			11

#define TWO					2
#define FIVE				5
#define TEN					10
#define INFI				100000000
#define SCORE_DEFEND		9900
#define SCORE_MUST_DEFEND	99000
#define SCORE_TERMINAL		1000000


FILE *fp;//��־�ļ�

enum PIECE {NOTHING, BLACK, WHITE};//����

int systemOver = 0; //ϵͳ����

SDL_Surface *pScreen;
SDL_Surface *pBackground;
SDL_Surface *pPiece;
SDL_Surface *pButton;

struct SDL_Rect rPieceBlack;
struct SDL_Rect rPieceWhite;
struct SDL_Rect rPieceLast;
struct SDL_Rect rPieceTarget;

struct SDL_Rect rButtonRegret[BUTTON_STATUS];
struct SDL_Rect rButtonQuit[BUTTON_STATUS];
struct SDL_Rect rButtonHuman[BUTTON_STATUS];
struct SDL_Rect rButtonComputer[BUTTON_STATUS];
struct SDL_Rect rButtonBlack;
struct SDL_Rect rButtonWhite;
struct SDL_Rect rButtonDraw;
struct SDL_Rect rButtonLater[BUTTON_STATUS];//��ť����

struct SDL_Rect *prButton1;
struct SDL_Rect *prButton2;
struct SDL_Rect *prButton3;//��ťָ��

enum PIECE map[TOTAL_LINE][TOTAL_LINE];
int stepX[TOTAL_PIECE + 1];
int stepY[TOTAL_PIECE + 1];//ÿ����¼
int regretStep = -1;

int moveX[TOTAL_DIRECTION] = {1, 1, 0, -1};
int moveY[TOTAL_DIRECTION] = {0, 1, 1, 1};//��������

char* style[TOTAL_STYLE] = {
"111111", "11111", "1111", "10111", "11011", 
"11101", "111", "1011", "1101", "11001",
"10101", "10011", "11", "101", "1001", 
"10001", "1"};//�����ַ���

int score[TOTAL_STYLE] = {
1000000, 1000000, 100000, 99000, 99000, 
99000, 10000, 9900, 9900, 2000, 
1900, 2000, 1000, 500, 300, 
200, 100};//���ͷ���

int styleWin[TOTAL_STYLE] = {
6, 5, 4, 4, 4,
4, 3, 3, 3, 2,
2, 2, 2, 2, 2,
1, 1};//���Ͷ�Ӧ��������

int styleLen[TOTAL_STYLE];//���ͳ���


//���SDL_RECT
 void fillRect(struct SDL_Rect* r, int x, int y, int w, int h) {
	r->x = x;	r->y = y;
	r->w = w;	r->h = h;
}

//ʱ�����
 double timeMul(int count) {
	return exp(-1.0/count);
}

//�������
 double distPlus(int count, int disX, int disY) {
	return 1 + 1/(abs(stepX[count - 1] - disX) + abs(stepY[count - 1] - disY));
}

 double mulMul(double x) {
	return 1 + x/10.0;
}


//�Ƿ�Ϊ����λ��
 int out(int posX, int posY) {
	return (posX < 0 || posX >= TOTAL_LINE || posY < 0 || posY >= TOTAL_LINE);
}

//�Ƿ�Ϊ����¼�
 int validMove(union SDL_Event* gameEvent) {
	return gameEvent->type == SDL_MOUSEMOTION || gameEvent->type == SDL_MOUSEBUTTONDOWN || gameEvent->type == SDL_MOUSEBUTTONUP;
}

//�Ƿ�Ϊ���������λ��
 int validPieceMove(int x) {
	return x <= SCREEN_WIDTH && ((x - SQUARE_POS) % SQUARE_WIDTH <= DIST_MOVE || (x - SQUARE_POS) % SQUARE_WIDTH >= SQUARE_WIDTH - DIST_MOVE);
}

//��굥����ť
 int getButtonMove(int x, int y) {
	if (x - BUTTON1_X <= BUTTON_WIDTH && x - BUTTON1_X >= 0 &&
		y - BUTTON1_Y <= BUTTON_HEIGHT && y - BUTTON1_Y >= 0)
		return 1;
	if (x - BUTTON2_X <= BUTTON_WIDTH && x - BUTTON2_X >= 0 &&
		y - BUTTON2_Y <= BUTTON_HEIGHT && y - BUTTON2_Y >= 0)
		return 2;
	if (x - BUTTON3_X <= BUTTON_WIDTH && x - BUTTON3_X >= 0 &&
		y - BUTTON3_Y <= BUTTON_HEIGHT && y - BUTTON3_Y >= 0)
		return 3;
	return 0;
}

//�������
 int getPieceMove(int x) {
	if ((x - SQUARE_POS) % SQUARE_WIDTH <= DIST_MOVE) 
		return (x - SQUARE_POS) / SQUARE_WIDTH;
	else
		return (x - SQUARE_POS) / SQUARE_WIDTH  + 1;

}

//����ת�����ַ�
 char getPieceChar(enum PIECE x, enum PIECE t) {
	if (t == BLACK)
	switch(x) {
		case NOTHING: return '0';
		case BLACK: return '1';
		case WHITE: return '2';
	}
	else
	switch(x) {
		case NOTHING: return '0';
		case BLACK: return '2';
		case WHITE: return '1';
	}
	return '0';
}

//��ɫ����
 enum PIECE getReversePiece(enum PIECE x) {
	if (x == BLACK) 
		return WHITE;
	if (x == WHITE)
		return BLACK;
	return NOTHING;
}

//��յ�ͼ
void fresh() {
	int i, j;
	for (i = 0; i < TOTAL_LINE; ++i)
		for (j = 0; j < TOTAL_LINE; ++j)
			map[i][j] = NOTHING;
	for (i = 0; i < TOTAL_PIECE + 1; ++i)
		stepX[i] = stepY[i] = -1;
}

//��ʾͼƬ
void flip(int count) {
	int i, j;
	struct SDL_Rect rTemp;
	//��ʾ����
	SDL_UpperBlit(pBackground, NULL, pScreen, NULL);
	//��ʾ��ť
	fillRect(&rTemp, BUTTON1_X, BUTTON1_Y, 0, 0);
	SDL_UpperBlit(pButton, prButton1, pScreen, &rTemp);
	fillRect(&rTemp, BUTTON2_X, BUTTON2_Y, 0, 0);
	SDL_UpperBlit(pButton, prButton2, pScreen, &rTemp);
	fillRect(&rTemp, BUTTON3_X, BUTTON3_Y, 0, 0);
	SDL_UpperBlit(pButton, prButton3, pScreen, &rTemp);
	//��ʾ����
	for (i = 0; i < TOTAL_LINE; ++i)
		for (j = 0; j < TOTAL_LINE; ++j) {
			fillRect(&rTemp, SQUARE_POS + SQUARE_WIDTH * i - PIECE_WIDTH / 2,
				SQUARE_POS + SQUARE_WIDTH * j - PIECE_WIDTH / 2, 0, 0);
			switch (map[i][j]) {
			case BLACK: SDL_UpperBlit(pPiece, &rPieceBlack, pScreen, &rTemp); break;
			case WHITE: SDL_UpperBlit(pPiece, &rPieceWhite, pScreen, &rTemp); break;
			}
			if (i == stepX[count + 1] && j == stepY[count + 1])
				SDL_UpperBlit(pPiece, &rPieceTarget, pScreen, &rTemp);
			if (i == stepX[count]&& j == stepY[count])
				SDL_UpperBlit(pPiece, &rPieceLast, pScreen, &rTemp);
		}
	//��ת��Ļ!
	SDL_Flip(pScreen);
}

//��ʼ��
void init() {
	int i;
	//��־�ļ���ʼ��
	fp = fopen("record.txt", "w");
	//���ͳ��������ʼ��
	for (i = 0; i < TOTAL_STYLE; ++i)
		styleLen[i] = strlen(style[i]);
	//�����ʼ��
	srand(time(NULL));
	//SDL��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("FIVE by ComboZhc", 0);
	//��Ļ��ʼ��
	pScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0);
	//ͼƬ��ʼ��
	pBackground = SDL_LoadBMP("images\\Background.bmp");
	pPiece = SDL_LoadBMP("images\\Piece.bmp");
	SDL_SetColorKey(pPiece, SDL_SRCCOLORKEY, SDL_MapRGB(pPiece->format, COLORKEY_R, COLORKEY_G, COLORKEY_B));		//��ɫ
	pButton = SDL_LoadBMP("images\\Button.bmp");
	SDL_SetColorKey(pButton, SDL_SRCCOLORKEY, SDL_MapRGB(pButton->format, COLORKEY_R, COLORKEY_G, COLORKEY_B));		//��ɫ
	//SDL_RECT��ʼ��
	fillRect(&rPieceBlack, 0, 0, PIECE_WIDTH, PIECE_WIDTH);
	fillRect(&rPieceWhite, 0, PIECE_WIDTH, PIECE_WIDTH, PIECE_WIDTH);
	fillRect(&rPieceLast, PIECE_WIDTH, 0, PIECE_WIDTH, PIECE_WIDTH);
	fillRect(&rPieceTarget, PIECE_WIDTH, PIECE_WIDTH, PIECE_WIDTH, PIECE_WIDTH);
	fillRect(&rButtonRegret[0], 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);;
	fillRect(&rButtonRegret[1], BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT);;
	fillRect(&rButtonRegret[2], BUTTON_WIDTH * 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonQuit[0], 0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonQuit[1], BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonQuit[2], BUTTON_WIDTH * 2, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonHuman[0], 0, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonHuman[1], BUTTON_WIDTH, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonHuman[2], BUTTON_WIDTH * 2, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonComputer[0], 0, BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonComputer[1], BUTTON_WIDTH, BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonComputer[2], BUTTON_WIDTH * 2, BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonBlack, 0, BUTTON_HEIGHT * 4, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonWhite, 0, BUTTON_HEIGHT * 5, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonDraw, 0, BUTTON_HEIGHT * 6, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonLater[0], BUTTON_WIDTH * 2, BUTTON_HEIGHT * 4, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonLater[1], BUTTON_WIDTH * 2, BUTTON_HEIGHT * 5, BUTTON_WIDTH, BUTTON_HEIGHT);
	fillRect(&rButtonLater[2], BUTTON_WIDTH * 2, BUTTON_HEIGHT * 6, BUTTON_WIDTH, BUTTON_HEIGHT);
	//��ť��ʼ��
	prButton1 = &rButtonHuman[0];
	prButton2 = &rButtonComputer[0];
	prButton3 = &rButtonQuit[0];
	//��������Ԫ��ʼ��
	stepX[0] = stepY[0] = -1;
}

//�������ȷ��λ��ȷ��������ַ���
void getPieceStr(char *str, int posX, int posY, int dir, int* pBlockL, int* pBlockR) {
	int j, tempX, tempY;
	tempX = posX;
	tempY = posY;
	*pBlockL = -1;
	*pBlockR = TOTAL_JUDGE;
	for (j = 0; j <= FIVE; ++j) {
		if (out(tempX, tempY))
			str[FIVE - j] = '2';
		else
			str[FIVE - j] = getPieceChar(map[tempX][tempY], map[posX][posY]);
		if (str[FIVE - j] == '2') {
			*pBlockL = FIVE - j;
			break;
		}
		tempX -= moveX[dir];
		tempY -= moveY[dir];
	}
	tempX = posX;
	tempY = posY;
	for (j = 0; j <= FIVE; ++j) {
		if (out(tempX, tempY))
			str[FIVE + j] = '2';
		else
			str[FIVE + j] = getPieceChar(map[tempX][tempY], map[posX][posY]);
		if (str[FIVE + j] == '2') {
			*pBlockR = FIVE + j;
			break;
		}
		tempX += moveX[dir];
		tempY += moveY[dir];
	}	
}

//���ۺ���
int judge(int posX, int posY) {
	int i, j, scSum = 0, scTemp, scMax, st;
	int blockL, blockR;
	char str[TOTAL_JUDGE + 1] = {"00000000000"};
	for (i = 0; i < TOTAL_DIRECTION; ++i) {
		getPieceStr(str, posX, posY, i, &blockL, &blockR);
		if (blockR - blockL <= FIVE)
			continue;//�˴������γ���������
		j = (blockL == -1 ? 0 : blockL);
		scMax = -INFI;
		while (j < FIVE) {
			while (str[++j] != '1');
			for (st = 0; st < TOTAL_STYLE; ++st) 
				if (strncmp(str + j, style[st], styleLen[st]) == 0)
					break;
			scTemp = 0;
			if (st != TOTAL_STYLE)
				scTemp = score[st];
			if (st != TOTAL_STYLE && st > 1) 
			{
				if (j - 1 == blockL && j + styleLen[st] == blockR)
					scTemp /= TEN;
				if (j - 1 == blockL || j + styleLen[st] == blockR)
					scTemp /= TEN;
			}
			//����ĳ����, �������͵÷�
			if (scTemp > scMax)
				scMax = scTemp;//ȡ������͵÷�
		}
		if (scSum >= SCORE_DEFEND && scMax >= SCORE_DEFEND)
			scSum += scMax * TEN;
		else
			scSum += scMax;
	}
	return scSum;
}

//�жϺ���
int judgeWin(int posX, int posY) {
	int i, j, st, maxSt = 0;
	int winCase = 2;
	int blockL, blockR;
	char str[TOTAL_JUDGE + 1] = {"00000000000"};
	for (i = 0; i < TOTAL_DIRECTION; ++i) {
		getPieceStr(str, posX, posY, i, &blockL, &blockR);
		if (blockR - blockL <= FIVE)
			continue;
		j = (blockL == -1 ? 0 : blockL);
		while (j < FIVE) {
			while (str[++j] != '1');
			for (st = 1; st <= 8; ++st) 
				if (strncmp(str + j, style[st], styleLen[st]) == 0)
					break;
			if (st <= 8) {
			if (styleWin[st] == 5) 
				winCase = 5;
			if (styleWin[st] == 4 && styleWin[st] > winCase)
				 winCase = 4;
			if (styleWin[st] == 3 && j - 1 > blockL && j + styleLen[st] < blockR && styleWin[st] > winCase)
				 winCase = 3;
			}
		}
	}
	return winCase;
}

//���㺯��
void compute(int *pPosX, int *pPosY, enum PIECE x, int count) {
	int max = -INFI, maxEnemy = -INFI, maxEnemyPos = 0, maxTemp = 0;
	int sc = 1, scEnemy = 0, nowWin = 0, maxNowWin = 0, nextWin = 0, maxNextWin = 0;
	int mustKill = 0;
	int ti, tj, ni, nj, bx = 0, by = 0, bbx, bby;
	for (ti = 0; ti < TOTAL_LINE; ++ti)
		for (tj = 0; tj < TOTAL_LINE; ++tj)
			if (map[ti][tj] == NOTHING) {
				map[ti][tj] = x;
				sc = judge(ti, tj);
				nowWin = judgeWin(ti, tj);
				maxEnemy = -INFI;
				maxEnemyPos = 0;
				maxNextWin = 0;
				for (ni = 0; ni < TOTAL_LINE; ++ni) {
					for (nj = 0; nj < TOTAL_LINE; ++nj) {
						if (map[ni][nj] == NOTHING) {
							map[ni][nj] = getReversePiece(x);
							nextWin = judgeWin(ni, nj);
							scEnemy = judge(ni, nj);
							if (maxNextWin < nextWin) 
								maxNextWin = nextWin;
							if (scEnemy >= SCORE_MUST_DEFEND && (nowWin < nextWin))
								sc = 0;//ɱ��, ��Ӯ
							map[ni][nj] = NOTHING; 
							if (scEnemy > maxEnemy) {
								if (maxEnemy < SCORE_MUST_DEFEND)
									maxEnemyPos = 1;
								else
									++maxEnemyPos;
								maxEnemy = scEnemy;
								bbx = ni;
								bby = nj;
							}
							else
								if (scEnemy == maxEnemy || scEnemy >= SCORE_MUST_DEFEND) 
									++maxEnemyPos;
						}
					}
				}
				if (sc >= SCORE_MUST_DEFEND && nowWin >= maxNextWin && nowWin >= maxNowWin) {
					if (sc > max) {
						max = sc;
						bx = ti;
						by = tj;
					}
					mustKill = 1;
					maxNowWin = nowWin;
					printf("MUST KILL(%d, %d) now = %d next = %d\n", ti, tj, nowWin, maxNextWin);
				}//ɱ��, ��Ӯ
				map[ti][tj] = NOTHING;
				if (!mustKill) {
					maxEnemy *= mulMul(maxEnemyPos);
					maxTemp = ((x == BLACK ? timeMul(count) : 1.90 - timeMul(count)) * distPlus(count, ti, tj)) * sc -  maxEnemy;
					if (maxTemp > max || maxTemp == max && rand() % 100 < 25) {
						max = maxTemp;
						bx = ti;
						by = tj;
					}
				}
				printf("(%d, %d), (%d, %d) = %d , %d = %d\n", ti, tj, bbx, bby, sc, maxEnemy, maxTemp);

			}
			printf("Choose(%d, %d) = %d\n", bx, by, max);
			*pPosX = bx;
			*pPosY = by;
}

void game(int flag) {
	int gameOver = 0;
	int result = 0;
	int firstCom = 0;
	int firstMake = flag;
	int count = 0;
	int posX = -1, posY = -1;
	int targetX = -1, targetY = -1;
	enum PIECE x = BLACK;
	union SDL_Event gameEvent;
	while (!gameOver && !systemOver) {
		flip(count);
		while (SDL_PollEvent(&gameEvent)) {

			systemOver = (gameEvent.type == SDL_QUIT);
			if (validMove(&gameEvent)) {
				switch (gameEvent.type) {
				case SDL_MOUSEMOTION:
					switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
					case 1: if (!firstMake) prButton1 = &rButtonLater[1];	break;
					case 2:	if (!result) prButton2 = &rButtonRegret[1];		break;
					case 3: prButton3 = &rButtonQuit[1];					break;
					default:
						if (!result)
							prButton2 = &rButtonRegret[0]; 
						if (!flag) 
							prButton1 = firstMake ? &rButtonComputer[2] : &rButtonLater[0];
						prButton3 = &rButtonQuit[0];
					} break;//ͣ����ť����
				case SDL_MOUSEBUTTONDOWN:
					switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
					case 1: if (!firstMake) prButton1 = &rButtonLater[2];	break;
					case 2:	if (!result) prButton2 = &rButtonRegret[2];		break;
					case 3: prButton3 = &rButtonQuit[2];					break;
					} break;//���°�ť����
				case SDL_MOUSEBUTTONUP:
					switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
					case 1: if (!firstMake) {
								firstCom = 1;
								firstMake = 1; 
								prButton1 = &rButtonComputer[2];
								++count;
								stepX[count] = TOTAL_LINE >> 1;
								stepY[count] = TOTAL_LINE >> 1;
								map[stepX[count]][stepY[count]] = x;
								x = getReversePiece(x);
							}
					case 2: //����
						if (flag) {
							if (!result && (firstMake && firstCom && count > 1) && count >= 1) {
								fprintf(fp, "Regret STEP%d\n", count);
								map[stepX[count]][stepY[count]] = NOTHING;
								stepX[count] = stepY[count] = -1;
								--count;
							}
							prButton1 = &rButtonHuman[2];
						}
						else {
							if (!result && count > 1) {
								fprintf(fp, "Regret step%d\n", count);
								map[stepX[count]][stepY[count]] = NOTHING;
								stepX[count] = stepY[count] = -1;
								--count;
								map[stepX[count]][stepY[count]] = NOTHING;
								stepX[count] = stepY[count] = -1;
								--count;
							}
							prButton1 = &rButtonComputer[2];
						}
						break;
					case 3: //�˳�
						gameOver = 1;
						break;
					}
					break;
				}
				flip(count);
				if (!result && validPieceMove(gameEvent.motion.x) && validPieceMove(gameEvent.motion.y)) {
					stepX[count + 1] = posX = getPieceMove(gameEvent.motion.x);
					stepY[count + 1] = posY = getPieceMove(gameEvent.motion.y);
					if (map[posX][posY] == NOTHING && gameEvent.type == SDL_MOUSEBUTTONUP) {
						//˫�˶�ս
						if (flag) {
							++count;
							stepX[count] = posX;
							stepY[count] = posY;
							map[posX][posY] = x;
							x = getReversePiece(x);
							printf("STEP %d : (%d, %d)\n", count, posX, posY);
							printf("JUDGE %d\n", judgeWin(posX, posY));
							if (judgeWin(posX, posY) >= 5) {
								result = 1;
								prButton2 = (x == WHITE ? &rButtonBlack : &rButtonWhite);
								break;
							}
						}
						//�˻���ս
						else {
							firstMake = 1;
							prButton1 = &rButtonComputer[2];
							++count;
							stepX[count] = posX;
							stepY[count] = posY;
							fprintf(fp, "HUM: (%d, %d)\n", posX, posY);
							map[posX][posY] = x;
							x = getReversePiece(x);
							if (judgeWin(posX, posY) >= 5) {
								result = 1;
								prButton2 = (x == WHITE ? &rButtonBlack : &rButtonWhite);
								break;
							}	
							if (result) break;
							flip(count);
							++count;
							if (count < TOTAL_PIECE) {
								compute(&posX, &posY, x, count);
								fprintf(fp, "COM: (%d, %d)\n", posX, posY);
								stepX[count] = posX;
								stepY[count] = posY;
								map[posX][posY] = x;
								x = getReversePiece(x);
								if (judgeWin(posX, posY) >= 5) {
									result = 1;
									prButton2 = (x == WHITE ? &rButtonBlack : &rButtonWhite);
								}
							}//����ʤ
							if (result) break;
						}

						//ͳ�ƽ��

					}
				}
			}
		}
		if (count == TOTAL_PIECE) {
			result = 1;
			prButton2 = &rButtonDraw;
		}	//ƽ��
		SDL_Delay(TIME_DELAY);
	}
}

int main(int argc, char *argv[]) {
	union SDL_Event gameEvent;
	init();
	fresh();
	while (!systemOver) {	
		flip(0);
		while (SDL_PollEvent(&gameEvent)) {
			systemOver = (gameEvent.type == SDL_QUIT);
			switch(gameEvent.type) {
			case SDL_MOUSEMOTION:
				switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
				case 1:	
					prButton1 = &rButtonHuman[1];	
					break;
				case 2:	
					prButton2 = &rButtonComputer[1];
					break;
				case 3: 
					prButton3 = &rButtonQuit[1];
					break;
				default:
					prButton1 = &rButtonHuman[0];
					prButton2 = &rButtonComputer[0];
					prButton3 = &rButtonQuit[0];
				} break;
			case SDL_MOUSEBUTTONDOWN:
				switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
				case 1:	prButton1 = &rButtonHuman[2];		break;
				case 2:	prButton2 = &rButtonComputer[2];	break;
				case 3: prButton3 = &rButtonQuit[2];		break;
				} break;
			case SDL_MOUSEBUTTONUP:
				switch (getButtonMove(gameEvent.motion.x, gameEvent.motion.y)) {
				case 1:
					prButton1 = &rButtonHuman[2];
					prButton2 = &rButtonRegret[0];
					prButton3 = &rButtonQuit[0];
					printf("Human VS Human\n");
					fprintf(fp, "Human VS Human\n");
					game(1);
					prButton1 = &rButtonHuman[0];
					prButton2 = &rButtonComputer[0];
					prButton3 = &rButtonQuit[0];
					fresh();
					break;
				case 2:
					prButton1 = &rButtonLater[0];
					prButton2 = &rButtonRegret[0];
					prButton3 = &rButtonQuit[0];
					printf("Human VS Computer\n");
					fprintf(fp, "Human VS Computer\n");
					game(0);
					prButton1 = &rButtonHuman[0];
					prButton2 = &rButtonComputer[0];
					prButton3 = &rButtonQuit[0];
					fresh();
					break;
				case 3:
					printf("System Quit\n");
					systemOver = 1;
					break;
				}
				break;
			}
		}
		SDL_Delay(TIME_DELAY);
	}
	fclose(fp);
	SDL_Quit();
	return 0;
}
