#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linked list.
int length(node* head) {
    int count = 0;
    node* current1 = head;
    while (current1 != NULL) {
        count++;
        current1 = current1->next;
    }
    return count;
}

// Parses the string in the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then the toCString function will return "abc".
char* toCString(node* head) {
    int len = length(head);
    printf("len = %d\n", len);
    char* str = (char*)malloc((len + 1) * sizeof(char)); 
    int i = 0;
    node* current2 = head;
    while (current2 != NULL) {
        str[i] = current2->letter;
        i++;
        current2 = current2->next;
    }
    printf("i = %d\n", i);
    str[i] = '\0'; // null terminator
    return str;
}

// Inserts a character to the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|.
void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        *pHead = newNode;
    }
    else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Deletes all nodes in the linked list.
void deleteList(node** pHead) {
    node* current = *pHead;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is: %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL) {
            printf("deleteList is not correct!");
            break;
        }
    }

    fclose(inFile);

    return 0;
}
