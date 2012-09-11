#include <iostream>
#include <utility>
#include <memory.h>
#include <algorithm>

using namespace std;

#define X first
#define Y second

typedef pair<int,int> point;

int N;
point p[ 102 ];
int dp[ 102 ][ 102 ];

bool cmp(point A, point B)
{
    return A.Y * B.X < B.Y * A.X;
}

int cross(point &O, point &A, point &B)
{
    return (A.X - O.X)*(B.Y - O.Y) - (A.Y - O.Y)*(B.X - O.X);
}

int solve(int a, int b)
{
    int &ret = dp[a][b];
    if ( ret != -1 ) return ret;
    if ( a!=0 && cross( p[a], p[b], p[0] ) <= 0 ) return ret = -2;
    ret = 2;
    for (int k=b+1; k<=N; k++)
    {
        if ( cross( p[a], p[b], p[k] ) <= 0 ) continue;
        int xd = solve( b, k );
        if ( xd == -2 ) continue;
        ret = max( ret, 1 + xd );
    }
    return ret;
}

int main()
{
    scanf("%d",&N);
    for (int i=1; i<=N; i++) cin >> p[i].X >> p[i].Y;
    
    sort( p+1, p+1+N, cmp );
    
    memset( dp, -1, sizeof dp );
    int ans = 3;
    for (int i=1; i<=N; i++) ans = max( ans, solve( 0, i ) );
    printf("%d\n",ans);
    
    return 0;
}