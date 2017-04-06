// Fantastic Bits challenge
// Xavier Morel - 2016-11-26
// Ranking 2208/2399 (Almost had no time to really work on it. :/)


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MIN_X 0
#define MAX_X 16001
#define MIN_Y 0
#define MAX_Y 7501
#define GOAL_SIZE 4000
#define POLE_RADIUS 300
#define WIZARD_RADIUS 400
#define SNAFFLE_RADIUS 150
#define MAX_SNAFFLES 7
#define GOAL_MIDDLE_TEAM0 Coords(0,3750)
#define GOAL_MIDDLE_TEAM1 Coords(16000,3750)
#define WIZARD_ENTITY_TYPE "WIZARD"
#define ENEMY_ENTITY_TYPE "OPPONENT_WIZARD"
#define SNAFFLE_ENTITY_TYPE "SNAFFLE"
#define BLUDGER_ENTITY_TYPE "BLUDGER"
#define LIMIT_MAX (0-1)

// FINE TUNABLE:
#define LIMIT_ATK_ENEMY 5000
#define LIMIT_GOAL_ENEMY 10000
#define LIMIT_GOAL_BALL  7000
#define MAX_DISTANCE_DEF_TO_GOAL 5000

#define THROW_SPEED_ATK "500"
#define THROW_SPEED_DEF "500"
#define MOVE_SPEED_ATK_TO_BALL "150"
#define MOVE_SPEED_DEF_TO_BALL "100"
#define MOVE_SPEED_DEF_TACKLE "100"
#define MOVE_SPEED_DEF_STANDBY "50"
#define MOVE_SPEED_DEF_TO_GOAL "100"

    class Coords
    {
    public:
        int     x;
        int     y;
        Coords() : x(0), y(0) {}
        Coords(int x, int y) : x(x), y(y) {}

        int getClosest(std::vector<Coords> others, int limit)
            {
                int closestNb = -1;
                int distance = LIMIT_MAX;
                int curDist = 0;
                if (limit == 0) {
                    limit = LIMIT_MAX;
                }

                int i = 0;
                for (Coords other : others) {
                    curDist = getDistance(other);
                    if (curDist < distance || distance == LIMIT_MAX) {
                        distance = curDist;
                        closestNb = i;
                    }
                }

                if (curDist > limit && limit > 0) {
                    std::cerr << "Min distance: " << std::to_string(curDist) << std::endl;
                    return -1;
                }
                return closestNb;
            }

        inline int getDistance(const Coords &other) const
            {
                std::cerr << "From " << write() << " to " << other.write() << std::endl;
                return abs(x - other.x) + abs(y - other.y);
            }

        std::string write() const
            {
                return std::to_string(x) + " " + std::to_string(y);
            }

        inline bool operator!=(const Coords &other) const
            {
                return x != other.x || y != other.y;
            }

        inline bool operator==(const Coords &other) const
            {
                return x == other.x && y == other.y;
            }

        inline Coords operator+(const Coords &other)
            {
                return Coords(x + other.x, y + other.y);
            }

        inline Coords operator-(const Coords &other)
            {
                return Coords(x - other.x, y - other.y);
            }

        inline Coords operator*(int k)
            {
                return Coords(x * k, y * k);
            }

        inline Coords operator*=(int k)
            {
                x *= k;
                y *= k;
                return *this;
            }

        inline bool onTrajectory(const Coords &a, const Coords &b) const
            {

                return true;
            }
    };

class Game
{
    int teamId;

    Coords goal;
    Coords myGoal;

    std::vector<Coords> wizards_pos;
    std::vector<Coords> wizards_vect;
    std::vector<bool> wizards_state;

    std::vector<Coords> enemies_pos;
    std::vector<Coords> enemies_vect;
    std::vector<bool> enemies_state;

    std::vector<Coords> snaffles_pos;
    std::vector<Coords> snaffles_vect;

    std::vector<Coords> bludgers_pos;
    std::vector<Coords> bludgers_vect;

public:
    void setTeamId(int teamId)
        {
            if (teamId == 0) {
                goal = GOAL_MIDDLE_TEAM1;
                myGoal = GOAL_MIDDLE_TEAM0;
            }
            else {
                goal = GOAL_MIDDLE_TEAM0;
                myGoal = GOAL_MIDDLE_TEAM1;
            }
        }

    void reset()
        {
            wizards_pos.clear();
            wizards_vect.clear();
            wizards_state.clear();
            enemies_pos.clear();
            enemies_vect.clear();
            enemies_state.clear();
            snaffles_pos.clear();
            snaffles_vect.clear();
            bludgers_pos.clear();
            bludgers_vect.clear();
        }

    inline int getTeamId()
        {
            return teamId;
        }

    void addWizard(Coords pos, Coords vect, bool state)
        {
            wizards_pos.push_back(pos);
            wizards_vect.push_back(vect);
            wizards_state.push_back(state);
        }

    void addOpponentWizard(Coords pos, Coords vect, bool state)
        {
            enemies_pos.push_back(pos);
            enemies_vect.push_back(vect);
            enemies_state.push_back(state);
        }

    void addSnaffle(Coords pos, Coords vect)
        {
            snaffles_pos.push_back(pos);
            snaffles_vect.push_back(vect);
        }

    void addBludger(Coords pos, Coords vect)
        {
            bludgers_pos.push_back(pos);
            bludgers_vect.push_back(vect);
        }

    std::string getOffensiveWizardAction()
        {
            Coords wiz_pos = wizards_pos.front();
            bool wiz_state = wizards_state.front();

            if (wiz_state == true) {
                // If I have a ball: fire it towards opponent goal.
                return "THROW " + goal.write() + " " + THROW_SPEED_ATK;
            }
            else {
                // If I don't: go toward the closest ball.
                // TODO What about close-by enemies?
                // TODO Should try and get to the ball closest to enemy goals?
                int ballNb = -1;

                std::cerr << "ATK Closest enemy." << std::endl;
                if (wiz_pos.getClosest(enemies_pos, LIMIT_ATK_ENEMY) > -1) {
                    std::cerr << "ATK Closest ball." << std::endl;
                    ballNb = goal.getClosest(snaffles_pos, LIMIT_MAX);
                }
                else {
                    std::cerr << "ATK Closest ball." << std::endl;
                    ballNb = wiz_pos.getClosest(snaffles_pos, LIMIT_MAX);
                }

                if (ballNb > -1) {
                    Coords snaffle = snaffles_pos.at(ballNb);
                    return "MOVE " + snaffle.write() + " " + MOVE_SPEED_ATK_TO_BALL;
                }
                else {
                    return "MOVE 0 0 10 Stuck >_<";
                }
            }
        }

    std::string getDefensiveWizardAction()
        {
            Coords wiz_pos = wizards_pos.back();
            bool wiz_state = wizards_state.back();

            if (wiz_state == true) {
                // If I have a ball, fire it towards my buddy (?) or goal (?)
                return "THROW " + wizards_pos.front().write() + " " + THROW_SPEED_DEF;
            }
            else {
                // If I don't:
                // If I'm far from my goals.
                if (wiz_pos.getDistance(myGoal) > MAX_DISTANCE_DEF_TO_GOAL) {
                    return "MOVE " + myGoal.write() + " " + MOVE_SPEED_DEF_TO_GOAL;
                }

                std::cerr << "DEF Closest enemy." << std::endl;
                int enemyNb = wiz_pos.getClosest(enemies_pos, LIMIT_GOAL_ENEMY);
                if (enemyNb > -1) {
                    //  - If an opponent is close, get between him and the goal
                    // TODO ...
                    Coords enemy = enemies_pos.at(enemyNb);
                    return "MOVE " + enemy.write() + " " + MOVE_SPEED_DEF_TACKLE;
                }

                //  - If no opponents are close,
                std::cerr << "DEF Closest ball." << std::endl;
                int ballNb = wiz_pos.getClosest(snaffles_pos, LIMIT_GOAL_BALL);
                if (ballNb > -1) {
                    //      - if a ball is close-by, go fetch it and fire it away
                    Coords snaffle = snaffles_pos.at(ballNb);
                    return "MOVE " + snaffle.write() + " " + MOVE_SPEED_DEF_TO_BALL;
                }

                //      - if no balls are close, just stand by.
                return "MOVE " + myGoal.write() + " " + MOVE_SPEED_DEF_STANDBY;
            }
        }

    std::string getWizardAction(int id)
        {
            if (id == 0) {
                // First wizard: fetch ball and fire it towards opponent goals
                return getOffensiveWizardAction();
            }
            else {
                // Second wizard: defend own goal.
                return getDefensiveWizardAction();
            }
        }
};


class Environment
{
    Game game;

public:
    Environment() {}

    void initialization(std::istream &input)
        {
            int myTeamId;
            input >> myTeamId; input.ignore();
            game.setTeamId(myTeamId);
        }

    void reset()
        {
            game.reset();
        }

    void input(std::istream &input)
        {
            int entities;
            input >> entities;
            input.ignore();

            for (int i = 0; i < entities; i++) {
                int id;
                std::string entityType;
                Coords pos;
                Coords vect;
                int state;

                input >> id >> entityType >> pos.x >> pos.y >> vect.x >> vect.y >> state;
                input.ignore();
                if (entityType == WIZARD_ENTITY_TYPE) {
                    game.addWizard(pos, vect, state == 1);
                }
                else if (entityType == ENEMY_ENTITY_TYPE) {
                    game.addOpponentWizard(pos, vect, state == 1);
                }
                else if (entityType == SNAFFLE_ENTITY_TYPE) {
                    game.addSnaffle(pos, vect);
                }
                else if (entityType == BLUDGER_ENTITY_TYPE) {
                    game.addBludger(pos, vect);
                }
                else {
                    std::cerr << "Wut ?! Unknown entity type: " << entityType << std::endl;
                }
            }
        }

    void compute(void)
        {
            ;
        }

    void output(std::ostream &output)
        {
            for (int i = 0; i < 2; i++) {
                output << game.getWizardAction(i) << std::endl;
            }
        }
};


/**
 * Grab Snaffles and try to throw them through the opponent's goal!
 * Move towards a Snaffle and use your team id to determine where you need to throw it.
 **/
int main()
{
    Environment env;
    env.initialization(std::cin);
    while (1) {
        env.reset();
        env.input(std::cin);
        env.compute();
        env.output(std::cout);
    }
}
