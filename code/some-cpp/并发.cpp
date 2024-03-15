#include <future>           //提供保存线程结果的库
#include <thread>           //线程库
#include <chrono>
#include <random>
#include <iostream>
#include <queue>
#include <exception>
#include <string>
#include <stdexcept>
#include <functional>
#include <utility>
#include <mutex>            //提供线程锁
#include <atomic>           //原子性
#include <condition_variable>       //条件变量库，配合metex使用，达到唤醒某个线程的目的
using namespace std;
/*
    future async(std::launch::async, F func, args...)   启动func，形成一个异步任务
    future async(std::launch::defferred, F func, args...)   形成一个推迟任务，当调用wait()或get()时，该任务被同步调用
    future async(F func, args...)       携带一个发射策略，如果不能立即执行就推迟调用

    Class future<> 用来表现某一操作的成果，可能是个返回值或者一个异常 被管理于一个shared state内
    shared state可被async()或std::packaged_task或promise创建

    future 提供一个接口，允许我们等待后台操作完成而不需返回结果。
    f.wait()  强制启动该线程并等待直到操作完成；
    还有下面两个函数并不强制启动线程
    f.wait_for(std::chrono::seconds(n));    等待n秒，
    f.wait_until(std::system_clock() + std::chrono::minutes(n))     等待直到某个时间点
    这两个函数会返回三种状态：
    future_status::deferred     当前线程尚未启动
    future_status::timeout      在设定的时间结束时当前线程操作还没做完
    future_status::ready        

    class std::promise 临时持有一个值或一个异常，可持有一个shared state，如果这个shared state持有一个值或异常，就说它是ready。

    std::packaged_task<> 可同时持有目标函数及其state
        // double compute(int x, int y);
        // std::packaged_task<double(int, int)> task(computer);    //创建一个任务
        // std::future<double> f = task.get_future();          //得到它的future
        // ...
        // task(7, 5);     //在一个分离的线程中执行这个任务    只需要这个任务的结果，不关心它的过程，让它到后台执行结果返回就行
        // ...
        // double res = f.get();       //获得任务结果
    
    class std::thread   用来启动和表现线程
    thread t(f, ...)        创建一个线程对象，表示f(可能带有实参)启动于一个线程中，或抛出异常std::system_error
    t.joinable()    若t有一个关联线程，就返回true
    t.join()        等待该线程完成任务
    t.detach()      解除t和线程之间的关联，并让线程继续运行
    t.get_id()      如果joinable就返回一个独一无二的std::thread::id,否则返回std::thread::id()

    <thread>库中声明了一个命名空间std::this_thread,提供线程专属的global函数
    this_thread::get_id()           获得当前线程ID
    this_thread::sleep_for(dur)     阻塞dur时间段
    this_thread::sleep_until()tp    阻塞到时间点tp
    this_thread::yield（）          建议释放控制并重新调度，让下一个线程能够执行

    Mutex和lock
                        mutex       recursive_mutex         timed_mutex         recursive_timed_mutex
    lock()                          捕获mutex（若无捕获则阻塞）
    try_lock()                      捕获mutex（若无捕获则返回false）
    unlock()                        解除被锁定的mutex
    try_lock_for()       -              -                       试着在时间段内捕获一个lock
    try_lock_until()     -              -                       试着捕获一个lock直到某个时间点
    多个lock             否             是（同一线程）            否                   是（同一线程）

    class std::lock_guard   提供一个接口，确保锁在离开作用域时总会被释放
        lock_guard lg(m)     
        lock_guard lg(m, adopt_lock)    adopt_lock作为初始化第二实参，确保任何情况下mutex离开作用域会被解锁

    class std::unique_lock  为一个不一定得锁定的mutex提供一个lock_guard

    clas std::condition_variable 用来唤醒一个或多个等待某特定条件的线程
        cv.notify_one()     唤醒一个线程
        cv.notify_all()     唤醒所有线程
        cv.wait(ul)         使用unique lock ul来等待通知
        cv.wait(ul, pred)   使用unique lock ul来等待通知，并且pred在一次苏醒后结果为true
        cv.wait_for(ul, timepoint)
        cv.wait_for(ul, duration, pred)     等待期限为duration，或pred在一次苏醒后结果为true
        cv.wait_until(ul, timepoint)
        cv.wait_until(ul, timepoint, pred)
*/

int doSomething(char c) {
    //用c作为种子生成随机数
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    //随机一段时间后打印
    for(int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}

int func1() {
    return doSomething('.');
}

int func2() {
    return doSomething('+');
}

int queryNumber() {
    cout << "read number: ";
    int num;
    cin.clear();
    cin >> num;

    if(!cin) {
        throw runtime_error("no number read");
    }
    return num;
}

void doSomething_s(char c, shared_future<int> f) {
    try {
        int num = f.get();
        for(int i = 0; i < num; i++) {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch (const exception &e) {
        cerr << "EXCEPTION in thread " << this_thread::get_id() << ": " << e.what() << endl;
    }
}

void doSomething_t(int num, char c) {
    try {
        default_random_engine dre(42 * c);
        uniform_int_distribution<int> id(10, 1000);
        for(int i = 0; i < num; i++) {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }
    }
    //确保没有异常离开线程并结束程序
    catch (const exception &e) {
        cerr << "THREAD-EXCEPTION (thread " << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch(...) {
        cerr << "THREAD-EXCEPTION (thread " << this_thread::get_id() << ")" << endl;
    }
}

void doSomething_p(promise<string> &p) {
    try {
        //读取字符，如果是x抛出异常
        std::cout << "read char('x for exception): ";
        char c = cin.get();
        if(c == 'x') {
            throw runtime_error(string("char ") + c + " read");
        }
        string s = string("char ") + c + " processed";
        p.set_value(move(s));       //存储结果
    }
    catch (...) {
        p.set_exception(current_exception());       //存储异常
    }
}

mutex printMutex;       //设置一个互斥锁，保证输出和打印同步
void print(const string &s) {
    lock_guard<mutex> lg(printMutex);       //锁住线程,并保证离开作用域时解锁
    for(char c: s) {
        cout.put(c);
    }
    cout << endl;
}

bool readyFlag;
mutex readyFlagMutex;
void thread1() {
    //做一些thread2需要的准备
    lock_guard<mutex> lg(readyFlagMutex);
    readyFlag = true;
}

void thread2() {
    //等待readyFlag置为true
    {
        unique_lock<mutex> ul(readyFlagMutex);
        while(!readyFlag) {
            ul.unlock();
            this_thread::yield();
            this_thread::sleep_for(chrono::milliseconds(100));
            ul.lock();
        }
    }//释放锁
    //执行thread1之后的操作
}

mutex readyMutex;
condition_variable readyCondVar;
void thread3() {
    //执行thread4前的准备
    cout << "<return>" << endl;
    cin.get();
    //发出信号表明thread3已经准备了一个条件
    {
        lock_guard<mutex> lg(readyMutex);
        readyFlag = true;
    }//释放锁
    readyCondVar.notify_one();
}

void thread4() {
    //等待thread3 ready
    {
        unique_lock<mutex> ul(readyMutex);
        readyCondVar.wait(ul, []{return readyFlag;});
    }//释放锁
    //执行thread3结束后的操作
    cout << "done" << endl;
}

queue<int> q;
mutex queueMutex;
condition_variable queueCondVar;
void provider (int val) {
    //将不同的值写入队列
    for(int i = 0; i < 6; i++) {
        {
            lock_guard<mutex> lg(queueMutex);
            q.push(val + i);
        }
        queueCondVar.notify_one();
        this_thread::sleep_for(chrono::milliseconds(val));
    }
}

void consumer(int num) {
    //弹出值
    while(true) {
        int val;
        {
            unique_lock<mutex> ul(queueMutex);
            queueCondVar.wait(ul, []{return !q.empty();});
            val = q.front();
            q.pop();
        }
        cout << "consumer " << num << ": " << val << endl;
    }
}

long atomic_data;
atomic<bool> atomic_readyFlag(false);
void atomic_provider() {
    cout << "<return>" << endl;
    cin.get();
    atomic_data = 42;
    atomic_readyFlag.store(true);
}

void atomic_consumer() {
    while(!atomic_readyFlag.load()) {
        cout.put('.').flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\nvalue: " << atomic_data << endl;
}

int main()
{
    cout << "starting func1() in background" << " and func2() in foreground: " << endl;
    //启动func1异步
    future<int> result1(async(func1));
    int result2 = func2();      //调用func2同步
    //打印结果（等到func1结束并把结果添加到result2）
    int result = result1.get() + result2;
    cout << "\nresult of func1() + func2(): " << result << endl;
    cout << "--------------------------------------------\n";
    cout << "starting 2 operations asynchronously" << endl;
    //在后台开启两个循环，打印.或+
    auto f1 = async([] {doSomething('.');});
    auto f2 = async([] {doSomething('+');});
    //如果至少一个后台任务在运行
    if(f1.wait_for(chrono::seconds(0)) != future_status::deferred || 
        f2.wait_for(chrono::seconds(0)) != future_status::deferred) {
        //等待至少一个循环结束
        while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
                f2.wait_for(chrono::seconds(0)) != future_status::ready) {
            this_thread::yield;         //提示重新调度到下个线程
        }
    }
    cout.put('\n').flush();
    //等待所有循环结束并处理异常
    try {
        f1.get();
        f2.get();
    }
    catch(const exception &e) {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout << "\ndone" << endl;
    cout << "---------------------------------------\n";
    //使用shared_future: 一般来说，一个future只能处理其结果一次，但有些时候需要对future进行多次get
    try {
        //创建一个线程查询数字
        shared_future<int> sf = async(queryNumber);
        //开始三个线程，在一个循环中每个都处理这个数字
        auto sf1 = async(launch::async, doSomething_s, '.', sf);
        auto sf2 = async(launch::async, doSomething_s, '+', sf);
        auto sf3 = async(launch::async, doSomething_s, '*', sf);
    }
    catch (const exception &e) {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout <<"\ndone" << endl;
    cout << "-----------------------------------------\n";
    //async()和future是高级接口，c++还提供底层接口thread和promise
    //thread
    try {
        thread t1(doSomething_t, 5, '.');   //在一个分离的线程里打印五个点
        cout << "-started fg thread " << t1.get_id() << endl;
        //在其他后台线程中打印其他字符
        for(int i = 0; i < 5; i++) {
            thread t(doSomething_t, 10, 'a' + i);
            cout << "-detach started bg thread " << t.get_id() << endl;
            t.detach();     //卸离线程，放到后台，是危险的，要小心使用
        }
        cin.get(); 
        cout << "-join fg thread " << t1.get_id() << endl;
        t1.join();  //等待t1结束
        cout << endl;
    }
    catch (const exception &e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << "----------------------------------------------\n";
    try {
        promise<string> p;
        thread tp(doSomething_p, ref(p));
        tp.detach();
        //创建一个future处理结果
        future<string> f(p.get_future());
        cout << "result: " << f.get() << endl;
    }
    catch (const exception &e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    catch (...) {
        cerr << "EXCEPTION " << endl;
    }
    cout << endl;
    cout << "--------------------------------------\n";
    auto lg1 = async(launch::async, print, "Hello form a first thread");
    auto lg2 = async(launch::async, print, "Hello form a second thread");
    print("Hello form the main thread");
    cout << endl;
    auto thread3_with_cond = async(launch::async, thread3);
    auto thread4_with_cond = async(launch::async, thread4);
    cout << endl;
    //三个生产者 100+， 300+， 500+
    auto p1 = async(launch::async, provider, 100);
    auto p2 = async(launch::async, provider, 300);
    auto p3 = async(launch::async, provider, 500);
    //两个消费者打印值
    auto c1 = async(launch::async, consumer, 1);
    auto c2 = async(launch::async, consumer, 2);
    cout << endl;
    auto p = async(launch::async, atomic_provider);
    auto c = async(launch::async, atomic_consumer);
}