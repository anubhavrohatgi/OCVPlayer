#include "videothread.h"


VideoThread::VideoThread(QObject *parent) : QThread(parent)
{
    mstop = true;
}


VideoThread::~VideoThread()
{
    mutex.lock();
    mstop = true;
    cap.release();
    mwait.wakeOne();
    mutex.unlock();
    wait();
}

bool VideoThread::loadVideo(const QString& filename)
{
    cap.open(filename.toStdString());
    if (cap.isOpened())
    {
        frameRate = (int) cap.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void VideoThread::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            mstop = false;
        }
        start(LowPriority);
    }
}

void VideoThread::run()
{
    int delay = (1000/frameRate);
    while(!mstop){
        if (!cap.read(frame))
        {
            mstop = true;
        }

        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        emit getImage(img);
        this->msleep(delay);
    }
}



void VideoThread::Stop()
{
    mstop = true;
}


void VideoThread::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}


bool VideoThread::isStopped() const{
    return this->mstop;
}
