Binary Search Tree-Based DBMS for Games and Players

This project is a Database Management System (DBMS) that manages and stores player and game data using Binary Search Trees (BSTs). 
This system provides functionalities for data insertion, retrieval, deletion, saving to a file, and more, all while ensuring efficiency through BST operations.

Project Overview
The DBMS loads datasets from CSV files and stores them in memory using BSTs, enabling efficient data management with minimal time complexity. 
Each player and game entry is stored as a node in their respective BST. The BST structure is particularly chosen to allow efficient insertion, deletion, and search operations.

Features and Thought Process
1. Data Storage in Memory
Data Structure: Player and Game data are stored in separate BSTs for efficient data management.
Implementation: Each node in the Player BST and Game BST represents a unique player or game. Primary keys (Player ID and Game ID) are used to maintain the tree's order and avoid duplicates.

2. Insertion
Logic: Before inserting a new node, the program checks for conflicts by comparing primary keys. Duplicate primary keys result in an error message.
Time Complexity: Average case 𝑂(log𝑛) and worst case O(n) for unbalanced trees.

3. Search and Retrieval
Logic: The DBMS allows searching for a player or game by ID. The search returns the node for viewing or modification.
Time Complexity: O(logn) for balanced trees.

4. Deletion
Logic: Nodes can be deleted by specifying their ID. The deletion process ensures proper restructuring of the tree and no memory leaks.
Time Complexity:  O(logn) on average, O(n) in the worst case for unbalanced trees.

5. Save Data to File
Logic: The system saves the data from memory to CSV files using Preorder Traversal. This allows for the same structure restoration upon reloading.
Time Complexity: O(n).

6. Show N Layers
Logic: Displays the tree up to the specified N layers. If N exceeds the actual layers, a warning is displayed.
Time Complexity: O(n).

7. Show Layer Number
Logic: Given a primary key, returns the layer number of the node in the tree.
Time Complexity: O(logn) for balanced trees.

8. Show Path
Logic: Prints the path to reach a specific node based on its primary key, using preorder traversal.
Time Complexity: O(logn) on average.

9. Edit Entry
Logic: The user can edit any entry, including primary keys. Post-editing, the node is repositioned in the tree if required.
Time Complexity: O(logn) for search and insertion.

10. Top N Players
Logic: Identifies the top N players based on the number of games played.
Time Complexity: O(nlogn), as it involves sorting players by game count.

11. Show Player Details
Logic: Displays the details of a player and all games played by them.
Time Complexity: O(n), as it includes traversing the player's games.

12. Check if Player Has Played a Specific Game
Logic: Checks if a player has played a specific game using Player ID and Game ID.
Time Complexity: O(2logn), ensuring efficient lookup in the worst case.
