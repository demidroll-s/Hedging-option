#pragma once
 
#include "stdafx.h"
#include "continuous_time_option_base.h"
 
class Path_independent_option:
    public Continuous_time_option_base {
public:
    virtual ~Path_independent_option() {}
    virtual double payoff(double final_stock_price) const = 0;
    double payoff(const std::vector<double>& stock_prices) const {
        return payoff(stock_prices.back());
    }
    bool is_path_dependent() const {
        return false;
    };
};