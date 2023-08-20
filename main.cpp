#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

inline void show_table(int& size, char table[][3]) {
    std::cout << "  ┌";
    for(int i = 0; i < std::pow(size, 2.1); i++) {
        std::cout << "─";
    }
    std::cout << "┐";

    for(int i = 0; i < size; i++) {
        std::cout << std::endl;
        if(i == 0) {
            std::cout << i + 1 << " │ ";
        }
        if(i == 1) {
            std::cout << i + 3 << " │ ";
        }
        if(i == 2) {
            std::cout << i + 5 << " │ ";
        }

        for(int j = 0; j < 3; j++) {
            std::cout << table[i][j] << " │ ";
        }
    }

    std::cout << std::endl << "  └";

    for(int i = 0; i < std::pow(size, 2.1); i++) {
        std::cout << "─";
    }

    std::cout << "┘" << std::endl;
}

bool has_win(char table[][3], char user_key) {
        if(table[0][0] == user_key && table[1][0] == user_key && table[2][0] == user_key) { //column check
            return true;
        } 
        else if(table[0][1] == user_key && table[1][1] == user_key && table[2][1] == user_key) {//column check
            return true;
        }
        else if(table[0][2] == user_key && table[1][2] == user_key && table[2][2] == user_key) {//column chec
            return true;
        }

        else if(table[0][0] == user_key && table[0][1] == user_key && table[0][2] == user_key) { //row check
            return true;
        } 
        else if(table[1][0] == user_key && table[1][1] == user_key && table[1][2] == user_key) {//row check
            return true;
        }
        else if(table[2][0] == user_key && table[2][1] == user_key && table[2][2] == user_key) {//row check
            return true;
        }

    return false;
}

int main() {
    std::string ANSI_RED = "\033[31m";
    std::string ANSI_RESET = "\033[0m";
    std::string error = ANSI_RED + "Error: ";
    std::string clear = "\033[2J";
    std::string ANSI_ITALIC = "\033[3m";
    std::string ANSI_PURPLE = "\033[35m";
    std::string success = ANSI_ITALIC + ANSI_PURPLE;
    int draw_position;
    char user_key;
    char table[3][3] = 
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int size = sizeof(table) / sizeof(table[0]);

    std::cout << std::endl << clear << "Welcome to Tic-Tac-Toe ✅" << std::endl << std::endl;
    show_table(size, table);

    while (user_key != 'o' && user_key != 'x') {
        std::cout << std::endl << ANSI_RESET << "> Which one do you wanna be? (o/x): ";
        std::cin >> user_key;
        if(user_key != 'o' && user_key != 'x') {
            std::cerr << ANSI_RED << "  [!] Oops, thats not a valid definition.";
        } else {
            std::cout << clear;
            break;
        }
    }

    show_table(size, table);
    std::cout << std::endl << " 👋 Glad to meet you." << std::endl;

    srand(static_cast<unsigned int>(time(0)));

    while(true) {
        std::cout << std::endl;
        std::cout << ANSI_RESET << "[Your turn] > Enter a position (1 - 9): ";
        std::cin >> draw_position;

        if(!draw_position) {
            std::cout << ANSI_RED << "  [!] Enter a integer value." << std::endl;
        } else {

            if(draw_position < 1  || draw_position > 9) {
                std::cerr << ANSI_RED << "  [!] The entered value is not a (1 - 9) range number correct.";
            } else { 
                int row = (draw_position - 1) / 3;
                int col = (draw_position - 1) % 3;
                if(table[row][col] != ' ') {
                    std::cout << ANSI_RED << "  [!] This position was already taken";
                } 
                else {
                    if(draw_position == 1) {
                        table[0][0] = user_key;
                        std::cout << clear;
                        show_table(size, table);
                    }
                    else if(draw_position == 2) {
                        table[0][1] = user_key;
                        std::cout << clear;
                        show_table(size, table);
                    }
                    else if(draw_position == 3) {
                        table[0][2] = user_key;
                        std::cout << clear;
                        show_table(size, table);
                    }
                    else if(draw_position == 4) {
                        table[1][0] = user_key;
                        std::cout << clear;
                        show_table(size, table);
                    }

                    std::cout << std::endl;
                    std::cout << "\e[1;93m[IA] Thinking... 🧠" << std::flush << std::endl;
                    int random_col = rand() % 3;
                    int random_row = rand() % 3;
                    while(table[random_col][random_row] != ' ') {
                        random_col = rand() % 3;
                        random_row = rand() % 3;
                    }

                    if(user_key == 'x') {
                        table[random_col][random_row] = 'o';
                    } 
                    else if(user_key == 'o') {
                        table[random_col][random_row] = 'x';
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << clear;

                    std::string temporal_position = std::to_string(draw_position);
                    std::string index = std::to_string(random_row * 3 + random_col + 1);

                    if(index == "1") {
                        index += "st";
                        temporal_position += "st";
                    } 
                    else if(index == "2") {
                        index += "nd";
                        temporal_position += "nd";
                    }
                     else if(index == "3") {
                        index += "rd";
                        temporal_position += "rd";
                    }
                     else if(index == "4") {
                        index += "th";
                        temporal_position += "th";
                    }
                     else if(index == "5") {
                        index += "th";
                        temporal_position += "th";
                    }
                     else if(index == "6") {
                        index += "th";
                        temporal_position += "th";
                    }
                     else if(index == "7") {
                        index += "th";
                        temporal_position += "th";
                    }
                     else if(index == "8") {
                        index += "th";
                        temporal_position += "th";
                    }
                     else if(index == "9") {
                        index += "th";
                        temporal_position += "th";
                    }

                    std::cout << "\e[0;34m\e[3m[You] Moved on the " << temporal_position << " position ✅" << std::endl << ANSI_RESET;
                    std::cout << "\e[0;32m\e[3m[IA] Moved on the " << index << " position ✅" << std::endl << std::endl << ANSI_RESET;
                    show_table(size, table);

                    if(has_win(table, user_key)) {
                        std::cout << std::endl;
                        std::cout << success <<"🎉 You have winned, congrats! 🥳" << ANSI_RESET;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}