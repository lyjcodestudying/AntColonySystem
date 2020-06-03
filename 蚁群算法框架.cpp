#include<cmath>
#include<iostream>
#include<cstdlib>

#define numNodes 100
#define numAnts 100
#define numTimes 5
#define numPaths 340
using namespace std;

double Adjacent[numNodes][numNodes];
double LightPath[numPaths][2];

bool iterateCondition(int start,int end) {
	return true;
}

class AntColonySystem {
	double info[numNodes][numNodes];//record the concertration of pheromone
	double visible[numNodes][numNodes];
	int* shortestPath[numNodes][numNodes];
public:
	AntColonySystem() {
		for (int i = 0; i < numNodes; i++)for (int j = 0; j < numNodes; j++)info[i][j] = 0, visible[i][j] = 0, shortestPath[i][j] = nullptr;
	}
	//init or redefine value of arrays 'info' and 'visible'
	void InitParameter(double value);
	//calculate probability of transition
	double TransProbability(int from, int to);
	//update pheromone: every step ants walk, leave its pheromone
	void UpdateLocalPathRule(int from, int to);
	//update pheromone: follow the best path, leave its pheromone
	void UpdateGlobalPathRule(int* shortestPath, int globalBestLength);
};

class ACSAnt {
	AntColonySystem antColony;
	int startNode;
	int endNode;
	int curNode;
	int allowed[numNodes];
	int Tour[numNodes][numNodes];//record the ant's current path
public:
	ACSAnt(AntColonySystem acs) {
		antColony = acs;
	}
	void setSE(int from, int to) { startNode = from; endNode = to; }
	int* Search();
	int Choose();//choose next node under some rules
	int MoveToNextNode(int nextNode);//deal with action of moving to next node
};



int main() {
	/*
		TODO1: transform data from file into matrix 'Adjecant' and 'LightPath'
	*/
	/*
		TODO2: calculate the shrotest distance between adjacent nodes, and delete the impossible paths
	*/
	//above is pre-processing

	AntColonySystem* ACS = new AntColonySystem();//initialize the info and visible parameter
	ACSAnt* Ants[numAnts];
	for (int i = 0; i < numAnts; i++) {
		Ants[i] = new ACSAnt(ACS);
	}

	int start = 0, end = 0;
	for (int path = 0; path < numPaths; path++) {
		start = LightPath[path][0], end = LightPath[path][1];
			//using an if statement could reduce the amount of computation to focus on a single (start,end) pair's shortest path finding 
			if (!iterateCondition(start,end)) continue;
			for (int time = 0; time < numTimes; time++) {//runing several times to gather priori knowledge of pheromone
				for (int i = 0; i < numAnts; i++) {
					Ants[i]->setSE(start, end);
				}
				/*
					TODO3:
					make every ants have an searching action and leave its pheromone on ACS map
					and compare and record its shortest paths every time it runs
				*/
			}
		
	}

	//below is post-processing
	/*
		TODO4: transform the current structure of path into file
	*/

	delete ACS;
	for (int i = 0; i < numAnts; i++) {
		delete Ants[i];
	}
}