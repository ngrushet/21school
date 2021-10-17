#include <stdio.h>
#define D 80
#define L 25
#define S 21

int quick_game = 1;

void print_field(int * racket, int * ball, int * score);
void game(int * ball, int * vect, int * racket, int * score);
void move(int * ball, int * vect, int * racket, int * score);
void move_racket(int * racket, char * inpt);
void change_direct(int * ball, int * racket, int * vect);
void ball_start(int * ball, int * racket);
void finish_screen(int * score);

int main() {
    int ball[2] = {D / 2, L / 2};
    int racket[2] = {L / 2, L / 2};
    int vect[2] = {1, 1};
    int score[2] = {0, 0};

    while (score[0] < S && score[1] < S && quick_game) {
        game(ball, vect, racket, score);
        if (quick_game)
            ball_start(ball, racket);
    }
    print_field(racket, ball, score);

    if (quick_game)
        finish_screen(score);
    else
        printf("Good luck!");

    return 0;
}

void print_field(int * racket, int * ball, int * score) {
    printf("\033c");

    printf("%39d  ", score[0]);

    printf("%d\n", score[1]);


    for (int i = 0; i < L; i++) {
        for (int j = 0; j < D; j++) {
            if (j == 0 && i >= racket[0] - 1 && i <= racket[0] + 1)
                printf("|");
            else if (j == D - 1 && i >= racket[1] - 1 && i <= racket[1] + 1)
                printf("|");
            else if (j >= D/2 - 1 && j <= D/2 &&  (j != ball[0] || i != ball[1]))
                printf("|");
            else if (j == ball[0] && i == ball[1])
                printf("o");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void game(int * ball, int * vect, int * racket, int * score) {
    int ball_in_game = 1;

    while (ball_in_game && quick_game) {
        move(ball, vect, racket, score);

        if (ball[0] == 0 || ball[0] == D - 1) {  // если мячик улетел в ворота
            ball_in_game = 0;  // останавливаем игру

            switch (ball[0]) {  //  и меняем счёт выигравшего
                case 0: {
                    score[1]++;
                    break;
                }
                case D - 1: {
                    score[0]++;
                }
            }
        }
    }
}

void move(int * ball, int * vect, int * racket, int * score) {
    char inpt[10];
    int eo = 0;

    while (!eo && quick_game) {
        print_field(racket, ball, score);
        fgets(inpt, 10, stdin);

        if (inpt[0] == 'A' || inpt[0] == 'Z' || inpt[0] == ' ' || inpt[0] == 'K' || inpt[0] == 'M')
                if (inpt[1] == '\n')
                    eo = 1;

        if (inpt[0] == 'a' || inpt[0] == 'z' || inpt[0] == 'k' || inpt[0] == 'm')
                if (inpt[1] == '\n')
                    eo = 1;

        if (inpt[0] == 'Q' || inpt[0] == 'q')
            quick_game = 0;

        if (eo) {
            move_racket(racket, inpt);
            change_direct(ball, racket, vect);
            ball[0] += vect[0];
            ball[1] += vect[1];
        }
    }
}

void move_racket(int * racket, char * inpt) {
    switch (inpt[0]) {
        case 'A':
        case 'a':
            if (racket[0] > 1)
                racket[0]--;
            break;
        case 'Z':
        case 'z':
            if (racket[0] < L - 2)
                racket[0]++;
            break;
        case 'K':
        case 'k':
            if (racket[1] > 1)
                racket[1]--;
            break;
        case 'M':
        case 'm':
            if (racket[1] < L - 2)
                racket[1]++;
    }
}

void change_direct(int * ball, int * racket, int * vect) {
    if (ball[1] == 0 || ball[1] == L - 1)
        vect[1] *= -1;

    if (ball[0] == 1 && racket[0] - 1 <= ball[1] && racket[0] + 1 >= ball[1])
        vect[0] *= -1;

    if (ball[0] == D - 2 && racket[1] - 1 <= ball[1] && racket[1] + 1 >= ball[1])
        vect[0] *= -1;
}

void ball_start(int * ball, int * racket) {
    if (ball[0] == 0) {
        ball[0]++;
        ball[1] = racket[0];
    }
    if (ball[0] == D - 1) {
        ball[0]--;
        ball[1] = racket[1];
    }
}

void finish_screen(int * score) {
    printf("\033c");
    if (score[0] == S) {
        printf("       @@@@@@@  @@         @@@      @@@   @@@ ,@@@@@@  @@@@@@@        @@@       \n"
               "       @@   @@@ @@        @@@@@      .@@@@@   ,@@      @@   @@@        @        \n"
               "       @@@@@@@  @@       @@@  @@&      @@@    ,@@@@@@  @@@@@@@         @        \n"
               "       @@       @@      @@@@@@@@@@     @@@    ,@@      @@   @@         @       \n"
               "       @@       @@@@@@ @@@      @@@    @@@    ,@@@@@@  @@    /@@      @@@       \n"
               "                                                                                \n"
               "             @@   @@    @@ @@@ @@@@  @@  @@@   @@ @@@@@@ @@@@@@                 \n"
               "             @@  @@@@  @@  @@  @@ @@ @@  @@ @@ @@ @@@@@  @@  @@                 \n"
               "              @@@@  @@@@   @@  @@  @@@@  @@  @@@@ @@     @@ @@                  \n"
               "               @@    @@@   @@@ @@    @@  @@    @@ @@@@@@ @@   @@  @             \n"
               "                                                                              @@  \n"
               "                                                                              @@\n"
               " @@@@@@@  .@@@@    @@@@@ @@   @@ @@   @@   @@@@   @@@@  @@@@@@@  @@@@  @@@@@  @@\n"
               " @@   @@ @@   @@  @@  @@  @@ @@  @@@@@@@  @@ @@   @@@      @    @@    @@@ @@   \n"
               " @@   @@  @@#@@@ @@@  @@   @@@        @@   @@@@@  @@@@     @    @@@@@  @@ @@  @@\n"
               "                           @@\n");
    }
    if (score[1] == S) {
        printf("       @@@@@@@  @@         @@@      @@@   @@@ ,@@@@@@  @@@@@@@        @@@  @@@  \n"
               "       @@   @@@ @@        @@@@@      .@@@@@   ,@@      @@   @@@        @    @   \n"
               "       @@@@@@@  @@       @@@  @@&      @@@    ,@@@@@@  @@@@@@@         @    @   \n"
               "       @@       @@      @@@@@@@@@@     @@@    ,@@      @@   @@         @    @   \n"
               "       @@       @@@@@@ @@@      @@@    @@@    ,@@@@@@  @@    /@@      @@@  @@@  \n"
               "                                                                                \n"
               "             @@   @@    @@ @@@ @@@@  @@  @@@   @@ @@@@@@ @@@@@@                 \n"
               "             @@  @@@@  @@  @@  @@ @@ @@  @@ @@ @@ @@@@@  @@  @@                 \n"
               "              @@@@  @@@@   @@  @@  @@@@  @@  @@@@ @@     @@ @@                  \n"
               "               @@    @@@   @@@ @@    @@  @@    @@ @@@@@@ @@   @@  @             \n"
               "                                                                              @@\n"
               "                                                                              @@\n"
               " @@@@@@@  .@@@@    @@@@@ @@   @@ @@   @@   @@@@   @@@@  @@@@@@@  @@@@  @@@@@  @@\n"
               " @@   @@ @@   @@  @@  @@  @@ @@  @@@@@@@  @@ @@   @@@      @    @@    @@@ @@    \n"
               " @@   @@  @@#@@@ @@@  @@   @@@        @@   @@@@@  @@@@     @    @@@@@  @@ @@  @@\n"
               "                           @@\n");
    }
}
