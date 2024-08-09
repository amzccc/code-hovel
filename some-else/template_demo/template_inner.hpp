/*********************************************************************************
 * @file		template_inner.hpp
 * @brief
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-08-06 21:05
 **********************************************************************************/
#ifndef TEMPLATE_INNER_H__
#define TEMPLATE_INNER_H__

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>

using namespace std;

enum Kind {
    bird,
    cat,
    dog
};

enum Voice {
    jojo,
    mimi,
    miao,
    wang,
};

enum Leg {
    two,
    four,
};

namespace inner {

class Animal {
public:
    virtual void property() = 0;
};

struct Dog : public Animal {
    string name{ "big yellow" };
    string job{ "home guard" };

    void property() override {
        cout << "name: " << name << '\t';
        cout << "job: " << job << endl;
    }
};

struct Cat  : public Animal {
    string name{ "mimi" };
    int lazy{ 10 };

    void property() override {
        cout << "name: " << name << '\t';
        cout << "lazy: " << lazy << endl;
    }
};

struct Bird : public Animal {
    vector<string> feather{ "red", "green", "blue" };

    void property() override {
        cout << "feather color: ";
        for(auto& color : feather) {
            cout << color << ", ";
        }
        cout << endl;
    }
};

template<Kind K>
constexpr bool is_animal = K == Kind::bird || K == Kind::cat || K == Kind::dog;

template<Kind K, Leg L>
constexpr bool is_valid_choice = K != Kind::bird || L != Leg::four;

template<Kind K, Voice V, Leg L,
    typename Choice = std::enable_if_t<is_animal<K>,
    std::conditional_t<K == Kind::bird, Bird,
    std::conditional_t<K == Kind::cat, Cat, Dog>>>,
    typename = std::enable_if_t<is_valid_choice<K, L>>>
struct Selection { };


template<Kind K, Voice V, typename Choice>
struct Selection<K, V, Leg::two, Choice> : public Choice {
    int tag = 2;
    int leg_count{ 2 };
    string voice{ "jojo" };

    void property() override {
        Choice::property();
        cout << "leg count: " << leg_count << '\t'
            << "voice: " << voice << endl;
    }
};

template<typename Choice>
struct Selection<Kind::cat, Voice::miao, Leg::four, Choice> : public Choice {
    int tag = 3;
    int leg_count{ 4 };
    string kind{ "cat" };
    string voice{ "miao" };

    void property() override {
        Choice::property();
        cout << "leg count: " << leg_count << '\t'
            << "kind: " << kind << "\t"
            << "voice: " << voice << endl;
    }
};

template<Leg L, typename Choice>
struct Selection<Kind::cat, Voice::mimi, L, Choice> : public Choice {
    int tag = 4;
    int leg_count{ 4 };
    string kind{ "cat" };
    string voice{ "mimi" };

    void property() override {
        Choice::property();
        cout << "leg count: " << leg_count << '\t'
            << "kind: " << kind << "\t"
            << "voice: " << voice << endl;
    }
};

template<Leg L, typename Choice>
struct Selection<Kind::dog, Voice::wang, L, Choice> : public Choice {
    int tag = 5;
    int leg_count{ 4 };
    string kind{ "dog" };
    string voice{ "wang" };

    void property() override {
        Choice::property();
        cout << "leg count: " << leg_count << '\t'
            << "kind: " << kind << "\t"
            << "voice: " << voice << endl;
    }
};

template<Voice V>
constexpr bool is_valid_voice = V == Voice::jojo || V == Voice::miao || V == Voice::mimi || V == Voice::wang;

template<Leg L>
constexpr bool is_valid_leg = L == Leg::two || L == Leg::four;

template<Kind K, Voice V, Leg L,
    typename Choice = std::enable_if_t<is_valid_voice<V>&& is_valid_leg<L>, Selection<K, V, L>>>
struct SelectInner : public Choice {
    void property() {
        Choice::property();
        cout << "size: " << sizeof(*this) << endl;
    }
};

}

#endif // !template_inner.hpp