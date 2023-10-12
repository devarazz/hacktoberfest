using System;
using System.Collections.Generic;

public class Dijkstra
{
    public static Dictionary<char, int> FindShortestDistances(Dictionary<char, Dictionary<char, int>> graph, char start)
    {
        Dictionary<char, int> distances = new Dictionary<char, int>();
        foreach (char node in graph.Keys)
        {
            distances[node] = int.MaxValue;
        }
        distances[start] = 0;

        SortedSet<(int, char)> priorityQueue = new SortedSet<(int, char)>();
        priorityQueue.Add((0, start));

        while (priorityQueue.Count > 0)
        {
            (int currentDistance, char currentNode) = priorityQueue.Min;
            priorityQueue.Remove(priorityQueue.Min);

            if (currentDistance > distances[currentNode])
                continue;

            foreach (var (neighbor, weight) in graph[currentNode])
            {
                int distance = currentDistance + weight;

                if (distance < distances[neighbor])
                {
                    distances[neighbor] = distance;
                    priorityQueue.Add((distance, neighbor));
                }
            }
        }

        return distances;
    }

    public static void Main(string[] args)
    {
        Dictionary<char, Dictionary<char, int>> graph = new Dictionary<char, Dictionary<char, int>>()
        {
            { 'A', new Dictionary<char, int> { { 'B', 1 }, { 'C', 4 } } },
            { 'B', new Dictionary<char, int> { { 'A', 1 }, { 'C', 2 }, { 'D', 5 } } },
            { 'C', new Dictionary<char, int> { { 'A', 4 }, { 'B', 2 }, { 'D', 1 } } },
            { 'D', new Dictionary<char, int> { { 'B', 5 }, { 'C', 1 } } }
        };

        char startNode = 'A';

        Dictionary<char, int> shortestDistances = FindShortestDistances(graph, startNode);

        foreach (var (node, distance) in shortestDistances)
        {
            Console.WriteLine($"Shortest distance from {startNode} to {node} is {distance}");
        }
    }
}
