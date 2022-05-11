#include "tom.h"
#include <QTimer>
#include <QVector>

int tom::row =21;
int tom::column=10;
int tom::ogRow=row;
int tom::ogCol=column;
tom::tom(int initialRow, int initialColumn,int d[24][24])
{
    for (int i = 0; i < 24; i++)
            for (int j = 0; j < 24; j++)
                data[i][j] = d[i][j];

    QPixmap image("tommy.png");
    image =image.scaledToWidth(40);
    image = image.scaledToHeight(40);
    setPixmap(image);
    // Set Position
    setPos(20 + 40 * initialColumn, 80 + 35 * initialRow);

    row = initialRow;
    column = initialColumn;
   ogRow=initialRow;
   ogCol=initialColumn;

    int index1=0, index2=0, index3=0, index4=0;
    int originindex=0;

    for(int i=0; i<24; i++){
        for(int j=0; j<24; j++){
            if(data[i][j]!=-1){
                originindex=data[i][j];
                if((j+1)<24&&data[i][j+1]!=-1){
                    index1=data[i][j+1];
                    matrix[originindex][index1]=1;
                }

                if((i+1)<24&&data[i+1][j]!=-1){
                    index2=data[i+1][j];
                    matrix[originindex][index2]=1;
                }

                if((j-1)>=0&&data[i][j-1]!=-1){
                    index3=data[i][j-1];
                    matrix[originindex][index3]=1;
                }

                if((i-1)>=0&&data[i-1][j]!=-1){
                    index4=data[i-1][j];
                    matrix[originindex][index4]=1;
                }

               for(int k=0; k<365; k++){
                   if(k!=index1&&k!=index2&&k!=index3&&k!=index4){
                       matrix[originindex][k]=0;
                   }
               }
            }
        }
    }
}
bool tom:: isathome(int roww, int columnn){
    if((roww!=9||columnn!=11)&&(roww!=9||columnn!=12)&&(roww!=10||columnn!=11)&&(roww!=10||columnn!=12)&&(roww!=11||columnn!=9)
            &&(roww!=11||columnn!=10)&&(roww!=11||columnn!=12)&&(roww!=11||columnn!=13)&&(roww!=11||columnn!=14)&&(roww!=12||columnn!=9)
            &&(roww!=12||columnn!=10)&&(roww!=12||columnn!=11)&&(roww!=12||columnn!=12)&&(roww!=12||columnn!=13)&&(roww!=12||columnn!=14)
            &&(roww!=13||columnn!=11)&&(roww!=13||columnn!=12)&&(roww!=14||columnn!=11)&&(roww!=14||columnn!=12))
        return true;
    else
        return false;
}

void tom::goHome()
{
    row = ogRow;
    column = ogCol;
    //setPos(20 + 40 * column, 80 + 35 * row);
}

void tom::move(QVector<int>paths){

    if(paths.size()>1){

    int i = 1;{
    if ((data[row][column + 1] != -1) &&(data[row][column+1]==paths[i])&& (isathome(row, column+1)))
    {column++;
    }

    if ((data[row][column - 1] != -1)&&(data[row][column-1]==paths[i]) && (isathome(row, column-1)))
    {column--;
    }

    if((data[row - 1][column] != -1) &&(data[row-1][column]==paths[i]) && (isathome(row-1, column)))
    {row--;
    }

    if((data[row + 1][column] != -1) &&(data[row+1][column]==paths[i]) && (isathome(row+1, column)))
    {row++;
    }
}
setPos(20 + 40 * column, 80 + 35 * row);
    }

}

void tom::advancee()
{
       move(Dijkstra(matrix,0));


}
QVector<int> tom:: Dijkstra(int matrix[COUNT][COUNT], int startVertex)
{
    int finalVertex=data[jerry::getrow()][jerry::getcolumn()];
    //int finalVertex=45;
    startVertex=data[row][column];

    int temp[COUNT][COUNT];
    for (int i = 0; i < COUNT; i++)
    {
        for (int j = 0; j < COUNT; j++)
        {
            if (matrix[i][j] == 0)
                temp[i][j] = INFINITE;
            else
                temp[i][j] = matrix[i][j];
        }
    }
    bool visited[COUNT];
    int previous[COUNT];
    float cost[COUNT];
    // 1st Row:
    for (int i = 0; i < COUNT; i++)
    {
        if (i == startVertex)
        {
            previous[i] = -1;
            cost[i] = 0;
            visited[i] = true;
        }
        else
        {
            previous[i] = startVertex;
            cost[i] = temp[startVertex][i];
            visited[i] = false;
        }
    }
    // All Rows:
    int count = 1;
    while (count < COUNT)
    {
        // Determine which vertex to visit.
        int minimum = INFINITE, visitedVertex;
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                visitedVertex = i;
            }
        }
        // Visit the vertex.
        visited[visitedVertex] = true;

        // Check whether there are shorter paths.
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false)
            {
                if ((cost[visitedVertex] + temp[visitedVertex][i]) < cost[i])
                {
                    previous[i] = visitedVertex;
                    cost[i] = (cost[visitedVertex] + temp[visitedVertex][i]);
                }
            }
        }
        count++;
    }

    QVector<int> finalPath;
    int k = finalVertex;
    finalPath.push_front(k);
    do{

        k = previous[k];
        finalPath.push_front(k);
    }while(k != startVertex);

    return finalPath;
}
