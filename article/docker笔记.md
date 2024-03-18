## dock为什么出现
开发的应用总是依赖于特定的配置环境，各种不同的配置环境就会造成移植应用出现障碍。
系统平滑移植、容器虚拟化技术。
可以把原始环境一模一样地复制过来。
## docker理念
一次镜像，处处运行。
**总结**
解决了运行环境和配置问题的软件容器，方便做持续集成并有助于整体发布的容器虚拟化技术。
## 能干嘛
技术职位变化
> coder -> programmer -> software engineer ->DevOps engineer开发+运维

## docker run干了啥
先在本机中寻找镜像，如果找到直接运行，找不到就到远端docker hub拉取，如果能找到，下载镜像到本地再以此镜像为模板生产容器实例运行，如果再找不到，返回失败错误，查不到该镜像

# 操作命令
## 帮助启动类命令
启动docker：systemctl start docker
停止docker：systemctl stop docker
重启docker：systemctl restart docker
查看docker状态：systemctl status docker
开机启动：systemctl enable docker
查看docker概要信息：docker info
查看docker总体帮助文档：docker --help
查看docker命令帮助文档：docker 具体命令 --help
~~遇事不决 --help~~

## 镜像命令
* docker images：列出本机主机上的镜像
> -a: 列出本地所有镜像（含历史映像层）
> -q: 只显示镜像ID

* docker search xxx镜像名：搜索xxx镜像名是否在远端库
> --limit 数字 限制显示几个镜像


* docker pull xxx镜像名：从远端拉取
> 镜像名后加[:TAG]，指定具体版本，不写默认是:latest


* docker system df： 查看镜像/容器/数据卷所占空间

* docker rmi xxx镜像名：删除某个镜像
> docker rmi -f xxx ——强制删除单个镜像
> docker rmi -f 镜像名1:TAG 镜像名2:TAG  ——删除多个镜像
> docker rmi -f $(docker images -qa) ——删除全部镜像 

**docker虚悬镜像**：仓库名、标签名都是<`none`>的镜像，俗称虚悬镜像。

## 容器命令
* 新建+启动容器：docker run [option] image [command] [args...]
> option: 
> --name 指定容器名称
> 
> -d 后台运行容器并返回容器id，即启动守护式容器
> -i 以交互式运行容器，通常与-t同时使用
> -t 为容器重新分配一个伪输入终端，与-i配合使用
> 例如：docker run -it --name=xxx ubuntu /bin/bash
> 
> -P 随机端口映射
> -p 指定端口映射

* 列出所有正在运行的容器：docker ps [options]
> option：
> -a 列出所有运行过的容器和历史上用过的容器
> -l 显示最近创建的容器
> -n num 显示最近创建的num个容器
> -q 静默模式，只显示容器编号

* 退出容器：exit 容器停止 ctrl+p+q 容器不停止

* 启动已停止运行的容器：docker start 容器id或容器名

* 重启容器：docker restart 容器id或容器名

* 停止容器：docker stop 容器id或容器名

* 强制停止容器：docker kill 容器id或容器名

* 删除已停止的容器：docker rm 容器id或容器名

* 启动守护式容器
> docker run -d 容器名
> 有的容器在后台运行时会自动退出，在run后要ps一下确定是否在运行

* 查看容器日志 docker logs 容器id或容器名

* 查看容器内进程 docker top 容器id或容器名

* 查看容器内部细节 docker inspect 容器id或容器名

* **进入正在运行的容器并以命令行运行** docker exec -it 容器id或容器名 [command]
> 还有一个命令 docker attach 容器id
> 区别在于，attach直接进入容器启动命令的终端，不会启动新的进程，用exit退出，会导致容器的停止；exec是在容器中打开新的终端，并且可以启动新的进程，用exit退出，不会导致容器的停止。推荐使用exec

* 从容器内拷贝文件到主机上 docker cp 容器id:容器内路径 目的主机路径

* 导入和导出容器
> export 导出容器的内容作为一个tar归档文件 
> `docker export 容器id > 文件名.tar `
> import 从tar包中的内容创建一个新的文件系统再导入为镜像 
> `cat 文件名.tar | docker import -镜像用户/镜像名:镜像版本号 `

## docker镜像
镜像是分层的
UnionFS（联合文件系统）:一种分层的、轻量级并且高性能的文件系统，支持对文件系统的修改作为一次提交来一层层的叠加。
**docker镜像加载原理**：
> docker的镜像实际上由一层一层的文件系统组成，也就是UnionFS。
> bootfs主要包含bootloader和kernel，bootloader主要是引导加载kernel，Linux刚启动时会加载bootfs文件系统，再docker镜像的最底层是引导文件系统bootfs。这一层与典型的Linux/Unix系统是一样的，包含boot加载器和内核。当boot加载完成之后整个内核就都在内存中了，此时内存的使用权已由bootfs转交给内核，此时系统也会卸载bootfs。
> rootfs在bootfs之上，包含典型Linux系统中的/dev，/proc，/bin，/etc等标准目录和文件。rootfs就是各种不同的操作系统发行版。

docker的镜像层都是只读的，容器层是可写的。

**docker镜像的commit操作**：
docker commit提交容器副本使之成为一个新的镜像
` docker commit -m="提交信息" -a="作者" 容器id 要创建的目标镜像名:[标签名] `

## 推送到私有库
1. 下载镜像Docker Registry
2. 运行私有库Registry，相当于本地有个私有Docker hub
> `docker run -d -p 5000:5000 -v 宿主机绝对路径:容器内路径 --privileged=true registry`

3. curl验证私服库上有什么镜像
> `curl -XGET http://ip:port/路径 `

4. 将新镜像修改符合私服规范
> `docker tag 镜像名:tag ip:port/镜像名:tag`

5. 修改配置文件使之支持http
> 私服库默认是不支持http的,需要修改/etc/docker/daemon.json
> `{
>   "registry-mirrors": ["加速镜像网址"],
>   "insecure-registries":["ip:port"] 
> }`

6. push推送到私服库
> `docker push ip:port/镜像名:tag`

7. curl验证私服库有什么镜像
8.  pull到本地并运行
> `docker pull ip:port/镜像名:tag`

## 容器数据卷
将docker容器内的数据保存到宿主机的磁盘中
`docker run -it --privileged=ture -v 宿主机内绝对路径:容器内路径 镜像名`
docker容器产生的数据，如果不备份，那么当容器实例删除后，容器内的数据自然也就没有了。
为了能保存数据在docker中，需要使用卷。
**特点**：
* 数据卷可在容器之间共享或重用数据
* 卷中的更改可以直接实时生效
* 数据卷中的更改不会包含在镜像的更新中
* 数据卷的生命周期一直持续到没有容器使用它为止

可以在容器内目录后设置文件的权限,默认是:rw，还可以是:ro(只读)，:wo(只写)
`docker run -it --privileged=ture -v 宿主机内绝对路径:容器内路径:rw 镜像名`

**数据卷的继承**
`docker run -it --privileged=ture --volumes-from 父类 --name 起名 镜像名`

# docker network
docker服务启动后，会创建一个docker的网络，实际上就是创建了一个虚拟网卡，用于和宿主机及容器之间进行通讯。

## docker network命令
`docker network ls`查看docker当前的网络，默认创建了三个网络，bridge、host、none。
`docker network --help` 查看帮助

## 网络模式
bridge: 虚拟网桥，为每个容器分配ip，并将容器连接到docker0。
host: 不会虚拟出自己的网卡和ip，而是使用宿主机的ip和端口。
none: 有独立的network namespace，但是没有进行任何配置，如分配ip，网桥连接，分配veth pair等。
container: 新创建的容器不会创建自己的网卡和ip，而是和一个已有的容器共享。
**使用命令**
`--network bridge`指定，默认使用docker0
`--network host`
`--network none`
`--network container: name或者容器id`

docker容器内部的ip有可能发生改变，这可能存在危险。

### bridge模式
docker在宿主机中虚拟出了一个交换机（或者理解为网桥）docker0，每启动一个容器，就会根据网段分配一个ip地址给容器，称为container-ip，而docker0就是每个容器的默认网关。因为都使用的是docker0这个网桥，所以容器之间就可以通过container-ip直接通信。
`docker run`的时候，没有指定网络模式就会使用默认的bridge，也就是docker0。然后在宿主机中查看网络就可以看到docker0或者自己创建的一大堆虚拟网卡。
网桥docker0为每个虚拟设备都创建一对接口，docker0上的称为**veth**，容器上的叫**eth0**，均是一对一匹配的，类似于交换机，这样的一对接口被称为**veth pair**。

### host模式
不会创建虚拟网卡，而是使用主机的。
host模式下，端口映射不会生效（很好理解，没有虚拟网卡这一层，主机的端口号就是容器的端口号，映射了也没用）
这种情况下，容器的端口会以主机的端口为主，如果重复了，就递增。

### none模式
就是没有网络

### container模式
和一个已有的容器共用一套虚拟网络。

### 自定义网络
如前所述，bridge模式下，容器在启停时ip可能会发生改变，就需要一种方式保证服务始终能被找到。
最好想到的方法就是再创建一个网络，把需要的容器都放到这个网络下，就不会受到其他容器的影响了，实际上就是实现了容器网络的隔离。