#include <sstream>
#include <string>
#include <fstream>

#include "TimeInfo.h"
#include "Quote.h"

using namespace std;

QuoteSystem::QuoteSystem(){
    outFilename = "quote.csv";
}

void QuoteSystem::addHSQuote(string timeStr, CMarketInfo* info){
    data.push_back(*info);
    times.push_back(timeStr);
}

void QuoteSystem::addQuoteData2Map(string timeStr, QuoteData* info){
    
}

void QuoteSystem::bak2File(const char* filename){
    ofstream of(filename, ios::app);
    for(size_t i = 0; i < data.size(); i++){
        of<<times[i]<<","<<QuoteData2Str(data[i])<<endl;
    }
    of.close();
}

string QuoteData2Str(QuoteData &info){
    ostringstream os;
    os<<info.contract_code
        <<","<<info.pre_square_price
        <<","<<info.futu_open_price
        <<","<<info.futu_last_price
        <<","<<info.buy_high_price
        <<","<<info.buy_high_amount
        <<","<<info.buy_total_amount
        <<","<<info.sale_low_price
        <<","<<info.sale_low_amount
        <<","<<info.sale_total_amount
        <<","<<info.futu_high_price
        <<","<<info.futu_low_price
        <<","<<info.average_price
        <<","<<info.change_direction
        <<","<<info.business_amount
        <<","<<info.bear_amount
        <<","<<info.business_balance
        <<","<<info.uplimited_price
        <<","<<info.downlimited_price
        <<","<<info.futu_exch_type
        <<","<<info.form_buy_price
        <<","<<info.form_sale_price
        <<","<<info.form_buy_amount
        <<","<<info.form_sale_amount
        <<","<<info.pre_close_price
        <<","<<info.pre_open_interest
        <<","<<info.futu_close_price
        <<","<<info.square_price
        <<","<<info.pre_delta
        <<","<<info.curr_delta
        <<","<<info.bid_price2
        <<","<<info.bid_volume2
        <<","<<info.bid_price3
        <<","<<info.bid_volume3
        <<","<<info.bid_price4
        <<","<<info.bid_volume4
        <<","<<info.bid_price5
        <<","<<info.bid_volume5
        <<","<<info.ask_price2
        <<","<<info.ask_volume2
        <<","<<info.ask_price3
        <<","<<info.ask_volume3
        <<","<<info.ask_price4
        <<","<<info.ask_volume4
        <<","<<info.ask_price5
        <<","<<info.ask_volume5
        <<","<<info.update_time
        ;
    return os.str();
}