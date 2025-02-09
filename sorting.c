//---------------------------------------------------------------------------------------------------------------------
// a2.c
//
// Bubble, Merge and Heap sorting algorithm program
// Using the command line in the terminal, the user will choose between bubble, merge or heap algoirthm.
// The user can choose either string or integer for the sorting process.
// The user will choose the number of elements inside the array and then will enter the elements that need to be sorted.
//
//
//---------------------------------------------------------------------------------------------------------------------
//
#include <stdio.h>

#define MAX_SIZE 50

void parseDataString(char* data, char arr[][MAX_SIZE], int* number_elements);
void parseDataInt(char* data, int arr[], int* number_elements);
int isValidElement(char* str);
int checkElementCount(int number_elements, char* data);
int atoiFunction(char* str);
int compareStrings(const char* str1, const char* str2);
char* copyString(char *destination, const char* source);

void bubbleSortString(char arr[][MAX_SIZE], int number_elements);
void bubbleSortInt(int arr[], int number_elements);

void mergeString(char arr[][MAX_SIZE], int left, int middle, int right);
void mergeSortString(char arr[][MAX_SIZE], int left, int right, int size);

void mergeInt(int arr[], int left, int middle, int right);
void mergeSortInt(int arr[], int left, int right, int size);

void heapifyString(char arr[][MAX_SIZE], int size, int current_node_index);
void buildHeapString(char arr[][MAX_SIZE], int size);
void heapSortString(char arr[][MAX_SIZE], int size);

void heapifyInt(int arr[], int size, int root_index);
void buildHeapInt(int arr[], int size);
void heapSortInt(int arr[], int size);

int sortingAlgorithmProgram(char* algorithm_name, char* data_type, char* data, int number_elements);

void printArrayStrings(char arr[][MAX_SIZE], int size);
void printArrayIntegers(int arr[], int size);

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the main function. We have 5 arguments on the command line (including the program name itself).
/// Here, different sorting algorithm works depending on the user input.
/// There are some error messages that will be printed in case the user entered a wrong input.
///
/// @param argc Number of arguments on the command line (Including the program name itself).
/// @param argv Pointer to array of C-style strings (Character arrays)
///
///
/// @return sorting_result
//
int main(int argc, char* argv[])
{
  if(argc != 5)
  {
    printf("Usage: %s <algorithm> <type> <count> <data>\n", argv[0]);
    return 1;
  }
  char* algorithm_name = argv[1];
  char* data_type = argv[2];
  char* str_count = argv[3];
  char* data = argv[4];
  if (!isValidElement(str_count))
  {
    printf("Element count is not an integer!\n");
    return 4;
  }
  int number_elements = atoiFunction(str_count);
  if(number_elements < 1)
  {
    printf("Invalid element count!\n");
    return 5;
  }
  int total_elements = checkElementCount(number_elements, data);
  if(total_elements != 0)
  {
    return total_elements;
  }
  if (compareStrings(data_type, "int") != 0 && compareStrings(data_type, "string") != 0) //check again
  {
    printf("Invalid data type!\n");
    return 3;
  }
  int sorting_result = sortingAlgorithmProgram(algorithm_name, data_type, data, number_elements);
  return sorting_result;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the parsing data function for strings.
/// It takes the data entered by the user and then it copies it to the array.
///
/// @param data A Pointer to the data in argv
/// @param arr Array of characters 
/// @param number_elements A pointer to number of elements in argv
///
/// @return none (void)
//
void parseDataString(char* data, char arr[][MAX_SIZE], int* number_elements)
{
  int index = 0;
  int start = 0;
  for(int i = 0; data[i] != '\0'; i++)
  {
    if(data[i] == ',')
    {
      data[i] = '\0';
      copyString(arr[index], &data[start]);
      start = i + 1;
      index++;
    }
  }

  copyString(arr[index], &data[start]);
  *number_elements = index + 1;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the parsing data function for integers.
/// It takes the data entered by the user and then it copies it to the array.
///
/// @param data A Pointer to the data in argv
/// @param arr Array of integers 
/// @param number_elements A pointer to number of elements in argv
///
/// @return none (void)
//
void parseDataInt(char* data, int arr[], int* number_elements)
{
  int index = 0;
  int start = 0;
  char temp[MAX_SIZE]; // Temporary buffer to hold each integer as a string

  for (int i = 0; data[i] != '\0'; i++)
  {
    if (data[i] == ',')
    {
      data[i] = '\0'; // Replace comma with null terminator
      copyString(temp, &data[start]); // Copy the substring to temp
      arr[index] = atoiFunction(temp); // Convert temp to integer and store in array
      start = i + 1;
      index++;
    }
  }

  // Handle the last integer after the last comma
  copyString(temp, &data[start]);
  arr[index] = atoiFunction(temp);
  *number_elements = index + 1;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is a function to check if the number of elements entered by the user is integer or not.
/// It compares the input of the user with the ASCII values from 0 to 9
///
/// @param str A Pointer to the number of elements in argv
///
/// @return 1
//
int isValidElement(char* str)
{
  while(*str)
  {
    if(*str < '0' || *str > '9')
    {
      return 0; //Not within ASCII range from 0 to 9
    }
    str++;
  }
  return 1;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function checks if the number of elements entered by the user is equal to number of elements entered in the array.
/// It counts the number of commas, then add + 1, and compares it with the number of elements .
///
/// @param data A Pointer to the data in argv
/// @param number_elements number of elements enetered by the user
///
/// @return 6 for not enough.
/// @return 7 for too many.
/// @return 0 
//
int checkElementCount(int number_elements, char* data)
{
  int total_elements = 0;
  for(int i = 0; data[i] != '\0'; i++)
  {
    if(data[i] == ',')
    {
      total_elements++;
    }
  }
  total_elements++;
  if(number_elements > total_elements)
  {
    printf("Not enough elements given!\n");
    return 6;
  }
  else if(number_elements < total_elements)
  {
    printf("Too many elements given!\n");
    return 7;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function compare the strings by going through each character one by one.
///
/// @param str1 A const char pointer for the first word.
/// @param str2 A const char pointer for the second word.
///
/// @return (*str1 - *str2)
//
int compareStrings(const char* str1, const char* str2)
{
  while (*str1 && *str2 && *str1 == *str2)
  {
    str1++;
    str2++;
  }
  return (*str1 - *str2);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function copy the strings from the command line entered by the user.
///
/// @param destination A char pointer to copy to string from the command line 
/// @param source a char Pointer to pass the string in the command line to the array
///
/// @return return_pointer
//
char* copyString(char* destination, const char* source)
{
  if(destination == NULL)
  {
    return NULL;
  }

  char *return_pointer = destination;

  while(*source != '\0')
  {
    *destination = *source;
    destination++;
    source++;
  }
  *destination = '\0';
  
  return return_pointer;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is a function that converts strings into an integers.
/// 
///
/// @param str Char pointer for the string entered by the user in the command line.
///
/// @return res
//
int atoiFunction(char* str)
{
  int res = 0;
  for (int i = 0; str[i] != '\0'; ++i)
      res = res * 10 + str[i] - '0';

  return res;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Bubble sort algorithm for strings.
/// Bubble sort repeatedly steps through the list, compares adjacent elements,
/// and swaps them if they are in the wrong order, gradually pushing the largest or smallest element to the end.
/// This process repeats until the list is sorted.
///
/// @param arr Array of strings 
/// @param number_elements number of elements in argv
///
/// @return void (none)
//
void bubbleSortString(char arr[][MAX_SIZE], int number_elements)
{
  printf("[");
  for(int i = 0; i < number_elements; i++)
  {
    printf("%s", arr[i]);
    if( i < number_elements - 1)
    {
      printf(", ");
    }
  }
  printf("]\n");

  printf("--- Start sorting ---\n");
  for (int i = number_elements - 1; i > 0; i--)
  {
    for (int j = 0; j < i; j++)
    {
      if (compareStrings(arr[j], arr[j+1]) > 0)
      {
        char temp[MAX_SIZE];
        copyString(temp, arr[j]);
        copyString(arr[j], arr[j+1]);
        copyString(arr[j+1], temp);
      }
    }

    printf("[");
    for(int k = 0; k < number_elements; k++)
    {
      printf("%s", arr[k]);
      if( k < number_elements - 1)
      {
        printf(", ");
      }
    }
    printf("]\n");

  }
  printf("--- Finished sorting ---\n");
  printArrayStrings(arr, number_elements);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Bubble sort algorithm for integers.
/// Bubble sort repeatedly steps through the list, compares adjacent elements,
/// and swaps them if they are in the wrong order, gradually pushing the largest or smallest element to the end.
/// This process repeats until the list is sorted.
///
/// @param arr Array of integers 
/// @param number_elements number of elements in argv
///
/// @return void (none)
//
void bubbleSortInt(int arr[], int number_elements)
{
  printf("[");
  for(int i = 0; i < number_elements; i++)
  {
    printf("%d", arr[i]);
    if( i < number_elements - 1)
    {
      printf(", ");
    }
  }
  printf("]\n");

  printf("--- Start sorting ---\n");
  for(int i = number_elements - 1; i > 0; i--)
  {
    for(int j = 0; j < i; j++)
    {
      if (arr[j] > arr[j+1])
      {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }

    printf("[");
    for(int k = 0; k < number_elements; k++)
    {
      printf("%d", arr[k]);
      if(k < number_elements - 1)
      {
        printf(", ");
      }
    }
    printf("]\n");
  }
  printf("--- Finished sorting ---\n");
  printArrayIntegers(arr, number_elements);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Merge Sort  algorithm for strings.
/// Merge sort recursively divides the list into smaller halves until each sublist contains only one element
/// Then, it merges these smaller sorted lists, comparing elements from each sublist and arranging them in order.
/// This process continues until the entire list is sorted.
///
/// @param arr Array of strings 
/// @param left Left array
/// @param middle Middle of the array
/// @param right Right array
///
/// @return void (none)
//
void mergeString(char arr[][MAX_SIZE], int left, int middle, int right)
{
  int first_half = middle - left + 1; //Size of left array
  int second_half = right - middle; //Size of right array

  char left_array[first_half][MAX_SIZE];
  char right_array[second_half][MAX_SIZE];

  for(int i = 0; i < first_half; i++)
  {
    copyString(left_array[i], arr[left + i]);
  }
  for(int j = 0; j < second_half; j++)
  {
    copyString(right_array[j], arr[middle + 1 + j]);
  }

  //Merge the temporary arrays back
  int left_index = 0;
  int right_index = 0;
  int merged_index = left; //Initial index of merged subarray

  while(left_index < first_half && right_index < second_half)
  {
    if(compareStrings(left_array[left_index], right_array[right_index]) <= 0)
    {
      copyString(arr[merged_index], left_array[left_index]);
      left_index++;
    }
    else
    {
      copyString(arr[merged_index], right_array[right_index]);
      right_index++;
    }
    merged_index++;
  }

  while(left_index < first_half)
  {
    copyString(arr[merged_index], left_array[left_index]);
    left_index++;
    merged_index++;
  }
  while(right_index < second_half)
  {
    copyString(arr[merged_index], right_array[right_index]);
    right_index++;
    merged_index++;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Merge Sort  algorithm for strings.
/// Merge sort recursively divides the list into smaller halves until each sublist contains only one element
/// Then, it merges these smaller sorted lists, comparing elements from each sublist and arranging them in order.
/// This process continues until the entire list is sorted.
///
/// @param arr Array of strings 
/// @param left Left array
/// @param right Right array
/// @param size size of the array
///
/// @return void (none)
//
void mergeSortString(char arr[][MAX_SIZE], int left, int right, int size)
{
  if(left < right)
  {
    int middle = left + (right - left) / 2;

    // Sorting left side
    mergeSortString(arr, left, middle, size);
    if (middle - left + 1 > 1) {
      printArrayStrings(arr + left, middle - left + 1);
    }

    // Sorting right side
    mergeSortString(arr, middle + 1, right, size);
    if(right - middle > 1) {
      printArrayStrings(arr + middle + 1, right - middle);
    }

    // Merging the sorted halves
    mergeString(arr, left, middle, right);

    // Printing the complete array after sorting both halves
    if(left == 0 && right == size - 1)
    {
      printArrayStrings(arr, size);
      printf("--- Finished sorting ---\n");
      printArrayStrings(arr, size);
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Merge Sort  algorithm for integers.
/// Merge sort recursively divides the list into smaller halves until each sublist contains only one element
/// Then, it merges these smaller sorted lists, comparing elements from each sublist and arranging them in order.
/// This process continues until the entire list is sorted.
///
/// @param arr Array of integers
/// @param left Left array
/// @param middle Middle of the array
/// @param right Right array
///
/// @return void (none)
//
void mergeInt(int arr[], int left, int middle, int right)
{
  int first_half = middle - left + 1; // Size of left array
  int second_half = right - middle;    // Size of right array

  int left_array[first_half];
  int right_array[second_half];

  for(int i = 0; i < first_half; i++)
  {
    left_array[i] = arr[left + i];
  }
  for(int j = 0; j < second_half; j++)
  {
    right_array[j] = arr[middle + 1 + j];
  }

  // Merge the temporary arrays back
  int left_index = 0;
  int right_index = 0;
  int merged_index = left; // Initial index of merged subarray

  while(left_index < first_half && right_index < second_half)
  {
    if(left_array[left_index] <= right_array[right_index])
    {
      arr[merged_index] = left_array[left_index];
      left_index++;
    }
    else
    {
      arr[merged_index] = right_array[right_index];
      right_index++;
    }
    merged_index++;
  }

  while(left_index < first_half)
  {
    arr[merged_index] = left_array[left_index];
    left_index++;
    merged_index++;
  }
  while(right_index < second_half)
  {
    arr[merged_index] = right_array[right_index];
    right_index++;
    merged_index++;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This is the Merge Sort  algorithm for integers.
/// Merge sort recursively divides the list into smaller halves until each sublist contains only one element
/// Then, it merges these smaller sorted lists, comparing elements from each sublist and arranging them in order.
/// This process continues until the entire list is sorted.
///
/// @param arr Array of integers
/// @param left Left array
/// @param right Right array
/// @param size Size of the array
///
/// @return void (none)
//
void mergeSortInt(int arr[], int left, int right, int size)
{
  if(left < right)
  {
    int middle = left + (right - left) / 2;

    // Sorting left side
    mergeSortInt(arr, left, middle, size);
    if(middle - left + 1 > 1)
    {
      printArrayIntegers(arr + left, middle - left + 1);
    }

    // Sorting right side
    mergeSortInt(arr, middle + 1, right, size);
    if(right - middle > 1)
    {
      printArrayIntegers(arr + middle + 1, right - middle);
    }

    // Merging the sorted halves
    mergeInt(arr, left, middle, right);

    // Printing the complete array after sorting both halves
    if(left == 0 && right == size - 1)
    {
      printArrayIntegers(arr, size);
      printf("--- Finished sorting ---\n");
      printArrayIntegers(arr, size);
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, heapifyString, is part of the Heap Sort algorithm for sorting strings.
/// It ensures that the binary tree rooted at current_node_index satisfies the heap property.
/// The largest element among the current node and its children is swapped with the current node.
/// This process recursively continues down the tree until the entire tree satisfies the heap property.
///
/// @param arr Array of strings
/// @param size Size of the array
/// @param root_index Index of the current node
///
/// @return void (none)
//
void heapifyString(char arr[][MAX_SIZE], int size, int root_index)
{
  int largest = root_index;
  int left = 2 * root_index + 1;
  int right = 2 * root_index + 2;

  if(left < size && compareStrings(arr[left], arr[largest]) > 0)
  {
    largest = left;
  }
  if(right < size && compareStrings(arr[right], arr[largest]) > 0)
  {
    largest = right;
  }
  if(largest != root_index)
  {
    char temp[MAX_SIZE];
    copyString(temp, arr[root_index]);
    copyString(arr[root_index], arr[largest]);
    copyString(arr[largest], temp);
    heapifyString(arr, size, largest);
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, buildHeapString, is used to build a heap from an array of strings.
/// It starts from the last non-leaf node (size/2 - 1) and iterates backwards to the root.
/// For each node, it calls the heapifyString function to ensure the heap property is satisfied.
/// After the loop, the entire array satisfies the heap property.
///
/// @param arr Array of strings
/// @param size Size of the array
///
/// @return void (none)
//
void buildHeapString(char arr[][MAX_SIZE], int size)
{
  for(int i = size / 2 - 1; i >= 0; i--)
  {
    heapifyString(arr, size, i);
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, heapSortString, implements the Heap Sort algorithm for sorting an array of strings.
/// It begins by building a heap from the input array using buildHeapString function.
/// Then, it repeatedly extracts the maximum element (root of the heap) and places it at the end of the array.
/// After each extraction, it adjusts the heap using heapifyString function.
/// This process continues until the entire array is sorted.
///
/// @param arr Array of strings
/// @param size Size of the array
///
/// @return void (none)
//
void heapSortString(char arr[][MAX_SIZE], int size)
{
  printArrayStrings(arr, size);
  printf("--- Start sorting ---\n");
  buildHeapString(arr, size);

  for(int i = size - 1; i > 0; i--)
  {
    char temp[MAX_SIZE];
    copyString(temp, arr[0]);
    copyString(arr[0], arr[i]);
    copyString(arr[i], temp);
    heapifyString(arr, i, 0);
    printArrayStrings(arr, size);
  }

  printf("--- Finished sorting ---\n");
  printArrayStrings(arr, size);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, heapifyInt, is part of the Heap Sort algorithm for sorting integers.
/// It ensures that the binary tree rooted at root_index satisfies the heap property.
/// The largest element among the current node and its children is swapped with the current node.
/// This process recursively continues down the tree until the entire tree satisfies the heap property.
///
/// @param arr Array of integers
/// @param size Size of the array
/// @param root_index Index of the current node
///
/// @return void (none)
//
void heapifyInt(int arr[], int size, int root_index)
{
  int largest = root_index;
  int left = 2 * root_index + 1;
  int right = 2 * root_index + 2;

  if(left < size && arr[left] > arr[largest])
  {
    largest = left;
  }
  if(right < size && arr[right] > arr[largest])
  {
    largest = right;
  }
  if(largest != root_index)
  {
    int temp = arr[root_index];
    arr[root_index] = arr[largest];
    arr[largest] = temp;
    heapifyInt(arr, size, largest); 
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, buildHeapInt, is used to build a heap from an array of integers.
/// It starts from the last non-leaf node (size/2 - 1) and iterates backwards to the root.
/// For each node, it calls the heapifyInt function to ensure the heap property is satisfied.
/// After the loop, the entire array satisfies the heap property.
///
/// @param arr Array of integers
/// @param size Size of the array
///
/// @return void (none)
//
void buildHeapInt(int arr[], int size)
{
  for(int i = size / 2 - 1; i >= 0; i--)
  {
    heapifyInt(arr, size, i);
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, heapSortInt, implements the Heap Sort algorithm for sorting an array of integers.
/// It begins by building a heap from the input array using buildHeapInt function.
/// Then, it repeatedly extracts the maximum element (root of the heap) and places it at the end of the array.
/// After each extraction, it adjusts the heap using heapifyInt function.
/// This process continues until the entire array is sorted.
///
/// @param arr Array of integers
/// @param size Size of the array
///
/// @return void (none)
//
void heapSortInt(int arr[], int size)
{
  printArrayIntegers(arr, size);
  printf("--- Start sorting ---\n");
  buildHeapInt(arr, size);

  for(int i = size - 1; i > 0; i--)
  {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    heapifyInt(arr, i, 0);
    printArrayIntegers(arr, size);
  }

  printf("--- Finished sorting ---\n");
  printArrayIntegers(arr, size);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function, sortingAlgorithm, selects and applies a sorting algorithm based on the specified algorithm_name and data_type.
/// Supported algorithms include Bubble Sort, Merge Sort, and Heap Sort for both integer and string data types.
/// It parses the input data, performs the sorting operation accordingly, and returns 0 upon successful execution.
/// If the specified algorithm or data type is invalid, it prints an error message and returns 2.
///
/// @param algorithm_name Name of the sorting algorithm
/// @param data_type Type of data to be sorted (string or int)
/// @param data Input data to be sorted
/// @param number_elements Number of elements in the input data
///
/// @return 0 for successful sorting, 2 for invalid input
//
int sortingAlgorithmProgram(char* algorithm_name, char* data_type, char* data, int number_elements)
{
  char arr_of_string[MAX_SIZE][MAX_SIZE];
  int arr_of_integers[MAX_SIZE];
  if(compareStrings(algorithm_name, "bubble") == 0)
  {
    if (compareStrings(data_type, "string") == 0)
    {
      parseDataString(data, arr_of_string, &number_elements);
      bubbleSortString(arr_of_string, number_elements);
    }
    else if (compareStrings(data_type, "int") == 0)
    {;
      parseDataInt(data, arr_of_integers, &number_elements);
      bubbleSortInt(arr_of_integers, number_elements);
    }
  }
  else if(compareStrings(algorithm_name, "merge") == 0)
  {
    if (compareStrings(data_type, "string") == 0)
    {
      parseDataString(data, arr_of_string, &number_elements);
      printArrayStrings(arr_of_string, number_elements);
      printf("--- Start sorting ---\n");
      mergeSortString(arr_of_string, 0, number_elements - 1, number_elements);
    }
    else if(compareStrings(data_type, "int") == 0)
    {
      parseDataInt(data, arr_of_integers, &number_elements);
      printArrayIntegers(arr_of_integers, number_elements);
      printf("--- Start sorting ---\n");
      mergeSortInt(arr_of_integers, 0, number_elements - 1, number_elements);
    }
  }
  else if(compareStrings(algorithm_name, "heap") == 0)
  {
    if(compareStrings(data_type, "int") == 0)
    {
      parseDataInt(data, arr_of_integers, &number_elements);
      heapSortInt(arr_of_integers, number_elements);
    }
    else if(compareStrings(data_type, "string") == 0)
    {
      parseDataString(data, arr_of_string, &number_elements);
      heapSortString(arr_of_string, number_elements);
    }
  }
  else
  {
    printf("Invalid sorting algorithm!\n");
    return 2;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function prints the array of strings
///
/// @param arr Array of strings 
/// @param size Size of the array
///
/// @return void (none)
//
void printArrayStrings(char arr[][MAX_SIZE], int size)
{
  printf("[");
  for(int i = 0; i < size; i++)
  {
    printf("%s", arr[i]);
    if( i < size - 1)
    {
      printf(", ");
    }
  }
  printf("]\n");
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function prints the array of Integers
///
/// @param arr Array of integer. 
/// @param size Size of the array.
///
/// @return void (none)
//
void printArrayIntegers(int arr[], int size)
{
  printf("[");
  for(int i = 0; i < size; i++)
  {
    printf("%d", arr[i]);
    if( i < size - 1)
    {
      printf(", ");
    }
  }
  printf("]\n");
}
