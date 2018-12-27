// frac.h

#ifndef frac_h
#define frac_h

#include <bits/stdc++.h>
using namespace std;

namespace Frac {
    typedef long long LL;
    
    struct frac {
        LL num, den;
        bool sgn;
        
        frac(LL num = 1, LL den = 1);
        virtual ~frac() {};
        long double getValue() const;
        void setValue(LL, LL);
        frac rev();
        
        void simplify();
        void input();
        friend ostream& operator<<(ostream&, frac&);
        frac operator+(const frac&) const;
        frac operator-(const frac&) const;
        frac operator*(const frac&) const;
        frac operator/(frac) const;
        
        bool operator==(const frac&) const;
        bool operator<(const frac&) const;
    };
    
    LL gcd(LL a, LL b) { return (b == 0) ? a : gcd(b, a % b); }
    
    void frac::input() {
        string s;
        cin >> s;
        bool flag = 0;
        int sgn = 1;
        LL _num = 0, _den = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '-') sgn ^= 1;
            if (s[i] == '/') flag = 1;
            if (!flag) {
                if (s[i] >= '0' && s[i] <= '9')
                    _num = _num * 10 + s[i] - '0';
            } else {
                if (s[i] >= '0' && s[i] <= '9')
                    _den = _den * 10 + s[i] - '0';
            }
        }
        if (_den == 0) _den = 1;
        this->num = _num, this->den = _den, this->sgn = sgn;
    }
    
    ostream& operator<<(ostream& os, frac& f) {
        f.simplify();
        if (f.sgn == 0) {
            if (f.den == 1)
                os << "-" << f.num;
            else
                os << "-" << f.num << "/" << f.den;
        } else {
            if (f.den == 1)
                os << "" << f.num;
            else
                os << "" << f.num << "/" << f.den;
        }
        return os;
    }
    
    frac::frac(LL _num, LL _den) : sgn(1) {
        assert(_den != 0);
        
        this->num = abs(_num), this->den = abs(_den);
        if (_num * _den < 0) this->sgn = 0;
        this->simplify();
    }
    
    long double frac::getValue() const { return 1.0 * this->num / this->den; }
    void frac::setValue(LL _num, LL _den) { *this = frac(_num, _den); }
    
    frac frac::rev() {
        frac ret;
        ret.num = den, ret.den = num, ret.sgn = sgn;
        return ret;
    }
    
    void frac::simplify() {
        LL g = gcd(num, den);
        num /= g, den /= g;
    }
    
    frac frac::operator+(const frac& f) const {
        frac ret;
        if (sgn == f.sgn) {
            ret.num = num * f.den + den * f.num;
            ret.den = den * f.den;
            ret.sgn = sgn;
        } else {
            ret.num = abs(num * f.den - den * f.num);
            ret.den = abs(den * f.den);
            if (this->getValue() > f.getValue())
                ret.sgn = sgn;
            else
                ret.sgn = f.sgn;
        }
        ret.simplify();
        return ret;
    }
    
    frac frac::operator-(const frac& f) const {
        frac ret;
        if (sgn == f.sgn) {
            ret.num = abs(num * f.den - den * f.num);
            ret.den = abs(den * f.den);
            if (getValue() >= f.getValue())
                ret.sgn = 1;
            else
                ret.sgn = 0;
        } else {
            ret.num = num * f.den + den * f.num;
            ret.den = den * f.den;
            ret.sgn = sgn;
        }
        ret.simplify();
        return ret;
    }
    
    frac frac::operator*(const frac& f) const {
        frac ret;
        ret.num = num * f.num;
        ret.den = den * f.den;
        if (sgn == f.sgn)
            ret.sgn = 1;
        else
            ret.sgn = 0;
        ret.simplify();
        return ret;
    }
    
    frac frac::operator/(frac f) const {
        frac ret, r;
        r = f.rev();
        ret = *this * r;
        ret.simplify();
        return ret;
    }
    
    bool frac::operator==(const frac& f) const {
        if (sgn != f.sgn) return 0;
        if (getValue() != f.getValue()) return 0;
        return 1;
    }
    
    bool frac::operator<(const frac& f) const {
        if (sgn != f.sgn) {
            if (sgn) return 1;
            else return 0;
        } else {
            if (getValue() < f.getValue()) {
                if (sgn) return 1;
                else return 0;
            } else if (getValue() > f.getValue()) {
                if (sgn) return 0;
                else return 1;
            } else
                return 0;
        }
    }
}

#endif /* frac_h */
