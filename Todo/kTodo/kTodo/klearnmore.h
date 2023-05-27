#pragma once

#include <QWidget>
#include "ui_klearnmore.h"

class KLearnMore : public QWidget
{
	Q_OBJECT

public:
	KLearnMore(QWidget *parent = Q_NULLPTR);
	~KLearnMore();

private:
	Ui::KLearnMore ui;
};
