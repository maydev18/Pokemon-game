#include <iostream>
#include <string>
using namespace std;
class Pokemon{
    public:
        string pokeName; //name of pokemon
        int weight; //his weight
        int attackFactor; //his attack factor
        string type; //his type(fire,water,rock,electric)
        Pokemon(){
            pokeName = "";
            type = "";
            attackFactor=0;
            weight =0;
        }
        Pokemon(string name_ , string type_ , int weight_ , int attackFactor_){
            pokeName = name_;
            type = type_;
            weight = weight_;
            attackFactor = attackFactor_;
        } 
};
class Trainer{
    public:
        string name = ""; // name of trainer
        int pokemons = 0; // number of pokemons
        Pokemon pokeCollection[100]; // his set of pokemons
        void addNewPokeToPokeCollection(Pokemon& p){
            if(!(ifPokePresent(p))) pokeCollection[pokemons++] = p;
            else{
                cout<<"pokemon already exits"<<endl;
            }
        }
        bool ifPokePresent(Pokemon & p){
            for(int i=0 ; i<pokemons ; i++){
                if(pokeCollection[i].pokeName == p.pokeName) return true;
            }
            return false;
        }
        void evolve(int pokeIndex){
            pokeCollection[pokeIndex].attackFactor += (0.1*pokeCollection[pokeIndex].attackFactor);
            pokeCollection[pokeIndex].weight += (0.1*pokeCollection[pokeIndex].weight);
        }
        Trainer addNewTrainer(){
            Trainer t;
            cout<<"enter trainer's name: ";
            cin >> t.name;
            cout<<"enter the number of pokemons of "<<t.name<<": ";
            int pok;
            cin >> pok;
            for(int i=0 ; i<pok ; i++){
                Pokemon p;
                cout<<"Enter the name of "<<i+1<<" pokemon: ";
                cin>>p.pokeName;
                if(t.ifPokePresent(p)){
                    cout<<p.pokeName<<" already is in pokemon collection. Please enter a different pokemon"<<endl;
                    i--;
                    continue;
                }
                cout<< "enter his type(rock , water , fire , electric): ";
                cin>>p.type;
                cout<<"enter his weight: ";
                cin >> p.weight;
                cout << "enter the attack factor of pokemon: ";
                cin >> p.attackFactor;
                t.addNewPokeToPokeCollection(p);
            }
            return t;
        }
        Trainer startMatch(int pokeIndex1 , Trainer & t2 , int PokeIndex2){
            if(pokeCollection[pokeIndex1].type == "fire" && t2.pokeCollection[PokeIndex2].type == "water"){
                t2.evolve(PokeIndex2);
                return t2;
            }
            else if(pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "fire"){
                evolve(pokeIndex1);
                return *this;
            }
            else if(pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "rock"){
                evolve(pokeIndex1);
                return *this;
            }
            else if(pokeCollection[pokeIndex1].type == "rock" && t2.pokeCollection[PokeIndex2].type == "water"){
                t2.evolve(PokeIndex2);
                return t2;
            }
            else if(pokeCollection[pokeIndex1].type == "fire" && t2.pokeCollection[PokeIndex2].type == "electric"){
                evolve(pokeIndex1);
                return *this;
            }
            else if(pokeCollection[pokeIndex1].type == "electric" && t2.pokeCollection[PokeIndex2].type == "fire"){
                t2.evolve(PokeIndex2);
                return t2;
            }
            else if(pokeCollection[pokeIndex1].type == "electric" && t2.pokeCollection[PokeIndex2].type == "water"){
                evolve(pokeIndex1);
                return *this;
            }
            else if(pokeCollection[pokeIndex1].type == "water" && t2.pokeCollection[PokeIndex2].type == "electric"){
                t2.evolve(PokeIndex2);
                return t2;
            }
            else {
                int moves1 , moves2;
                moves1 = t2.pokeCollection[PokeIndex2].weight/pokeCollection[pokeIndex1].attackFactor;
                moves2 = pokeCollection[pokeIndex1].weight/t2.pokeCollection[PokeIndex2].attackFactor;
                if(moves1 < moves2){
                    evolve(pokeIndex1);
                    return *this;
                }
                else if(moves1 > moves2){
                    t2.evolve(PokeIndex2);
                    return t2;
                }
                else return Trainer(); //no one wins
            }
        }
        void displaypokemons(){
            cout<<"{ ";
            for(int i=0 ; i<pokemons ; i++){
                if(i == pokemons-1){
                    cout<<pokeCollection[i].pokeName<<" ( "<<i+1<<" ) "<<" } "<<endl;
                }
                else{
                    cout<<pokeCollection[i].pokeName<<" ( "<<i+1<<" ) "<<" , ";
                }
            }
        }
};
