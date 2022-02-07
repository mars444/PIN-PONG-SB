#include <stdio.h>

void rackets(char r[25] [80], int racket1, int racket2);
void draw_cort(char r[25] [80], int score1, int score2);

int main() {
    int racket1 = 13;
    int racket2 = 13;
    int score1 = 18, score2 = 18;
    char player1_input, player2_input;   // вводимый символ
    char o = '*';   // шарик
    int x = 13, y = 41;   // координаты шарика
    int dx = -1, dy = -1;   // изменение координат шарика (скорость)
    while (1 == 1) {
        player1_input = getchar();
        player2_input = getchar();   //        scanf("%c", &f);
        char r[25] [80];
        // Заполняем поле
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 80; j++) {
                if (j == 41)
                    r[i][j] = 'I';
                else if (i == 0 || i == 24)
                    r[i][j] = '-';
                else if (j == 79 || j == 0)
                    r[i][j] = '=';
                else
                    r[i][j] = ' ';
            }
        }
        // обработка движения ракетки
        if (player1_input == 'z')
            racket1++;
        else if (player1_input == 'a')
            racket1--;
        else if (player2_input == 'm')
            racket2++;
        else if (player2_input == 'k')
            racket2--;
        rackets(r, racket1, racket2);
        if (r[x][y - 1] == '-')   // столкновение с бортиками
        dx *= -1;
        if (r[x][y - 1] == '|' || r[x][y + 1] == '|')   // todo: Исправить столкновени с ракеткой
        dy *= -1;
        r[x += dx][y += dy] = o;    // отрисовка шарика
        if (r[x][y - 1] == '=') {
            score2++;
            x = 13;
            y = 41;
        } else if (r[x][y + 1] == '=') {
            score1++;
            x = 13;
            y = 41;
        }
        // отрисовка результа
        draw_cort(r, score1, score2);
        if (score1 == 21) {
            printf("Player 1 Win! ");
            break;
        }
        if (score2 == 21) {
            printf("Player 2 Win! ");
            break;
        }
        //        scanf("%c", &f);
    }
}
void rackets(char r[25] [80], int racket1, int racket2) {
    r[racket2 - 1][77] = '|';
    r[racket2 + 1][77] = '|';
    r[racket2][77] = '|';
    r[racket1][2] = '|';
    r[racket1 - 1][2] = '|';
    r[racket1 + 1][2] = '|';
}
void draw_cort(char r[25] [80], int score1, int score2) {
printf("%20d %40d\n", score1, score2);
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", r[i][j]);
        }
        printf("\n");
    }
}






