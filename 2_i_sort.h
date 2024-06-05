#pragma once

#include "0_input_check.h"

class ISort {
public:
	virtual ~ISort() {}

	virtual void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) = 0;
};

class bubble_sort : public ISort {
public:
	bubble_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override
	{
		size_t n = vec.size();

		for (size_t i = 0; i < n; i++) {
			bool swapped = false;
			for (size_t j = 0; j < n - 1; j++) {
				num_comparisons++;
				if ((ascending_or_descending == 1 && vec[j] > vec[j + 1]) ||
					  (ascending_or_descending != 1 && vec[j] < vec[j + 1])) {
					std::swap(vec[j], vec[j + 1]);
					num_permutations++;
					swapped = true;
				}
			}
			if (!swapped) break;
		}
	}
};

class selection_sort : public ISort {
public:
	selection_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override
	{
		int n = static_cast<int>(vec.size());

		if (ascending_or_descending == 1) {
			for (int i = 0; i < n - 1; i++) {
				int min_idx = i;
				bool swapped = false;
				for (int j = i + 1; j < n; j++) {
					num_comparisons++;
					if (vec[j] < vec[min_idx]) { min_idx = j, swapped = true; }
				}
				if (swapped == true) {
					std::swap(vec[min_idx], vec[i]);
					num_permutations++;
				}
			} 
		}
		else {
			for (int i = 0; i < n - 1; i++) {
				int max_idx = i;
				bool swapped = false;
				for (int j = i + 1; j < n; j++) {
					num_comparisons++;
					if (vec[j] > vec[max_idx]) { max_idx = j, swapped = true; }
				}
				if (swapped == true) {
					std::swap(vec[max_idx], vec[i]);
				  num_permutations++;
				}
			}
		}
	}
};

class insertion_sort : public ISort {
public:
	insertion_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		int n = static_cast<int>(vec.size());
		int key = 0;
		int j = 0;
		for (int i = 1; i < n; i++) {
			key = vec[i];
			j = i - 1;
			while (num_comparisons++,j >= 0 && ((ascending_or_descending == 1 &&vec[j] > key) ||
				(ascending_or_descending != 1 && vec[j] < key))) {
				vec[j + 1] = vec[j];
				num_permutations++;
				j--;
			}
			vec[j + 1] = key;
		}
	}
};


class shell_sort : public ISort {
public:
	shell_sort() : ISort() {}


	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		int n = static_cast<int>(vec.size());
		for (int gap = n / 2; gap > 0; gap /= 2)
			for (int i = gap; i < n; i += 1) {
				int insert = vec[i];
				int j;
				bool permuted = false;
				for (j = i; j >= gap; j -= gap) {
					num_comparisons++;
					if ((ascending_or_descending == 1 && vec[j - gap] > insert) ||
						  (ascending_or_descending != 1 && vec[j - gap] < insert)) {
						vec[j] = vec[j - gap];
						permuted = true;
					}
					else break;
				}
				vec[j] = insert;
				if (permuted) num_permutations++;
			}
	}
};


class quick_sort : public ISort {
public:
	quick_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override {
		quickSort(vec, 0, static_cast<int>(vec.size()) - 1, num_comparisons, num_permutations, ascending_or_descending);
	}

private:
	void quickSort(std::vector<int>& vec, int low, int high, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		if (low < high) {
			int pivot = vec[(low + high) / 2];
			int i = low;
			int j = high;

			while (i <= j) {
				while (num_comparisons++,(ascending_or_descending == 1 && vec[i] < pivot) || (ascending_or_descending != 1 && vec[i] > pivot)) {
					i++;
				}
				while (num_comparisons++,(ascending_or_descending == 1 && vec[j] > pivot) || (ascending_or_descending != 1 && vec[j] < pivot)) {
					j--;
				}
				if (i <= j) {
					if (i < j && (vec[i] != vec[j])) {
						std::swap(vec[i], vec[j]);
						num_permutations++;
					}
					i++;
					j--;
				}
			}
			if (low < j)
				quickSort(vec, low, j, num_comparisons, num_permutations, ascending_or_descending);
			if (i < high)
				quickSort(vec, i, high, num_comparisons, num_permutations, ascending_or_descending);
		}
	}
};
