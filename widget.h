#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <qglobal.h>
#include <QtMqtt/qmqttclient.h>
#include <QLabel>
#include <QProgressBar>
#include <chrono>
#include <QPixmap>
#include <QMap>
#include <format>


class Widget : public QWidget {
Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

    QVBoxLayout layout;
    QLineEdit ipAddress;
    QLineEdit port;
    QPushButton connectBtn;
    QPushButton subscribeBtn;
    QPushButton disconnectBtn;
    QMqttClient client;
    QLabel temp;
    QProgressBar hum;
    QImage img;
    QMap<QString, QLabel *> labels;
    std::chrono::duration<double> time;
    QString topics[15] = {"323", "325", "325_a", "319", "315", "313", "305", "321", "321_a", "321_b", "317_b", "317_a",
                          "317", "311", "307"};

    void connect_mqtt();

    void subscribeMqtt();

    void handleMessage(const QMqttMessage &message);

    void disconnectMqtt();

};

#endif // WIDGET_H
