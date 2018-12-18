#include "hangman.h"

//Сложность игры
typedef enum gameLevels
{
	easy = 9,
	hard = 7
} level;

/*
Объявление переменных, как для модели
*/
int steps = (level)easy;
int wordSize = 0;
int gameStatus = -1;

unsigned char *word;
unsigned char *guessedWord;

unsigned char letter;

string header = "\t\t\t\t\tИгра \"Виселица\"\n\n";

/*
Игра "Виселица"
Статусы игры:
- -1 -> Общая ошибка(например, конфликт статуса игры) -> выход из игры
- 0 -> Начало игры
- 1 -> Игра
- 2 -> Победа
- 3 -> Поражение
*/
int gallows()
{
	setGameStatus(0);

	//Старт игры
	char gameLevel;
	do
	{
		gameLevel = gameStart();
	} while (gameLevel != '0' && gameLevel != '1');
	
	//Выбор уровня сожности
	if (gameLevel == '0')
	{
		steps = (level)easy;
	}
	else if (gameLevel == '1')
	{
		steps = (level)hard;
	}
	
	//Ввод слова
	do
	{
		//system("@cls||clear");
		printf("%s", header);
		if (wordSize > 0) {
			//Вывод подсказки
			string hint = "\t\tСлово должно содержать только заглавные и прописные русские буквы!\n\n";
			printf("%s", hint);
		}
		string wordEnter = "\t\t\tВаше слово:  ";
		printf("%s", wordEnter);
		getWord();
		initGuessedWord(word[0], word[wordSize - 1]);
		checkWord();
	} while (checkWin() != 1);
	//system("@cls||clear");
	printGuessedWord();


	//Угладывание букв
	while (checkWin() == 1)
	{
		letter = '\0';
		while (checkLetter() == 0)
		{
			printf("\t\t\t\tВведите букву: ");
			getLetter();
		}
		if (compareWordAndLetter() == 1) {
			changeGuessedWord();
			//printf("Буква угаданна, осталось шагов: %d\n", steps);
		}
		else {
			steps--;
			//printf("Буква не угаданна, осталось шагов: %d\n", steps);
		}
		//system("@cls||clear");
		printGuessedWord();
	}
	//system("@cls||clear");
	printf("%s", header);
	if (gameStatus == 2)
	{
		printf("\t\t\t\t\tВы выиграли!\n");
	}
	else
	{
		printf("\t\t\t\t\tВы проиграли!\n");
	}
	system("pause");
	return gameStatus;
}

/*
Вывод начала игры и выставление уровня сложности
*/
char gameStart()
{
	//system("@cls||clear");
	string startGame = "\t\t\t\tВыберите уровень сложности:\n\t\t\t0 - легко(9 попыток)\t1 - сложно(7 попыток)\n\t\t\tВаш выбор:  ";
	printf("%s%s", header, startGame);
	return getchar();
}

/*
Проверка статуса игры
Статусы:
- -1 -> Общая ошибка(например, конфликт статуса игры) -> выход из игры
 - 0 -> Игра не начата
 - 1 -> Идет игра
 - 2 -> Победа
 - 3 -> Поражение
*/
int checkWin()
{
	if (gameStatus == -1) {
		return -1;
	}
	else if (gameStatus == 0) {
		return 0;
	}
	else if (gameStatus == 1) {
		if (compareStrings(word, guessedWord) && steps > 0) {
			setGameStatus(2);
			return 2;
		}
		else if (steps <= 0) {
			setGameStatus(3);
			return 3;
		}
		else {
			setGameStatus(1);
			return 1;
		}
	}
	else {
		setGameStatus(-1);
		return -1;
	}
}
/*
Сравнение двух строк
Статусы:
 - 0 -> Строки не равны
 - 1 -> Строки равны
*/
int compareStrings(unsigned char* first, unsigned char* second)
{
	for (int i = 0; i < wordSize; i++)
	{
		if (first[i] != second[i]) {
			return 0;
		}
	}
	return 1;
}

/*
Выставление статуса игры
*/
void setGameStatus(int status)
{
	gameStatus = status;
}

/*
Проверка введенного изначального слова
1) Проверяет статус игры
2) Проверяет корректность введеннного слова
Статусы: 
 - -1 -> Общая ошибка(например, конфликт статуса игры) -> выход из игры
 - 1 -> Корректно введено слово -> изменение статуса игры на "Игра"
 - 0 -> Некорректно введенное слово -> статус игры остается "Началом игры" -> объяснение правил -> повторный запрос слова
*/
int checkWord()
{
	if (gameStatus == 0) {
		int compareSize = 0;
		for (int i = 0; i < wordSize; i++)
		{
			unsigned char compareLetter = word[i];
			/*
			Заглавные русские -> [0xC0; 0xE0)
			Прописные русские -> [0xE0; 0xFF]
			*/
			if ((compareLetter > 0xC0 && compareLetter <= 0xFF)) {
				compareSize++;
			}
		}
		if (compareSize == wordSize) {
			setGameStatus(1);
			return 1;
		}
		else {
			setGameStatus(0);
			return 0;
		}
	}
	else {
		setGameStatus(-1);
		return -1;
	}
}

/*
Проверка совпадения буквы со словом
1) Проверяет статус игры
2) Проверяет совпадения буквы
Статусы
- -1 -> Общая ошибка(например, конфликт статуса игры) -> выход из 
- 1 -> Буква совпала
- 0 -> Буква не совпала
*/
int compareWordAndLetter()
{
	if (gameStatus == 1) {
		for (int i = 1; i < (wordSize - 1); i++)
		{
			if (word[i] == letter) {
				changeGuessedWord();
				return 1;
			}
		}
		return 0;
	}
	else {
		setGameStatus(-1);
		return -1;
	}
}

/*
Проверка введенной буквы
!) Проверяет статус игры
2) Проверяет корректность буквы
Статусы:
- -1 -> Общая ошибка(например, конфликт статуса игры) -> выход из игры
- 0 -> Некорректно введенная буква -> количество оставшихся шагов не меняется -> вывод ошибки -> повторный запрос буквы
- 1 -> Корректно введенная буква
*/
int checkLetter()
{
	if (gameStatus == 1) {
		unsigned char compareLetter = letter;
		/*
		Заглавные русские -> [0xC0; 0xE0)
		Прописные русские -> [0xE0; 0xFF]
		*/
		if ((compareLetter > 0xC0 && compareLetter <= 0xFF)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return -1;
	}
}

/*
Инициализация угаданного слова
*/
void initGuessedWord(char first, char last)
{
	guessedWord = (unsigned char *)malloc(sizeof(unsigned char) * (wordSize + 1));
	for (int i = 0; i < wordSize; i++)
	{
		guessedWord[i] = '_';
	}
	guessedWord[0] = first;
	guessedWord[wordSize - 1] = last;
	guessedWord[wordSize] = '\0';
}


/*
Изменение угаданного слова
*/
void changeGuessedWord()
{
	int *guessedLetterPosition = (int *)malloc(sizeof(int));
	int guessedLetterCount = 0;

	for (int i = 0; i < wordSize; i++)
	{
		if (letter == word[i]) {
			guessedLetterCount++;
			guessedLetterPosition = (int *)realloc(guessedLetterPosition, sizeof(int) * guessedLetterCount);
			guessedLetterPosition[guessedLetterCount - 1] = i;
		}
	}

	for (int i = 0; i < guessedLetterCount; i++)
	{
		guessedWord[guessedLetterPosition[i]] = letter;
	}
}

/*
Считывание слова
*/
void getWord() 
{
	int tries = 0;
	wordSize = 0;
	while (wordSize == 0)
	{
		if (tries > 1)
		{
			getchar();
		}
		int size = 0;
		unsigned char wordLetter;

		word = (unsigned char *)malloc(sizeof(unsigned char));

		//todo Возможно изменить для визуальной оболочки
		while ((wordLetter = getchar()) != '\n') {
			size++;
			word = (unsigned char *)realloc(word, sizeof(unsigned char) * size);
			word[size - 1] = wordLetter;
		}
		size++;
		word = (unsigned char *)realloc(word, sizeof(unsigned char) * size);
		word[size - 1] = '\0';
		wordSize = size - 1;

		tries++;

	}
}

/*
Считывание буквы
*/
void getLetter()
{
	if (letter = getchar() == '\n')
	{
		letter = getchar();
	}
}

//\t\t\t ╔\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═
/*
Печать неугаданного слова
*/
void printGuessedWord()
{
	printf("%s\t\t\t\t\t\n", header);
	int stage = (level)easy - steps;
	if (stage == 0)
	{
		std::wcout << L"";
	}
	else if (stage == 1)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 2)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 3)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 4)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║   |\n\t\t\t ║   |\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 5)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║   |\\\n\t\t\t ║   |\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 6)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║  /|\\\n\t\t\t ║   |\n\t\t\t ║\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 7)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║  /|\\\n\t\t\t ║   |\n\t\t\t ║    \\\n\t\t\t ║\n\t\t\t═╩═";
	}
	else if (stage == 8)
	{
		std::wcout << L"\t\t\t ╔---╗\n\t\t\t ║   ║\n\t\t\t ║   ☻\n\t\t\t ║  /|\\\n\t\t\t ║   |\n\t\t\t ║  / \\\n\t\t\t ║\n\t\t\t═╩═";
	}
	printf("\n\n\t\t\t");
	for (int i = 0; i < wordSize; i++)
	{
		printf("%c ", guessedWord[i]);
	}
	printf("\n");
}
