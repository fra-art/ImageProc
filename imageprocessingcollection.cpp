#include "imageprocessingcollection.h"
#include <QMessageBox>

void ImageProcessingCollection::invert_image(QImage image)
{

    cv::Mat image_to_invert = qimage_to_mat(image);
    if(image_to_invert.channels() == 1){
        image_to_invert.forEach<uchar>([](uchar& pixel, const int* pos){pixel = ~pixel;});
    }
    else if(image_to_invert.channels() == 3){
        image_to_invert.forEach<cv::Vec3b>([](cv::Vec3b& pixel, const int* pos){
            pixel[0] = ~pixel[0];
            pixel[1] = ~pixel[1];
            pixel[2] = ~pixel[2];
        });

    }

    emit image_finished(mat_to_qimage(image_to_invert), "Inverted");

}

void ImageProcessingCollection::test_image_fast()
{
    //QImage newImage(512, 512, QImage::Format_Grayscale8);
    cv::Mat newImage(512, 512, CV_8UC1);

    unsigned char* pixel = newImage.data;
    for(int y = 0; y < newImage.rows; y++){
        //line = newImage.scanLine(y);
        for(int x = 0; x < newImage.cols; x++){
            //line[x] = static_cast<unsigned char>(y/2);
            *pixel = static_cast<unsigned char>(y / 2);
            pixel++;
        }
    }
    emit image_finished(mat_to_qimage(newImage), "Test Image Fast");
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
    loaded_image.convertTo(QImage::Format_RGB888);
    emit image_finished(loaded_image, path.c_str());
}

void ImageProcessingCollection::time_measurement(QString time)
{
    emit time_measured("Function took: " + time);
}

void ImageProcessingCollection::resize_image(int height, int width, QImage image)
{
    cv::Size size(height, width);
    cv::Mat newImage(512, 512, CV_8UC3);
    cv::Mat image_to_resize = qimage_to_mat(image);
    cv::resize(image_to_resize, newImage, size);

    emit image_finished(mat_to_qimage(newImage), "Resized");

}

void ImageProcessingCollection::equalize_histogram(QImage image)
{

        cv::Mat src = qimage_to_mat(image);
        cv::Mat newImage;

        if(src.channels() == 1){
            cv::equalizeHist( src, newImage );
        }
        else{
            std::vector<cv::Mat> channels;
            cv::split(src, channels);
            for(cv::Mat& channel : channels){
                cv::equalizeHist(channel, channel);

            }
            cv::merge(channels, newImage);
        }
        emit image_finished(mat_to_qimage(newImage), "Equalized");
}

void ImageProcessingCollection::gaussian_blurr(int height, int width, QImage image)
{
     cv::Mat src = qimage_to_mat(image);
     cv::Mat newImage;
     cv::Size size(height, width);
     cv::GaussianBlur(src, newImage, size, 0,0);
    emit image_finished(mat_to_qimage(newImage), "filtered_gaussian");

}

void ImageProcessingCollection::median(int size, QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::medianBlur(src, newImage, size);
    emit image_finished(mat_to_qimage(newImage), "Median Filter");
}

void ImageProcessingCollection::mean(QImage image, int size)
{
    cv::Mat newImage;
    cv::Mat src = qimage_to_mat(image);
    if(size % 2){
        if(src.type() == CV_8UC1){
            newImage = mean_single_channel(src, size);
        }
        else{
            std::vector<cv::Mat> channels;
            cv::split(src, channels);
            for(auto& channel : channels){
                channel = mean_single_channel(channel, size);
            }
            cv::merge(channels, newImage);
        }
    }
    emit image_finished(mat_to_qimage(newImage), "Mean Filter");



}

cv::Mat ImageProcessingCollection::mean_single_channel(cv::Mat src, int size)
{
    int sum = 0;
    cv::Mat newImage = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    for(int x = size/2; x < src.cols - (size/2); ++x){
        for(int y = size/2; y < src.rows - (size/2); ++y){
            sum = 0;
            for(int i = -(size/2); i < size/2; ++i){
                for(int j = -(size/2); j < size/2; ++j){
                    sum += src.at<unsigned char>(y+j, x+i);
                }
            }
                newImage.at<unsigned char>(y, x) = sum/(size*size);
            }
        }
    return newImage;
    }

void ImageProcessingCollection::mean_separated(QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;

   //cv::filter2D(src, newImage, ddepht, kernel, cv::Point(-1,-1), 0, 1);


    emit image_finished(mat_to_qimage(newImage), "filtered_seperated_median");
}

void ImageProcessingCollection::dilate(QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::dilate(src, newImage, cv::Mat(), cv::Point(-1,-1), 2, 1, 1);
    emit image_finished(mat_to_qimage(newImage), "dilated");
}

void ImageProcessingCollection::erode(QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::erode(src, newImage, cv::Mat(), cv::Point(-1,-1), 2, 1, 1);
    emit image_finished(mat_to_qimage(newImage), "eroded");
}

void ImageProcessingCollection::sobel_filter(bool x, bool y, int size, QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::Sobel(src, newImage, -1, x, y, size);
    emit image_finished(mat_to_qimage(newImage), "sobel_filtered");

}

void ImageProcessingCollection::laplacian(QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::Laplacian(src, newImage, CV_8UC3, 1, 1, 0, 1);
    emit image_finished(mat_to_qimage(newImage), "laplacian");

}

void ImageProcessingCollection::canny_filter(QImage image, double t1, double t2)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    cv::Canny(src, newImage, t1, t2, 3, false);
    emit image_finished(mat_to_qimage(newImage), "canny");
}

void ImageProcessingCollection::draw_line(cv::Point start, cv::Point end, QImage image)
{
    cv::Mat src = qimage_to_mat(image);
    cv::Mat newImage;
    int thickness = 2;
    int lineType = cv::LINE_8;
    cv::line(src, start, end, cv::Scalar( 0, 0, 0 ), thickness, lineType );
    emit image_finished(mat_to_qimage(newImage), "line_drawn");
}

QImage ImageProcessingCollection::binarisieren(QImage image, int schwelle)
{
    image.convertTo(QImage::Format_Grayscale8);
    unsigned char* image_data_ptr = image.bits();
    for(int i = 0; i < image.width(); ++i){
        for(int j = 0; j < image.height(); ++j){

        if(*image_data_ptr < schwelle){
            *image_data_ptr = 0;
        }
        else{
            *image_data_ptr = 255;
        }
        image_data_ptr++;
    }
    }
    return image;
}


QImage ImageProcessingCollection::mat_to_qimage(cv::Mat image)
{
    if(image.type() == CV_8UC1){
        return QImage(static_cast<uchar*>(image.data), image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8).copy();
    }
    else{
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        return QImage(static_cast<uchar*>(image.data), image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB888).copy();
    }
}

cv::Mat ImageProcessingCollection::qimage_to_mat(QImage image)
{
    if(image.format() == QImage::Format_RGB888){
        cv::Mat mat(image.height(), image.width(), CV_8UC3, image.bits());
        cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
        return mat.clone();
    }
    else if(image.format() == QImage::Format_Grayscale8){
        return cv::Mat(image.height(), image.width(), CV_8UC1, image.bits()).clone();
    }
    else{
        return cv::Mat(42, 42, CV_8UC1);
    }
}

