#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioBuffer>
#include <QDataStream>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <chrono>
#include <cmath>
#include "qcustomplot.h"
#include "AudioFile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void performFFT(const std::vector<double>& audioData);
    void plotFFT(const std::vector<double>& magnitude);
    int FFT(int dir, int m, double *x, double *y);
    void performInverseFFT();
    void plotInverseFFT(const std::vector<double>& audioDataInverse);
    void plotAudioSignal(const std::vector<double>& audioData, double durationInSeconds);
    void butterworthLowPassFilter(std::vector<double>& signal, double sampleRate);
    void normalizeAudio(std::vector<double>& audioData);
    void saveToWavFile(const QString& fileName, const std::vector<double>& audioData, int sampleRate);

private slots:
    void on_openButton_clicked();
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_inverseFFTButton_clicked();
    void on_FFTButton_clicked();
    void on_FiltreButton_clicked();
    void updatePosition(qint64 position);
    void setPosition(int position);
    void updateSliderPosition();
    void updateDuration();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;
    uint32_t sampleRate;
    QMediaPlayer *player;
    QAudioOutput *audioOutPut;
    QTimer *timer;
    QString fileName;
    QMessageBox msgBox;
    std::vector<double> audioData; // Déclaration de la variable membre audioData
    AudioFile<double> audioFile; // Déclaration de la variable AudioFile
    double durationInSeconds; // Déclaration de la variable de la durée du piste audio
    int order; // Déclaration de la variable pour l'ordre du filtre
    double cutoffFrequency; // Déclaration de la variable de la fréquance de coupure pour le filtre
    std::vector<double> realPart; // Déclaration de la variable pour sauvegarder les données audio pour la FFT Inverse
    std::vector<double> imagPart; // Déclaration de la variable pour sauvegarder les données audio pour la FFT Inverse
};
#endif // MAINWINDOW_H
