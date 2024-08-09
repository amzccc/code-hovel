#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using std::cout;
using std::endl;

std::random_device seed;
std::default_random_engine eng(seed());
std::uniform_int_distribution<int> generator(1, 5);

class Goods;

class GoodsMediator {
public:
    void registerGoods(Goods& goods) {
        m_goodslist.push_back(goods);
    }

    int notify() {
        return generator(eng);
    }

private:
    std::vector<Goods> m_goodslist{};
};

class Goods {
public:
    Goods(GoodsMediator& mediator) : m_mediator(mediator) { 
        mediator.registerGoods(*this);
    }

    virtual void waitEnter() {
        std::cout << "wait for " << m_mediator.notify() << " s\n";;
    }

protected:
    GoodsMediator& m_mediator;
};

class FruitGoods : public Goods {
public:
    FruitGoods(GoodsMediator& mediator) : Goods(mediator) { }
    
    void waitEnter() {
        cout << "fruit: ";
        Goods::waitEnter();
        
    }
};

class ClothesGoods : public Goods {
public:
    ClothesGoods(GoodsMediator& mediator) : Goods(mediator) { }
    
    void waitEnter() {
        cout << "clothes: ";
        Goods::waitEnter();
    }
};

class SeafoodGoods : public Goods {
public:
    SeafoodGoods(GoodsMediator& mediator) : Goods(mediator) { }

    void waitEnter() {
        cout << "seafood: ";
        Goods::waitEnter();
    }
};


int main() {
    GoodsMediator mediator;
    FruitGoods fruit(mediator);
    ClothesGoods clothes(mediator);
    SeafoodGoods seafood(mediator);

    fruit.waitEnter();
    clothes.waitEnter();
    seafood.waitEnter();

    return 0;
}