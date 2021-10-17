#include <stdio.h>
#define H 25
#define W 80
// символ живой клетки
#define alive_symbol '*'
// символ мертвой клетки
#define die_symbol ' '

//отрисовка
void print_field(char field[H][W]);

void scan_field_bash(char field[H][W], FILE * in);

//перезапись временного массива в реальный
void temp_to_real(char field[H][W], char temp_field[H][W]);

// смерть или жизнь для клетки
void live_or_die(int x, int y, char field[H][W], char temp_field[H][W]);

// считаем количество живых вокруг
int count_of_live_around(int x, int y, char field[H][W]);

// проверка на существование координаты
int exist(int x, int y);

// заполнение итогового массива
void processing(char field[H][W], char temp_field[H][W]);


int main(int argc, char *argv[]) {
//int main(int argc, char *argv[]) {

    int error = 0; // error counter
    
    if (argc != 2) {
        error ++;
    }
    
    // массив поля X Y
    // каждый элемент заполнен либо " " (мертвая) либо "*" (живая)
    char field[H][W] = {' '};

    // временный массив для заполнения
    char temp_field[H][W] = {' '};

    // открываем файл 'in.txt' с инпутом
    FILE *in;
    if (!error) {
        if ((in = fopen(argv[1], "r")) == NULL) {
            printf ("Cannot open file.\n");
            error ++;
        }
    }
    if (!error) {
        
        scan_field_bash(field, in);
        print_field(field);
        // processing
        char key_print = ' ';
        
        while (key_print != 'q') {
        
            key_print = getchar();
            if (key_print == ' ') {
                processing(field, temp_field);
                // ОТРИСОВКА
                print_field(field);
            }
        }
    }
    return 0;
}

void processing(char field[H][W], char temp_field[H][W]) {
    
    // готовим следующее поколение к релизу
    for ( int i = 0; i < H; i++) {
        for ( int j = 0; j < W; j++) {
            live_or_die(i, j, field, temp_field);
        }
    }
    // релизим его
    temp_to_real(field, temp_field);
}

// useless
void scan_field_hand(char field[H][W], FILE * in) {
    while (!feof(in)) {
        int x,y;
        scanf("%d %d", &x, &y);
        field[x][y] = 'x';
    }
}

void scan_field_bash(char field[H][W], FILE * in) {
    char buff=' ';
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W + 1; j++) {
            fscanf(in,"%c", &buff);
            if (buff != '\n') {
                field[i][j] = buff;
            }
        }
    }
}

void print_field(char field[H][W]) {
    printf("\033c");  // стираем всё поле

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
}

//перезапись временного массива в реальный
void temp_to_real(char field[H][W], char temp_field[H][W]) {
    for ( int i = 0; i < H; i++) {
        for ( int j = 0; j < W; j++) {
            field[i][j] = temp_field[i][j];
        }
    }
}

// смерть или жизнь для клетки
void live_or_die(int x, int y, char field[H][W], char temp_field[H][W]) {
    int alive_count = count_of_live_around(x, y, field);
    
    if (field[x][y] == alive_symbol) {
        if ((2 == alive_count || alive_count == 3)){
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
    int temp_x = 0, temp_y = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_x = x - 1 + i;
                temp_y = y - 1 + j;
                if ((exist(temp_x, temp_y))
                    && (field[temp_x][temp_y] == alive_symbol)
                    && !((x == temp_x) && (y == temp_y))) {
                    alive++;
                }
            }
        }
    return alive;
}

// проверка на существование координаты
int exist(int x, int y) {
    int res = 0;
    if ((x >= 0) && (y >= 0) && (x < H) && (y < W))
        res = 1;
    return res;
}
