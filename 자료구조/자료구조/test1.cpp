#include <stdio.h>
#include <Windows.h>

char board[19][19] = { };

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

void PutStone(int turn) {
	turn = 0;
	int i, j;
	scanf("%d %d", &i, &j);
	if (board[j][i] == '+') {
		board[j][i] = 'O';
	}
	ChangeBoard();

}

int main() {
	system("cls");
	
	int turn = 0;

	PrintBoard();
	PutStone(turn);

	return 0;
}