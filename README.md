# Traveling Salesman Problem
Given N points, plan the shortest path of traveling from start (point 0) to goal (point N-1). Meanwhile, all other points are visited at the end of the traversal.

## Brute Force
Generate every possible route from start to goal, and compare the length at the termination step. Pick the shortest length and output the route. Complexity: O(N!).
