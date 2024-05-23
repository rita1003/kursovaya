#include <iostream>
#include <vector>
#include <iomanip>
#include "Windows.h"
#include <conio.h>

class Character {
private:
    int positionX1;
    int positionX2;
    int positionY;
public:
    int getX1() { return positionX1; }
    int getX2() { return positionX2; }
    int getY() { return positionY; }

    void setX1(int X1) {
        if (X1 > 0 && X1 < 52)
            this->positionX1 = X1;
    }
    void setX2(int X2) {
        if (X2 > 1 && X2 < 53)
            this->positionX2 = X2;
    }
    void setY(int Y) {
        if (Y > 0 && Y < 26)
            this->positionY = Y;
    }
};

class Prey : public Character {
public:
    Prey() {
        setX1(14); setX2(15), setY(12);
    }

    void npcActing() {
        int temp1 = -1 + rand() % 3;
        int temp2 = -1 + rand() % 3;
        while (temp1 == 0 && temp2 == 0) {
            temp1 = -1 + rand() % 3;
            temp2 = -1 + rand() % 3;
        }

        setX1(getX1() + temp1);
        setX2(getX2() + temp1);
        setY(getY() + temp2);
    }
};

class Predator : public Character {
private:
    Prey& prey;
public:
    Predator(Prey& prey) : prey(prey) {
        setX1(36); setX2(37), setY(12);
    }

    void npcActing() {
        if (prey.getX1() != getX1() && prey.getX1() != getX2() && prey.getX2() != getX1() && prey.getY() != getY()) {
            int temp = rand() % 2;
            switch (temp) {
            case 0:
                if (prey.getX1() < getX1()) {
                    setX1((getX1()) - 1);
                    setX2((getX2()) - 1);
                }
                else {
                    setX1((getX1()) + 1);
                    setX2((getX2()) + 1);
                }
            case 1:
                if (prey.getY() < getY())
                    setY((getY()) - 1);
                else
                    setY((getY()) + 1);
            }
        }
        else if (prey.getX1() == getX1() || prey.getX1() == getX2() || prey.getX2() == getX1()) {
            if (prey.getY() < getY())
                setY((getY()) - 1);
            else if (prey.getY() > getY())
                setY((getY()) + 1);
        }
        else if (prey.getY() == getY()) {
            if (prey.getX1() < getX1()) {
                setX1((getX1()) - 1);
                setX2((getX2()) - 1);
            }
            else if (prey.getX1() > getX1()) {
                setX1((getX1()) + 1);
                setX2((getX2()) + 1);
            }
        }
    }
};

class Arena {
private:
    int side;
    char border;
    std::vector<std::vector<char>> arena;
    Predator* pred;
    Prey* prey;
    bool GameOver = false;
public:
    Arena(Predator* pred, Prey* prey) : side{ 27 }, border('='), arena(side), pred(pred), prey(prey) {
        for (int i{ 0 }; i < side; i++) {
            if (i == 0 || i == (side)-1) {
                arena[i].resize(side * 2, border);
            }
            else {
                arena[i].resize(side * 2);
                for (int j{ 0 }; j < side * 2; j++) {
                    if (j == 0 || j == (side * 2) - 1)
                        arena[i][j] = '|';
                    else
                        arena[i][j] = ' ';
                }
            }
        }
    }

    void arenaShow() {
        arena[(*prey).getY()][(*prey).getX1()] = '*';
        arena[(*prey).getY()][(*prey).getX2()] = '*';
        arena[(*pred).getY()][(*pred).getX1()] = '(';
        arena[(*pred).getY()][(*pred).getX2()] = ')';

        for (int i{ 0 }; i < side; i++) {
            for (int j{ 0 }; j < side * 2; j++) {
                if (j == 0 && i != 0 && i != side - 1)
                    std::cout << std::setw(5) << std::right << i;
                else if (j == 0)
                    std::cout << std::setw(5) << std::right << "";
                std::cout << arena[i][j];
            }
            std::cout << std::endl;
            if (i == side - 1) {
                for (int j{ 0 }; j < side * 2; j++) {
                    if (j == 0 || j == (side * 2) - 1)
                        std::cout << std::setw(6) << std::left << "";
                    else if (j == 1)
                        std::cout << " ";
                    else if (j % 2 != 0)
                        std::cout << std::setw(2) << std::left << j / 2;
                    else
                        std::cout << "";
                }
                std::cout << std::endl;
            }
        }
        arena[(*prey).getY()][(*prey).getX1()] = ' ';
        arena[(*prey).getY()][(*prey).getX2()] = ' ';
        arena[(*pred).getY()][(*pred).getX1()] = ' ';
        arena[(*pred).getY()][(*pred).getX2()] = ' ';
    }

    bool ifGameisOver() {
        if (((*prey).getX1() == (*pred).getX1() || (*prey).getX1() == (*pred).getX2() || (*prey).getX2() == (*pred).getX1()) && (*prey).getY() == (*pred).getY())
            return true;
        else
            return false;
    }
};

class Point2D : public Character {
private:
    Prey& prey;
    Predator& pred;
public:
    Point2D(Predator& pred, Prey& prey) : prey(prey), pred(pred) {}

    void playerPreyActing() {
        bool is_wrong_key = true;
        while (is_wrong_key) {
            int hit;
            std::cout << "Введите клавишу (1-8): ";
            std::cin >> hit;
            switch (hit) {
            case 1: //W
                is_wrong_key = false;
                prey.setY(prey.getY() - 1);
                break;
            case 2: //S
                is_wrong_key = false;
                prey.setY(prey.getY() + 1);
                break;
            case 3: //A
                is_wrong_key = false;
                prey.setX1(prey.getX1() - 1);
                prey.setX2(prey.getX2() - 1);
                break;
            case 4: //D
                is_wrong_key = false;
                prey.setX1(prey.getX1() + 1);
                prey.setX2(prey.getX2() + 1);
                break;
            case 5: //E
                is_wrong_key = false;
                prey.setY(prey.getY() - 1);
                prey.setX1(prey.getX1() + 1);
                prey.setX2(prey.getX2() + 1);
                break;
            case 6: //Q
                is_wrong_key = false;
                prey.setY(prey.getY() - 1);
                prey.setX1(prey.getX1() - 1);
                prey.setX2(prey.getX2() - 1);
                break;
            case 7: //C
                is_wrong_key = false;
                prey.setY(prey.getY() + 1);
                prey.setX1(prey.getX1() + 1);
                prey.setX2(prey.getX2() + 1);
                break;
            case 8: //Z
                is_wrong_key = false;
                prey.setY(prey.getY() + 1);
                prey.setX1(prey.getX1() - 1);
                prey.setX2(prey.getX2() - 1);
                break;
            default:
                std::cout << "Неверно нажатая клавиша." << std::endl;
                break;
            }

        }
    }

    void playerPredActing() {
        bool are_wrong_steps = true;
        std::cout << "Выберите кол-во ходов: 1, 2, 3: ";
        int steps;
        std::cin >> steps;
        while (are_wrong_steps) {
            switch (steps) {
            case 1: //1
                are_wrong_steps = false;
                break;
            case 2: //2
                are_wrong_steps = false;
                break;
            case 3: //3
                are_wrong_steps = false;
                break;
            default:
                std::cout << "Неверно нажатая клавиша." << std::endl;
                std::cout << "Выберите кол-во ходов: 1, 2, 3: ";
                std::cin >> steps;
                break;
            }
        }
        bool is_wrong_key = true;
        while (is_wrong_key) {
            int hit;
            std::cout << "Введите клавишу (1-4): ";
            std::cin >> hit;
            switch (hit) {
            case 1: //W
                is_wrong_key = false;
                pred.setY(pred.getY() - (1 * steps));
                break;
            case 2: //S
                is_wrong_key = false;
                pred.setY(pred.getY() + (1 * steps));
                break;
            case 3: //A
                is_wrong_key = false;
                pred.setX1(pred.getX1() - (1 * steps));
                pred.setX2(pred.getX2() - (1 * steps));
                break;
            case 4: //D
                is_wrong_key = false;
                pred.setX1(pred.getX1() + (1 * steps));
                pred.setX2(pred.getX2() + (1 * steps));
                break;
            default:
                std::cout << "Неверно нажатая клавиша." << std::endl;
                break;
            }
        }
    }


};


int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "NEW GAME!";
    Sleep(1000);
    system("cls");

    std::cout << "Клавиши управления: 1,2,3,4,5,6,7,8.\n";
    std::cout << "** - жертва, () - хищник.\n";

    std::cout << "За кого вы хотите играть?\n1 - хищник, 2 - жертва\n";
    std::cout << "0 - ВЫХОД.\n";
    std::cout << "Ваш выбор : ";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1: {
        Prey prey;
        Predator pr(prey);
        Arena ar(&pr, &prey);
        Point2D ddd(pr, prey);
        int steps = 30;
        while (true) {
            system("cls");
            std::cout << "Осталось шагов: " << steps << std::endl;

            ar.arenaShow();

            if (ar.ifGameisOver()) {
                system("cls");
                std::cout << "WON!\n";
                break;
            }

            if (steps == 0) {
                system("cls");
                std::cout << "LOST!\n";
                break;
            }

            std::cout << "ХОДИТЕ!\n";
            ddd.playerPredActing();
            system("cls");
            ar.arenaShow();

            if (ar.ifGameisOver()) {
                system("cls");
                std::cout << "WON!\n";
                break;
            }

            prey.npcActing();
            steps--;
        }
        break;
    }
    case 2: {
        Prey prey;
        Predator pr(prey);
        Arena ar(&pr, &prey);
        Point2D ddd(pr, prey);
        int steps = 30;
        while (true) {
            system("cls");

            std::cout << "Осталось шагов: " << steps << std::endl;
            ar.arenaShow();

            if (ar.ifGameisOver()) {
                system("cls");
                std::cout << "LOST!\n";
                break;
            }

            if (steps == 0) {
                system("cls");
                std::cout << "WON!\n";
                break;
            }

            std::cout << "ХОДИТЕ!\n";
            ddd.playerPreyActing();
            pr.npcActing();
            steps--;
        }
        break;
    }
    case 0:
        system("cls");
        std::cout << "GAME OVER!" << std::endl;
        return 0;
        break;
    default:
        system("cls");
        std::cout << "Некорректный выбор...\n";
        break;
    }
    return 0;
}
