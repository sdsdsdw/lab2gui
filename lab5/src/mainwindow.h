// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scribblearea.h"
#include <QList>
#include <QMainWindow>
#include <QtWidgets>
#include <QDockWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    void createDockWidget();
    void penWidthChanged(int newWidth);
    void createMenu();
    ScribbleArea *scribbleArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // MAINWINDOW_H
