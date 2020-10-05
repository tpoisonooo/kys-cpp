## 如何在 linux 上编译
本作支持 linux 32/64 bit 环境，以本机示范如何编译。

### 编译环境
本机 OS 是 x86 ubuntu18.04，菜鸡配置，没有显卡要求i

```
$ uname -a
Linux BJ-DZ0103437 5.4.0-47-generic #51~18.04.1-Ubuntu SMP Sat Sep 5 14:35:50 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
```

### 下载依赖

#### 基础依赖
这几个是 bass（播放语音用的） 运行依赖
```
sudo  apt-get install libgtkd-3-dev  libglade2-dev
```

以下是游戏本身依赖
```
sudo  apt-get install libsdl2-image-dev  libsdl2-ttf-dev  liblua5.3-dev libminizip-dev libsdl2-dev
sudo apt-get install libopencc-dev
sudo apt-get install libfmt-dev libsqlite3-dev
```

### 代码魔改

### build

### 资源链接和运行

