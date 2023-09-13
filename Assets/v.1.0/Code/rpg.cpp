#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <locale.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <array>
#include <list>

#include "dirent.h";
#include <sys\types.h>

using namespace std;

#include "json.hpp";

using json = nlohmann::json;

class Drop {
public:
    string drop;
    string rar;
    int weight;
    Drop newDrop(string drop, string rar, int weight) {
        Drop _drop;
        _drop.drop = drop;
        _drop.rar = rar;
        _drop.weight = weight;
        return _drop;
    }
};

class Enemy {
public:
    string name;
    int level;
    int health;
    int attack;
    int possibility;
    int crit;
    int critdamage;
    int weight;
    int speed;
    int range;
    int aggression;
    int type;
    int featurePower;
    bool isBoss;
    vector<Drop> CustomDrop;
    Enemy newEnemy(string name, int level, int health, int attack, int possibility, int crit, int critdamage, int weight, int speed, int range, int aggression, int type, int featurePower) {
        Enemy enemy;
        enemy.name = name;
        enemy.level = level;
        enemy.health = health;
        enemy.attack = attack;
        enemy.possibility = possibility;
        enemy.crit = crit;
        enemy.critdamage = critdamage;
        enemy.weight = weight;
        enemy.speed = speed;
        enemy.range = range;
        enemy.aggression = aggression;
        enemy.type = type;
        enemy.featurePower = featurePower;
        return enemy;
    }
};

class Weapon {
public:
    string name;
    int attack;
    int possibility;
    int crit;
    int critdamage;
    int type;
    int featurePower;
    int use;
    bool on;
    int speed;
    int range;
    bool HaveParentWeapon;
    int ParentCost;
    int cost;
    bool isOnlyDrop;
    Weapon newWeapon(string name, int attack, int possibility, int crit, int critdamage, int type, int featurePower, int use, bool on, int speed, int range, bool iod) {
        Weapon weapon;
        weapon.name = name;
        weapon.attack = attack;
        weapon.possibility = possibility;
        weapon.crit = crit;
        weapon.critdamage = critdamage;
        weapon.type = type;
        weapon.featurePower = featurePower;
        weapon.use = use;
        weapon.on = on;
        weapon.speed = speed;
        weapon.range = range;
        weapon.cost = 10;
        weapon.HaveParentWeapon = false;
        weapon.isOnlyDrop = iod;
        return weapon;
    }
};


enum Rarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,
    Mythic
};

class Slot {
public:
    int id;
    Rarity rarity;
    Slot newSlot(int id, Rarity rarity) {
        Slot slot;
        slot.id = id;
        slot.rarity = rarity;
        return slot;
    }
};



string name;
int money = 0;
int gp = 0;
int gxp = 0;
int xp = 0;
int level = 1;
int health = 100;
int type;
int allxp = 0;
int x = 3;
int ex = 17;
int mineBlood = 0;
int minePoison = 0;
int enemyBlood = 0;
int enemyPoison = 0;
chrono::steady_clock sc;
auto timer_start = sc.now();
bool lfive = false;
int killg = 0;
Enemy enemy;
vector<Enemy> enemys;
Weapon weapon;
vector<Weapon> weapons;
Slot slot;
vector<Slot> slots;
int envanter[4] = { 1,2,0,0 };

void clear() {
    system("cls");//std::cout << "\x1B[2J\x1B[H";    (For Linux)
}

void startScreen();
void goMarket();

bool findIfNotExist(int id) {
    for (int i = 0; i < slots.size(); i++) {
        if (slots[i].id == id) return false;
    }
    return true;
}

void oneUseableItem() {
    clear();

    cout << "#   #   ###   ####   #  #  #####  #####" << endl;
    cout << "## ##  #   #  #   #  ###   #___     #  " << endl;
    cout << "# # #  #####  ####   # #   #        #  " << endl;
    cout << "#   #  #   #  #   #  #  #  #####    #  " << endl;


    cout << "Health: " << health << endl << "Money: " << money << endl << "Level: " << level << "    Xp:" << xp << endl << endl;

    int wtd;

    int wrm = 0;

    vector<int> all;

    cout << "What you will do:\n0 for Exit\n";
    for (int i = 0; i < size(weapons); i++) {

        if (!weapons[i].isOnlyDrop && weapons[i].use != -1) { cout << i + 1 - wrm << " for " << weapons[i].name << " (" << weapons[i].cost << " money) - " << weapons[i].use << "\n"; all.push_back(i); }
        else wrm++;
    }


    cout << endl;
    cin >> wtd;

    if (wtd == 0) goMarket();
    else
    {
        wtd = all[wtd-1]+1;

        if (wtd < size(weapons)) { if (!weapons[wtd - 1].isOnlyDrop && weapons[wtd - 1].use != -1 && money - weapons[wtd - 1].cost >= 0) { money -= weapons[wtd - 1].cost; weapons[wtd - 1].use++; weapons[wtd - 1].on = true; if (findIfNotExist(wtd - 1)) slots.push_back(slot.newSlot(wtd - 1, Common)); } }

    }
    oneUseableItem();
}

void tooMuchUsableItem() {
    clear();

    cout << "#   #   ###   ####   #  #  #####  #####" << endl;
    cout << "## ##  #   #  #   #  ###   #___     #  " << endl;
    cout << "# # #  #####  ####   # #   #        #  " << endl;
    cout << "#   #  #   #  #   #  #  #  #####    #  " << endl;


    cout << "Health: " << health << endl << "Money: " << money << endl << "Level: " << level << "    Xp:" << xp << endl << endl;

    int wtd;

    int wrm = 0;
    vector<int> all;

    cout << "What you will do:\n0 for Exit\n";
    for (int i = 0; i < size(weapons); i++) {
        
        if (!weapons[i].isOnlyDrop && weapons[i].use == -1) { cout << i + 1 - wrm << " for " << weapons[i].name << " (" << weapons[i].cost << " money)\n"; all.push_back(i); }
        else if (!weapons[i].isOnlyDrop && weapons[i].HaveParentWeapon) { cout << i + 1 - wrm << " for " << weapons[i].name << " (" << weapons[i].ParentCost << " money)\n"; all.push_back(i); }
        else wrm++;

    }


    cout << endl;
    cin >> wtd;

    Rarity rart;
    int r = rand() % 100;
    if (r < 65) rart = Common;
    else if (r < 85) rart = Uncommon;
    else if (r < 90) rart = Rare;
    else if (r < 95) rart = Epic;
    else if (r < 98) rart = Legendary;
    else if (r < 100) rart = Mythic;



    if (wtd == 0) goMarket();
    else  
    {   
        wtd = all[wtd - 1] + 1;
        if (wtd < size(weapons)) { if (((!weapons[wtd - 1].isOnlyDrop && weapons[wtd - 1].use == -1) || (!weapons[wtd - 1].isOnlyDrop && weapons[wtd - 1].HaveParentWeapon)) && money - weapons[wtd - 1].cost >= 0) { money -= weapons[wtd - 1].cost; weapons[wtd - 1].on = true; slots.push_back(slot.newSlot(wtd - 1, rart)); } }

    }
    tooMuchUsableItem();
}

void goMarket() {
    clear();

    cout << "#   #   ###   ####   #  #  #####  #####" << endl;
    cout << "## ##  #   #  #   #  ###   #___     #  " << endl;
    cout << "# # #  #####  ####   # #   #        #  " << endl;
    cout << "#   #  #   #  #   #  #  #  #####    #  " << endl;


    cout << "Health: " << health << endl << "Money: " << money << endl << "Level: " << level << "    Xp:" << xp << endl << endl;

    string wtd;

    cout << "What you will do:\n0 for Exit\n1 for Disposable Items\n2 for Weapons\n";

    cin >> wtd;

    if (wtd == "0") startScreen();
    else if (wtd == "1") oneUseableItem();
    else if (wtd == "2") tooMuchUsableItem();

}

void goInventory() {
    clear();

    cout << "  #  #  #  #   #  #####  #  #  #####   ###   ####  #   #" << endl;
    cout << "  #  ## #  #   #  #___   ## #    #    #   #  #   #  # # " << endl;
    cout << "  #  # ##   # #   #      # ##    #    #   #  ####    #  " << endl;
    cout << "  #  #  #    #    #####  #  #    #     ###   #   #   #  " << endl;

    cout << "Health: " << health << endl << "Money: " << money << endl << "Level: " << level << "    Xp:" << xp << endl << endl;


    cout << "Open Items: \n\n";

    string incode, outcode = "\033[0m";

    for (int i = 0; i < slots.size(); i++) {
        if (weapons[slots[i].id].on) {
            if (slots[i].rarity == Common) incode = "";
            else if (slots[i].rarity == Uncommon) incode = "\033[1;32m";
            else if (slots[i].rarity == Rare) incode = "\033[1;34m";
            else if (slots[i].rarity == Epic) incode = "\033[1;35m";
            else if (slots[i].rarity == Legendary) incode = "\033[1;33m";
            else if (slots[i].rarity == Mythic) incode = "\033[1;31m";
            if (weapons[slots[i].id].use != -1) cout << incode << i + 1 << " : " << weapons[slots[i].id].name << " - " << weapons[slots[i].id].use << outcode << endl;
            else cout << incode << i + 1 << " : " << weapons[slots[i].id].name << outcode << endl;
        }
    }

    cout << "\nInventory: \n\n";

    for (int i = 0; i < 4; i++) {
        if (envanter[i] != 0) {
            if (slots[envanter[i] - 1].rarity == Common) incode = "";
            else if (slots[envanter[i] - 1].rarity == Uncommon) incode = "\033[1;32m";
            else if (slots[envanter[i] - 1].rarity == Rare) incode = "\033[1;34m";
            else if (slots[envanter[i] - 1].rarity == Epic) incode = "\033[1;35m";
            else if (slots[envanter[i] - 1].rarity == Legendary) incode = "\033[1;33m";
            else if (slots[envanter[i] - 1].rarity == Mythic) incode = "\033[1;31m";
            if (weapons[slots[envanter[i] - 1].id].use != -1) cout << incode << i + 1 << " : " << weapons[slots[envanter[i] - 1].id].name << " - " << weapons[slots[envanter[i] - 1].id].use << outcode << endl;
            else cout << incode << i + 1 << " : " << weapons[slots[envanter[i] - 1].id].name << outcode << endl;
        }
    }


    int item, slot;

    cout << "\nWhat you will do:\n0 0 for Exit\n(item id - inventory id) for change Item\n";

    cin >> item >> slot;

    if (item == 0 || slot == 0) startScreen();
    else {
        if (weapons[slots[item - 1].id].on) envanter[slot - 1] = item;
    }
    goInventory();
}

void raidStep(string out) {
    clear();

    if (health > 90 + 20 * level) health = 90 + 20 * level;

    cout << "Name: " << name;
    for (int i = 0; i < 21 - ("Name: " + name).length(); i++) cout << " ";
    cout << "|    " << "Name: " << enemy.name << endl;

    cout << "Level: " << level;
    for (int i = 0; i < 20 - ("Level: " + to_string(level)).length(); i++) cout << " ";
    cout << "|    " << "Level: " << enemy.level << endl;

    cout << "Health: " << health;
    for (int i = 0; i < 20 - ("Health: " + to_string(health)).length(); i++) cout << " ";
    cout << "|    " << "Health: " << enemy.health << endl;

    cout << "Blood: " << mineBlood;
    for (int i = 0; i < 20 - ("Blood: " + to_string(mineBlood)).length(); i++) cout << " ";
    cout << "|    " << "Blood: " << enemyBlood << endl;

    cout << "Poison: " << minePoison;
    for (int i = 0; i < 20 - ("Poison: " + to_string(minePoison)).length(); i++) cout << " ";
    cout << "|    " << "Poison: " << enemyPoison << endl << endl;

    string line = "";
    for (int i = 0; i < 22; i++) {
        if (i == 0 || i == 21) line += "|";
        else if (i == x) line += "O";
        else if (i == ex) line += "X";
        else line += " ";
    }

    cout << "/--------------------\\" << endl;
    cout << "|                    |" << endl;
    cout << line << endl;
    cout << "|                    |" << endl;
    cout << "\\--------------------/" << endl;


    cout << endl << endl << "00:Run Away\n01:Get Closer\n02:Get Far\n03:Wait\n04:Learn Trait\n\nWeapons: " << endl;

    string incode, outcode = "\033[0m";


    for (int i = 0; i < 4; i++) {
        if (envanter[i] != 0) {
            if (slots[envanter[i] - 1].rarity == Common) incode = "";
            else if (slots[envanter[i] - 1].rarity == Uncommon) incode = "\033[1;32m";
            else if (slots[envanter[i] - 1].rarity == Rare) incode = "\033[1;34m";
            else if (slots[envanter[i] - 1].rarity == Epic) incode = "\033[1;35m";
            else if (slots[envanter[i] - 1].rarity == Legendary) incode = "\033[1;33m";
            else if (slots[envanter[i] - 1].rarity == Mythic) incode = "\033[1;31m";
            if (weapons[slots[envanter[i] - 1].id].use != -1) cout << incode << i + 1 << " : " << weapons[slots[envanter[i] - 1].id].name << " - " << weapons[slots[envanter[i] - 1].id].use << outcode << endl;
            else cout << incode << i + 1 << " : " << weapons[slots[envanter[i] - 1].id].name << outcode << endl;
        }
    }

    cout << endl << out << endl << endl << "Move: ";
    string hammle;
    int hamlee, hamle;

    cin >> hammle;

    stringstream ss;
    ss << hammle;
    int num;
    ss >> num;
    hamlee = num;
    hamle = hamlee;

    bool kac = false;

    bool info = false;

    if (hamle > 4 || hammle == "0") hammle = "03";

    if (hammle == "00") {
        int r = rand() % 50;
        if (r > enemy.speed) {
            r = rand() % 50;
            if (r > enemy.speed) {
                startScreen();
                return;
            }
            else kac = true;
        }
        else kac = true;
    }
    else if (hammle == "01") {
        x += 2;
        if (x == ex) x -= 2;
        kac = true;
    }
    else if (hammle == "02") {
        x -= 2;
        if (x < 0) x += 2;
        kac = true;
    }
    else if (hammle == "03") {
        kac = true;
    }
    else if (hammle == "04") {
        info = true;
    }

    if (!info) {

        int rar;

        if (!kac) {

            hamle = slots[envanter[hamle - 1] - 1].id + 1;

        }

        rar = slots[envanter[hamlee - 1] - 1].rarity;

        int at = 0;
        int cank = 0;

        if (mineBlood > 0) { health -= 2; mineBlood--; }

        if (minePoison > 0) { health -= 3; minePoison--; }

        if (enemyBlood > 0) { enemy.health -= 2; enemyBlood--; }

        if (enemyPoison > 0) { enemy.health -= 3; enemyPoison--; }

        if (weapons[hamle - 1].speed >= enemy.speed && !kac && weapons[hamle - 1].range >= ex - x && health > 0) {

            at = 0;
            cank = 0;

            if (weapons[hamle - 1].type == 2 && weapons[hamle - 1].use > 0) {
                int r = rand() % 100;

                if (r < weapons[hamle - 1].crit) cank = weapons[hamle - 1].critdamage;
                else if (r < weapons[hamle - 1].possibility) cank = weapons[hamle - 1].attack;
                else cank = -weapons[hamle - 1].attack;
                health += cank;

                gxp += max(0, cank / 5);

                weapons[hamle - 1].use--;
            }
            else if (weapons[hamle - 1].use == -1 || weapons[hamle - 1].use > 0) {
                if (weapons[hamle - 1].use != -1) weapons[hamle - 1].use--;
                at;
                int r = rand() % 100;


                if (r < weapons[hamle - 1].crit / 10 * (10 + rar)) at = (float)weapons[hamle - 1].critdamage / 10 * (10 + rar);
                else if (r < weapons[hamle - 1].possibility / 10 * (10 + rar)) at = (float)weapons[hamle - 1].attack / 10 * (10 + rar);
                else at = 0;

                if (at > 0) at += level - 1;

                enemy.health -= at;

                r = rand() % 100;

                if (r < enemy.aggression * 40 && enemy.aggression < 3) enemy.aggression++;

                gxp += at / 2;

                if (at > 0) {

                    if (weapons[hamle - 1].type == 3) enemyBlood += weapons[hamle - 1].featurePower;
                    if (weapons[hamle - 1].type == 4) enemyPoison += weapons[hamle - 1].featurePower;
                }

            }
        }

        int rat = 0;


        if (enemy.aggression == 0) {

            if (enemy.range >= ex - x) {

                int r = rand() % 100;

                if (r < enemy.crit) rat = enemy.critdamage;
                else if (r < enemy.possibility) rat = enemy.attack;
                else rat = 0;

                if (rat > 0) rat += enemy.level - 1;

                if (weapons[hamle - 1].type == 0 && at > 0) rat -= (float)rat / 100 * weapons[hamle - 1].featurePower / 10 * (10 + rar);
                if (rat < 0) rat = 0;

                int tr = 0;

                for (int i = 0; i < 4; i++) {
                    if (envanter[i] != 0) { if (weapons[slots[envanter[i] - 1].id].type == 5) tr += (int)((float)weapons[slots[envanter[i] - 1].id].featurePower / 10 * (10 + (int)slots[envanter[i] - 1].rarity)); }
                }

                rat -= (int)(((float)rat / 100) * (float)tr);
                if (rat < 0) rat = 0;


                if (enemy.health > 0) health -= rat;

                gxp += rat / 10;

                if (rat > 0) {

                    if (enemy.type == 1) mineBlood += enemy.featurePower;
                    if (enemy.type == 2) minePoison += enemy.featurePower;
                }
            }
            else if (ex < 18 && enemy.health < 5) ex += 2;

        }
        if (enemy.aggression == 1) {

            if (enemy.range >= ex - x) {

                int r = rand() % 100;

                if (r < enemy.crit) rat = enemy.critdamage;
                else if (r < enemy.possibility) rat = enemy.attack;
                else rat = 0;

                if (rat > 0) rat += enemy.level - 1;

                if (weapons[hamle - 1].type == 0 && at > 0) rat -= (float)rat / 100 * weapons[hamle - 1].featurePower / 10 * (10 + rar);
                if (rat < 0) rat = 0;

                int tr = 0;

                for (int i = 0; i < 4; i++) {
                    if (envanter[i] != 0) { if (weapons[slots[envanter[i] - 1].id].type == 5) tr += (int)((float)weapons[slots[envanter[i] - 1].id].featurePower / 10 * (10 + (int)slots[envanter[i] - 1].rarity)); }
                }

                rat -= (int)(((float)rat / 100) * (float)tr);
                if (rat < 0) rat = 0;


                if (enemy.health > 0) health -= rat;

                gxp += rat / 10;

                if (rat > 0) {

                    if (enemy.type == 1) mineBlood += enemy.featurePower;
                    if (enemy.type == 2) minePoison += enemy.featurePower;
                }
            }
            else if (ex < 18 && enemy.health < 5);
            else ex -= 2;

        }
        if (enemy.aggression == 2) {

            if (enemy.range >= ex - x) {

                int r = rand() % 100;

                if (r < enemy.crit) rat = enemy.critdamage;
                else if (r < enemy.possibility) rat = enemy.attack;
                else rat = 0;

                if (rat > 0) rat += enemy.level - 1;

                if (weapons[hamle - 1].type == 0 && at > 0) rat -= (float)rat / 100 * weapons[hamle - 1].featurePower / 10 * (10 + rar);
                if (rat < 0) rat = 0;

                int tr = 0;

                for (int i = 0; i < 4; i++) {
                    if (envanter[i] != 0) { if (weapons[slots[envanter[i] - 1].id].type == 5) tr += (int)((float)weapons[slots[envanter[i] - 1].id].featurePower / 10 * (10 + (int)slots[envanter[i] - 1].rarity)); }
                }

                rat -= (int)(((float)rat / 100) * (float)tr);
                if (rat < 0) rat = 0;

                if (enemy.health > 0) health -= rat;

                gxp += rat / 10;

                if (rat > 0) {

                    if (enemy.type == 1) mineBlood += enemy.featurePower;
                    if (enemy.type == 2) minePoison += enemy.featurePower;
                }
            }
            else ex -= 2;

        }
        if (enemy.aggression == 3) {

            if (enemy.range >= ex - x) {

                int r = rand() % 100;

                if (r < enemy.crit) rat = enemy.critdamage;
                else if (r < enemy.possibility) rat = enemy.attack;
                else rat = 0;

                if (rat > 0) rat += enemy.level - 1;

                if (weapons[hamle - 1].type == 0 && at > 0) rat -= (float)rat / 100 * weapons[hamle - 1].featurePower / 10 * (10 + rar);
                if (rat < 0) rat = 0;

                int tr = 0;

                for (int i = 0; i < 4; i++) {
                    if (envanter[i] != 0) { if (weapons[slots[envanter[i] - 1].id].type == 5) tr += (int)((float)weapons[slots[envanter[i] - 1].id].featurePower / 10 * (10 + (int)slots[envanter[i] - 1].rarity)); }
                }

                rat -= (int)(((float)rat / 100) * (float)tr);
                if (rat < 0) rat = 0;


                if (enemy.health > 0) health -= rat;

                gxp += rat / 10;

                if (rat > 0) {

                    if (enemy.type == 1) mineBlood += enemy.featurePower;
                    if (enemy.type == 2) minePoison += enemy.featurePower;
                }
            }
            if (ex - 2 != x) ex -= 2;

        }






        if (weapons[hamle - 1].speed < enemy.speed && !kac && weapons[hamle - 1].range >= ex - x && health > 0) {

            at = 0;
            cank = 0;

            if (weapons[hamle - 1].type == 2 && weapons[hamle - 1].use > 0) {
                int r = rand() % 100;

                if (r < weapons[hamle - 1].crit) cank = weapons[hamle - 1].critdamage;
                else if (r < weapons[hamle - 1].possibility) cank = weapons[hamle - 1].attack;
                else cank = -weapons[hamle - 1].attack;
                health += cank;

                gxp += max(0, cank / 5);

                weapons[hamle - 1].use--;
            }
            else if (weapons[hamle - 1].use == -1 || weapons[hamle - 1].use > 0) {
                if (weapons[hamle - 1].use != -1) weapons[hamle - 1].use--;
                at;
                int r = rand() % 100;

                if (r < weapons[hamle - 1].crit / 10 * (10 + rar)) at = (float)weapons[hamle - 1].critdamage / 10 * (10 + rar);
                else if (r < weapons[hamle - 1].possibility / 10 * (10 + rar)) at = (float)weapons[hamle - 1].attack / 10 * (10 + rar);
                else at = 0;


                if (at > 0) at += level - 1;

                enemy.health -= at;

                if (r < enemy.aggression * 40 && enemy.aggression < 3) enemy.aggression++;


                gxp += at / 2;

                if (at > 0) {

                    if (weapons[hamle - 1].type == 3) enemyBlood += weapons[hamle - 1].featurePower;
                    if (weapons[hamle - 1].type == 4) enemyPoison += weapons[hamle - 1].featurePower;
                }

            }
        }

        if (enemy.health < 1) {
            if (weapons[hamle - 1].type == 1 && at > 0) {
                out = out + " You Gained " + to_string(weapons[hamle - 1].featurePower) + " Money.";
                gp += weapons[hamle - 1].featurePower;
                gxp += gp;
            }

            money += enemy.level * 5 + gp - (enemy.level - level);
            xp += enemy.level * 5 + gxp;
            allxp += enemy.level * 5 + gxp;
            cout << endl << "You Win the Fight. You Gained " << enemy.level * 5 + gp << " Money. You Gained " << enemy.level * 5 + gxp << " Xp." << endl;
            if (xp > level * 75 + 75) { cout << "Level Up !" << endl; xp -= level * 75 + 75; level++; health += 50 + (level - 1) * 10; money += level * 10; if (level == 5) lfive = true; }
            if (weapons[hamle - 1].type == 2) {
                if (cank > 0) out = "You Gained " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
                else out = "You Were Poisoned! You Losed " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
            }
            else out = "You Dealt " + to_string(at) + " Damage. Enemy Dealt " + to_string(rat) + " Damage.";
            if (weapons[hamle - 1].type == 1 && at > 0) {
                out = out + " You Gained " + to_string(weapons[hamle - 1].featurePower) + " Money.";
                if (enemy.isBoss) out += " You Killed The " + enemy.name + "! Success Time : " + to_string(static_cast<chrono::duration<double>>(sc.now() - timer_start).count());
            }
            if (size(enemy.CustomDrop) > 0) {
                
                int tw = 0;

                for (int i = 0; i < size(enemy.CustomDrop); i++) {
                    tw += enemy.CustomDrop[i].weight;
                }

                int r = rand() % tw;

                Drop drp;
                drp.drop = "";

                for (int i = 0; i < size(enemy.CustomDrop); i++) {
                    tw -= enemy.CustomDrop[i].weight;
                    if (tw <= 0) drp = enemy.CustomDrop[i];
                }

                if (drp.drop == "") drp = enemy.CustomDrop[0];

                for (int i = 0; i < size(weapons); i++) {
                    if (drp.drop == weapons[i].name) {
                        Rarity rart = Common;
                        if (drp.rar == "Random") {
                            Rarity rart;
                            int r = rand() % 100;
                            if (r < 65) rart = Common;
                            else if (r < 85) rart = Uncommon;
                            else if (r < 90) rart = Rare;
                            else if (r < 95) rart = Epic;
                            else if (r < 98) rart = Legendary;
                            else if (r < 100) rart = Mythic;
                        }
                        else if (drp.rar == "Common") rart = Common;
                        else if (drp.rar == "Uncommon") rart = Uncommon;
                        else if (drp.rar == "Rare") rart = Rare;
                        else if (drp.rar == "Epic") rart = Epic;
                        else if (drp.rar == "Legendary") rart = Legendary;
                        else if (drp.rar == "Mythic") rart = Mythic;

                        weapons[i].on = true;
                        if (weapons[i].use != -1) { weapons[i].use++; if (findIfNotExist(i)) slots.push_back(slot.newSlot(i, rart)); }
                        else slots.push_back(slot.newSlot(i, rart));
                    }
                }

            }
            cout << endl << out << endl;
            string s;
            cin >> s;
            startScreen();
        }

        else if (health < 1) {
            cout << endl << "You Lose The Game. Success Time : " << to_string(static_cast<chrono::duration<double>>(sc.now() - timer_start).count());
            if (weapons[hamle - 1].type == 2) {
                if (cank > 0) out = "You Gained " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
                else out = "You Were Poisoned! You Losed " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
            }
            else out = "You Dealt " + to_string(at) + " Damage. Enemy Dealt " + to_string(rat) + " Damage.";
            if (weapons[hamle - 1].type == 1 && at > 0) {
                out = out + " You Gaines" + to_string(weapons[hamle - 1].featurePower) + " Money.";
                gp += weapons[hamle - 1].featurePower;
            }
            cout << endl << out << endl;
            string s;
            cin >> s;

            if (type == 0) {

                string myText;

                string fileT = "";

                ifstream MyReadFile("cmdrpg-lb.txt");

                while (getline(MyReadFile, myText)) {
                    fileT += myText + "\n";
                }

                MyReadFile.close();
                ofstream MyFile("cmdrpg-lb.txt");
                MyFile << fileT + name + "\n" + to_string(allxp) + "\n";
                MyFile.close();

            }

            exit(0);
        }
        else {
            if (weapons[hamle - 1].speed >= enemy.speed) {
                if (weapons[hamle - 1].type == 2) {
                    if (cank > 0) out = "You Gained " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
                    else out = "You Were Poisoned! You Losed " + to_string(cank) + " Health. Enemy Dealt " + to_string(rat) + " Damage.";
                }
                else out = "You Dealt " + to_string(at) + " Damage. Enemy Dealt " + to_string(rat) + " Damage.";
                if (weapons[hamle - 1].type == 1 && at > 0) {
                    out = out + " You Gaines" + to_string(weapons[hamle - 1].featurePower) + " Money.";
                    gp += weapons[hamle - 1].featurePower;
                }
            }
            else {
                if (weapons[hamle - 1].type == 2) {
                    if (cank > 0) out = "Enemy Dealt " + to_string(rat) + " Damage. You Gained " + to_string(cank) + " Health.";
                    else out = "Enemy Dealt " + to_string(rat) + " Damage. You Were Poisoned! You Losed " + to_string(cank) + " Health.";
                }
                else out = "Enemy Dealt " + to_string(rat) + " Damage. You Dealt " + to_string(at) + " Damage.";
                if (weapons[hamle - 1].type == 1 && at > 0) {
                    out = out + " You Gained " + to_string(weapons[hamle - 1].featurePower) + " Money.";
                    gp += weapons[hamle - 1].featurePower;
                }
            }


            raidStep(out);
        }

    }
    else {
        int what;

        cout << "Which Feature (0:Enemy Rest Weapons): ";
        cin >> what;
        if (what == 0) {
            out = "\nName : " + enemy.name;
            out += "\nLevel : " + to_string(enemy.level);
            out += "\nHealth : " + to_string(enemy.health);
            out += "\nAccuracy : " + to_string(enemy.possibility);
            out += "\nDamage : " + to_string(enemy.attack);
            out += "\nCritical Change : " + to_string(enemy.crit);
            out += "\nCritical Damage : " + to_string(enemy.critdamage);
            out += "\nSpeed : " + to_string(enemy.speed);
            out += "\nRange : " + to_string(enemy.range);
            if (enemy.type == 0) out += "\nType : None";
            else if (enemy.type == 1) out += "\nType : Bleed Maker";
            else if (enemy.type == 2) out += "\nType : Poison Maker";
            out += "\nFeature Power : " + to_string(enemy.featurePower);
            out += "\n";
        }
        else {
            string incode, outcode = "\033[0m";

            if (slots[envanter[what-1] - 1].rarity == Common) incode = "";
            else if (slots[envanter[what - 1] - 1].rarity == Uncommon) incode = "\033[1;32m";
            else if (slots[envanter[what - 1] - 1].rarity == Rare) incode = "\033[1;34m";
            else if (slots[envanter[what - 1] - 1].rarity == Epic) incode = "\033[1;35m";
            else if (slots[envanter[what - 1] - 1].rarity == Legendary) incode = "\033[1;33m";
            else if (slots[envanter[what - 1] - 1].rarity == Mythic) incode = "\033[1;31m";

            what--;
            out = "\nName : " + incode + weapons[slots[envanter[what] - 1].id].name + outcode;
            out += "\nAccuracy : " + to_string(weapons[slots[envanter[what] - 1].id].possibility / 10 * (10 + (int)slots[envanter[what] - 1].rarity));
            out += "\nDamage : " + to_string((int)((float)weapons[slots[envanter[what] - 1].id].attack / 10 * (10 + (int)slots[envanter[what] - 1].rarity)));
            out += "\nCritical Change : " + to_string(weapons[slots[envanter[what] - 1].id].crit / 10 * (10 + (int)slots[envanter[what] - 1].rarity));
            out += "\nCritical Damage : " + to_string((int)((float)weapons[slots[envanter[what] - 1].id].critdamage / 10 * (10 + (int)slots[envanter[what] - 1].rarity)));
            out += "\nSpeed : " + to_string(weapons[slots[envanter[what] - 1].id].speed);
            out += "\nRange : " + to_string(weapons[slots[envanter[what] - 1].id].range);
            if (weapons[slots[envanter[what] - 1].id].type == 0) out += "\nType : Defense";
            else if (weapons[slots[envanter[what] - 1].id].type == 1) out += "\nType : Money Gainer";
            else if (weapons[slots[envanter[what] - 1].id].type == 2) out += "\nType : Consumable";
            else if (weapons[slots[envanter[what] - 1].id].type == 3) out += "\nType : Bleed Maker";
            else if (weapons[slots[envanter[what] - 1].id].type == 4) out += "\nType : Poison Maker";
            else if (weapons[slots[envanter[what] - 1].id].type == 5) out += "\nType : Armor";
            out += "\nFeature Power : " + to_string((int)((float)weapons[slots[envanter[what] - 1].id].featurePower / 10 * (10 + (int)slots[envanter[what] - 1].rarity)));
            if ((int)slots[envanter[what] - 1].rarity == 0) out += "\nRarity : Common";
            else if ((int)slots[envanter[what] - 1].rarity == 1) out += "\nRarity : \033[1;32mUncommon\033[0m";
            else if ((int)slots[envanter[what] - 1].rarity == 2) out += "\nRarity : \033[1;34mRare\033[0m";
            else if ((int)slots[envanter[what] - 1].rarity == 3) out += "\nRarity : \033[1;35mEpic\033[0m";
            else if ((int)slots[envanter[what] - 1].rarity == 4) out += "\nRarity : \033[1;33mLegendary\033[0m";
            else if ((int)slots[envanter[what] - 1].rarity == 5) out += "\nRarity : \033[1;31mMythic\033[0m";
            out += "\n";

        }



        raidStep(out);
    }

}

void randomRaid() {
    clear();

    int fullR = 0;

    for (int i = 0; i < size(enemys); i++) {
        if (enemys[i].level == level) fullR += enemys[i].weight;
        else if (abs(level - enemys[i].level) == 1) fullR += enemys[i].weight / 2;
    }


    fullR = rand() % fullR;

    for (int i = 0; i < size(enemys); i++) {
        if (enemys[i].level == level) fullR -= enemys[i].weight;
        else if (abs(level - enemys[i].level) == 1) fullR -= enemys[i].weight / 2;
        if (fullR < 0) {

            enemy = enemys[i]; break;
        }
    }

    enemy.health -= enemy.health / 10 * (enemy.level - level);
    enemy.attack -= enemy.attack / 10 * (enemy.level - level);
    enemy.critdamage -= enemy.critdamage / 10 * (enemy.level - level);


    x = 2 + rand() % 3;
    if (x % 2 == 0) x--;
    ex = 15 + rand() % 3;
    if (ex % 2 == 0) ex--;

    gp = 0;
    gxp = 0;

    mineBlood = 0;
    minePoison = 0;
    enemyBlood = 0;
    enemyPoison = 0;

    raidStep("");
}

void se() {

    int id;

    cin >> id;

    clear();


    enemy = enemys[id];


    enemy.health -= enemy.health / 10 * (enemy.level - level);
    enemy.attack -= enemy.attack / 10 * (enemy.level - level);
    enemy.critdamage -= enemy.critdamage / 10 * (enemy.level - level);


    x = 2 + rand() % 3;
    if (x % 2 == 0) x--;
    ex = 15 + rand() % 3;
    if (ex % 2 == 0) ex--;

    gp = 0;
    gxp = 0;

    mineBlood = 0;
    minePoison = 0;
    enemyBlood = 0;
    enemyPoison = 0;

    raidStep("");
}

void startScreen() {
    clear();

    cout << "#####  #   #  ####     ####   ####    ####" << endl;
    cout << "#      ## ##  #   #    #   #  #   #  #    " << endl;
    cout << "#      # # #  #   #    ####   ####   #   #" << endl;
    cout << "#####  #   #  ####     #   #  #       ### " << endl << endl;

    cout << "Welcome to CMD RPG." << endl << name << endl << "Health: " << health << endl << "Money: " << money << endl << "Level: " << level << "    Xp:" << xp << endl << endl;

    string wtd;

    cout << "What you will do:\n0 for Random Attack.\n1 for go to Market\n2 for go to Inventory\n\n ";

    cin >> wtd;

    if (wtd == "0") randomRaid();
    else if (wtd == "1") goMarket();
    else if (wtd == "2") goInventory();
    else if (wtd == "Debug~SE") se();
    else startScreen();


}

typedef struct Score {
public:
    string name;
    int value;
}Scoress;

bool compare(Scoress a, Scoress b) {
    if (a.value < b.value)
        return 0;
    else
        return 1;
}

void leaderBoard() {

    clear();

    string filename = "cmdrpg-lb.txt";
    string line;
    vector<Scoress> vec;
    ifstream mFile(filename);
    if (mFile.is_open())
    {
        while (!mFile.eof())
        {
            Score scor;
            getline(mFile, line);
            scor.name = line;
            getline(mFile, line);
            stringstream ss;
            ss << line;
            int num;
            ss >> num;
            scor.value = num;
            vec.push_back(scor);
        }
        mFile.close();
    }
    else
        cout << "Couldn't open the file\n";


    Scoress arr[1000];

    for (int i = 0; i < vec.size() - 1; i++) arr[i] = vec[i];

    sort(arr, arr + vec.size() - 1, compare);


    for (int j = 0; j < vec.size() - 1; j++)
    {
        cout << j + 1 << ":" << arr[j].name << ":" << arr[j].value << endl;
    }

    string bos;
    cin >> bos;

}
void LoadFromJSON(string path) {

    ifstream f(path);
    json data = json::parse(f);

    int el = data["Enemys"]["Count"];
    int wl = data["Weapons"]["Count"];

    for (int i = 0; i < el; i++) {
        Enemy Nenemy;
        Nenemy.name = data["Enemys"][to_string(i)]["Name"];
        Nenemy.level = data["Enemys"][to_string(i)]["Level"];
        Nenemy.health = data["Enemys"][to_string(i)]["Health"];
        Nenemy.attack = data["Enemys"][to_string(i)]["Attack"];
        Nenemy.possibility = data["Enemys"][to_string(i)]["Possibility"];
        Nenemy.crit = data["Enemys"][to_string(i)]["Crit"];
        Nenemy.critdamage = data["Enemys"][to_string(i)]["CritDamage"];
        Nenemy.weight = data["Enemys"][to_string(i)]["Weight"];
        Nenemy.speed = data["Enemys"][to_string(i)]["Speed"];
        Nenemy.range = data["Enemys"][to_string(i)]["Range"];
        Nenemy.aggression = data["Enemys"][to_string(i)]["Aggression"];
        Nenemy.type = data["Enemys"][to_string(i)]["Type"];
        Nenemy.featurePower = data["Enemys"][to_string(i)]["FeaturePower"];
        Nenemy.isBoss = data["Enemys"][to_string(i)]["IsBoss"];
        int drops = data["Enemys"][to_string(i)]["CustomDrop"]["Count"];
        for (int j = 0; j < drops; j++) {
            Drop Ndrop;
            Ndrop.drop = data["Enemys"][to_string(i)]["CustomDrop"][to_string(j)]["Drop"];
            Ndrop.rar = data["Enemys"][to_string(i)]["CustomDrop"][to_string(j)]["Rarity"];
            Ndrop.weight = data["Enemys"][to_string(i)]["CustomDrop"][to_string(j)]["Weight"];
            Nenemy.CustomDrop.push_back(Ndrop);
        }
        enemys.push_back(Nenemy);
    }

    for (int i = 0; i < wl; i++) {
        Weapon Nweapon;
        Nweapon.name = data["Weapons"][to_string(i)]["Name"];
        Nweapon.attack = data["Weapons"][to_string(i)]["Attack"];
        Nweapon.possibility = data["Weapons"][to_string(i)]["Possibility"];
        Nweapon.crit = data["Weapons"][to_string(i)]["Crit"];
        Nweapon.critdamage = data["Weapons"][to_string(i)]["CritDamage"];
        Nweapon.speed = data["Weapons"][to_string(i)]["Speed"];
        Nweapon.range = data["Weapons"][to_string(i)]["Range"];
        Nweapon.type = data["Weapons"][to_string(i)]["Type"];
        Nweapon.featurePower = data["Weapons"][to_string(i)]["FeaturePower"];
        Nweapon.use = data["Weapons"][to_string(i)]["Use"];
        Nweapon.on = data["Weapons"][to_string(i)]["On"];
        Nweapon.HaveParentWeapon = data["Weapons"][to_string(i)]["HaveParentWeapon"];
        Nweapon.ParentCost = data["Weapons"][to_string(i)]["ParentCost"];
        Nweapon.cost = data["Weapons"][to_string(i)]["Cost"];
        Nweapon.isOnlyDrop = data["Weapons"][to_string(i)]["IsOnlyDrop"];
        weapons.push_back(Nweapon);
    }

}


int main() {

    setlocale(LC_ALL, "Turkish");

    srand(time(NULL));

    clear();

    DIR* directory;

    struct dirent* entry;
    directory = opendir(".");
    
    while ((entry = readdir(directory)) != NULL)
    {
        string fname = entry->d_name;
        if (entry->d_type == DT_REG && fname.find(".json") != std::string::npos)
        {
            LoadFromJSON(fname);
        }

    }

    for (int i = 0; i < size(weapons); i++) {
        if (weapons[i].on) slots.push_back(slot.newSlot(i, Common));
    }



    do {

        cout << "User Name: ";
        cin >> name;

    } while (name.length() > 12);

    if (name == "Debug~Man") {
        money = 99999900;
    }

    while (true) {
        cout << "Game Mode (0: Classic , 1: Leaderboard): ";
        cin >> type;
        if (type > -1 && type < 2) break;
    }

    if (type != 1) { timer_start = sc.now(); startScreen(); }
    else leaderBoard();

}
