// https://zxbcw.cn/post/218247/

#include <conio.h>
#include <handleapi.h>
#include <processthreadsapi.h>
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

// char HEAD = '@'; // The shape of snake head
// char BODY = 'O'; // The shape of snake body
#define HEAD '@'                                    // The shape of snake head
#define BODY 'O'                                    // The shape of snake body
char a[HEIGHT][WIDTH] = {{BODY, BODY, BODY, HEAD}}; // The initial char is 0
char *p[HEIGHT * WIDTH] = {&a[0][3], &a[0][2], &a[0][1],
                           &a[0][0]}; // p[0] stand for snake head

int n = 3; // The length of snake body (without head)
int i, j;
int direction = 1; // 1.right;2.up;3.left;4.down;-1.exit
int delay = 200;   // delay 0.2s(200ms)
_Bool isPause = 0;
#define moveBody()                                                             \
  {                                                                            \
    *p[n] = 0;                                                                 \
    for (i = n; i > 0; i--) {                                                  \
      p[i] = p[i - 1];                                                         \
      /* per part goes to the address of the next part of body*/               \
    }                                                                          \
    *p[0] = BODY;                                                              \
    /* The First part of snake body come to snake head*/                       \
  }

// https://cloud.tencent.com/developer/article/1790043?from=15425
// https://cloud.tencent.com/developer/article/2132941?from=15425
#define gotoxy(y, x)                                                           \
  {                                                                            \
    COORD coord = {(x), (y)}; /* coord */                                      \
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),                  \
                             coord); /* Move Cursor to coord */                \
  }

void moveRight() {
  moveBody();
  p[0] = p[0] + 1; // Move snake head
  *p[0] = HEAD;    // change the char of new head(new address)'s shape to HEAD
}
void moveLeft() {
  moveBody();
  p[0] = p[0] - 1;
  *p[0] = HEAD;
}
void moveDown() {
  moveBody();
  p[0] = p[0] + WIDTH;
  *p[0] = HEAD;
}
void moveUp() {
  moveBody();
  p[0] = p[0] - WIDTH;
  *p[0] = HEAD;
}

void show() {
  system("clear");
  printf("Your Score is:%d\n", n - 3);
  for (i = 0; i < WIDTH * 2; i++)
    printf("_");
  printf("\n");
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (a[i][j] == 0)
        printf("_|");
      else
        printf("%c|", a[i][j]);
    }
    printf("\n");
  }
  printf("\nw,s,a,d->Up Down Left Right;\nj,k->Speed Up/Down;\nESC: Exit\n");
}

void randomApple() // Random
{
  srand(time(NULL));
  do {
    i = rand() % HEIGHT;
    j = rand() % WIDTH;
    // if random location is 0 ->*;else find again and again
  } while (a[i][j] != 0);
  a[i][j] = '*';
}

void canEat() {
  switch (direction) {
  // Right
  case 1: {
    if (*(p[0] + 1) == '*') {
      n++; // length++
      p[n] = p[n - 1];
      randomApple();
    }
    break;
  }
  // Up
  case 2: {
    if (*(p[0] - WIDTH) == '*') {
      n++; // length++
      p[n] = p[n - 1];
      randomApple();
    }
    break;
  }
  // Left
  case 3: {
    if (*(p[0] - 1) == '*') {
      n++; // length++
      p[n] = p[n - 1];
      randomApple();
    }
    break;
  }
  // Down
  case 4: {
    if (*(p[0] + WIDTH) == '*') {
      n++; // length++
      p[n] = p[n - 1];
      randomApple();
    }
    break;
  }
  }
}

void isFail() {
  if (p[0] - WIDTH < &a[0][0] && direction == 2 ||
      p[0] + WIDTH > &a[HEIGHT - 1][WIDTH - 1] && direction == -2 ||
      direction == 1 && (p[0] - a[0]) % WIDTH == WIDTH - 1 ||
      direction == -1 &&
          (p[0] - a[0]) % WIDTH == 0) // snake is not in the matrix
  {
    printf("fail!\n");
    direction = -1;
  } else {
    switch (direction) {
    // Right
    case 1: {
      for (i = n; i > 0; i--) {
        if ((p[0] + 1) == p[i]) // Right of the head is body
        {
          printf("fail!\n");
          direction = -1;
        }
      }
      break;
    }
    // Up
    case 2: {
      for (i = n; i > 0; i--) {
        if ((p[0] - WIDTH) == p[i]) // Up of the head is body
        {
          printf("fail!\n");
          direction = -1;
        }
      }
      break;
    }
    // Left
    case 3: {
      for (i = n; i > 0; i--) {
        if ((p[0] - 1) == p[i]) // Left of the head is body
        {
          printf("fail!\n");
          direction = -1;
        }
      }
      break;
    }
    // Down
    case 4: {
      for (i = n; i > 0; i--) {
        if ((p[0] + WIDTH) == p[i]) // Down of the head is body
        {
          printf("fail!\n");
          direction = -1;
        }
      }
      break;
    }
    }
  }
}

DWORD WINAPI
KeyMonitor(LPVOID lpParam) // Direction Control：w,s,a,d-->Up Down Left Right
{
  char k;
  while (1) {
    k = _getch();

    switch (k) {
    case 'w': // Up
    {
      if (direction != 4)
        direction = 2;
      break;
    }
    case 's': // Down
    {
      if (direction != 2)
        direction = 4;
      break;
    }
    case 'a': // Left
    {
      if (direction != 1)
        direction = 3;
      break;
    }
    case 'd': // Right
    {
      if (direction != 3)
        direction = 1;
      break;
    }
    case 'j': // SpeedUp
    {
      delay = delay * 4 / 5;
      break;
    }
    case 'k': // SpeedDown
    {
      delay = delay * 5 / 4;
      break;
    }
    case 27: // ESC
    {
      printf("Exit!\n");
      isPause = 0;
      direction = -1;
      return 0;
      break;
    }
    case ' ': // Space
    {
      if (isPause) {
        printf("Continue!\n");
      } else {
        printf("Pause!\n");
      }
      isPause = !isPause;
      break;
    }
    }
  }
}

int main() {

  randomApple();
  HANDLE hThread1 = CreateThread(NULL, 0, KeyMonitor, NULL, 0, NULL);
  while (1) {
    show();
    do {
      Sleep(delay);
    } while (isPause);
    isFail();          // Judge if will eat self
    canEat();          // Judge if will eat *
    switch (direction) // choose which direction to move
    {
    case 1: // Right
    {
      moveRight();
      break;
    }
    case 2: // Up
    {
      moveUp();
      break;
    }
    case 3: // Left
    {
      moveLeft();
      break;
    }
    case 4: // Down
    {
      moveDown();
      break;
    }
    case -1: // Exit
    {
      printf("Your Final Score is:%d\n", n - 3);
      CloseHandle(hThread1);
      return -1;
      break;
    }
    }
  }

  return 0;
}
