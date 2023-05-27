#include "kbtnshowgrouptodo.h"

KBtnShowGroupTodo::KBtnShowGroupTodo(QString name, int groupId, int groupCount, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setCursor(QCursor(Qt::PointingHandCursor));
	m_groupName = name;
	m_groupId = groupId;
	m_groupCount = groupCount;
	ui.lineEdit->setReadOnly(true);
	//鼠标初始状态的设置
	m_mouseStatus = 2;
	update();
}

KBtnShowGroupTodo::~KBtnShowGroupTodo()
{
}

void KBtnShowGroupTodo::enterEvent(IN QEvent* event) //鼠标进入事件	m_mouseStatus = 1
{
	if (m_mouseStatus == 3)
	{
		return;
	}
	ui.groupBox->setStyleSheet("background-color: rgb(244,245,247);");
	ui.lineEdit->setStyleSheet("background-color: rgb(244,245,247);");
	m_mouseStatus = 1;
	update();
}
void KBtnShowGroupTodo::leaveEvent(IN QEvent* event)//鼠标移动事件		m_mouseStatus = 2
{
	if (m_mouseStatus == 3)
	{
		return;
	}
	ui.groupBox->setStyleSheet("background-color: rgb(255,255,255);");
	ui.lineEdit->setStyleSheet("background-color: rgb(255,255,255);");
	m_mouseStatus = 2;
	update();
}
void KBtnShowGroupTodo::mousePressEvent(IN QMouseEvent* event)//鼠标点击事件	m_mouseStatus = 3
{
	ui.groupBox->setStyleSheet("background-color: rgb(232,235,239);");
	ui.lineEdit->setStyleSheet("background-color: rgb(232,235,239);");
	ui.lineEdit->setStyleSheet("");
	m_mouseStatus = 3;
	update();
	emit signalBtnClicked(this);//通知该组被按下
}

void KBtnShowGroupTodo::changePress()	//互斥
{
	m_mouseStatus = 3;
	ui.groupBox->setStyleSheet("background-color: rgb(232,235,239);");
	ui.lineEdit->setStyleSheet("background-color: rgb(232,235,239);");
	update();
}
void KBtnShowGroupTodo::changeRelease()
{
	m_mouseStatus = 2;
	ui.groupBox->setStyleSheet("background-color: rgb(255,255,255);");
	ui.lineEdit->setStyleSheet("background-color: rgb(255,255,255);");
	update();
}

//初始化样式-设置显示出来的文本
void KBtnShowGroupTodo::initDisplay()
{
	ui.lineEdit->setText(m_groupName + QString("(") + QString::number(m_groupCount) + QString(")"));
}


//getter setter
int KBtnShowGroupTodo::getGroupId() const
{
	return m_groupId;
}
void KBtnShowGroupTodo::setGroupId(int groupId)
{
	m_groupId = groupId;
}

QString KBtnShowGroupTodo::getGroupName() const
{
	return m_groupName;
}
void KBtnShowGroupTodo::setGroupName(QString groupName)
{
	m_groupName = groupName;
}

int KBtnShowGroupTodo::getGroupCount() const
{
	return m_groupCount;
}
void KBtnShowGroupTodo::setGroupCount(int groupCount)
{
	m_groupCount = groupCount;
}