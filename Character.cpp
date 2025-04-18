#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

//Класс Конвертор
class Converter{
private:
    //коэфиценты
    float factor_power; //силы
    float factor_dexterity;//ловкость
    float factor_bodytype;//телосложение
    float factor_intelligence;//интеллект
    float factor_luck;//удачи
public:
    Converter()
    :factor_power(1.0), factor_dexterity(1.0), factor_bodytype(1.0), factor_intelligence(1.0), factor_luck(1.0) {}
    //setters
    void set_factor_power(float value){
        factor_power = value;
    }
    void set_factor_dexterity(float value){
        factor_dexterity = value;
    }
    void set_factor_bodytype(float value){
        factor_bodytype = value;
    }
    void set_factor_intelligence(float value){
        factor_intelligence = value;
    }
    void set_factor_luck(float value){
        factor_luck = value;
    }
    //geters
    float get_factor_power(){
        return factor_power;
    }
    float get_factor_dexterity(){
        return factor_dexterity;
    }
    float get_factor_bodytype(){
        return factor_bodytype;
    }
    float get_factor_intelligence(){
        return factor_intelligence;
    }
    float get_factor_luck(){
        return factor_luck;
    }

};


// Класс предмета
class Item {
private:
    string name; // название предмета
    string description; // описание предмета
    float power_item; // сила предмета
    float dexterity_item; // ловкость предмета
    float speed_item; // скорость предмета

public:
    // Конструктор предмета
    Item(const string& name, const string& description, float power, float dexterity, float speed)
        : name(name), description(description), power_item(power), dexterity_item(dexterity), speed_item(speed) {}

    // Метод для отображения предмета
    void display() const {
        cout << " ----------------------------------------------|" << endl;
        cout << " |  Subject: " << name << endl;
        cout << " |  Description: " << description << endl;
        cout << " |  Power: " << power_item << endl;
        cout << " |  Dexterity: " << dexterity_item << endl;
        cout << " |  Speed: " << speed_item << endl;
        cout << " ----------------------------------------------| " << endl;
    }

    // Методы для получения характеристик предмета
    float getPower() const { return power_item; }
    float getDexterity() const { return dexterity_item; }
    float getSpeed() const { return speed_item; }
};

// Класс персонажа
class Character {
protected:
    string name; // имя персонажа
    string type; // тип персонажа (враг или класс)
    vector<Item> inventory; // инвентарь
    float power_Character; // сила персонажа
    float dexterity_Character; // ловкость персонажа
    float bodytype_Character; // телосложение персонажа
    float intelligence_Character; // интеллект персонажа
    float luck_Character; // удача персонажа

public:
    // Конструктор персонажа
    Character(const string& name, const string& type, float power, float dexterity, float bodytype, float intelligence, float luck)
        : name(name), type(type), power_Character(power), dexterity_Character(dexterity),
         bodytype_Character(bodytype), intelligence_Character(intelligence), luck_Character(luck) {}

    // Метод для добавления предмета в инвентарь
    void addItem(const Item& item) {
        inventory.push_back(item);
        // Влияние предмета на характеристики персонажа
        power_Character += item.getPower();
        dexterity_Character += item.getDexterity();
    }

    // Метод для отображения информации о персонаже
    virtual void displayCharacterInfo() const {

        cout << "----------------------------------------------|" << endl;
        cout << "|  Character's name: " << name << endl;
        cout << "|  Type: " << type << endl;
        cout << "|  Power: " << power_Character << endl;
        cout << "|  Dexterity: " << dexterity_Character << endl;
        cout << "|  Bodytype: " << bodytype_Character << endl;
        cout << "|  Intelligence: " << intelligence_Character << endl;
        cout << "|  Luck: " << luck_Character << endl;
        cout << "----------------------------------------------|" << endl;

        cout << "Inventory:" << endl;
        for (const auto& item : inventory) {
            item.display();
        }
    }

    // Метод для получения имени персонажа
    string getName() const { return name; }

    // Метод для выполнения атаки
    void attack(const Character& enemy) const {
        cout << name << " attacking " << enemy.getName() << "!" << endl;
    }
};

// Класс главного героя, наследуется от Character
class Hero : public Character {
public:
    // Конструктор главного героя
    Hero(const string& name, float power, float dexterity, float bodytype, float intelligence, float luck)
        : Character(name, "The main character", power, dexterity, bodytype, intelligence, luck) {}

    // Метод для специальной атаки
    void specialAttack() const {
        cout << name << " uses a special attack!" << endl;
    }
};

// Класс врага, наследуется от Character
class Enemy : public Character {
public:
    // Конструктор врага
    Enemy(const string& name, float power, float dexterity, float bodytype, float intelligence, float luck)
        : Character(name, "Enemy", power, dexterity, bodytype, intelligence, luck) {}

    // Метод для атаки
    void attack(const Hero& hero) const {
        cout << name << " attacking " << hero.getName() << "!" << endl;
    }
};

// Функция для создания главного героя
Hero createHero() {
    string name;
    float power, dexterity, bodytype, intelligence, luck;

    cout << "Enter the name of the main character: ";
    cin >> name;

    cout << "Enter the power: ";
    cin >> power;
    cout << "Enter dexterity: ";
    cin >> dexterity;
    cout << "Enter your physique: ";
    cin >> bodytype;
    cout << "Enter intelligence: ";
    cin >> intelligence;
    cout << "Enter luck: ";
    cin >> luck;

    return Hero(name, power, dexterity, bodytype, intelligence, luck);
}
