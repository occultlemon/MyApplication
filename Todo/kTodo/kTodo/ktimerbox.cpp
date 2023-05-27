#include "ktimerbox.h"

const static int WPX = 450;
const static int HPX = 400;

KTimerBox::KTimerBox(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(WPX, HPX);
	this->setMaximumSize(WPX, HPX);
	this->setWindowFlag(Qt::FramelessWindowHint);
	ui.pbnCancel->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnOK->setCursor(QCursor(Qt::PointingHandCursor));
	ui.timeEditSetTime->setTime(QDateTime::currentDateTime().time());
	(void)connect(ui.pbnCancel, &QPushButton::clicked, this, &KTimerBox::onPbnCancelClicked);
	(void)connect(ui.pbnOK, &QPushButton::clicked, this, &KTimerBox::onPbnOKClicked);
	(void)connect(ui.pbnOK, &QPushButton::clicked, this, &KTimerBox::signalPbnOk);
}

KTimerBox::~KTimerBox()
{
}

void KTimerBox::onPbnCancelClicked()
{
	emit signalCloseThis();
	this->hide();
}

void KTimerBox::onPbnOKClicked()
{
	if (ui.calendarWidget->selectedDate().isValid())
	{
		emit signalGetTime(ui.calendarWidget->selectedDate(), ui.timeEditSetTime->time(), ui.comboBoxSetAgain->currentIndex());
	}
	emit signalCloseThis();
	this->hide();
}


//设置重复 隐藏
void KTimerBox::gboxSetAgainHide()
{
	ui.groupBoxSetAgain->hide();
	ui.groupBoxSetTime->show();
}
//设置时间 隐藏
void KTimerBox::gboxSetTimeHide()
{
	ui.groupBoxSetTime->hide();
	ui.groupBoxSetAgain->show();
}
//弹窗事件	重写父类基类函数
bool KTimerBox::event(IN QEvent* event)
{
	if (QEvent::WindowDeactivate == event->type())
	{
		this->hide();
		emit signalCloseThis();
	}
	return QWidget::event(event);
}

//设置日期（yyyy-MM-dd）、时间(hh:mm)、和重复(0\1\2\3)
void KTimerBox::setDateTimeAgain(QDate date, QTime time, int again)
{
	ui.calendarWidget->setSelectedDate(date);
	ui.timeEditSetTime->setTime(time);
	ui.comboBoxSetAgain->setCurrentIndex(again);
}

//getter 
QDate KTimerBox::getDate()
{
	return ui.calendarWidget->selectedDate();
}

QTime KTimerBox::getTime()
{
	return ui.timeEditSetTime->time();
}

int KTimerBox::getAgain()
{
	return ui.comboBoxSetAgain->currentIndex();
}
