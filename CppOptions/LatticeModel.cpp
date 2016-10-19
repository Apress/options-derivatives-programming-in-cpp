//

#include "LatticeModel.hpp"

#include <vector>
#include <cmath>

using vec = std::vector<double>;


double computePO(int ptype, double S, double X)
{
    if (ptype == 0)
    {
        return std::max(0.0, S - X);
    }
    else
    {
        return std::max(0.0, X - S);
    }
}


//void dolatice(int N,
//              double S0,
//              double rr,
//              double sigma,
//              int k, int T, double X, int ptype)
//{
//    vec this_s(2*N);
//    vec this_o(2*N);
//    vec next_s(2*N);
//    vec next_o(2*N);
//
//    double dt    = T / N;
//    double drift = (rr - 0.5 * sigma * sigma) * T;
//    double vol   = sigma * sqrt(k * dt);
//    double disc_dt = exp(-rr * dt);
//    double scale_s = exp(-drift / N);
//
//    for (int i=0; i<2*N; ++i)
//    {
//        this_s[i] = S0 * exp(drift + (i-N) * vol);
//        this_o[i] = computePO(ptype, this_s[i], X);
//    }
//
//    vec probs(3);
//    probs[0] = 0.5 / k;
//    probs[1] = (k-1)/k;
//    probs[2] = probs[0];
//
//    int interval = 10;
//
//    for (int i=N-1; i>=0; --i)
//    {
//        if (i % interval == 0)
//        {
//
//        }
//        for (int j=0; j<2*N; ++j)
//        {
//            double v =0;
//            v += probs[0] * this_o[j];
//            v += probs[1] * this_o[j+1];
//            v += probs[2] * this_o[j+2];
//
//            next_o[i] = disc_dt * v;  // discounted value
//        }
//
//        this_o = next_o;
//
//        if (1)
//        { // american option only
//            for (int j=0; j<2*N; ++j)
//            {
//                next_s[j] = scale_s * this_s[j];
//            }
//
//            this_s = next_s;
//
//            double payoff;
//            for (int j=0; j<2*N; ++j)
//            {
//                payoff = computePO(ptype, this_s[j], X);
////                this_o =
//            }
//        }
//    }
//
//}


class BinomialModel {
public:
    BinomialModel(const BinomialModel &p);
    ~BinomialModel();
    BinomialModel &operator=(const BinomialModel &p);

    BinomialModel(double T, // expiration time
                  double S,   // stock price
                  double r,   // interest rate
                  double sigma,
                  double q,   // dividend yield
                  int n,      // numer of steps
                  bool call
    );

    double optionPriceForStrike(double K);
    virtual void computePriceStep(int i, int j, double K, vec &prices,
                                  double p_u, double p_d, double u);


protected:
    double getStockPrice() { return m_S; }
private:
    double m_T;     // expiration time
    double m_S;     // stock price
    double m_r;     // interest rate
    double m_sigma; // volatility
    double m_q;     // dividend yield
    int m_n;        // numer of steps
    bool m_call;    // true = call, false = put

};


class AmericanBinomialModel : public BinomialModel {
    AmericanBinomialModel(const BinomialModel &p);
    ~AmericanBinomialModel();
    AmericanBinomialModel &operator=(const BinomialModel &p);

    AmericanBinomialModel(double T, // expiration time
                  double S,   // stock price
                  double r,   // interest rate
                  double sigma,
                  double q,   // dividend yield
                  int n,      // numer of steps
                  bool call
                  );

    virtual void computePriceStep(int i, int j, double K, vec &prices,
                                  double p_u, double p_d, double u);
};



AmericanBinomialModel::AmericanBinomialModel(const BinomialModel &p)
: BinomialModel(p)
{
}

AmericanBinomialModel::~AmericanBinomialModel()
{
}

AmericanBinomialModel &AmericanBinomialModel::operator=(const BinomialModel &p)
{
    BinomialModel::operator=(p);  // no new data members in this calss
    return *this;
}

AmericanBinomialModel::AmericanBinomialModel(double T, // expiration time
                      double S,   // stock price
                      double r,   // interest rate
                      double sigma,
                      double q,   // dividend yield
                      int n,      // numer of steps
                      bool call)
: BinomialModel(T, S, r, sigma, q, n, call)
{
}

void AmericanBinomialModel::computePriceStep(int i, int j, double K, vec &prices, double p_u, double p_d, double u)
{
    BinomialModel::computePriceStep(i, j, K, prices, p_u, p_d, u);

    // compute exercise price for American option
    //
    double exercise = K - getStockPrice() * pow(u, 2*i - j);
    if (prices[i] < exercise)
    {
        prices[i] = exercise;
    }
}


// ------------

BinomialModel::BinomialModel(double T, double S, double r,
              double sigma,
              double q,
              int n, bool call)
: m_T(T),
  m_S(S),
  m_r(r),
  m_sigma(sigma),
  m_n(n),
  m_q(q),
  m_call(call)
{
}

BinomialModel::BinomialModel(const BinomialModel &p)
: m_T(p.m_T),
  m_S(p.m_S),
  m_r(p.m_r),
  m_sigma(p.m_sigma),
  m_n(p.m_n),
  m_q(p.m_q),
  m_call(p.m_call)
{
}

BinomialModel::~BinomialModel()
{
}

BinomialModel &BinomialModel::operator=(const BinomialModel &p)
{
    if (this != &p)
    {
        m_T = p.m_T;
        m_S = p.m_S;
        m_r = p.m_r;
        m_sigma = p.m_sigma;
        m_n = p.m_n;
        m_q = p.m_q;
        m_call = p.m_call;
    }
    return *this;
}

void BinomialModel::computePriceStep(int i, int j, double K,
                                     vec &prices, double p_u, double p_d, double u)
{
    prices[i] = p_u * prices[i] + p_d * prices[i+1];
}

double BinomialModel::optionPriceForStrike(double K)
{

    double delta = m_T / m_n;   // size of each step
    double u = exp(m_sigma * sqrt(delta));

    double p_u = (u * exp(-m_r * delta) - exp(-m_q * delta)) * u / (u*u - 1);
    double p_d =      exp(-m_r * delta) - p_u;

    vec prices(m_n);

    //  compute last day values (leafs of the tree)
    for (int i= 0; i<m_n; ++i)
    {
        if (m_call)
        {
            prices[i] =  std::max(0.0, m_S * pow(u, 2*i - m_n) - K);
        }
        else
        {
            prices[i] =  std::max(0.0, K - m_S * pow(u, 2*i - m_n));
        }
    }

    for (int j = m_n-1; j>=0; --j)
    {
        for (int i = 0; i<j; ++i)
        {
            computePriceStep(i, j, K, prices, p_u, p_d, u);
        }
    }

    return prices[0];
}



















