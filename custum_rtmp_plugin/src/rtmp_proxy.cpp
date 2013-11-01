#include "rtmp_proxy.h"

#include <QtNetwork/qtcpsocket.h>
#include "global.h"

RtmpProxy::RtmpProxy(string rtmp_server_name, int rtmp_server_port, int proxy_port) : _rtmp_server_name(rtmp_server_name), _rtmp_server_port(rtmp_server_port), _rtmp_client_socket(NULL)
{
    _rtmp_server_socket = new QTcpSocket(this);
    QObject::connect(_rtmp_server_socket, SIGNAL(readyRead()), this, SLOT(readRtmpServer()));
    _proxy_server_socket = new QTcpServer(this);
    if (!_proxy_server_socket->listen(QHostAddress::LocalHost, proxy_port))
    {
        traceerr("Server Error", "Unable to start the server: %s", _proxy_server_socket->errorString().toStdString().c_str() );
        _proxy_server_socket->close();
    }
    QObject::connect(_proxy_server_socket, SIGNAL(newConnection()), this, SLOT(newProxyConnection()));
}

RtmpProxy::~RtmpProxy()
{
}

void RtmpProxy::newProxyConnection()
{
    _rtmp_client_socket = _proxy_server_socket->nextPendingConnection();
    _rtmp_server_socket->connectToHost(_rtmp_server_name.c_str(), _rtmp_server_port);
    _rtmp_server_socket->waitForConnected();
    if(_rtmp_server_socket->state() != QAbstractSocket::ConnectedState)
    {
    	return;
    }
    QObject::disconnect(_proxy_server_socket, SIGNAL(newConnection()), this, SLOT(newProxyConnection()));//we accept only one connection
    QObject::connect(_rtmp_client_socket, SIGNAL(readyRead()), this, SLOT(readProxyClient()));
}

void RtmpProxy::readProxyClient()
{
    while(_rtmp_client_socket->bytesAvailable() > 0)
    {
    	_rtmp_server_socket->write(_rtmp_client_socket->readAll());
    }
}

void RtmpProxy::readRtmpServer()
{
	_rtmp_client_socket->write(_rtmp_server_socket->readAll());
}
