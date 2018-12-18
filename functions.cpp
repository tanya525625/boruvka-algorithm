#include "Header.h"

//  �������� �����
struct Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

// �������� �������
void boruvkaMST(struct Graph* graph)
{
	// ���������� ������ �� �����
	int V = graph->V, E = graph->E;
	Edge *edge = graph->edge;

	struct subset *subsets = new subset[V];

	//������ ��� �������� ������� ����� � ���������� �����
	int *cheapest = new int[V];

	//�������� ��������, ���� ��������� ������ �� ������ ��������
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
		cheapest[v] = -1;
	}

	// ���������� V ��������, ��� ����� 0
	// ����� ���������� ��������� ����� ���� ����������� �������� ������
	int numTrees = V;
	int MSTweight = 0;
	int countOp = 0;

	// ���� ����������� ��������� ����� ����������� �� ��� ���, 
	// ���� ��� ���������� �� ����������� � ������ ������ 
	clock_t start = clock();
	while (numTrees > 1)
	{
		for (int v = 0; v < V; ++v)
		{
			cheapest[v] = -1;
			countOp++;
		}

		// ������ ����� ��� �����
		for (int i = 0; i < E; i++)
		{
			// ����������� �������������� � ���������� 
			int set1 = find(subsets, edge[i].src, countOp);
			int set2 = find(subsets, edge[i].dest, countOp);
			countOp += 3;
			// ���� ����������� ������ ����������
			// �� ������������� ������ ������

			if (set1 == set2)
				continue;
			//countOp += 3;
			// ����� �������, �������� �� ������� �����
			// ������ � ������� �����, ��� ����������
			else
			{
				if (cheapest[set1] == -1 ||
					edge[cheapest[set1]].weight > edge[i].weight)
				{
					cheapest[set1] = i;
				}
					

				if (cheapest[set2] == -1 ||
					edge[cheapest[set2]].weight > edge[i].weight)
					cheapest[set2] = i;
			}
			countOp += 5;
		}

		// ���������� ����� � ���������� ����� � ������
		for (int i = 0; i < V; i++)
		{
			if (cheapest[i] != -1)
			{
				int set1 = find(subsets, edge[cheapest[i]].src, countOp);
				int set2 = find(subsets, edge[cheapest[i]].dest, countOp);

				if (set1 == set2)
					continue;
				MSTweight += edge[cheapest[i]].weight;
				//cout << "Edge included in MST: " << edge[cheapest[i]].src << " - "<<edge[cheapest[i]].dest << endl;

				// ����������� ��������� � ���������� ���������� ��������
				Union(subsets, set1, set2, countOp);
				numTrees--;
				countOp += 6;
			}
		}
	}
	clock_t end = clock();
	//cout << end - start << " ";
	cout << countOp << " " ;
	//cout << "Weight of MST is " << MSTweight << endl;
	return;
}

// ���������� ����������, ������� ����������� ����� � �������� i
int find(struct subset subsets[], int i, int &countOp)
{
	if (subsets[i].parent != i)
	{
		countOp+=2;
		subsets[i].parent =
			find(subsets, subsets[i].parent, countOp);
	}
		
	
	return subsets[i].parent;
}

// ����������� ���������
void Union(struct subset subsets[], int x, int y, int &countOp)
{
	int xroot = find(subsets, x, countOp);
	int yroot = find(subsets, y, countOp);
	countOp += 2;
	// ����������� �� �����
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	
	// ���� ����� �����
	// ����� ������ �� ��� � �������� �����, ���������� �����
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
	countOp += 3;
}

struct Graph* generator(int V, int E, struct Graph* graph)
{
	srand((unsigned int)time(NULL));
	int curE = 0;
	int div = E;

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			// ���������� ����� i-j 
			graph->edge[curE].src = i;
			graph->edge[curE].dest = j;
			// ����������� ���������
			graph->edge[curE].weight = rand() % 20 + 1;
			curE++;
			div--;
			if (div == 0)
				break;
		}
		if (div == 0)
			break;
	}

	return graph;
}

void test(int initCountV, int delta, int finCountV, int deltaE)
{
	int V = initCountV;
	int n = 0;
	//while (V != finCountV)
	while (n != 10)
	{
		int E = V + deltaE;
		struct Graph* graph = createGraph(V, E);
		graph = generator(V, E, graph);
		boruvkaMST(graph);
		//V += delta;
		V *= 2;
		n++;
	}
}

void test2(int initCountV, int E,  int deltaE)
{
	int V = initCountV;
	int n = 0;
	while (n != 10)
	{
		E = E + deltaE;
		struct Graph* graph = createGraph(V, E);
		graph = generator(V, E, graph);
		boruvkaMST(graph);
		n++;
	}
}