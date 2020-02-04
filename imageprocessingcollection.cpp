#include "imageprocessingcollection.h"
#include <QMessageBox>

void ImageProcessingCollection::invert_image(QImage image)
{

    image.invertPixels();

    emit image_finished(image, "Inverted");

}

void ImageProcessingCollection::test_image_fast()
{
    QImage newImage(512, 512, QImage::Format_Grayscale8);


                unsigned char* line;
        for(int y = 0; y < newImage.height(); y++){
            line = newImage.scanLine(y);
            for(int x = 0; x < newImage.width(); x++){
                line[x] = static_cast<unsigned char>(y/2);
            }
    }
    emit image_finished(newImage, "Test Image Fast");
}

void ImageProcessingCollection::test_image_slow()
{
    QImage test_image_s(512, 512, QImage::Format_Grayscale8);

                unsigned char* pixel_ptr = test_image_s.bits();
        for(int y = 0; y < test_image_s.height(); y++){
            for(int x = 0; x < test_image_s.width(); x++){
                *pixel_ptr = static_cast<unsigned char>(y/2);
                pixel_ptr++;
            }
    }
    emit image_finished(test_image_s, "Test Image Slow");
}

void ImageProcessingCollection::bildLaden(std::string path)
{
    QImage loaded_image;
    loaded_image.load(path.c_str());
    emit image_finished(loaded_image, path.c_str());
}

void ImageProcessingCollection::time_measurement(QString time)
{
    emit time_measured("Function took: " + time);
}

void ImageProcessingCollection::scale_image(double factor)
{

}

