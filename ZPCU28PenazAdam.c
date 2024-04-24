#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { MUZ = 1, ZENA } Pohlavi;

typedef struct {
    char j[12];
    Pohlavi p;
} Jmeno;

Jmeno J[134]; 

char temp[12];



int x = 0;
int IsInArray(char* Jmeno)
{
    for (int i = 0; i < 135; i++)
    {
        if (strcmp(Jmeno, J[i].j) == 0)
        {
            return 1;
        }
    }
    return 0;
  
    
}

void bubbleSort(Jmeno arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i].j, arr[j].j) > 0)
            {
                Jmeno temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printWomen()
{
    int odradkovani = 10;
    for (int i = 18; i < 134; i++)
    {
        if (odradkovani <= 0)
        {
            printf("\n");
            odradkovani = 10;
        }
        if (J[i].p == ZENA)
        {
            printf("%s ", J[i]);
            odradkovani--;
        }
        
    }
}

void printMen()
{
    int odradkovani = 10;
    for (int i = 18; i < 135; i++)
    {
        if (odradkovani <= 0)
        {
            printf("\n");
            odradkovani = 10;
        }
        if (J[i].p == MUZ)
        {
            printf("%s ", J[i]);
            odradkovani--;
        }
        
    }
}

void main() 
{
    FILE* file;
    char bytes[1000];
    int x = 0;
    file = fopen("Jmena", "rb");
    

    size_t bytes_read = fread(bytes, sizeof(char), 1000, file);
    int index1 = -1;
    int index2 = 0;
    int index3 = 0;
    int pohlavi = 0; //0 = žena
    int length = 0;
    char temp[12];

    
    for (int i = 0; i < 1500; i++) {
        if (bytes[i] == -52)
        {
            while (length != 0)
            {
                J[index1].j[index3] = bytes[i - length];
                index3++;
                length--;
            }
            index1--;
            bubbleSort(J, 135);
            printWomen();
            printf("\n");
            printf("\n");
            printMen();

            break;
        }
        if (bytes[i] >= 65 && bytes[i] <= 126) 
        {
            
            if (pohlavi == 0 && index2 == 0)
            {
                J[index1].p = ZENA;
            }
            if (pohlavi == 1 && index2 == 0)
            {
                J[index1].p = MUZ;
            }
            
            temp[index2] = bytes[i];

            index2++;
            
            
        }
        else 
        {
            if (IsInArray(temp) == 0)
            {
                while (length != 0)
                {
                    J[index1].j[index3] = bytes[i - length];
                    index3++;
                    length--;
                }
            }
            else
            {
                index1--;
            }
            
            memset(temp, 0, sizeof temp);
            if (bytes[i] > 50 && bytes[i] < 65)
            {
                index2 = 0;
                index3 = 0;
                index1++;
                pohlavi = 0;
                length = bytes[i] - 50;
            }
            else
            {
                index3 = 0;
                index2 = 0;
                index1++;
                pohlavi = 1; 
                length = bytes[i];
            }
        }

    }
    
}
