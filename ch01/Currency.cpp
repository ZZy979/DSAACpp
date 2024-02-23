#include "Currency.h"

#include <iomanip>
#include <stdexcept>

// Create a currency object
Currency::Currency(Sign_type sign, unsigned long dollars, unsigned int cents) {
    set_value(sign, dollars, cents);
}

Currency::Currency(double amount) {
    set_value(amount);
}

// Set currency value
void Currency::set_value(Sign_type sign, unsigned long dollars, unsigned int cents) {
    if (cents > 99)     // too many cents
        throw std::invalid_argument("Cents should be < 100");
    amount_ = dollars * 100 + cents;
    if (sign == minus) amount_ = -amount_;
}

// Set currency value
void Currency::set_value(double amount) {
    // 2 decimal digits only
    if (amount < 0)
        amount_ = static_cast<long>((amount - 0.001) * 100);
    else
        amount_ = static_cast<long>((amount + 0.001) * 100);
}

// Add a and b
Currency operator+(const Currency& a, const Currency& b) {
    return Currency(a.get_amount() + b.get_amount());
}

Currency operator-(const Currency& a, const Currency& b) {
    return Currency(a.get_amount() - b.get_amount());
}

Currency operator*(const Currency& c, double x) {
    return Currency(c.get_amount() * x);
}

Currency operator/(const Currency& c, double x) {
    return Currency(c.get_amount() / x);
}

Currency operator%(const Currency& c, double x) {
    return Currency(c.get_amount() * x / 100);
}

std::istream& operator>>(std::istream& is, Currency& c) {
    if (double d; is >> d) c.set_value(d);
    return is;
}

// Insert currency value into stream os
std::ostream& operator<<(std::ostream& os, const Currency& c) {
    if (c.get_sign() == minus) os << '-';
    os << '$' << std::fixed << std::setprecision(2) << fabs(c.get_amount());
    return os;
}
