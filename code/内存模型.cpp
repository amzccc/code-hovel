#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

using namespace std;

/**
 *@brief 一致性：保证变量在cpu中的执行顺序和代码中的位置顺序是否一致
 *      同步：保证变量的读写具有稳定的先后顺序，即一对同步操作保证了在写操作后，再将值同步给其他线程的读操作 
 *
 *      现代C++保证了变量间执行顺序的同步一致性
 *      即，保证了任何后面的指令操作不能被优化到memory_order_acquire之前；任何前面的指令不能被优化到memory_order_release之后
 */

 // 保证内存一致性
void test_seq_cst() {
    atomic<bool> flag_x = false;
    atomic<bool> flag_y = false;
    thread t2([&]() {
            while(!flag_y.load(memory_order_seq_cst));          // 3
            assert(flag_x.load(memory_order_seq_cst) == true);  // 4
        });
    thread t1([&]() {
            flag_x.store(true, memory_order_seq_cst);           // 1
            flag_y.store(true, memory_order_seq_cst);           // 2
        });
    t2.join();
    t1.join();
}

// 不保证一致性
void test_seq_relaxed() {
    atomic<bool> flag_x = false;
    atomic<bool> flag_y = false;
    thread t2([&]() {
            while(!flag_y.load(memory_order_relaxed));          // 3
            assert(flag_x.load(memory_order_seq_cst) == true);  // 4
        });
    thread t1([&]() {
            flag_x.store(true, memory_order_relaxed);           // 1
            flag_y.store(true, memory_order_relaxed);           // 2
        });
    t2.join();
    t1.join();
}

// 保证同步，即2会在3之前执行，也就保证了flag_x在断言处一定为true
void test_acquire_release() {
    atomic<bool> flag_x = false;
    atomic<bool> flag_y = false;
    thread t2([&]() {
            while(!flag_y.load(memory_order_acquire));          // 3
            assert(flag_x.load(memory_order_relaxed) == true);  // 4
        });
    thread t1([&]() {
            flag_x.store(true, memory_order_relaxed);           // 1
            flag_y.store(true, memory_order_release);           // 2
        });
    t2.join();
    t1.join();
}

int main() {
    test_seq_cst();

    test_seq_relaxed();

    test_acquire_release();

    return 0;
}