#include<iostream>
using namespace std;

int earnings_for_enemy_and_minion(int enemy, int armor_e, int minion, int armor_m);

int earnings_for_two_enemies(int enemy1, int armor1, int enemy2, int armor2){
	if(armor2==0){
		if(enemy1>=enemy2) return enemy2;
		else return enemy1+earnings_for_two_enemies(enemy2-enemy1, 0, enemy1, armor1);
	}
	else{
		if(enemy1>=enemy2+armor2) return enemy2;
		if(enemy1>=armor2) return enemy1-armor2+earnings_for_two_enemies(enemy2+armor2-enemy1, 0, enemy1, armor1);
		else return earnings_for_two_enemies(enemy2,armor2-enemy1,enemy1,armor1);
	}
}

int earnings_for_minion_and_enemy(int minion, int armor_m, int enemy, int armor_e){
	if(armor_e==0){
		if(minion>=enemy) return enemy;
		else return minion+earnings_for_enemy_and_minion(enemy-minion, 0, minion, armor_m);
	}
	else{
		if(minion>=enemy+armor_e) return enemy;
		if(minion>=armor_e) return minion-armor_e+earnings_for_enemy_and_minion(enemy+armor_e-minion, 0, minion, armor_m);
		else return earnings_for_enemy_and_minion(enemy, armor_e-minion, minion, armor_m);
	}
}

int earnings_for_enemy_and_minion(int enemy, int armor_e, int minion, int armor_m){
	if(armor_m==0){
		if(enemy>=minion) return -minion;
		else return earnings_for_minion_and_enemy(minion-enemy, 0, enemy, armor_e);
	}
	else{
		if(enemy>=minion+armor_m) return -minion;
		if(enemy>=armor_m) return armor_m-minion+earnings_for_minion_and_enemy(minion+armor_m-enemy,0,enemy,armor_e);
		else return earnings_for_minion_and_enemy(minion, armor_m-enemy, enemy, armor_e);
	}
}

int main(void){
	printf("Please enter the number of units on your opponent\'s board, press enter to stop inputting\n");
	int n_opponent = 0;
	scanf("%d",&n_opponent);
	int opponent[n_opponent];
	int armor_opponent[n_opponent];
	printf("Please enter all power and armor on your opponent\'s board, seperated by space, press enter to stop inputting\n");
	for(int i = 0; i < n_opponent; ++i){
		scanf("%d %d",&opponent[i],&armor_opponent[i]);
	}
	printf("Please enter the number of units on your board, press enter to stop inputting\n");
	int n_minion = 0;
	scanf("%d",&n_minion);
	int minion[n_minion];
	int armor_minion[n_minion];
	printf("Please enter all power and armor on your board, seperated by space, press enter to stop inputting\n");
	for(int i = 0; i < n_minion; ++i){
		scanf("%d %d",&minion[i],&armor_minion[i]);
	}
	int two_enemy[n_opponent][n_opponent];
	int max_two_enemy = 0;
	int max_two_enemy_i = -1;
	int max_two_enemy_j = -1;
	for(int i = 0; i < n_opponent; i++){
		for(int j = i + 1; j < n_opponent; j++){
			two_enemy[i][j] = earnings_for_two_enemies(opponent[i],armor_opponent[i],opponent[j],armor_opponent[j]);
			if(two_enemy[i][j]>max_two_enemy){
				max_two_enemy = two_enemy[i][j];
				max_two_enemy_i = i;
				max_two_enemy_j = j;
			}
		}
	}
	int minion_enemy[n_minion][n_opponent];
	int max_minion_enemy = -10000000;
	int max_minion = -1;
	int max_enemy = -1;
	for(int i = 0; i < n_minion; i++){
		for(int j = 0; j < n_opponent; j++){
			minion_enemy[i][j]=earnings_for_minion_and_enemy(minion[i],armor_minion[i],opponent[j],armor_opponent[j]);
			if(minion_enemy[i][j]>max_minion_enemy){
				max_minion_enemy = minion_enemy[i][j];
				max_minion = i;
				max_enemy = j;
			}
		}
	}
	if(max_two_enemy >= max_minion_enemy){
		printf("Let the %dth enemy with strength %d attak the %d enemy with strength %d, get %d earning\n", max_two_enemy_i+1, opponent[max_two_enemy_i], max_two_enemy_j+1, opponent[max_two_enemy_j], max_two_enemy);
	}
	else if (max_minion_enemy > 0){
		printf("Let the %dth minion with strength %d attak the %d enemy with strength %d, get %d earning\n", max_minion+1, minion[max_minion], max_enemy+1, opponent[max_enemy], max_minion_enemy);
	}
	else{
		printf("Don\'t play this card, it won't give you positive points");
	}
	system("pause");
}
