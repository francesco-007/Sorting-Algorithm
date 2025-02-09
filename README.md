# Sorting Algorithms in C

## 📌 Overview
This project implements three fundamental sorting algorithms in C: **Bubble Sort, Heap Sort, and Merge Sort**. The program is designed to handle both **integer** and **string** sorting, making it a versatile tool for understanding different sorting techniques.

## 🚀 Features
- ✅ **Bubble Sort**: A simple comparison-based algorithm that repeatedly swaps adjacent elements if they are in the wrong order.
- ✅ **Heap Sort**: A more efficient sorting method that uses a binary heap data structure to sort elements.
- ✅ **Merge Sort**: A divide-and-conquer algorithm that splits the data into smaller subarrays and merges them back in order.
- ✅ **Sorting for both Integers and Strings**: The program allows users to sort lists of integers and strings using the implemented sorting algorithms.


## The program is started using the following command-line arguments:

./sorting <algorithm> <datatype> <count> <list>

Explanation of Arguments:

<algorithm>: The sorting algorithm to use. Valid options are:

bubble: Use Bubble Sort.

merge: Use Merge Sort.

heap: Use Heap Sort.

<datatype>: The type of data to sort. Valid options are:

int: For integers.

string: For strings.

<count>: The number of elements in the array (any positive integer).

<list>: The array to sort, consisting of elements separated by commas (,). Ensure that:

The elements match the specified datatype.

There are no spaces between the elements.

**Example Output**

Command line: ./sorting bubble int 3 3,2,1<br>
[3, 2, 1]<br>
--- Start sorting ---<br>
[2, 1, 3]<br>
[1, 2, 3]<br>
--- Finished sorting ---<br>
[1, 2, 3]<br>
