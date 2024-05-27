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
		size_t n = vec.size();
		
		for (size_t i = 0; i < n; i++) {
			bool swapped = false;
			size_t min_in = i;
			for (size_t j = 0; j < n - 1; j++) {
				num_comparisons++;
				if ((ascending_or_descending == 1 && vec[j] > vec[min_in]) ||
					(ascending_or_descending != 1 && vec[j] < vec[min_in])) {
					std::swap(vec[j], vec[min_in]);
					num_permutations++;
					swapped = true;
				}
			}
			if (!swapped) break;
		}
	}
};

class insertion_sort : public ISort {
public:
	insertion_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		size_t n = vec.size();
		int key = 0, j = 0, n_p = 0, n_c = 0;
		for (size_t i = 1; i < n; i++) {
			key = vec[i];
			j = i - 1;
			bool swapped = false;
			while (j >= 0 && ((ascending_or_descending == 1 && vec[j] > key) ||
				    (ascending_or_descending != 1 && vec[j] < key))) {
				vec[j + 1] = vec[j];
				j--;
				num_comparisons++;
				swapped = true;
			}
			vec[j + 1] = key;
			if (swapped) num_permutations++;
		}
	}
};


class shell_sort : public ISort {
public:
	shell_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override {
		int n = vec.size();
		for (int gap = n / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i += 1) {
				int insert = vec[i];
				int j;
				for (j = i; j >= gap && ((ascending_or_descending == 1 && vec[j - gap] > insert) ||
					(ascending_or_descending != 1 && vec[j - gap] < insert)); j -= gap) {
					num_comparisons++;
					vec[j] = vec[j - gap];
					num_permutations++;
				}
				vec[j] = insert;
				num_permutations++;
			}
		}
	}
};

class quick_sort : public ISort {
public:
	quick_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override {
		recursive_sort(vec, 0, vec.size() - 1, num_comparisons, num_permutations, ascending_or_descending);
	}

private:
	void recursive_sort(std::vector<int>& vec, int low, int high, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		if (low < high) {
			int pivot = partition(vec, low, high, num_comparisons, num_permutations, ascending_or_descending);
			recursive_sort(vec, low, pivot - 1, num_comparisons, num_permutations, ascending_or_descending);
			recursive_sort(vec, pivot + 1, high, num_comparisons, num_permutations, ascending_or_descending);
		}
	}

	int partition(std::vector<int>& vec, int low, int high, int& num_comparisons, int& num_permutations, int ascending_or_descending) {
		int pivot = vec[(low + high) / 2];
		int i = low - 1;
		int j = high + 1;
		while (true) {
			do {
				i++;
				num_comparisons++;
			} while ((ascending_or_descending == 1 && vec[i] < pivot) ||
				(ascending_or_descending != 1 && vec[i] > pivot));

			do {
				j--;
				num_comparisons++;
			} while ((ascending_or_descending == 1 && vec[j] > pivot) ||
				(ascending_or_descending != 1 && vec[j] < pivot));

			if (i >= j)
				return j;

			std::swap(vec[i], vec[j]);
			num_permutations++;
		}
	}
};