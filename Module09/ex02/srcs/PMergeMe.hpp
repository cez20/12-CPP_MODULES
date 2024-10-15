#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>
# include <deque>
# include <algorithm>
# include <array>


class PMergeMe
{
	public:
		PMergeMe();
		PMergeMe( PMergeMe const & src );
		~PMergeMe();

		PMergeMe &		operator=( PMergeMe const & rhs );

		void			processArguments(int argCount, char **argList);
		void			initializeContainers();
		
		void			mergeInsertionSort();
		template<typename T>
		void			sortPairs(T & container);
		template<typename T>
		void   			mergeSortRecursive(T & container, size_t left, size_t right);
		template<typename T>
		void			mergeSort(T & container, const size_t left, const size_t middle, const size_t right);

		void			printInitialIntSequence();
		template <typename T>
		void			printContainer(T & container);

		bool			isArraySizeOdd();
		
	private:
		std::clock_t 			_start;
		std::vector<double>		_myVector;
		std::deque<double>		_myDeque;
		std::list<double>		_initialSequence;
		std::vector<int>		_smallestElementIndexes;
		std::vector<int>		_largestElementIndexes;
		int						_unpairedElement;
		// size_t					_myVectorSortTime;
		// size_t					_myDequeSortTime;
};

double  stringToDouble(const std::string& s);
bool 	isValidNumberFormat (const std::string& arg);
bool 	isBelowIntMax(const std::string& arg);



#endif /* ******************************************************** PMERGEME_H */