//imageEditor.hpp

#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QApplication>
#include <QVBoxLayout>
#include <QSharedPointer>
#include <algorithm>
#include <QVector2D>
#include <QtMath>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QSlider>
#include <QSpinBox>
#include <QRadioButton>
#include <QWidgetAction>

class ImageEditor : public QMainWindow
{
    Q_OBJECT

public:
    ImageEditor(QWidget *parent = nullptr);
    ~ImageEditor();

private slots:
    void openImage();
    void saveImage();
    void grayscale();
    void sepia();
    void invert();
    void pixelize();
    void rotateImage();
    void updatePixelize(int cellSize);
    void updateTwirlAngle(int angle);
    void updateBrightness(int value);
    void setGrayscale();
    void setSepia();
    void setInvert();
private:
    void setupMenu();
    void setupCentralWidget();
    void setupLeftPanel();
    void setupRightPanel();
    void drawImage();
    void adjustBrightness(int value);
    QRgb averageBlockColor(const QImage &block);

    QLabel imageLabel;
    QPixmap pixmap;
    QImage image;

    QSpinBox *pixelizeSpinBox;
    QSlider *twirlSlider;
    QSlider *brightnessSlider;
    QLabel *pixelizeLabel;
    QLabel *twirlLabel;
    QLabel *brightnessLabel;
};