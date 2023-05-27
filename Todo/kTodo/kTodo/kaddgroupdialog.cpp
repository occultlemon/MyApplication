#include "kaddgroupdialog.h"

KAddGroupDialog::KAddGroupDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlag(Qt::FramelessWindowHint);
	(void)connect(ui.pbnCancel, &QPushButton::clicked, this, &KAddGroupDialog::onPbnCloseClicked);
	(void)connect(ui.pbnClose, &QPushButton::clicked, this, &KAddGroupDialog::onPbnCloseClicked);
	(void)connect(ui.lineEditGroupName, &QLineEdit::textChanged, this, &KAddGroupDialog::onPbnOKClicked);
	(void)connect(ui.pbnOK, &QPushButton::clicked, this, &KAddGroupDialog::signalHand);
	(void)connect(ui.pbnOK, &QPushButton::clicked, this, &KAddGroupDialog::onPbnCloseClicked);
	this->hide();
	//编辑框回车新建分组
	(void)connect(ui.lineEditGroupName, &QLineEdit::returnPressed, this, &KAddGroupDialog::signalHand);
	(void)connect(ui.lineEditGroupName, &QLineEdit::returnPressed, this, &KAddGroupDialog::onPbnOKClicked);
	ui.pbnCancel->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnOK->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnClose->setCursor(QCursor(Qt::PointingHandCursor));

}

KAddGroupDialog::~KAddGroupDialog()
{
}

//关闭事件
void KAddGroupDialog::closeEvent(IN QCloseEvent* event)
{
	Q_UNUSED(event);
	ui.lineEditGroupName->clear();
}
//信号通信 传递信息
void KAddGroupDialog::signalHand()
{
	emit addGroup(ui.lineEditGroupName->text());
}

//关闭按钮
void KAddGroupDialog::onPbnCloseClicked()
{
	this->close();
}
//确定按钮
void KAddGroupDialog::onPbnOKClicked()
{
	if (ui.lineEditGroupName->text().size() > 0)
	{
		ui.pbnOK->setEnabled(true);
		ui.pbnOK->setStyleSheet("background-color: rgb(4,184,174);\ncolor: rgb(255, 255, 255);\nborder:2px groove gray;\nborder-radius:5px;");
	}
	else
	{
		ui.pbnOK->setEnabled(false);
		ui.pbnOK->setStyleSheet("background-color: rgb(180,234,231);\ncolor: rgb(255, 255, 255);\nborder:2px groove gray;\nborder-radius:5px;");
	}
}