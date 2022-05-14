#ifndef __CONCERTLISTS_H
#define __CONCERTLISTS_H


// ����� �� ��� �� ����� ����� ���� ������� ����
// CILists


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct concertInstrument
{
	int num; // ��� ����� ���
	int inst; // ���� ���� �� ��� �����
	char importance; // (1 / 0) ��� ���� ����� �� �� ����� ���� ����� �����
} ConcertInstrument;


typedef struct CIlistNode
{
	ConcertInstrument CI; // concert instrument
	struct CIlistNode* next;
} CIListNode;

typedef struct CIlist
{
	CIListNode* head;
	CIListNode* tail;
} CIList;

typedef int BOOL;
#define FALSE 0
#define TRUE 1

void printCIList(CIList* lst);
//CIList listConcat(CIList* l1, CIList* l2);
void makeEmptyCIList(CIList* lst);
BOOL isEmptyCIList(CIList* lst);
void insertNodeToEndCIList(CIList* lst, CIListNode* tail);
void insertDataToEndCIList(CIList* lst, int id, int amount, int importance);
CIListNode* createNewCIListNode(int id, int amount, int importance, CIListNode* next);


#endif
