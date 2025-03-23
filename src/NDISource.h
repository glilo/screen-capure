#pragma once
#include<qstring.h>


class NDISource
{
protected:
    QString _name;
    QString _host;


public:
    NDISource(QString name, QString host);
    ~NDISource();
    QString getName();
    QString getHost();
};

