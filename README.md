# SARAPP
## SARApp功能
我在Qt学习中做的小东西，主要功能如下：
1. 包括接收端和发送端两个界面，采用udp组播实现定时收发数据；
2. 在接收端以表格的形式展现收到的数据，采用model/view，并且按照收到的时间作升序降序；
3. 10s内若没有新数据进来，清空所有数据；
4. 做一个自定义滑动开关，控制是否接收数据；
5. 做白天黑夜两种皮肤，实现换肤功能；
6. 具体功能演示见/video/功能演示.mp4

## 参考
样式表参考了一去丶二三里的黑色炫酷：https://blog.csdn.net/chenyijun/article/details/85107853
自定义控件参考了挨踢人啊：https://www.cnblogs.com/itrena/p/5938229.html

## 存在的BUG
1. 自定义滑块开关（接收消息）在有udp数据报过来时切换过快或者无数据进来时切换，会发送一个空报文给model，原因是在isReceiveOrNot槽函数里，当滑块开启时，疏通信号后进行了信号的重发，应该在信号重发前加一个是否有数据报进来的判断。（当然我目前还不会写）
![image](https://user-images.githubusercontent.com/65387291/126066311-4aa21cae-51dd-44eb-8009-7cdf00284b8e.png)
2. 在切换皮肤风格时，自定义滑块会发送变化，虽然开关状态没有变。
3. 具体BUG复现见/video/bug1.mp4和bug2.mp4

## 2021720
解决bug1：        if(this->udpSocket->hasPendingDatagrams())


