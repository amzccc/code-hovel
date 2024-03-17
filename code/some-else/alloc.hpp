// 二级的内存分配器
// 大于128字节使用malloc(),小于128字节使用内存池管理
#include <cstdlib>
#include <new>

namespace mystl {

enum {Align = 8};
enum {SmallObj = 128};
enum {FREELISTSIZE = 16};
enum {BLOCK_SIZE = 20};

struct FreeList
    {
        FreeList* next;
    };

class alloc {
    private:
    static char* free_head;      //freelist head
    static char* free_end;       //freelist end
    static size_t heap_size;      //memory pool size

    static FreeList* free_list[FREELISTSIZE];      //一条16个节点的自由链表

    public:
    static void* allocate (size_t n);
    static void deallocate(void* p, size_t n);
    static void* reallocate (void* p, size_t old_size, size_t new_size);

    private:
    static size_t M_round_up (size_t bytes);
    static void* M_refill (size_t n);
    static char* M_chunk_alloc (size_t size, size_t &nblk);
    static size_t M_freelist_index (size_t bytes);

};

char* alloc::free_head = nullptr;
char* alloc::free_end = nullptr;
size_t alloc::heap_size = 0;

FreeList* alloc::free_list[FREELISTSIZE] = {
    nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr
};

void* alloc::allocate (size_t n) {
    if (n > static_cast<size_t>(SmallObj)) {
        return malloc(n);
    }
    FreeList* my_free_list;
    my_free_list = free_list[M_freelist_index(n)];
    FreeList* result = my_free_list;
    if(result == nullptr) { //当前指针没有分配内存池，就填充
        void* res = M_refill(M_round_up(n));
        return res;
    }
    my_free_list = result->next;    //指向下一个块
    return result;
}

//释放p指向的空间，实际上是把p指向的空间重新放回内存池中，而不是释放掉
void alloc::deallocate(void* p, size_t n) {
    if(n > static_cast<size_t>(SmallObj)) {
        free(p);
        return ;
    }
    FreeList* q = reinterpret_cast<FreeList*> (p);
    FreeList* my_free_list = free_list[M_freelist_index(n)];
    q->next = my_free_list;
    my_free_list = q;
}

void* alloc::reallocate (void* p, size_t old_size, size_t new_size) {
    deallocate(p, old_size);
    p = allocate(new_size);
    return p;
}

size_t alloc::M_round_up (size_t bytes) {
    bytes = (bytes >> 3);
    return (bytes << 3) + 8;
}

//第几个节点
size_t alloc::M_freelist_index(size_t bytes) {
    return (bytes >> 3);
}

//填充free_list
void* alloc::M_refill(size_t n) {
    size_t nblock = BLOCK_SIZE;
    char* c = M_chunk_alloc (n, nblock);
    //得到内存后划分区块
    FreeList* my_free_list;
    FreeList* result, *cur, *next;
    if (nblock == 1) {
        return c;
    }
    my_free_list = free_list[M_freelist_index(n)];
    result = (FreeList*)c;
    my_free_list = next = (FreeList*)(c + n);
    for(size_t i = 1; ; ++i) {
        cur = next;
        next = (FreeList*)((char*)next + n);
        if(nblock - 1 == i) {
            cur->next = nullptr;
            break;
        }
        else {
            cur->next = next;
        }
    }
    return result;
}

char* alloc::M_chunk_alloc (size_t size, size_t &nblk) {
    size_t need_bytes = size * nblk;
    size_t pool_bytes = free_end - free_head;
    char* result;
    //如果内存池中剩余的大小满足需求，就返回它
    if(pool_bytes >= need_bytes) {
        result = free_head;
        free_head = result + need_bytes;
        return result;
    }
    //如果不能完全满足需求，但至少能分配一个或以上
    else if(pool_bytes >= size){
        nblk = pool_bytes / size;
        need_bytes = size * nblk;
        result = free_head;
        free_head += need_bytes;
        return result;
    }
    //一个也不能满足
    else {
        //如果内存池还有剩余，把剩下的都加入到对应的free_list中
        if(pool_bytes > 0) {
            FreeList* my_free_list = free_list[M_freelist_index(pool_bytes)];    
            ((FreeList*)free_head)->next = my_free_list;
            my_free_list = (FreeList*)free_head;
        }
        //再申请heap空间
        size_t bytes_to_get = need_bytes << 1;
        free_head = (char*)malloc(bytes_to_get);
        if(!free_head) {
            //内存不够用了，查看是否有未用的区块
            FreeList* my_free_list, *p;
            for(size_t i = size; i <= SmallObj; i += Align) {
                my_free_list = free_list[M_freelist_index(i)];
                p = my_free_list;
                if(p) {
                    my_free_list = p->next;
                    free_head = (char*)p;
                    free_end = free_head + i;
                    return M_chunk_alloc (size, nblk);
                }
            }
            //山穷水尽了就只能报错了
            free_end = nullptr;
            throw std::bad_alloc();
        }
        free_end = free_head + bytes_to_get;
        heap_size += bytes_to_get;
        return M_chunk_alloc(size, nblk);
    }
}
}