#include <QPushButton>
#include <QStyleFactory>
#include "widget.h"
#include "iostream"

void Widget::connect_mqtt() {
    auto val1 = this->ipAddress.text();
    auto val2 = this->port.text();

//    auto client = new QMqttClient(this);

    this->client.setHostname(val1);
    this->client.setPort(val2.toInt());
    this->client.connectToHost();
    this->time = std::chrono::system_clock::now().time_since_epoch();

    this->ipAddress.setDisabled(true);
    this->port.setDisabled(true);

    std::cout << "Connecting to " << val1.toStdString() << ":" << val2.toStdString() << std::endl;
}

Widget::Widget(QWidget *parent) :
        QWidget(parent) {
    auto font = QFont("Arial", 11);

    this->img.load("data.png");

    this->ipAddress.setText("");
    this->ipAddress.setPlaceholderText("Enter IP address");
    this->port.setText("");
    this->port.setPlaceholderText("Enter port");

    this->layout.addWidget(&this->ipAddress);
    this->layout.addWidget(&this->port);

    this->connectBtn.setText("Connect");
    QPushButton::connect(&this->connectBtn, &QPushButton::clicked, this, &Widget::connect_mqtt);
    this->layout.addWidget(&this->connectBtn);

    this->subscribeBtn.setText("Subscribe");
    QPushButton::connect(&this->subscribeBtn, &QPushButton::clicked, this, &Widget::subscribeMqtt);
    this->layout.addWidget(&this->subscribeBtn);

    auto layout_ = new QHBoxLayout(nullptr);

    auto tempLabel = new QLabel("Temperature: ");
    layout_->addWidget(tempLabel);
    layout_->addWidget(&this->temp);

    this->layout.addLayout(layout_);

    auto humLabel = new QLabel("Humidity: ");
    this->layout.addWidget(humLabel);
    this->hum.setRange(0, 100);
    this->hum.setFormat("%v%");
    this->hum.setValue(0);
    this->hum.setTextVisible(true);
//    this->hum.setStyle(QStyleFactory::create("fusion"));
    this->layout.addWidget(&this->hum);

    this->disconnectBtn.setText("Disconnect");
    QPushButton::connect(&this->disconnectBtn, &QPushButton::clicked, this, &Widget::disconnectMqtt);
    this->layout.addWidget(&this->disconnectBtn);

    auto pix = new QPixmap("/Users/aleksandrmikhailov/testqt/map.png");
    auto label = new QLabel();


    label->setPixmap(pix->scaled(500, 500, Qt::KeepAspectRatio));
    this->layout.addWidget(label);

    auto *label_ = new QLabel("", label);


    auto label_323 = new QLabel("<span style=color:red>0°C</span>", label);
    label_323->setGeometry(15, 20, 50, 20);
    label_323->setFont(font);

    auto label_325 = new QLabel("<span style=color:red>0°C</span>", label);
    label_325->setGeometry(55, 20, 50, 20);
    label_325->setFont(font);

    auto label_325_a = new QLabel("<span style=color:red>0°C</span>", label);
    label_325_a->setGeometry(95, 20, 50, 20);
    label_325_a->setFont(font);

    auto label_319 = new QLabel("<span style=color:red>0°C</span>", label);
    label_319->setGeometry(156, 20, 50, 20);
    label_319->setFont(font);

    auto label_315 = new QLabel("<span style=color:red>0°C</span>", label);
    label_315->setGeometry(233, 20, 50, 20);
    label_315->setFont(font);

    auto label_313 = new QLabel("<span style=color:red>0°C</span>", label);
    label_313->setGeometry(300, 20, 50, 20);
    label_313->setFont(font);

    auto label_305 = new QLabel("<span style=color:red>0°C</span>", label);
    label_305->setGeometry(452, 20, 50, 20);
    label_305->setFont(font);

    auto label_321 = new QLabel("<span style=color:red>0°C</span>", label);
    label_321->setGeometry(100, 118, 50, 20);
    label_321->setFont(font);

    auto label_321_a = new QLabel("<span style=color:red>0°C</span>", label);
    label_321_a->setGeometry(137, 118, 50, 20);
    label_321_a->setFont(font);

    auto label_321_b = new QLabel("<span style=color:red>0°C</span>", label);
    label_321_b->setGeometry(177, 118, 50, 20);
    label_321_b->setFont(font);

    auto label_317_b = new QLabel("<span style=color:red>0°C</span>", label);
    label_317_b->setGeometry(215, 118, 50, 20);
    label_317_b->setFont(font);

    auto label_317_a = new QLabel("<span style=color:red>0°C</span>", label);
    label_317_a->setGeometry(255, 118, 50, 20);
    label_317_a->setFont(font);

    auto label_317 = new QLabel("<span style=color:red>0°C</span>", label);
    label_317->setGeometry(300, 118, 50, 20);
    label_317->setFont(font);

    auto label_311 = new QLabel("<span style=color:red>0°C</span>", label);
    label_311->setGeometry(380, 118, 50, 20);
    label_311->setFont(font);

    auto label_307 = new QLabel("<span style=color:red>0°C</span>", label);
    label_307->setGeometry(452, 118, 50, 20);
    label_307->setFont(font);

    this->labels.insert("323", label_323);
    this->labels.insert("325", label_325);
    this->labels.insert("325_a", label_325_a);
    this->labels.insert("319", label_319);
    this->labels.insert("315", label_315);
    this->labels.insert("313", label_313);
    this->labels.insert("305", label_305);
    this->labels.insert("321", label_321);
    this->labels.insert("321_a", label_321_a);
    this->labels.insert("321_b", label_321_b);
    this->labels.insert("317_b", label_317_b);
    this->labels.insert("317_a", label_317_a);
    this->labels.insert("317", label_317);
    this->labels.insert("311", label_311);
    this->labels.insert("307", label_307);



//    this->tempChart.setTitle("Temperature");
//    this->tempChart.addSeries(&this->tempSeries);
//    auto end = std::chrono::system_clock::now().time_since_epoch();

//    this->tempChart.createDefaultAxes();
//    this->layout.setParent(this);
    this->setLayout(&this->layout);
    this->setWindowTitle("MQTT Client");

}

void Widget::handleMessage(const QMqttMessage &message) {
    if (message.topic().name() == "temp") {
        this->temp.setText(message.payload() + "°C");
        return;
//        this->tempSeries.append(QPointF(std::chrono::duration<std::chrono::seconds, ulong>(this->time - std::chrono::system_clock::now().time_since_epoch()), message.payload().toDouble()));
    } else if (message.topic().name() == "hum") {
        this->hum.setValue(message.payload().toInt());
        return;
    }
//    std::cout << message.payload().toStdString() << std::endl;
    auto topic = message.topic().name();
    const auto &payload = message.payload();
    auto text = QString("<span style=color:red>") + QString(payload) + QString("°C</span>");
    this->labels[topic]->setText(text);
}

void Widget::subscribeMqtt() {
    for (auto &room: this->topics) {
        auto sub = this->client.subscribe(room);
        QObject::connect(sub, &QMqttSubscription::messageReceived, this, &Widget::handleMessage);
        std::cout << "Subscribed to " << room.toStdString() << std::endl;
    }
    auto sub1 = this->client.subscribe(QString("temp"));
    QObject::connect(sub1, &QMqttSubscription::messageReceived, this, &Widget::handleMessage);
    auto sub2 = this->client.subscribe(QString("hum"));
    QObject::connect(sub2, &QMqttSubscription::messageReceived, this, &Widget::handleMessage);
    std::cout << "Subscribed" << std::endl;
}

void Widget::disconnectMqtt() {
    this->client.disconnectFromHost();
    this->ipAddress.setDisabled(false);
    this->port.setDisabled(false);
    std::cout << "Disconnected" << std::endl;
}

Widget::~Widget()
= default;

