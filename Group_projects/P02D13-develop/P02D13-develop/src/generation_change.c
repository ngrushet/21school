// символ живой клетки
#define alive_symbol "*"

// символ мертвой клетки
#define die_symbol " "

// размеры поля
#define field_height 25;
#define  field_width 80;

// массив поля X Y
// каждый элемент заполнен либо " " (мертвая) либо "*" (живая)
char field[field_height][field_width] = {" "};

// временный массив для заполнения
char temp_field[field_height][field_width] = {" "};

//перезапись временного массива в реальный
void temp_to_real(int* field, int* temp_field) {
    for (int i = 0; i < field_height; i++) {
        for (int j = 0; j < field_height; j++) {
            field[i][j] = temp_field[i][j];
        }
    }
}

// смерть или жизнь для клетки
void live_or_die(int x, int y, int** field,
                 int** temp_field) {
    int alive_count = count_of_live_around(x, y);
    if ((field[x][y] == alive_symbol)
        && ((alive_count < 2 || alive_count > 3))){
        temp_field[x][y] = die_symbol;
    } else if ((field[x][y] == die_symbol) && (alive_count == 3)) {
        temp_field[x][y] = alive_symbol;
        }
}

// считаем количество живых вокруг
int count_of_live_around(int x, int y, int** field, char alive_symbol) {
        // считаем количество живых вокруг
    int alive = 0;
    int temp_x = 0, temp_y = 0;
        for (int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                temp_x = x - 1 + i;
                temp_y = y - 1 + j;
                if (exist(temp_x, temp_y)
                    && field[temp_x][temp_y] == alive_symbol
                    && (x != temp_x && y != temp_y))
                    alive++;
            }
        }
    return alive;
}

// проверка на существование координаты
int exist(int x, int y, field_width, field_height) {
    int res = 0;
    if (x >= 0) && y >=0 && x < field_width && y < field_height)
        res = 1;
    return res;
}
