#include <stdio.h>
#include <Windows.h>

void PrintBoard() {
	char board[19][19] = { };
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			board[j][i] = '+';
			printf("%c ", board[j][i]);
		}
		printf("\n");
	}

}


int main() {
	system("cls");
	
	PrintBoard();

	return 0;
}