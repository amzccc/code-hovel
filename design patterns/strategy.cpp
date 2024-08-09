#include <iostream>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

class DiscountStrategy {
public:
    virtual void discount() = 0;
};

class TenPercent : public DiscountStrategy {
public:
    void discount() override {
        cout << "10% discount!\n";
    }
};

class TwentyPercent : public DiscountStrategy {
public:
    void discount() override {
        cout << "20% discount!\n";
    }
};

class ThirtyPercent : public DiscountStrategy {
public:
    void discount() override {
        cout << "30% discount!\n";
    }
};

class Supermarket {
public:
    Supermarket() = default;
    
    void setDiscount(const std::shared_ptr<DiscountStrategy>& strategy) {
        m_discount = strategy;
    }
    
    void discount() {
        m_discount->discount();
    }

private:
    std::shared_ptr<DiscountStrategy> m_discount{ nullptr };
};

int main() {
    Supermarket market;
    market.setDiscount(std::make_shared<TenPercent>());
    market.discount();
    market.setDiscount(std::make_shared<TwentyPercent>());
    market.discount();
    market.setDiscount(std::make_shared<ThirtyPercent>());
    market.discount();
    
    return 0;
}