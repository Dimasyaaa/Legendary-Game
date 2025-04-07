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
        cout << " |  Предмет: " << name << endl;
        cout << " |  Описание: " << description << endl;
        cout << " |  Сила: " << power_item << endl;
        cout << " |  Ловкость: " << dexterity_item << endl;
        cout << " |  Скорость: " << speed_item << endl;
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
        cout << "|  Имя персонажа: " << name << endl;
        cout << "|  Тип: " << type << endl;
        cout << "|  Сила: " << power_Character << endl;
        cout << "|  Ловкость: " << dexterity_Character << endl;
        cout << "|  Телосложение: " << bodytype_Character << endl;
        cout << "|  Интеллект: " << intelligence_Character << endl;
        cout << "|  Удача: " << luck_Character << endl;
        cout << "----------------------------------------------|" << endl;

        cout << "Инвентарь:" << endl;
        for (const auto& item : inventory) {
            item.display();
        }
    }

    // Метод для получения имени персонажа
    string getName() const { return name; }

    // Метод для выполнения атаки
    void attack(const Character& enemy) const {
        cout << name << " атакует " << enemy.getName() << "!" << endl;
    }
};

// Класс главного героя, наследуется от Character
class Hero : public Character {
public:
    // Конструктор главного героя
    Hero(const string& name, float power, float dexterity, float bodytype, float intelligence, float luck)
        : Character(name, "Главный герой", power, dexterity, bodytype, intelligence, luck) {}

    // Метод для специальной атаки
    void specialAttack() const {
        cout << name << " использует специальную атаку!" << endl;
    }
};

// Класс врага, наследуется от Character
class Enemy : public Character {
public:
    // Конструктор врага
    Enemy(const string& name, float power, float dexterity, float bodytype, float intelligence, float luck)
        : Character(name, "Враг", power, dexterity, bodytype, intelligence, luck) {}

    // Метод для атаки
    void attack(const Hero& hero) const {
        cout << name << " атакует " << hero.getName() << "!" << endl;
    }
};

// Функция для создания главного героя
Hero createHero() {
    string name;
    float power, dexterity, bodytype, intelligence, luck;

    cout << "Введите имя главного героя: ";
    cin >> name;

    cout << "Введите силу: ";
    cin >> power;
    cout << "Введите ловкость: ";
    cin >> dexterity;
    cout << "Введите телосложение: ";
    cin >> bodytype;
    cout << "Введите интеллект: ";
    cin >> intelligence;
    cout << "Введите удачу: ";
    cin >> luck;

    return Hero(name, power, dexterity, bodytype, intelligence, luck);
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создание главного героя через меню
    Hero hero = createHero();

    // Отображение информации о главном герое
    hero.displayCharacterInfo();

    // Создание врагов
    Enemy goblin("Гоблин", 30, 25, 40, 10, 5);

    // Отображение информации о врагах
    goblin.displayCharacterInfo();

    // Пример использования специальных методов
    hero.specialAttack();
    goblin.attack(hero);

    return 0;
}
