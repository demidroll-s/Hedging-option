#pragma once
 
#include "black_scholes_model.h"
 
class Priceable {
public:
    virtual double price(const BlackScholesModel& model) const = 0;
};