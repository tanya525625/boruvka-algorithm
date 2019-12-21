#pragma once
#include <ctime>
#include <stdio.h> 
#include <iostream>

using namespace std;
// Структура ребра 
struct Edge
{
	// Начальная, конечная вершины и вес
	int src, dest, weight;
};

// Структура графа
struct Graph
{
	// Количество вершин и ребер
	int V, E;

	// Массив ребер
	Edge* edge;
};

// Структура компоненты
struct subset
{
	int parent;
	int rank;
};

int find(struct subset subsets[], int i, int &countOp);
void Union(struct subset subsets[], int x, int y, int &countOp);
void boruvkaMST(struct Graph* graph);
struct Graph* createGraph(int V, int E);
void test(int initCountV, int delta, int finCountV, int deltaE);
struct Graph* generator(int V, int E, struct Graph* graph);
void test2(int initCountV, int E, int deltaE);
