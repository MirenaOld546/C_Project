#include "stdio.h"
#include <stdbool.h>
#include <locale.h>

int main(void)
{
	//char *setlocale(LC_ALL, const char "C"); Вариант из спецификации 2024 не работает
	// Обязательно кодировать в ANSI или Windows-1251 иначе язык будет неправильно отображаться в программе на виндовс
	char *locale = setlocale(LC_ALL, "");
	int gold = 0;
	char action = '0';

	//Харрактеристики мостра
	char monster_goblin_name[] = "Гоблин";
	int monster_goblin_hp = 3;
	int monster_goblin_damage = 1;
	int monster_goblin_gold = 5;
	//Временные переменные для боя,
	char tempC_name_monster[] = "";
	int tempI_hp_monster = 0;
	int tempI_damage_monster = 0;
	int tempI_gold_monster = 0;
	bool tempB_die_monster = true;
	// Харрактеристики игрока
	int player_damage = 1;
	int player_hp = 5;
	int player_hp_max = 5;

	printf ("Привет путник, добро пожалоать в Си-Иур\n");
	printf ("Ты выходишь на тропу приключений и тебя ждут монстры!)\n");

	while (action != 'r')
	{
		// Здесь будет отдых и восстановление здоровья
		if (action == 'e')		
		{
			printf("Ты отдыхаешь\n.");
			player_hp = player_hp_max;
			printf("Твое здоровье восстановлено до %d ХП\n", player_hp);
		}


		if (tempB_die_monster) //проверка мертвый ли он, если да то предложат найти нового
		{
			printf ("'i'Ищем нового монстра, 'e'отдыхаем или r'уходим?\n");
			action = getchar();
			getchar();
			// При инициализации задается временные переменные для боя,
			//и монстер не считается мертвым, т.к. он найден и начинается бой
			// изменятся будут именно они
			if(action == 'i')
			{				
				tempI_hp_monster = monster_goblin_hp;
				tempI_damage_monster = monster_goblin_damage;
				tempI_gold_monster = monster_goblin_gold;
				tempB_die_monster = false;
			}
		}

		if (tempI_hp_monster > 0) //Здесь будет бой с монстром
		{
			//деремся пока ХП монстра более нуля, к
			//атака монстра
			printf ("Ты видешь %s", monster_goblin_name);
			printf (" у него %d ХП\n",tempI_hp_monster);
			printf ("Твое здоровье %d ХП\n 'a'Атакуем или 'e'бежим?\n", player_hp);
			action = getchar();
			getchar();
			//Монстр так же атакует тебя в ответ
			if (action == 'a')
			{
				tempI_hp_monster = tempI_hp_monster - player_damage;
				printf ("Нанесен %d урон монстру\n", player_damage);
				player_hp = player_hp - tempI_damage_monster;
				printf ("Тебе нанесен %d урон\n", tempI_damage_monster);
			}

			if (player_hp <= 0)
			{
				printf ("Ты умер! Все золото осталось в лесу.");
				gold = 0;
				action = 'r';
			}

			if (action == 'e')
			{
				printf ("Ты убежал!\n");
				player_hp = player_hp - tempI_damage_monster;
				printf ("Тебе нанесен %d урон\n", tempI_damage_monster);
				tempB_die_monster = true;
			}

			//Когда ХП ноль и менее то выводиться сообщение что он умер
			if (tempI_hp_monster <= 0)
			{
				tempB_die_monster = true;
				gold = gold + tempI_gold_monster;
				printf("Гоблин убит!\n Ты получил %d  золота!\n", gold);
			}

		}
		else //Если оно менее нуля то он считается мертвым
		{
			tempB_die_monster = true;
		}

	}
	printf ("Прощай! Ты заработал %d Нажми Enter клавишу.", gold);
	action = getchar();
	getchar();
	return 0;
}
