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

// ���� ���� ����Ʈ
typedef struct {
    Champion* head;
    int count;
} SingleLinkedList;

// ���� ���� ����Ʈ
typedef struct {
    Champion* head;
    Champion* tail;
    int count;
} DoubleLinkedList;

// ���Ͽ��� �����͸� �о�� ���� ���� ����Ʈ�� �����ϴ� �Լ�
void loadChampions_SL(SingleLinkedList* list) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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

// ���Ͽ��� �����͸� �о�� ���� ���� ����Ʈ�� �����ϴ� �Լ�
void loadChampions_DL(DoubleLinkedList* list) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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

// ���� ���� ����Ʈ�� ��� ��Ҹ� ����ϴ� �Լ�
void printAll_SL(SingleLinkedList* list) {
    Champion* cur = list->head;
    while (cur != NULL) {
        //printf("%s %s %d %d %d\n", cur->position, cur->name, cur->hp, cur->attack, cur->defense);
        cur = cur->next;
    }
}

// ���� ���� ����Ʈ�� ��� ��Ҹ� ����ϴ� �Լ�
void printAll_DL(DoubleLinkedList* list) {
    Champion* cur = list->head;
    while (cur != NULL) {
        //printf("%s %s %d %d %d\n", cur->position, cur->name, cur->hp, cur->attack, cur->defense);
        cur = cur->next;
    }
}

// ���� ������ ���� ���� �Լ�
Champion* merge(Champion* first, Champion* second) {
    // �ӽ� ���� ���
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

// ���� ���� �Լ�
Champion* mergeSort(Champion* head) {
    if (head == NULL || head->next == NULL) return head;

    Champion* slow = head;
    Champion* fast = head->next;

    // ����Ʈ�� ������ ����
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Champion* mid = slow->next;
    slow->next = NULL;

    return merge(mergeSort(head), mergeSort(mid));
}

// ���� ������ ����Ͽ� �̸����� ���� ���� ����Ʈ�� �����ϴ� �Լ�
void sortByName_SL(SingleLinkedList* list) {
    list->head = mergeSort(list->head);
}

// ���� ������ ����Ͽ� �̸����� ���� ���� ����Ʈ�� �����ϴ� �Լ�
void sortByName_DL(DoubleLinkedList* list) {
    list->head = mergeSort(list->head);
    Champion* cur = list->head;
    while (cur->next != NULL) {
        cur->next->prev = cur;
        cur = cur->next;
    }
    list->tail = cur;
}

// �ִ� ü���� ���� è�Ǿ��� ã�� �Լ� (���� ���� ����Ʈ)
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

// �ִ� ü���� ���� è�Ǿ��� ã�� �Լ� (���� ���� ����Ʈ)
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
    printf("���� ���� ����Ʈ�� ��� �ð�: %f ��\n", cpu_time_used);

    start = clock();
    sortByName_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ ���� �ð�: %f ��\n", cpu_time_used);

    start = clock();
    Champion* maxHPChampion_SL = findMaxHP_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ���� �ִ� ü�� è�Ǿ� ã�� �ð�: %f ��\n", cpu_time_used);

    start = clock();
    printAll_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ�� ��� �ð�: %f ��\n", cpu_time_used);

    start = clock();
    sortByName_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ ���� �ð�: %f ��\n", cpu_time_used);

    start = clock();
    Champion* maxHPChampion_DL = findMaxHP_DL(&doubleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ���� �ִ� ü�� è�Ǿ� ã�� �ð�: %f ��\n", cpu_time_used);

    return 0;
}
