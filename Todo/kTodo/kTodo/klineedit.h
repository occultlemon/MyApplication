/*
══════════════════════════════════════╗
	@filename:		klineedit.h
	@describe:		自定义文本框组件
	@editor:		wangjie
	@time:			2023/5/19
══════════════════════════════════════╣
*/
#ifndef __KLINEEDIT_H__
#define __KLINEEDIT_H__
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<qlineedit.h>
#include "ui_klineedit.h"
#include<qstring.h>
#include <QMouseEvent>

class KLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	KLineEdit(QWidget* parent = Q_NULLPTR);
	~KLineEdit();

protected:
	//鼠标点击事件
	void mousePressEvent(QMouseEvent* event);
	//设置编辑字体的颜色
	void setEditFontColor();

private:
	Ui::KLineEdit ui;
};
#endif // !__KLINEEDIT_H__