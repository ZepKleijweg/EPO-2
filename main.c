#include <stdio.h>
#include <stdlib.h>

/*  maze[i][j]
J ->0   1   2   3   4   5   6   7   8   9   10  11  12
I
0   -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
1   -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
2   -1  -1  0   0   0   0   0   0   0   0   0   -1  -1
3   -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
4   0   0   0   0   0   0   0   0   0   0   0   0   0
5   -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
6   0   0   0   0   0   0   0   0   0   0   0   0   0
7   -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
8   0   0   0   0   0   0   0   0   0   0   0   0   0
9   -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
10  -1  -1  0   0   0   0   0   0   0   0   0   -1  -1
11  -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
12  -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1

Checkpoint mapping
ckp ->  [i][j]
1   ->  [12][4]
2   ->  [12][6]
3   ->  [12][8]

4   ->  [8][12]
5   ->  [6][12]
6   ->  [4][12]

7   ->  [0][8]
8   ->  [0][6]
9   ->  [0][4]

10  ->  [4][0]
11  ->  [6][0]
12  ->  [8][0]

*/

int maze[13][13];

/* Set appropriate places to 0 */
void initMaze()
{
    int i,j;

    /* Everything -1 */
    for(i=0;i<13;i++)
    {
        for(j=0;j<13;j++)
        {
            maze[i][j] = -1;
        }
    }

    /* 0 columns */
    for(i=0;i<13;i++)
    {
        maze[i][4] = 0;
        maze[i][6] = 0;
        maze[i][8] = 0;
    }
    for(i=2;i<11;i++)
    {
        maze[i][2] = 0;
        maze[i][10] = 0;
    }

    /* 0 rows */
    for(i=0;i<13;i++)
    {
        maze[4][i] = 0;
        maze[6][i] = 0;
        maze[8][i] = 0;
    }
    for(i=2;i<11;i++)
    {
        maze[2][i] = 0;
        maze[10][i] = 0;
    }
}

/* Map the ckp values to i and j values */
int * map(int in,int v)
{
    int ckp[2];

    switch(in){
    case 1:
        ckp[0] = 12;
        ckp[1] = 4;
        break;
    case 2:
        ckp[0] = 12;
        ckp[1] = 6;
        break;
    case 3:
        ckp[0] = 12;
        ckp[1] = 8;
        break;
    case 4:
        ckp[0] = 8;
        ckp[1] = 12;
        break;
    case 5:
        ckp[0] = 6;
        ckp[1] = 12;
        break;
    case 6:
        ckp[0] = 4;
        ckp[1] = 12;
        break;
    case 7:
        ckp[0] = 0;
        ckp[1] = 8;
        break;
    case 8:
        ckp[0] = 0;
        ckp[1] = 6;
        break;
    case 9:
        ckp[0] = 0;
        ckp[1] = 4;
        break;
    case 10:
        ckp[0] = 4;
        ckp[1] = 0;
        break;
    case 11:
        ckp[0] = 6;
        ckp[1] = 0;
        break;
    case 12:
        ckp[0] = 8;
        ckp[1] = 0;
        break;
    }

    if(v)
    {
        return ckp[1];
    }
    else
    {
        return ckp[0];
    }
}

void setN(int i,int j, int x)
{
    if(i != 0 && maze[i-1][j] == 0) maze[i-1][j] = x+1;
    if(i != 12 && maze[i+1][j] == 0) maze[i+1][j] = x+1;
    if(j != 0 && maze[i][j-1] == 0) maze[i][j-1] = x+1;
    if(j != 12 && maze[i][j+1] == 0) maze[i][j+1] = x+1;
}

void sNs(int x)
{
    int i,j,br;



    br=0;
    for(i=0;i<13;i++)
    {
        for(j=0;j<13;j++)
        {
            if(maze[i][j] == x)
            {
                setN(i,j,x);
            }
        }
    }
}

int check(int x,int si, int sj)
{
    int r,i,j;
    r=1;
    for(i=0;i<13;i++)
    {
        for(j=0;j<13;j++)
        {
            if(maze[i][j] == x && i == si && j == sj)
            {
                r=0;
            }
        }
    }
    return r;
}

void route(int si,int sj,int ei,int ej)
{


    int cnt;
    cnt = 1;
    initMaze();

    maze[ei][ej] = 1;

    while (check(cnt,si,sj))
    {
        printf("%d\n",cnt);
        sNs(cnt);
        cnt++;

        int i,j;

    }



    int i,j;
    for(i=0;i<13;i++)
    {
        for(j=0;j<13;j++)
        {
            printf("%3d",maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main()
{
    int N,i,sp[2],tmp;

    initMaze();

/* get the positions of the checkpoints */
    printf("First enter the amount of checkpoints terminated by an enter.\n");
    scanf("%d",&N);

    /* [ckp][[i][j]] */
    int ckp[N][2];

    printf("Enter the checkpoints terminated by an enter.\n");

    for(i=N;i>0;i--)
    {
        int p[2];
        scanf("%d",&tmp);
        p[0] = map(tmp,0);
        p[1] = map(tmp,1);
        ckp[N-i][0] = p[0];
        ckp[N-i][1] = p[1];
    }

/* Get the start position */
    printf("Enter the start position terminated by an enter.\n");
    scanf("%d",&tmp);
    sp[0] = map(tmp,0);
    sp[1] = map(tmp,1);

/* Route to the checkpoints */
    /* route (x[i],x[j],y[i],y[j]); route from X to Y */
    route(sp[0],sp[1],ckp[0][0],ckp[0][1]);
    for(i=N;i>1;i--)
    {
        route(ckp[N-i][0],ckp[N-i][1],ckp[N-i+1][0],ckp[N-i+1][1]);
    }

    /* Floodfill the maze from start to finish */
    /* floodFill(); */

    return 0;
}
