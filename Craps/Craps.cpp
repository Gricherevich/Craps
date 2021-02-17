#include <string>
#include <iostream>
#include <sstream>
#include <time.h>
#include <random>

static int chipsNumbers{ 1000 }, betChips;
static int chipsBotNumbers{ 1000 }, betBotChips;

bool replay()
{
    std::string answer;

	while (true)
	{
		std::getline(std::cin, answer);
		if (answer == "exit")
			return false;
		if (answer == "play")
			return true;
		else
			std::cout << "Incorrect command try again.\n";
		
	}
}

void botThrow(int &firstBotThrow,int &secondBotThrow)
{
	int minValue{ 1 }, maxValue{ 6 };

	std::random_device rd;
	std::mt19937 mersenne(rd());
	firstBotThrow = minValue + mersenne() % (maxValue - minValue);
	secondBotThrow = minValue + mersenne() % (maxValue - minValue);
}

void playerThrow(int &firstPlayerThrow, int &secondPlayerThrow)
{
	int minValue{ 1 }, maxValue{ 6 };

	std::random_device rd;
	std::mt19937 mersenne(rd());
	firstPlayerThrow = minValue + mersenne() % (maxValue - minValue);
	secondPlayerThrow = minValue + mersenne() % (maxValue - minValue);
}

void comparisonNumber(const int &firstBotThrow, const int &secondBotThrow, const int &firstPlayerThrow, const int &secondPlayerThrow,
	int &botSum, int &playerSum)
{
	botSum = firstBotThrow + secondBotThrow;
	playerSum = firstPlayerThrow + secondPlayerThrow;

	if (botSum > playerSum)
	{
		std::cout << "Computer: " << botSum << "\nYou: " << playerSum
			<< "\nYou lose\n";
	}
	else if (playerSum > botSum)
	{
		std::cout << "Computer: " << botSum << "\nYou: " << playerSum
			<< "\nYou win\n";
	}
	else
	{
		std::cout << "Computer: " << botSum << "\nYou: " << playerSum
			<< "\ndraw\n";
	}
}

uint16_t getBet()
{
	std::cout << "You have " << chipsNumbers << " chips: \n";
	while (true)
	{
		std::cout << "Input your bet: \n";
		std::cin >> betChips;

		if (betChips > chipsNumbers)
		{
			std::cout << "You don't have enough chips. Bet again!";
			continue;
		}
		else
		{
			chipsNumbers -= betChips;
			return betChips;
		}
	}
	

}

uint16_t getBetBot(uint16_t const playsedChips)
{

	std::mt19937 botBetRand(time(0));
	std::uniform_int_distribution<> difference(-100, 100);
	
	if (playsedChips)
	{
		betBotChips = playsedChips + difference(botBetRand);
		chipsBotNumbers -= betBotChips;
		return betBotChips;
	}
	else
		return 0;

}

uint16_t sumBet(uint16_t &playsedChips, uint16_t &playsedBotChips,const int	&botSum, const int &playerSum)
{
	uint16_t winSum = playsedChips + playsedBotChips;
		return winSum;
}

int main()
{
	std::cout << "\t\tWELCOME TO CRAPS TABLE\n"
		<< "If you want to play print 'play', for exit print 'exit'\n";

	int firstBotThrow, secondBotThrow, firstPlayerThrow, secondPlayerThrow;
	int botSum{ 0 }, playerSum{ 0 };

	while (replay())
	{
		uint16_t playsedChips = getBet();
		uint16_t playsedBotChips = getBetBot(playsedChips);

		botThrow(firstBotThrow, secondBotThrow);
		playerThrow(firstPlayerThrow, secondPlayerThrow);
		comparisonNumber(firstBotThrow, secondBotThrow, firstPlayerThrow, secondPlayerThrow, botSum, playerSum);
		uint16_t result = sumBet(playsedChips, playsedBotChips, botSum, playerSum);

		if (botSum > playerSum)
			chipsBotNumbers += result;
		else if(botSum < playerSum)
			chipsNumbers += result;
		else if (botSum == playerSum)
		{
			chipsNumbers += playsedChips;
			chipsBotNumbers += playsedBotChips;
		}


		std::cout << chipsNumbers << " " << result << " " << chipsBotNumbers;
		std::cout << "\nIf you want to play again print 'play', to exit print 'exit'.\n";
		std::cin.ignore(32767, '\n');
	}

	return 0;
}
