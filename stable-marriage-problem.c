#include <stdio.h>
#include <stdbool.h>

#define N 3

//array print
void printArray(int arr[N][N]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
}

//prefer check
bool prefNewMan(int pref[N][N], int woman, int man, int currentMan){
	for (int i = 0; i < N; i++){
		if (pref[woman][i] == man){
		return true;
		}
		if (pref[woman][i] == currentMan){
		return false;
		}
	}
	return false;
}

void stableMarriage(int menPref[N][N], int womanPref[N][N]){
	int womenPartner[N];
	bool menFree[N];
	int freeCount = N;

	//make available
	for (int i = 0; i < N; i++){
		womenPartner[i] = -1;
		menFree[i] = false;
	}
	
	//make for every man
	while (freeCount > 0){
		int man;

		//find free man
		for (man = 0; man < N; man++){
			if (menFree[man] == false){
				break;
			}
		}

		//check pref list
		for (int i = 0; i < N && menFree[man] == false; i++){
			int woman = menPref[man][i];

			if (womenPartner[woman] == -1){
				womenPartner[woman] = man;
				menFree[man] = true;
				freeCount--;
			} else { //if woman married
				int currentPartner = womenPartner[woman];
				if (prefNewMan(womanPref, woman, man, currentPartner)){
					womenPartner[woman] = man;
					menFree[man] = true;
					menFree[currentPartner] = false;
				}
			}
		}
	}

	printf("Woman\tMan\n");
	for (int i = 0; i < N; i++){
		printf("%d\t%d\n", i, womenPartner[i]);
	}
}
int main(){
	int menPref[N][N] = {
		{0, 1, 2},
		{1, 0, 2},
		{1, 2, 0}
	};
	

	int womenPref[N][N] = {
		{2, 1, 0},
		{0, 1, 2},
		{2, 0, 1}
	};

	printf("Men's choice list:\n");
	printArray(menPref);

	printf("Women's choice list:\n");
	printArray(womenPref);

	printf("\nStable matches:\n");
	stableMarriage(menPref, womenPref);

	return 0;
}
