#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutPut(new QAudioOutput(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Sound Project");
    player->setAudioOutput(audioOutPut);

    connect(ui->labelDuration, &QLabel::objectNameChanged, this, &MainWindow::updateDuration);

    // Connecter le signal mediaStatusChanged au slot onMediaStatusChanged
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);

    // Connecter le timer au slot updateSliderPosition
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSliderPosition);
    timer->start(100); // Mettre à jour toutes les 100 ms
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    player->play();
}

void MainWindow::on_pauseButton_clicked()
{
    player->pause();
}

void MainWindow::on_stopButton_clicked()
{
    player->stop();
}

void MainWindow::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void MainWindow::setPosition(int position)
{
    player->setPosition(position);
}

void MainWindow::updateDuration()
{
    // Obtenir la fréquence d'échantillonnage et la durée
    sampleRate = audioFile.getSampleRate();
    durationInSeconds = audioFile.getLengthInSeconds();
    ui->labelDuration->setText(QString("Durée : %1 secondes").arg(durationInSeconds, 0, 'f', 2));
}

void MainWindow::updateSliderPosition()
{
    ui->positionSlider->setValue(player->position());
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::LoadedMedia)
    {
        ui->positionSlider->setValue(0);
        ui->positionSlider->setMaximum(player->duration());
    }
}

void MainWindow::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open WAV file"), "", tr("WAV Files (*.wav)"));

    // Charger le fichier WAV
    bool loaded = audioFile.load(fileName.toStdString());
    if (!loaded)
    {
        qDebug() << "Erreur lors de l'ouverture du fichier WAV!";
        return;
    }

    // Récupérer des informations sur le fichier
    int sampleRate = audioFile.getSampleRate();
    int numChannels = audioFile.getNumChannels();
    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();

    // Fusionner les canaux si nécessaire (par exemple, si c'est un fichier stéréo)
    std::vector<double> audioData(numSamplesPerChannel);

    if (numChannels == 1)
    {
        // Mono
        audioData = audioFile.samples[0];  // Utiliser directement les données si mono
    }
    else
    {
        // Stéréo : fusionner les canaux (par exemple, prendre la moyenne des deux canaux)
        for (int i = 0; i < numSamplesPerChannel; ++i)
        {
            audioData[i] = (audioFile.samples[0][i] + audioFile.samples[1][i]) / 2.0;
        }
    }

    // Display some info in labels
    ui->sampleRateLabel->setText(QString::number(sampleRate));

    // Normaliser les amplitudes
    double maxAmplitude = *std::max_element(audioData.begin(), audioData.end());
    for (auto& sample : audioData) {
        sample /= maxAmplitude;
    }

    // Récupérer le nom du fichier sélectionner
    QFileInfo fileInfo(fileName);
    QString selectedFileName = fileInfo.fileName();
    ui->labelTitleWav->setText(selectedFileName);

    // Lire le fichier audio avec le lecteur
    player->setSource(QUrl::fromLocalFile(fileName));

    // Forcé la position du Slider
    ui->positionSlider->setValue(0);
    ui->positionSlider->setMaximum(player->duration());

    // updateDuration();

    // Utiliser AudioFile pour lire le fichier audio
    audioFile.load(fileName.toStdString());

    // Afficher la durée sur labelDuration
    updateDuration();

    // Appliquer le filtre passe-bas Butterworth
    // butterworthLowPassFilter(audioData, sampleRate, 1000.0); // 1000 Hz est la fréquence de coupure

    // Afficher le signal audio avec customplot
    plotAudioSignal(audioData, durationInSeconds);
}

void MainWindow::plotFFT(const std::vector<double>& magnitude)
{
    QVector<double> x(magnitude.size()), y(magnitude.size());

    // Préparer les données FFT pour l'affichage
    for (int i = 0; i < magnitude.size(); ++i)
    {
        x[i] = i * (sampleRate / 2.0) / magnitude.size(); // Fréquence
        y[i] = magnitude[i]; // Magnitude
    }

    // Ajouter les données au graphique
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);

    // Définir les axes
    ui->customPlot->xAxis->setLabel("Frequency (Hz)");
    ui->customPlot->yAxis->setLabel("Magnitude");

    // Définir les plages des axes pour une vue plus restreinte
    ui->customPlot->xAxis->setRange(0, sampleRate / 2); // Plage de fréquences jusqu'à la moitié de la fréquence d'échantillonnage
    ui->customPlot->yAxis->setRange(0, *std::max_element(magnitude.begin(), magnitude.end()) / 2); // Ajuster la plage de magnitude

    // Mettre à jour le graphique
    ui->customPlot->replot();
}

int MainWindow::FFT(int dir,int m,double *x,double *y)
{
    int n,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;

    /* Calculate the number of points */
    n = 1;
    for (i=0;i<m;i++)
        n *= 2;

    /* Do the bit reversal */
    i2 = n >> 1;
    j = 0;
    for (i=0;i<n-1;i++) {
        if (i < j) {
            tx = x[i];
            ty = y[i];
            x[i] = x[j];
            y[i] = y[j];
            x[j] = tx;
            y[j] = ty;
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l=0;l<m;l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j=0;j<l1;j++) {
            for (i=j;i<n;i+=l2) {
                i1 = i + l1;
                t1 = u1 * x[i1] - u2 * y[i1];
                t2 = u1 * y[i1] + u2 * x[i1];
                x[i1] = x[i] - t1;
                y[i1] = y[i] - t2;
                x[i] += t1;
                y[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (dir == 1)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    if (dir == 1) {
        for (i=0;i<n;i++) {
            x[i] /= n;
            y[i] /= n;
        }
    }

    return(1);
}

void MainWindow::performFFT(const std::vector<double>& audioData)
{
    int m = log2(audioData.size()); // Nombre d'échantillons = 2^m
    std::vector<double> real(audioData); // Partie réelle
    std::vector<double> imag(audioData.size(), 0.0); // Partie imaginaire

    // Supprimer le DC offset
    double mean = std::accumulate(real.begin(), real.end(), 0.0) / real.size();
    for (size_t i = 0; i < real.size(); ++i)
    {
        real[i] -= mean;
    }

    // Appliquer une fenêtre de Hamming
    // for (size_t i = 0; i < real.size(); ++i)
    // {
    //     real[i] *= 0.54 - 0.46 * cos(2 * M_PI * i / (real.size() - 1));
    // }

    // Effectuer la FFT
    FFT(1, m, real.data(), imag.data());

    // Calculer la magnitude des fréquences
    std::vector<double> magnitude(audioData.size() / 2);
    for (size_t i = 0; i < magnitude.size(); ++i)
    {
        magnitude[i] = sqrt(real[i] * real[i] + imag[i] * imag[i]);
    }

    // Enregistrer les parties réelles et imaginaires dans des variables membres
    realPart = real;
    imagPart = imag;

    // Affichage de la FFT avec QCustomPlot
    plotFFT(magnitude);
}

void MainWindow::performInverseFFT()
{
    int m = log2(realPart.size()); // Nombre d'échantillons = 2^m

    // Effectuer la FFT inverse avec les parties réelles et imaginaires enregistrées
    FFT(-1, m, realPart.data(), imagPart.data());

    // Calculer les données audio inversées
    // std::vector<double> audioDataInverse(realPart.size());
    // for (size_t i = 0; i < audioDataInverse.size(); ++i)
    // {
    //     audioDataInverse[i] = realPart[i];
    // }

    // Normaliser les amplitudes après la FFT inverse
    for (auto& sample : realPart) {
        sample /= realPart.size();
    }

    // Calculer les données audio inversées
    std::vector<double> audioDataInverse(realPart.size());
    for (size_t i = 0; i < audioDataInverse.size(); ++i)
    {
        audioDataInverse[i] = realPart[i];
    }

    // Normaliser l'audio
    normalizeAudio(audioDataInverse);

    // Affichage de la FFT inverse avec QCustomPlot
    plotInverseFFT(audioDataInverse);
}

void MainWindow::plotInverseFFT(const std::vector<double>& audioDataInverse)
{
    QVector<double> x(audioDataInverse.size()), y(audioDataInverse.size());

    // Préparer les données FFT inverse pour l'affichage
    for (int i = 0; i < audioDataInverse.size(); ++i)
    {
        x[i] = i / static_cast<double>(sampleRate); ; // Échantillon
        y[i] = audioDataInverse[i]; // Amplitude
    }

    // Ajouter les données au graphique
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);

    // Définir les axes
    ui->customPlot->xAxis->setLabel("time (s)");
    ui->customPlot->yAxis->setLabel("Amplitude");

    // Définir les plages des axes pour une vue plus restreinte
    // ui->customPlot->xAxis->setRange(0, audioDataInverse.size() / 2); // Plage des échantillons
    // ui->customPlot->yAxis->setRange(*std::min_element(audioDataInverse.begin(), audioDataInverse.end()), *std::max_element(audioDataInverse.begin(), audioDataInverse.end()) / 2); // Ajuster la plage d'amplitude
    ui->customPlot->rescaleAxes();

    // Mettre à jour le graphique
    ui->customPlot->replot();
}

void MainWindow::on_inverseFFTButton_clicked()
{
    // Charger le fichier WAV
    // bool loaded = audioFile.load(fileName.toStdString());
    // if (!loaded)
    // {
    //     qDebug() << "Erreur lors de l'ouverture du fichier WAV!";
    //     return;
    // }

    // // Récupérer des informations sur le fichier
    // int sampleRate = audioFile.getSampleRate();
    // int numChannels = audioFile.getNumChannels();
    // int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();

    // qDebug() << "Sample Rate:" << sampleRate;
    // qDebug() << "Number of Channels:" << numChannels;
    // qDebug() << "Number of Samples per Channel:" << numSamplesPerChannel;

    // // Fusionner les canaux si nécessaire (par exemple, si c'est un fichier stéréo)
    // std::vector<double> audioData(numSamplesPerChannel);

    // if (numChannels == 1)
    // {
    //     // Mono
    //     audioData = audioFile.samples[0];  // Utiliser directement les données si mono
    // }
    // else
    // {
    //     // Stéréo : fusionner les canaux (par exemple, prendre la moyenne des deux canaux)
    //     for (int i = 0; i < numSamplesPerChannel; ++i)
    //     {
    //         audioData[i] = (audioFile.samples[0][i] + audioFile.samples[1][i]) / 2.0;
    //     }
    // }

    // Effectuer la FFT inverse sur les données audio
    performInverseFFT();
}

void MainWindow::plotAudioSignal(const std::vector<double>& audioData, double durationInSeconds)
{
    QVector<double> x(audioData.size()), y(audioData.size());

    // Préparer les données audio pour l'affichage
    for (int i = 0; i < audioData.size(); ++i)
    {
        x[i] = i / static_cast<double>(sampleRate); // Échantillon en secondes
        y[i] = audioData[i]; // Amplitude
    }

    // Ajouter la durée
    QVector<double> time(x.size());
    for (int i = 0; i < x.size(); ++i) {
        time[i] = i / static_cast<double>(audioFile.getSampleRate());
    }

    // Ajouter les données au graphique
    ui->waveSignalPlot->addGraph();
    ui->waveSignalPlot->graph(0)->setData(time, y);

    // Définir les axes
    ui->waveSignalPlot->xAxis->setLabel("Time (s)");
    ui->waveSignalPlot->yAxis->setLabel("Amplitude");

    // Définir les plages des axes pour une vue plus restreinte
    ui->waveSignalPlot->xAxis->setRange(0, durationInSeconds/ 2); // Plage de temps en secondes
    ui->waveSignalPlot->yAxis->setRange(-1, 1); // Plage d'amplitude normalisée
    ui->waveSignalPlot->rescaleAxes();

    // Mettre à jour le graphique
    ui->waveSignalPlot->replot();
}

void MainWindow::butterworthLowPassFilter(std::vector<double>& signal, double sampleRate)
{
    // Get the order filter
    order = ui->comboBoxOrdreFiltre->currentIndex() + 1;

    // Get the cut off frequency
    cutoffFrequency = ui->lineEditFrequenceCoupure->text().toDouble();

    double wc = tan(M_PI * cutoffFrequency / sampleRate);
    double k1 = wc * wc;
    double k2 = sqrt(2.0) * wc;
    double k3 = wc * wc;

    double a0 = k1 / (1.0 + k2 + k3);
    double a1 = 2.0 * a0;
    double a2 = a0;
    double b1 = 2.0 * (k1 - 1.0) / (1.0 + k2 + k3);
    double b2 = (1.0 - k2 + k3) / (1.0 + k2 + k3);

    std::vector<double> filteredSignal(signal.size());

    for (size_t i = 2; i < signal.size(); ++i)
    {
        filteredSignal[i] = a0 * signal[i] + a1 * signal[i - 1] + a2 * signal[i - 2]
                            - b1 * filteredSignal[i - 1] - b2 * filteredSignal[i - 2];
    }

    signal = filteredSignal;
}

void MainWindow::on_FFTButton_clicked()
{
    // Charger le fichier WAV
    bool loaded = audioFile.load(fileName.toStdString());
    if (!loaded)
    {
        qDebug() << "Erreur lors de l'ouverture du fichier WAV!";
        return;
    }

    // Récupérer des informations sur le fichier
    int sampleRate = audioFile.getSampleRate();
    int numChannels = audioFile.getNumChannels();
    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();

    qDebug() << "Sample Rate:" << sampleRate;
    qDebug() << "Number of Channels:" << numChannels;
    qDebug() << "Number of Samples per Channel:" << numSamplesPerChannel;

    // Fusionner les canaux si nécessaire (par exemple, si c'est un fichier stéréo)
    std::vector<double> audioData(numSamplesPerChannel);

    if (numChannels == 1)
    {
        // Mono
        audioData = audioFile.samples[0];  // Utiliser directement les données si mono
    }
    else
    {
        // Stéréo : fusionner les canaux (par exemple, prendre la moyenne des deux canaux)
        for (int i = 0; i < numSamplesPerChannel; ++i)
        {
            audioData[i] = (audioFile.samples[0][i] + audioFile.samples[1][i]) / 2.0;
        }
    }

    // Effectuer la FFT sur les données audio
    performFFT(audioData);
}

void MainWindow::on_FiltreButton_clicked()
{
    // Charger le fichier WAV
    bool loaded = audioFile.load(fileName.toStdString());
    if (!loaded)
    {
        qDebug() << "Erreur lors de l'ouverture du fichier WAV!";
        return;
    }

    // Récupérer des informations sur le fichier
    int sampleRate = audioFile.getSampleRate();
    int numChannels = audioFile.getNumChannels();
    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();

    // Fusionner les canaux si nécessaire (par exemple, si c'est un fichier stéréo)
    std::vector<double> audioData(numSamplesPerChannel);

    if (numChannels == 1)
    {
        // Mono
        audioData = audioFile.samples[0];  // Utiliser directement les données si mono
    }
    else
    {
        // Stéréo : fusionner les canaux (par exemple, prendre la moyenne des deux canaux)
        for (int i = 0; i < numSamplesPerChannel; ++i)
        {
            audioData[i] = (audioFile.samples[0][i] + audioFile.samples[1][i]) / 2.0;
        }
    }

    // Normaliser les amplitudes
    double maxAmplitude = *std::max_element(audioData.begin(), audioData.end());
    for (auto& sample : audioData) {
        sample /= maxAmplitude;
    }

    // Lire le fichier audio avec le lecteur
    player->setSource(QUrl::fromLocalFile(fileName));

    // Utiliser AudioFile pour lire le fichier audio
    audioFile.load(fileName.toStdString());


    // Appliquer le filtre passe-bas Butterworth
    butterworthLowPassFilter(audioData, sampleRate);

    // Sauvegarder le signal audio filtré dans un nouveau fichier WAV
    saveToWavFile("filtered_audio.wav", audioData, sampleRate);

    // Afficher le signal audio avec customplot
    plotAudioSignal(audioData, durationInSeconds);
}

void MainWindow::normalizeAudio(std::vector<double>& audioData)
{
    // Trouver l'amplitude maximale dans le signal audio
    double maxAmplitude = *std::max_element(audioData.begin(), audioData.end());

    // Diviser chaque échantillon par l'amplitude maximale
    for (auto& sample : audioData)
    {
        sample /= maxAmplitude;
    }
}

// void MainWindow::saveToWavFile(const QString& fileName, const std::vector<double>& audioData, int sampleRate, int numChannels)
// {
//     QFile file(fileName);
//     if (!file.open(QIODevice::WriteOnly))
//     {
//         qDebug() << "Impossible d'ouvrir le fichier pour écriture!";
//         return;
//     }

//     QDataStream out(&file);

//     // Écrire l'en-tête WAV
//     out.writeRawData("RIFF", 4);
//     quint32 fileSize = 36 + audioData.size() * 2;
//     out.writeBytes(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
//     out.writeRawData("WAVE", 4);
//     out.writeRawData("fmt ", 4);
//     quint32 fmtSize = 16;
//     out.writeBytes(reinterpret_cast<const char*>(&fmtSize), sizeof(fmtSize));
//     quint16 audioFormat = 1;
//     out.writeBytes(reinterpret_cast<const char*>(&audioFormat), sizeof(audioFormat));
//     out.writeBytes(reinterpret_cast<const char*>(&numChannels), sizeof(numChannels));
//     out.writeBytes(reinterpret_cast<const char*>(&sampleRate), sizeof(sampleRate));
//     quint32 byteRate = sampleRate * numChannels * 2;
//     out.writeBytes(reinterpret_cast<const char*>(&byteRate), sizeof(byteRate));
//     quint16 blockAlign = numChannels * 2;
//     out.writeBytes(reinterpret_cast<const char*>(&blockAlign), sizeof(blockAlign));
//     quint16 bitsPerSample = 16;
//     out.writeBytes(reinterpret_cast<const char*>(&bitsPerSample), sizeof(bitsPerSample));
//     out.writeRawData("data", 4);
//     quint32 dataSize = audioData.size() * 2;
//     out.writeBytes(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));

//     // Écrire les données audio
//     for (auto sample : audioData)
//     {
//         qint16 intSample = static_cast<qint16>(sample * 32767);
//         out.writeBytes(reinterpret_cast<const char*>(&intSample), sizeof(intSample));
//     }

//     file.close();



// }


void MainWindow::saveToWavFile(const QString &filePath, const std::vector<double> &data, int sampleRate)
{
    audioFile.setNumChannels(1);
    audioFile.setSampleRate(sampleRate);
    audioFile.samples[0].resize(data.size());
    for (int i = 0; i < data.size(); ++i) {
        // Assurez-vous que les valeurs sont comprises entre -1 et 1
        audioFile.samples[0][i] = std::max(-1.0, std::min(1.0, data[i]));
    }
    audioFile.save(filePath.toStdString());

        // Message pour la sauvegarde de l'audio
        msgBox.setText("Un fichier audio viens d'être sauvegarder.");
        msgBox.exec();
}
