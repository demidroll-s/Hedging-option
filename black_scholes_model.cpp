#include "black_scholes_model.h"
 
using namespace std;
 
#include "matlib.h"
 
Black_Scholes_model::Black_Scholes_model() :
    drift(0.0),
    stock_price(0.0),
    volatility(0.0),
    risk_free_rate(0.0),
    date(0.0) {
}
 
vector<double> Black_Scholes_model::generate_risk_neutral_price_path(double to_date, int n_steps) const {
    return generate_price_path(to_date, n_steps, risk_free_rate);
}
 
vector<double> Black_Scholes_model::generate_price_path(double to_date, int n_steps) const {
    return generate_price_path(to_date, n_steps, drift);
}
 
vector<double> Black_Scholes_model::generate_price_path(double to_date, int n_steps, double drift) const {
    vector<double> path(n_steps, 0.0);
    vector<double> epsilon = rand_n(n_steps);
    double dt = (to_date - date) / n_steps;
    double a = (drift - volatility * volatility * 0.5) * dt;
    double b = volatility * sqrt(dt);
    double current_log_S = log(stock_price);
    for (int i = 0; i < n_steps; i++) {
        double d_log_S = a + b * epsilon[i];
        double log_S = current_log_S + d_log_S;
        path[i] = exp(log_S);
        current_log_S = log_S;
    }
    return path;
}
 
////////////////////////////////
//
//   TESTS
//
////////////////////////////////
 
void test_risk_neutral_price_path() {
    rng("default");
 
    Black_Scholes_model bsm;
    bsm.risk_free_rate = 0.05;
    bsm.volatility = 0.1;
    bsm.stock_price = 100.0;
    bsm.date = 2.0;
 
    int n_paths = 10000;
    int n_steps = 5;
    double maturity = 4.0;
    vector<double> final_prices(n_paths, 0.0);
    for (int i = 0; i < n_paths; i++) {
        vector<double> path = bsm.generate_risk_neutral_price_path(maturity, n_steps);
        final_prices[i] = path.back();
    }
    ASSERT_APPROX_EQUAL(mean(final_prices), exp(bsm.risk_free_rate * 2.0) * bsm.stock_price, 0.5);
}

void test_bsm() {
    TEST(test_risk_neutral_price_path);
}