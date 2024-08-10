#include <iostream>
#include <random>
#include <coroutine>
#include <array>

using namespace std;

enum class Status : char {
    start,
    correct,
    less,
    greater,
};

class Judge {
public:
    Judge(int answer, int min, int max) : m_answer(answer), min(min), max(max) { }

    Status operator()() {
        if(m_guess == m_answer) {
            stat = Status::correct;
        }
        else if(m_guess < m_answer) {
            stat = Status::less;
        }
        else if(m_guess > m_answer) {
            stat = Status::greater;
        }
        return stat;
    }

    Status stat = Status::start;
    int min;
    int max;
    int m_guess = -1;

private:
    int m_answer;
};

class CoRoutine {
public:
    struct promise_type {
        promise_type(Judge& j) : judge(j) { }

        suspend_never initial_suspend() {
            return {};
        }

        CoRoutine get_return_object() {
            return CoRoutine(coroutine_handle<promise_type>::from_promise(*this));
        }

        suspend_never final_suspend() noexcept {
            return {};
        }

        suspend_always yield_value(int val) {
            judge.m_guess = val;
            return {};
        }

        void return_void() { }

        void unhandled_exception() { }

    private:
        Judge& judge;
    };

public:
    CoRoutine(const coroutine_handle<promise_type>& handle) : m_handle(handle) { }

    coroutine_handle<promise_type> m_handle;
};

CoRoutine guess(Judge& judge) {
    std::array<int, 2> range{ judge.min, judge.max };
    int number;
    while(judge.stat != Status::correct) {
       if(judge.stat == Status::less) {
            range[0] = number + 1;
        }
        else if(judge.stat == Status::greater) {
            range[1] = number - 1;
        }
        number = (range[0] + range[1]) / 2;
        cout << "guess number: " << number << endl;
        co_yield number;
    }
    co_return;
}

int main() {
    random_device seed;
    default_random_engine eng(seed());
    int answer = uniform_int_distribution<int>(1, 100)(eng);
    cout << "guess a number between 1 and 100.\n";
    Judge judge(answer, 1, 100);
    auto coroutine = guess(judge);
    while(true) {
        auto result = judge();
        if(result == Status::correct) {
            cout << "you're right!" << endl;
            coroutine.m_handle.destroy();
            break;
        }
        else if(result == Status::less) {
            cout << "miss, less than answer.\n";
        }
        else if(result == Status::greater) {
            cout << "miss, greater than answer.\n";
        }
        coroutine.m_handle.resume();
    }

    return 0;
}