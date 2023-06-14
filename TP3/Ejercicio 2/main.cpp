#include <bits/stdc++.h>

using namespace std;
const int inf = INT_MAX;

int n, m;
vector<vector<int>> capacidad;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& pred) {
    fill(pred.begin(), pred.end(), -1);
    pred[s] = -2;
    queue<pair<int, int>> q;
    q.push(make_pair(s, inf));

    while (!q.empty()) {
        int act = q.front().first;
        int flujo = q.front().second;
        q.pop();

        for (int sig : adj[act]) {
            if (pred[sig] == -1 && capacidad[act][sig]) {
                pred[sig] = act;
                int nuevo_flujo = min(flujo, capacidad[act][sig]);
                if (sig == t)
                    return nuevo_flujo;
                q.push(make_pair(sig, nuevo_flujo));
            }
        }
    }

    return 0;
}

int maxflujo(int s, int t) {
    int flujo = 0;
    vector<int> pred(n);
    int nuevo_flujo;

    while (nuevo_flujo = bfs(s, t, pred)) {
        flujo += nuevo_flujo;
        int act = t;
        while (act != s) {
            int prev = pred[act];
            capacidad[prev][act] -= nuevo_flujo;
            capacidad[act][prev] += nuevo_flujo;
            act = prev;
        }
    }
    return flujo;
}



int main() {
    // IO rapido
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int cantCasos;
    cin >> cantCasos;
    while (cantCasos--){
        cin >> n >> m;
        capacidad.assign(n+2, vector<int>(n+2, 0));
        adj.assign(n+2, vector<int>());
        for (int i = 1; i < n + 1; i++){
            int x;
            cin >> x;
            if(x == 0){
                adj[0].push_back(i);
                capacidad[0][i] = 1;
            } else {
                adj[n + 1].push_back(i);
                capacidad[n + 1][i] = 1;
            }
        }
        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            capacidad[u][v] = 1;
            capacidad[v][u] = 1;
        }
        int res = maxflujo(0, n+1);
        cout << res << "\n";
    }
    return 0;
} 
