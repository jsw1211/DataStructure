//#include <stdio.h>
//#include <string.h>
//
//int champions_cnt = 22;
//
//struct Champion {
//
//	char name[15] = { NULL };
//	int hp = NULL;
//	int mp = NULL;
//	int speed = NULL;
//	int range = NULL;
//	char position[10] = { NULL };
//
//};
//
//
//Champion champions[50] = { "Jayce", 3466, 8307, 452, 73, "mid",
//"Vayne", 3318, 2790, 390, 60, "support",
//"Lee Sin", 9864, 6257, 747, 19, "support",
//"Teemo", 1915, 1313, 700, 68, "mid",
//"Nami", 2968, 2153, 803, 74, "support",
//"Jinx", 2583, 3042, 123, 53, "jungle",
//"Cassiopeia", 6067, 7330, 683, 24, "top",
//"Ahri", 4573, 7079, 177, 79, "top",
//"Fiora", 2591, 9329, 337, 81, "jungle",
//"Zac", 9864, 7272, 405, 49, "bottom",
//"Janna", 4922, 2275, 690, 66, "jungle",
//"Ashe", 7421, 5549, 428, 31, "top",
//"Twitch", 2980, 7703, 204, 91, "mid",
//"Ezreal", 3660, 9835, 274, 44, "mid",
//"Sona", 5655, 8442, 252, 26, "bottom",
//"Lulu", 3231, 2014, 503, 32, "support",
//"Amumu", 6763, 3994, 427, 19, "jungle",
//"Master Yi", 5737, 7168, 434, 61, "top",
//"Jarvan", 1895, 3070, 323, 80, "mid",
//"Shen", 4794, 9220, 783, 42, "mid",
//"Fizz", 9864, 1913, 433, 38, "bottom",
//"Taric", 6158, 7451, 160, 36, "bottom" };
//
//void Search() {
//	char champion_name[15];
//	scanf("%[^\n]", champion_name);
//	for (int i = 0; i < champions_cnt; ++i) {
//		int name_result = strcmp(champion_name, champions[i].name);
//		if (name_result == 0) {
//			printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//				champions[i].speed, champions[i].range, champions[i].position);
//			break;
//		}
//	}
//}
//
//void Insert() {
//	scanf(" %[^\n] %d %d %d %d %s ", champions[champions_cnt].name, &champions[champions_cnt].hp, &champions[champions_cnt].mp,
//		&champions[champions_cnt].speed, &champions[champions_cnt].range, champions[champions_cnt].position);
//	++champions_cnt;
//}	
//
//void Delete() {
//	char champion_name[15];
//	scanf("%[^\n]", champion_name);
//	for (int i = 0; i < champions_cnt; ++i) {
//		int name_result = strcmp(champion_name, champions[i].name);
//		if (name_result == 0) {
//			for (int j = i; j < champions_cnt; ++j) {
//				strcpy(champions[j].name, champions[j + 1].name);
//				champions[j].hp = champions[j + 1].hp;
//				champions[j].mp = champions[j + 1].mp;
//				champions[j].speed = champions[j + 1].speed;
//				champions[j].range = champions[j + 1].range;
//				strcpy(champions[j].position, champions[j + 1].position);
//			}
//			--champions_cnt;
//		}
//	}
//}
//
//void DeleteAll() {
//	char champion_position[10];
//	scanf("%s", champion_position);
//	for (int i = 0; i < champions_cnt; ++i) {
//		int name_result = strcmp(champion_position, champions[i].position);
//		if (name_result == 0) {
//			for (int j = i; j < champions_cnt; ++j) {
//				strcpy(champions[j].name, champions[j + 1].name);
//				champions[j].hp = champions[j + 1].hp;
//				champions[j].mp = champions[j + 1].mp;
//				champions[j].speed = champions[j + 1].speed;
//				champions[j].range = champions[j + 1].range;
//				strcpy(champions[j].position, champions[j + 1].position);
//			}
//			--champions_cnt;
//			--i;
//		}
//	}
//}
//
//void PrintAll() {
//	for (int i = 0; i < champions_cnt; ++i) {
//		printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//			champions[i].speed, champions[i].range, champions[i].position);
//	}
//}
//
//void FindMaxHp() {
//	int max_hp = champions[0].hp;
//	for (int i = 0; i < champions_cnt; ++i) {
//		if (max_hp < champions[i].hp) {
//			max_hp = champions[i].hp;
//		}
//	}
//	for (int i = 0; i < champions_cnt; ++i) {
//		if (max_hp == champions[i].hp) {
//			printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//				champions[i].speed, champions[i].range, champions[i].position);
//		}
//	}
//}
//
//void SortByHp() {
//	Champion index;
//	for (int i = champions_cnt; i >= 0; --i) {
//		for (int j = 0; j < i; ++j) {
//			if (champions[j].hp < champions[j + 1].hp) {
//				index = champions[j + 1];
//				champions[j + 1]= champions[j];
//				champions[j] = index;
//			}
//		}
//	}
//}
//
//int main() {
//	int key;
//	printf("1:Search\n");
//	printf("2:Insert\n");
//	printf("3:Delete\n");
//	printf("4:DeleteAll\n");
//	printf("5:PrintAll\n");
//	printf("6:FindMaxHp\n");
//	printf("7:SortByHp\n");
//	printf("0:종료\n");
//	printf("Insert기능 사용 시 이름에 띄어쓰기가 있을 수도 있으므로 이름을 입력한 후 엔터를 치고 다음 값들을 전체적으로 입력해주세요\n");
//	while (1) {
//		scanf("%d", &key);
//		if (key == 1) {
//			Search();
//		}
//		else if (key == 2) {
//			Insert();
//		}
//		else if (key == 3) {
//			Delete();
//		}
//		else if (key == 4) {
//			DeleteAll();
//		}
//		else if (key == 5) {
//			PrintAll();
//		}
//		else if (key == 6) {
//			FindMaxHp();
//		}
//		else if (key == 7) {
//			SortByHp();
//		}
//		else if (key == 0) {
//			return 0;
//		}
//		else {
//			printf("없는 명령어 입니다.\n");
//		}
//	}
//
//	return 0;
//}