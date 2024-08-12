#pragma once

#include "inet.h"

#define ID_MOVEMENT 1
#define ID_NEWS 2
#define ID_SIGNALS 3
#define ID_WHALE 4

struct crypto {
	std::string name;
	float price;
	float change;
	float per_min;
};

struct news {
	std::string caption;
	std::string text;
	time_t creation_time;
};

struct transaction {
	std::string sender;
	crypto cryptocurrency;
	float count;
	float total_price;
	time_t time;

};

class tradingbot
{
public:
	tradingbot(int send_id, std::string webhook, std::string token, std::string user_id);

	void get_crypto_prices();
	std::vector<crypto> get_strong_movements();
	std::vector<news> parse_news();
	std::vector<std::string> get_signals();
	std::vector<transaction> get_new_whale_transactions();

	bool send_info(int info_id, void* data);

private:
	int send_id;
	std::string webhook;
	std::string token, user_id;

	std::vector<crypto> cryptocurrencies;

};

