//#include <stdio.h>
//#include <Windows.h>
//
//void printAstar() {
//	printf("*\n");
//}
//
//void printStars(int num) {
//	printf("*");
//	printStars();
//	
//}
//
//int main() {
//	int input; // 입력받는 번호
//
//	while (1) {
//		scanf("%d", &input);
//		if (input == 1) {
//			for (int i = 1; i <= 4; ++i) {
//				for (int j = 1; j <= i; ++j) {
//					printf("*");
//				}
//				printf("\n");
//				Sleep(1000);
//			}
//		}
//		else if (input == 2) {
//			int input_num;
//			scanf("%d", &input_num);
//			for (int i = 1; i <= input_num; ++i) {
//				for (int j = 1; j <= i; ++j) {
//					printf("*");
//				}
//				printf("\n");
//				Sleep(1000);
//			}
//		}
//		else if (input == 3) {
//			int input_num;
//			scanf("%d", &input_num);
//			for (int i = 1; i <= input_num; ++i) {
//				for (int j = 1; j <= i; ++j) {
//					printf("%d", j);
//				}
//				printf("\n");
//				Sleep(1000);
//			}
//		}
//		else if (input == 4) {
//			printAstar();
//		}
//		else if (input == 5) {
//			int input_num;
//			scanf("%d", &input_num);
//			printStars(input_num);
//		}
//	}
//
//	return 0;
//}