#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_share_screen.h"

class share_screen : public QMainWindow
{
    Q_OBJECT

public:
    share_screen(QWidget *parent = nullptr);
    ~share_screen();

private:
    Ui::share_screenClass ui;
};
