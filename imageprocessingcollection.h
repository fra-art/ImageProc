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
    void equalize_histogram(QImage image);
    void gaussian_blurr(int height, int width, QImage image);
    void median(int size, QImage image);
    void mean(QImage image, int size);//mit opencv
    cv::Mat mean_single_channel(cv::Mat image, int size);
    void mean_separated(QImage image);
    void dilate(QImage image);
    void erode(QImage image);
    void sobel_filter(bool x, bool y, int size, QImage image);
    void laplacian(QImage image);
    void canny_filter(QImage image, double t1, double t2);
    void draw_line(cv::Point start, cv::Point end, QImage image);//
    void histogram(QImage image);//
    static QImage binarisieren(QImage image, int schwelle);//

signals:
    void image_finished(QImage, QString);
    void binarised_image_finished(QImage);
    void time_measured(QString);

private:
    QImage mat_to_qimage(cv::Mat image);
    cv::Mat qimage_to_mat(QImage image);
};

#endif // IMAGEPROCESSINGCOLLECTION_H
