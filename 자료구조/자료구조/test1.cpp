#include <stdio.h>
#include <Windows.h>

char board[19][19] = { };
int turn = 0;
int bstone = 0; //���� �� ī��Ʈ
int wstone = 0; //�� �� ī��Ʈ

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
			printf("%c ", board[j][i]);
		}
		printf("\n");
	}
}

void PutStone() {
	int i, j;
	scanf("%d %d", &i, &j);
	if (turn % 2 == 0) {
		if (board[j][i] == '+') {
			board[j][i] = 'O';
			++turn;
			++bstone;
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
		}
		else if (j > 18 || i > 18 || j < 0 || i < 0) {
			printf("������ ������ϴ�.\n");
			printf("���� �ٽ� �����ּ���.\n");
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
			turn = 0;
		}
		else {
			printf("�̹� ���� �����մϴ�.");
			printf("���� �ٽ� �����ּ���.\n");
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
			turn = 0;
		}
	}
	else if(turn % 2 == 1) {
		if (board[j][i] == '+') {
			board[j][i] = 'X';
			++turn;
			++wstone;
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
		}
		else if (j > 18 || i > 18 || j < 0 || i < 0) {
			printf("������ ������ϴ�.\n");
			printf("���� �ٽ� �����ּ���.\n");
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
			turn = 1;
		}
		else {
			printf("�̹� ���� �����մϴ�.");
			printf("���� �ٽ� �����ּ���.\n");
			printf("���� ���� �� : %d, �� ���� �� : %d\n", bstone, wstone);
			turn = 1;
		}
	}
	ChangeBoard();

}

int main() {
	system("cls");
	

	PrintBoard();
	while (1) {
		PutStone();
	}

	return 0;
}