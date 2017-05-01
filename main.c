#include <stdio.h>
#include <stdlib.h>

/*  maze[i][j]
        J ->0   1   2   3   4   5   6   7   8   9   10  11  12
I   C                       -9      -8      -7
0           -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
1           -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
2           -1  -1  0   0   0   0   0   0   0   0   0   -1  -1
3           -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
4   9       0   0   0   0   0   0   0   0   0   0   0   0   0   15
5           -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
6   19      0   0   0   0   0   0   0   0   0   0   0   0   0   25
7           -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
8   29      0   0   0   0   0   0   0   0   0   0   0   0   0   35
9           -1  -1  0   -1  0   -1  0   -1  0   -1  0   -1  -1
10          -1  -1  0   0   0   0   0   0   0   0   0   -1  -1
11          -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
12          -1  -1  -1  -1  0   -1  0   -1  0   -1  -1  -1  -1
                            51      52      53


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
int map(int in,int v)
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

int mapBack(int pi,int pj)
{
    int r;
    r = 10* (pi/2-1) + (pj/2-1);

    switch(r)
    {
        case -9:
            r = 9;
            break;
        case -8:
            r = 8;
            break;
        case -7:
            r = 7;
            break;
        case 9:
            r = 10;
            break;
        case 19:
            r = 11;
            break;
        case 29:
            r = 12;
            break;
        case 15:
            r = 6;
            break;
        case 25:
            r = 5;
            break;
        case 35:
            r = 4;
            break;
        case 51:
            r = 1;
            break;
        case 52:
            r = 2;
            break;
        case 53:
            r = 3;
            break;
    }
    return r;
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

void traceback(int x,int si,int sj)
{
    /*
        0
    1   d   2
        3
    */
    int i,j,k,v,pi,pj,d;

    if(mapBack(si,sj) < 4)
    {
        d = 0;
    }
    else if(mapBack(si,sj) < 7)
    {
        d = 1;
    }
    else if(mapBack(si,sj) < 10)
    {
        d = 3;
    }

    else
    {
        d = 2;
    }

    v=x;

    for(i=0;i<13;i++)
    {
        for(j=0;j<13;j++)
        {
            if(maze[i][j] == v && i == si && j == sj)
            {
                printf("%02d ",mapBack(i,j));
                v--;
                pi=i;
                pj=j;
            }
        }
    }

    for(k=v-1;k>=0;k--)
    {
        switch(d)
        {
            case 0:
                if(maze[pi-1][pj] == v)
                {
                    pi = pi-1;
                }
                else if(maze[pi][pj-1] == v)
                {
                    pj = pj-1;
                    d = 1;
                }
                else if(maze[pi][pj+1] == v)
                {
                    pj = pj+1;
                    d = 2;
                }
                v--;
                break;
            case 1:
                if(maze[pi][pj-1] == v)
                {
                    pj = pj-1;
                }
                else if(maze[pi-1][pj] == v)
                {
                    pi = pi-1;
                    d = 0;
                }
                else if(maze[pi+1][pj] == v)
                {
                    pi = pi+1;
                    d = 3;
                }
                v--;
                break;
            case 2:
                if(maze[pi][pj+1] == v)
                {
                    pj = pj+1;
                }
                else if(maze[pi-1][pj] == v)
                {
                    pi = pi-1;
                    d = 0;
                }
                else if(maze[pi+1][pj] == v)
                {
                    pi = pi+1;
                    d = 3;
                }
                v--;
                break;
            case 3:
                if(maze[pi+1][pj] == v)
                {
                    pi = pi+1;
                }
                else if(maze[pi][pj-1] == v)
                {
                    pj = pj-1;
                    d = 1;
                }
                else if(maze[pi][pj+1] == v)
                {
                    pj = pj+1;
                    d = 2;
                }
                v--;
                break;
        }

        if(pi%2 == 0 && pj%2 == 0)
        {
            if(v != 0)
            {
                printf("c%02d ",10*(pi/2-1)+(pj/2-1));
            }
            else
            {
                printf("%02d ",mapBack(pi,pj));
            }
        }
    }

    printf("\n");
}

void route(int si,int sj,int ei,int ej)
{


    int cnt;
    cnt = 1;
    initMaze();

    maze[ei][ej] = 1;

    while (check(cnt,si,sj))
    {
        sNs(cnt);
        cnt++;

        int i,j;

    }

    traceback(cnt,si,sj);

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

void setMine()
{
    int N,tmp;

    printf("Enter the amount of mines and the position of these mines.\n");
    scanf("%d",&N);

    while(scanf("%c") == 1)
    {
        scanf("%d",&tmp);
    }
}

int main()
{
    int N,i,sp[2],tmp;

    initMaze();

/* Set certain places to -1 due to mines on the road */
    /* setMine(); */

/* Get the start position */
    printf("Enter the start position terminated by an enter.\n");
    scanf("%d",&tmp);
    sp[0] = map(tmp,0);
    sp[1] = map(tmp,1);

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
