#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QImage>
#include <QWaitCondition>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class VideoThread : public QThread
{    Q_OBJECT

 public:
    //Constructor
    VideoThread(QObject *parent = 0);

    //Destructor
    ~VideoThread();

    //Load a video from memory
    bool loadVideo(const QString& filename);

    //Play the video
    void Play();

    //Stop the video
    void Stop();

    //check if the player has been stopped
    bool isStopped() const;

 private:
    bool mstop;
    QMutex mutex;
    QWaitCondition mwait;
    cv::Mat frame;
    int frameRate;
   cv::VideoCapture cap;
    cv::Mat RGBframe;
    QImage img;

 signals:
    //Signal to output frame to be displayed
    void getImage(const QImage &image);

 protected:
     void run();
     void msleep(int ms);

};

#endif // VIDEOTHREAD_H
