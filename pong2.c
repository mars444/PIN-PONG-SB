#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define BOARD_WIDTH                   80
#define BOARD_HEIGHT                  25
#define PLATFORM_DEFAULT              11



void engine(
    int X, int Y,
    int platform_1, int platform_2,
    int ball_x, int ball_y,
    int v_x, int v_y,
    int rating_player_1, int rating_player_2);

void display(
    int X, int Y,
    int platform_1, int platform_2,
    int ball_x, int ball_y,
    int rating_player_1, int rating_player_2);

int main() {
    initscr();
    keypad(stdscr, true);   //  Включаем режим чтения функциональных клавиш
    noecho();               //  Выключаем отображение вводимых символов, нужно для
    halfdelay(1);           //  Устанавливаем ограничение по времени ожидания getch() в 1 сек

    const int X = BOARD_WIDTH;
    const int Y = BOARD_HEIGHT;

    int platform_1 = 11;
    int platform_2 = 11;

    int ball_x = 20;
    int ball_y = 11;

    int v_x = 1;
    int v_y = -1;

    int rating_player_1 = 0;
    int rating_player_2 = 0;

    engine(X, Y, platform_1, platform_2, ball_x, ball_y, v_x, v_y, rating_player_1, rating_player_2);
    endwin();
}

void engine(
    int X, int Y,
    int platform_1, int platform_2,
    int ball_x, int ball_y,
    int v_x, int v_y,
    int rating_player_1, int rating_player_2) {
    char cm;

    // начальный экран

    printw("___________________________________________________________________________________\n");
    display(X, Y, platform_1, platform_2, ball_x, ball_y, rating_player_1, rating_player_2);
    printw("___________________________________________________________________________________\n");

    // запускаем игру
    while (1) {
        // ждем и проверяем ввод комманд
        // команды:
        // A|Z, K|M - движение платформ игроков
        // q - выход из игры

        if ((cm = getch()) != ERR) {
            if (cm == 'a' || cm == 'z' || cm == 'k' || cm == 'm' || cm == 'q' || cm == ' ') {
                // halfdelay(2);
                /// проверям кнопку на выход
                if (cm == 'q') {
                    printw("Exit the game (y/n) ?");
                    char exit_game;
                    char enter;
                    halfdelay(50);
                    exit_game = getch();
                    if (exit_game == 'y') {
                        halfdelay(5);
                        break;
                    } else if (exit_game == 'n') {
                        halfdelay(5);
                        continue;
                    }
                }

                // обработка положения платформ
                if (cm == 'a' && platform_1 > 1) {
                    platform_1 = platform_1 - 1;
                }

                if (cm == 'z' && platform_1 < Y - 1) {
                    platform_1 = platform_1 + 1;
                }

                if (cm == 'k' && platform_2 > 1) {
                    platform_2 = platform_2 - 1;
                }

                if (cm == 'm' && platform_2 < Y - 1) {
                    platform_2 = platform_2 + 1;
                }
            }
        } else {
            // halfdelay(2);
            // движение мяча
            // обрабатываются раньше, т.к. мяч летит быстрее и выжнее
            ball_x = ball_x + v_x;
            ball_y = ball_y + v_y;

            // отражение от стенок
            if ((ball_y == 0 || ball_y == Y) && (ball_x != 0 || ball_x != 80)) {
                v_y = -1 * v_y;
            }

            // соприкосновение с платформами
            if (ball_x == 1 && (platform_1 == ball_y ||
                platform_1 == ball_y - 1 ||
                platform_1 == ball_y + 1)) {
                v_x = -1 * v_x;
            }

            if (ball_x == X - 1 && (platform_2 == ball_y ||
                platform_2 == ball_y - 1 ||
                platform_2 == ball_y + 1)) {
                v_x = -1 * v_x;
            }
        }

        // условия розыгрыша раунда
        if (ball_x == 0) {
            // обновление результатов
            rating_player_2 = rating_player_2 + 1;

            if (rating_player_2 == 5) {
                clear();
                printw("\n\n                                Player 2 WIN\n");
                refresh();
                // сброс счета
                rating_player_1 = 0;
                rating_player_2 = 0;
                printw("\n\n\nExit...\n");
                refresh();
                for (int i = 3; i >= 0; i--) {
                    printw("%d...", i);
                    sleep(1);
                    refresh();
                }
                break;
            }

            // сброс позиции мяча
            ball_x = 60;
            ball_y = 11;
            // сброс вектора скорости
            v_x = -1;
            v_y = -1;
            // сброс позиции платформ
            platform_1 = 11;
            platform_2 = 11;
        }

        if (ball_x == X) {
            // обновление результатов
            rating_player_1 = rating_player_1 + 1;

            if (rating_player_1 == 5) {
                clear();
                printw("\n\n                                Player 2 WIN\n");
                refresh();
                // сброс счета
                rating_player_1 = 0;
                rating_player_2 = 0;
                printw("\n\n\nExit...\n");
                refresh();
                for (int i = 5; i >= 0; i--) {
                    printw("%d...", i);
                    sleep(1);
                    refresh();
                }
                break;
            }

            // сброс позиции мяча
            ball_x = 20;
            ball_y = 11;
            // сброс вектора скорости
            v_x = 1;
            v_y = -1;
            // сброс позиции платформ
            platform_1 = 11;
            platform_2 = 11;
        }
        clear();
        printw("___________________________________________________________________________________\n");
        display(X, Y, platform_1, platform_2, ball_x, ball_y, rating_player_1, rating_player_2);
        printw("___________________________________________________________________________________\n");
        refresh();
    }
}

void display(
    int X, int Y,
    int platform_1, int platform_2,
    int ball_x, int ball_y,
    int rating_player_1, int rating_player_2) {
    char platform = 'H';
    char ball = 'O';
    char net = '|';
    char space = ' ';

    // запускаем прорисовку экрана построчно
    for (int i = 0; i <= Y; i++) {
        // прорисовываем строку
        for (int j = 0; j <= X; j++) {
            // прорисовка мяча
            if (i == ball_y && j == ball_x) {
                printw("%c", ball);
                continue;
            }

            // прорисовка платформ
            if (j == 0 && (platform_1 == i || platform_1 == i + 1 || platform_1 == i - 1)) {
                printw("%c", platform);
                continue;
            }

            if (j == X && (platform_2 == i || platform_2 == i + 1 || platform_2 == i - 1)) {
                printw("%c", platform);
                continue;
            }

            // прорисовка сетки
            if (j == X / 2) {
                printw("%c", net);
                continue;
            }

            // прорисовка счета (тут сложно, т.к. мяч может закрывать одну из цифр)
            if (i == 1 && j == X / 2 - 3 && rating_player_1 < 10) {
                printw("%d", rating_player_1);
                continue;
            }

            if (i == 1 && j == X / 2 + 3 && rating_player_2 < 10) {
                printw("%d", rating_player_2);
                continue;
            }

            // теперь, когда счет больше 10-ти
            if (i == 1 && j == X / 2 - 2 && ball_x == X / 2 - 3 && rating_player_1 >= 10) {
                printw("%d", rating_player_1 % 10);
                continue;
            }

            if (i == 1 && j == X / 2 - 3 && ball_x == X / 2 - 2 && rating_player_1 >= 10) {
                printw("%d", rating_player_1 / 10);
                continue;
            }

            if (i == 1 && j == X / 2 - 3 && rating_player_1 >= 10) {
                printw("%d", rating_player_1);
                j = j + 1;
                continue;
            }

            if (i == 1 && j == X / 2 + 2 && ball_x == X / 2 + 3 && rating_player_2 >= 10) {
                printw("%d", rating_player_2 / 10);
                continue;
            }

            if (i == 1 && j == X / 2 + 3 && ball_x == X / 2 + 2 && rating_player_2 >= 10) {
                printw("%d", rating_player_2 % 10);
                continue;
            }

            if (i == 1 && j == X / 2 + 2 && rating_player_2 >= 10) {
                printw("%d", rating_player_2);
                j = j + 1;
                continue;
            }

            // заполнение самого поля
            printw("%c", space);
        }
        printw("\n");
    }
}
