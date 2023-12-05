#include "imageEditor.hpp"

ImageEditor::ImageEditor(QWidget *parent) : QMainWindow(parent), imageLabel(this)
{
    setWindowTitle("Image Editor");
    resize(800, 600);

    setupMenu();
    setupCentralWidget();
    setupLeftPanel();
    setupRightPanel();
}

ImageEditor::~ImageEditor()
{
    pixmap = QPixmap();
}

void ImageEditor::setupMenu() 
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));

    QAction *openAction = new QAction(tr("Open Image"), this);
    connect(openAction, &QAction::triggered, this, &ImageEditor::openImage);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(tr("Save Image"), this);
    connect(saveAction, &QAction::triggered, this, &ImageEditor::saveImage);
    fileMenu->addAction(saveAction);

    QMenu *imageProcessingMenu = menuBar()->addMenu(tr("Image Processing"));

    QAction *grayscaleAction = new QAction(tr("Grayscale"), this);
    connect(grayscaleAction, &QAction::triggered, this, &ImageEditor::grayscale);
    imageProcessingMenu->addAction(grayscaleAction);

    QAction *sepiaAction = new QAction(tr("Sepia"), this);
    connect(sepiaAction, &QAction::triggered, this, &ImageEditor::sepia);
    imageProcessingMenu->addAction(sepiaAction);

    QAction *invertAction = new QAction(tr("Invert"), this);
    connect(invertAction, &QAction::triggered, this, &ImageEditor::invert);
    imageProcessingMenu->addAction(invertAction);

    QAction *pixelizeAction = new QAction(tr("Pixelize"), this);
    connect(pixelizeAction, &QAction::triggered, this, &ImageEditor::pixelize);
    imageProcessingMenu->addAction(pixelizeAction);

    QAction *rotateAction = new QAction(tr("Rotate"), this);
    connect(rotateAction, &QAction::triggered, this, &ImageEditor::rotateImage);
    imageProcessingMenu->addAction(rotateAction);
}

void ImageEditor::updatePixelize(int cellSize)
{
    pixelize();
}

void ImageEditor::updateTwirlAngle(int angle)
{
    rotateImage();
}

void ImageEditor::updateBrightness(int value)
{
    adjustBrightness(value);
}

void ImageEditor::setGrayscale()
{
    grayscale();
}

void ImageEditor::setSepia()
{
    sepia();
}

void ImageEditor::setInvert()
{
    invert();
}

void ImageEditor::setupCentralWidget()
{
    setCentralWidget(&imageLabel);

    imageLabel.resize(800, 600);
}

void ImageEditor::setupLeftPanel()
{
    QDockWidget *leftDock = new QDockWidget(" ", this);
    leftDock->setWidget(&imageLabel);
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
}

void ImageEditor::setupRightPanel()
{
    QRadioButton *radioButton1 = new QRadioButton("Grayscale", this);
    QRadioButton *radioButton2 = new QRadioButton("Sepia", this);
    QRadioButton *radioButton3 = new QRadioButton("Invert", this);

    connect(radioButton1, &QRadioButton::toggled, this, &ImageEditor::grayscale);
    connect(radioButton2, &QRadioButton::toggled, this, &ImageEditor::sepia);
    connect(radioButton3, &QRadioButton::toggled, this, &ImageEditor::invert);

    QVBoxLayout *sliderLayout = new QVBoxLayout;
    sliderLayout->addWidget(radioButton1);
    sliderLayout->addWidget(radioButton2);
    sliderLayout->addWidget(radioButton3);

    pixelizeLabel = new QLabel("Pixelize:", this);
    pixelizeSpinBox = new QSpinBox(this);
    pixelizeSpinBox->setRange(1, 100);
    pixelizeSpinBox->setValue(1);
    connect(pixelizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ImageEditor::pixelize);

    twirlLabel = new QLabel("Twirl Angle:", this);
    twirlSlider = new QSlider(Qt::Horizontal, this);
    twirlSlider->setRange(0, 360);
    twirlSlider->setValue(180);
    connect(twirlSlider, &QSlider::valueChanged, this, &ImageEditor::updateTwirlAngle);

    sliderLayout->addWidget(pixelizeLabel);
    sliderLayout->addWidget(pixelizeSpinBox);
    sliderLayout->addWidget(twirlLabel);
    sliderLayout->addWidget(twirlSlider);

    brightnessLabel = new QLabel("Brightness:", this);
    brightnessSlider = new QSlider(Qt::Horizontal, this);
    brightnessSlider->setRange(-255, 255);
    brightnessSlider->setValue(0);  
    connect(brightnessSlider, &QSlider::valueChanged, this, &ImageEditor::updateBrightness);

    sliderLayout->addWidget(brightnessLabel);
    sliderLayout->addWidget(brightnessSlider);

    QPushButton *openImageButton = new QPushButton("Open Image", this);
    connect(openImageButton, &QPushButton::clicked, this, &ImageEditor::openImage);

    QPushButton *saveImageButton = new QPushButton("Save Image", this);
    connect(saveImageButton, &QPushButton::clicked, this, &ImageEditor::saveImage);

    QWidget *buttonContainer = new QWidget(this);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->addLayout(sliderLayout);
    buttonLayout->addWidget(openImageButton);
    buttonLayout->addWidget(saveImageButton);

    QDockWidget *rightDock = new QDockWidget(" ", this);
    rightDock->setWidget(buttonContainer);
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rightDock->setAllowedAreas(Qt::RightDockWidgetArea);

    rightDock->setMaximumWidth(200);

    rightDock->setMinimumHeight(this->height());
    rightDock->setMaximumHeight(this->height());

    addDockWidget(Qt::RightDockWidgetArea, rightDock);
}

void ImageEditor::drawImage()
{
    imageLabel.setPixmap(pixmap.scaled(imageLabel.size(), Qt::KeepAspectRatio));
}

void ImageEditor::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    image.load(fileName);
    if (image.isNull()) 
    {
        QMessageBox::warning(this,
        QGuiApplication::applicationDisplayName(),
        tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    pixmap = QPixmap::fromImage(image);
    drawImage();
}

void ImageEditor::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        QString(),
        tr("Image file (*.jpg);;All Files (*)"));

    if (fileName.isEmpty())
        return;

    if (!image.save(fileName)) 
    {
        QMessageBox::warning(
            this,
            QGuiApplication::applicationDisplayName(),
            tr("Error saving %1").arg(QDir::toNativeSeparators(fileName)));
    }
}

void ImageEditor::grayscale()
{
    QImage imgCopy = image.copy(image.rect());
    int red=0, green=0, blue=0;

    for(int i=0; i < imgCopy.height(); i++)
    {
        for(int j = 0; j < imgCopy.width(); j++)
        {
            red = imgCopy.pixelColor(j, i).red();
            green = imgCopy.pixelColor(j, i).green();
            blue = imgCopy.pixelColor(j, i).blue();
            int mean = (red + green + blue) / 3;
            image.setPixel(j, i, qRgb(mean, mean, mean));
        }
    }
    pixmap = QPixmap::fromImage(image);
    drawImage();
}

void ImageEditor::sepia()
{
    QImage imgCopy = image.copy(image.rect());

    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            int red = imgCopy.pixelColor(j, i).red();
            int green = imgCopy.pixelColor(j, i).green();
            int blue = imgCopy.pixelColor(j, i).blue();

            int newRed = static_cast<int>(0.393 * red + 0.769 * green + 0.189 * blue);
            int newGreen = static_cast<int>(0.349 * red + 0.686 * green + 0.168 * blue);
            int newBlue = static_cast<int>(0.272 * red + 0.534 * green + 0.131 * blue);

            newRed = qBound(0, newRed, 255);
            newGreen = qBound(0, newGreen, 255);
            newBlue = qBound(0, newBlue, 255);

            image.setPixel(j, i, qRgb(newRed, newGreen, newBlue));
        }
    }

    pixmap = QPixmap::fromImage(image);
    drawImage();
}

void ImageEditor::invert()
{
    QImage imgCopy = image.copy(image.rect());

    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            int red = 255 - imgCopy.pixelColor(j, i).red();
            int green = 255 - imgCopy.pixelColor(j, i).green();
            int blue = 255 - imgCopy.pixelColor(j, i).blue();

            image.setPixel(j, i, qRgb(red, green, blue));
        }
    }

    pixmap = QPixmap::fromImage(image);
    drawImage();
}

void ImageEditor::pixelize()
{
    const int CELL_SIZE = pixelizeSpinBox->value();

    for (int i = 0; i < image.height(); i += CELL_SIZE) 
    {
        for (int j = 0; j < image.width(); j += CELL_SIZE) 
        {
            QImage imgCell = image.copy(j, i, CELL_SIZE, CELL_SIZE);
            QRgb rgb = averageBlockColor(imgCell);

            for (int y = i; y < std::min(i + CELL_SIZE, image.height()); y++)
            {
                for (int x = j; x < std::min(j + CELL_SIZE, image.width()); x++) 
                {
                    image.setPixel(x, y, rgb);
                }
            }
        }
    }

    pixmap = QPixmap::fromImage(image);
    drawImage();
}

QRgb ImageEditor::averageBlockColor(const QImage &block)
{
    int totalRed = 0, totalGreen = 0, totalBlue = 0;

    for (int y = 0; y < block.height(); y++) 
    {
        for (int x = 0; x < block.width(); x++) 
        {
            QRgb pixelColor = block.pixel(x, y);
            totalRed += qRed(pixelColor);
            totalGreen += qGreen(pixelColor);
            totalBlue += qBlue(pixelColor);
        }
    }

    int numPixels = block.width() * block.height();
    int avgRed = totalRed / numPixels;
    int avgGreen = totalGreen / numPixels;
    int avgBlue = totalBlue / numPixels;

    return qRgb(avgRed, avgGreen, avgBlue);
}

void ImageEditor::rotateImage() 
{
    QImage imgCopy = image.copy(image.rect());
    float maxDistance = QVector2D(imgCopy.width(), imgCopy.height()).length() / 2;
    QVector2D imageCenter(imgCopy.width() / 2, imgCopy.height() / 2);
    float maxAngle = 2.0;

    for (int i = 0; i < imgCopy.height(); i++)
    {
        for (int j = 0; j < imgCopy.width(); j++)
        {
            QVector2D currentPos(j, i);
            QVector2D v = currentPos - imageCenter;
            float r = v.length();
            float twirlAngle = r / maxDistance * maxAngle;
            float angle = atan2(v.y(), v.x());
            QVector2D out(r * cos(angle + twirlAngle) + imageCenter.x(),
                          r * sin(angle + twirlAngle) + imageCenter.y());

            int x = static_cast<int>(out.x());
            int y = static_cast<int>(out.y());

            x = qBound(0, x, imgCopy.width() - 1);
            y = qBound(0, y, imgCopy.height() - 1);

            imgCopy.setPixel(j, i, image.pixel(x, y));
        }
    }

    image = imgCopy.copy(imgCopy.rect());
    pixmap = QPixmap::fromImage(image);
    drawImage();
}

void ImageEditor::adjustBrightness(int value)
{
    QImage imgCopy = image.copy(image.rect());

    for (int i = 0; i < imgCopy.height(); i++) 
    {
        for (int j = 0; j < imgCopy.width(); j++) 
        {
            int red = imgCopy.pixelColor(j, i).red() + value;
            int green = imgCopy.pixelColor(j, i).green() + value;
            int blue = imgCopy.pixelColor(j, i).blue() + value;

            red = qBound(0, red, 255);
            green = qBound(0, green, 255);
            blue = qBound(0, blue, 255);

            image.setPixel(j, i, qRgb(red, green, blue));
        }
    }

    pixmap = QPixmap::fromImage(image);
    drawImage();
}