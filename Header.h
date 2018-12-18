#pragma once
#include <ctime>
#include <stdio.h> 
#include <iostream>

using namespace std;
// ��������� ����� 
struct Edge
{
	// ���������, �������� ������� � ���
	int src, dest, weight;
};

// ��������� �����
struct Graph
{
	// ���������� ������ � �����
	int V, E;

	// ������ �����
	Edge* edge;
};

// ��������� ����������
struct subset
{
	int parent;
	int rank;
};

int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
void boruvkaMST(struct Graph* graph);
struct Graph* createGraph(int V, int E);
void test(int initCountV, int delta, int finCountV, int deltaE);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);