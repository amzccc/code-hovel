#include <iostream>
#include <map>
#include <queue>
#include <vector>


void bubble_sort(int arr[], int length);
void select_sort(int arr[], int length);
void insert_sort(int arr[], int length);
void quick_sort(int arr[], int left, int right);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void mergesort(int arr[], int left, int right);
void heap_sort(int arr[], int length);
void heapify(int arr[], int left, int right);
void radix_sort(int arr[],int length);
int maxbit(int arr[], int length);
int main()      
{
    //测试数组
    using std::cout;
    using std::endl;
    const int size = 10;
    int arr[size] = {8, 7, 4, 2, 1, 5, 6, 9, 0, 3};
    //打印原数组
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
    
    //测试函数
    bubble_sort(arr, size);       //冒泡
    //select_sort(arr, size);       //选择
    //insert_sort(arr, size);       //插入
    //quick_sort(arr, 0, 9);      //快排
    //merge_sort(arr, 0, 9);      //归并 递归形式
    //mergesort(arr, 0, 9);       //归并 迭代形式
    //heap_sort(arr,size);
    //radix_sort(arr,size);

    //打印排序后数组
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}


//-------------------------------------------------------------------------------------------
//冒泡排序
/*
冒泡排序的时间复杂度是O(N²),空间复杂度为O(1)
冒泡排序具有稳定性。
*/
void bubble_sort(int arr[], int length)    
{
    for(int i = 0; i < length; ++i)      //遍历数组，每次结束将最大元素依次放到最后
    {
        for(int j = 0; j < length - i - 1; ++j)     //开始冒泡，如果相邻前一个元素大于后一个就交换   
        {
            if(arr[j] > arr[j + 1])
            {
                //int temp = arr[j];
                //arr[j] = arr[j + 1];
                //arr[j + 1] = temp;
                
                //异或运算符实现交换两数    ##注意两数不能相等##
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
            }
        }
    }
}   
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
//选择排序
/*
选择排序时间复杂度为O(N²)；空间复杂度为O(1)
选择排序不具备稳定性
*/
void select_sort(int arr[], int length)
{
    for(int i = 0; i < length; i++)     //循环遍历数组，每次遍历中的最小元素放到前面
    {
        int k = i;  //初始化k，用于记录最小元素下标
        //每次遍历都选择将最小值的下标传递给k
        for (int j = i + 1; j < length; j++)
        {
            if (arr[k] > arr[j])
                k = j;
        }
        //遍历完成后，将最小元素与当前数组最前面元素交换
        int temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
    }
}
//-------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
//插入排序
/*
插入排序时间复杂度为O(N²),空间复杂度为O(1)
插入排序具备稳定性
*/
void insert_sort(int arr[], int length)
{   
    for(int i = 0; i < length; i++)    
    {   
        int key = arr[i];    //记录待插入值   
        int j = i - 1;       
        while(j >= 0 && (arr[j] > key))    
        {   
            arr[j + 1] = arr[j];
            j--;
        }   
        arr[j + 1] = key;  
    }
}
//---------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
//快速排序
/*
快速排序在随机选择基准的优化下，时间复杂度为O(N*logN),空间复杂度为O(logN)
快速排序不具备稳定性
*/
void quick_sort(int arr[], int left, int right)
{   
    if(left >= right)
        return;
    int base = arr[right];  //随机选择基准可以降低O，这个程序演示总选择数组最后一个元素作为基准
    int left_guard = left;
    int right_guard = right;
    while (left_guard <= right_guard)
    {   
        //左右哨兵碰头或数组中只有一个元素，结束循环
        if(left_guard == right_guard)
            break;
        //左侧小于基准就向后走一步
        while(arr[left_guard] < base && left_guard < right_guard)      //选择右侧作为基准时，一定要左侧先开始走
            ++left_guard;
        //右侧大于基准就向前走一步
        while(arr[right_guard] >= base && right_guard > left_guard)
            --right_guard;
        //当左哨兵所在元素大于基准，右哨兵所在元素小于基准时，两个while结束，交换元素
        int temp = arr[left_guard];
        arr[left_guard] = arr[right_guard];
        arr[right_guard] = temp;
    }
    //将基准放到中间
    //由于基准在右侧，左哨兵先走，所以两哨兵碰头时所指向的元素一定是大于基准的
    arr[right] = arr[right_guard];
    arr[right_guard] = base;        //至此数组分为两个区域，左侧小于等于基准，右侧大于基准
    //对子区域继续快排
    quick_sort(arr, left, left_guard - 1);      //左子域
    quick_sort(arr, right_guard + 1, right);    //右子域
}
//---------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
//归并排序
/*
归并排序的时间复杂度为O（N*logN),空间复杂度为O(N)
归并排序具备稳定性
*/
//归并排序利用“分治”的思想，先把数组二分为有序的子数组，再将两子数组中的元素比较后有序放入数组中
//递归形式
void merge_sort(int arr[], int left, int right)
{   
    if(left >= right)
        return;
    int mid = left + (right - left)/2;      //数组从中间分成两部分
    merge_sort(arr, left, mid);     //使左子数组有序
    merge_sort(arr, mid + 1, right);    //使右子数组有序
    merge(arr, left, mid, right);       //合并左右两有序数组
}
void merge(int arr[], int left, int mid, int right)
{
    if(left >= right)
        return;
    const int SIZE = right - left + 1;
    int arr_copy[10];     //准备一个临时数组
    int lbegin = left;      
    int lend = mid;
    int rbegin = mid + 1;
    int rend = right;       //两子数组范围
    int num = 0;        //临时数组下标
    while(lbegin <= lend && rbegin <= rend)
        //三元运算符，将两数组中较小的元素放入临时数组并后移
        arr_copy[num++] = arr[lbegin] <= arr[rbegin]? arr[lbegin++]:arr[rbegin++]; 
    while(lbegin <= lend)       //这个while和下个while将两数组中其中一个剩下的元素继续放入临时数组
        arr_copy[num++] = arr[lbegin++];
    while(rbegin <= rend)
        arr_copy[num++] = arr[rbegin++];
    for(int i = 0; i < SIZE; ++i)       //将临时数组中有序的元素依次拷贝到原数组
        arr[left + i] = arr_copy[i];
}

//迭代形式
void mergesort(int arr[], int left, int right)
{
    if(left >= right)
        return;
    const int SIZE = right - left + 1;
    for(int i = 1; i < SIZE; i *= 2)        //步长i表示每次比较的子数组内元素数
    {
        int lbegin;
        int lend;
        int rbegin;
        int rend;
        int arr_copy[10];
        for(lbegin = left; lbegin < SIZE - i; lbegin = rend)
        {
            rbegin = lend = lbegin +i;      //end - begin等于此次比较的子数组的元素数目
            rend = lend + i;
            //int begin = lbegin;     //保存原数组的起始位置
            if(rend > SIZE)     //右数组尾标如果超出原数组长度就没意义了，上面的rend可能超出长度
                rend = SIZE;    //如果超出就强制置为数组末尾
            int num = 0;        //num是临时数组的下标
            while(lbegin < lend && rbegin < rend)       //下面部分就是merge过程了
                arr_copy[num++] = arr[lbegin] < arr[rbegin]? arr[lbegin++]:arr[rbegin++];
            /*  
            //注释的这段也可以实现merge，但需要多一个记录数组起始位置的参数begin
            while(lbegin < lend)
                arr_copy[num++] = arr[lbegin++];
            while(rbegin < rend)
                arr_copy[num++] = arr[rbegin++];
            for(int j = 0; j < i * 2; j++)
                arr[begin + j] = arr_copy[j];
            */
            while(lbegin < lend)        //左数组剩下的移动到最后，右数组剩下则不动，代码更优
                arr[--rbegin] = arr[--lend];
            while(num > 0)
                arr[--rbegin] = arr_copy[--num];
        }
    }
}
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
//堆排序
/*
堆排序的时间复杂度为O(N*logN),空间复杂度为O(1)
堆排序不具备稳定性
一般升序用大根堆，降序用小根堆
*/
void heap_sort(int arr[], int length)
{   
    //初始化堆
    for (int i = length / 2 - 1; i >= 0; i--)   //堆最后父节点是length/2 -1 
        heapify(arr, i, length - 1);
    
    //将首项与末尾交换，再对前面数组继续堆化
    for(int i = length - 1; i > 0; i--)
    {   
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, 0, i - 1);
    }
}
void heapify(int arr[], int begin, int end)        //大根堆化   从begin位置开始向下堆化
{      
    int headnode = begin;       //父节点   
    int subnode = headnode * 2 + 1;
    while(subnode <= end)
    {
        if((subnode + 1) <= end && arr[subnode + 1] > arr[subnode])     //选择子节点中较大的
            subnode++;
        if(arr[subnode] > arr[headnode])   //如果子节点大于父节点就交换
        {
            int temp = arr[subnode];
            arr[subnode] = arr[headnode];
            arr[headnode] = temp;
            //如果有，继续比较孙子
            headnode = subnode;
            subnode = headnode * 2 + 1;
        }
        else        //父最大就直接返回 
            return;
    }
}
//--------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//桶排序
//桶排序的思想不同于基于比较的01思想，而是根据数据的特殊性对数据进行排序
//基数排序——桶思想的一种
//将数组按照个位数字放入队列中，再倒出；然后按照十位，百位，直到最大位数
void radix_sort(int arr[],int length)
{
    int d = maxbit(arr, length);
    std::queue<int> bocket[10];
    for(int i = 1; i <= d; i *= 10)
    {   
        for(int j = 0; j < length; j++)
            bocket[arr[j] % i].push(arr[j]);
        for(int j = 0; j < length; j++)
        {   
            int num = 0;
            while(!bocket[j].empty())
            {
                arr[num++] = bocket[j].front();
                bocket[j].pop();
            }
        }
    }
}

int maxbit(int arr[], int length)       //计算最高位位数
{
    int maxbt = arr[0];
    for(int i = 1; i < length; i++)
    {
        if(maxbt < arr[i])
            maxbt = arr[i];
    }
    int d = 1;
    while ((maxbt / d) != 0)
    {
        d *= 10;
    }
    d /= 10;
    return d;
}
