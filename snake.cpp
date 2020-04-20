#include "snake.h"
using namespace std;

int nScreenWidth = 80;
int nScreenHeight = 30;

int fPlayerX = 60;  // Starting coordinates for snake head
int fPlayerY = 20;

int main(void)
{
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while(1)
	{
		int direction = 2; // UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
		bool dead = false;

		int score = 0;
		int foodX = 20;
		int foodY = 20;

		snakeSegment * head = new snakeSegment;       // Initialize snake head
		head->x = fPlayerX;
		head->y = fPlayerY;
		head->next = nullptr;
		head->prev = nullptr;
		head->isHead = true;

		snakeSegment* tail = new snakeSegment;        // Initialize tail
		tail->x = fPlayerX - 1;
		tail->next = nullptr;
		tail->y = fPlayerY;
		tail->prev = head;
		tail->isHead = false;

		head->next = tail;

		tail = newTail(tail);
		
		

		

		while (!dead)
		{

			//Controls
			if ((GetAsyncKeyState((unsigned short)VK_UP) & 0x8000) && direction != 1)
			{
				direction = 0;
			}

			if ((GetAsyncKeyState((unsigned short)VK_DOWN) & 0x8000) && direction != 0)
			{
				direction = 1;
			}

			if ((GetAsyncKeyState((unsigned short)VK_LEFT) & 0x8000) && direction != 3)
			{
				direction = 2;
			}
			if ((GetAsyncKeyState((unsigned short)VK_RIGHT) & 0x8000) && direction != 2)
			{
				direction = 3;
			}

			moveSnake(direction, head);

			// Collision detection
			if (screen[head->y * nScreenWidth + head->x] == L'|' || screen[head->y * nScreenWidth + head->x] == L'-' || screen[head->y * nScreenWidth + head->x] == L'O')
				dead = true;

			// Detects food pickup
			if (head->x == foodX && head->y == foodY)
			{
				while (screen[foodY * nScreenWidth + foodX] != L' ')
				{
					foodX = rand() % nScreenWidth;
					foodY = rand() % (nScreenHeight - 3) + 3;
				}
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				tail = newTail(tail);
				

				score++;
			}

			// Draws frame
			for (int x = 0; x < nScreenWidth; x++)
				for (int y = 0; y < nScreenHeight; y++)
				{
					
					wsprintf(&screen[nScreenWidth + 5], L"SNAKE BY REX!                          SCORE: %d", score);

					if (y == 0 || y == 2 || y == nScreenHeight - 1)
						screen[y * nScreenWidth + x] = L'-';
					else if (x == 0 || x == nScreenWidth - 1)
						screen[y * nScreenWidth + x] = L'|';
					else
						screen[y * nScreenWidth + x] = L' ';

					if (x == foodX && y == foodY)
						screen[y * nScreenWidth + x] = L'@';

					if (x == head->x && y == head->y)
						screen[y * nScreenWidth + x] = dead ? L'X' : L'P';

					if (dead)
					{
						wsprintf(&screen[(nScreenHeight/2) * nScreenWidth + 30], L"*PRESS SPACE TO CONTINUE*");
						//play game over sound
						mciSendString(L"play C:\\Users\\rswin\\source\\repos\\SnakeGame\\gameoverman.wav", NULL, 0, NULL);
					}

					if (head->next != nullptr)
					{
						snakeSegment* ptr = head->next;
						while (ptr != nullptr)
						{
							if (x == ptr->x && y == ptr->y)
								screen[y * nScreenWidth + x] = dead ? L'+' : L'O';

							ptr = ptr->next;
						}
					}


				}



			// Display Frame
			screen[nScreenWidth * nScreenHeight - 1] = L'\0';
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			Sleep(75);

		}
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
	}
	
	

	return 0;
}