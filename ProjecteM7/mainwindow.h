#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QUrl url;
    QList<QString> list;
    int cançoPrincipi = 0;
    int pause = 0;

private slots:
    void on_pushButton_play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_audio_clicked();

    void on_pushButton_Seguent_clicked();

    void on_pushButton_anterior_clicked();

    void on_verticalSlider_Volume_valueChanged(int value);

    void positionChanged(qint64 progress);

    void nextSong();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
