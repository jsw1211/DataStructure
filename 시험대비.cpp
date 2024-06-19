#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS 100

struct Data {
    char name[10]{};
    int age{};
    char ID[10]{};
    int team{};
    int score{};
};

struct Node {
    Data data;
    Node* next;
};
Node* head = nullptr;

void PrintAll() {
    Node* p = head;
    for (p = head; p->next != head; p = p->next) {
        printf("%s %d %s %d %d\n", p->data.name, p->data.age, p->data.ID, p->data.team, p->data.score);
    }
}

void Delete() {
    char input_ID[10]{};
    scanf(" %s", input_ID);
    Data data;
    Node* p = head;
    //헤드일때

    while (strcmp(head->data.ID, input_ID) == 0) {
        Node* temp = head;
        head = head->next;

        Node* t = head;
        while (t->next != temp) {
            t = t->next;
        }
        t->next = head;
        delete temp;
    }

    //아닐때
    Node* prev_p = head;
    for (p = head; p->next != head; p = p->next) {
        if (strcmp(p->data.ID, input_ID) == 0) {
            prev_p->next = prev_p->next->next;
            delete p;
            p = prev_p;
            continue;
        }
        prev_p = p;
    }
}

void Search() {
    char input_name[10];
    scanf(" %s", input_name);
    Node* p = head;
    bool check = false;

    for (p = head; p->next != head; p = p->next) {
        if (strcmp(p->data.name, input_name) == 0) {
            printf("%s %d %s %d %d\n", p->data.name, p->data.age, p->data.ID, p->data.team, p->data.score);
            check = true;
            continue;
        }
    }
    if (check == false)
        printf("없다\n");
}

int main() {
    FILE* file = fopen("midTerm.txt", "r");
    Data temp;
    Node* current;
    int key;

    while (fscanf(file, "%s %d %s %d %d", temp.name, &temp.age, temp.ID, &temp.team, &temp.score) != EOF) {
        if (head == nullptr) {
            head = new Node{ temp };
            head->next = head;
            current = head;
            continue;
        }
        else {
            Node* newNode = new Node{ temp };
            newNode->next = head;
            current->next = newNode;
            current = newNode;
        }
    }

    while (1) {
        scanf("%d", &key);

        if (key == 1)
            PrintAll();
        else if (key == 2)
            Delete();
        else if (key == 3)
            Search();
    }


    return 0;
}