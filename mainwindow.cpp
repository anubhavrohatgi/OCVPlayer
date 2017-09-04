#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    vthread = new VideoThread();
    QObject::connect(vthread, SIGNAL(getImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)),
                              vthread, SLOT(onChangecbox(QString)));
}

MainWindow::~MainWindow()
{
    delete vthread;
    delete ui;
}


void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(vthread->isRunning()){
        vthread->Stop();

        ui->label->clear();
        ui->pushButton_2->setText(tr("Play"));
    }
    QString filename = QFileDialog::getOpenFileName(this,
                                          tr("Open Video"), ".",
                                          tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty()){
        if (!vthread->loadVideo(filename))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (vthread->isStopped())
    {
        vthread->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        vthread->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
