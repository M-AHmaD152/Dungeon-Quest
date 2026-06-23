#include <iostream>
#include <string>

using namespace std;

void displayStats(string name, int health = 100, int attack = 10)
{
    
    cout<<"Name: "<<name<<endl;
    cout<<"Health: "<<health<<endl;
    cout<<"Attack: "<<attack<<endl;

}

void damageTaken(int* health, int damage)
{
    *health -= damage;
    cout<<"----------Damage Taken "<<damage<<"----------"<<endl;
    cout<<endl;
    
}
void showMonsters(string monstersName[], int monsterHealth[], int size)
{
    
    for (int i = 0; i< size; i++)
    {
        cout<<"Name of The Monster: "<<monstersName[i]<<"\t"<<"Health: "<<monsterHealth[i]<<"\n";
    }
}

void printDivider() 
{
    cout << "----------------------------------\n";
}
void addItem(string* inventory, int index,string item)
{
    inventory[index] = item;
}
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
void showInventory(string* inventory, int size)
{
    for(int i = 0; i < size; i++)
    {
        cout<<inventory[i]<<endl;
    }
}
int main(void)
{
    string name;
    int health = 100;
    int attack = 10;
    int monsterAttack = 10;
    int round = 1;
    int capacity = 3;
    string* inventory = new string[capacity];
    
    printDivider();
    cout << "       DUNGEON QUEST\n";
    printDivider();
    string monstersName[3] = {"Goblin", "Orc", "Dragon"};
    int monstersHealth[3] = {30, 30, 100};
    int combatChoice;
    cout<<"Enter the Name: ";
    cin>>name;
    displayStats(name);
    cout<<"Things Present in the inventory\n";
    addItem(inventory, 0, "sword");
    addItem(inventory, 1, "Shield");
    addItem(inventory, 2, "Potion Health");
    expandInventory(inventory, capacity, "Magic Wand");
    showInventory(inventory, capacity);
    int monsterChoice;
    showMonsters(monstersName, monstersHealth, 3);
    cout<<"Choose Your Monster (as Enemy)(1-3): ";
    cin>> monsterChoice;
    string selectedMonster = monstersName[monsterChoice - 1];
    int selectedHealth = monstersHealth[monsterChoice - 1];

    cout<<"Monster: "<<selectedMonster<<"\t Health: "<<selectedHealth<<endl;
    printDivider();

    bool running = true;

    while(health > 0 && selectedHealth > 0 && running)
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
                selectedHealth -= attack;
                cout << "\nYou attack " << selectedMonster << " for " << attack << " damage!\n";
                cout << selectedMonster << "'s health: " << selectedHealth << endl;
            if(selectedHealth <= 0)
            {
                cout<<"\n Ah!! I can't Die no! \n";
            }
            else
            {
                cout << selectedMonster << " attacks you for " << monsterAttack << " damage!\n";
                damageTaken(&health, monsterAttack);
                cout << "Your health: " << health << endl;
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
    if(health <= 0)
    {
        cout<<"\nalas! You Died Game Over!!\n";
    }
    else if(selectedHealth <= 0)
    {
        cout<<"\nCongratulations! You Have Won!!\n";
    }
    else
    {
        cout<<"\nYou fled away!\n";
    }
    printDivider();
    delete[] inventory;
    return 0;
}