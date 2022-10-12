#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Pokemon
{
public:
    string pokeName;  // name of pokemon
    int weight;       // his weight
    int attackFactor; // his attack factor
    string type;      // his type(fire,water,rock,electric)
    Pokemon()
    {
        pokeName = "";
        type = "";
        attackFactor = 0;
        weight = 0;
    }
    Pokemon(string name_, string type_, int weight_, int attackFactor_)
    {
        pokeName = name_;
        type = type_;
        weight = weight_;
        attackFactor = attackFactor_;
    }
};
class Trainer
{
public:
    string name = "";            // name of trainer
    int pokemons = 0;            // number of pokemons
    Pokemon pokeCollection[100]; // his set of pokemons

    // add new pokemon to poke collection after checking redundancy/
    void addNewPokeToPokeCollection(Pokemon &p)
    {
        if (!(ifPokePresent(p)))
            pokeCollection[pokemons++] = p;
        else
        {
            cout << "pokemon already exits" << endl;
        }
    }
    // check is pokemon is already present
    bool ifPokePresent(Pokemon &p)
    {
        for (int i = 0; i < pokemons; i++)
        {
            if (pokeCollection[i].pokeName == p.pokeName)
                return true;
        }
        return false;
    }
    // it increases the weight and attack factor to 10% of a specific index pokemon in poke Collection
    void evolve(int pokeIndex)
    {
        pokeCollection[pokeIndex].attackFactor += (0.1 * pokeCollection[pokeIndex].attackFactor);
        pokeCollection[pokeIndex].weight += (0.1 * pokeCollection[pokeIndex].weight);
    }
    // to add new Trainer
    Trainer addNewTrainer()
    {
        Trainer t;
        cout << "enter trainer's name: ";
        cin >> t.name;
        cout << "enter the number of pokemons of " << t.name << ": ";
        int pok;
        cin >> pok;
        for (int i = 0; i < pok; i++)
        {
            Pokemon p;
            cout << "Enter the name of " << i + 1 << " pokemon: ";
            cin >> p.pokeName;
            if (t.ifPokePresent(p))
            {
                cout << p.pokeName << " already is in pokemon collection. Please enter a different pokemon" << endl;
                i--;
                continue;
            }
            cout << "enter his type(rock , water , fire , electric): ";
            cin >> p.type;
            cout << "enter his weight: ";
            cin >> p.weight;
            cout << "enter the attack factor of pokemon: ";
            cin >> p.attackFactor;
            if(p.attackFactor >= 10000){
                cout << "Attack factor cannot be greater than 10000, please enter an appropriate attack factor";
                cin >> p.attackFactor;
                cout << endl;
            }
            t.addNewPokeToPokeCollection(p);
        }
        return t;
    }
    Trainer startMatch(int pokeIndex1, Trainer &t2, int PokeIndex2)
    {
        if (pokeCollection[pokeIndex1].type == "fire" && t2.pokeCollection[PokeIndex2].type == "water")
        {
            t2.evolve(PokeIndex2);
            return t2;
        }
        else if (pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "fire")
        {
            evolve(pokeIndex1);
            return *this;
        }
        else if (pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "rock")
        {
            evolve(pokeIndex1);
            return *this;
        }
        else if (pokeCollection[pokeIndex1].type == "rock" && t2.pokeCollection[PokeIndex2].type == "water")
        {
            t2.evolve(PokeIndex2);
            return t2;
        }
        else if (pokeCollection[pokeIndex1].type == "fire" && t2.pokeCollection[PokeIndex2].type == "electric")
        {
            evolve(pokeIndex1);
            return *this;
        }
        else if (pokeCollection[pokeIndex1].type == "electric" && t2.pokeCollection[PokeIndex2].type == "fire")
        {
            t2.evolve(PokeIndex2);
            return t2;
        }
        else if (pokeCollection[pokeIndex1].type == "electric" && t2.pokeCollection[PokeIndex2].type == "water")
        {
            evolve(pokeIndex1);
            return *this;
        }
        else if (pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "electric")
        {
            t2.evolve(PokeIndex2);
            return t2;
        }
        else
        {
            int moves1, moves2;
            moves1 = t2.pokeCollection[PokeIndex2].weight / pokeCollection[pokeIndex1].attackFactor;
            moves2 = pokeCollection[pokeIndex1].weight / t2.pokeCollection[PokeIndex2].attackFactor;
            if (moves1 < moves2)
            {
                evolve(pokeIndex1);
                return *this;
            }
            else if (moves1 > moves2)
            {
                t2.evolve(PokeIndex2);
                return t2;
            }
            else
                return Trainer(); // no one wins
        }
    }
    void displaypokemons()
    {
        cout << "{ ";
        for (int i = 0; i < pokemons; i++)
        {
            if (i == pokemons - 1)
            {
                cout << pokeCollection[i].pokeName << " ( " << i + 1 << " ) "
                     << " } " << endl;
            }
            else
            {
                cout << pokeCollection[i].pokeName << " ( " << i + 1 << " ) "
                     << " , ";
            }
        }
    }
};
int main()
{
    Trainer trainers[100];
    // taking default trainers and their pokemon from Trainers.txt to start the game without adding trainers
    ifstream input("Trainers.txt");
    int train;
    input >> train;
    for (int i = 0; i < train; i++)
    {
        int poks;
        input >> trainers[i].name >> poks;
        for (int j = 0; j < poks; j++)
        {
            string name, type;
            input >> name >> type;
            int weight, attackfactor;
            input >> weight >> attackfactor;
            Pokemon p = Pokemon(name, type, weight, attackfactor);
            trainers[i].addNewPokeToPokeCollection(p);
        }
    }
    input.close();
    cout << "************************************Welcome to pokemon game************************************" << endl;
    int ifcontinue = 1;
    do
    {
        cout << "1. Start the game with default pokemons and trainers which system has provided\n2. Add new Trainers and their pokemons\n3. Exit\n";
        cout << "your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            int matchesWonBy1 = 0, matchesWonBy2 = 0;
            for (int i = 0; i < 3; i++)
            {
                cout << "*****************************************";
                cout << "Round - " << i + 1;
                cout << "*****************************************" << endl;
                cout << "Following is the list of all trainers. Pick them up by selecting the number in front of them" << endl;
                int user1, user2;
                for (int i = 0; i < train; i++)
                {
                    cout << i + 1 << " - " << trainers[i].name << endl;
                }
                cout << "choice of first user: ";
                cin >> user1;
                cout << endl;
                cout << "choice of second user: ";
                cin >> user2;
                cout << endl;
                user1--, user2--;
                if (user1 > train || user2 > train)
                {
                    cout << "someone entered wrong choice, Restarting the game!!!" << endl;
                    continue;
                }
                cout << "Displaying the set of pokemons of user1"
                     << "( " << trainers[user1].name << " )" << endl;
                trainers[user1].displaypokemons();
                cout << endl;
                cout << "Displaying the set of pokemons of user2"
                     << "( " << trainers[user2].name << " )" << endl;
                trainers[user2].displaypokemons();
                cout << endl;
                cout << "Please enter the number of pokemon corresponding to the choice of your pokemon" << endl;
                int user1pok, user2pok;
                cout << "choice of pokemon of first user: ";
                cin >> user1pok;
                cout << endl;
                cout << "choice of pokemon of second user: ";
                cin >> user2pok;
                cout << endl;
                user1pok--;
                user2pok--;
                Trainer won = trainers[user1].startMatch(user1pok, trainers[user2], user2pok);
                if (won.name == trainers[user1].name)
                {
                    cout << trainers[user1].pokeCollection[user1pok].pokeName << " won and it has been evolved" << endl
                         << endl;
                    matchesWonBy1++;
                }
                else if (won.name == trainers[user2].name)
                {
                    cout << trainers[user2].pokeCollection[user2pok].pokeName << " won and it has been evolved" << endl
                         << endl;
                    matchesWonBy2++;
                }
                else
                {
                    cout << "its a tie" << endl
                         << endl
                         << endl;
                }
                cout << "Current Leaderboard is: " << endl;
                cout << "user1---> " << matchesWonBy1 << endl;
                cout << "user2---> " << matchesWonBy2 << endl
                     << endl;
            }
            if (matchesWonBy1 > matchesWonBy2)
            {
                cout << "P1ayer 1 won the match" << endl;
            }
            else if (matchesWonBy1 < matchesWonBy2)
            {
                cout << "Player 2 won the match" << endl;
            }
            else
            {
                cout << "its a tie between player 1 and player 2" << endl;
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            Trainer t;
            t = t.addNewTrainer();
            trainers[train++] = t;
            cout << "New Trainer added successfully" << endl;
            cout << "Now you want to start the game? press 1 for yes and 0 for no: ";
            cin >> ifcontinue;
            if (ifcontinue == 0)
            {
                cout << "see you again" << endl;
                break;
            }
            else
                continue;
        }
        else if (choice == 3)
        {
            cout << "thanks for playing the game. See you again" << endl;
            ifcontinue = 0;
            break;
        }
        else
        {
            cout << "wrong choice entered, restarting the game!!!!" << endl;
        }
        cout << "Do you want to play again? press 1 for yes and 0 for no: ";
        cin >> ifcontinue;
        if (ifcontinue == 0)
        {
            cout << "see you again" << endl;
        }
    } while (ifcontinue);
    return 0;
}