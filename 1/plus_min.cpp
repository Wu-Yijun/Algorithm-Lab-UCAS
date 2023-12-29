// #1A. A+B problem (advanced)
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <iostream>
#include <vector>

using namespace std;

class LargeDigit {
  public:
    size_t Read(FILE* __stream);
    size_t Print(FILE* __stream) const;
    // return num of digits
    // return -1 if error
    size_t GetLength() const;

    bool GetSign() const { return is_positive_; }
    bool SetSign(bool is_positive) { return is_positive_ = is_positive; }
    bool TurnSign() { return is_positive_ = !is_positive_; }

    LargeDigit operator+(const LargeDigit& r_num) const;
    LargeDigit operator-(const LargeDigit& r_num) const;

    // when out of boundry, return 0;
    int operator[](size_t pos) const;
    // when out of boundry, increase size
    void SetDigit(size_t pos, int num);
    // push back
    void PushBack(int num) { return digits_.push_back(num); }

  private:
    // compare abslute value
    bool AbsLarger(const LargeDigit& r_num) const;
    // returning sign positive
    LargeDigit AbsAdd(const LargeDigit& r_num) const;
    // returning sign = if l_num is larger than r
    LargeDigit AbsSub(const LargeDigit& r_num) const;

    bool is_positive_;
    vector<int> digits_;
};

int main() {
    LargeDigit a, b;
    a.Read(stdin);
    b.Read(stdin);
    (a + b).Print(stdout);
    return 0;
}

size_t LargeDigit::Read(FILE* __stream) {
    digits_.clear();
    int c;
    while (isspace(c = fgetc(__stream))) {
    }
    is_positive_ = true;
    do {
        if (c == '-')
            is_positive_ = false;
        if ('0' <= c && c <= '9')
            digits_.insert(digits_.begin(), c - '0');
    } while (!isspace(c = fgetc(__stream)));
    return digits_.size();
}
size_t LargeDigit::GetLength() const {
    int len = 0;
    for (size_t i = 0; i < digits_.size(); ++i)
        if (digits_[i] != 0)
            len = i + 1;
    return len;
}
size_t LargeDigit::Print(FILE* __stream) const {
    size_t len = GetLength();
    if (len == 0)
        fputc('0', __stream);
    else if (!is_positive_)  // there is no "-0"
        fputc('-', __stream);
    for (size_t i = 0; i < len; ++i) fputc('0' + digits_[len - 1 - i], __stream);
    return len;
}

LargeDigit LargeDigit::operator+(const LargeDigit& r_num) const {
    if (is_positive_ == r_num.GetSign()) {
        auto res = AbsAdd(r_num);
        res.SetSign(is_positive_);
        return res;
    } else {
        auto res = AbsSub(r_num);
        if (!is_positive_) {
            res.TurnSign();
        }
        return res;
    }
}
LargeDigit LargeDigit::operator-(const LargeDigit& r_num) const {
    if (is_positive_ == r_num.GetSign()) {
        auto res = AbsSub(r_num);
        if (!is_positive_) {
            res.TurnSign();
        }
        return res;
    } else {
        auto res = AbsAdd(r_num);
        res.SetSign(is_positive_);
        return res;
    }
}
int LargeDigit::operator[](size_t pos) const {
    if (pos < 0)
        return 0;
    if (pos < digits_.size())
        return digits_[pos];
    else
        return 0;
}
void LargeDigit::SetDigit(size_t pos, int num) {
    if (pos < 0)
        return;
    if (pos < digits_.size()) {
        digits_[pos] = num;
    } else {
        digits_.resize(digits_.size() * 2);
        SetDigit(pos, num);
    }
}

bool LargeDigit::AbsLarger(const LargeDigit& r_num) const {
    if (size_t i = GetLength(), j = r_num.GetLength(); j != i) {
        return i > j;
    } else {
        for (size_t k = 0; k < i; ++k)
            if (operator[](i - 1 - k) > r_num[i - 1 - k])
                return true;
            else if (operator[](i - 1 - k) < r_num[i - 1 - k])
                return false;
        return false;
    }
}
LargeDigit LargeDigit::AbsAdd(const LargeDigit& r_num) const {
    size_t len = std::max(GetLength(), r_num.GetLength());
    int carry = 0;
    LargeDigit res;
    res.SetSign(is_positive_);
    for (size_t i = 0; i < len; ++i) {
        int k = operator[](i) + r_num[i] + carry;
        res.PushBack(k % 10);
        carry = k / 10;
    }
    if (carry)
        res.PushBack(carry);
    return res;
}
LargeDigit LargeDigit::AbsSub(const LargeDigit& r_num) const {
    const LargeDigit *l_p, *r_p;
    LargeDigit res;
    if (AbsLarger(r_num)) {
        l_p = this;
        r_p = &r_num;
        res.SetSign(true);
    } else {
        l_p = &r_num;
        r_p = this;
        res.SetSign(false);
    }
    const auto& l = *l_p;
    const auto& r = *r_p;
    size_t len = l.GetLength();
    int borrow = 0;
    for (size_t i = 0; i < len; ++i) {
        int k = l[i] - r[i] - borrow;
        if (k < 0) {
            k = k + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.PushBack(k);
    }
    return res;
}