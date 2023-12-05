#include "mainwindow.h"
#include "scribblearea.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), scribbleArea(new ScribbleArea(this))
{
    setCentralWidget(scribbleArea);
    setWindowTitle(tr("Paint"));
    resize(700, 500);

    createMenu();
    createDockWidget();
}

MainWindow::~MainWindow() {}

void MainWindow::createMenu()
{
    QMenuBar *menuBar = this->menuBar();

    // Меню "File"
    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QAction *openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(tr("Save"), this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAction);

    fileMenu->addSeparator();  // Разделитель

    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitAction);

    // Меню "Edit"
    QMenu *editMenu = menuBar->addMenu(tr("Edit"));

    QAction *penColorAction = new QAction(tr("Select Pen Color"), this);
    connect(penColorAction, &QAction::triggered, this, &MainWindow::penColor);
    editMenu->addAction(penColorAction);

    QAction *penWidthAction = new QAction(tr("Select Pen Width"), this);
    connect(penWidthAction, &QAction::triggered, this, &MainWindow::penWidth);
    editMenu->addAction(penWidthAction);

    // Меню "Help"
    QMenu *helpMenu = menuBar->addMenu(tr("Help"));

    QAction *aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createDockWidget()
{
    QDockWidget *dockWidget = new QDockWidget(tr("Brush Settings"), this);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    QWidget *dockWidgetContent = new QWidget(dockWidget);

    QVBoxLayout *layout = new QVBoxLayout(dockWidgetContent);

    QSlider *penWidthSlider = new QSlider(Qt::Horizontal);
    penWidthSlider->setRange(1, 50);
    penWidthSlider->setValue(scribbleArea->penWidth());
    connect(penWidthSlider, &QSlider::valueChanged, this, &MainWindow::penWidthChanged);
    layout->addWidget(penWidthSlider);

    QPushButton *penColorButton = new QPushButton(tr("Select Pen Color"));
    connect(penColorButton, &QPushButton::clicked, this, &MainWindow::penColor);
    layout->addWidget(penColorButton);

    dockWidgetContent->setLayout(layout);
    dockWidget->setWidget(dockWidgetContent);
}

void MainWindow::penWidthChanged(int newWidth)
{
    scribbleArea->setPenWidth(newWidth);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::open()
{
    if (maybeSave()) 
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width:"), scribbleArea->penWidth(), 1, 50, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"), tr("example"));
}

bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Scribble"), tr("The image has been modified.\n"
                                                           "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile("png");
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return scribbleArea->saveImage(fileName, fileFormat.constData());
}
