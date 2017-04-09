#pragma once

#include "TXLib.h"
#define bigger(a, b) (a > b)? a : b

void ROL (  int data [], int Size);
void ROR (  int data [], int Size, int first, int last);
void Gen (  int data [], int Size, bool ifrand, int RSize);
void Bubble (  int data [], int Size);
void Exchange(int data [], int Size, int a, int b);
void REV (  int data [], int Size);
int  MinPos (int data [], int Size, int start);
void Selection (int data [], int Size);
void Print (int data [], int size);
void SortGraph(void (*Func)(int [], int), COLORREF g1, COLORREF g2);
void AB(int arr[], int size, int end1);
int Find(int data[], int size, int el);
int BinarySearch(int arr[], int size, int now);


int Exchanges;
int Scans;

//=======================================================================
// Функция распечатки. Нужна для распечатки массивов.
//=======================================================================

void Print (int data [], int size)
    {
		for (int i = 0; i < size; i++)
		{
			printf(" = %d, ", data[i]);
		}


    printf (" \n");
    }

//=======================================================================
// Функция движения массива влево.
//=======================================================================

void ROL (int data [], int Size)
    {

    Gen (data, Size, true, Size);

    int i = 0;


    int last = data [0];


    while (i < Size)
        {

        data [i] = data [i + 1];

        i++;

        }

    data [Size - 1] = last;

    }

//=======================================================================
// Функция движения массива вправо.
//=======================================================================

void ROR (int data [], int Size, int first, int last)
    {

    Gen (data, Size, true, Size);

    int i = first;

    int help = data [last];


    while (i <= last)
        {

        data [last - 1 - i] = data [last - i - 2];

        i++;

        }

    data [first] = help;

    }


//=======================================================================
// Функция заполнения массива. ifrand - чтобы был полностью рандоминый.
//=======================================================================

void Gen (int data [], int Size, bool ifrand, int RSize)
    {

    if (ifrand == true) srand(time(0));

    int i = 0;

    while (i < Size)
        {

        data [i] = rand()%RSize;

        i++;

        }

    }

//=======================================================================
// Функция обмена двух элементов (Swap).
//=======================================================================

void Exchange(int data [], int Size, int a, int b)
    {

    assert (a < Size);
    assert (b < Size);

    int d = data [a];
    data [a] = data [b];
    data [b] = d;

	Exchanges++;

    }

//=======================================================================
// Функция реверса.
//=======================================================================

void REV (int data [], int size, int left, int right)
    {
    int i = left;

    while (i < right)
        {

        Exchange (data, size, i, right - i - 1);


        $(i) += 1;

        }

    }

//=======================================================================
// Функия поиска позиции
//=======================================================================

int MinPos (int data [], int Size, int start)
    {

    int i = start + 1;
    int Min = start;

    while (i < Size)
        {
        if (data [i] < data [Min])
            {
            Min = i;
            }
        Scans++;
        i++;
        }

    return Min;
    }

//-----------------------------------------------------------------------------

void Selection (int data [], int Size)
    {
    int start = 0;
    Exchanges = 0;
	Scans = 0;


    while (start < Size)
        {

        Exchange (data, Size, MinPos(data, Size, start), start);

        start++;

        }
    }

//-----------------------------------------------------------------------------

void SortGraph(void (*Func)(int [], int), COLORREF g1, COLORREF g2)
	{

	int data[512] = {};

	txSetColor(g1, 2);

	int old_x = 0, old_y = 0, new_x = 0, new_y = 0;



	for (int x = 0; x < sizearr(data); x++)
		{

		Gen(data, x, false, 100);

		Func(data, x);

		int y = Exchanges;

		new_x = 50 + x;
		new_y = 950 - y;

		if (new_x > 50 && new_x < 750 && new_y > 250 && new_y < 950 &&
			old_x > 50 && old_x < 750 && old_y > 250 && old_y < 950)
		{
			txLine(old_x, old_y, new_x, new_y);
			if (new_x % 50 == 0) txCircle(new_x, new_y, 5);
		}

		old_x = new_x;
		old_y = new_y;

		}

	old_x = 0;
    old_y = 0;
    new_x = 0;
    new_y = 0;

	txSetColor(g2, 2);


	for (int x = 0; x < sizearr(data); x++)
		{

		Gen(data, x, false, 100);

		Func(data, x);

		int y = Scans;

		new_x = 50 + x;
		new_y = 950 - y;

		if (new_x > 50 && new_x < 750 && new_y > 250 && new_y < 950 &&
			old_x > 50 && old_x < 750 && old_y > 250 && old_y < 950) txLine(old_x, old_y, new_x, new_y);


		old_x = new_x;
		old_y = new_y;
        }

	while (txMouseButtons() != 1);

	}

//-----------------------------------------------------------------------------

void AB(int arr[], int size, int end1)
    {
    REV(arr, size, 0, size);
    Print(arr, size);
    REV(arr, size, 0, end1);
    Print(arr, size);
    REV(arr, size, end1, size);

    }

//-----------------------------------------------------------------------------

void BubbleSort (int data [], int Size)
	{
	int swaps = 0;
	int comparisons = 0;
	Exchanges = 0;
	Scans = 0;

	while (true)
    	{
    	int i = 0;
    	int changes = 0;
    	int compares = 0;

    	while (i < Size - 1)
        	{
        	if (data [i]  > data [i+1])
            	{
            	Exchange (data, Size, i, i+1);
            	changes ++;
            	}
        	Scans++;
        	i++;
        	}
    	comparisons = comparisons + compares;
    	if (changes == 0) break;
    	}

	}

//-----------------------------------------------------------------------------

void QuickSort (int data[], int size, int left, int right)
    {
    int mid = (left + right)/ 2;
    int count1 = left;
    int count2 = right;

    while (count1 <= count2)
        {
        while (data[count1] < data[mid])
            {
            count1++;
            }
        while (data[count2] > data[mid])
           {
            count2--;
            }
        if (count1 <= count2)
            {
            Exchange (data, size, count1, count2);
            count1++;
            count2--;
            }
        Scans++;
        }
    if (count1 < right)
        {
        QuickSort (data, size, count1, right);
        }
    if (count2 > left)
       {
        QuickSort (data, size, left, count2);
       }
    Scans+=2;
    }

//-----------------------------------------------------------------------------

void QuickSortGraph(COLORREF g1, COLORREF g2)
	{

	int data[700] = {};

	txSetColor(g1, 2);

	int old_x = 0, old_y = 0, new_x = 1, new_y = 1;



	for (int x = 1; x < sizearr(data); x++)
		{

		Gen(data, x, false, 100);

		Exchanges = 0;
        Scans = 0;

		QuickSort(data, x, 0, x - 1);

		int y = Exchanges;

		new_x = 50 + x;
		new_y = 950 - y;

		if (new_x > 50 && new_x < 750 && new_y > 250 && new_y < 950 &&
			old_x > 50 && old_x < 750 && old_y > 250 && old_y < 950) 
		{
			txLine(old_x, old_y, new_x, new_y);
			if (new_x % 50 == 0) txCircle(new_x, new_y, 5);
		}
		

		old_x = new_x;
		old_y = new_y;
		}

    old_x = 0;
    old_y = 0;
    new_x = 0;
    new_y = 0;

	txSetColor(g2, 2);

    for (int x = 1; x < sizearr(data); x++)
        {

        Gen(data, x, false, 100);

        Exchanges = 0;
        Scans = 0;

        QuickSort(data, x, 0, x-1);

        int y = Scans;

        new_x = 50 + x;
        new_y = 950 - y;

		if (new_x > 50 && new_x < 750 && new_y > 250 && new_y < 950 &&
			old_x > 50 && old_x < 750 && old_y > 250 && old_y < 950) txLine(old_x, old_y, new_x, new_y);

		
        old_x = new_x;
        old_y = new_y;
        }

	//while (txMouseButtons() != 1);

	}

//-----------------------------------------------------------------------------

void InsertionSort (int data[], int size)
    {

    Exchanges = 0;

    Scans = 0;

    int i = 0;
    while (i <= size)
        {
        ROR (data, size, BinarySearch(data, size, i), i);
        i++;
        }
    }

//-----------------------------------------------------------------------------

int Find (int data[], int size, int el)
    {
    int i = el - 1;
    while (i >= 0)
        {
        if (data[i] == data[el])
            {
            return i;
            }
        if (data[i] < data[el])
            {
            return i + 1;
            }

        Scans+=2;

        i--;
        }
    return 0;
    }

//-----------------------------------------------------------------------------

int BinarySearch(int arr[], int size, int now)
{
	int left = 0; int right = now;

	if (arr[now] < arr[0])
		return 0;

	while (right - left > 1)
	{
		if (arr[(right + left) / 2] == arr[now])
			return (right + left) / 2;
		if (arr[(right + left) / 2] > arr[now])
			right = (right + left) / 2;
		else
			left = (right + left) / 2;
	}



	return bigger(right, left);

}

//----------------------------------------------------------------------------
