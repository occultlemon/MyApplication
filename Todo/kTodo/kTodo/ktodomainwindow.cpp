#include "ktodomainwindow.h"
const static int WPX = 1400;
const static int HPX = 900;

KTodoMainWindow::KTodoMainWindow(IN QWidget* parent, IN KDBConnect* db, QMap<QString, QString> user)
	: QWidget(parent)
{
	ui.setupUi(this);
	//设置用户名显示
	ui.labelUsername->setText(user["username"]);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMinimumSize(WPX, HPX);
	//数据库初始化
	initTodoList();
	//组件初始化
	initModuleTop();
	initModuleMain();
	initModuleLeft();
	initModuleRight();
	initMyHomePage(nullptr);
	ui.groupBoxShowFinished->hide();

}
KTodoMainWindow::~KTodoMainWindow()
{
	//适用迭代器删除存储todo事项和todo分组的存储容器
	for (QList<KTodoItems*>::iterator it = m_listTodoLists.begin(); it != m_listTodoLists.end(); ++it)
	{
		if (m_listTodoLists.size() > 0)
		{
			it = m_listTodoLists.erase(it);
		}
		else
		{
			m_listTodoLists.clear();
			break;	//必须要有，否则仍然会使用这个错误的迭代器，造成报错
		}
	}
	for (QList<KBtnShowGroupTodo*>::iterator it = m_listTodoGroups.begin(); it != m_listTodoGroups.end(); ++it)
	{
		if (m_listTodoGroups.size() > 0)
		{
			it = m_listTodoGroups.erase(it);
		}
		else
		{
			m_listTodoGroups.clear();
			break;
		}
	}
	delete m_pPbnAddGroup;		//添加分组
	delete m_pAddGroupDialog;	//分组弹窗
	delete m_pTimerBoxDeadTime;
	delete m_pTimerBoxNoticeTime;
	delete m_pTimerBoxNewAdd;
	delete m_pIntro;
	delete m_pLocal;
	delete m_pOther;
	delete m_pOverTimeSort;
	delete m_pCreateTimeSort;
	delete m_pFirstSort;
	delete m_pAddGroupAnimation;
}

//鼠标移动
void KTodoMainWindow::mouseMoveEvent(INOUT QMouseEvent* event)
{
	//若鼠标左键被按下
	if (m_isMousePressed == true)
	{
		//鼠标相对于屏幕的位置
		QPoint curMousePoint = event->globalPos() - m_mousePoint;
		//移动主窗体位置
		move(curMousePoint);
	}
}

//鼠标单击
void KTodoMainWindow::mousePressEvent(INOUT QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_mousePoint = event->pos();    //鼠标相对于窗体的位置
		m_isMousePressed = true;        //鼠标按下
		event->accept();
		if (ui.lineEditTodo->text().size() > 0)
		{
			return;
		}
		//中间编辑框
		ui.lineEditTodo->clearFocus();
		ui.lineEditTodo->setPlaceholderText("+点击新建待办");
		ui.lineEditTodo->setStyleSheet("color:rgb(62, 193, 135);");
		//右侧编辑框
		ui.lineEditTodoNameRight->setReadOnly(true);
		ui.lineEditTodoNameRight->setStyleSheet("border:none;");
		//右侧下方的三个组件 单击其他位置收起		这里会导致一个组件互斥引起的地址访问冲突问题  出于时间问题没有设计组件收起
		//ui.groupBoxIntroRight->close();
		//ui.pbnAddIntroRight->setEnabled(true);
		//ui.pbnAddIntroRight->show();
		//ui.groupBoxAddLocalRight->close();
		//ui.pbnAddLocalRight->setEnabled(true);
		//ui.pbnAddLocalRight->show();
		//ui.groupBoxAddOtherRight->close();
		//ui.pbnAddOtherRight->setEnabled(true);
		//ui.pbnAddOtherRight->show();

		//QString introStr = m_pIntro->toHtml();	//描述
		//if (introStr.size() == 0)
		//{
		//	ui.pbnAddIntroRight->setText("添加待办");
		//}
		//else
		//{
		//	ui.pbnAddIntroRight->setText(introStr);
		//}
		//QString localStr = m_pLocal->toHtml();	//地点
		//if (localStr.size() == 0)
		//{
		//	ui.pbnAddLocalRight->setText("添加地点");
		//}
		//else
		//{
		//	ui.pbnAddLocalRight->setText(localStr);
		//}
		//QString otherStr = m_pOther->toHtml();	//备注
		//if (otherStr.size() == 0)
		//{
		//	ui.pbnAddOtherRight->setText("添加备注");
		//}
		//else
		//{
		//	ui.pbnAddOtherRight->setText(otherStr);
		//}
	}
}

void KTodoMainWindow::mouseReleaseEvent(IN QMouseEvent* event)
{
	// 鼠标未按下
	m_isMousePressed = false;
	event->accept();
}

//初始化模块
void KTodoMainWindow::initModuleTop()	//顶部模块
{
	//更多
	(void)connect(ui.pbnMainPageLearnMore, &QPushButton::clicked, this, &KTodoMainWindow::onPbnMainPageLearnMoreClicked);
	ui.pbnMainPageLearnMore->setCursor(QCursor(Qt::PointingHandCursor));
	//注销
	(void)connect(ui.pbnMainPageExit, &QPushButton::clicked, this, &KTodoMainWindow::onPbnMainPageExitClicked);
	ui.pbnMainPageExit->setCursor(QCursor(Qt::PointingHandCursor));
	//最小化
	(void)connect(ui.pbnMainPageMin, &QPushButton::clicked, this, &KTodoMainWindow::onPbnMainPageMinClicked);
	ui.pbnMainPageMin->setCursor(QCursor(Qt::PointingHandCursor));
	//最大化
	(void)connect(ui.pbnMainPageMax, &QPushButton::clicked, this, &KTodoMainWindow::onPbnMainPageMaxClicked);
	ui.pbnMainPageMax->setCursor(QCursor(Qt::PointingHandCursor));
	//关闭
	(void)connect(ui.pbnMainPageCloseAll, &QPushButton::clicked, this, &KTodoMainWindow::onPbnMainPageCloseAllClicked);
	ui.pbnMainPageCloseAll->setCursor(QCursor(Qt::PointingHandCursor));
}

void KTodoMainWindow::initModuleLeft()	//左侧模块
{
	//左侧区域的按钮组件绑定
	//我的首页按钮
	(void)connect(ui.pbnMyHomePage, &QPushButton::clicked, this, [=]()
		{ui.stackedWidgetMidMain->setCurrentIndex(1); ui.labelLittleTitle->setText("我的首页"); initMyHomePage(nullptr); });
	ui.pbnMyHomePage->setCursor(QCursor(Qt::PointingHandCursor));
	//我的待办按钮
	(void)connect(ui.pbnMyTodo, &QPushButton::clicked, this, [=]()
		{ui.stackedWidgetMidMain->setCurrentIndex(0); ui.labelLittleTitle->setText("我的待办"); initMyTodo(m_mapListTodoItems[1], nullptr); ui.groupBoxShowFinished->hide(); });
	ui.pbnMyTodo->setCursor(QCursor(Qt::PointingHandCursor));
	//意见反馈
	(void)connect(ui.pbnFeedback, &QPushButton::clicked, this, [=]()
		{QDesktopServices::openUrl(QUrl("https://f.wps.cn/form-write/LDjnhJov?feedbackother=1", QUrl::TolerantMode)); });
	ui.pbnFeedback->setCursor(QCursor(Qt::PointingHandCursor));

	//初始化添加分组按钮 -- 添加分组按钮总是出现在组别列表区域的下方，为了保持一个相对位置，避免组别太多把按钮挤出去，因此这里进行代码的ui设计
	m_pPbnAddGroup = new QPushButton(QIcon(":/KTodoMainWindow/images/addGroup.png"), "添加分组", this);
	m_pPbnAddGroup->setCursor(QCursor(Qt::PointingHandCursor));		//鼠标形状 手指型
	m_pPbnAddGroup->setStyleSheet("text-align:left; border-radius:10px; padding-left:9px; padding-top:10px;");
	ui.vLayoutGroupLeft->addWidget(m_pPbnAddGroup);
	//添加分组	弹窗
	m_pAddGroupDialog = new KAddGroupDialog(this);
	(void)connect(m_pPbnAddGroup, &QPushButton::clicked, this, &KTodoMainWindow::onPbnAddOneGroupClicked);
	m_pAddGroupAnimation = new QPropertyAnimation(m_pAddGroupDialog, "geometry", this);
	(void)connect(m_pAddGroupDialog, &KAddGroupDialog::addGroup, this, &KTodoMainWindow::addGroup);
	//获取组别数据verticalLayoutMid
	initTodoGroup();
	//更新我的待办名称的数量
	ui.pbnMyTodo->setText(QString("我的待办") + "(" + QString::number(m_mapListTodoItems[1].size()) + ")");
}


void KTodoMainWindow::initModuleMain()	//主模块
{
	//设置默认首页
	ui.stackedWidgetMidMain->setCurrentIndex(1);
	//当前操作的todo事项初始化
	m_pCurrentItems = nullptr;
	//当前操作的todo分组初始化
	m_pCurrentGroups = nullptr;
	//当前选中的组的id；
	m_groupId = -1;
	//组件布局
	//刷新按钮
	(void)connect(ui.pbnRefresh, &QPushButton::clicked, this, &KTodoMainWindow::onPbnRefreshClicked);
	ui.pbnRefresh->setCursor(QCursor(Qt::PointingHandCursor));
	//排序按钮
	QMenu* sort = new QMenu(this);
	ui.pbnSort->setMenu(sort);
	ui.pbnSort->setCursor(QCursor(Qt::PointingHandCursor));
	m_pOverTimeSort = new QAction(QIcon(":/KTodoMainWindow/images/daoqishijian.png"), "到期时间排序", this);
	m_pCreateTimeSort = new QAction(QIcon(":/KTodoMainWindow/images/chuangjianshijian.png"), "创建时间排序  √", this);
	m_pFirstSort = new QAction(QIcon(":/KTodoMainWindow/images/youxianji.png"), "优先级排序", this);
	(void)connect(m_pOverTimeSort, &QAction::triggered, this, &KTodoMainWindow::onPbnOverTimeSortClicked);
	(void)connect(m_pCreateTimeSort, &QAction::triggered, this, &KTodoMainWindow::onPbnCreateTimeSortClicked);
	(void)connect(m_pFirstSort, &QAction::triggered, this, &KTodoMainWindow::onPbnFirstSortClicked);
	sort->addAction(m_pOverTimeSort);
	sort->addAction(m_pCreateTimeSort);
	sort->addAction(m_pFirstSort);
	ui.pbnSort->setStyleSheet("QPushButton::menu-indicator{image:none;}");//取出黑色倒三角 -- 三角没了会多一个边框
	//编辑框
	ui.lineEditTodo->setPlaceholderText("+点击新建待办");
	ui.lineEditTodo->setStyleSheet("color:rgb(62, 193, 135);");
	//编辑框回车新建待办
	(void)connect(ui.lineEditTodo, &QLineEdit::returnPressed, this, &KTodoMainWindow::addTodoReturnPress);

	//我的待办页面的组件隐藏
	ui.groupBoxShowTodo->hide();
	ui.groupBoxShowFinished->hide();
	ui.pbnShowFinished->hide();
	initMyHomePage(nullptr);	//初始化主页
	initMyTodo(m_mapListTodoItems[1], nullptr);		//初始化我的待办页面
	//显示区域的一些组件
	(void)connect(ui.pbnNotArrange, &QPushButton::clicked, this, [=]() {	//未安排
		if (ui.groupBoxNotArrange->isVisible())
			ui.groupBoxNotArrange->hide();
		else
			ui.groupBoxNotArrange->show();
		});
	(void)connect(ui.pbnNextSeven, &QPushButton::clicked, this, [=]() {		//七天
		if (ui.groupBoxNextSeven->isVisible())
			ui.groupBoxNextSeven->hide();
		else
			ui.groupBoxNextSeven->show();
		});
	(void)connect(ui.pbnAfter, &QPushButton::clicked, this, [=]() {			//以后
		if (ui.groupBoxAfter->isVisible())
			ui.groupBoxAfter->hide();
		else
			ui.groupBoxAfter->show();
		});
	(void)connect(ui.pbnOverdue, &QPushButton::clicked, this, [=]() {		//逾期
		if (ui.groupBoxOverdue->isVisible())
			ui.groupBoxOverdue->hide();
		else
			ui.groupBoxOverdue->show();
		});
	(void)connect(ui.pbnShowFinished, &QPushButton::clicked, this, &KTodoMainWindow::onPbnShowFinishedClicked);	//显示已完成
}

void KTodoMainWindow::initModuleRight()	//右侧模块初始化
{
	ui.pbnCloseRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnWriteRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnSaveChangeRight->setCursor(QCursor(Qt::PointingHandCursor));
	m_ifNoticeTime = false;
	m_ifOverTime = false;
	//测试 注掉
	ui.groupBoxRightMain->hide();
	ui.groupBoxRightNull->show();
	m_pIntro = nullptr;
	m_pLocal = nullptr;
	m_pOther = nullptr;
	//时间选择器盒子弹窗
	m_pTimerBoxDeadTime = nullptr;
	m_pTimerBoxDeadTime = new KTimerBox;
	m_pTimerBoxDeadTime->setAttribute(Qt::WA_DeleteOnClose);
	m_pTimerBoxNoticeTime = nullptr;
	m_pTimerBoxNoticeTime = new KTimerBox;
	m_pTimerBoxNoticeTime->setAttribute(Qt::WA_DeleteOnClose);
	//ui组件隐藏
	ui.lineEditTodoNameRight->setReadOnly(true);
	ui.groupBoxIntroRight->hide();
	ui.groupBoxAddLocalRight->hide();
	ui.groupBoxAddOtherRight->hide();
	//ui
	ui.pbnDeadTimeRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnDeadTimeRight->setStyleSheet("#pbnDeadTimeRight::hover{background-color:rgb(244,245,247);}");
	ui.pbnDeadTimeRight->setStyleSheet("text-align:left;");
	ui.pbnSetNoticeRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnSetNoticeRight->setStyleSheet("#pbnSetNoticeRight::hover{background-color:rgb(244,245,247);}");
	ui.pbnSetNoticeRight->setStyleSheet("text-align:left;");
	ui.pbnAddIntroRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnAddIntroRight->setStyleSheet("text-align:left;");
	ui.pbnAddLocalRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnAddLocalRight->setStyleSheet("#pbnAddLocalRight::hover{background-color:rgb(244,245,247);}");
	ui.pbnAddLocalRight->setStyleSheet("text-align:left;");
	ui.pbnAddOtherRight->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnAddOtherRight->setStyleSheet("text-align:left;");


	//右侧的一些connect函数	
	//右侧关闭
	(void)connect(ui.pbnCloseRight, &QPushButton::clicked, this, [=]() {
		ui.groupBoxRightMain->hide(); ui.groupBoxRightNull->show(); });
	//修改todo名称的ui设计
	(void)connect(ui.pbnWriteRight, &QPushButton::clicked, this, [=]() {
		ui.lineEditTodoNameRight->setReadOnly(false); ui.lineEditTodoNameRight->setStyleSheet("border:1px solid black"); });
	//单击到期时间按钮触发
	(void)connect(ui.pbnDeadTimeRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnDeadTimeRightClicked);	//单击事件
	(void)connect(m_pTimerBoxDeadTime, &KTimerBox::signalCloseThis, this, &KTodoMainWindow::closeTimerBoxDeadTime);
	(void)connect(m_pTimerBoxDeadTime, &KTimerBox::signalGetTime, this, &KTodoMainWindow::getDeadTime);
	(void)connect(m_pTimerBoxDeadTime, &KTimerBox::signalPbnOk, this, [=]() {m_ifOverTime = true; });
	//设置提醒日期
	(void)connect(ui.pbnSetNoticeRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnSetNoticeRightClicked);	//单击事件
	(void)connect(m_pTimerBoxNoticeTime, &KTimerBox::signalCloseThis, this, &KTodoMainWindow::closeTimerBoxNoticeTime);
	(void)connect(m_pTimerBoxNoticeTime, &KTimerBox::signalGetTime, this, &KTodoMainWindow::getNoticeTime);
	(void)connect(m_pTimerBoxNoticeTime, &KTimerBox::signalPbnOk, this, [=]() {m_ifNoticeTime = true; });
	//描述
	(void)connect(ui.pbnAddIntroRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnAddIntroRightClicked);
	//地点
	(void)connect(ui.pbnAddLocalRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnAddLocalRightClicked);
	//备注
	(void)connect(ui.pbnAddOtherRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnAddOtherRightClicked);
	//checkbox
	(void)connect(ui.checkBoxTodoNameRight, &QCheckBox::clicked, this, [=]() {m_pCurrentItems->finishCheckBox(); });
	//保存按钮
	(void)connect(ui.pbnSaveChangeRight, &QPushButton::clicked, this, &KTodoMainWindow::onPbnSaveChangeRightClicked);
}

void KTodoMainWindow::initTodoList()		//事项列表
{
	//QVariant 可以保存很多Qt的数据类型
	QVector<QVariant> todoLists;
	QSqlQuery query = this->m_pDatabase->execQuery("select * from todoList", todoLists);
	while (query.next())
	{
		//从数据库获取对应信息
		int id = query.value("id").toInt();							//id
		int groupId = query.value("groupId").toInt();				//组别id
		QDate createTime = query.value("createTime").toDate();		//创建时间
		QString todoName = query.value("todoName").toString();		//事项名称
		int todoLevel = query.value("todoLevel").toInt();			//级别
		QDate overTime = query.value("overTime").toDate();			//结束时间
		int again = query.value("again").toInt();					//重复设置
		QDateTime noticeTime = query.value("noticeTime").toDateTime();	//提醒时间
		QString intro = query.value("intro").toString();			//描述
		QString local = query.value("local").toString();			//地点
		QString other = query.value("other").toString();			//备注
		QString finishPerson = query.value("finishPerson").toString();	//完成人
		bool ifFinish = query.value("ifFinish").toBool();			//是否完成
		QString groupName = query.value("groupName").toString();	//所属的组

		KTodoItems* items = new KTodoItems(id, groupId, todoName, todoLevel, overTime, noticeTime, again, intro, local, other, finishPerson, ifFinish, groupName);

		//两个对于该项item的事件  1、点击这个item在右侧显示详细信息	2、点击复选框，实现已完成-未完成的切换
		(void)connect(items, &KTodoItems::signalCurrentItem, this, &KTodoMainWindow::initItemsDetail);
		(void)connect(items, &KTodoItems::signalChangedCheckBox, this, &KTodoMainWindow::onCheckBoxChanged);

		this->m_listTodoLists.push_back(items);		//所有待办
		this->m_mapListTodoItems[groupId].push_back(items);	//不同群组存储	
		this->m_mapTodoItems[id] = items;
	}

}

void KTodoMainWindow::initTodoGroup()	//事项分组	
{

	QVector<QVariant> todoGroups;
	QSqlQuery query = this->m_pDatabase->execQuery("select * from groupList", todoGroups);
	while (query.next())
	{
		int groupId = query.value("groupId").toInt();
		QString groupName = query.value("groupName").toString();
		int groupCount = query.value("groupCount").toInt();
		m_listGroupIds.push_back(groupId);
		if (groupId != 1)
		{
			KBtnShowGroupTodo* btn = new KBtnShowGroupTodo(groupName, groupId, groupCount);
			//单击哪个群组就更新哪个群组，组件之间互斥
			(void)connect(btn, &KBtnShowGroupTodo::signalBtnClicked, this, &KTodoMainWindow::onGroupTodoClicked);

			btn->initDisplay();	//更新群组后()内的数字
			ui.vLayoutGroupLeft->insertWidget(0, btn);
			//内存容器保存相应
			m_listTodoGroups.push_back(btn);	//保存所有的组别 list
			m_mapTodoGroups[groupId] = btn;		//保存id+list 用map
		}
		else
		{
			KBtnShowGroupTodo* btn = new KBtnShowGroupTodo(groupName, groupId, groupCount, this);
			btn->hide();
			m_listTodoGroups.push_back(btn);
			m_pCurrentGroups = btn;
			m_mapTodoGroups[groupId] = btn;
		}
	}
}

//新建待办
void KTodoMainWindow::addTodoReturnPress()
{
	int currentGroupId = m_pCurrentGroups->getGroupId();	//当前操作的组的组别id
	if (ui.lineEditTodo->text().size() == 0)
	{
		ui.lineEditTodo->clearFocus();
		ui.lineEditTodo->setPlaceholderText("+点击新建代办");
		ui.lineEditTodo->setStyleSheet("color:rgb(4,184,174);border-color:black;");
		return;
	}
	//按下回车则产生新的todoitems
	QString itemName = ui.lineEditTodo->text();
	int itemId = m_listTodoLists.size() + 1;
	KTodoItems* todoItems = new KTodoItems(itemName, itemId);
	todoItems->setGroupName(m_pCurrentGroups->getGroupName());
	todoItems->setGroupId(currentGroupId);
	m_listTodoLists.push_back(todoItems);		//一些存储
	m_mapListTodoItems[currentGroupId].push_back(todoItems);
	m_mapTodoItems[itemId] = todoItems;
	//单击该item 在右侧显示details
	(void)connect(todoItems, &KTodoItems::signalCurrentItem, this, &KTodoMainWindow::initItemsDetail);
	//当复选框被选择，要通知
	(void)connect(todoItems, &KTodoItems::signalChangedCheckBox, this, &KTodoMainWindow::onCheckBoxChanged);
	//添加新事件分情况：在某个分组中  或者 在首页（也就是我的待办 groupid = 1）
	if (currentGroupId == 1 && ui.stackedWidgetMidMain->currentIndex() == 1)
	{
		ui.vBoxNotArrange->insertWidget(0, todoItems);
		ui.lineEditTodo->clear();
		ui.groupBoxNotArrange->show();
		ui.pbnNotArrange->show();
	}
	else
	{
		ui.vBoxShowTodo->insertWidget(0, todoItems);
		ui.lineEditTodo->clear();
		ui.groupBoxShowTodo->show();
		ui.labelPictureHomePage->hide();
		ui.labNotAddHomePage->hide();
	}
	//插库
	QVector<QVariant> addItems;
	QString sqlStr = "insert into todoList(id, groupId, createTime, todoName, finishPerson, ifFinish, groupName) values(?,?,?,?,?,?,?)";
	addItems.push_back(itemId);	//id
	addItems.push_back(m_pCurrentGroups->getGroupId());		//groupid
	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeStr = dateTime.toString("yyyy-MM-dd HH:mm");
	addItems.push_back(dateTimeStr);		//创建时间	格式： 2023-05-22 17:30
	addItems.push_back(itemName);	//事项名称

	//addItems.push_back(m_pCurrentGroups->getGroupName());	//完成人
	addItems.push_back(ui.labelUsername->text());	//完成人
	addItems.push_back(false);	//是否完成
	addItems.push_back(m_pCurrentGroups->getGroupName());	//组别名称

	todoItems->initItemsDisplay(ui.stackedWidgetMidMain->currentIndex() == 1);
	QSqlQuery query = this->m_pDatabase->execQuery(sqlStr, addItems);
	addItems.clear();

	//插库 更新数据
	addItems.push_back(currentGroupId);
	addItems.push_back(currentGroupId);
	int count = m_mapListTodoItems[currentGroupId].size();
	query = this->m_pDatabase->execQuery("update groupList set groupCount = (select count(*) from todoList where groupId=?) where groupId=?", addItems);

	m_pCurrentGroups->setGroupCount(count);
	m_pCurrentGroups->initDisplay();
	ui.pbnMyTodo->setText(QString("我的待办") + "(" + QString::number(m_mapListTodoItems[1].size()) + ")");
}

//初始化我的主页 -- 单击我的主页按钮以后这里进行刷新
void KTodoMainWindow::initMyHomePage(IN KTodoItems* items)
{
	ui.pbnSort->hide();
	if (m_pCurrentGroups != nullptr)
	{
		m_pCurrentGroups->changeRelease();
	}
	m_pCurrentGroups = m_mapTodoGroups[1];
	ui.labelPictureHomePage->hide();
	ui.labNotAddHomePage->hide();
	ui.lineEditTodo->clear();
	ui.lineEditTodo->setPlaceholderText("+点击新建待办");
	ui.lineEditTodo->setStyleSheet("color:rgb(62, 193, 135);");

	if (m_mapListTodoItems[1].size() == 0)
	{
		ui.labelPictureHomePage->show();
		ui.labNotAddHomePage->show();
		ui.pbnNotArrange->hide();
		ui.groupBoxNotArrange->hide();
		ui.pbnNextSeven->hide();
		ui.groupBoxNextSeven->hide();
		ui.pbnAfter->hide();
		ui.groupBoxAfter->hide();
		ui.pbnOverdue->hide();
		ui.groupBoxOverdue->hide();
		return;
	}
	if (items != nullptr)
	{
		addOneTodoHomePage(items);
		return;
	}
	//minMain区域数据展示
	QList<KTodoItems*>::iterator it;
	for (it = m_mapListTodoItems[1].begin(); it != m_mapListTodoItems[1].end(); ++it)
	{
		if ((*it)->getIfFinish())
		{
			continue;
		}
		(*it)->initItemsDisplay(true);
		if (!(*it)->getOverTime().isValid())	//未安排
		{
			ui.vBoxNotArrange->insertWidget(0, (*it));
		}
		else if ((*it)->getOverTime().year() != QDate::currentDate().year())
		{
			ui.vBoxAfter->insertWidget(0, (*it));
		}
		else if (QDate::currentDate().daysTo((*it)->getOverTime()) <= 7 && QDate::currentDate().daysTo((*it)->getOverTime()) > 0)	//七天
		{
			ui.vBoxNextSeven->insertWidget(0, (*it));
		}
		else if (QDate::currentDate().daysTo((*it)->getOverTime()) < 0)		//已逾期
		{
			ui.vBoxOverdue->insertWidget(0, (*it));
		}
		else//以后
		{
			ui.vBoxAfter->insertWidget(0, (*it));
		}
	}
	//判断每个vbox区域是否都有内容，若有则展开，空则隐藏
	if (ui.vBoxNotArrange->count() > 0)		//未安排
	{
		ui.groupBoxNotArrange->setVisible(true);
		ui.pbnNotArrange->show();
	}
	else
	{
		ui.groupBoxNotArrange->hide();
		ui.pbnNotArrange->hide();
	}
	if (ui.vBoxNextSeven->count() > 0)		//七天
	{
		ui.groupBoxNextSeven->setVisible(true);
		ui.pbnNextSeven->show();
	}
	else
	{
		ui.groupBoxNextSeven->hide();
		ui.pbnNextSeven->hide();
	}
	if (ui.vBoxAfter->count() > 0)		//以后
	{
		ui.groupBoxAfter->setVisible(true);
		ui.pbnAfter->show();
	}
	else
	{
		ui.groupBoxAfter->hide();
		ui.pbnAfter->hide();
	}
	if (ui.vBoxOverdue->count() > 0)		//逾期
	{
		ui.groupBoxOverdue->setVisible(true);
		ui.pbnOverdue->show();
	}
	else
	{
		ui.groupBoxOverdue->hide();
		ui.pbnOverdue->hide();
	}
}


//初始化我的待办 -- 单击我的待办按钮后这里进行刷新
void KTodoMainWindow::initMyTodo(IN QList<KTodoItems*> listItems, IN KTodoItems* items)
{
	if (m_pCurrentGroups != nullptr)
	{
		m_pCurrentGroups->changeRelease();
	}
	m_pCurrentGroups = m_mapTodoGroups[1];
	ui.pbnSort->show();
	ui.labelPictureTodoPage->hide();
	ui.labNotAddTodoPage->hide();

	ui.lineEditTodo->clear();
	ui.lineEditTodo->setPlaceholderText("+点击新建待办");
	ui.lineEditTodo->setStyleSheet("color:rgb(62, 193, 135);");

	if (items != nullptr)
	{
		//新增一条数据以后，我的待办这里只调用新增一条的
		addOneTodoMyTodoPage(items);
		return;
	}

	deleteLayout(ui.vBoxShowFinished);
	deleteLayout(ui.vBoxShowTodo);

	if (listItems.size() == 0)
	{
		ui.labelPictureTodoPage->show();
		ui.labNotAddTodoPage->show();
		ui.pbnShowFinished->hide();
		ui.groupBoxShowTodo->hide();
		ui.groupBoxShowFinished->hide();
		return;
	}
	//遍历所有item存储，将其展示出来
	QList<KTodoItems*>::iterator it;
	for (it = listItems.begin(); it != listItems.end(); ++it)
	{
		(*it)->initItemsDisplay(false);
		if ((*it)->getIfFinish())
		{
			ui.vBoxShowFinished->insertWidget(0, (*it));
			(*it)->show();
		}
		else
		{
			ui.vBoxShowTodo->insertWidget(0, (*it));
			(*it)->show();
		}
	}

	if (ui.vBoxShowFinished->count() > 0)
	{
		ui.pbnShowFinished->setVisible(true);
		ui.groupBoxShowFinished->setVisible(true);
	}
	else
	{
		ui.pbnShowFinished->hide();
		ui.groupBoxShowFinished->hide();
	}
	if (ui.vBoxShowTodo->count() > 0)
	{
		ui.groupBoxShowTodo->setVisible(true);
	}
	else
	{
		ui.groupBoxShowTodo->hide();
	}
}

//初始化右侧的todo事项的细节展示
void KTodoMainWindow::initItemsDetail(IN KTodoItems* items)
{
	ui.groupBoxRightMain->show();
	ui.groupBoxRightNull->hide();
	//颜色互斥
	if (m_pCurrentItems != nullptr)
	{
		m_pCurrentItems->changeRelease();
	}
	items->changePress();
	m_pCurrentItems = items;	//记录当前的item
	ui.checkBoxTodoNameRight->setChecked(items->getIfFinish());		//是否完成
	int level = (5 - items->getTodoLevel()) >= 0 && (5 - items->getTodoLevel()) < 4 ? 5 - items->getTodoLevel() : 0;
	ui.comboBoxFirstRight->setCurrentIndex(level);	//设置优先级
	ui.lineEditTodoNameRight->setText(items->getTodoName());
	if (items->getOverTime().isValid())
	{
		ui.pbnDeadTimeRight->setText(items->getOverTime().toString("MM月dd日") + "到期");
	}
	else
	{
		ui.pbnDeadTimeRight->setText("设置到期时间");
	}
	if (items->getNoticeTime().isValid())
	{
		ui.pbnSetNoticeRight->setText(items->getNoticeTime().toString("MM月dd日 hh:mm") + "提醒我");
	}
	else
	{
		ui.pbnSetNoticeRight->setText("设置提醒");
	}
	if (items->getIntro().size() > 0)
	{
		ui.pbnAddIntroRight->setText(items->getIntro());
	}
	else
	{
		ui.pbnAddIntroRight->setText("添加描述");
	}
	if (items->getLocal().size() > 0)
	{
		ui.pbnAddLocalRight->setText(items->getLocal());
	}
	else
	{
		ui.pbnAddLocalRight->setText("添加地点");
	}
	if (items->getOther().size() > 0)
	{
		ui.pbnAddOtherRight->setText(items->getOther());
	}
	else
	{
		ui.pbnAddOtherRight->setText("添加备注");
	}
	ui.groupBoxIntroRight->hide();
	ui.groupBoxAddLocalRight->hide();
	ui.groupBoxAddOtherRight->hide();
	ui.pbnAddIntroRight->show();
	ui.pbnAddLocalRight->show();
	ui.pbnAddOtherRight->show();

}

//新增一条todo事项 触发我的首页
void KTodoMainWindow::addOneTodoHomePage(IN KTodoItems* items)
{
	items->initItemsDisplay(true);
	if (!items->getOverTime().isValid())//未安排
	{
		ui.vBoxNotArrange->insertWidget(0, items);

	}
	else if (items->getOverTime().year() != QDate::currentDate().year())	//以后
	{
		ui.vBoxAfter->insertWidget(0, items);
	}
	else if (QDate::currentDate().daysTo(items->getOverTime()) <= 7 && QDate::currentDate().daysTo(items->getOverTime()) > 0)//未来七天
	{
		ui.vBoxNextSeven->insertWidget(0, items);

	}
	else if (QDate::currentDate().daysTo(items->getOverTime()) < 0)//已逾期
	{
		ui.vBoxOverdue->insertWidget(0, items);
	}
	else//以后
	{
		ui.vBoxAfter->insertWidget(0, items);
	}
	//主要区域的分类展示
	if (ui.vBoxNotArrange->count() > 0)
	{
		ui.groupBoxNotArrange->setVisible(true);
		ui.pbnNotArrange->show();
	}
	else
	{
		ui.groupBoxNotArrange->hide();
		ui.pbnNotArrange->hide();
	}
	if (ui.vBoxNextSeven->count() > 0)
	{
		ui.pbnNextSeven->show();
		ui.groupBoxNextSeven->setVisible(true);
	}
	else
	{
		ui.pbnNextSeven->hide();
		ui.groupBoxNextSeven->hide();
	}
	if (ui.vBoxAfter->count() > 0)
	{
		ui.groupBoxAfter->setVisible(true);
		ui.pbnAfter->show();
	}
	else
	{
		ui.pbnAfter->hide();
		ui.groupBoxAfter->hide();
	}
	if (ui.vBoxOverdue->count() > 0)
	{
		ui.groupBoxOverdue->setVisible(true);
		ui.pbnOverdue->show();
	}
	else
	{
		ui.groupBoxOverdue->hide();
		ui.pbnOverdue->hide();
	}
}

//新增一条todo事项，触发 我的待办页面的变化
void KTodoMainWindow::addOneTodoMyTodoPage(IN KTodoItems* items)
{
	items->initItemsDisplay(false);
	if (items->getIfFinish())
	{
		ui.vBoxShowFinished->insertWidget(0, items);
	}
	else
	{
		ui.vBoxShowTodo->insertWidget(0, items);
	}

	if (ui.vBoxShowFinished->count() > 0)
	{
		ui.pbnShowFinished->show();
		ui.groupBoxShowFinished->show();
	}
	else
	{
		ui.pbnShowFinished->hide();
		ui.groupBoxShowFinished->hide();
	}
	if (ui.vBoxShowTodo->count() > 0)
	{
		ui.groupBoxShowTodo->show();
	}
	else
	{
		ui.groupBoxShowTodo->hide();
	}
}

//添加新分组
void KTodoMainWindow::addGroup(QString name)
{
	int groupId = m_listTodoGroups.size() + 1;
	KBtnShowGroupTodo* pBtnShowGroup = new KBtnShowGroupTodo(name, groupId, 0, this);
	m_listTodoGroups.push_back(pBtnShowGroup);
	//自定义信号 点击组别区域时，当前的group更新
	(void)connect(pBtnShowGroup, &KBtnShowGroupTodo::signalBtnClicked, this, &KTodoMainWindow::onGroupTodoClicked);
	pBtnShowGroup->initDisplay();
	ui.vLayoutGroupLeft->insertWidget(0, pBtnShowGroup);
	//插库
	QVector<QVariant> vecNewGroups;
	vecNewGroups.push_back(groupId);
	vecNewGroups.push_back(name);
	vecNewGroups.push_back(0);
	QSqlQuery query = this->m_pDatabase->execQuery("insert into groupList(groupId,groupName,groupCount) values(?,?,?)", vecNewGroups);
	ui.groupBoxRightMain->hide();
	ui.groupBoxRightNull->show();
}

//新建一个分组的触发事件
void KTodoMainWindow::onPbnAddOneGroupClicked()
{
	//组件位置
	QPoint start = m_pPbnAddGroup->mapToGlobal(m_pPbnAddGroup->pos());
	QPoint globalPos = this->mapToGlobal(QPoint(0, 0));
	int x = globalPos.x() + (this->width() - m_pAddGroupDialog->width()) / 2;	//弹窗的x坐标
	int y = globalPos.y() + (this->height() - m_pAddGroupDialog->height()) / 2;	//弹窗的x坐标
	m_pAddGroupDialog->setWindowModality(Qt::ApplicationModal);			//其他窗口锁死

	m_pAddGroupAnimation->setCurrentTime(500);
	m_pAddGroupAnimation->setStartValue(QRect(QCursor::pos().x(), QCursor::pos().y(), 0, 0));	//动画开始
	m_pAddGroupAnimation->setEndValue(QRect(x, y, 400, 250));	//动画结束
	m_pAddGroupAnimation->setEasingCurve(QEasingCurve::InOutQuad);	//曲线
	m_pAddGroupAnimation->start();
	m_pAddGroupDialog->show();
}

//组别单击，实现main区域的todo事件切换
void KTodoMainWindow::onGroupTodoClicked(IN KBtnShowGroupTodo* pBtnShowGroup)
{
	//组件初始化
	ui.pbnSort->show();
	ui.labelPictureTodoPage->hide();
	ui.labNotAddTodoPage->hide();
	ui.groupBoxShowFinished->hide();
	//互斥
	if (m_pCurrentGroups != nullptr)
	{
		m_pCurrentGroups->changeRelease();
	}
	pBtnShowGroup->changePress();
	//将新建的和当前组划为统一等级，实现互斥
	m_pCurrentGroups = pBtnShowGroup;

	//！！！这里一定要将互斥组件之间的公用布局删掉，在点击其他组建的时候重新创建，不然数据会到处窜
	deleteLayout(ui.vBoxShowTodo);
	deleteLayout(ui.vBoxShowFinished);

	//判断是否在我的待办页面并初始化组件
	int groupId = pBtnShowGroup->getGroupId();
	ui.stackedWidgetMidMain->setCurrentIndex(0);
	ui.labelLittleTitle->setText(pBtnShowGroup->getGroupName());
	if (m_mapListTodoItems[groupId].size() == 0)
	{
		ui.pbnShowFinished->hide();
		ui.groupBoxShowFinished->hide();
		ui.groupBoxShowTodo->hide();
		ui.labelPictureTodoPage->show();
		ui.labNotAddTodoPage->show();
		return;
	}

	//显示组内的items
	QList<KTodoItems*>::iterator it;
	for (it = m_mapListTodoItems[groupId].begin(); it != m_mapListTodoItems[groupId].end(); ++it)
	{
		//在我的首页上显示新增的group内的items
		(*it)->initItemsDisplay(ui.stackedWidgetMidMain->currentIndex() == 1);
		if ((*it)->getIfFinish())	//已完成
		{
			ui.vBoxShowFinished->insertWidget(0, (*it));
			(*it)->show();
		}
		else
		{
			ui.vBoxShowTodo->insertWidget(0, (*it));
			(*it)->show();
		}
	}
	if (ui.vBoxShowFinished->count() > 0)
	{
		ui.pbnShowFinished->setVisible(true);
		ui.groupBoxShowFinished->setVisible(true);
	}
	else
	{
		ui.pbnShowFinished->hide();
		ui.groupBoxShowFinished->hide();
	}
	if (ui.vBoxShowTodo->count() > 0)
	{
		ui.groupBoxShowTodo->show();
	}
	else
	{
		ui.groupBoxShowTodo->hide();
	}

}
//日期函数
void KTodoMainWindow::closeTimerBoxDeadTime()		//关闭
{
	ui.pbnDeadTimeRight->setStyleSheet("background-color: rgb(255,255,255);text-align:left;");
	ui.pbnDeadTimeRight->setCursor(Qt::PointingHandCursor);
	ui.pbnDeadTimeRight->setEnabled(true);
}
void KTodoMainWindow::onPbnDeadTimeRightClicked()	//设置到期时间
{
	QPoint start = ui.pbnDeadTimeRight->mapToGlobal(ui.pbnDeadTimeRight->pos());
	m_pTimerBoxDeadTime->gboxSetTimeHide();
	m_pTimerBoxDeadTime->move(start - QPoint(0, 50));
	QDate date;
	QTime time;
	date = m_pCurrentItems->getOverTime().isValid() ? m_pCurrentItems->getOverTime() : QDate::currentDate();
	time = m_pCurrentItems->getNoticeTime().isValid() ? m_pCurrentItems->getNoticeTime().time() : QTime::currentTime();
	m_pTimerBoxDeadTime->setDateTimeAgain(date, time, m_pCurrentItems->getAgain());
	m_pTimerBoxDeadTime->show();
	ui.pbnDeadTimeRight->setStyleSheet("background-color: rgb(168, 168, 168);text-align:left;");
	ui.pbnDeadTimeRight->setCursor(Qt::BlankCursor);
	ui.pbnDeadTimeRight->setEnabled(false);
}

void KTodoMainWindow::getDeadTime(QDate date, QTime time, int again)		//获取todo到期时间
{
	QDateTime dateTime;
	dateTime.setDate(date);
	dateTime.setTime(time);
	if (date.isValid())//有到期时间QDate
	{
		ui.pbnDeadTimeRight->setText(date.toString("MM月dd日") + "到期");
	}
	else
	{
		ui.pbnDeadTimeRight->setText("设置到期时间");
	}
}

void KTodoMainWindow::onPbnSetNoticeRightClicked()	//设置提醒时间
{
	QPoint start = ui.pbnSetNoticeRight->mapToGlobal(ui.pbnSetNoticeRight->pos());
	m_pTimerBoxNoticeTime->gboxSetAgainHide();	//设置重复 组件隐藏
	//提取已经设置的日期、时间，重复
	QDate date;
	QTime time;
	date = m_pCurrentItems->getOverTime().isValid() ? m_pCurrentItems->getOverTime() : QDate::currentDate();
	time = m_pCurrentItems->getNoticeTime().isValid() ? m_pCurrentItems->getNoticeTime().time() : QTime::currentTime();
	m_pTimerBoxNoticeTime->setDateTimeAgain(date, time, m_pCurrentItems->getAgain());
	m_pTimerBoxNoticeTime->move(start - QPoint(0, 50));
	m_pTimerBoxNoticeTime->show();
	ui.pbnSetNoticeRight->setStyleSheet("background-color: rgb(168, 168, 168);\ntext-align:left;");
	ui.pbnSetNoticeRight->setCursor(Qt::PointingHandCursor);
	ui.pbnSetNoticeRight->setEnabled(false);
}

void KTodoMainWindow::closeTimerBoxNoticeTime()	//关闭提醒时间日期选择器弹窗
{
	ui.pbnSetNoticeRight->setStyleSheet("background-color: rgb(255,255,255);\ntext-align:left;");
	ui.pbnSetNoticeRight->setCursor(Qt::PointingHandCursor);
	ui.pbnSetNoticeRight->setEnabled(true);
}
void KTodoMainWindow::getNoticeTime(QDate date, QTime time, int again)		//获取todo到期时间
{
	QDateTime dateTime;
	dateTime.setDate(date);
	dateTime.setTime(time);
	if (dateTime.isValid())//有效提示时间
	{
		ui.pbnSetNoticeRight->setText(dateTime.toString("MM月dd日 hh:mm") + "提醒我");
	}
	else
	{
		ui.pbnSetNoticeRight->setText("设置提醒");

	}
}

void KTodoMainWindow::onPbnAddIntroRightClicked()	//描述
{
	ui.pbnAddIntroRight->hide();
	if (m_pIntro == nullptr)
	{
		m_pIntro = new QTextEdit(this);
	}
	if (ui.pbnAddIntroRight->text() == "添加描述")
	{
		m_pIntro->setPlaceholderText("添加描述信息");
	}
	else
	{
		QString str = ui.pbnAddIntroRight->text();
		m_pIntro->setText(str);
	}

	m_pIntro->setMaximumSize(300, 120);
	m_pIntro->setMinimumSize(300, 120);
	m_pIntro->setStyleSheet("border:1px solid black");
	ui.hBoxAddIntroRight->addWidget(m_pIntro);
	ui.groupBoxIntroRight->show();
}
void KTodoMainWindow::onPbnAddLocalRightClicked()	//地点
{
	ui.pbnAddLocalRight->hide();
	if (m_pLocal == nullptr)
	{
		m_pLocal = new QTextEdit(this);
	}
	if (ui.pbnAddLocalRight->text() == "添加地点")
	{
		m_pLocal->setPlaceholderText("添加地点信息");
	}
	else
	{
		QString str = ui.pbnAddLocalRight->text();
		m_pLocal->setText(str);
	}
	m_pLocal->setMaximumSize(300, 120);
	m_pLocal->setMinimumSize(300, 120);
	m_pLocal->setStyleSheet("border:1px solid black");
	ui.hBoxAddLocalRight->addWidget(m_pLocal);
	ui.groupBoxAddLocalRight->show();
}
void KTodoMainWindow::onPbnAddOtherRightClicked()	//备注
{
	ui.pbnAddOtherRight->hide();
	if (m_pOther == nullptr)
	{
		m_pOther = new QTextEdit(this);
	}
	if (ui.pbnAddOtherRight->text() == "添加备注")
	{
		m_pOther->setPlaceholderText("添加备注信息");
	}
	else
	{
		QString str = ui.pbnAddOtherRight->text();
		m_pOther->setText(str);
	}

	m_pOther->setMaximumSize(300, 120);
	m_pOther->setMinimumSize(300, 120);
	m_pOther->setStyleSheet("border:1px solid black");
	ui.hBoxAddOtherRight->addWidget(m_pOther);
	ui.groupBoxAddOtherRight->show();
}


void KTodoMainWindow::onPbnSaveChangeRightClicked()		//保存修改
{
	if (!this->msgConfirmed("提示", "确认保存修改？"))
	{
		return;
	}
	//获取数据
	QString name = ui.lineEditTodoNameRight->text();	//待办名称
	int level = 5 - ui.comboBoxFirstRight->currentIndex();	//优先级
	QDateTime overTime;//到期时间
	if (m_pTimerBoxDeadTime->getDate().isValid())
	{
		overTime.setDate(m_pTimerBoxDeadTime->getDate());
	}
	else
	{
		overTime.setDate(m_pCurrentItems->getOverTime());
	}
	QDateTime str;//提醒时间
	str.setDate(m_pTimerBoxNoticeTime->getDate());
	str.setTime(m_pTimerBoxNoticeTime->getTime());
	QDateTime noticeTime;
	noticeTime = str.isValid() ? str : m_pCurrentItems->getNoticeTime();
	int again = m_pTimerBoxDeadTime->getAgain();//重复设置
	QString intro = (m_pIntro != nullptr) ? m_pIntro->toPlainText() : ui.pbnAddIntroRight->text();	//描述
	QString local = (m_pLocal != nullptr) ? m_pLocal->toPlainText() : ui.pbnAddLocalRight->text();	//地点
	QString other = (m_pOther != nullptr) ? m_pOther->toPlainText() : ui.pbnAddOtherRight->text();	//备注
	QString groupName = m_pCurrentItems->getGroupName();//组别名
	int groupId = m_pCurrentGroups->getGroupId();	//组别id
	//保存数据
	m_pCurrentItems->setTodoName(name);
	m_pCurrentItems->setTodoLevel(level);
	m_pCurrentItems->setIntro(intro);
	m_pCurrentItems->setLocal(local);
	m_pCurrentItems->setOther(other);
	//插库
	QVector<QVariant> vecUpdate;
	vecUpdate.push_back(name);
	vecUpdate.push_back(level);
	vecUpdate.push_back(intro);
	vecUpdate.push_back(local);
	vecUpdate.push_back(other);
	QString sqlString = "update todoList set todoName=?, todoLevel=?, intro=?, local=?, other=?";
	if (m_ifOverTime)//确认了重复和到期时间有效
	{
		m_pCurrentItems->setOverTime(overTime.date());
		m_pCurrentItems->setAgain(again);
		QString overTimeStr = overTime.toString("yyyy-MM-dd HH:mm");//设置日期格式
		vecUpdate.push_back(overTimeStr);
		vecUpdate.push_back(again);
		sqlString.append(",overTime=?, again=?");
	}
	if (m_ifNoticeTime)//确认了提示时间有效
	{
		m_pCurrentItems->setNoticeTime(noticeTime);
		QString noticeTimeStr = noticeTime.toString("yyyy-MM-dd HH:mm");//设置日期格式
		vecUpdate.push_back(noticeTimeStr);
		sqlString.append(",noticeTime=?");
	}
	m_pCurrentItems->initItemsDisplay(ui.stackedWidgetMidMain->currentIndex() == 1);
	vecUpdate.push_back(m_pCurrentItems->getId());
	sqlString.append("where id=?");
	QSqlQuery sql = this->m_pDatabase->execQuery(sqlString, vecUpdate);
	//若在我的待办页面进行的更新，则也更新一下首页
	if (ui.stackedWidgetMidMain->currentIndex() == 1)
		initMyHomePage(m_pCurrentItems);
	//重置状态
	m_ifNewAdd = false;
	m_ifNoticeTime = false;
	m_ifOverTime = false;
}


//刷新按钮
void KTodoMainWindow::onPbnRefreshClicked()
{
	if (ui.stackedWidgetMidMain->currentIndex() == 1)
	{
		initMyHomePage(nullptr);
		showMessage("待办列表已同步至最新");
	}
	else
	{
		initMyTodo(m_mapListTodoItems[m_pCurrentGroups->getGroupId()], nullptr);
		showMessage("待办列表已同步至最新");
	}
}

void KTodoMainWindow::deleteLayout(IN QLayout* currentLayout)
{
	QLayoutItem* child;
	while ((child = currentLayout->takeAt(0)) != 0)
	{
		child->widget()->setParent(nullptr);
		child->widget()->hide();
	}
}

//显示已完成
void KTodoMainWindow::onPbnShowFinishedClicked()
{
	if (ui.groupBoxShowFinished->isVisible())
	{
		ui.pbnShowFinished->setText("显示已完成");
		ui.pbnShowFinished->setIcon(QIcon(":/KTodoMainWindow/images/downs.png"));
		ui.groupBoxShowFinished->hide();
	}
	else
	{
		ui.pbnShowFinished->setText("隐藏已完成");
		ui.pbnShowFinished->setIcon(QIcon(":/KTodoMainWindow/images/ups.png"));
		ui.groupBoxShowFinished->show();
	}
}

//勾选框事件
void KTodoMainWindow::onCheckBoxChanged(IN KTodoItems* item)
{
	if (item->getIfFinish())//由完成->未完成
	{
		if (m_groupId == -1)
		{
			ui.vBoxShowFinished->insertWidget(0, item);
		}
		ui.groupBoxShowFinished->show();
		ui.pbnShowFinished->show();
	}
	if (!item->getIfFinish())//由未完成->完成
	{
		if (m_groupId == -1)
		{
			if (ui.stackedWidgetMidMain->currentIndex() == 1)
			{
				initMyHomePage(item);
			}
			else
			{
				item->onCheckBoxChanged();
				ui.vBoxShowTodo->insertWidget(0, item);
				ui.groupBoxShowTodo->show();
			}

		}
		if (ui.vBoxShowFinished->count() == 0)
		{
			ui.groupBoxShowFinished->hide();
			ui.pbnShowFinished->hide();
		}
	}
	item->setStyleSheet("background-color: rgb(132, 132, 132);");
	//插库
	QVector<QVariant> vecCheckbox;
	vecCheckbox.push_back(item->getIfFinish());
	vecCheckbox.push_back(item->getId());
	QSqlQuery sql = this->m_pDatabase->execQuery("update todoList set ifFinish=? where id =?", vecCheckbox);
}


//排序方法(sql语句、排序方式：case)
void KTodoMainWindow::sortTodos(QString sqlString, int sort)
{
	//在主页以外的其他页可以进行排序
	int groupId = m_pCurrentGroups->getGroupId();
	QList<int> listSort;	//存储排序结果
	QVector<QVariant> vecSort;
	vecSort.push_back(groupId);
	//查出来的结果有的没有设置过期时间，放在后面
	QSqlQuery sql = this->m_pDatabase->execQuery(sqlString, vecSort);//sqlString
	while (sql.next())
	{
		listSort.push_back(sql.value("id").toInt());
	}
	//向布局中摆放
	//先清除现有布局
	deleteLayout(ui.vBoxShowFinished);
	deleteLayout(ui.vBoxShowTodo);

	//遍历当前组的全部items
	//从全部的item中拿需要的
	for (int i = 0; i < listSort.size(); i++)
	{
		KTodoItems* item = m_mapTodoItems[listSort.at(i)];
		switch (sort)
		{
		case 1://按过期时间排序（存在过期时间（已完成，未完成）-不存在过期时间（已完成-未完成））
			if (item->getOverTime().isValid()) //时间存在
			{
				if (item->getIfFinish())  //完成了
				{
					ui.vBoxShowFinished->insertWidget(0, item);
					item->show();
				}
				else
				{
					ui.vBoxShowTodo->insertWidget(0, item);//ui的lout
					item->show();

				}
			}
			else   //时间不存在
			{
				if (item->getIfFinish())//完成了
				{
					ui.vBoxShowFinished->insertWidget(ui.vBoxShowFinished->count() - 1, item);
					item->show();
				}
				else
				{
					ui.vBoxShowTodo->insertWidget(ui.vBoxShowTodo->count() - 1, item);
					item->show();
				}
			}
			break;
		case 2://按创建时间排序  一定存在（在新建时就有，因此作为默认选择）
			if (item->getIfFinish())//完成了
			{
				ui.vBoxShowFinished->insertWidget(0, item);
				item->show();
			}
			else
			{
				ui.vBoxShowTodo->insertWidget(0, item);//ui的lout
				item->show();
			}
			break;
		case 3://优先级排序 这个字段一定存在	默认状态下优先级为0
			if (item->getIfFinish())//完成了
			{
				ui.vBoxShowFinished->insertWidget(0, item);
				item->show();
			}
			else
			{
				ui.vBoxShowTodo->insertWidget(0, item);//ui的lout
				item->show();
			}
			break;
		default:
			break;
		}

	}

}
//排序方式的按钮事件
void KTodoMainWindow::onPbnOverTimeSortClicked()
{
	m_pOverTimeSort->setText("到期时间排序   √");
	m_pCreateTimeSort->setText("创建时间排序");
	m_pFirstSort->setText("优先级排序 ");
	this->sortTodos("select id from todoList where groupId = ? order by overTime desc", 1);
}
void KTodoMainWindow::onPbnCreateTimeSortClicked()
{
	m_pOverTimeSort->setText("到期时间排序");
	m_pCreateTimeSort->setText("创建时间排序  √");
	m_pFirstSort->setText("优先级排序");
	this->sortTodos("select id from todoList where groupId = ? order by createTime desc", 2);
}
void KTodoMainWindow::onPbnFirstSortClicked()
{
	m_pOverTimeSort->setText("到期时间排序");
	m_pCreateTimeSort->setText("创建时间排序");
	m_pFirstSort->setText("优先级排序   √");
	this->sortTodos("select id from todoList where groupId = ? order by todoLevel desc", 3);
}




//消息提示
void KTodoMainWindow::showMessage(QString message)
{
	QMessageBox* box = new QMessageBox(QMessageBox::Information, "消息！", message);
	box->exec();
}

//消息确认
bool KTodoMainWindow::msgConfirmed(QString title, QString message)
{
	QMessageBox::StandardButton result = QMessageBox::question(NULL, title, message, QMessageBox::Yes | QMessageBox::No);
	switch (result)
	{
	case QMessageBox::Yes:
		qDebug() << "Yes";
		return true;
	case QMessageBox::No:
		qDebug() << "NO";
		return false;
	default:
		return false;
		break;
	}
}

//须知
void KTodoMainWindow::onPbnMainPageLearnMoreClicked()
{
	KLearnMore* more = new KLearnMore();
	more->show();
}
//注销
void KTodoMainWindow::onPbnMainPageExitClicked()
{
	emit signalCloseMainWindow();
	this->close();
}
void KTodoMainWindow::onPbnMainPageMinClicked()//最小化
{
	if (this->windowState() == Qt::WindowMinimized)
	{
		this->showNormal();
	}
	else
	{
		this->showMinimized();
	}
}
void KTodoMainWindow::onPbnMainPageMaxClicked()//最大化
{
	if (this->windowState() == Qt::WindowMaximized)
	{
		this->showNormal();
	}
	else
	{
		this->showMaximized();
	}
}
void KTodoMainWindow::onPbnMainPageCloseAllClicked()//关闭
{
	this->close();
}