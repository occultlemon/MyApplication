#include "ktodoitems.h"

KTodoItems::KTodoItems(QString name, int id, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//信息赋初值
	this->m_todoName = name;
	this->m_id = id;
	this->m_todoLevel = 1;
	this->m_again = 0;
	this->m_ifFinish = false;
	//组件初始化
	this->m_pHBox = new QHBoxLayout(this);
	m_pHBox->setSpacing(0);
	ui.groupBoxHide->setLayout(m_pHBox);
	m_pLabelAgain = new QLabel;		//四个组件用于显示信息
	m_pLabelOverTime = new QLabel;
	m_pLabelGroupName = new QLabel;
	m_pLabelNoticeTime = new QLabel;
	//隐藏标题栏
	this->setWindowFlag(Qt::FramelessWindowHint);
	//勾选
	(void)connect(ui.checkBox, &QCheckBox::clicked, this, &KTodoItems::finishCheckBox);//状态改变
}

KTodoItems::KTodoItems(int id, int groupId, QString todoName, int todoLevel, QDate overTime, QDateTime noticeTime, int again, QString intro, QString local, QString other, QString finishPerson, bool ifFinish, QString groupName, QWidget* parent) :QWidget(parent)
{
	ui.setupUi(this);
	//数据库信息初始化
	this->m_id = id;
	this->m_groupId = groupId;
	//this->m_createTime = m_createTime;
	this->m_todoName = todoName;
	this->m_todoLevel = todoLevel;
	this->m_overTime = overTime;
	this->m_again = again;
	this->m_noticeTime = noticeTime;
	this->m_intro = intro;
	this->m_local = local;
	this->m_other = other;
	this->m_finishPerson = finishPerson;
	this->m_ifFinish = ifFinish;
	this->m_groupName = groupName;
	//组件初始化
	this->m_pHBox = new QHBoxLayout(this);
	m_pHBox->setSpacing(0);
	ui.groupBoxHide->setLayout(m_pHBox);
	m_pLabelAgain = new QLabel;
	m_pLabelOverTime = new QLabel;
	m_pLabelGroupName = new QLabel;
	m_pLabelNoticeTime = new QLabel;
	//隐藏标题栏
	this->setWindowFlag(Qt::FramelessWindowHint);
	(void)connect(ui.checkBox, &QCheckBox::clicked, this, &KTodoItems::finishCheckBox);//状态改变

}

KTodoItems::~KTodoItems()
{
	delete m_pHBox;
	delete m_pLabelAgain;
	delete m_pLabelOverTime;
	delete m_pLabelGroupName;
	delete m_pLabelNoticeTime;
}


//鼠标操作
void KTodoItems::enterEvent(IN QEvent* event) //鼠标进入事件
{
	if (m_mouseState == 3)
	{
		return;
	}
	this->setCursor(QCursor(Qt::PointingHandCursor));
	this->setStyleSheet("background-color: rgb(244,245,247);");
	m_mouseState = 1;
	update();
}
void KTodoItems::leaveEvent(IN QEvent* event) //鼠标离开事件
{
	if (m_mouseState == 3)
	{
		return;
	}
	m_mouseState = 2;
	this->setStyleSheet("background-color: rgb(255,255,255);");
	update();
}
void KTodoItems::mousePressEvent(IN QMouseEvent* event) //鼠标点击事件
{
	emit signalCurrentItem(this);
}

//互斥事件
void KTodoItems::changePress()//被按下的颜色
{
	this->setCursor(QCursor(Qt::PointingHandCursor));
	this->setStyleSheet("background-color: rgb(232,235,239);");
	m_mouseState = 3;
	update();
}
void KTodoItems::changeRelease()//松开的颜色
{
	m_mouseState = 2;
	this->setStyleSheet("background-color: rgb(255,255,255);");
	update();
}


//初始化页面
void KTodoItems::initItemsDisplay(bool itemsShow)
{
	QLayoutItem* layItemChild;
	while ((layItemChild = m_pHBox->takeAt(0)) != 0)
	{
		//setParent为NULL，防止删除之后界面不消失
		if (layItemChild->widget())
		{
			layItemChild->widget()->setParent(NULL);
		}
		delete layItemChild;
	}
	//检查是否完成
	ui.checkBox->setChecked(m_ifFinish);

	//任务名
	QString todoNames;
	for (int i = 0; i < m_todoLevel - 1 && m_todoLevel != 5 && m_todoLevel != NULL; i++)
	{
		todoNames = todoNames + "!";
	}
	todoNames = todoNames + " " + m_todoName;
	ui.labelName->clear();
	ui.labelName->setText(todoNames);

	//结束时间 -- 若在有效期内，则同时设置重复
	if (m_overTime.isValid())
	{
		int year = m_overTime.year();
		int month = m_overTime.month();
		int day = m_overTime.day();
		int dayWeek = m_overTime.dayOfWeek();
		m_pLabelOverTime->setText(QString::fromUtf8("%1年%2月%3日 周%4  丨  ").arg(year).arg(month).arg(day).arg(dayWeek));
		m_pHBox->addWidget(m_pLabelOverTime, 0, Qt::AlignLeft);
	}
	if (m_again > 0)
	{
		switch (m_again)
		{
		case 1:
			m_pLabelAgain->setText("🕑 每天重复  丨  ");
			break;
		case 2:
			m_pLabelAgain->setText("🕑 每周重复  丨  ");
			break;
		case 3:
			m_pLabelAgain->setText("🕑 每月重复  丨  ");
			break;
		case 4:
			m_pLabelAgain->setText("🕑 不重复  丨  ");
			break;
		default:
			break;
		}
		m_pHBox->addWidget(m_pLabelAgain, 0, Qt::AlignLeft);
		m_pLabelAgain->setAlignment(Qt::AlignLeft);
	}

	//提醒时间
	if (m_noticeTime.isValid())
	{
		//获取系统当前北京时间
		QDateTime currentTime = QDateTime::currentDateTime();
		QString strCurrentTime = currentTime.toString("yyyy-MM-dd");
		int yearCurrent = strCurrentTime.split("-")[0].toInt();
		int monthCurrent = strCurrentTime.split("-")[1].toInt();
		int dayCurrent = strCurrentTime.split("-")[2].toInt();
		//获取提醒时间
		QString strNoticeTime = m_noticeTime.toString("yyyy-MM-dd");
		int yearNotice = strNoticeTime.split("-")[0].toInt();
		int monthNotice = strNoticeTime.split("-")[1].toInt();
		int dayNotice = strNoticeTime.split("-")[2].toInt();

		if (yearNotice == yearCurrent && monthNotice == monthCurrent)
		{
			if (dayNotice - dayCurrent == 1)
			{
				m_pLabelNoticeTime->setText(QString::fromUtf8("🔔 明天%1  丨  ").arg(m_noticeTime.time().toString("hh:mm")));
			}
			else if (dayNotice - dayCurrent == -1)
			{
				m_pLabelNoticeTime->setText(QString::fromUtf8("🔔 昨天%1  丨  ").arg(m_noticeTime.time().toString("hh:mm")));
			}
			else if (dayNotice - dayCurrent == 0)
			{
				m_pLabelNoticeTime->setText(QString::fromUtf8("🔔 今天%1  丨  ").arg(m_noticeTime.time().toString("hh:mm")));
			}
			else
			{
				m_pLabelNoticeTime->setText(QString::fromUtf8("🔔 %1月%2日 %3  丨  ").arg(monthNotice).arg(dayNotice).arg(m_noticeTime.time().toString("hh:mm")));
			}
		}
		m_pLabelNoticeTime->setAlignment(Qt::AlignLeft);
		m_pHBox->addWidget(m_pLabelNoticeTime, 0, Qt::AlignLeft);
	}

	//群组名
	if ((!this->m_groupName.isEmpty()) && itemsShow)
	{
		m_pLabelGroupName->setText("👷" + this->m_groupName);
		m_pHBox->addWidget(m_pLabelGroupName, 0, Qt::AlignLeft);
	}

	//未填写
	if (m_pHBox->count() == 0)
	{
		ui.groupBoxHide->hide();
		this->setMaximumHeight(100);
	}
	else
	{
		this->setMaximumHeight(100);
		ui.groupBoxHide->show();
	}

}

//勾选信号
void KTodoItems::finishCheckBox()
{
	this->m_ifFinish = !this->m_ifFinish;
	emit signalChangedCheckBox(this);
}



// 完成和未完成之间的切换
void  KTodoItems::onCheckBoxChanged()
{
	ui.checkBox->setChecked(this->m_ifFinish);
}

//getter setter
int KTodoItems::getId() const
{
	return m_id;
}
void KTodoItems::setId(int id)
{
	m_id = id;
}

int KTodoItems::getGroupId() const
{
	return m_groupId;
}

void KTodoItems::setGroupId(int groupId)
{
	m_groupId = groupId;
}


QString KTodoItems::getTodoName() const
{
	return m_todoName;
}

void KTodoItems::setTodoName(QString name)
{
	m_todoName = name;
}


int KTodoItems::getTodoLevel() const
{
	return m_todoLevel;
}

void KTodoItems::setTodoLevel(int level)
{
	m_todoLevel = level;
}


QDate KTodoItems::getOverTime() const
{
	return m_overTime;
}

void KTodoItems::setOverTime(QDate overTime)
{
	m_overTime = overTime;
}


int KTodoItems::getAgain() const
{
	return m_again;
}

void KTodoItems::setAgain(int again)
{
	m_again = again;
}


QDateTime KTodoItems::getNoticeTime() const
{
	return m_noticeTime;
}

void KTodoItems::setNoticeTime(QDateTime noticeTime)
{
	m_noticeTime = noticeTime;
}


QString KTodoItems::getIntro() const
{
	return m_intro;
}

void KTodoItems::setIntro(QString intro)
{
	m_intro = intro;
}


QString KTodoItems::getLocal() const
{
	return m_local;
}

void KTodoItems::setLocal(QString local)
{
	m_local = local;
}


QString KTodoItems::getOther() const
{
	return m_other;
}

void KTodoItems::setOther(QString other)
{
	m_other = other;
}


QString KTodoItems::getFinishPerson() const
{
	return m_finishPerson;
}

void KTodoItems::setFinishPerson(QString finishPerson)
{
	m_finishPerson = finishPerson;
}


bool KTodoItems::getIfFinish() const
{
	return m_ifFinish;
}

void KTodoItems::setIfFinish(bool ifFinish)
{
	m_ifFinish = ifFinish;
}


QString KTodoItems::getGroupName() const
{
	return m_groupName;
}

void KTodoItems::setGroupName(QString groupName)
{
	m_groupName = groupName;
}

