#pragma once

#include <cmath>
#include <iostream>

enum Sign_type { plus, minus };

class Currency {
public:
    explicit Currency(Sign_type sign = plus, unsigned long dollars = 0, unsigned int cents = 0);
    explicit Currency(double amount);
    ~Currency() = default;

    void set_value(Sign_type sign, unsigned long dollars, unsigned int cents);
    void set_value(double amount);

    Sign_type get_sign() const { return amount_ < 0 ? minus : plus; }
    unsigned long get_dollars() const { return abs(amount_) / 100; }
    unsigned int get_cents() const { return abs(amount_) % 100; }
    double get_amount() const { return amount_ / 100.0; }

    Currency& operator=(double amount) { set_value(amount); return *this; }
    Currency& operator+=(const Currency& c) { amount_ += c.amount_; return *this; }
    Currency& operator-=(const Currency& c) { amount_ -= c.amount_; return *this; }
    Currency& operator*=(double x) { amount_ *= x; return *this; }
    Currency& operator/=(double x) { amount_ /= x; return *this; }
    Currency& operator%=(double x) { amount_ *= x / 100; return *this; }

private:
    long amount_;   // number of cents
};

Currency operator+(const Currency& a, const Currency& b);
Currency operator-(const Currency& a, const Currency& b);
Currency operator*(const Currency& c, double x);
Currency operator/(const Currency& c, double x);
Currency operator%(const Currency& c, double x);

std::istream& operator>>(std::istream& is, Currency& c);
std::ostream& operator<<(std::ostream& os, const Currency& c);
