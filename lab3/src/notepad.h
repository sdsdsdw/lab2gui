#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QSpinBox>
#include <QCoreApplication>
#include <QWidgetAction>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void clearText();
    void toUppercase();
    void toLowercase();
    void increaseFont();
    void decreaseFont();
    void removeDoubleSpaces();
    void showAboutDialog();
    void showHelp();
    void closeApp();
    void spinBoxSlot(int value);
    void documentWasModified();

private:
    QTextEdit *textEdit;
    QTabWidget *tabWidget;
    QDockWidget *fileDock;
    QDockWidget *editingDock;
    QStatusBar *statusBar;
    QLabel *temporaryStatusLabel;
    QLabel *normalStatusLabel;
    QLabel *permanentStatusLabel;
    QString currentFilePath;

    void createMenus();
    void createMenusFiles(QDockWidget *fileDock);
    void createToolbar(QDockWidget *editingDock);
    void createFileMenu();
    void createEditingMenu();
    void createHelpMenu();
    void createFileToolbar(QToolBar *firstToolBar);
    void createEditingToolbar(QToolBar *secondToolBar);
    void createFileAction(const QString &text, void (Notepad::*slot)(), QMenu *menu);
    void createEditAction(const QString &text, void (Notepad::*slot)(), QMenu *menu);
    void createHelpAction(const QString &text, void (Notepad::*slot)(), QMenu *menu);
    void createToolbarAction(const QString &text, void (Notepad::*slot)(), QToolBar *toolbar);

    void createStatusBar();
    void showTemporaryMessage(const QString &message, int timeout);
    void showNormalMessage(const QString &message);
    void showPermanentMessage(const QString &message);
    void createTab();
    QTextEdit* getCurrentTextEdit();
    QString getCurrentTabFilePath();
    void updateTabText(int tabIndex, const QString &filePath);
};

#endif // NOTEPAD_H