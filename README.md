# MitkademEx4
This is a project created by Ron Sherman and Amit Nir.
This project determines which search algorithm is the best, between BFS, DFS, AStar, BestSearch.
The problems the server handles in this case are search problems but can be modified with the help of generics which are well spread in the project (we used it to solve search problems on matrices).

# Server
There are two server options in this project: Parallel and Serial, the first one deals  with clients simultaneously, while the other does that one at a time.

# Client
The clients are giving the server problems and with the use of cache and file saving system, with the help of a client handler, we can return the solution to their problem.

# Compile & Run
```bash
g++ -std=c++14 *.cpp -o __name__ -pthread
```

# git 
https://github.com/Ron123456/MitkademEx4
