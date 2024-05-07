#include <stdio.h>
#include <Windows.h>

char board[19][19] = { };
int turn = 0;
int bstone = 0; //검은 돌 카운트
int wstone = 0; //흰 돌 카운트

struct Point {
    int x{ -1 };
    int y{ -1 };
    char stone;
};

struct Node {
    struct Point data;
    struct Node* next;
};

struct Node* top = NULL;
struct Node* redoStack = NULL;

void Push(struct Node** stack, Point p) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = p;
    new_node->next = *stack;
    *stack = new_node;
}

Point Pop(struct Node** stack) {
    if (*stack == NULL) {
        printf("Stack Underflow\n");
        exit(1);
    }
    else {
        struct Node* temp = *stack;
        Point p = temp->data;
        *stack = (*stack)->next;
        free(temp);
        return p;
    }
}

void PrintBoard() {

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            board[j][i] = '+';
            printf("%c ", board[j][i]);
        }
        printf("\n");
    }
}

void ChangeBoard() {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            auto& ch = board[j][i];
            printf("%c ", ch);
            if ('@' == ch) { ch = 'O'; }
            if ('#' == ch) { ch = 'X'; }
        }
        printf("\n");
    }
}

void PutStone() {
    int i, j;
    printf("좌표 값을 입력해주세요: ");
    scanf("%d %d", &i, &j);
    if (turn % 2 == 0) {
        if (j > 18 || i > 18 || j < 0 || i < 0) {
            printf("범위를 벗어났습니다.\n");
            printf("돌을 다시 놓아주세요.\n");
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
            turn = 0;
        }
        else if (board[j][i] == '+') {
            struct Point p;
            p.x = j;
            p.y = i;
            p.stone = (turn % 2 == 0) ? 'O' : 'X';
            Push(&top, p);

            board[j][i] = 'O';
            ++turn;
            ++bstone;
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
        }
        else {
            printf("이미 돌이 존재합니다.");
            printf("돌을 다시 놓아주세요.\n");
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
            turn = 0;
        }
    }
    else if (turn % 2 == 1) {
        if (j > 18 || i > 18 || j < 0 || i < 0) {
            printf("범위를 벗어났습니다.\n");
            printf("돌을 다시 놓아주세요.\n");
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
            turn = 1;
        }
        else if (board[j][i] == '+') {
            struct Point p;
            p.x = j;
            p.y = i;
            p.stone = (turn % 2 == 0) ? 'O' : 'X';
            Push(&top, p);

            board[j][i] = 'X';
            ++turn;
            ++wstone;
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
        }
        else {
            printf("이미 돌이 존재합니다.");
            printf("돌을 다시 놓아주세요.\n");
            printf("검은 돌의 수 : %d, 흰 돌의 수 : %d\n", bstone, wstone);
            turn = 1;
        }
    }
}

void ROW_COL_Stone() {
    int row_wstone[19] = { 0 }; //행 흰 돌
    int row_bstone[19] = { 0 }; //행 검은 돌
    int col_wstone[19] = { 0 }; //열 흰 돌
    int col_bstone[19] = { 0 }; //열 검은 돌
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (board[j][i] == 'O') {
                ++row_bstone[j];
                ++col_bstone[i];
            }
        }
    }
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (board[j][i] == 'X') {
                ++row_wstone[j];
                ++col_wstone[i];
            }
        }
    }
    for (int i = 0; i < 19; ++i) {
        printf("%d번째 행 검은 돌의 수: %d\n", i + 1, row_bstone[i]);
        printf("%d번째 열 검은 돌의 수: %d\n", i + 1, col_bstone[i]);
        printf("%d번째 행 흰 돌의 수: %d\n", i + 1, row_wstone[i]);
        printf("%d번째 열 흰 돌의 수: %d\n", i + 1, col_wstone[i]);

    }
}

void Continuous_Stone(int x_start, int x_dir, int y_start, int y_dir) {
    int cnt{};
    char prev{};
    char ch{};
    int max_count{};
    char max_color{};
    int i{};

    while (0 <= x_start and x_start <= 18 and
        0 <= y_start and y_start <= 18) {

        ch = board[x_start][y_start];

        if (cnt == 0) {
            if (ch != '+') {
                cnt = 1;
                prev = ch;
            }
        }
        else if (ch == '+') {
            if (max_count < cnt) {
                max_count = cnt;
                max_color = prev;
            }
            cnt = 0;
        }
        else if (prev != ch) {
            if (max_count < cnt) {
                max_count = cnt;
                max_color = prev;
            }
            cnt = 1;
            prev = ch;
        }
        else {
            ++cnt;
        }
        x_start += x_dir;
        y_start += y_dir;
        i++;
    }
    if (max_count < cnt) {
        max_count = cnt;
        max_color = prev;
    }

    if (max_color == 'O' || max_color == '@') {
        max_color = 'B';
    }
    if (max_color == 'X' || max_color == '#') {
        max_color = 'W';
    }

    printf("최대 수: %d, 색: %c\n", max_count, max_color);
}

void Row_Continuous_Stone(int x_start, int x_dir, int y_start, int y_dir) {
    int cnt{};
    char prev{};
    char ch{};
    int max_count{};
    char max_color{};
    int i{};
    Point saved;
    Point result;

    while (0 <= x_start and x_start <= 18 and
        0 <= y_start and y_start <= 18) {

        ch = board[x_start][y_start];

        if (cnt == 0) {
            if (ch != '+') {
                cnt = 1;
                prev = ch;

                saved.x = x_start;
                saved.y = y_start;
            }
        }
        else if (ch == '+') {
            if (max_count < cnt) {
                max_count = cnt;
                max_color = prev;

                result = saved;
            }
            cnt = 0;
        }
        else if (prev != ch) {
            if (max_count < cnt) {
                max_count = cnt;
                max_color = prev;

                result = saved;
            }
            cnt = 1;
            prev = ch;

            saved.x = x_start;
            saved.y = y_start;
        }
        else {
            ++cnt;
        }
        x_start += x_dir;
        y_start += y_dir;
        i++;
    }
    if (max_count < cnt) {
        max_count = cnt;
        max_color = prev;

        result = saved;
    }

    for (int i = 0; i < max_count; ++i) {
        auto& ch = board[result.x][result.y];
        if (max_color == 'O') {
            ch = '@';
        }
        else {
            ch = '#';
        }
        result.x += x_dir;
        result.y += y_dir;
    }
}

void SaveBoard() {
    FILE* fp = fopen("omok_save.txt", "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            fprintf(fp, "%c ", board[j][i]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("게임이 저장되었습니다.\n");
}

void LoadBoard() {
    FILE* fp = fopen("omok_save.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            fscanf(fp, " %c", &board[j][i]);
        }
    }

    fclose(fp);
    printf("게임이 로드되었습니다.\n");
}

void Undo() {
    if (top == NULL) {
        printf("더 이상 무르기를 할 수 없습니다.\n");
        return;
    }

    struct Point p = Pop(&top);
    Push(&redoStack, p);
    board[p.x][p.y] = '+';

    printf("무르기가 완료되었습니다.\n");
}

void Redo() {
    if (redoStack == NULL) {
        printf("더 이상 무르기를 취소할 수 없습니다.\n");
        return;
    }

    struct Point p = Pop(&redoStack);
    Push(&top, p);
    board[p.x][p.y] = p.stone;

    printf("무르기 취소가 완료되었습니다.\n");
}

int main() {
    system("cls");


    PrintBoard();
    while (1) {
        int command;
        printf("명령을 입력하세요 (1: 돌 놓기, 2: 저장, 3: 불러오기, 4: 무르기, 5: 무르기 취소): ");
        scanf("%d", &command);

        switch (command) {
        case 1:
            PutStone();
            break;
        case 2:
            SaveBoard();
            break;
        case 3:
            LoadBoard();
            break;
        case 4:
            Undo();
            break;
        case 5:
            Redo();
            break;
        default:
            printf("잘못된 명령입니다.\n");
            break;
        }

        ROW_COL_Stone();
        // 가로
        for (int i = 0; i < 19; ++i) {
            Row_Continuous_Stone(0, 1, i, 0);

        }

        // 세로
        for (int i = 0; i < 19; ++i) {
            printf("%d열 ", i + 1);
            Continuous_Stone(i, 0, 0, 1);
        }

        // 대각선
        for (int i = 18; i >= 0; --i) {
            printf("우하향 대각선 ");
            Continuous_Stone(i, 1, 0, 1);
        }
        for (int i = 1; i < 19; ++i) {
            printf("우하향 대각선 ");
            Continuous_Stone(0, 1, i, 1);
        }
        for (int i = 0; i < 19; ++i) {
            printf("좌하향 대각선 ");
            Continuous_Stone(i, -1, 0, 1);
        }
        for (int i = 0; i < 19; ++i) {
            printf("좌하향 대각선 ");
            Continuous_Stone(18, -1, i, 1);
        }

        ChangeBoard();
        printf("\n\n\n");
    }

    return 0;
}