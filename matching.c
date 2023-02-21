/*10
 * main.c
 *
 *  Created on: Feb 19, 2023
 *      Author: alexisng
 */


#include <stdio.h>

int* program_match(int (*arr)[5], int start_dep, int size){
	int rank = 5;
	static int combo[2];

		for (int i = 0; i < size; ++i){
			int start_level = 0;
			int compare_level = 0;
			while (arr[start_level][start_dep] == 0){
				++start_level;
			}
			while (arr[compare_level][i] == 0){
				++compare_level;
			}
			if (arr[start_level][start_dep] == arr[compare_level][i] && start_dep != i){ // if there's two departments that want the same
				int programmer = (arr[start_level][start_dep]) - 1; // the programmer they want
				while (arr[rank][programmer] != start_dep || arr[rank][programmer] != i){ // until the programmer's pref matches
					if (arr[rank][programmer] == start_dep + 1){
						arr[0][start_dep] = arr[start_level][start_dep];
						combo[0] = start_dep;
						combo[1] = arr[start_level][start_dep];
						return combo; // returns programmer
					}
					if (arr[rank][programmer] == i  + 1){
						arr[0][i] = arr[compare_level][i];
						combo[0] = i;
						combo[1] = arr[compare_level][i];
						return combo; // return the i department programmer
					}
					++rank; // check the lower pref

				}
			}
		}
	combo[0] = -1;
	combo[1] = 0;
	return combo;
}

int set_zero(int (*arr)[5], int curr, int added_pair){
	curr+=1;
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j){
			if (i == 0 && j == 0) {
				j = curr;
			}

			if (arr[i][j] == added_pair){
				arr[i][j] = 0;
			}
 		}
	}
	return 0;
}

int main(){
	FILE *fp;
	char str[15];
	int pref[10][5];
	// file reading
	fp = fopen("input.txt", "r");
	int i = 0;
	if (fp == NULL){
		printf("Error opening file\n");
		return 1;
	}
	while (fgets(str, 15, fp)){
		sscanf(str,"%d %d %d %d %d",&pref[i][0],&pref[i][1], &pref[i][2], &pref[i][3], &pref[i][4]);
		++i;
		}
	fclose(fp);

//	// checks if it is unique & finds the repeat
	int size = 5;
	int total_dep = 15;
	int total_pro = 15;
	for (int i = 0; i < 6; ++i){
		int *match;

		if (i == 5){
			match = program_match(pref, total_dep, size);
		}else{
		match = program_match(pref, i, size);
		}
		total_dep -= (*(match + 0)+1);
		total_pro -= *(match + 1);

		if ((*(match+0)+1) != 0){
			set_zero(pref, *(match+0), *(match + 1));
		}else{
			pref[0][total_dep -1] = total_pro;
			for(int iter = 0; iter < 5; ++iter){
				printf("Department #%d will chose Programmer #%d\n", (iter + 1), pref[0][iter]);
			}
			break;
		}

	}

	return 0;
}
