#include "Currency.h"

#include <stdexcept>

// Create a currency object
Currency::Currency(Sign_type sign, unsigned long dollars, unsigned int cents) {
    set_value(sign, dollars, cents);
}

// Set currency value
void Currency::set_value(Sign_type sign, unsigned long dollars, unsigned int cents) {
    if (cents > 99)     // too many cents
        throw std::invalid_argument("Cents should be < 100");
    amount = dollars * 100 + cents;
    if (sign == minus) amount = -amount;
}

// Set currency value
void Currency::set_value(double dollars) {
    // 2 decimal digits only
    if (dollars < 0)
        amount = static_cast<long>((dollars - 0.001) * 100);
    else
        amount = static_cast<long>((dollars + 0.001) * 100);
}

// Add c and *this
Currency Currency::operator+(const Currency& c) const {
    Currency result;
    result.amount = amount + c.amount;
    return result;
}

// Insert currency value into stream os
std::ostream& operator<<(std::ostream& os, const Currency& c) {
    if (c.get_sign() == minus) os << '-';
    os << '$' << c.get_dollars() << '.';
    if (c.get_cents() < 10) os << '0';
    os << c.get_cents();
    return os;
}
