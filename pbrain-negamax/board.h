#ifndef BROAD_H
#define BROAD_H
#include "skelet/pisqpipe.h"
#include <windows.h>

typedef unsigned long DWORD;

#define EMPTY_MOVE 0
#define TURN_MOVE 1
#define OPPONENT_MOVE 2
#define OUTSIDE_MOVE 3
//���巽��
//����
#define UP_DOWN 0
//��������
#define LEFTUP_RIGHTDOWN 1
//����
#define LEFT_RIGHT 2
//��������
#define RIGHTUP_LEFTDOWN 3

typedef int Tsymbol;
struct Tsquare;
typedef Tsquare *Psquare;

struct Tsquare
{
	Tsymbol z;  //0=nothing, 1=my, 2=opponent, 3=outside
	short x, y; //coordinates 0..width-1, 0..height-1
};

#define MAX_BOARD 127

struct Mov
{
	int x;
	int y;
	int val;
	Mov *Nxt;
};

extern int diroff[9], width, height, height2;
extern Psquare board, boardb, boardk;

void boardInit();

void SetChessOnBoard(int x, int y, int type);

Psquare Square(int x, int y);

#define nxtP(p, i) (p = (Psquare)(((char *)p) + (i * s)))
#define prvP(p, i) (p = (Psquare)(((char *)p) - (i * s)))

//�����ж�
//��������
#define NO_FORBIDDEN 0
#define THREE_THREE_FBD 1
#define FOUR_FOUR_FBD 2
#define LONGFBD 3

struct ChessAnalyzeData
{
	int adjsameNxt;		 //��¼��(x, y)Next���ڵ�������ɫ������
	int adjemptyNxt;	 //��¼adjsame��������λ��
	int jumpsameNxt;	 //��¼adjempty��������ɫ������
	int jumpemptyNxt;	//��¼jumpsame��Ŀ�λ��
	int jumpjumpsameNxt; //��¼jumpempty���������ɫ������

	int adjsamePre;		 //��¼��(x, y)pre���ڵ�������ɫ������
	int adjemptyPre;	 //��¼adjsameǰ������λ��
	int jumpsamePre;	 //��¼adjemptyǰ������ɫ������
	int jumpemptyPre;	//��¼jumpsameǰ�Ŀ�λ��
	int jumpjumpsamePre; //��¼jumpemptyǰ��������ɫ������

	Psquare pNxt;
	Psquare pPrv;

	ChessAnalyzeData(); //����
};

void AnalysisLine(Psquare p0, int direction, ChessAnalyzeData *data);

//�ؼ�����ּ��
int KeyPointForbiddenCheck(Psquare p, int direction, int shift);
//���ּ��
int ForbiddenCheck(ChessAnalyzeData *checkData, Psquare p0);

Mov *MergeSort(Mov *source, int count);
void MergePass(Mov *source, Mov *target, const int s, const int n);
void Merge(Mov *source, Mov *target, int l, int m, int r);
#endif