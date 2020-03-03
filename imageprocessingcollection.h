#ifndef IMAGEPROCESSINGCOLLECTION_H
#define IMAGEPROCESSINGCOLLECTION_H

#include <QWidget>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
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
    void resize_image(int height, int width, QImage image);
private slots:

    //void zoomIn();
    //void zoomOut();
    //void normalSize();

public slots:

signals:
    void image_finished(QImage, QString);
    void time_measured(QString);

private:
    QImage mat_to_qimage(cv::Mat image);
    cv::Mat qimage_to_mat(QImage image);
};

#endif // IMAGEPROCESSINGCOLLECTION_H
