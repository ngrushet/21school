#include <stdio.h>
#define H 25
#define W 80
// символ живой клетки
#define alive_symbol '*'
// символ мертвой клетки
#define die_symbol ' '

// отрисовка
void print_field(char field[H][W]);

void scan_field_bash(char field[H][W], FILE * in);

// перезапись временного массива в реальный
int temp_to_real(char field[H][W], char temp_field[H][W], char old_field[H][W]);

// смерть или жизнь для клетки
void live_or_die(int x, int y, char field[H][W], char temp_field[H][W]);

// считаем количество живых вокруг
int count_of_live_around(int x, int y, char field[H][W]);

// проверка на существование координаты
int exist(int x, int y);

// заполнение итогового массива
void processing(char field[H][W], char temp_field[H][W]);

//  вывод конца игры
void game_over(int gameOver);

// печать одного и того же символа n раз
void print_symbol(int n, char ch);

// проверка на жизнь клетки
int are_you_alive(int row, int column, char field[H][W]);

int main(int argc, char *argv[]) {
    int error = 0;  // error counter
    if (argc != 2) {
        error++;
    }
// открываем файл 'in.txt' с инпутом
    FILE *in;
    if (!error) {
        if ((in = fopen(argv[1], "r")) == NULL) {
            printf("Cannot open file.\n");
            error++;
        }
    }

    if (!error) {
        int gameOver = 0;
        // массив поля X Y
        // каждый элемент заполнен либо " " (мертвая) либо "*" (живая)
        char field[H][W];

        // временный массив для заполнения
        char temp_field[H][W];

        // массив для хранения предыдущего поколения
        char old_field[H][W];

        scan_field_bash(field, in);
        print_field(field);
        fclose(in);
        // processing
        char key_print = ' ';

        while (key_print != 'q') {
            key_print = getchar();
            if (key_print == ' ') {
                processing(field, temp_field);
                gameOver = temp_to_real(field, temp_field, old_field);
                // ОТРИСОВКА
                print_field(field);
            }
            if (gameOver != 0) {
                game_over(gameOver);
                key_print = 'q';
            }
        }
    }
    return 0;
}

void print_symbol(int n, char ch) {
    for (int i = 0; i < n; i++) {
        printf("%c", ch);
    }
}

void game_over(int gameOver) {
    char* reason = "";
    print_symbol(H, '\n');
    print_symbol(H / 2, '\n');
    print_symbol(W / 2 - 1 - 4, ' ');
    printf("GAME OVER\n\n");
    print_symbol(W / 2 - 1 - 4, ' ');
    if (gameOver == 1)
        reason = "Now changes";
    else if (gameOver == 2)
        reason = "Everyone died";
    else if (gameOver == 3)
        reason = "Life is cyclical";
    printf("%s", reason);
    print_symbol(H / 2, '\n');
}

void processing(char field[H][W], char temp_field[H][W]) {
    // готовим следующее поколение к релизу
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            live_or_die(i, j, field, temp_field);
        }
    }
}

void scan_field_bash(char field[H][W], FILE * in) {
    char buff = ' ';
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W + 1; j++) {
            fscanf(in, "%c", &buff);
            if (buff != '\n') {
                field[i][j] = buff;
            }
        }
    }
}

void print_field(char field[H][W]) {
    printf("\033c");  // стираем всё поле
    print_symbol(W + 2, '-');
    printf("\n");
    for (int i = 0; i < H; i++) {
        printf("|");
        for (int j = 0; j < W; j++) {
            printf("%c", field[i][j]);
        }
        printf("|");
        printf("\n");
    }
    print_symbol(W + 2, '-');
    printf("\n");
}

// перезапись временного массива в реальный
int temp_to_real(char field[H][W], char temp_field[H][W], char old_field[H][W]) {
    int compare = 1, all_die = 1, cycle = 1, res = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (field[i][j] != temp_field[i][j])
                compare = 0;
            if (temp_field[i][j] == alive_symbol)
                all_die = 0;
            if (old_field[i][j] != temp_field[i][j])
                cycle = 0;
            old_field[i][j] = field[i][j];
            field[i][j] = temp_field[i][j];
        }
    }
    if (compare) {
        res = 1;
    } else if (all_die) {
        res = 2;
    } else if (cycle) {
        res = 3;
    }
    return res;
}

// смерть или жизнь для клетки
void live_or_die(int x, int y, char field[H][W], char temp_field[H][W]) {
    int alive_count = count_of_live_around(x, y, field);
    if (field[x][y] == alive_symbol) {
        if (2 == alive_count || alive_count == 3) {
            temp_field[x][y] = alive_symbol;
        } else {
            temp_field[x][y] = die_symbol;
        }
    }

    if (field[x][y] == die_symbol) {
        if (alive_count == 3) {
            temp_field[x][y] = alive_symbol;
        } else {
            temp_field[x][y] = die_symbol;
        }
    }
}

// считаем количество живых вокруг
int count_of_live_around(int x, int y, char field[H][W]) {
    // считаем количество живых вокруг
    int alive = 0;
    int temp_x, temp_y;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_x = x - 1 + i;
                temp_y = y - 1 + j;
                if (!((x == temp_x) && (y == temp_y)) && (are_you_alive(temp_x, temp_y, field))) {
                    alive++;
                }
            }
        }
    return alive;
}

// проверка на существование координаты
int are_you_alive(int row, int column, char field[H][W]) {
    int res = 0;
    // в поле
    if ((row >= 0) && (column >= 0) && (row < H) && (column < W) && (field[row][column] == alive_symbol)) {
        res = 1;
        // левый край и в поле
    } else if (column < 0 && row >= 0 && row < H) {
        if (field[row][W-1] == alive_symbol) {
            res = 1;
        }
        // правый край и в поле
    } else if (column >= W && row >= 0 && row < H) {
        if (field[row][0] == alive_symbol) {
            res = 1;
        }
        // левый край и выше поля
    } else if (column < 0 && row < 0) {
        if (field[H-1][W-1] == alive_symbol) {
            res = 1;
        }
        // левый край и ниже поля *
    } else if (column < 0 && row >= H) {
        if (field[0][W-1] == alive_symbol) {
            res = 1;
        }
        // правый край и выше поля
    } else if (column >= W && row < 0) {
        if (field[H-1][0] == alive_symbol) {
            res = 1;
        }
        // правый край и ниже поля
    } else if (column >= W && row >= H) {
        if (field[0][0] == alive_symbol) {
            res = 1;
        }
        // выше поля
    } else if (column >= 0 && row < 0 && column < W) {
        if (field[H - 1][column] == alive_symbol) {
            res = 1;
        }
        // ниже поля
    } else if (column >= 0 && row >= H && column < W) {
        if (field[0][column] == alive_symbol) {
            res = 1;
        }
    }
    return res;
}
