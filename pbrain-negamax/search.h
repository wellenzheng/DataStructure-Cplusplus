#ifndef ALPHABETA_H
#define ALPHABETA_H
#include "skelet\pisqpipe.h"
#include <windows.h>
#include "evaluation.h"
#include "board.h" 
#include "historytable.h"

const char *infotext="name=\"mysearch\", author=\"  xyh  \", version=\"1.0\", country=\"China\", www=\"#####\"";

extern int firstPlayer;
 int** m_HistoryTable[2];

int** PosValue;
int m_nRecordCount[2][7];
int*** m_nRecord;

DWORD stopTime();



Psquare board,boardb,boardk;

Mov bestMove;


Mov* GenerateMoves(int& moveLen,int player);
void MakeMove(Mov m,int player);
void UnmakeMove(Mov);
int distance(Psquare p0,Psquare p1);

//�̶��������
void SimpleSearch();
//������������+alphaBeta����
void IterDeeping();
//��С��������
int NegaMax00(int depth,int player,int MaxDepth);
//��С��������+��ʷ������
int NegaMax(int depth, int player, int MaxDepth);
//alphaBeta����
int alphabeta(int depth,int alpha,int beta,int player,int MaxDepth);
//�ж��Ƿ��ǽ���
bool isBan(Psquare p0,int player);
//����ѡ��һ��
Mov mov_rd(Mov* moveList,int count);
//�ж�ִ��move������Ƿ����
bool isGameOver(Mov move);

void freeResource();
#endif