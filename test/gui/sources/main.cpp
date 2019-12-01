
// Include
#include "mainframe.h"

/** Default app */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create
    mainframe calculator;
    {
        calculator.show();
    }

    // Run
    return app.exec();
}
