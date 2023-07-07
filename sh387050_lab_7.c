#include <stdio.h>

//actually does the bubble sort and counts 1 on the index when a swap is completed
void bubbleSort(int arr[], int n, int swaps[]) 
{
    int temp;

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps[j]++;
                swaps[j + 1]++;
            }
        }
    }
}

int main() 
{
    int arr[] = { 97, 16, 45, 63, 13, 22, 7, 58, 72 };
    int n = 9;
    int swaps[9];
    
    //ensure that all indexes are set to 0 as to not introduce error into the final
    for (int i = 0; i < n; i++) 
    {
        swaps[i] = 0;
    }

    //prints the array we are working with
    printf("Array before sorting: ");

    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");

    bubbleSort(arr, n, swaps);

    //prints the sorted array
    printf("Array after sorting: ");

    for (int k = 0; k < n; k++) 
    {
        printf("%d ", arr[k]);
    }
    printf("\n");

    //prints the swaps array which has counted the number of swaps per index
    printf("Number of swaps for each index: ");

    for (int l = 0; l < n; l++) 
    {
        printf("%d ", swaps[l]);
    }
    printf("\n");

    return 0;
}
