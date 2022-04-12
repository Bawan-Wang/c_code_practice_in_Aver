#include <stdio.h>
#include <stdlib.h>

int m[10][17] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0},
                          {0,255,255,255,255,255,255,255,255,0,0,255,255,255,255,0,0},
                          {0,0,0,255,255,255,255,0,0,0,255,255,255,255,0,0,0},
                          {0,0,255,255,255,255,0,0,0,255,255,255,0,0,255,255,0},
                          {0,255,255,255,0,0,255,255,0,0,0,255,255,255,0,0,0},
                          {0,0,255,255,0,0,0,0,0,255,255,0,0,0,255,255,0},
                          {0,0,0,0,0,0,255,255,255,255,0,0,255,255,255,255,0},
                          {0,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,255,255,0,0,0,0,255,255,255,255,0,0,0,0}};

int label[10][17];


// direction vectors
//const int dx[] = {+1, 0, -1, 0};
//const int dy[] = {0, +1, 0, -1};

// matrix dimensions
int row_count;
int col_count;

const int dx[] = {+1, 0, -1, 0, +1, +1, -1, -1};
const int dy[] = {0, +1, 0, -1, -1, +1, -1, +1};

void dfs(int xIdx, int yIdx, int current_label) {
    int direction;
    
    if (xIdx < 0 || xIdx >= row_count) {
        return; // out of bounds
    }
    if (yIdx < 0 || yIdx >= col_count) {
        return; // out of bounds
    }
    if (label[xIdx][yIdx] || !m[xIdx][yIdx]) {
        return; // already labeled or not marked with 1 in m
    }
    
    // mark the current cell
    label[xIdx][yIdx] = current_label;

    // recursively mark the neighbors
    for (direction = 0; direction < 8; direction++)
        dfs(xIdx + dx[direction], yIdx + dy[direction], current_label);
}

int find_components() {
    int iRow, iCol;
    int component = 0;
    for (iRow = 0; iRow < row_count; iRow++) {
        for (iCol = 0; iCol < col_count; iCol++) { 
            if (!label[iRow][iCol] && m[iRow][iCol]) {
                dfs(iRow, iCol, ++component);
            }
        }
    }

    return component;
}

void printMArray(int width, int height)
{
    int row, col;
    
    for(row = 0; row < height; row++) {
        for(col = 0; col < width; col++) { 
            printf("%3d ", m[row][col]);
        }
        printf("\n");
    }
    printf("\n");          
}

void printLabelArray(int width, int height)
{
    int row, col;
    
    for(row = 0; row < height; row++) {
        for(col = 0; col < width; col++) { 
            printf("%3d ", label[row][col]);
        }
        printf("\n");
    }
    printf("\n");          
}

int main(int argc, char *argv[])
{
    int components_num;
    
    row_count = 10;
    col_count = 17;
    components_num = find_components();

    printf("components_num = %d\n", components_num);

    printMArray(17, 10);

    printLabelArray(17, 10);
  
    system("PAUSE");	
    return 0;
}
