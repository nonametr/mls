#ifndef RTMP_PROXY_H_
#define RTMP_PROXY_H_

#include <QtNetwork/qtcpserver.h>
#include <vector>
#include <string>

using namespace std;

class RtmpProxy : public QObject
{
	Q_OBJECT
public:
    RtmpProxy(string rtmp_server_name, int rtmp_server_port, int proxy_port);
    virtual ~RtmpProxy();
private:
    QTcpServer* _proxy_server_socket;
    QTcpSocket* _rtmp_server_socket;
    QTcpSocket* _rtmp_client_socket;
    string _rtmp_server_name;
    int _rtmp_server_port;
protected slots:
    void readRtmpServer();
    //void disconnectedRtmpServer();
    void newProxyConnection();
    //void disconnectedRtmpClient();
    void readProxyClient();
};

#endif /* RTMP_PROXY_H_ */
