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
} Champion;

typedef struct BSTNode {
    Champion data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// 단일 연결 리스트
typedef struct SingleLinkedList {
    Champion* head;
    int count;
} SingleLinkedList;

// 이진 탐색 트리
typedef struct BinaryTree {
    BSTNode* root;
    int count;
} BinaryTree;

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

// 병합 정렬을 위한 병합 함수
Champion* merge(Champion* first, Champion* second) {
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

// 파일에서 데이터를 읽어와 이진 탐색 트리에 저장하는 함수
void loadChampions_BT(BinaryTree* tree) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    Champion temp;
    while (fscanf(file, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.attack, &temp.defense) != EOF) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = temp;
        newNode->left = NULL;
        newNode->right = NULL;

        if (tree->root == NULL) {
            tree->root = newNode;
        }
        else {
            BSTNode* current = tree->root;
            BSTNode* parent = NULL;
            while (current != NULL) {
                parent = current;
                if (strcmp(newNode->data.name, current->data.name) < 0) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (strcmp(newNode->data.name, parent->data.name) < 0) {
                parent->left = newNode;
            }
            else {
                parent->right = newNode;
            }
        }
        tree->count++;
    }

    fclose(file);
}

// 중위 순회 (In-Order Traversal)를 통해 이진 탐색 트리 데이터를 배열에 저장하는 함수
void inOrderTraversalToArray(BSTNode* node, Champion* array, int* index) {
    if (node != NULL) {
        inOrderTraversalToArray(node->left, array, index);
        array[*index] = node->data;
        (*index)++;
        inOrderTraversalToArray(node->right, array, index);
    }
}

// 새로운 이진 탐색 트리를 배열로부터 생성하는 함수
BSTNode* sortedArrayToBST(Champion* array, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = array[mid];
    node->left = sortedArrayToBST(array, start, mid - 1);
    node->right = sortedArrayToBST(array, mid + 1, end);

    return node;
}

// 이진 탐색 트리에서 이름으로 챔피언을 검색하는 함수
BSTNode* searchByName_BT(BSTNode* root, const char* name) {
    if (root == NULL || strcmp(root->data.name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->data.name) < 0) {
        return searchByName_BT(root->left, name);
    }
    else {
        return searchByName_BT(root->right, name);
    }
}

// 이진 탐색 트리에 새로운 챔피언을 삽입하는 함수
BSTNode* insert_BT(BSTNode* root, Champion data) {
    if (root == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (strcmp(data.name, root->data.name) < 0) {
        root->left = insert_BT(root->left, data);
    }
    else {
        root->right = insert_BT(root->right, data);
    }
    return root;
}

// 이진 탐색 트리에서 노드를 삭제하는 함수
BSTNode* delete_BT(BSTNode* root, const char* name) {
    if (root == NULL) return root;

    if (strcmp(name, root->data.name) < 0) {
        root->left = delete_BT(root->left, name);
    }
    else if (strcmp(name, root->data.name) > 0) {
        root->right = delete_BT(root->right, name);
    }
    else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        BSTNode* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete_BT(root->right, temp->data.name);
    }
    return root;
}

// 이진 탐색 트리의 모든 노드를 중위 순회하여 출력하는 함수
void printAll_BT(BSTNode* node) {
    if (node != NULL) {
        printAll_BT(node->left);
        printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.attack, node->data.defense);
        printAll_BT(node->right);
    }
}

// 이진 탐색 트리를 중위 순회하여 정렬하는 함수
void sortByName_BT(BinaryTree* tree) {
    if (tree->root == NULL) return;

    Champion* array = (Champion*)malloc(tree->count * sizeof(Champion));
    int index = 0;

    inOrderTraversalToArray(tree->root, array, &index);

    tree->root = sortedArrayToBST(array, 0, tree->count - 1);
    free(array);
}

int main() {
    SingleLinkedList singleList = { NULL, 0 };
    BinaryTree binaryTree = { NULL, 0 };

    clock_t start, end;
    double cpu_time_used;

    // 단일 연결 리스트에 데이터 로드 및 정렬 시간 측정
    loadChampions_SL(&singleList);

    start = clock();
    sortByName_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("단일 연결 리스트 정렬 시간: %f 초\n", cpu_time_used);

    // 이진 탐색 트리에 데이터 로드
    loadChampions_BT(&binaryTree);

    char name[50];
    Champion newChampion;

    // 이진 탐색 트리에서 검색 시간 측정
    printf("검색할 챔피언의 이름을 입력하세요: ");
    scanf("%s", name);
    start = clock();
    BSTNode* searchResult = searchByName_BT(binaryTree.root, name);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (searchResult != NULL) {
        printf("챔피언 찾기 (%s) 시간: %f 초, 이름: %s\n", name, cpu_time_used, searchResult->data.name);
    }
    else {
        printf("챔피언 찾기 (%s) 시간: %f 초, 찾지 못했습니다.\n", name, cpu_time_used);
    }

    // 이진 탐색 트리에 삽입 시간 측정
    printf("삽입할 챔피언의 정보를 입력하세요 (포지션 이름 HP Attack Defense): ");
    scanf("%s %s %d %d %d", newChampion.position, newChampion.name, &newChampion.hp, &newChampion.attack, &newChampion.defense);
    start = clock();
    binaryTree.root = insert_BT(binaryTree.root, newChampion);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("챔피언 삽입 (%s) 시간: %f 초\n", newChampion.name, cpu_time_used);

    // 이진 탐색 트리에서 삭제 시간 측정
    printf("삭제할 챔피언의 이름을 입력하세요: ");
    scanf("%s", name);
    start = clock();
    binaryTree.root = delete_BT(binaryTree.root, name);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("챔피언 삭제 (%s) 시간: %f 초\n", name, cpu_time_used);

    // 이진 탐색 트리 출력 시간 측정
    start = clock();
    printAll_BT(binaryTree.root);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("이진 탐색 트리 출력 시간: %f 초\n", cpu_time_used);

    // 이진 탐색 트리 정렬 시간 측정
    start = clock();
    sortByName_BT(&binaryTree);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("이진 탐색 트리 정렬 시간: %f 초\n", cpu_time_used);

    return 0;
}
