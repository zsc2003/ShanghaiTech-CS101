#include "guess.h"
#include <assert.h>
#include <stdio.h>

static int secret;
static int guesses;
static int answer;

GuessResult guess(int value) {
  guesses++;
  return secret == value ? GuessResult::Great : GuessResult::Sorry;
}
void confirm(int value) { answer = value; }

int main() {
  scanf("%d", &secret);
  assert(secret >= 0);

  player_B();

  printf("%d %d", answer, guesses);

  return 0;
}
