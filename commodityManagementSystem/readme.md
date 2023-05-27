# 第六周大作业



## 已完成

1、输入框设置合法性检验；

2、较好的`ui`设计实现，具有良好的组件命名规范，侧边导航栏切换；

3、使用`StockWidget`具有良好的扩展性，方便后面增加页面；

4、实现基本的增删改查操作，功能基本完整；

5、程序结束时注意内存管理，析构时释放防止内存泄漏；

6、数据库采用防注入写法，提高性能；登录时连接数据库，组件间进行地址传递，全部关闭时断开连接；

## 遇到问题及解决办法

```c++
//问题1：
//写信号槽的时候存在问题：无法确定需要哪个重载函数 实例&QSpinBox::valueChanged
//原因是因为	QSpinBox 有两个重载函数
Q_SIGNALS:
    void valueChanged(int);
    void valueChanged(const QString &);
//有两种解决办法( QOverload 和 函数指针)，这里使用了QOverload
	(void)connect(ui.spinBoxOrderPageNum, QOverload<int>::of(&QSpinBox::valueChanged), this, &KOutOrder::calculateTotalPrice);

//问题2
//侧边栏位置偏移的问题
//对于这个问题调试了很多遍，尝试多种布局，但没有从根本上解决。最后的处理办法是，尽量降低视觉上的感官，将那个偏移的位置量尽可能缩小到视觉上发现不了的地步，若老师您有较好的解决办法，希望您可以告知。
//具体位置在kmainwindow.cpp的44行

//问题3
//关于商品图片更换失败的问题
//目前还在尝试别的设计方式来解决


//问题4
//关于历史订单页面数据更新不及时的问题
//在订单页下单之后，数据已经成功加入到数据库中，通过.show()是可以看到的，但是侧边栏点击历史订单页面并不能实时显示，因此我加入了一个按钮实现数据更新。
void KHistoryOrder::onBtnRefreshClicked()
{

	this->m_pHistoryPageTableModel->select();
	ui.tableViewHistoryPage->setModel(this->m_pHistoryPageTableModel);

	this->getTableViewData();
	this->setTableViewData();
}

//问题5
//由于时间问题，第一次上传的是基础版本，功能已基本实现，后面再继续增加、优化功能组件并持续上传更新。

```


