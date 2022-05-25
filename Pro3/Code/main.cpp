#include "iostream"
using namespace std;
int main()
{
    long long modNum = 1000000007;
    long long resNum = 0;
    int maxN = 700;
    long long redNode[maxN][maxN], blackNode[maxN][maxN];
    int n,i,j,k,l;
    cin >> n;
    blackNode[1][1]= 1 ;
    blackNode[1][2] = 2;
    redNode[0][1] = 1;
    for (i = 0; i <= 10 ; i++)
    {
        for (j = 2; j <n ; j++)
        {
            for ( k = 1; k < j; k++)
            {
            redNode[i][j+1] += blackNode[i][j-k]*blackNode[i][k];
            blackNode[i+1][j+1] +=(redNode[i][j-k]+blackNode[i][j-k])*(redNode[i][k]+blackNode[i][k])%modNum;
            redNode[i][j+1] %= modNum;
            blackNode[i+1][j+1] %= modNum;
            }
        }
    }
    for(i=0;i <=n;++i)
    {
        resNum = (resNum+blackNode[i][n])%modNum;
    }
    cout << resNum;
    return 0;
}
