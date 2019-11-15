#include "search.h"
#include <algorithm>
#include <string.h>
#include <iostream>

void brain_init()
{
	pipeOut((char *)"DEBUG brain_init");
	if (width < 5 || width > MAX_BOARD || height < 5 || height > MAX_BOARD)
	{
		pipeOut((char *)"ERROR size of the board");
		return;
	}

	boardInit();
	evaluationInit(width, height);
	initHistoryTable(width, height);
	pipeOut((char *)"OK");
}

void brain_restart()
{
	pipeOut((char *)"DEBUG brain_restart");
	boardInit();
	evaluationInit(width, height);
	initHistoryTable(width, height);
	pipeOut((char *)"OK");
}

int isFree(int x, int y)
{
	return x >= 0 && y >= 0 && x < width && y < height && Square(x, y)->z == EMPTY_MOVE;
}

void brain_my(int x, int y)
{
	pipeOut((char *)"DEBUG brain_my [%d,%d]", x, y);
	if (isFree(x, y))
	{
		SetChessOnBoard(x, y, TURN_MOVE);
	}
	else
	{
		pipeOut((char *)"ERROR my move [%d,%d]", x, y);
	}
}

void brain_opponents(int x, int y)
{
	pipeOut((char *)"DEBUG brain_opponents [%d , %d]", x, y);
	if (isFree(x, y))
	{
		SetChessOnBoard(x, y, OPPONENT_MOVE);
	}
	else
	{
		pipeOut((char *)"ERROR opponents's move [%d,%d]", x, y);
	}
}

void brain_block(int x, int y)
{
	if (isFree(x, y))
	{
		SetChessOnBoard(x, y, OUTSIDE_MOVE);
	}
	else
	{
		pipeOut((char *)"ERROR winning move [%d,%d]", x, y);
	}
}

int brain_takeback(int x, int y)
{
	pipeOut((char *)"DEBUG brain_takeback [%d , %d]", x, y);
	if (!isFree(x, y))
	{
		SetChessOnBoard(x, y, EMPTY_MOVE);
		return 0;
	}
	return 2;
}

#define MATCH_SPARE 7

DWORD stopTime()
{
	return start_time + std::min(info_timeout_turn, info_time_left / MATCH_SPARE) - 30;
}

void brain_turn()
{
	pipeOut((char *)"DEBUG brain_turn");

	IterDeeping();
}

void brain_end()
{
	freeResource();
}

#ifdef DEBUG_EVAL
#include <windows.h>

void brain_eval(int x, int y)
{
	HDC dc;
	HWND wnd;
	RECT rc;
	char c;
	wnd = GetForegroundWindow();
	dc = GetDC(wnd);
	GetClientRect(wnd, &rc);
	c = (char)(board[x][y] + '0');
	TextOut(dc, rc.right - 15, 3, &c, 1);
	ReleaseDC(wnd, dc);
}

#endif

void IterDeeping()
{

	int nMinTimer = GetTickCount() + int((std::min(info_timeout_turn, info_time_left / MATCH_SPARE) - 30) * 0.618f);
	reSetHistoryTable(width, height);

	Mov resultMov;

	for (int depth = 1; depth < 20; (depth < 4 ? depth *= 2 : depth += 1))
	{
		bestMove.val = -10000;
		pipeOut((char *)"DEBUG MAX depth:%d,", depth);

		int score;

		score = alphabeta(depth, -9999, 9999, 0, depth);
		pipeOut((char *)"DEBUG Depth value:%d", score);
		pipeOut((char *)"DEBUG BestMove:[%d,%d],%d", bestMove.x, bestMove.y, bestMove.val);
		pipeOut((char *)"DEBUG Time use:%d,time left:%d", GetTickCount() - start_time, info_timeout_turn - (GetTickCount() - start_time));

		if (terminate)
			break;

		if (GetTickCount() > nMinTimer)
			break;

		if (score == 9999)
			break;
	}
	do_mymove(bestMove.x, bestMove.y);
}

int NegaMax(int depth, int player, int MaxDepth)
{
	if (depth <= 0)
	{
		return evaluate(player);
	}

	int bestMoveIndex = -1;
	int bestVal = -10000;
	int moveListLen = 0;
	Mov *moveList = GenerateMoves(moveListLen, player);

	if (moveListLen == 0)
	{
		pipeOut((char *)"gen movelist is empty");
		delete[] moveList;
		moveList = NULL;
		return evaluate(player);
	}
	for (int i = 0; i < moveListLen; i++)
	{
		moveList[i].val = getHistoryScore(moveList[i], player);
	}

	moveList = MergeSort(moveList, moveListLen);

	for (int i = 0; i < moveListLen; i++)
	{
		if (terminate || GetTickCount() >= stopTime())
		{
			pipeOut((char *)"DEBUG It's time to terminate");
			break;
		}

		MakeMove(moveList[i], player);

		if (isGameOver(moveList[i]))
		{
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
			UnmakeMove(moveList[i]);
			delete[] moveList;
			moveList = NULL;
			return 9999;
		}

		moveList[i].val = -NegaMax(depth - 1, 1 - player, MaxDepth);

		UnmakeMove(moveList[i]);

		if (bestVal < moveList[i].val)
		{

			bestVal = moveList[i].val;
			bestMoveIndex = i;
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
		}
	}

	if (bestMoveIndex != -1)
	{
		enterHistoryScore(moveList[bestMoveIndex], depth, player);
	}

	if (depth == MaxDepth)
	{
		bestMove = moveList[bestMoveIndex];
	}
	delete[] moveList;
	moveList = NULL;

	return bestVal;
}

void SimpleSearch()
{
	Mov resultMov;
	int depth = 4;

	bestMove.val = -10000;
	int score;
	score = NegaMax00(depth, 0, depth);
	pipeOut((char *)"DEBUG Depth value:%d", score);
	pipeOut((char *)"DEBUG BestMove:[%d,%d],%d", bestMove.x, bestMove.y, bestMove.val);
	do_mymove(bestMove.x, bestMove.y);
}

int NegaMax00(int depth, int player, int MaxDepth)
{
	if (depth <= 0)
	{
		return evaluate(player);
	}

	int bestMoveIndex = -1;
	int bestVal = -10000;
	int moveListLen = 0;
	Mov *moveList = GenerateMoves(moveListLen, player);

	if (moveListLen == 0)
	{
		pipeOut((char *)"gen movelist is empty");
		delete[] moveList;
		moveList = NULL;
		return evaluate(player);
	}

	for (int i = 0; i < moveListLen; i++)
	{
		if (terminate || GetTickCount() >= stopTime())
		{
			pipeOut((char *)"DEBUG It's time to terminate");
			break;
		}

		MakeMove(moveList[i], player);

		if (isGameOver(moveList[i]))
		{
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
			UnmakeMove(moveList[i]);
			delete[] moveList;
			moveList = NULL;
			return 9999;
		}

		moveList[i].val = -NegaMax(depth - 1, 1 - player, MaxDepth);

		UnmakeMove(moveList[i]);

		if (bestVal < moveList[i].val)
		{

			bestVal = moveList[i].val;
			bestMoveIndex = i;
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
		}
	}

	if (depth == MaxDepth)
	{
		bestMove = moveList[bestMoveIndex];
	}
	delete[] moveList;
	moveList = NULL;

	return bestVal;
}

int alphabeta(int depth, int alpha, int beta, int player, int MaxDepth)
{
	if (depth <= 0)
	{
		return evaluate(player); //游戏结束，返回估值
	}

	int bestMoveIndex = -1;
	int bestVal = -10000;
	int moveListLen = 0;
	Mov *moveList = GenerateMoves(moveListLen, player);

	if (moveListLen == 0)
	{
		pipeOut((char *)"gen movelist is empty");
		delete[] moveList;
		moveList = NULL;
		return evaluate(player);
	}

	for (int i = 0; i < moveListLen; i++)
	{
		moveList[i].val = getHistoryScore(moveList[i], player);
	}

	moveList = MergeSort(moveList, moveListLen);

	for (int i = 0; i < moveListLen; i++) //对每一个可能的走法
	{
		if (terminate || GetTickCount() >= stopTime())
		{
			pipeOut((char *)"DEBUG It's time to terminate");
			break;
		}

		MakeMove(moveList[i], player); //产生子节点，递归搜索子节点

		if (isGameOver(moveList[i]))
		{
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
			UnmakeMove(moveList[i]);
			delete[] moveList;
			moveList = NULL;
			return evaluate(player);
		}

		moveList[i].val = -alphabeta(depth - 1, -beta, -alpha, 1 - player, MaxDepth);

		UnmakeMove(moveList[i]); //撤销搜索过的子节点

		if (moveList[i].val > alpha)
		{
			alpha = bestVal = moveList[i].val; //保存最大值
			bestMoveIndex = i;
			if (depth == MaxDepth)
			{
				bestMove = moveList[i];
			}
		}
		if (alpha >= beta)
		{
			break; //beta剪枝
		}

		// if (moveList[i].val > bestVal)
		// {
		// 	bestVal = moveList[i].val;
		// 	bestMoveIndex = i;
		// 	if (depth == MaxDepth)
		// 	{
		// 		bestMove = moveList[i];
		// 	}
		// }
		// if (bestVal > alpha)
		// {
		// 	alpha = bestVal;
		// }
		// if (alpha >= beta)
		// {
		// 	break;
		// }
	}
	if (bestMoveIndex != -1)
	{
		enterHistoryScore(moveList[bestMoveIndex], depth, player);
	}
	if (depth == MaxDepth)
	{
		bestMove = moveList[bestMoveIndex];
	}
	delete[] moveList;
	moveList = NULL;

	return alpha;
}

Mov *GenerateMoves(int &moveLen, int player)
{
	int range = 3;
	int count = 0;
	Psquare p = boardb;

	Mov *result = new Mov[width * height];

	int *makeSign = new int[width * height];
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			makeSign[i * width + j] = 0;
		}
	}

	while (p != boardk)
	{
		if (p->z == TURN_MOVE || p->z == OPPONENT_MOVE)
		{
			for (int i = (p->x - range < 0 ? 0 : p->x - range); i <= (p->x + range > width ? width : p->x + range); i++)
			{
				for (int j = (p->y - range < 0 ? 0 : p->y - range); j <= (p->y + range > height ? height : p->y + range); j++)
				{

					if (Square(i, j)->z == EMPTY_MOVE && makeSign[i * width + j] == 0)
					{
						makeSign[i * width + j] = 1;
						if (isBan(Square(i, j), player))
						{
							continue;
						}
						result[count].x = i;
						result[count].y = j;
						result[count].val = 0;
						count++;
					}
				}
			}
		}
		p = (Psquare)(((char *)p) + sizeof(Tsquare));
	}

	delete[] makeSign;

	if (count == 0)
	{
		if (Square(0, 0)->z == EMPTY_MOVE)
		{
			srand(GetTickCount());
			int rndX = rand() % width;
			int rndY = rand() % height;
			for (int i = (rndX - range < 0 ? 0 : rndX - range); i <= (rndX + range > width ? width : rndX + range); i++)
			{
				for (int j = (rndY - range < 0 ? 0 : rndY - range); j <= (rndY + range > height ? height : rndY + range); j++)
				{
					makeSign[i * width + j] = 1;
					result[count].x = i;
					result[count].y = j;
					result[count].val = 0;
					count++;
				}
			}
		}
	}

	moveLen = count;
	return result;
}

Mov mov_rd(Mov *moveList, int count)
{
	srand(GetTickCount());
	int num = rand() % count;

	return moveList[num];
}

bool isBan(Psquare p0, int player)
{

	if (info_fb_check && player == firstPlayer)
	{
		ChessAnalyzeData checkData[4];
		p0->z = player + 1;
		int fb_type = ForbiddenCheck(checkData, p0);
		p0->z = EMPTY_MOVE;

		if (fb_type != NO_FORBIDDEN)
		{
			return true;
		}
	}
	return false;
}

bool isGameOver(Mov move)
{
	Psquare p0 = Square(move.x, move.y);

	for (int i = 0; i < 4; i++)
	{
		int s = diroff[i];
		Psquare pPrv = p0;
		Psquare pNxt = p0;
		int count = -1;
		do
		{
			prvP(pPrv, 1);
			count++;
		} while (pPrv->z == p0->z);
		do
		{
			nxtP(pNxt, 1);
			count++;
		} while (pNxt->z == p0->z);

		if (count == 5)
			return true;
		else if (count > 5 && !info_exact5)
			return true;
	}
	return false;
}

void freeResource()
{
	delete[] PosValue;
	PosValue = NULL;

	delete[] m_nRecord;
	m_nRecord = NULL;
};