/*
══════════════════════════════════════╗
	filename:	KREADME_H
	describe:	操作手册
	editor:		wangjie
	time:		2023/5/11
══════════════════════════════════════╣
*/
#ifndef KREADME_H
#define KREADME_H
#define IN
#define OUT
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kreadme.h"

class KReadme : public QWidget
{
	Q_OBJECT

public:
	KReadme(QWidget* parent = Q_NULLPTR);
	~KReadme();

private:
	Ui::KReadme ui;
};
#endif // !KREADME_H