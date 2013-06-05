#pragma once

#include "HsFutures.h"

#include "Quote.h"

extern QuoteSystem Quote;

struct SingleOrder{
    char* username;
    char* password;
    char* futu_exch_type;
    char* futures_account;
    char* contract_code;
    char* entrust_bs;
    char* futures_direction;
    char* hedge_type;
    char* futu_entrust_prop;
    char* futu_entrust_price;
    char* entrust_amount;
    char* entrust_kind;
};

class TradeServer{
public:
    TradeServer();
    int startServer();
    int closeServer();
    bool hasStart();

private:
    IHsFutuComm* server;
};