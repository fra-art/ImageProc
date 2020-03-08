#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QString>
#include <chrono>
//Timer klasse zur Verfügung gestellt von Joris Nonnast
class Timer : public QObject
{
    Q_OBJECT
    std::chrono::high_resolution_clock::time_point start_time;

public:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();

signals:
    void measured_time(QString);

public slots:
};

#define TIME_THIS Timer timer; connect(&timer, &Timer::measured_time, this, &MainWindow::zeitmessung);
#endif
