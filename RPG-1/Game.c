#include "stdio.h"
#include <stdbool.h>
#include <locale.h>

int main(void)
{
	//char *setlocale(LC_ALL, const char "C"); Вариант из спецификации 2024 не работает
	// Обязательно кодировать в ANSI или Windows-1251 иначе язык будет неправильно отображаться в программе на виндовс
	char *locale = setlocale(LC_ALL, "");
	int gold = 0;
	char action;
	int hp_goblin = 3;
	int tempI_hp_monster = 0;
	int player_damage = 1;
	bool tempB_die_monster = true;
	printf ("Привет путник, добро пожалоать в Си-Иур\n");
	printf ("Пред тобой гоблин,убей его!)\n");

	while (action != 'r')
	{
		if (tempB_die_monster) //проверка мертвый ли он, если да то предложат найти нового
		{
			printf ("'i'Ищем нового монстра или 'r'уходим?\n");			
			action = getchar();
			getchar();
			if(action == 'i')
			{
				tempI_hp_monster = hp_goblin;
				tempB_die_monster = false;
			}
		}
		if (tempI_hp_monster > 0) //Здесь будет бой с монстром
		{
			//деремся пока ХП монстра более нуля, к
			//атака монстра
			printf ("Ты видешь гоблина у него %d ХП\n 'a'Атакуем или 'r'бежим?\n",tempI_hp_monster);			
			action = getchar();
			getchar();
			if (action == 'a')
			{
				tempI_hp_monster = tempI_hp_monster - player_damage;
			}

			//огда ХП ноль и менее то выводиться сообщение что он умер
			if (tempI_hp_monster <= 0)
			{
				tempB_die_monster = true;
				gold = gold + 5;
				printf("Гоблин убит!\n Ты получил %d  золота!\n", gold);
			}

		}
		else //Если оно менее нуля то он считается мертвым
		{
			tempB_die_monster = true;

		}
				
	}
	printf ("Прощай! Нажми Enter клавишу.");
	action = getchar();
	getchar();
	return 0;
}
