#pragma once

enum class GuessResult {
	Great,
	Sorry,
};

GuessResult guess(int value);
void confirm(int value);

void player_B();
