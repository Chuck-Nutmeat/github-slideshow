#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <mmsystem.h>  // mciSendString()
#include <conio.h>
#pragma comment(lib, "winmm.lib")
//play sound, wait, then play other sound

struct food
{
	int x;
	int y;
};

struct snakeSegment
{
	bool isHead;
	int x;
	int y;
	snakeSegment* next;
	snakeSegment* prev;
};

struct snakeSegment* createHead(int startX, int startY)
{
	snakeSegment* head = new snakeSegment;
	head->x = startX;
	head->y = startY;
	head->next = nullptr;
	head->prev = nullptr;
	head->isHead = true;
	return head;
}


snakeSegment* newTail(snakeSegment* tail) // New tail is added when food is eaten
{
	snakeSegment* newSegment = new snakeSegment;
	snakeSegment* prevPtr = new snakeSegment;
	newSegment->x = tail->x;
	newSegment->y = tail->y;
	prevPtr = tail;
	tail->next = newSegment;
	tail = newSegment;
	tail->prev = prevPtr;
	tail->next = nullptr;
	tail->isHead = false;  
	return tail;
}



//snakeSegment* newHead(snakeSegment* head, snakeSegment* newSegment, int direction) // New head is added in direction of snakes motion 
//{
//	snakeSegment* nextPtr = new snakeSegment;
//
//	switch (direction)
//	{
//	case 0:	
//		newSegment->x = head->x;
//		newSegment->y = head->y + 1;
//		break;
//	case 1:
//		newSegment->x = head->x;
//		newSegment->y = head->y - 1;
//		break;
//	case 2:
//		newSegment->x = head->x - 1;
//		newSegment->y = head->y;
//		break;
//	case 3:
//		newSegment->x = head->x + 1;
//		newSegment->y = head->y;
//		break;
//	default:
//		break;
//	}
//
//	nextPtr = head;
//	head->prev = newSegment;
//	head = newSegment;
//	head->next = nextPtr;
//	head->prev = nullptr;
//	return head;
//}

void movePlayer(int dir, int * playerX, int * playerY)
{
	
	switch (dir)
	{
	case 0:
	{
		*playerY = (*playerY - 1);
		break; 
	}
	case 1:
	{
		*playerY = *playerY + 1;
		break;
	}
	case 2:
	{
		*playerX -= 2;
		break;
	}
	case 3:
	{
		*playerX += 2;
		break;
	}
	default:
		break;
	}
}

void moveSnake(int dir, struct snakeSegment* head)
{
	snakeSegment* ptr = head;

	if (ptr->next != nullptr)        // If head has another piece attached ie. if head is not a single segment
	{
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;         // Moves pointer to tail
		}
									 // Pointer now at tail
		while (!ptr->isHead)
		{                            // Changes xy position to that of the previous piece from tail to head
			ptr->x = ptr->prev->x;
			ptr->y = ptr->prev->y;
			ptr = ptr->prev;
		}
	}

	switch (dir)                    // Moves head
	{
	case 0:         //UP
	{
		head->y = head->y - 1;
		break;
	}
	case 1:			//DOWN
	{
		head->y = head->y + 1;
		break;
	}
	case 2:			//LEFT
	{
		head->x = head->x - 1;
		break;
	}
	case 3:			//RIGHT
	{
		head->x = head->x + 1;
		break;
	}
	}
}