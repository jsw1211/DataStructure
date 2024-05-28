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

// ���� ���� ����Ʈ
typedef struct SingleLinkedList {
    Champion* head;
    int count;
} SingleLinkedList;

// ���� Ž�� Ʈ��
typedef struct BinaryTree {
    BSTNode* root;
    int count;
} BinaryTree;

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

// ���� ������ ���� ���� �Լ�
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

// ���� ���� �Լ�
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

// ���� ������ ����Ͽ� �̸����� ���� ���� ����Ʈ�� �����ϴ� �Լ�
void sortByName_SL(SingleLinkedList* list) {
    list->head = mergeSort(list->head);
}

// ���Ͽ��� �����͸� �о�� ���� Ž�� Ʈ���� �����ϴ� �Լ�
void loadChampions_BT(BinaryTree* tree) {
    FILE* file = fopen("LOLDic.txt", "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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

// ���� ��ȸ (In-Order Traversal)�� ���� ���� Ž�� Ʈ�� �����͸� �迭�� �����ϴ� �Լ�
void inOrderTraversalToArray(BSTNode* node, Champion* array, int* index) {
    if (node != NULL) {
        inOrderTraversalToArray(node->left, array, index);
        array[*index] = node->data;
        (*index)++;
        inOrderTraversalToArray(node->right, array, index);
    }
}

// ���ο� ���� Ž�� Ʈ���� �迭�κ��� �����ϴ� �Լ�
BSTNode* sortedArrayToBST(Champion* array, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = array[mid];
    node->left = sortedArrayToBST(array, start, mid - 1);
    node->right = sortedArrayToBST(array, mid + 1, end);

    return node;
}

// ���� Ž�� Ʈ������ �̸����� è�Ǿ��� �˻��ϴ� �Լ�
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

// ���� Ž�� Ʈ���� ���ο� è�Ǿ��� �����ϴ� �Լ�
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

// ���� Ž�� Ʈ������ ��带 �����ϴ� �Լ�
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

// ���� Ž�� Ʈ���� ��� ��带 ���� ��ȸ�Ͽ� ����ϴ� �Լ�
void printAll_BT(BSTNode* node) {
    if (node != NULL) {
        printAll_BT(node->left);
        printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.attack, node->data.defense);
        printAll_BT(node->right);
    }
}

// ���� Ž�� Ʈ���� ���� ��ȸ�Ͽ� �����ϴ� �Լ�
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

    // ���� ���� ����Ʈ�� ������ �ε� �� ���� �ð� ����
    loadChampions_SL(&singleList);

    start = clock();
    sortByName_SL(&singleList);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� ���� ����Ʈ ���� �ð�: %f ��\n", cpu_time_used);

    // ���� Ž�� Ʈ���� ������ �ε�
    loadChampions_BT(&binaryTree);

    char name[50];
    Champion newChampion;

    // ���� Ž�� Ʈ������ �˻� �ð� ����
    printf("�˻��� è�Ǿ��� �̸��� �Է��ϼ���: ");
    scanf("%s", name);
    start = clock();
    BSTNode* searchResult = searchByName_BT(binaryTree.root, name);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (searchResult != NULL) {
        printf("è�Ǿ� ã�� (%s) �ð�: %f ��, �̸�: %s\n", name, cpu_time_used, searchResult->data.name);
    }
    else {
        printf("è�Ǿ� ã�� (%s) �ð�: %f ��, ã�� ���߽��ϴ�.\n", name, cpu_time_used);
    }

    // ���� Ž�� Ʈ���� ���� �ð� ����
    printf("������ è�Ǿ��� ������ �Է��ϼ��� (������ �̸� HP Attack Defense): ");
    scanf("%s %s %d %d %d", newChampion.position, newChampion.name, &newChampion.hp, &newChampion.attack, &newChampion.defense);
    start = clock();
    binaryTree.root = insert_BT(binaryTree.root, newChampion);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("è�Ǿ� ���� (%s) �ð�: %f ��\n", newChampion.name, cpu_time_used);

    // ���� Ž�� Ʈ������ ���� �ð� ����
    printf("������ è�Ǿ��� �̸��� �Է��ϼ���: ");
    scanf("%s", name);
    start = clock();
    binaryTree.root = delete_BT(binaryTree.root, name);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("è�Ǿ� ���� (%s) �ð�: %f ��\n", name, cpu_time_used);

    // ���� Ž�� Ʈ�� ��� �ð� ����
    start = clock();
    printAll_BT(binaryTree.root);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� Ž�� Ʈ�� ��� �ð�: %f ��\n", cpu_time_used);

    // ���� Ž�� Ʈ�� ���� �ð� ����
    start = clock();
    sortByName_BT(&binaryTree);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� Ž�� Ʈ�� ���� �ð�: %f ��\n", cpu_time_used);

    return 0;
}
