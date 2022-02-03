#include "black_scholes_model.h"
 
using namespace std;
 
#include "matlib.h"
 
Black_Scholes_model::Black_Scholes_model() :
    drift(0.0),
    stockPrice(0.0),
    volatility(0.0),
    riskFreeRate(0.0),
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
    vector<double> epsilon = randn(n_steps);
    double dt = (to_date - date) / n_steps;
    double a = (drift - volatility * volatility * 0.5) * dt;
    double b = volatility * sqrt(dt);
    double current_log_S = log(stock_price);
    for (int i = 0; i < n_steps; i++) {
        double d_log_S = a + b * epsilon[i];
        double log_S = current_log_S + d_log_S;
        path[i] = exp(log_S);
        current_Log_S = log_S;
    }
    return path;
}
 
////////////////////////////////
//
//   TESTS
//
////////////////////////////////
 
void testRiskNeutralPricePath() {
    rng("default");
 
    BlackScholesModel bsm;
    bsm.riskFreeRate = 0.05;
    bsm.volatility = 0.1;
    bsm.stockPrice = 100.0;
    bsm.date = 2.0;
 
    int nPaths = 10000;
    int nsteps = 5;
    double maturity = 4.0;
    vector<double> finalPrices(nPaths,0.0);
    for (int i=0; i<nPaths; i++) {
        vector<double> path =
            bsm.generateRiskNeutralPricePath( maturity,
                                              nsteps );
        finalPrices[i] = path.back();
    }
    ASSERT_APPROX_EQUAL( mean( finalPrices ),
        exp( bsm.riskFreeRate*2.0)*bsm.stockPrice, 0.5);
}
 
void testVisually() {
    BlackScholesModel bsm;
    bsm.riskFreeRate = 0.05;
    bsm.volatility = 0.1;
    bsm.stockPrice = 100.0;
    bsm.date = 2.0;
 
    int nSteps = 1000;
    double maturity = 4.0;
 
    vector<double> path = bsm.generatePricePath( maturity,
                                                 nSteps );
    double dt = (maturity-bsm.date)/nSteps;
    vector<double> times = linspace(dt, maturity, nSteps );
    plot("examplePricePath.html",
         times,
         path );
}
 
 
void testBlackScholesModel() {
    TEST( testRiskNeutralPricePath );
    TEST( testVisually );
}