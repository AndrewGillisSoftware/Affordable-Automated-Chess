#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <stdbool.h>

#define UNKNOWN_POS -1

#define EMPTY_PIECE 2
#define WHITE_PIECE 1
#define BLACK_PIECE 0
#define NULL 0

#define NUM_OF_SPACES 8

struct Range {
	int from;
	int to;
} Range;

struct Board {
	int tiles[NUM_OF_SPACES];
} Board;

bool initBoard(struct Board* board)
{
	if (board == NULL)
	{
		return false;
	}

	for (int i = 0; i < NUM_OF_SPACES; i++)
	{
		board->tiles[i] = EMPTY_PIECE;
	}

	return true;
}


#endif
