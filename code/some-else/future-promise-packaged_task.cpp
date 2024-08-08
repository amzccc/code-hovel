#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>

using std::cout;
using std::endl;



int main() {

#if 0   // future
    cout << "call async\n";
    auto startpoint = std::chrono::steady_clock::now();
    std::future<std::chrono::steady_clock::time_point> f = std::async(std::launch::deferred, []() {
        cout << "async execute...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return std::chrono::steady_clock::now();
    });
    cout << "do something else...\n";
    cout << "wait...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto endpoint = f.get();
    auto consumed = std::chrono::duration_cast<std::chrono::milliseconds>(endpoint - startpoint).count();
    cout << "get future, elapsed: " << consumed << "ms.\n";
#endif

#if 0   // promise
    auto task = [](std::promise<int>& promise) {
        cout << "task execute...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        promise.set_value(42);
    };
    std::promise<int> p;
    auto f = p.get_future();
    auto f2 = p.get_future();
    auto startpoint = std::chrono::steady_clock::now();
    task(p);
    cout << "promise value: " << f.get() << endl;
    auto endpoint = std::chrono::steady_clock::now();
    cout << "elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(endpoint - startpoint).count() << "s.\n";
#endif

#if 0   // packaged_task
    std::packaged_task<std::string()> task([]() {
        auto utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return std::ctime(&utc);
    });
    auto f = task.get_future();
    std::jthread t(std::move(task));
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    cout << "main time: \n" << std::ctime(&time);
    cout << "task result:\n" << f.get();
#endif

#if 1   // shared_future
    std::packaged_task<int(int, int)> task([](int a, int b) -> int {
        cout << "calculate...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return a + b;
    });
    
    std::shared_future<int> sf = task.get_future();
    std::shared_future<int> sf2 = sf;
    std::thread t1([](std::shared_future<int> f) {
        int result = f.get();
        cout << "thread 1 get future: " << result << endl;
    }, sf);
    std::thread t2([](std::shared_future<int> f) {
        int result = f.get();
        cout << "thread 2 get future: " << result << endl;
    }, sf);
    std::thread t(std::ref(task), 1, 1);
    std::thread t3([](std::shared_future<int> f) {
        int result = f.get();
        cout << "thread 3 get future: " << result << endl;
    }, sf);
    t.join();
    t1.join();
    t2.join();
    t3.join();
    std::cout << sf2.get() << endl;
#endif

    return 0;
}