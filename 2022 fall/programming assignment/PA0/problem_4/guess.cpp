#include "guess.h"

void player_B()
{
	if (guess(0) == GuessResult::Great)
	{
		confirm(0);
		return;
 	}
	if (guess(1) == GuessResult::Great)
	{
		confirm(1);
		return;
 	}
	if (guess(2) == GuessResult::Great)
	{
		confirm(2);
		return;
 	}
	if (guess(3) == GuessResult::Great)
	{
		confirm(3);
		return;
 	}
	if (guess(4) == GuessResult::Great)
	{
		confirm(4);
		return;
 	}
	if (guess(5) == GuessResult::Great)
	{
		confirm(5);
		return;
 	}
	if (guess(6) == GuessResult::Great)
	{
		confirm(6);
		return;
 	}
	if (guess(7) == GuessResult::Great)
	{
		confirm(7);
		return;
 	}
	if (guess(8) == GuessResult::Great)
	{
		confirm(8);
		return;
 	}
	confirm(9);
	return
}
