#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

class Object {
public:
    Object(int num) : num(num) {
        cout << "construct Object\naddress: " << this << endl;
        throw std::runtime_error("exception in constructor");
    }

    virtual ~Object() {
        cout << "destory Object\naddress: " << this << endl;
    }

public:
    static void* operator new(std::size_t size) {
        cout << "object reload new operator" << endl;
        return ::operator new(size);
    }

    static void operator delete(void* ptr) {
        cout << "object reload delete operator" << endl;
        return ::operator delete(ptr);
    }

    static void* operator new(std::size_t size, void* pMemory) {
        cout << "placement new, "
            << "address: " << pMemory << endl;
        return pMemory;
    }

    static void operator delete(void* ptr, void* pMemory) {
        cout << "placement delete, "
            << "object ptr address: " << ptr << ", " << "memory address: " << pMemory << endl;
        // 其他有关内存池的回收操作
    }

private:
    int num{ 42 };
};

void* operator new(std::size_t size) {
    auto handler = std::get_new_handler();
    for(int try_count = 3; try_count; try_count--) {
        auto ptr = std::malloc(size);
        if(ptr) {
            cout << "new size: " << size << "\naddress: " << ptr << endl;
            return ptr;
        }
        if(handler) {
            handler();
        }
    }
    throw std::bad_alloc();
}

void operator delete(void* ptr) {
    cout << "delete memory address: " << ptr << endl;
    free(ptr);
}

int main() {
    // std::set_new_handler([]() {
    //     cout << "new operator failed, need to handle!\n";
    // });
    // auto ptr = new Object(13);
    // delete(ptr);


    char* buff = new char[1024];
    try {
        auto ptr2 = new(buff) Object(13);
        ptr2->~Object();
    }
    catch(std::exception& e) {
        cout << "catch exception: " << e.what() << endl;
    }

    delete[] buff;

    return 0;
}