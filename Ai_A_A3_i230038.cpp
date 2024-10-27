#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game {
    public:

    string gID;
    string name;
    string developer;
    string publisher;
    float fSize;
    int downloads;
};

class Player {
    public:

    string pID;
    string name;
    string pNumber;
    string email;
    string pass;
    
    class GamesPlayed {
        public:
        string gID;
        float hoursPlayed;
        int achievementsUnl;
        GamesPlayed* next;
    } *gamesPlayed;
};

// Node of Player BST
class PlayerNode {
    public:
    Player player;
    PlayerNode* l;
    PlayerNode* r;
};

// Node of Game BST
class GameNode {
    public:
    Game game;
    GameNode* l;
    GameNode* r;
};


// Function for creating new Game Node
GameNode* createGameNode(const Game& game) {
    GameNode* newN = new GameNode;
    newN->game = game;
    newN->l = newN->r = nullptr;
    return newN;
}

// Function for insertion of Game in the Game BST
GameNode* insertGame(GameNode* root, const Game& game) {
    if (root == nullptr) {
        return createGameNode(game);
    }

    if (game.gID < root->game.gID) {
        root->l = insertGame(root->l, game);
    } else if (game.gID > root->game.gID) {
        root->r = insertGame(root->r, game);
    } else {
        cout<<"Error!!! The following game ID : "<<endl;
        cout<<game.gID<<" already exists."<<endl;
    }

    return root;
}

// Function to create a new Player node
PlayerNode* createPlayerNode(const Player& player) {
    PlayerNode* newN = new PlayerNode;
    newN->player = player;
    newN->l = newN->r = nullptr;
    return newN;
}

// Function to insert a Player into the BST
PlayerNode* insertPlayer(PlayerNode* root, const Player& player) {
    if (root == nullptr) {
        return createPlayerNode(player);
    }

    if (player.pID < root->player.pID) {
        root->l = insertPlayer(root->l, player);
    } else if (player.pID > root->player.pID) {
        root->r = insertPlayer(root->r, player);
    } else {
        cout<<"Error!!! The following Player ID : "<<endl;
        cout<<player.pID<<" already exists."<<endl;
    }

    return root;
}

// Printing Players
void printPlayers(PlayerNode* currNode) {
    if (currNode) {
        printPlayers(currNode->l);
        cout<<"Player ID: "<<currNode->player.pID<<endl;
        cout<<"Name: "<<currNode->player.name<<endl;
        printPlayers(currNode->r);
    }
}

// Printing Games
void printGames(GameNode* currNode) {
    if (currNode) {
        printGames(currNode->l);
        cout<<"Game ID: "<<currNode->game.gID<<endl;
        cout<<"Name: "<<currNode->game.name<<endl;
        printGames(currNode->r);
    }
}

// Skipping lines based on Roll No
bool shouldSkipLine(int lastRollNo) {
    int temp = (lastRollNo * 10) + 100;
    return rand() % 1000 < temp;
}

// Reading and Storing From Game File
void readGames(GameNode*& gameTree, const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Game game;
        getline(ss, game.gID, ',');
        getline(ss, game.name, ',');
        getline(ss, game.developer, ',');
        getline(ss, game.publisher, ',');
        ss >> game.fSize;
        ss.ignore();
        ss >> game.downloads;

        gameTree = insertGame(gameTree, game);
    }
}

// Reading and Storing Players from the file
void readPlayers(PlayerNode*& playerTree, const string& filename, int lastRollNo) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (shouldSkipLine(lastRollNo)) {
            //tells us to skip the line
            continue; 
        }

        stringstream ss(line);
        Player player;
        getline(ss, player.pID, ',');
        getline(ss, player.name, ',');
        getline(ss, player.pNumber, ',');
        getline(ss, player.email, ',');
        getline(ss, player.pass, ',');

        player.gamesPlayed = nullptr; 

        while (ss.good()) {
            string gID;
            float hoursPlayed;
            int achievementsUnl;

            getline(ss, gID, ',');
            ss >> hoursPlayed;
            ss.ignore();
            ss >> achievementsUnl;

            Player::GamesPlayed* newGame = new Player::GamesPlayed;
            newGame->gID = gID;
            newGame->hoursPlayed = hoursPlayed;
            newGame->achievementsUnl = achievementsUnl;
            newGame->next = player.gamesPlayed;
            player.gamesPlayed = newGame; 
        }

        playerTree = insertPlayer(playerTree, player);
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); 

    int rollNo;
    cout<<"Enter your Roll Number in the following format (e.g. 23xxxx): "<<endl;
    cin>>rollNo;
    
    int lastRollNo = rollNo % 100; //Last 2 digits of Roll no
    if(lastRollNo > 89){
        lastRollNo -+ 10;
    }

    GameNode* gameTree = nullptr;
    PlayerNode* playerTree = nullptr;


    readGames(gameTree, "Games.txt");
    

    readPlayers(playerTree, "Players.txt", lastRollNo);

    // Printing the Storred Games and Players Respectively
    cout<<"Stored Games:"<<endl;
    printGames(gameTree);

    cout<<"Stored Players:"<<endl;
    printPlayers(playerTree);

    return 0;
}
