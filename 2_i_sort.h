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
		int n = vec.size();
		for (int i = 0; i < n - 1; i++) {
			bool is_sorted = true;
			for (int j = 0; j < n - i - 1; j++) {
				num_comparisons++;
				if ((ascending_or_descending == 1 && vec[j] > vec[j + 1]) ||
					 (ascending_or_descending != 1 && vec[j] < vec[j + 1])) {
					std::swap(vec[j], vec[j + 1]);
					num_permutations++;
					is_sorted = false;
				}
			}
			if (is_sorted) break;
		}
	}
};

class selection_sort : public ISort {
public:
	selection_sort() : ISort() {}

	void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override
	{
		int n = vec.size();
		for (int i = 0; i < n - 1; i++) {
			int extreme_index = i;
			for (int j = i + 1; j < n; j++) {
				num_comparisons++;
				if ((ascending_or_descending == 1 && vec[j] < vec[extreme_index]) ||
					(ascending_or_descending != 1 && vec[j] > vec[extreme_index])) {
					extreme_index = j;
				}
			}
			if (i != extreme_index) {
				std::swap(vec[i], vec[extreme_index]);
				num_permutations++;
			}
		}
	}
};

class insertion_sort : public ISort {
public:
	insertion_sort() : ISort() {}

  void Sort(std::vector<int>& vec, int& num_comparisons, int& num_permutations, int ascending_or_descending) override {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
      int insert = vec[i];
			int j = i - 1;
        while (j >= 0 && ((ascending_or_descending == 1 && vec[j] > insert) ||
                          (ascending_or_descending != 1 && vec[j] < insert))) {
          num_comparisons++;
          vec[j + 1] = vec[j];
          j--;
          num_permutations++;
        }
        vec[j + 1] = insert;
        num_permutations++;
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