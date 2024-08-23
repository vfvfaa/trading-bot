
#include <iostream>
#include <Windows.h>

#include "tradingbot.h"

int main()
{
	int send_id;
	std::string webhook;
	std::string token = "", user_id = "";

	std::string info = "[Crypto-Trading Bot] - by Trandor";
	SetConsoleTitleA(info.c_str());

	HANDLE hfile = CreateFileA(("settings.txt"), FILE_ALL_ACCESS, NULL, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD file_size = GetFileSize(hfile, nullptr);
	if (hfile == NULL || hfile == INVALID_HANDLE_VALUE || file_size < 10) {
		CloseHandle(hfile);
		int t = 0;
	gt:
		std::cout << ("choose where to send the information\n1 - Discord\n2 - Telegram\n");
		std::cin >> t;
		if (t == 1) {

			std::string webhook = "";
			std::cout << ("enter the server's webhook:\n");
			std::cin >> webhook;
			hfile = CreateFileA(("settings.txt"), FILE_ALL_ACCESS, NULL, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			std::string write = ("discord\n") + webhook;
			WriteFile(hfile, write.c_str(), write.size(), nullptr, nullptr);
			CloseHandle(hfile);
		}
		else if (t == 2) {

			std::string token = "", user = "";
			std::cout << ("enter the telegram bot token:\n");
			std::cin >> token;
			std::cout << ("enter your user id:\n");
			std::cin >> user;
			std::string write = ("telegram\n") + token + ("\n") + user;
			WriteFile(hfile, write.c_str(), write.size(), nullptr, nullptr);
			CloseHandle(hfile);

		}
		else {
			goto gt;
		}
		std::cout << ("Saved!\n\n");
	}
	else
	{
		std::cout << ("your settings are loaded\n\n");
	}

	std::cout << ("start searching and calculating?(Y\\n)\n");
	while (!GetAsyncKeyState('Y')) {
		Sleep(1);
	}
	system(("cls"));
	tradingbot bot(send_id, webhook, token, user_id);

	while (true)
	{
		std::cout << ("recognize cryptocurrency prices (from Binance)...\n");
		bot.get_crypto_prices();

		std::cout << ("looking for strong price movements in a short period of time...\n");

		std::vector<crypto> movements = bot.get_strong_movements();
		if (movements.size() == 0) {
			std::cout << ("no major price movements yet.\n");
		}
		else {
			bot.send_info(ID_MOVEMENT, &movements);
		}

		std::cout << ("parsing cryptocurrency news...\n");
		std::vector<news> crypto_news = bot.parse_news();

		if (crypto_news.size() > 0) {
			bot.send_info(ID_NEWS, &crypto_news);
		}
		
		std::cout << ("looking for signals...\n");
		std::vector<std::string> signals = bot.get_signals();

		if (signals.size() > 0) {
			bot.send_info(ID_SIGNALS, &signals);
		}
	
		std::cout << ("view whale wallet transactions...\n");
		std::vector<transaction> whale_transactions = bot.get_new_whale_transactions();

		if (whale_transactions.size() > 0) {
			bot.send_info(ID_WHALE, &whale_transactions);
		}

		std::cout << ("repetition in 2 minutes\n");
		Sleep(120);
		std::cout << "\n\n";
	}
}

