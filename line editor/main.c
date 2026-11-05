
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define SIZE 200

char lines[MAX][SIZE];
int count = 0;

// Remove newline from input
void removeNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}

// Insert a line
void insertLine()
{
    int pos, i;

    if (count == MAX)
    {
        printf("Document is full!\n");
        return;
    }

    printf("Enter line number to insert: ");
    scanf("%d", &pos);
    getchar();

    if (pos < 1 || pos > count + 1)
    {
        printf("Invalid position!\n");
        return;
    }

    for (i = count; i >= pos; i--)
        strcpy(lines[i], lines[i - 1]);

    printf("Enter text: ");
    fgets(lines[pos - 1], SIZE, stdin);
    removeNewline(lines[pos - 1]);

    count++;
    printf("Line inserted successfully!\n");
}

// Delete a line
void deleteLine()
{
    int pos, i;

    if (count == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter line number to delete: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count)
    {
        printf("Invalid line number!\n");
        return;
    }

    for (i = pos - 1; i < count - 1; i++)
        strcpy(lines[i], lines[i + 1]);

    count--;
    printf("Line deleted successfully!\n");
}

// Display document
void displayLines()
{
    int i;

    if (count == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("\n--- DOCUMENT ---\n");

    for (i = 0; i < count; i++)
        printf("%d. %s\n", i + 1, lines[i]);
}

// Save document
void saveFile()
{
    FILE *fp = fopen("document.txt", "w");
    int i;

    if (fp == NULL)
    {
        printf("Unable to save file!\n");
        return;
    }

    for (i = 0; i < count; i++)
        fprintf(fp, "%s\n", lines[i]);

    fclose(fp);
    printf("Document saved successfully!\n");
}

// Load document
void loadFile()
{
    FILE *fp = fopen("document.txt", "r");
    char temp[SIZE];

    if (fp == NULL)
    {
        printf("No saved file found. Starting new document.\n");
        return;
    }

    count = 0;

    while (count < MAX && fgets(temp, SIZE, fp) != NULL)
    {
        removeNewline(temp);
        strcpy(lines[count], temp);
        count++;
    }

    fclose(fp);
    printf("Document loaded successfully!\n");
}

// Search a word
void searchWord()
{
    char word[SIZE];
    int i, found = 0;

    printf("Enter word to search: ");
    getchar();
    fgets(word, SIZE, stdin);
    removeNewline(word);

    for (i = 0; i < count; i++)
    {
        if (strstr(lines[i], word) != NULL)
        {
            printf("Found at line %d\n", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("Word not found!\n");
}

// Count lines and words
void countWords()
{
    int i, j, words = 0;
    int inWord;

    for (i = 0; i < count; i++)
    {
        inWord = 0;

        for (j = 0; lines[i][j] != '\0'; j++)
        {
            if (isspace((unsigned char)lines[i][j]))
                inWord = 0;
            else if (!inWord)
            {
                words++;
                inWord = 1;
            }
        }
    }

    printf("Total lines: %d\n", count);
    printf("Total words: %d\n", words);
}

int main()
{
    int choice;

    loadFile();

    do
    {
        printf("\n===== SIMPLE LINE EDITOR =====\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Display Document\n");
        printf("4. Save Document\n");
        printf("5. Load Document\n");
        printf("6. Search Word\n");
        printf("7. Count Lines and Words\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        switch (choice)
        {
            case 1: insertLine(); break;
            case 2: deleteLine(); break;
            case 3: displayLines(); break;
            case 4: saveFile(); break;
            case 5: loadFile(); break;
            case 6: searchWord(); break;
            case 7: countWords(); break;
            case 8:
                saveFile();
                printf("Exiting editor...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}
