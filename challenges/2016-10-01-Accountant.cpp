// Accountant challenge
// Xavier Morel - 2016-10-01
// Ranking 675/6214


#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

typedef struct {
    int             x;
    int             y;
}                   Coords;

typedef struct {
    int             id;
    bool            alive = true;
    Coords          pos;
}                   Data;

typedef struct {
    int             id = -1;
    bool            alive = true;
    int             data_dist = 0;
    int             data_id = 0;
    int             player_dist = 0;
    int             life;
    Coords          pos;
}                   Mob;

int                 getDistance(Coords a, Coords b)
{
    int xdiff = b.x - a.x;
    int ydiff = b.y - a.y;
    return std::sqrt((xdiff * xdiff) + (ydiff * ydiff));
}

class               Environment {
public:
    size_t          data_count;
    size_t          mobs_count;
    map<int, Data>  data;
    map<int, Mob>   mobs;
    Coords          player;

    std::string     action;

    void            initialization(std::istream &input) {
        ;
    }

    void            reset() {
        for (int i = 0; i < data.size(); i++) {
            data[i].alive = false;
        }
        for (int i = 0; i < mobs.size(); i++) {
            mobs[i].alive = false;
        }
        action = "";
    }

    void            input(std::istream &input) {
        input >> player.x >> player.y; input.ignore();
        input >> data_count; input.ignore();
        for (int i = 0; i < data_count; i++) {
            Data node;
            input >> node.id >> node.pos.x >> node.pos.y; input.ignore();
            data[node.id] = node;
        }

        input >> mobs_count; input.ignore();
        for (int i = 0; i < mobs_count; i++) {
            Mob mob;
            input >> mob.id >> mob.pos.x >> mob.pos.y >> mob.life; input.ignore();
            computeDistances(mob);
            //            computeTurns(mob);
            mobs[mob.id] = mob;
        }
    }

    void computeDistances(Mob &mob)
        {
            int closest = -1;
            int distance = 999999;

            for (auto iter : data) {
                Data datanode = iter.second;
                if (datanode.alive) {
                    int dist = getDistance(datanode.pos, mob.pos);
                    if (dist < distance) {
                        distance = dist;
                        closest = datanode.id;
                    }
                }
            }

            mob.player_dist = getDistance(mob.pos, player);
            mob.data_id = closest;
            mob.data_dist = distance;
        }

    int getDamage(int distance)
        {
            return 125000 / pow(distance, 1.2f);
        }

    void applyVector(Coords &pos, Coords dest, int distance)
        {
            ;
        }

    void computeTurns(Mob &mob)
        {
            int turnsToLive = 0;
            int turnsToCap = 0;

            int life, distToData, distToPlayer;
            Coords pos = mob.pos;
            Coords destination = data[mob.data_id].pos;

            life = mob.life;
            distToData = mob.data_dist;
            distToPlayer = mob.player_dist;

            while (distToData > 500 || life > 0) {
                life -= getDamage(distToPlayer);

                applyVector(pos, destination, 500);
                distToData = getDistance(pos, destination);
                distToPlayer = getDistance(pos, player);

                if (life > 0) {
                    turnsToLive++;
                }
                if (distToData > 500) {
                    turnsToCap++;
                }
            }
            cerr << "Mob " << std::to_string(mob.id) << " turns:" << std::endl;
            cerr << "To live: " << std::to_string(turnsToLive) << std::endl;
            cerr << "To capt: " << std::to_string(turnsToCap) << std::endl;
        }

    std::string     moveOut(Mob menace)
        {
            int x, y;

            x = menace.pos.x > (player.x - 500) ? player.x - 750 : player.x + 750;
            y = menace.pos.y > (player.y - 500) ? player.y - 750 : player.y + 750;

            return "MOVE " + std::to_string(x) + " " + std::to_string(y) + " HAAAAAAAaaaa";
        }

    void            compute(void) {
        Mob target;

        for (auto iter : mobs) {
            Mob mob = iter.second;

            // Skip dead.
            if (!mob.alive) {
                continue;
            }

            // Pick one enemy.
            if (target.id < 0) {
                target = mob;
                continue;
            }

            // Switch target if current is far and this one is close, or closer to a datanode.
            if (target.player_dist > 3000 && (mob.player_dist < 3000 || mob.data_dist < target.data_dist)) {
                target = mob;
                continue;
            }

            // Switch target if this one is closer to me than the current target...
            if (mob.player_dist < target.player_dist) {
                target = mob;
            }
        }

        if (target.player_dist < 2500) {
            action = moveOut(target);
        } else {
            action = "SHOOT " + std::to_string(target.id) + " DIIIIIE";
        }
    }

    void            output(std::ostream &output) {
        output << action << std::endl;
    }
};

int                 main()
{
    Environment     env;

    env.initialization(std::cin);

    while (1) {
        env.reset();
        env.input(std::cin);
        env.compute();
        env.output(std::cout);
    }
}
