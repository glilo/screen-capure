#include "NDISource.h"



NDISource::NDISource(QString name, QString host)
{
	_name = name;
	_host = host;
}

NDISource::~NDISource() {

}


QString NDISource::getName() {
	return _name;
}

QString NDISource::getHost() {
	return _host;
}

