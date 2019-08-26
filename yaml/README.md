# 固件编译及刷固件方法
### 0、前置条件
请确认已经按照[本方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)连接好TTL工具，并且TTL工具驱动已经正确安装。

### 1、下载固件配置文件（下方右键另存为）
> ####   固件版本定义：
> - [dc1_homeassistant](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant.yaml)：相对稳定版本，用于接入Home Assistant
> - [dc1_homeassistant_test](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_test.yaml)：测试版本，用于接入Home Assistant
> - dc1_mqtt：相对稳定版本，用于接入mqtt平台
> - dc1_mqtt_test：测试版本，用于接入mqtt平台


```
配置文件对应版本更新历史

dc1_homeassistant：
v2019.03.28.002：
编译固件前请更新esphome及esphome-core到最新版本！
1、优化按钮，解决重启问题

dc1_homeassistant_test：

dc1_mqtt：
v2019.08.26.001
感谢[yaming116](https://github.com/yaming116) QQ昵称：花开堪折枝的mqtt版本修改及测试，使用mqtt时禁止使用api！

dc1_mqtt_test：无

```

### 2、修改固件配置文件
按照自己的情况修改配置文件中substitutions内的参数。其他的配置如果不是很了解就不要去修改了。

```
#--------------------- 只需要改这下面的内容 ---------------------
substitutions:
  #WiFi芯片版本，型号中带B的为csm64f02_b，不带B的为csm64f02
  board_model: csm64f02
  #设备名称(多个dc1改成不一样的)
  device_name: phicomm_dc1
  #WiFi_SSID名称
  wifi_ssid: '2L'
  #WiFi密码
  wifi_password: '1122334455'
  #如果SSID是隐藏的，设置为true
  wifi_fast_connect: 'false'
  #WiFi离线多久后重启设备，秒s/分钟min/小时h，不需要此功能设置为0s
  wifi_reboot_timeout: 600s
  #OTA密码
  ota_password: '123456'
  #与客户端（如Home Assistant）失去连接多久后重启设备，秒s/分钟min/小时h，不需要此功能设置为0s
  api_reboot_timeout: 600s
  #电量统计的数据更新时间，秒s/分钟min/小时h
  cse7766_update_interval: 1s
#--------------------- 只需要改这上面的内容 ---------------------
```

关于WiFi模组版本的选择，请查看下图，找出自己对应的芯片版本即可。
看红色箭头的位置，带B的为csm64f02_b，不带B的为csm64f02

![image](https://github.com/Samuel-0-0/phicomm_dc1-esphome/blob/master/yaml/%E6%A8%A1%E7%BB%84%E5%9E%8B%E5%8F%B7%E9%80%89%E6%8B%A9.jpg?raw=true)

### 3、搭建编译环境及刷固件
**因platformio需要python2.7的环境，所以python2.7为必须。**
- Windows

[点此查看](https://github.com/Samuel-0-0/esphome-tools-dc1/tree/master)

- MacOS

> MacOS自带python2.7，所以无需再安装。

1. [从此处下载esphome](https://github.com/Samuel-0-0/esphome)（打开页面后，右上角「 Clone or download 」 → 「 Download ZIP 」），下载后解压缩。

2. 打开终端，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）

```
# 进入esphome的setup.py所在目录
cd xxxxx
# 编译 esphome
# 如提示权限不足，命令前加上sudo
python setup.py build
# 安装 esphome
python setup.py install
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
> 注意！多个配置文件放在一起除了改文件名还要改device_name: XXX，不能出现device_name重复的现象
1. 安装[官方esphome容器](https://hub.docker.com/r/esphome/esphome)
2. 执行如下命令：
```
docker exec -it esphome_container_name /bin/bash -c "cd /esphome_config_path&&git clone https://github.com/Samuel-0-0/esphome.git&&cd esphome&&python setup.py build&&python setup.py install&&rm -rf /esphome_config_path/esphome"

注意！看清楚上面的命令行，有3处地方需要根据实际情况修改，
a. esphome_container_name  改成实际的容器名字
b. esphome_config_path   改成实际的配置文件夹路径，共2处！！
```
3. 打开浏览器，输入容器IP地址:6052，如：192.168.1.10:6052


