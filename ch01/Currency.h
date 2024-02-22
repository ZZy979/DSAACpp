#pragma once

#include <cmath>
#include <iostream>

enum Sign_type { plus, minus };

class Currency {
public:
    Currency(Sign_type sign = plus, unsigned long dollars = 0, unsigned int cents = 0);
    ~Currency() = default;

    void set_value(Sign_type sign, unsigned long dollars, unsigned int cents);
    void set_value(double dollars);

    Sign_type get_sign() const { return amount < 0 ? minus : plus; }
    unsigned long get_dollars() const { return abs(amount) / 100; }
    unsigned int get_cents() const { return abs(amount) % 100; }

    Currency operator+(const Currency& c) const;
    Currency& operator+=(const Currency& c) { amount += c.amount; return *this; }

private:
    long amount;    // number of cents
};

std::ostream& operator<<(std::ostream& os, const Currency& c);
