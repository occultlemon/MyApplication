#include "klineedit.h"

KLineEdit::KLineEdit(QWidget* parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);
}

KLineEdit::~KLineEdit()
{
}

//鼠标点击事件
void KLineEdit::mousePressEvent(QMouseEvent* event)
{
	if (this->text().size() > 0)
	{
		return;
	}
	this->setPlaceholderText("输入内容后，回车创建成功");
	this->setStyleSheet("color:gray;");
}
//设置编辑字体的颜色
void KLineEdit::setEditFontColor()
{
	this->setStyleSheet("color:black;");
}