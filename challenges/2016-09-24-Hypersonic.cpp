// Hypersonic Challenge
// Xavier Morel - 2016-09-24
// Ranking 1070/2715 (blehhh)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

#define ITEM_MAX_DISTANCE 10
#define COMPUTATION_MAX_DISTANCE 50

#define TYPE_PLAYER 0
#define TYPE_BOMB 1
#define TYPE_ITEM 2

#define TILE_EMPTY '.'
#define TILE_BOX '0'
#define TILE_BONUS_BOMB '1'
#define TILE_BONUS_REACH '2'
#define TILE_WALL 'X'
#define TILE_BOMB 'B'
#define TILE_ITEM 'I'

int width = 0;
int height = 0;

class Coords {
public:
    int x;
    int y;
    Coords() : x(-1), y(-1) {}
    Coords(int x, int y) : x(x), y(y) {}

    Coords above()
        {
            return Coords(x, y - 1);
        }

    Coords below()
        {
            return Coords(x, y + 1);
        }

    Coords leftOf()
        {
            return Coords(x - 1, y);
        }

    Coords rightOf()
        {
            return Coords(x + 1, y);
        }

    inline void up()
        {
            --y;
        }

    inline void down()
        {
            ++y;
        }

    inline void left()
        {
            --x;
        }

    inline void right()
        {
            ++x;
        }

    inline bool isValid()
        {
            return x >= 0 && y >= 0 && x < width && y < height;
        }
};

class Tile {
public:
    int score;
    char type;
    bool danger;
    bool reachable;

    Tile() : score(0), danger(false), reachable(false), type(TILE_EMPTY) {}

    inline bool isBox()
        {
            return (type == TILE_BOX || type == TILE_BONUS_BOMB || type == TILE_BONUS_REACH);
        }

    inline bool isBlocking()
        {
            return !isFree();
        }

    inline bool isFree()
        {
            return (type == TILE_EMPTY || type == TILE_ITEM);
        }

    inline bool isWalkable()
        {
            return isFree() && !isDanger();
        }

    inline bool isDanger()
        {
            return danger;
        }

    inline bool isItem()
        {
            return (type == TILE_ITEM);
        }

    inline bool isReachable()
        {
            return reachable;
        }
};

class Board {
private:
    vector<vector<Tile>> tiles;

public:
    Board() {}

    void reset()
        {
            // TODO ...
            tiles.clear();
        }

    void addRow(string row)
        {
            vector<Tile> row_tiles;
            for (int i = 0; i < row.size(); i++) {
                Tile tile;
                tile.type = row.at(i);
                row_tiles.push_back(tile);
            }

            tiles.push_back(row_tiles);
        }

    inline Tile get(Coords pos)
        {
            return tiles.at(pos.y).at(pos.x);
        }

    void setBomb(Coords pos, int reach, int danger)
        {
            tiles.at(pos.y).at(pos.x).type = TILE_BOMB;
            tiles.at(pos.y).at(pos.x).danger = true;

            for (Coords c = pos.leftOf(); c.isValid(); c.left()) {
                //            cerr << "See if I can set danger at " << c.x << " " << c.y << endl;
                if (get(c).isFree()) {
                    //                cerr << "Set danger at " << c.x << " " << c.y << endl;
                    tiles.at(c.y).at(c.x).danger = true;
                }
                else {
                    break;
                }
            }
            for (Coords c = pos.rightOf(); c.isValid(); c.right()) {
                //            cerr << "See if I can set danger at " << c.x << " " << c.y << endl;
                if (get(c).isFree()) {
                    //                cerr << "Set danger at " << c.x << " " << c.y << endl;
                    tiles.at(c.y).at(c.x).danger = true;
                }
                else {
                    break;
                }
            }
            for (Coords c = pos.above(); c.isValid(); c.up()) {
                //            cerr << "See if I can set danger at " << c.x << " " << c.y << endl;
                if (get(c).isFree()) {
                    //                cerr << "Set danger at " << c.x << " " << c.y << endl;
                    tiles.at(c.y).at(c.x).danger = true;
                }
                else {
                    break;
                }
            }
            for (Coords c = pos.below(); c.isValid(); c.down()) {
                //            cerr << "See if I can set danger at " << c.x << " " << c.y << endl;
                if (get(c).isFree()) {
                    //                cerr << "Set danger at " << c.x << " " << c.y << endl;
                    tiles.at(c.y).at(c.x).danger = true;
                }
                else {
                    break;
                }
            }
        }

    void setReachable(Coords pos)
        {
            tiles.at(pos.y).at(pos.x).reachable = true;
        }

    void setItem(Coords pos)
        {
            tiles.at(pos.y).at(pos.x).type = TILE_ITEM;
        }

    void setScore(Coords pos, int score)
        {
            tiles.at(pos.y).at(pos.x).score = score;
        }

    inline bool isBox(Coords pos)
        {
            return get(pos).isBox();
        }

    inline bool isBlocking(Coords pos)
        {
            return get(pos).isBlocking();
        }

    inline bool isFree(Coords pos)
        {
            return get(pos).isFree();
        }

    inline bool isItem(Coords pos)
        {
            return get(pos).isItem();
        }

    inline bool isDanger(Coords pos)
        {
            return get(pos).isDanger();
        }

    inline bool isReachable(Coords pos)
        {
            return get(pos).isReachable();
        }

    inline bool isWalkable(Coords pos)
        {
            return get(pos).isWalkable();
        }
};

Board board;

typedef struct {
    Coords pos;
    int id;
    int param1;
    int reach;
} Entity;

typedef struct {
    Coords pos;
    int score = 0;
    bool toBomb = false;
    bool getToSafety = false;
    bool fetchItem = false;
} Destination;

bool checkBombLocation(Coords pos, int reach)
{
    int i;
    cerr << "Checking bomb pos " << pos.x << " " << pos.y << endl;
    Coords c, d;
    for (c = pos.above(), i = 0; i < reach && c.isValid() && board.isFree(c); c.up()) {
        d = c.leftOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
        d = c.rightOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    if (c.isValid() && board.isFree(c)) {
        d = c.above();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    for (c = pos.below(), i = 0; i < reach && c.isValid() && board.isFree(c); c.down()) {
        d = c.leftOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
        d = c.rightOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    if (c.isValid() && board.isFree(c)) {
        d = c.below();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    for (c = pos.leftOf(), i = 0; i < reach && c.isValid() && board.isFree(c); c.left()) {
        d = c.above();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
        d = c.below();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    if (c.isValid() && board.isFree(c)) {
        d = c.leftOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    for (c = pos.rightOf(), i = 0; i < reach && c.isValid() && board.isFree(c); c.right()) {
        d = c.above();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
        d = c.below();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }
    if (c.isValid() && board.isFree(c)) {
        d = c.rightOf();
        if (d.isValid() && board.isWalkable(d)) {
            cerr << "Could flee from " << c.x << " " << c.y << " to " << d.x << " " << d.y << endl;
            return true;
        }
    }

    return false;
}

class Game
{
private:
    int myId;
    Entity players[4];

    Destination currentObjective;
    bool didntmove;
    bool items_present;

public:
    string action;

    Game(int id) : myId(id) {
        currentObjective.score = 0;
    }

    void reset()
        {
            didntmove = false;
            items_present = false;
            action = "";
        }

    void addEntity(int entityType, Entity entity)
        {
            switch (entityType) {
            case TYPE_PLAYER:
                if (entity.id == myId) {
                    if (players[entity.id].pos.x == entity.pos.x
                                            && players[entity.id].pos.y == entity.pos.y
                                            && entity.param1 > 0
                        ) {
                        didntmove = true;
                    }
                }
                players[entity.id] = entity;
                break;
            case TYPE_BOMB:
                board.setBomb(entity.pos, entity.reach, entity.param1);
                break;
            case TYPE_ITEM:
                board.setItem(entity.pos);
                items_present = true;
                break;
            }
        }

    int getPositionScore(Coords pos)
        {
            int score = 0;
            int reach = players[myId].reach;
            int i;
            Coords c;

            for (c = pos, i = 0; c.isValid() && i < reach; c.left()) {
                if (board.isBox(c)) {
                    score++;
                    break;
                }
                if (board.isBlocking(c)) {
                    break;
                }
            }

            for (c = pos, i = 0; c.isValid() && i < reach; c.right()) {
                if (board.isBox(c)) {
                    score++;
                    break;
                }
                if (board.isBlocking(c)) {
                    break;
                }
            }

            for (c = pos, i = 0; c.isValid() && i < reach; c.up()) {
                if (board.isBox(c)) {
                    score++;
                    break;
                }
                if (board.isBlocking(c)) {
                    break;
                }
            }

            for (c = pos, i = 0; c.isValid() && i < reach; c.down()) {
                if (board.isBox(c)) {
                    score++;
                    break;
                }
                if (board.isBlocking(c)) {
                    break;
                }
            }

            return score;
        }

    void computeReachableTiles()
        {
            Destination objective = currentObjective;

            list<Coords> toProcess;
            toProcess.push_back(players[myId].pos);

            bool shouldFindCover = false;
            if (board.isDanger(players[myId].pos)) {
                shouldFindCover = true;
            }

            int i = 0;

            while (toProcess.size() > 0) {
                i++;
                Coords pos = toProcess.front();
                toProcess.pop_front();

                cerr << "Pos " << pos.x << " " << pos.y << endl;
                board.setReachable(pos);
                int score = getPositionScore(pos);
                cerr << "Score: " << score << endl;
                board.setScore(pos, score);

                bool dangerous = board.isDanger(pos);
                cerr << "Dangerous: " << (dangerous ? "yes" : "no") << endl;

                if (!dangerous) {
                    if (shouldFindCover) { // && !dangerous) {
                        if (!objective.getToSafety) {
                            cerr << "Get to any possible cover!" << endl;
                            objective.getToSafety = true;
                            objective.fetchItem = false;
                            objective.toBomb = false;
                            objective.pos = pos;
                            objective.score = 0;
                        }
                    }

                    //                if (!shouldFindCover || !dangerous) {
                    if (board.isItem(pos) && objective.fetchItem == false && i <= ITEM_MAX_DISTANCE) {
                        cerr << "Closeby item + (should be) no danger, go for it !" << endl;
                        objective.getToSafety = !dangerous;
                        objective.fetchItem = true;
                        objective.toBomb = false;
                        objective.pos = pos;
                        objective.score = 4;
                    }

                    if (score > objective.score) {
                        if (checkBombLocation(pos, players[myId].reach)) {
                            cerr << "Better than current objective: go bomb it!" << endl;
                            objective.pos = pos;
                            objective.score = score;
                            objective.toBomb = true;
                            objective.fetchItem = false;
                            objective.getToSafety = false;
                        }
                        else {
                            cerr << "Nope that's too dangerous!" << endl;
                        }
                    }
                }

                if (i > COMPUTATION_MAX_DISTANCE) { // dont go too far...
                    cerr << "Already computed " << i << " entries. Stop for now..." << endl;
                    break;
                }

                pos.up();
                if (pos.isValid() && !board.isReachable(pos) && board.isFree(pos)) {
                    toProcess.push_back(pos);
                }
                pos.down(); // back to origin

                pos.down();
                if (pos.isValid() && !board.isReachable(pos) && board.isFree(pos)) {
                    toProcess.push_back(pos);
                }
                pos.up(); // back to origin

                pos.left();
                if (pos.isValid() && !board.isReachable(pos) && board.isFree(pos)) {
                    toProcess.push_back(pos);
                }
                pos.right(); // back to origin

                pos.right();
                if (pos.isValid() && !board.isReachable(pos) && board.isFree(pos)) {
                    toProcess.push_back(pos);
                }
                cerr << "#############" << endl;
            }

            cerr << "Go to " << objective.pos.x << " " << objective.pos.y << endl;

            currentObjective = objective;

            //        for (int i = 0; i < height; ++i) {
            //            for (int j = 0; j < width; ++j) {
            //                if (board.isReachable(Coords(j, i))) {
            //                    cerr << "Reachable: " << j << " " << i << endl;
            //                }
            //            }
            //        }

        }

    void computeObjective()
        {
            //if (didntmove) {
            //    cerr << "Didnt move: special output" << endl;
            //    action = "BOMB 0 0 x_x";
            //    return;
            //}

            action = "MOVE ";
            if (
                            currentObjective.pos.x == players[myId].pos.x
                                        && currentObjective.pos.y == players[myId].pos.y
                ) {
                if (currentObjective.toBomb) {
                    action = "BOMB ";
                }
                currentObjective.toBomb = false;
                currentObjective.score = 0;
                currentObjective.getToSafety = false;
                currentObjective.fetchItem = false;
            }

            action += to_string(currentObjective.pos.x);
            action += " ";
            action += to_string(currentObjective.pos.y);
        }
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int myId;
    cin >> width >> height >> myId; cin.ignore();

    Game game(myId);

    // game loop
    while (1) {
        board.reset();
        game.reset();

        for (int i = 0; i < height; i++) {
            string row;
            cin >> row; cin.ignore();
            board.addRow(row);
        }

        int entities;
        cin >> entities; cin.ignore();
        for (int i = 0; i < entities; i++) {
            Entity entity;

            int type;
            cin >> type
                >> entity.id
                >> entity.pos.x
                >> entity.pos.y
                >> entity.param1
                >> entity.reach;
            cin.ignore();
            game.addEntity(type, entity);
        }

        game.computeReachableTiles();
        game.computeObjective();

        cout << game.action << endl;
    }
}
