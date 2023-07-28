#include <stdio.h>
#include <stdlib.h>

// Global variable for record size
int recordSz = 15;

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Fill out this structure
struct HashType
{
    struct RecordType* data;
    int size;
};

// Compute the hash function
int hash(int x, int tableSz)
{
    return x % tableSz;
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void displayRecordsInHash(struct HashType* pHashArray)
{
    printf("Records in Hash:\n");
    for (int i = 0; i < pHashArray->size; ++i)
    {
        if (pHashArray->data[i].id != -1)
        {
            printf("Index: %d -> ID: %d, Name: %c, Order: %d\n", i, pHashArray->data[i].id, pHashArray->data[i].name, pHashArray->data[i].order);
        }
    }
}

int main(void)
{
    struct RecordType* pRecords;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Hash table creation
    int HashSize = recordSz;
    struct HashType HashTable;
    HashTable.data = (struct RecordType*)malloc(sizeof(struct RecordType) * HashSize);
    HashTable.size = HashSize;

    // Initialize hash table slots to -1 to represent an empty slot
    for (int i = 0; i < HashSize; ++i)
    {
        HashTable.data[i].id = -1;
    }

    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id, HashSize);

        // Linear probing to handle collisions
        while (HashTable.data[index].id != -1)
        {
            index = (index + 1) % HashSize;
        }

        HashTable.data[index] = pRecords[i];
    }

    displayRecordsInHash(&HashTable);

    // Frees Memory
    free(pRecords);
    free(HashTable.data);

    return 0;
}
