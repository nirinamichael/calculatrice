#pragma once

// Includes
#include <QWidget>
#include <QApplication>
#include <QPushButton>

/**
 * @class Mainframe class definition
 * This class  defines the main window app
 */
class mainframe : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief mainframe
     * Constructor which instanciates the app
     */
    mainframe(QApplication& pApp)
        : QWidget()
        , mApp(&pApp)
        , mButton(nullptr)
    { this->instanciate();}

public:
    /**
     * @brief instanciate
     * Create an instance of this window
     */
    inline void instanciate()
    {
        this->setFixedSize(300, 100);
        this->mButton = new QPushButton("Exit", this);
        this->mButton->move(100,0);
        this->connect(
                    this->mButton,
                    SIGNAL(clicked()),
                    qApp,
                    SLOT(quit()));
    }

private:
    QApplication* mApp;
    QPushButton* mButton;

};
