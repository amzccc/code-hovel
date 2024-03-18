[toc]
# redis基本操作
## 数据库操作
redis默认有16个数据库，编号0~15，默认访问0号数据库。
操作|说明
|:-|:-|
select 数据库编号|选择指定数据库
dbsize|获取当前数据库键值对数量
flushdb|清空当前数据库
flushall|清空所有数据库
save|将数据保存到磁盘
bgsave|将数据异步保存至磁盘
lastsave|获取最后一次成功保存的unix时间

## 通用数据操作
操作范围为当前数据库
操作|说明
|:-|:-|
keys 格式|查看符合指定格式的key，*为通配符
exists key1[key2 ...]|查看是否存在一至多个指定的key
type key | 按key查看value的数据类型
del key1[key2 ...]|按key删除一至多个键值对
rename key1 key2 | 重命名key1为key2，如果k2存在，其值会被覆盖掉
renamenx key1 key2 | key2不存在时重命名key1
move key 数据库编号 | 按key将一个键值对移动到指定数据库
copy key1 key2 | 将key1的值拷贝给key2

## 字符串  
redis的key都是字符串类型，value可以有多种类型。
**value是字符串类型的操作**
操作| 说明
|-|-|
set key value | 添加/修改一个键值对
get key | 按key获取value
mset key1 value1 [key2 value2 ...] | 添加/修改一至多个键值对
mget key1 [key2 ...] | 按key获取一至多个value
append key value | 在原有value后追加内容
strlen key | 查看字符串长度
getrange key startindex endindex | 获取范围[startindex, endindex]的子串。(index从0开始，-n表示倒数第n个字符)
set key value nx (setnx key value) | 仅在key不存在时，添加一个键值对
set key value xx | 仅在key已存在时，修改一个键值对
set key value get (getset key value)|修改一个键值对并返回原值，原值不存在则返回null
msetnx key1 value1 [key2 value2 ...]|批量setnx

**如果字符串的内容是数值**
操作|说明
|-|-|
incr key | key不存在就创建key 1，key存在就使value加1
incrby key 整数值 |按key使value增加给定的整数值
incrbyfloat key 小数值 | 按key使value增长给定的小数值
decr key|value减1
decrby key 数值 | value减少对应数值

**临时键值对**
生存时间time to live（ttl），指键值对距离被删除的剩余秒数。
如果重新set，ttl将被重置。默认是永久的。
操作|说明
|-|-|
expire key 秒数 |　设定一个生存时间
ttl key| 查看生存时间的剩余秒数
pexpire key 毫秒数 | 设定一个毫秒数的ttl

**以下操作仅支持字符串**
操作|说明
-|-
set key value ex 秒数 （setex key 秒数 value）| set + expire
set key value pe 毫秒数 （psetex key 毫秒数 value） | set + pexpire
set key value exat unix秒| 设置一个unix秒的过期时刻
set key value pxat unix毫秒 | 设置一个unix毫秒的过期时刻
set key value keepttl | set时不重置ttl

## 散列表
key-field-value,键-字段-值
-|-|-
-|-|-
key|field1|value1
<br>|field2|value2
<br>|...
key2|field1|value1
<br>|field2|value2
<br>|...

操作|说明
-|-
hset key field1 value1 [field2 value2 ...]|添加/修改一个键与一至多对字段和值
hget key field| 按key和field获取一对value
hmget key field1 [field2 ...]| 按key和field获取一至多对value
hgetall key |　按key获取全部的field-value
hdel key field1 [field2] | 删除一至多对field-value
hsetnx key field value |　仅在field不存在时添加一对field-value
hkeys key|查看一个key中的所有field
hvals key | 查看一个散列表中所有的value
hlen key | 统计一个散列表中有多少对field-value
hexists key field | 查看一个field是否存在
hstrlen key field | 按key和field查看value的长度
**如果value是数值**
操作和字符串中value是数值部分的类似,指令在前面加个h

## 列表
key - value0 - value1 - ...,键-有序的值列队
-|-|-|-
-|-|-|-
key1|value0|value1|...
key2|value0|value1|...
...|

操作|说明
-|-
rpush key value0 [value1 ...] | 在列表右侧加入一至多个值
lpush key [value1 ...] value 0 | 在列表左侧加入一至多个值
rpushx key value0 [value1 ...] | 仅当列表存在时,在列表右侧加入一至多个值
lpushx key [value1 ...] value 0 | 仅当列表存在时,在列表左侧加入一至多个值
rpop key [数量] | 从列表右侧弹出(指定数量的)值,全部弹出后,key也会被删除
lpop key [数量]| 从列表左侧弹出(指定数量的)值,全部弹出后,key也会被删除
lset key *index value | 修改指定位置的值
linsert key before/after 定位value value | 在定位value前/后插入一个值
lindex key *index |按索引查看值
lrange key *startindex *endindex | 查看范围的值
llen key | 查看队列长度
lrem key 数量 value | 删除指定值,数量为正代表从左侧开始删除,数量为负代表从右侧开始删除
ltrim key *startindex * endindex | 将列表修建到给定的范围

## 集合
key - stringX, stringY, ...,键-无序的不重复的成员
-|-|-|-
-|-|-|-
key1|stringX|stringY|...
key2|stringY|stringZ|...
...|

操作|说明
-|-
sadd key stringX [stringY ...]| 添加一至多个成员
srem key stringX [stringY ...] | 删除一至多个成员
scard key | 返回成员数量
sismember key string | 查看是否存在指定成员
smismember key stringX [stringY ...] | 批量查看是否存在指定成员
smembers key | 查看集合中所有成员
srandmember key [数量] | 随机查看指定数量的成员
spop key [数量] | 随机取出指定数量的成员
smove key1 key2 string | 将指定成员从集合1移到集合2
sinter key1 [key2 ...] | 查看给定集合的交集
sinterstore newkey key1 [key2 ...] | 存储给定集合的交集到一个新的集合
sunion key1 [key2 ...] | 查看给定集合的并集
sunionstore newkey key1 [key2 ...] | 存储给定集合的并集到一个新的集合
sdiff key1 [key2 ...] | 查看给定集合的差集
sdiffstore newkey key1 [key2 ...] | 存储给定集合的差集到一个新的集合

## 有序集合(ZSet)
key - score1:stringX, score2:stringY, ...
键 - 按分数排序的不重复的成员
-|-|-|-
--|--|--|--
key1 | score1 | socre2 |...
 <br>|stringX | stringY | ...
 key2 | score1 | score2 | ...
 <br>| stringY | stringZ | ...
分数是float64的浮点数,且可以重复.

操作|说明
-|-
zadd key [nx/xx] [gt/lt] [ch] [incr] score1 stringX [score2 stringY ...] | 添加一至多个成员.<br> nx:仅当成员不存在时添加成员; <br>xx:仅当成员存在时修改成员; <br>lt(less than): <br>仅当分数低于原有分数时才更新分数;  <br>gt(greater than):仅当分数高于原有分数时才更新分数;<br>~*nx不可以与lt/gt一起使用~ <br> ch:返回变更的成员数量; <br> ~选择incr时,只能操作一个分数-成员对.~ <br>incr:累加分数
zrem key stringX [stringY ...] | 删除多个成员
zcount key minScore maxScore | 返回指定分数区间内的成员数量. <br>支持开区间:分数前加"("; <br>支持无穷大:"-inf","+inf".
zscore key string | 查看成员分数,成员不存在时返回null
zmscore key stringX [stringY ...] | 批量查看成员分数
zcard key | 查看成员数量
zincrby key 数值 string | 将指定成员的分数增加给定的数值

**按区间操作**
操作|说明
-|-
zrange key start end [byscore/bylex] [rev] [limit 偏移量 查看数量] [withscores] | 查看指定分数区间内的成员. <br>byscore:按分数升序排序,支持开区间和无穷;<br> bylex:(分数相同时)按成员字符排序;<br> ~*bylex指定的字符串区间,需要指定开闭,"[string"表示闭区间,"(string"表示开区间.~ <br> ~*bylex支持选取到开始或结束,"-"表示开始,"+"表示结束.~ <br>rev:反转. <br>limit用于指定查看的范围,仅在开启byscore/bylex时可用;<br>withscores:带分数.
zrangestore newkey key start end [nyscore/bylex] [rev] [limit 偏移量 查看数量]| 按区间存储到一个新的key
zlexcount key startString endString | 查看指定字符串区间内的成员数量
zremrangebylex key startString endString | 删除指定字符串区间内的成员
zremrangebyscore key minScore maxScore | 删除指定分数区间内的成员
zrank key string|查看成员升序排名.
zrevrank key string | 查看成员降序排名
zremrangebyrank | 删除指定排名区间内的成员
**交集、并集、差集**
操作|说明
-|-
zinter key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores]| 查看给定集合的交集。<br>weights: 依次为每个集合的分数设置权重，默认为1；<br>aggregate:新分数的计算方法，默认为sum；<br> ~新分数=aggregate(集合1中该成员的分数×权重1，集合2中该成员函数×分数2,...)~
zinterstore newkey key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores] | 存储给定集合的交集
zunion key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores] | 查看给定集合的并集
zunionstore newkey key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores] | 存储给定集合的并集
zdiff key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores] | 查看给定集合的差集
zdiffstore newkey key的数量 key1 [key2 ...] [weights 权重1 [权重2 ...]] [aggregate sum/min/max] [withscores] | 存储给定集合的差集

## 遍历
操作| 说明
-|-
scan 游标 [match 格式] [count 游标] [type 指定类型]| 遍历一定数量的key。<br>游标：开始遍历的位置，从0开始，scan命令将返回遍历结束位置，如果返回0，说明已经遍历完成。<br>match:指定key的格式，*为通配符；<br>count:指定遍历啊结束的游标,默认是0；<br>type:指定遍历的类型。
**特定键值对的遍历**
操作|说明
-|-
hscan key 游标 [match 格式] [count 游标] | 遍历算列表中的字段和值
sscan key 游标 [match 格式] [count 游标] | 遍历指定集合中的成员
zscan key 游标 [match 格式] [count 游标] | 遍历指定有序集合中的成员与分数

## 事务
操作|说明
-|-
**multi**|开启事务
**exec**|执行事务
**discard** | 回滚事务

**监视操作**
操作|说明
-|-
watch key1 [key2 ...] | 按key开始监视键值对。<br> ~需要在开启事务前启动。~ <br> ~如果被监视的键值对在事务exec或discard之前被事务之外的操作改动，事务将被discard。~
unwatch | 停止监视。 <br> ~exec或discard会自动调用unwatch.~












