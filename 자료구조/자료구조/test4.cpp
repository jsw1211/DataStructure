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
//void Search_R(int i, char champion_name[15]) {
//	if (i == champions_cnt) {
//		return;
//	}
//	else {
//		int name_result = strcmp(champion_name, champions[i].name);
//		if (name_result == 0) {
//			printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//				champions[i].speed, champions[i].range, champions[i].position);
//		}
//		Search_R(++i, champion_name);
//	}
//}
//
//void Insert_R(int i) {
//	if (i == champions_cnt) {
//		scanf(" %[^\n] %d %d %d %d %s", champions[champions_cnt].name, &champions[champions_cnt].hp, &champions[champions_cnt].mp,
//			&champions[champions_cnt].speed, &champions[champions_cnt].range, champions[champions_cnt].position);
//		++champions_cnt;
//	}
//	else {
//		if (champions[i].hp == -1) {
//			scanf(" %[^\n] %d %d %d %d %s", champions[i].name, &champions[i].hp, &champions[i].mp,
//				&champions[i].speed, &champions[i].range, champions[i].position);
//			return;
//		}
//		Insert_R(++i);
//	}
//}
//
//void Delete_R(int i, char champion_name[10]) {
//	if (i == champions_cnt) {
//		return;
//	}
//	else {
//		int name_result = strcmp(champion_name, champions[i].name);
//		if (name_result == 0) {
//			strcpy(champions[i].name, "\0");
//			champions[i].hp = -1;
//			champions[i].mp = -1;
//			champions[i].speed = -1;
//			champions[i].range = -1;
//			strcpy(champions[i].position, "\0");
//		}
//		Delete_R(++i, champion_name);
//	}
//}
//
//void DeleteAll_R(int i, char champion_position[10]) {
//	if (i == champions_cnt) {
//		return;
//	}
//	else {
//		int position_result = strcmp(champion_position, champions[i].position);
//		if (position_result == 0) {
//			strcpy(champions[i].name, "\0");
//			champions[i].hp = -1;
//			champions[i].mp = -1;
//			champions[i].speed = -1;
//			champions[i].range = -1;
//			strcpy(champions[i].position, "\0");
//			--i;
//		}
//		DeleteAll_R(++i, champion_position);
//	}
//}
//
//void PrintAll_R(int i) {
//	if (i == champions_cnt) {
//		return;
//	}
//	else {
//		if (champions[i].hp != -1) {
//			printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//				champions[i].speed, champions[i].range, champions[i].position);
//		}
//		PrintAll_R(++i);
//	}
//}
//
//int FindMaxHp_R(int i, int max_hp) {
//	if (i == champions_cnt) {
//		return max_hp;
//	}
//	if (max_hp < champions[i].hp) {
//		max_hp = champions[i].hp;
//	}
//	return FindMaxHp_R(++i, max_hp);
//}
//
//void MaxHpPrint(int i, int max_hp) {
//	if (i == champions_cnt) {
//		return;
//	}
//	if (max_hp == champions[i].hp) {
//		printf("%s %d %d %d %d %s\n", champions[i].name, champions[i].hp, champions[i].mp,
//			champions[i].speed, champions[i].range, champions[i].position);
//	}
//	MaxHpPrint(++i, max_hp);
//}
//
//void SortByHp_R(int i) {
//	Champion index;
//	if (i == 0) {
//		return;
//	}
//	for (int j = 0; j < i; ++j) {
//		if (champions[j].hp < champions[j + 1].hp) {
//			index = champions[j + 1];
//			champions[j + 1] = champions[j];
//			champions[j] = index;
//		}
//	}
//	SortByHp_R(--i);
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
//			char s_champion_name[15];
//			scanf(" %[^\n]", s_champion_name);
//			Search_R(0, s_champion_name);
//		}
//		else if (key == 2) {
//			Insert_R(0);
//		}
//		else if (key == 3) {
//			char d_champion_name[15];
//			scanf("%[^\n]", d_champion_name);
//			Delete_R(0, d_champion_name);
//		}
//		else if (key == 4) {
//			char champion_position[10];
//			scanf("%s", champion_position);
//			DeleteAll_R(0, champion_position);
//		}
//		else if (key == 5) {
//			PrintAll_R(0);
//		}
//		else if (key == 6) {
//			int max_hp = FindMaxHp_R(0, champions[0].hp);
//			MaxHpPrint(0, max_hp);
//		}
//		else if (key == 7) {
//			SortByHp_R(champions_cnt - 1);
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