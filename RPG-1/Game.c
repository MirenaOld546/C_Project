#include "stdio.h"
#include <stdbool.h>
#include <locale.h>

int main(void)
{
	//char *setlocale(LC_ALL, const char "C"); Вариант из спецификации 2024 не работает
	// Обязательно кодировать в ANSI или Windows-1251 иначе язык будет неправильно отображаться в программе на виндовс
	//Системные Харрактеристики
	char *locale = setlocale(LC_ALL, "");
	char action = '0';
	size_t tempST_length; //определяет длинну наименования монстра в инициализации
	int i;
	int stage = 1; // Стадия игрыы (глубина в лес). Отвечает за глубину прохода в лес и награду

	//Харрактеристики мостра
	char monster_goblin_name[] = "Гоблин";
	int monster_goblin_hp = 3;
	int monster_goblin_damage = 1;
	int monster_goblin_gold = 4;

	//Временные переменные для боя,
	char tempC_name_monster[10] = "          ";
	int tempI_hp_monster = 0;
	int tempI_damage_monster = 0;
	int tempI_gold_monster = 0;
	bool tempB_die_monster = true;
	int tempI_score = 0;

	// Харрактеристики игрока
	int player_damage = 1;
	int player_hp = 10;
	int player_hp_max = 10;
	int player_total_score = 0;
	int player_gold = 0;
	

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
				tempST_length = sizeof(monster_goblin_name)/sizeof(char);//определяем длину массива
				for (i=0;i<tempST_length;i++)
				{
					tempC_name_monster[i] = monster_goblin_name[i];
				}	
				for (i=tempST_length;i<10;i++)
				{
					tempC_name_monster[i] = ' ';
				}			
				tempI_hp_monster = monster_goblin_hp;
				tempI_damage_monster = monster_goblin_damage;
				tempI_gold_monster = monster_goblin_gold + stage;
				tempB_die_monster = false;
			}
		}

		if (tempI_hp_monster > 0) //Здесь будет бой с монстром
		{
			//деремся пока ХП монстра более нуля, к
			//атака монстра
			printf ("Ты видешь %s", tempC_name_monster);
			printf (" у него %d ХП\n",tempI_hp_monster);
			printf ("Твое здоровье %d ХП\n 'a'Атакуем или 'e'бежим?\n", player_hp);		
			action = getchar();
			getchar();	
			//Монстр так же атакует тебя в ответ
			if (action == 'a')
			{
				tempI_hp_monster -= player_damage;
				printf ("Нанесен %d урон монстру\n", player_damage);
				player_hp -= tempI_damage_monster;
				printf ("Тебе нанесен %d урон\n", tempI_damage_monster);
			}

			if (action == 'e')
			{
				printf ("Ты убежал!\n");
				player_hp -= tempI_damage_monster;
				printf ("Тебе нанесен %d урон\n", tempI_damage_monster);
				tempB_die_monster = true;
			}

			//Когда ХП ноль и менее то выводиться сообщение что он умер
			if (tempI_hp_monster <= 0)
			{
				tempB_die_monster = true;
				player_gold += tempI_gold_monster;
				player_total_score++;
				tempI_score++;
				printf("Гоблин убит!\n Ты получил %d  золота! Теперь у тебя %d золота и %d ХП.\n", tempI_gold_monster, player_gold, player_hp);
			}
			
			//Каждый 5 временных очков повышают стадию и обнуляются
			if (tempI_score >= 5)
			{
				stage++;
				tempI_score = 0;
				printf ("Поздравляю ты зашел дальше в лес, награды станет больше. \nГлубина изучения леса: %d.\n", stage);
			}
			
			
			// Все проверки ниже сделаны для окончания блужданий или смерти-------------------
			if (player_hp <= 0)
			{
				printf ("Ты умер! %d золота осталось в лесу.\n", player_gold);
				player_gold = 0;
				action = 'r';
			}
			if (action == 'r')
			{
			tempI_score = 0;
			}

		}
		else //Если оно менее нуля то он считается мертвым
		{
			tempB_die_monster = true;
		}

	}
	printf ("Прощай! Ты заработал %d золота. Убил %d монстров.\nВошёл в глубь леса на %d.\nНажми Enter клавишу.", player_gold, player_total_score, stage);
	action = getchar();
	getchar();
	return 0;
}
