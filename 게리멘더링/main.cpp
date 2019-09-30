#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n;
int line[11][11];
int people[11];
int town[11];
int nRet;

int bfs(int temp[10], int type, int total_cnt)
{
	int cnt = 1;
	queue <int> que;
	int visit[11] = { 0, };

	for (int i = 1; i <= n; i++){
		if (temp[i] == type){
			que.push(i);
			visit[i] = 1;
			break;
		}
	}

	int cur = 0;
	int nxt = 0;
	while (!que.empty())
	{
		cur = que.front();
		que.pop();

		for (int i = 1; i <= line[cur][0]; i++){
			nxt = line[cur][i];
			if (visit[nxt] == 0 && temp[nxt] == type){
				cnt++;
				visit[nxt] = 1;
				que.push(nxt);
			}
		}
	}

	if (cnt == total_cnt)
		return 1;
	else
		return 0;
}



int dfs(int num, int cnt, int total)
{
	if (cnt == total){
		int ret = bfs(town, 1, total);
		int ret2 = bfs(town, 0, n - total);

		if (ret && ret2){
			ret = 0;
			ret2 = 0;
			for (int i = 1; i <= n; i++){
				if (town[i] == 1)
				{
					ret += people[i];
				}
				else
				{
					ret2 += people[i];
				}
			}
			nRet = min(nRet, abs(ret - ret2));
		}
		return 0;
	}

	for (int i = num; i <= n; i++){
		town[i] = 1;
		dfs(i + 1, cnt + 1, total);
		town[i] = 0;
	}
}

int main()
{
	int temp = 0;

	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> people[i];

	for (int i = 1; i <= n; i++){
		cin >> temp;

		for (int j = 0; j <= temp; j++){
			if (j == 0)	{
				line[i][0] = temp;
				continue;
			}
			cin >> line[i][j];
		}
	}
	nRet = 987654321;
	for (int i = 1; i < n; i++){
		dfs(1, 0, i);
	}
	if (nRet == 987654321)
		nRet = -1;

	cout << nRet << endl;
	return 0;
}