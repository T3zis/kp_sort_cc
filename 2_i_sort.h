#pragma once

#include "0_input_check.h"

class ISort {
public:
	virtual ~ISort() {}

	virtual void Sort(int **matrix, int rows, int columns) = 0;

};

class bubble_sort : public ISort {
public:
	bubble_sort() : ISort() {}

	void Sort(int** matrix, int rows, int columns) override
	{

	}
};

class selection_sort : public ISort {
public:
	selection_sort() : ISort() {}

	void Sort(int** matrix, int rows, int columns) override
	{

	}
};

class insertion_sort : public ISort {
public:
	insertion_sort() : ISort() {}

	void Sort(int** matrix, int rows, int columns) override
	{

	}
};

class shell_sort : public ISort {
public:
	shell_sort() : ISort() {}

	void Sort(int** matrix, int rows, int columns) override
	{

	}
};

class quiq_sort : public ISort
{
public:
	quiq_sort() : ISort() {}

	void Sort(int** matrix, int rows, int columns) override
	{

	}
};