#include "ctest.h"
#include <hangman.h>

CTEST (checkLetterTest, uncorrectFirstLetterTests)
{
	char letter;
	letter = 'a';
	setLetter(letter);
	setGameStatus(1);
	const int CHECK_VALUE = checkLetter();
	const int EXPECTED = 0;
	ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkLetterTest, uncorrectLastLetterTests)
{
        char letter;
        letter = 'Z';
        setLetter(letter);
        setGameStatus(1);
        const int CHECK_VALUE = checkLetter();
        const int EXPECTED = 0;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkLetterTest, correctFirstLetterTests)
{
        char letter;
        letter = 127;
        setLetter(letter);
        setGameStatus(1);
        const int CHECK_VALUE = checkLetter();
        const int EXPECTED = 1;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}


CTEST (checkLetterTest, correctLastLetterTests)
{
        char letter;
        letter = 255;
        setLetter(letter);
        setGameStatus(1);
        const int CHECK_VALUE = checkLetter();
        const int EXPECTED = 1;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkLetterTest, uncorrectGameStatusTests)
{
        setGameStatus(0);
        const int CHECK_VALUE = checkLetter();
        const int EXPECTED = -1;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkWordTest, correctWordTests)
{
	unsigned char word[] = "Ананас";
	setWord(6, word);
        setGameStatus(0);
        const int CHECK_VALUE = checkWord();
        const int EXPECTED = 1;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkWordTest, uncorrectWordTests)
{
        unsigned char word[] = "Pineapple";
        setWord(9, word);
        setGameStatus(0);
        const int CHECK_VALUE = checkWord();
        const int EXPECTED = 0;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

CTEST (checkWordTest, uncorrectGameStatusTests)
{
        setGameStatus(1);
        const int CHECK_VALUE = checkWord();
        const int EXPECTED = -1;
        ASSERT_EQUAL(EXPECTED, CHECK_VALUE);
}

