#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

    ui->pushButton_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));


    /*connect(player, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        ui->tempsCancion->setText(QString::number(pos));
        ui->horizontalSlider_songDuration->setValue(pos);
    });*/
    connect(player, &QMediaPlayer::durationChanged, [&](qint64 dur) {
        ui->horizontalSlider_songDuration->setMaximum(dur);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::positionChanged(qint64 progress) {
    QTime duration(0, (progress / 60000) % 60, (progress / 1000) % 60);
    QString timeStr = duration.toString("m:ss");
    ui->tempsCancion->setText(timeStr + "/" + QTime(0, (player->duration() / 60000) % 60, (player->duration() / 1000) % 60).toString("m:ss"));

    ui->horizontalSlider_songDuration->setValue(progress);

    if (ui->horizontalSlider_songDuration->value() == ui->horizontalSlider_songDuration->maximum()) {

       //nextSong();
    }
}

void MainWindow::nextSong(){

    //Primer canço de la listWidget
    int cançoActual = 0;

    if(ui->listWidget->currentRow() != ui->listWidget->count() - 1){
        cançoActual = ui->listWidget->currentRow() + 1;
    }

    ui->listWidget->setCurrentRow(cançoActual);
    QString canço = ui->listWidget->currentItem()->text();
    url = QUrl::fromLocalFile(canço);
    player->setSource(url);
    player->play();
}

void MainWindow::on_pushButton_play_clicked()
{
    //// en premer el boto play
    if(cançoPrincipi == 0){
        QString canço = ui->listWidget->item(cançoPrincipi)->text();
        ui->listWidget->setCurrentRow(cançoPrincipi);
        url = QUrl::fromLocalFile(canço);
        cançoPrincipi++;
    }
    player->setSource(url);
    player->play();
}


void MainWindow::on_pushButton_Pause_clicked()
{
    if(pause != 0){
       pause = 0;
       player->play();
       ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else{
       player->pause();
       pause = 1;
       ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    }

}


void MainWindow::on_pushButton_Stop_clicked()
{
    player->stop();
}

void MainWindow::on_verticalSlider_Volume_valueChanged(int value)
{
    qreal linearVolume = QAudio::convertVolume(value / qreal(100.0),
                                                   QAudio::LogarithmicVolumeScale,
                                                   QAudio::LinearVolumeScale);

    //ui->lavel_volum->setText(QString::number(value));
    audioOutput->setVolume(linearVolume);
}

void MainWindow::on_pushButton_audio_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"),"",tr("MP3 Files (*.MP3)"));

    QFileInfo FileAudio(FileName);
    ui->listWidget->addItem(FileName);

}

void MainWindow::on_pushButton_Seguent_clicked()
{
    //Primer canço de la listWidget
    int cançoActual = 0;

    if(ui->listWidget->currentRow() != ui->listWidget->count() - 1){
        cançoActual = ui->listWidget->currentRow() + 1;
    }

    ui->listWidget->setCurrentRow(cançoActual);
    QString canço = ui->listWidget->currentItem()->text();
    url = QUrl::fromLocalFile(canço);
}

void MainWindow::on_pushButton_anterior_clicked()
{
    //Ultima canço de la listWidget
    int ultimaCanço = ui->listWidget->count() - 1;

    if(ui->listWidget->currentRow() == 0){
        //Estas a la primera canço
    } else{
       ultimaCanço = ui->listWidget->currentRow() - 1;
    }

    ui->listWidget->setCurrentRow(ultimaCanço);
    QString canço = ui->listWidget->currentItem()->text();
    url = QUrl::fromLocalFile(canço);
}

