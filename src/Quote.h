#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "HSFutures.h"
#include "Constants.h"

using namespace std;

typedef CMarketInfo QuoteData;
typedef double PriceType;
typedef unsigned int QuantityType;
typedef map<string, vector<QuoteData>> QuoteMap;

class ContractQuote{
public:
    ContractQuote(string contract);
    void addQuote(QuoteData* info);


public:
    vector<QuoteData> data;
    vector<string> times;
    vector<unsigned int> timeNum;
};

class QuoteSystem{

public:
    QuoteSystem();
    void addHSQuote(string timeStr, QuoteData* info);
    void bak2File(const char* filename);

    void addQuoteData2Map(string timeStr, QuoteData* info);
public:
    vector<QuoteData> data;
    vector<string> times;
    vector<string> contracts;


    QuoteMap quoteMap;

private:
    string outFilename;

    
};

string QuoteData2Str(QuoteData &info);

enum HS_MARKET_INFO{
    HS_QUOTE_CONTRACT_CODE = 0,
    HS_QUOTE_PRE_SQUARE_PRICE,
    HS_QUOTE_FUTU_OPEN_PRICE,
    HS_QUOTE_FUTU_LAST_PRICE,
    HS_QUOTE_BUY_HIGH_PRICE,
    HS_QUOTE_BUY_HIGH_AMOUNT,
    HS_QUOTE_BUY_TOTAL_AMOUNT,
    HS_QUOTE_SALE_LOW_PRICE,
    HS_QUOTE_SALE_LOW_AMOUNT,
    HS_QUOTE_SALE_TOTAL_AMOUNT,
    HS_QUOTE_FUTU_HIGH_PRICE,
    HS_QUOTE_FUTU_LOW_PRICE,
    HS_QUOTE_AVERAGE_PRICE,
    HS_QUOTE_CHANGE_DIRECTION,
    HS_QUOTE_BUSINESS_AMOUNT,
    HS_QUOTE_BEAR_AMOUNT,
    HS_QUOTE_BUSINESS_BALANCE,
    HS_QUOTE_UPLIMITED_PRICE,
    HS_QUOTE_DOWNLIMITED_PRICE,
    HS_QUOTE_FUTU_EXCH_TYPE,
    HS_QUOTE_FORM_BUY_PRICE,
    HS_QUOTE_FORM_SALE_PRICE,
    HS_QUOTE_FORM_BUY_AMOUNT,
    HS_QUOTE_FORM_SALE_AMOUNT,
    HS_QUOTE_PRE_CLOSE_PRICE,
    HS_QUOTE_PRE_OPEN_INTEREST,
    HS_QUOTE_FUTU_CLOSE_PRICE,
    HS_QUOTE_SQUARE_PRICE,
    HS_QUOTE_PRE_DELTA,
    HS_QUOTE_CURR_DELTA,
    HS_QUOTE_BID_PRICE2,
    HS_QUOTE_BID_VOLUME2,
    HS_QUOTE_BID_PRICE3,
    HS_QUOTE_BID_VOLUME3,
    HS_QUOTE_BID_PRICE4,
    HS_QUOTE_BID_VOLUME4,
    HS_QUOTE_BID_PRICE5,
    HS_QUOTE_BID_VOLUME5,
    HS_QUOTE_ASK_PRICE2,
    HS_QUOTE_ASK_VOLUME2,
    HS_QUOTE_ASK_PRICE3,
    HS_QUOTE_ASK_VOLUME3,
    HS_QUOTE_ASK_PRICE4,
    HS_QUOTE_ASK_VOLUME4,
    HS_QUOTE_ASK_PRICE5,
    HS_QUOTE_ASK_VOLUME5
};