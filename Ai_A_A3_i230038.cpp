#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


template <typename T>
class qNode{
public:
    T data;
    qNode* next;
    qNode(T d){
        data = d;
        next = nullptr;
    }
};

template <typename T>
class Queue {
private:
    qNode<T>* fr;
    qNode<T>* rear;

public:
    Queue(){
        fr = nullptr;
        rear = nullptr;
    }

    bool isEmpty(){
        return fr == nullptr;
    }

    void enqueue(T data){
        qNode<T>* newNode = new qNode<T>(data);
        if(rear != nullptr){
            rear->next = newNode;
        }else{
            fr = newNode;
        }
        rear = newNode;
    }

    T dequeue(){
        if(isEmpty()){
            cout<<"Queue is empty !!! :("<<endl;
        }
        qNode<T>* tempPtr = fr;
        T data = tempPtr->data;
        fr = fr->next;
        if(!fr){
            rear = nullptr;
        }
        delete tempPtr;
        return data;
    }
};

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

// Function to delete Game
GameNode* deleteGame(GameNode* root, const string& gID) {
    if (root == nullptr) {
        cout<<"Game ID not found!!! :("<<endl;
        return root;
    }

    if (gID < root->game.gID) {
        root->l = deleteGame(root->l, gID);
    } else if (gID > root->game.gID) {
        root->r = deleteGame(root->r, gID);
    } else {
        // Node with has either one child or no child
        if (root->l == nullptr) {
            GameNode* temp = root->r;
            delete root;
            return temp;
        } else if (root->r == nullptr) {
            GameNode* temp = root->l;
            delete root;
            return temp;
        }

        // Node which has two children
        GameNode* temp = root->r;
        while (temp && temp->l != nullptr) {
            temp = temp->l;
        }
        root->game = temp->game;
        root->r = deleteGame(root->r, temp->game.gID);
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

PlayerNode* deletePlayer(PlayerNode* root, const string& pID) {
    if (root == nullptr) {
        cout<<"Player ID not found!!! :("<<endl;
        return root;
    }

    if (pID < root->player.pID) {
        root->l = deletePlayer(root->l, pID);
    } else if (pID > root->player.pID) {
        root->r = deletePlayer(root->r, pID);
    } else {
        // Node having either one child or no child
        if (root->l == nullptr) {
            PlayerNode* temp = root->r;
            delete root;
            return temp;
        } else if (root->r == nullptr) {
            PlayerNode* temp = root->l;
            delete root;
            return temp;
        }

        // Node having  two children
        PlayerNode* temp = root->r;
        while (temp && temp->l != nullptr) {
            temp = temp->l;
        }
        root->player = temp->player;
        root->r = deletePlayer(root->r, temp->player.pID);
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
        ss>>game.fSize;
        ss.ignore();
        ss>>game.downloads;

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
            ss>>hoursPlayed;
            ss.ignore();
            ss>>achievementsUnl;

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

// Searching for Game by its ID
GameNode* searchGame(GameNode* root, const string& gID) {
    if (root == nullptr || root->game.gID == gID) {
        return root;
    }

    if (gID < root->game.gID) {
        return searchGame(root->l, gID);
    }
    return searchGame(root->r, gID);
}

// Searching for Player by its ID
PlayerNode* searchPlayer(PlayerNode* root, const string& pID){
    if (root == nullptr || root->player.pID == pID) {
        return root;
    }

    if(pID < root->player.pID){
        return searchPlayer(root->l, pID);
    }
    return searchPlayer(root->r, pID);
}

// Save Game Data Preorder
void saveGPreorder(GameNode* root, ofstream& outFile){
    if (root == nullptr) {
        return;
    }
    outFile<<root->game.gID<<','<<root->game.name<<','<<root->game.developer<<','<<root->game.publisher<<','<<root->game.fSize<<','<<root->game.downloads<<endl;

    // Using Recursion
    saveGPreorder(root->l, outFile);
    saveGPreorder(root->r, outFile);
}

// save Player Data PReorder
void savePPreorder(PlayerNode* root, ofstream& outFile){
    if (root == nullptr){
        return;
    } 

    outFile<<root->player.pID<<','<<root->player.name<<','<<root->player.pNumber<<','<<root->player.email<<','<<root->player.pass;

    Player::GamesPlayed* gameCurrPtr = root->player.gamesPlayed;
    while (gameCurrPtr != nullptr) {
        outFile<<','<<gameCurrPtr->gID<<','<<gameCurrPtr->hoursPlayed<<','<<gameCurrPtr->achievementsUnl;
        gameCurrPtr = gameCurrPtr->next;
    }
    outFile<<endl;

    // Using Recursion
    savePPreorder(root->l, outFile);
    savePPreorder(root->r, outFile);
}

// Saving to CSV
void saveData(GameNode* gameTree, PlayerNode* playerTree,const string& gFileN, const string& pFileN) {
    ofstream gFile(gFileN);
    ofstream pFile(pFileN);


    if(gFile.is_open()){
        saveGPreorder(gameTree, gFile);
        gFile.close();
        cout<<"Game data saved successfully to "<<gFileN<<endl;
    }else{
        cout<<"Error opening game file for writing."<<endl;
    }

    if(pFile.is_open()){
        savePPreorder(playerTree, pFile);
        pFile.close();
        cout<<"Congrats !!! :) Player data saved successfully to "<<pFileN<<endl;
    }else{
        cout<<"Error!!! :( File is not openning"<<endl;
    }
}


template <typename NodeType>
struct layerNode {
    NodeType* node;
    int layer;

    layerNode(){
        node = nullptr;
        layer = 0;
    }

    layerNode(NodeType* n, int l) {
        node = n;
        layer = l;

    }
};

// show N layers of Game Tree
void showGNLayers(GameNode* root, int N) {
    if (!root) {
        cout<<"Game tree is empty!!! :("<<endl;
        return;
    }

    Queue<layerNode<GameNode>> q;
    q.enqueue(layerNode<GameNode>(root, 1));
    int lastLayer = 1;

    while (!q.isEmpty()) {
        layerNode<GameNode> currLayerNode = q.dequeue();
        GameNode* currNode = currLayerNode.node;
        int layer = currLayerNode.layer;

        if(layer > N){
            cout<<"Layer Limit was Reached, can't go further"<<endl;
            return;
        }

        cout<<"Layer is : "<<layer<<endl;
        cout<<"Game ID is : "<<currNode->game.gID<<" and Name is : "<<currNode->game.name<<endl;

        if (currNode->l){
             q.enqueue(layerNode<GameNode>(currNode->l, layer + 1));
        }
        if (currNode->r){
            q.enqueue(layerNode<GameNode>(currNode->r, layer + 1));
        } 
        lastLayer = layer;
    }

    if(lastLayer < N){
        cout<<"Layer Limit was Reached, can't go further"<<endl;
    }
}

// Show N layers of Player Tree
void showPNLayers(PlayerNode* root, int N){
    if (!root) {
        cout<<"Player tree is empty!"<<endl;
        return;
    }

    Queue<layerNode<PlayerNode>> q;
    q.enqueue(layerNode<PlayerNode>(root, 1));
    int lastLayer = 1;

    while (!q.isEmpty()) {
        layerNode<PlayerNode> currLayerNode = q.dequeue();
        PlayerNode* currNode = currLayerNode.node;
        int layer = currLayerNode.layer;

        if(layer > N){
            cout<<"Layer Limit was Reached, can't go further"<<endl;
            return;
        }

        cout<<"Layer is : "<<layer<<endl;
        cout<<"Player ID is: "<<currNode->player.pID<<" and Name is: "<<currNode->player.name<<endl;

        if (currNode->l){
            q.enqueue(layerNode<PlayerNode>(currNode->l, layer + 1));
        } 

        if (currNode->r){
            q.enqueue(layerNode<PlayerNode>(currNode->r, layer + 1));
        } 
        lastLayer = layer;
    }

    if(lastLayer < N){
        cout<<"Layer Limit was Reached, can't go further"<<endl;
    }
}


// Find layer of Game by ID
int findGameLayer(GameNode* root, const string& gID) {
    int layer = 1;
    GameNode* currPtr = root;

    while (currPtr){
        if (currPtr->game.gID == gID) {
            return layer;
        } else if (gID < currPtr->game.gID) {
            currPtr = currPtr->l;
        } else {
            currPtr = currPtr->r;
        }
        layer++;
    }
    //Not found
    return -1;
}

// Find layer of  Player by ID
int findPlayerLayer(PlayerNode* root, const string& pID) {
    int layer = 1;
    PlayerNode* currPtr = root;

    while (currPtr) {
        if (currPtr->player.pID == pID) {
            return layer;
        } else if (pID < currPtr->player.pID) {
            currPtr = currPtr->l;
        } else {
            currPtr = currPtr->r;
        }
        layer++;
    }
    // Not found
    return -1;
}


int main() {
    srand(static_cast<unsigned>(time(0))); 

    int rollNo;
    cout<<"Enter your Roll Number in the following format (e.g. 23xxxx): "<<endl;
    cin>>rollNo;
    
    int lastRollNo = rollNo % 100; //Last 2 digits of Roll no
    if(lastRollNo > 89){
        lastRollNo -= 10;
    }

    GameNode* gameTree = nullptr;
    PlayerNode* playerTree = nullptr;


    readGames(gameTree, "Games.txt");
    

    readPlayers(playerTree, "Players.txt", lastRollNo);

    // Printing the Stored Games and Players Respectively
    // cout<<"Stored Games:"<<endl;
    // printGames(gameTree);

    // cout<<"Stored Players:"<<endl;
    // printPlayers(playerTree);


    string searchGID, searchPID;
    cout<<"Enter the Game ID to search: (e.g. 9831286229)";
    cin>>searchGID;
    GameNode* foundGame = searchGame(gameTree, searchGID);
    if(foundGame){
        cout<<"Game Found!"<<endl;
        cout<<"Game ID: "<<foundGame->game.gID<<endl;
        cout<<"Name: "<<foundGame->game.name<<endl;
        cout<<"Developer: "<<foundGame->game.developer<<endl;
        cout<<"Publisher: "<<foundGame->game.publisher<<endl;
        cout<<"Size: "<<foundGame->game.fSize<<" GB"<<endl;
        cout<<"Downloads: "<<foundGame->game.downloads<<endl;
    }else{
        cout<<"Game not found!"<<endl;
    }

    cout<<"Enter the Player ID to search: (e.g. 0295971126) ";
    cin>>searchPID;
    PlayerNode* isFoundPlayer = searchPlayer(playerTree, searchPID);
    if(isFoundPlayer){
        cout<<"Player Found!!! :)"<<endl;
        cout<<"Player ID : "<<isFoundPlayer->player.pID<<endl;
        cout<<"Name : "<<isFoundPlayer->player.name<<endl;
        cout<<"Phone Number : "<<isFoundPlayer->player.pNumber<<endl;
        cout<<"Email : "<<isFoundPlayer->player.email<<endl;
    }else{
        cout<<"Player not found!!! :("<<endl;
    }


    string deleteGID, deletePID;
    cout<<"Enter the Game ID to delete: ";
    cin>>deleteGID;
    gameTree = deleteGame(gameTree, deleteGID);

    cout<<"Enter the Player ID to delete : ";
    cin>>deletePID;
    playerTree = deletePlayer(playerTree, deletePID);

    // cout<<"New Stored Games are :"<<endl;
    // printGames(gameTree);
    // cout<<"New Stored Players are :"<<endl;
    // printPlayers(playerTree);

    saveData(gameTree, playerTree, "saveGames.csv", "savePlayers.csv");

    int noOfLayers;
    cout<<"Enter the number of layers : "<<endl;
    cin>>noOfLayers;

    cout<<"Game Tree Layers are : "<<endl;
    showGNLayers(gameTree , noOfLayers);

    cout<<"Player Tree Layers are : "<<endl;
    showPNLayers(playerTree , noOfLayers);


    string searchGIDLayer, searchPIDLayer;
    cout<<"Enter the Game ID whose layer you want to find: (e.g. 0533242523 )"<<endl;
    cin>>searchGIDLayer;
    int gLayer = findGameLayer(gameTree, searchGIDLayer);
    if(gLayer != -1){
        cout<<"This Game ID "<<searchGIDLayer<<" is found at this layer number: "<<gLayer<<endl;
    }else{
        cout<<"Game ID not found in the tree. :("<<endl;
    }

    cout<<"Enter the Player ID whose layer you want to find:  (e.g. 0024285437 )"<<endl;
    cin>>searchPIDLayer;
    int plLayer = findPlayerLayer(playerTree, searchPIDLayer);
    if(plLayer != -1){
        cout<<" This Player ID : "<<searchPIDLayer<<" is found at this layer number : "<<plLayer<<endl;
    }else{
        cout<<"Player ID not found in the tree. :("<<endl;
    }


    return 0;
}

