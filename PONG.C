#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
void engine(int X, int Y, int p_1, int p_2, int b_x, int b_y, int v_x, int v_y, int r_1, int r_2);
void display(int X, int Y, int p_1, int p_2, int b_x, int b_y, int r_1, int r_2);
void pong(int X, int Y, int p_1, int p_2, int b_x, int b_y, int v_x, int v_y, int r_1, int r_2);


    static int p_1 = 11;
    static int p_2 = 11;

    static int r_1 = 0;
    static int r_2 = 0;

    static int b_x = 20;
    static int b_y = 11;



typedef struct PinPong {
    int p_1;
    int p_2;
    int r_1;
    int r_2;
    int b_x;
    int b_y;
} Pong;

 

int main() {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    const int X = 80;
    const int Y = 25;

    int v_x = 1;
    int v_y = -1;



    int pid = fork();
    if(pid == 0) {
        pong(X, Y,p_1,p_2,b_x,b_y, v_x, v_y, r_1, r_2);
        
    } else {
        engine(X, Y,p_1,p_2,b_x,b_y, v_x, v_y, r_1, r_2);;
    }
    
    endwin();
}

void pong(int X, int Y, int p_1, int p_2, int b_x, int b_y, int v_x, int v_y, int r_1, int r_2) {
    while (1) {
            // проверям кнопку на выход
            // if (cm == 'q') {
            //     break;
            // }

            // движение мяча
            // обрабатываются раньше, т.к. мяч летит быстрее и выжнее
            b_x = b_x + v_x;
            b_y = b_y + v_y;

            // отражение от стенок
            if ((b_y == 0 || b_y == Y) && (b_x != 0 || b_x != 80)) {
                v_y = -1 * v_y;
            }

            // соприкосновение с платформами
            if (b_x == 1 && (p_1 == b_y || p_1 == b_y - 1 || p_1 == b_y + 1)) {
                v_x = -1 * v_x;
            }

            if (b_x == X - 1 && (p_2 == b_y ||p_2 == b_y - 1 || p_2 == b_y + 1)) {
                v_x = -1 * v_x;
            }
            clear();
            display(X, Y,p_1,p_2,b_x,b_y, r_1, r_2);
            refresh();
            printf("p1 == %d p2 == %d  bx == %d   by == %d  r1 == %d  r2 == %d  \n", p_1, p_2, b_x, b_y , r_1, r_2);
            
            sleep(1);
            }

}

void engine(int X, int Y, int p_1, int p_2, int b_x, int b_y, int v_x, int v_y, int r_1, int r_2) {
    char cm;

    // начальный экран
      display(X, Y,p_1,p_2,b_x,b_y, r_1, r_2);

    // запускаем игру
    while (1) {
        // ждем и проверяем ввод комманд
        // команды:
        // A|Z, K|M - движение платформ игроков
        // q - выход из игры

            cm = getch();

          
             // условия розыгрыша раунда
            if (b_x == 0) {
                // обновление результатов
                r_2 = r_2 + 1;

                if (r_2 == 21) {
                    printw("Player 2 WIN!\n");
                    // сброс счета
                    r_1 = 0;
                    r_2 = 0;
                    break;
                }

                // сброс позиции мяча
               b_x = 60;
               b_y = 11;
                // сброс вектора скорости
                v_x = -1;
                v_y = -1;
                // сброс позиции платформ
               p_1 = 11;
               p_2 = 11;
            }

            if (b_x == X) {
                // обновление результатов
                r_1 = r_1 + 1;

                if (r_1 == 21) {
                    printw("Player 1 WIN!\n");
                    // сброс счета
                    r_1 = 0;
                    r_2 = 0;
                    break;
                }

                // сброс позиции мяча
               b_x = 20;
               b_y = 11;
                // сброс вектора скорости
                v_x = 1;
                v_y = -1;
                // сброс позиции платформ
               p_1 = 11;
               p_2 = 11;
            }

            // обработка пробела по заданию
            if (cm == ' ') {
                display(X, Y,p_1,p_2,b_x,b_y, r_1, r_2);
                continue;
            }

            // обработка положения платформ
            if (cm == 'a' && p_1 > 1) {
               p_1 =p_1 - 1;
            }

            if (cm == 'z' && p_1 < Y - 1) {
               p_1 =p_1 + 1;
            }

            if (cm == 'k' && p_2 > 1) {
               p_2 =p_2 - 1;
            }

            if (cm == 'm' && p_2 < Y - 1) {
               p_2 =p_2 + 1;
            }
            clear();
            display(X, Y,p_1,p_2,b_x, b_y, r_1, r_2);
            refresh();
        }
    
}

void display(int X, int Y, int p_1, int p_2, int b_x, int b_y, int r_1, int r_2) {
    char platform = 'H';
    char ball = 'O';
    char net = '|';
    char space = ' ';

    // запускаем прорисовку экрана построчно
    for (int i = 0; i <= Y; i++) {
        // прорисовываем строку
        for (int j = 0; j <= X; j++) {
            // прорисовка мяча
            if (i == b_y && j == b_x) {
                printw("%c", ball);
                continue;
            }

            // прорисовка платформ
            if (j == 0 && (p_1 == i || p_1 == i + 1 || p_1 == i - 1)) {
                printw("%c", platform);
                continue;
            }

            if (j == X && (p_2 == i || p_2 == i + 1 || p_2 == i - 1)) {
                printw("%c", platform);
                continue;
            }

            // прорисовка сетки
            if (j == X/2) {
                printw("%c", net);
                continue;
            }

            // прорисовка счета (тут сложно, т.к. мяч может закрывать одну из цифр)
            if (i == 1 && j == X/2 - 3 && r_1 < 10) {
                printw("%d", r_1);
                continue;
            }

            if (i == 1 && j == X/2 + 3 && r_2 < 10) {
                printw("%d", r_2);
                continue;
            }

            // теперь, когда счет больше 10-ти
            if (i == 1 && j == X/2 - 2 && b_x == X/2 - 3 && r_1 >= 10) {
                printw("%d", r_1 % 10);
                continue;
            }

            if (i == 1 && j == X/2 - 3 && b_x == X/2 - 2 && r_1 >= 10) {
                printw("%d", r_1 / 10);
                continue;
            }

            if (i == 1 && j == X/2 - 3 && r_1 >= 10) {
                printw("%d", r_1);
                j = j + 1;
                continue;
            }

            if (i == 1 && j == X/2 + 2 && b_x == X/2 + 3 && r_2 >= 10) {
                printw("%d", r_2 / 10);
                continue;
            }

            if (i == 1 && j == X/2 + 3 && b_x == X/2 + 2 && r_2 >= 10) {
                printw("%d", r_2 % 10);
                continue;
            }

            if (i == 1 && j == X/2 + 2 && r_2 >= 10) {
                printw("%d", r_2);
                j = j + 1;
                continue;
            }

            // заполнение самого поля
            printw("%c", space);
        }
        printw("\n");
    }
}
