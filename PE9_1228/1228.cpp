#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Road {
    int weight;
    int destination;

    Road() : destination(0), weight(0) {}
    Road(int dest, int w) : destination(dest), weight(w) {}
};

const int MAX_NODES = 1000;

Road roads[MAX_NODES + 1][MAX_NODES];
int roadWeights[MAX_NODES];

pair<int, int*> countCost(int currentNode, int preNode, int signCost) {
    int maxRoadWeight = 0, totalSignCost = 0, preRoadWeight = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        int neighbor = roads[currentNode][i].destination;
        int roadWeight = roads[currentNode][i].weight;

        if (neighbor == 0){
            break;
        }

        maxRoadWeight = max(maxRoadWeight, roadWeight);
        if (neighbor == preNode){
            preRoadWeight = roadWeight;
        }
    }

    for (int i = 0; i < MAX_NODES; i++) {
        if (roads[currentNode][i].destination == 0){
            break;
        }

        totalSignCost = totalSignCost + signCost;
    }

    int* updatedValues = new int[MAX_NODES];
    fill(updatedValues, updatedValues + MAX_NODES, 0);

    for (int i = 0; i < MAX_NODES; i++) {
        int neighbor = roads[currentNode][i].destination;

        if (neighbor == 0){
            break;
        }

        if (neighbor == preNode){
            continue;
        }

        auto result = countCost(neighbor, currentNode, signCost);

        for (int j = 0; j < MAX_NODES; j++) {
        updatedValues[j] += result.second[j] + roadWeights[j] - roads[currentNode][i].weight;
        }

        totalSignCost += result.first;
    }

    int evenCost = totalSignCost;

    for (int i = 0; i < MAX_NODES; i++) {

        if (roadWeights[i] >= maxRoadWeight) {
        evenCost = min(evenCost, updatedValues[i] + (preNode ? roadWeights[i] - preRoadWeight : 0));
        updatedValues[i] = min(updatedValues[i], totalSignCost);
        } 
        else {
        updatedValues[i] = totalSignCost;
        }
    }

    return {evenCost, updatedValues};
}

    int main() {
    int numNodes, signCost, startNode, endNode, roadWeight;

    while (cin >> numNodes >> signCost) {
        fill_n(&roads[0][0], sizeof(roads) / sizeof(roads[0][0]), Road(0, 0));
        fill_n(roadWeights, MAX_NODES, 0);

        for (int i = 1; i < numNodes; i++) {
            cin >> startNode >> endNode >> roadWeight;

            int a = 0;
            while (roads[startNode][a].destination != 0){
                a++;
            }
            
            roads[startNode][a] = Road(endNode, roadWeight);

            int b = 0;
            while (roads[endNode][b].destination != 0){
                b++;
            }

            roads[endNode][b] = Road(startNode, roadWeight);

            roadWeights[i - 1] = roadWeight;
        }

        sort(roadWeights, roadWeights + numNodes - 1);
        int newSize = unique(roadWeights, roadWeights + numNodes - 1) - roadWeights;

        auto result = countCost(1, 0, signCost);
        cout << result.first << endl;
    }

    return 0;
}
