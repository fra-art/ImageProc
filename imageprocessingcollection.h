#ifndef IMAGEPROCESSINGCOLLECTION_H
#define IMAGEPROCESSINGCOLLECTION_H

#include <QWidget>
#include "timer.h"

class ImageProcessingCollection : public QObject
{
    Q_OBJECT

public:
    ImageProcessingCollection() = default;
    void invert_image(QImage image);
    void test_image_fast();
    void test_image_slow();
    void bildLaden(std::string path);
    void time_measurement(QString time);


public slots:

signals:
    void image_finished(QImage, QString);
    void time_measured(QString);
};

#endif // IMAGEPROCESSINGCOLLECTION_H
