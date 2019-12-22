# 固件编译及刷固件方法
### 0、前置条件
请确认已经按照[本方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)连接好TTL工具，并且TTL工具驱动已经正确安装。

### 1、下载固件配置文件（下方右键另存为）
> ####   固件版本定义：
> - [dc1_homeassistant_api](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_api.yaml)：用于通过API接入Home Assistant
> - [dc1_homeassistant_mqtt](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_mqtt.yaml)：用于通过MQTT接入Home Assistant
> - [dc1_mqtt](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_mqtt.yaml)：用于接入其他mqtt平台


```
配置文件对应版本更新历史

dc1_homeassistant_api:

v2019.12.02.001：
迁移到1.14版本ESPHome

v2019.03.28.002：
编译固件前请更新esphome及esphome-core到最新版本！
1、优化按钮，解决重启问题


dc1_homeassistant_mqtt:

v2019.12.02.001：
迁移到1.14版本ESPHome

v2019.08.26.001：
感谢[yaming116](https://github.com/yaming116) QQ昵称：花开堪折枝的mqtt版本修改及测试，使用mqtt时禁止使用api！


```

### 2、修改固件配置文件
按照自己的情况修改配置文件中substitutions内的参数。其他的配置如果不是很了解就不要去修改了。


### 3、搭建编译环境及刷固件

- Windows

[点此查看](https://github.com/Samuel-0-0/esphome-tools-dc1/tree/master)

- MacOS

**以下方法暂时不可用，请勿使用**

打开终端，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）

```
# 安装 esphome
pip install esphome
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
1. 安装[官方esphome容器](https://hub.docker.com/r/esphome/esphome)
```
# 如果不使用线刷把`--device=/dev/ttyUSB0` 去掉
docker run --net=host --device=/dev/ttyUSB0 -v docker/esphome/config:/config --name esphome -td  esphome/esphome 
```
2. 执行如下命令：
```
docker exec -it esphome /bin/bash -c "mkdir /usr/src/app/esphome/components/cat9554 && cd /usr/src/app/esphome/components/cat9554 && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/__init__.py && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.cpp && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.h"

```
3. 打开浏览器，输入容器IP地址:6052，如：192.168.1.10:6052

- Github Actions
1. Github Actions提供了自动编译固件的功能, 直接去Actions标签下最新Build Firmware里的Artifacts下载bin.
2. 使用esptools, esphome自带的web server等工具刷写,OTA升级

配网功能在home assistant版本里已加入, 不用更改yaml, 刷机完成后等待1分钟进入配网模式.

如果要自定义yaml文件, 请先fork这个项目, 然后更改yaml, commit更改会触发编译, 首次fork可能要去actions里面同意使用actions条款.
