#include <QApplication>
#include "imageEditor.hpp"

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    ImageEditor editor;
    editor.show();
    return app.exec();
}