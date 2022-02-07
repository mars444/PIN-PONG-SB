#include <stdio.h>

#define MAX_X 80
#define MAX_Y 25
#define MIN_X 1
#define MIN_Y 1
#define RACKET1 1
#define RACKET2 80
#define SCORE 1

int ball_x = 40;
int ball_y = 12;
int speed_x = 1;
int speed_y = 1;

// I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

void display_board(int racket_player1, int racket_player2);
int change_position(char button, int racket_position);
void move_ball(int racket_position);
void touch_up_down();
void touch_racket(int racket_position);
int check_goal();
void set_default();
void print_winner(int score1, int score2);
void print_score(int score_player1, int score_player2);

int main() {
    int racket_player1 = 11;
    int racket_player2 = 11;
    int score_player1 = 0;
    int score_player2 = 0;

    print_score(score_player1, score_player2);
    display_board(racket_player1, racket_player2);
    while (1) {
        char button = getchar();
        if (button == 'A' || button == 'Z' || button == 'K' || button == 'M' || button == ' ') {
            if (button == 'A' || button == 'Z') {
                racket_player1 = change_position(button, racket_player1);
                move_ball(racket_player1);
            } else {
                racket_player2 = change_position(button, racket_player2);
                move_ball(racket_player2);
            }
            print_score(score_player1, score_player2);
            display_board(racket_player1, racket_player2);
            if (check_goal() == 2) {
                score_player2 += 1;
                set_default();
                racket_player1 = 11;
                racket_player2 = 11;
            } else if (check_goal() == 1) {
                score_player1 += 1;
                set_default();
                racket_player1 = 11;
                racket_player2 = 11;
            }
            if (score_player1 == SCORE || score_player2 == SCORE) {
                print_winner(score_player1, score_player2);
                break;
            }
        }
    }
}




void display_board(int racket_player1, int racket_player2) {
    printf("--------------------------------------------------------------------------------\n");
    for (int y = MIN_Y; y < MAX_Y; y++) {
         for (int x = MIN_X; x <= MAX_X; x++) {
             if (x == MIN_X && (y == racket_player1 || y == racket_player1 + 1 || y == racket_player1 + 2)) {
                 if (y == racket_player1) {
                     printf("]");
                 } else if (y == racket_player1 + 1) {
                     printf("|");
                 } else {
                     printf("]");
                 }
             } else if (x == MAX_X && (y == racket_player2 || y == racket_player2 + 1 \
                                                        || y == racket_player2 + 2)) {
                 if (y == racket_player2) {
                     printf("[\n");
                 } else if (y == racket_player2 + 1) {
                     printf("|\n");
                 } else {
                     printf("[\n");
                 }
             } else if (ball_x == x && ball_y == y) {
                 if (ball_x < MAX_X && ball_x > MIN_X) {
                     printf("O");
                 } else if (ball_x == MAX_X) {
                     printf("O\n");
                 } else if (ball_x == MIN_X) {
                     printf("O");
                 }
             } else if (x == MIN_X || x == MAX_X) {
                 printf(" ");
                 if (x == MAX_X) {
                     printf("\n");
                 }
             } else if (x == MAX_X/2 || x == MAX_X/2+1) {
                 if (y == MAX_Y/2) {
                     if (x == MAX_X/2) {
                         printf("{");
                     } else if (x == MAX_X/2+1) {
                         printf("}");
                     } else {
                         printf(" ");
                     }
                 } else {
                     if (y == MAX_Y/2-1 && x == MAX_X/2) {
                         printf("\\");
                     } else if (y == MAX_Y/2-1 && x == MAX_X/2+1) {
                         printf("/");
                     } else if (y == MAX_Y/2+1 && x == MAX_X/2) {
                         printf("/");
                     } else if (y == MAX_Y/2+1 && x == MAX_X/2+1) {
                         printf("\\");
                     } else {
                         printf("|");
                     }
                 }
             } else {
                 printf(" ");
             }
         }
    }
    printf("--------------------------------------------------------------------------------\n");
}

int change_position(char button, int racket_position) {
    if (button == 'A' || button == 'K') {
        if (racket_position > 1) {
            racket_position = racket_position - 1;
        }
    } else if (button == 'Z' || button == 'M') {
        if (racket_position < 22) {
            racket_position = racket_position + 1;
        }
    }
    return racket_position;
}
// Код движения мяча

void move_ball(int racket_position) {
  touch_racket(racket_position);
  ball_x += speed_x;
  ball_y += speed_y;

  touch_up_down();
  // gool_left_right
  /*
  for (int x = MIN_X; x <= MAX_X; x++) {
    for(int y = MIN_Y; y <= MAX_Y; y++) {
      if (x == ball_x && y == ball_y)
        printf("%c", 'O');
      else printf(" ");
    }printf("\n");
  }*/
}

// Код проверяющий касание потолка или пола
void touch_up_down() {
  if (ball_y == MAX_Y-1)
    speed_y = -speed_y;
  if (ball_y == MIN_Y)
    speed_y = -speed_y;
}

// Код проверяющий касание ракетки
void touch_racket(int racket_position) {
if (ball_x == RACKET1+1 && (ball_y == racket_position || \
                            ball_y == racket_position + 1 || \
                            ball_y == racket_position + 2))
  speed_x = -speed_x;
if (ball_x == RACKET2-1 && (ball_y == racket_position || \
                            ball_y == racket_position + 1 || \
                            ball_y == racket_position + 2))
  speed_x = -speed_x;
}

int check_goal() {
    if (ball_x < 1) {
        return 2;
    } else if (ball_x > 80) {
        return 1;
    } else {
        return 0;
    }
}

void set_default() {
    ball_x = 40;
    ball_y = 12;
    speed_x = -speed_x;
    speed_y = -speed_y;
}

void print_winner(int score1, int score2) {
  if (score1 == SCORE) {
    printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n");
    printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
    printf("ww   *       *       *      *       *       *       *      *      *     *     ww\n");
    printf("ww                *                                                           ww\n");
    printf("ww       *      ***     *        *       *       *       *     *              ww\n");
    printf("ww            ** **    #### #        #   ####  ####         #  ####           ww\n");
    printf("ww           **  **    #  # #       # #  #     #  #            #              ww\n");
    printf("ww               **    #### #      ####  ###   ####         #  ####           ww\n");
    printf("ww               **    #    #     #   #  #     ##           #     #           ww\n");
    printf("ww               **    #    #### #    #  ##### #  #         #  ####           ww\n");
    printf("ww                                                                            ww\n");
    printf("ww                                                                            ww\n");
    printf("ww                                                                            ww\n");
    printf("ww       ##               ##                                                  ww\n");
    printf("ww        ##             ##                                                   ww\n");
    printf("ww        ##            ##      ##     ## ######   #####                      ww\n");
    printf("ww         ##          ##             ###    ##    ####                       ww\n");
    printf("ww         ##    #    ##      ##     ##     ##     ###                        ww\n");
    printf("ww          ##  # #  ##      ##     ##     ##      ##                         ww\n");
    printf("ww          ## #  # ##      ##     ##     ##                                  ww\n");
    printf("ww           ##   ##       ##     ##     ##       ##                          ww\n");
    printf("ww                                                                            ww\n");
    printf("ww                                                                            ww\n");
    printf("ww                                                                            ww\n");
    printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
  } else if (score2 == SCORE) {
    printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n");
    printf("ww                                                                            ww\n");
    printf("www                                                                          www\n");
    printf("ww              ******* #### #        #  #### ####       #  ####              ww\n");
    printf("www             **   ** #  # #       # # #    #  #          #                www\n");
    printf("ww                   ** #### #      #### ###  ####       #  ####              ww\n");
    printf("www             ******* #    #     #   # #    ##         #     #             www\n");
    printf("ww              **      #    #### #    # #### #  #       #  ####              ww\n");
    printf("www             *******                                                      www\n");
    printf("ww                                                                            ww\n");
    printf("www                                                                          www\n");
    printf("ww              ##           ##     ##   ######   #####                       ww\n");
    printf("www              ##         ##          ##   ##   ####                       www\n");
    printf("ww               ##        ##     ##   ##   ##    ###                         ww\n");
    printf("www               ##  #   ##     ##   ##   ##     ##                         www\n");
    printf("ww                ## # # ##     ##   ##   ##                                  ww\n");
    printf("www                ##   ##     ##   ##   ##      ##                          www\n");
    printf("ww                                                                            ww\n");
    printf("www                                                                          www\n");
    printf("ww                                                                            ww\n");
    printf("www                                                                          www\n");
    printf("ww                                                                            ww\n");
    printf("www                                                                          www\n");
    printf("ww                                                                            ww\n");
    printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }
}

void print_score(int score_player1, int score_player2) {
    printf("--------------------------------------------------------------------------------\n");
    printf("|     PLAYER 1           ------------------------------           PLAYER 2     |\n");
    if (score_player1 >= 10 && score_player2 >= 10) {
        printf("|       %d                                                          %d         |\n", \
                                         score_player1, score_player2);
    } else if (score_player1 >= 10 && score_player2 < 10) {
        printf("|       %d                                                           %d         |\n", \
                                         score_player1, score_player2);
    } else if (score_player1 < 10 && score_player2 >= 10) {
        printf("|        %d                                                          %d         |\n", \
                                         score_player1, score_player2);
    } else if (score_player1 < 10 && score_player2 < 10) {
        printf("|        %d                                                           %d         |\n", \
                                         score_player1, score_player2);
    }
}
