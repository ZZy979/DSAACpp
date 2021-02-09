#include "offline_equivalence_class.h"
#include "Stack/Array_stack.h"

int equivalence_class(int n, vector<vector<int>> relations)
{
	vector<vector<int>> adj(n);
	for (vector<int>& edge : relations) {
		adj[edge[0]].push_back(edge[1]);
		adj[edge[1]].push_back(edge[0]);
	}

	vector<bool> visited(n);
	Array_stack<int> unprocessed;
	vector<int> equivalence_class(n);
	int next_class = 0;
	for (int i = 0; i < n; ++i)
		if (!visited[i]) {
			visited[i] = true;
			unprocessed.push(i);
			equivalence_class[i] = next_class;
			while (!unprocessed.empty()) {
				int u = unprocessed.top();
				unprocessed.pop();
				for (int v : adj[u])
					if (!visited[v]) {
						visited[v] = true;
						unprocessed.push(v);
						equivalence_class[v] = next_class;
					}
			}
			++next_class;
		}
	return next_class;
}
