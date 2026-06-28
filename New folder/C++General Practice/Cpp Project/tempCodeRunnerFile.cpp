#include <iostream>
#include <string>

using namespace std;
class Hero
{
    public:
    string name;
    int health = 100;
    int attack = 10;
    string* inventory;
    int capacity = 3;
    Hero(string heroName)
    {
        name = heroName;
        health = 100;
        attack = 10;
        capacity = 3;
        inventory = new string[capacity];
    }
void displayStats()
{
    
    cout<<"Name: "<<name<<endl;
    cout<<"Health: "<<health<<endl;
    cout<<"Attack: "<<attack<<endl;

}

void damageTaken(int damage)
{
    health -= damage;
    cout<<"----------Damage Taken "<<damage<<"----------"<<endl;
    cout<<endl;
    
}

void addItem(int index, string item)
{
    inventory[index] = item;
}
void showInventory(int size)
{
    for(int i = 0; i < size; i++)
    {
        cout<<inventory[i]<<endl;
    }
}
~Hero ()
{
    delete[] inventory;
}
};
class Monster
{
    public: 
    string name;
    int health;
    int attack;

    Monster(string monsterName, int monsterHealth, int monsterAttack)
    {
        name = monsterName;
        health = monsterHealth;
        attack = monsterAttack;
    }
    void displayStats()
    {
        cout<<"Monster Name: "<<name<<"\t\t";
        cout<<"Monster Health: "<<health<<"\t";
        cout<<"Monster Attack: "<<attack<<"\t";
    }
    void takeDamage(int damage)
    {
        health -= damage;
    }
    bool isAlive()
    {
        if (health > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};
void expandInventory(string* &inventory, int& capacity, string newItem)
{
    string* newInventory = new string[capacity + 1];

    for (int i = 0; i< capacity; i++)
    {
        newInventory[i] = inventory[i];
    }
    newInventory[capacity] = newItem;
    delete[]inventory;
    inventory = newInventory;
    capacity++;
}
void printDivider() 
{
    cout << "----------------------------------\n";
}
int main(void)
{

    string name;
    
    
    int round = 1;
    
    printDivider();
    cout << "       DUNGEON QUEST\n";
    printDivider();
    cout<<"Enter the hero Name: ";
    cin>>name;
    Hero hero(name);
    Monster monster[3] = {Monster("Goblin", 30, 8), Monster("Orc", 50, 10), Monster("Dragon", 100, 12)};
    for (int i = 0; i< 3; i++)
    {
        cout<< (i + 1)<<". ";
        monster[i].displayStats();
        cout<<"\n";
    }
    int combatChoice;
    hero.displayStats();
    cout<<"Things Present in the inventory\n";
    hero.addItem(0, "sword");
    hero.addItem(1, "Shield");
    hero.addItem(2, "Potion Health");
    expandInventory(hero.inventory, hero.capacity, "Magic Wand");
    hero.showInventory(hero.capacity);
    int monsterChoice;
    
    cout<<"Choose Your Monster (as Enemy)(1-3): ";
    cin>> monsterChoice;
    Monster& selectedMonster = monster[monsterChoice - 1];

    cout<<"Monster: "<<selectedMonster.name<<"\t Health: "<<selectedMonster.health<<endl;
    printDivider();

    bool running = true;

    while(hero.health > 0 && selectedMonster.health > 0 && running)
    { 
        printDivider();
        cout << "Round " << round << "\n";
        printDivider();
        cout<<"\nEnter your Choice: \n";
        cout<<"1.Fight the Monster?\n";
        cout<<"2. Run\n";
        cin>>combatChoice;
        switch (combatChoice)
        {
            case 1:
                selectedMonster.takeDamage(hero.attack);
                cout << "\nYou attack " << selectedMonster.name << " for " << hero.attack << " damage!\n";
                cout << selectedMonster.name << "'s health: " << selectedMonster.health << endl;
            if(selectedMonster.health <= 0)
            {
                cout<<"\n Ah!! I can't Die no! \n";
            }
            else
            {
                cout << selectedMonster.name << " attacks you for " << selectedMonster.attack << " damage!\n";
                hero.damageTaken(selectedMonster.attack);
                cout << "Your health: " << hero.health << endl;
            }
            break;
        case 2: 
            cout<<"You Ran Away!\n";  
            running = false;
            break;
        default:
            cout<<"Invalid Choice";
            break;
        }
        round++;
    }
    printDivider();
    if(hero.health <= 0)
    {
        cout<<"\nalas! You Died Game Over!!\n";
    }
    else if(!selectedMonster.isAlive())
    {
        cout<<"\nCongratulations! You Have Won!!\n";
    }
    else
    {
        cout<<"\nYou fled away!\n";
    }
    printDivider();
    return 0;
}