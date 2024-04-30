#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int champions_cnt = 22;

struct Champion
{
    char name[15] = { NULL };
    int hp = NULL;
    int mp = NULL;
    int speed = NULL;
    int range = NULL;
    char position[10] = { NULL };
};

struct ChampionNode
{
    Champion data;
    ChampionNode* next{ NULL };
};

Champion champions[50] = { "Jayce", 3466, 8307, 452, 73, "mid",
"Vayne", 3318, 2790, 390, 60, "support",
"Lee Sin", 9864, 6257, 747, 19, "support",
"Teemo", 1915, 1313, 700, 68, "mid",
"Nami", 2968, 2153, 803, 74, "support",
"Jinx", 2583, 3042, 123, 53, "jungle",
"Cassiopeia", 6067, 7330, 683, 24, "top",
"Ahri", 4573, 7079, 177, 79, "top",
"Fiora", 2591, 9329, 337, 81, "jungle",
"Zac", 9864, 7272, 405, 49, "bottom",
"Janna", 4922, 2275, 690, 66, "jungle",
"Ashe", 7421, 5549, 428, 31, "top",
"Twitch", 2980, 7703, 204, 91, "mid",
"Ezreal", 3660, 9835, 274, 44, "mid",
"Sona", 5655, 8442, 252, 26, "bottom",
"Lulu", 3231, 2014, 503, 32, "support",
"Amumu", 6763, 3994, 427, 19, "jungle",
"Master Yi", 5737, 7168, 434, 61, "top",
"Jarvan", 1895, 3070, 323, 80, "mid",
"Shen", 4794, 9220, 783, 42, "mid",
"Fizz", 9864, 1913, 433, 38, "bottom",
"Taric", 6158, 7451, 160, 36, "bottom" };

ChampionNode* Array2LinkedList() {

    if (champions_cnt == 0) {
        return NULL;
    }

    ChampionNode* head = (ChampionNode*)malloc(sizeof(ChampionNode));
    head->data = champions[0];
    head->next = head;



    ChampionNode* current = head;
    for (int i = 1; i < champions_cnt; ++i) {
        ChampionNode* node = (ChampionNode*)malloc(sizeof(ChampionNode));
        node->data = champions[i];
        node->next = head;
        current->next = node;
        current = current->next;
    }

    return head;
}

void Search_SL(ChampionNode* head) {
    char champion_name[15];
    scanf(" %[^\n]", champion_name);
    for (ChampionNode* p = head; p->next != head; p = p->next) {
        Champion& node_data = p->data;
        int name_result = strcmp(champion_name, node_data.name);
        if (name_result == 0) {
            printf("%s %d %d %d %d %s\n", node_data.name, node_data.hp, node_data.mp,
                node_data.speed, node_data.range, node_data.position);
            return;
        }
    }

    printf("없는 챔피언 입니다.\n");
}

void Insert_SL(ChampionNode* head) {
    ChampionNode* new_p = (ChampionNode*)malloc(sizeof(ChampionNode));
    scanf(" %[^\n] %d %d %d %d %s ", new_p->data.name, &new_p->data.hp, &new_p->data.mp,
        &new_p->data.speed, &new_p->data.range, new_p->data.position);

    ChampionNode* current;
    ChampionNode* temp = head;

    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = new_p;
    new_p->next = head;
}

void Delete_SL(ChampionNode** head) {
    auto head_node = *head;
    char champion_name[15];
    scanf(" %[^\n]", champion_name);

    // 찾는 데이터가 헤드일 경우
    if (0 == strcmp(champion_name, head_node->data.name)) {
        ChampionNode* p = head_node;
        while (p->next != head_node) { p = p->next; }
        p->next = head_node->next;
        free(head_node);
        *head = p->next;
        return;
    }

    // 헤드가 아닐 경우
    ChampionNode* prev = head_node;
    for (ChampionNode* p = head_node->next; p->next != head_node->next; p = p->next) {
        Champion& node_data = p->data;
        int name_result = strcmp(champion_name, node_data.name);
        if (name_result == 0) {
            prev->next = p->next;
            delete(p);
            return;
        }
        prev = prev->next;
    }
}

void DeleteAll_SL(ChampionNode** head) {
    auto head_node = *head;
    char champion_position[10];
    scanf("%s", champion_position);

    // 찾는 데이터가 헤드일 경우
    while (0 == strcmp(champion_position, (*head)->data.position)) {
        ChampionNode* p = head_node;
        while (p->next != head_node) { p = p->next; }
        p->next = head_node->next;
        free(head_node);
        *head = p->next;
        head_node = p->next;
    }

    ChampionNode* prev = head_node;
    for (ChampionNode* p = head_node->next; p->next != head_node->next; p = p->next) {
        Champion& node_data = p->data;
        int name_result = strcmp(champion_position, node_data.position);
        if (name_result == 0) {
            prev->next = p->next;
            delete(p);
            p = prev;
        }
        else {
            prev = prev->next;
        }
    }
}

void PrintAll_SL(ChampionNode* head) {
    ChampionNode* p = head;
    while (true) {
        Champion& node_data = p->data;
        printf("%s %d %d %d %d %s\n", node_data.name, node_data.hp, node_data.mp,
            node_data.speed, node_data.range, node_data.position);
        p = p->next;
        if (p == head) {
            break;
        }
    }

}

void FindMaxHp_SL(ChampionNode* head) {
    ChampionNode* p = head;
    int max_hp = champions[0].hp;

    for (p = head; p->next != head; p = p->next) {
        Champion& node_data = p->data;
        if (max_hp < node_data.hp) {
            max_hp = node_data.hp;
        }
    }

    for (p = head; p->next != head; p = p->next) {
        Champion& node_data = p->data;
        if (max_hp == node_data.hp) {
            printf("%s %d %d %d %d %s\n", node_data.name, node_data.hp, node_data.mp,
                node_data.speed, node_data.range, node_data.position);
        }
    }
}

void SortByHp_SL(ChampionNode* head) {
    Champion index;
    ChampionNode* p = head;
    ChampionNode* i, * j;
    for (i = head; i->next != head; i = i->next) {
        for (j = i->next; j != head; j = j->next) {
            if (i->data.hp < j->data.hp) {
                index = i->data;
                i->data = j->data;
                j->data = index;
            }
        }
    }
}

int main() {
    int key;
    ChampionNode* head = Array2LinkedList();
    printf("1:Search\n");
    printf("2:Insert\n");
    printf("3:Delete\n");
    printf("4:DeleteAll\n");
    printf("5:PrintAll\n");
    printf("6:FindMaxHp\n");
    printf("7:SortByHp\n");
    printf("0:종료\n");
    printf("Insert기능 사용 시 이름에 띄어쓰기가 있을 수도 있으므로 이름을 입력한 후 엔터를 치고 다음 값들을 전체적으로 입력해주세요\n");
    while (1) {
        scanf("%d", &key);
        if (key == 1) {
            Search_SL(head);
        }
        else if (key == 2) {
            Insert_SL(head);
        }
        else if (key == 3) {
            Delete_SL(&head);
        }
        else if (key == 4) {
            DeleteAll_SL(&head);
        }
        else if (key == 5) {
            PrintAll_SL(head);
        }
        else if (key == 6) {
            FindMaxHp_SL(head);
        }
        else if (key == 7) {
            SortByHp_SL(head);
        }
        else if (key == 0) {
            return 0;
        }
        else {
            printf("없는 명령어 입니다.\n");
        }
    }

    return 0;
}