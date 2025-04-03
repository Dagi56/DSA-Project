/*
             Our Project Title is Campus Navigator
        The CampusNavigator program is a comprehensive C++ implementation designed to model and navigate
     a campus environment using graph theory concepts. In This  program we tried to provides essential functionalities
     for managing buildings (nodes) and pathways (edges) between them, along with various algorithms to
     analyze and traverse the campus layout.  in this implementation  we Attempts to demonstrate practical
     applications of data structures and algorithms in solving real-world navigation problems.

        */

    //  The other point is that We also tried to include information(buildings, paths etc..) which may Available in campus
    // here we attempt to design our project program by using code block Editor.

   //    Name of Group members                                   id no

  //  1. Anwar Muhammad Ebrahim............................GUR/01580/15
  //  2. Anwar MOhammed Kebede............................GUR/02280/15
  //  3.Murad Baye ........................................GUR/01631/15
  //  4.Dagim Alene .......................................GUR/01928/15
  //  5. Amanuel Tesfaye....................................GUR/02602/15

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;
class CampusNavigator {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;
    // Helper function for Dijkstra's algorithm
    vector<string> getShortestPath(const string& start, const string& end) {
        unordered_map<string, int> distances;
        unordered_map<string, string> predecessors;
        set<pair<int, string>> pq; // (distance, building)
        // Initialize distances
        for (const auto& entry : adjList) {
            distances[entry.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.insert({0, start});
        while (!pq.empty()) {
            string current = pq.begin()->second;
            pq.erase(pq.begin());
            for (const auto& neighbor : adjList[current]) {
                string next = neighbor.first;
                int weight = neighbor.second;
                int newDist = distances[current] + weight;
                if (newDist < distances[next]) {
                    pq.erase({distances[next], next});
                    distances[next] = newDist;
                    predecessors[next] = current;
                    pq.insert({newDist, next});
                }
            }
        }
        //Now we will Reconstruct the  path
        vector<string> path;
        if (distances[end] == numeric_limits<int>::max()) {
            return path; // No path exists
        }
        for (string at = end; at != start; at = predecessors[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
public:
    void addEdge(const string& building1, const string& building2, int weight) {
        adjList[building1].emplace_back(building2, weight);
        adjList[building2].emplace_back(building1, weight);
    }
    void deleteNode(const string& building) {
        for (auto& entry : adjList) {
            auto& edges = entry.second;
            edges.erase(
                remove_if(edges.begin(), edges.end(),
                    [&building](const pair<string, int>& edge) {
                        return edge.first == building;
                    }
                ),
                edges.end()
            );
        }
        adjList.erase(building);
    }
    void updateWeight(const string& building1, const string& building2, int newWeight) {
        for (auto& edge : adjList[building1]) {
            if (edge.first == building2) {
                edge.second = newWeight;
                break;
            }
        }
        for (auto& edge : adjList[building2]) {
            if (edge.first == building1) {
                edge.second = newWeight;
                break;
            }
        }
    }
    void depthFirstTraversal(const string& start) {
        unordered_map<string, bool> visited;
        stack<string> s;
        s.push(start);
        cout << "DFS Traversal :- ";
        while (!s.empty()) {
            string current = s.top();
            s.pop();
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                for (const auto& neighbor : adjList[current]) {
                    if (!visited[neighbor.first]) {
                        s.push(neighbor.first);
                    }
                }
            }
        }
        cout << endl;
    }
    void breadthFirstTraversal(const string& start) {
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;
        cout << "BFS Traversal :- ";
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";
            for (const auto& neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
    void displayCampus() {
        for (const auto& pair : adjList) {
            cout << " "<< pair.first ;
            for (const auto& neighbor : pair.second) {
                cout << " " << neighbor.first << " ==> " << neighbor.second << " ";
            }
            cout <<" "<< endl;
        }
    }
    // Public method to show shortest path
    void showShortestPath(const string& start, const string& end) {
        vector<string> path = getShortestPath(start, end);
        if (path.empty()) {
            cout << "\nNo path exists from " << start << " to " << end << endl;
            return;
        }
        cout << "\nShortest path from " << start << " to " << end << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " --> ";
            }
        }
        // Calculate total distance
        int totalDistance = 0;
        for (size_t i = 0; i < path.size() - 1; i++) {
            for (const auto& edge : adjList[path[i]]) {
                if (edge.first == path[i+1]) {
                    totalDistance += edge.second;
                    break;
                }
            }
        }
        cout << "\nTotal distance: " << totalDistance << endl;
    }
};
int main() {
    CampusNavigator navigator;
    // Enhanced campus map with Some buildings and paths
    navigator.addEdge("Main Library", "Cafeteria", 1);
    navigator.addEdge("Main Library", "Gate-way", 1);
    navigator.addEdge("Main Library", "Computer Lab", 2);
    navigator.addEdge("Main Library", "Registrar", 2);
    navigator.addEdge("Cafeteria", "Gym", 1);
    navigator.addEdge("Gym", "Dormitory", 3);
    navigator.addEdge("Gym", "Game Zone", 3);
    navigator.addEdge("Computer Lab", "Dormitory", 2);
    navigator.addEdge("Dormitory", "Main Office", 1);
    navigator.addEdge("Dormitory", "Lounge", 2);
    navigator.addEdge("Lounge", "Stadium", 1);
    navigator.addEdge("Lounge", " Tele-Shop", 2);
    navigator.addEdge("Main Office", "Lecture Hall 1", 2);
    navigator.addEdge("Lecture Hall 1", "Lecture Hall 2", 1);
    navigator.addEdge("Lecture Hall 2", "Administration", 2);
    navigator.addEdge("Administration", "Parking Lot", 1);
    navigator.addEdge("Game Zone", "Recreation center", 2);
    navigator.addEdge("Recreation center", "Cafeteria", 1);
    navigator.addEdge("Registrar", "Health Center", 1);
    navigator.addEdge("Health Center", "Parking Lot", 2);
    cout << "  The buildings and paths that may Available in the  Campus Layout is :- " << endl;
    navigator.displayCampus();
    // Example  for  traversals
    navigator.depthFirstTraversal("Main Library");
    navigator.breadthFirstTraversal("Main Library");
    // Here is an Example for weight update
    navigator.updateWeight("Main Library", "Cafeteria", 5);
    cout << "\nUpdated campus layout after changing weight:" << endl;
    navigator.displayCampus();
    // Here is an Example for node deletion
    navigator.deleteNode("Cafeteria");
    cout << "\nCampus layout after deleting Cafeteria:" << endl;
    navigator.displayCampus();
    // Here we have Tried to include  Some Examples to find the shortest paths
    cout << "\n there are some Shortest Path Examples:" << endl;
    navigator.showShortestPath("Dormitory", "Gym");
    navigator.showShortestPath("Main Library", "Administration");
    navigator.showShortestPath("Gate-way", "Stadium");
    navigator.showShortestPath("Computer Lab", "Parking Lot");
    navigator.showShortestPath("Game Zone", "Health Center");
    navigator.showShortestPath("Lecture Hall 1", "Recreation center");
    navigator.showShortestPath("Registrar", "Tele-Shop");
    navigator.showShortestPath("Stadium", "Parking Lot");
    navigator.showShortestPath("Dormitory", "Lecture Hall 2");
    return 0;
}
