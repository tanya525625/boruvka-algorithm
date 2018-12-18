#include "Header.h"

//  Создание графа
struct Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

// Алгоритм Борувки
void boruvkaMST(struct Graph* graph)
{
	// Извлечение данных из графа
	int V = graph->V, E = graph->E;
	Edge *edge = graph->edge;

	struct subset *subsets = new subset[V];

	//Массив для хранения индекса ребра с наименьшим весом
	int *cheapest = new int[V];

	//Создание множеств, пока состоящих только из одного элемента
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
		cheapest[v] = -1;
	}

	// Изначально V деревьев, вес равен 0
	// После выполнения алгоритма будет одно минимальное остовное дерево
	int numTrees = V;
	int MSTweight = 0;

	// Цикл объдинения компонент будет происходить до тех пор, 
	// пока все компоненты не объединятся в единое дерево 
	clock_t start = clock();
	while (numTrees > 1)
	{
		for (int v = 0; v < V; ++v)
		{
			cheapest[v] = -1;
		}

		// Проход через все ребра
		for (int i = 0; i < E; i++)
		{
			// Определение принадлежности к компаненте 
			int set1 = find(subsets, edge[i].src);
			int set2 = find(subsets, edge[i].dest);

			// Если принадлежат единой компоненте
			// Не рассматриваем данный случай
			if (set1 == set2)
				continue;

			// Иначе смотрим, является ли текущее ребро
			// ребром с меньшим весом, чем предыдущие
			else
			{
				if (cheapest[set1] == -1 ||
					edge[cheapest[set1]].weight > edge[i].weight)
					cheapest[set1] = i;

				if (cheapest[set2] == -1 ||
					edge[cheapest[set2]].weight > edge[i].weight)
					cheapest[set2] = i;
			}
		}

		// Добавление ребер с наименьшим весом в дерево
		for (int i = 0; i < V; i++)
		{
			if (cheapest[i] != -1)
			{
				int set1 = find(subsets, edge[cheapest[i]].src);
				int set2 = find(subsets, edge[cheapest[i]].dest);

				if (set1 == set2)
					continue;
				MSTweight += edge[cheapest[i]].weight;
				//cout << "Edge included in MST: " << edge[cheapest[i]].src << " - "<<edge[cheapest[i]].dest << endl;

				// Объединение компонент и уменьшение количества деревьев
				Union(subsets, set1, set2);
				numTrees--;
			}
		}
	}
	clock_t end = clock();
	cout << end - start << endl;
	//cout << "Weight of MST is " << MSTweight << endl;
	return;
}

struct Graph* generator(int V, int E, struct Graph* graph)
{
	srand((unsigned int)time(NULL));
	int curE = 0;
	int div = E;
	while (div != 0)
	{
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				// Добавление ребра i-j 
				graph->edge[curE].src = i;
				graph->edge[curE].dest = j;
				// Обеспечение связности
				graph->edge[curE].weight = rand() % 20 + 1;
				curE++;
				div--;
				if (div == 0)
					break;
			}
			if (div == 0)
				break;
		}
	}
	return graph;
}

void test(int initCountV, int delta, int finCountV, int deltaE) 
{
	int V = initCountV;
	while (V != finCountV)
	{
		int E = V + deltaE;
		struct Graph* graph = createGraph(V, E);
		graph = generator(V, E, graph);
		boruvkaMST(graph);
		V += delta;
	}
}

// Нахождение компоненты, которой принадлежит ребро с индексом i
int find(struct subset subsets[], int i)
{
	if (subsets[i].parent != i)
		subsets[i].parent =
		find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

// Объединение компонент
void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// Объединение по рангу
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	// Если ранги равны
	// Выбор одного из них в качестве корни, увеличение ранга
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}
