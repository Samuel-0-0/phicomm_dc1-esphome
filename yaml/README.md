# 固件编译及刷固件方法
### 0、前置条件
请确认已经按照[本方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)连接好TTL工具，并且TTL工具驱动已经正确安装。

### 1、下载固件配置文件（下方右键另存为）
> ####   固件版本定义：
> - [dc1_homeassistant_api](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_api.yaml)：用于通过API接入Home Assistant
> - [dc1_homeassistant_mqtt](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_mqtt.yaml)：用于通过MQTT接入Home Assistant
> - [dc1_mqtt](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_mqtt.yaml)：用于接入其他mqtt平台

> 下载配置文件依赖[secrets.yaml](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/secrets.yaml)，如果已配置此文件，修改合并到自己的secrets.yaml
```
配置文件对应版本更新历史

dc1_homeassistant_api:
v2019.12.26.001：
修复bug，感谢老妖对驱动和其他的测试及修复

v2019.12.02.001：
迁移到1.14版本ESPHome

v2019.03.28.002：
编译固件前请更新esphome及esphome-core到最新版本！
1、优化按钮，解决重启问题


dc1_homeassistant_mqtt:
v2019.12.26.001：
修复bug

v2019.12.02.001：
迁移到1.14版本ESPHome

v2019.08.26.001：
感谢[yaming116](https://github.com/yaming116) QQ昵称：花开堪折枝的mqtt版本修改及测试，使用mqtt时禁止使用api！


```

### 2、修改固件配置文件
按照自己的情况修改配置文件中substitutions内的参数。其他的配置如果不是很了解就不要去修改了。
按照自己的情况修改配置文件secrets.yaml内的参数。

### 3、关于captive portal（AP配网模式）说明
太多人问这个问题了，其实自己去esphome官方文档看一下就知道工作原理了。
只有当无法连接预设的wifi的情况下，才会显示AP热点，然后你去连这个热点，默认密码1234567890，
连上后打开192.168.4.1, 重新配置好wifi， 接着重启设备，设备重启后会连接新配置的wifi

### 4、搭建编译环境及刷固件

- Windows

打开CMD，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）

```
# 安装 esphome
pip install esphome
# 找到安装目录，进入esphome/components
如：C:\Users\Administrator\AppData\Local\Programs\Python\Python37\Lib\site-packages\esphome\components
新建cat9554文件夹
下载[__init__.py](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/__init__.py) [cat9554.cpp](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/cat9554.cpp) [cat9554.h](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/cat9554.h)
将文件放入新建的文件夹中
# 进入配置文件所在目录
cd xxxxx
# 编译固件(xxxxx.yaml为你的配置文件名字)
esphome xxxxx.yaml compile
# 刷固件（线刷或者OTA皆可）
esphome xxxxx.yaml upload
```
- MacOS

打开终端，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）

```
# 安装 esphome
pip install esphome
# 找到安装目录，进入esphome/components
新建cat9554文件夹
下载[__init__.py](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/__init__.py) [cat9554.cpp](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/cat9554.cpp) [cat9554.h](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/esphome/components/cat9554/cat9554.h)
将文件放入新建的文件夹中
# 进入配置文件所在目录
cd xxxxx
# 编译固件(xxxxx.yaml为你的配置文件名字)
esphome xxxxx.yaml compile
# 刷固件（线刷或者OTA皆可）
esphome xxxxx.yaml upload
```

- Linux

> 与MacOS类似，参考MacOS的方法

- Docker

**临时使用方法**

> 注意！多个配置文件放在一起除了改文件名还要改device_name: XXX，不能出现device_name重复的现象
1. 安装[官方esphome容器](https://hub.docker.com/r/esphome/esphome)，方法参考其上
2. 如果是在容器宿主机终端，执行如下命令：
```
docker exec -it 容器名字 /bin/bash -c "mkdir /usr/src/app/esphome/components/cat9554 && cd /usr/src/app/esphome/components/cat9554 && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/__init__.py && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.cpp && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.h"

```

如果是在容器终端，执行：
```
mkdir /usr/src/app/esphome/components/cat9554 && cd /usr/src/app/esphome/components/cat9554 && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/__init__.py && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.cpp && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.h

```
3. 打开浏览器，输入容器IP地址:6052，如：192.168.1.10:6052

### 5、设备OTA更名操作

如果设备需要改名字，通常的做法是重新线刷，这样很麻烦，作者提供了新的方式。
找到配置文件wifi中
```
#需要修改名字的时候，启用，OTA后禁用
#use_address: ota.local
```
删除#use_address: ota.local前的#号，将ota修改成原来老的device_name，
将device_name改成新的名字，这样OTA一次，之后在use_address前重新加上#号即可

