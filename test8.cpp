#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Champion {
    char position[50];
    char name[50];
    int hp;
    int attack;
    int defense;
    struct Champion* next;
    struct Champion* prev;
} Champion;

// 단일 연결 리스트
typedef struct {
    Champion* head;
    int count;
} SingleLinkedList;

// 이중 연결 리스트
typedef struct {
    Champion* head;
    Champion* tail;
    int count;
} DoubleLinkedList;

// 파일에서 데이터를 읽어와 단일 연결 리스트에 저장하는 함수
void loadChampions_SL(SingleLinkedList* list) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    Champion temp;
    while (fscanf(file, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.attack, &temp.defense) != EOF) {
        Champion* newChampion = (Champion*)malloc(sizeof(Champion));
        *newChampion = temp;
        newChampion->next = list->head;
        list->head = newChampion;
        list->count++;
    }

    fclose(file);
}

// 파일에서 데이터를 읽어와 이중 연결 리스트에 저장하는 함수
void loadChampions_DL(DoubleLinkedList* list) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    Champion temp;
    while (fscanf(file, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.attack, &temp.defense) != EOF) {
        Champion* newChampion = (Champion*)malloc(sizeof(Champion));
        *newChampion = temp;
        newChampion->next = list->head;
        newChampion->prev = NULL;
        if (list->head != NULL) {
            list->head->prev = newChampion;
        }
        list->head = newChampion;
        if (list->tail == NULL) {
            list->tail = newChampion;
        }
        list->count++;
    }

    fclose(file);
}

// 단일 연결 리스트의 모든 요소를 출력하는 함수
void printAll_SL(SingleLinkedList* list) {
    Champion* cur = list->head;
    while (cur != NULL) {
        //printf("%s %s %d %d %d\n", cur->position, cur->name, cur->hp, cur->attack, cur->defense);
        cur = cur->next;
    }
}

// 이중 연결 리스트의 모든 요소를 출력하는 함수
void printAll_DL(DoubleLinkedList* list) {
    Champion* cur = list->head;
    while (cur != NULL) {
        //printf("%s %s %d %d %d\n", cur->position, cur->name, cur->hp, cur->attack, cur->defense);
        cur = cur->next;
    }
}

// 병합 정렬을 위한 병합 함수
Champion* merge(Champion* first, Champion* second) {
    // 임시 더미 노드
    Champion dummy;
    Champion* tail = &dummy;
    dummy.next = NULL;

    while (first != NULL && second != NULL) {
        if (strcmp(first->name, second->name) <= 0) {
            tail->next = first;
            first = first->next;
        }
        else {
            tail->next = second;
            second = second->next;
        }
        tail = tail->next;
    }

    if (first != NULL) tail->next = first;
    else tail->next = second;

    return dummy.next;
}

// 병합 정렬 함수
Champion* mergeSort(Champion* head) {
    if (head == NULL || head->next == NULL) return head;

    Champion* slow = head;
    Champion* fast = head->next;

    // 리스트를 반으로 나눔
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Champion* mid = slow->next;
    slow->next = NULL;

    return merge(mergeSort(head), mergeSort(mid));
}

// 병합 정렬을 사용하여 이름으로 단일 연결 리스트를 정렬하는 함수
void sortByName_SL(SingleLinkedList* list) {
    list->head = mergeSort(list->head);
}

// 병합 정렬을 사용하여 이름으로 이중 연결 리스트를 정렬하는 함수
void sortByName_DL(DoubleLinkedList* list) {
    list->head = mergeSort(list->head);
    Champion* cur = list->head;
    while (cur->next != NULL) {
        cur->next->prev = cur;
        cur = cur->next;
    }
    list->tail = cur;
}

// 최대 체력을 가진 챔피언을 찾는 함수 (단일 연결 리스트)
Champion* findMaxHP_SL(SingleLinkedList* list) {
    Champion* maxHPChampion = NULL;
    int maxHP = 0;

    Champion* cur = list->head;
    while (cur != NULL) {
        if (cur->hp > maxHP) {
            maxHP = cur->hp;
            maxHPChampion = cur;
        }
        cur = cur->next;
    }

    return maxHPChampion;
}

// 최대 체력을 가진 챔피언을 찾는 함수 (이중 연결 리스트)
Champion* findMaxHP_DL(DoubleLinkedList* list) {
    Champion* maxHPChampion = NULL;
    int maxHP = 0;

    Champion* cur = list->head;
    while (cur != NULL) {
        if (cur->hp > maxHP) {
            maxHP = cur->hp;
            maxHPChampion = cur;
        }
        cur = cur->next;
    }

    return maxHPChampion;
}

int main() {
    SingleLinkedList singleList = { NULL, 0 };
    DoubleLinkedList doubleList = { NULL, NULL, 0 };

    clock_t start, end;
    double cpu_time_used;

    loadChampions_SL(&singleList);
    loadChampions_DL(&doubleList);

    start = clock();
    printAll_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("단일 연결 리스트의 출력 시간: %f 초\n", cpu_time_used);

    start = clock();
    sortByName_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("단일 연결 리스트 정렬 시간: %f 초\n", cpu_time_used);

    start = clock();
    Champion* maxHPChampion_SL = findMaxHP_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("단일 연결 리스트에서 최대 체력 챔피언 찾는 시간: %f 초\n", cpu_time_used);

    start = clock();
    printAll_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("이중 연결 리스트의 출력 시간: %f 초\n", cpu_time_used);

    start = clock();
    sortByName_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("이중 연결 리스트 정렬 시간: %f 초\n", cpu_time_used);

    start = clock();
    Champion* maxHPChampion_DL = findMaxHP_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("이중 연결 리스트에서 최대 체력 챔피언 찾는 시간: %f 초\n", cpu_time_used);

    return 0;
}
