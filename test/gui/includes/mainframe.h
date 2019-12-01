#pragma once

// This file contains for now 3 classes. Everything is here there is no cpp file
// digitBtn is our QPushButton custom class
// digiPad is a widget formed by some digitBtn
// mainframe is our main window

// Qt includes
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

// Stl include
#include <sstream>

// Our include
#include "core/includes/core.h"

/**
 * @brief The digitBtn class
 * Extension from QPushButton class in order to reemit click with a button index info
 */
class digitBtn : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief digitBtn constructor
     * @param pParent : parent widget
     * @param pIndex : index of this button
     * @param pText : text on this button
     */
    digitBtn(QWidget* pParent, int pIndex, const QString& pText)
        : QPushButton(pText, pParent)
        , mIndex(pIndex)
    {
        this->connect(this, SIGNAL(clicked()), this, SLOT(reEmitClick()));
    }

private slots:
    /**
     * @brief reEmitClick slot is connected to "clicked signal" of QPushButton
     * its emit onClick signal with this button index
     */
    inline void reEmitClick()
    {
        emit onClick(this->mIndex);
    }

signals:
    /**
     * @brief onClick signal prototype (only prototype needed)
     * @param pIndex : info to be transmitted.
     */
    void onClick(int);

private:
    int mIndex; /**< index of this button */

};

/**
 * @brief The digiPad class
 * Define 10 digits + dot buttons
 */
class digiPad : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief digiPad constructor
     * @param pParent : parent widget where this is to be placed
     */
    digiPad(QWidget* pParent) : QWidget(pParent)
    {
        this->instanciate();
    }

public:
    /**
     * @brief instanciate
     * Create an instance of this widget
     */
    inline void instanciate()
    {
        // Declare once a table of digit text
        static const QString gDigitText[11] = {"7","8","9","4","5","6","1","2","3","0","."};

        // Setup of our 10 digits items
        for (int i = 0; i <= 10; i++)
        {
            // Digit text (a number btw 0 and 9 or a dot)
            const QString& lText = gDigitText[i];

            // Create a button for that number
            this->mDigitBtns[i] = new digitBtn(this, i, lText);

            // Place it on this parent widget screen
            this->place(this->mDigitBtns[i], i);

            // Connect that button to a common slot
            this->connect(this->mDigitBtns[i], SIGNAL(onClick(int)), this, SLOT(onDigit(int)));
        }
    }

public:
    /**
     * @brief size of this widget
     * @return size
     */
    inline QSize size() const
    {
        return this->mFitSize;
    }

private slots:
    /**
     * @brief onDigit is called when a digit button was clicked
     * @param pValue : integer value corresponding to that button
     */
    inline void onDigit(int pIndex)
    {
        // Declare once the index to value converter
        static const int gConvert[11] = {7, 8, 9, 4, 5, 6, 1, 2, 3, 0, 0};

        // Get the correct value from index (0 to 9 and dot)
        int lValue = gConvert[pIndex];

        // Debug message
        std::stringstream lSt;
        {
            pIndex < 10 ? lSt << "button " << lValue : lSt << "button dot";
            lSt << " clicked!";
        }

        // Print debug message
        QMessageBox::information(this, "test", lSt.str().c_str());
    }

private:
    /**
     * @brief place a given button on the screen according to its index
     * @param pButton : target button
     * @param pIndex : index from 0 to 10
     */
    inline void place(digitBtn* pButton, int pIndex)
    {
        // Parameters of size and position
        static const int mBtnWidth = 50;
        static const int mBtnHeight = 50;
        static const int mBtnPadding = 10;
        static const int mOffsetX = mBtnPadding;
        static const int mOffsetY = mBtnPadding;

        // Eval row and column corresponding to the index
        const int lRowIndex = pIndex / 3;
        const int lColumnIndex = pIndex % 3;

        // Eval x and y position on the screen (px)
        int lXpos = mOffsetX + lColumnIndex*(mBtnPadding + mBtnWidth);
        int lYpos = mOffsetY + lRowIndex*(mBtnPadding + mBtnHeight);

        // Default button width
        int lWidth = mBtnWidth;
        {
            // Special treatment for the index = 9 (button 0 on the fourth row)
            lWidth += pIndex == 9 ? (mBtnWidth + mBtnPadding) : 0;

            // Special treatment for the index = 10 (dot button also on the fourth row)
            lXpos += pIndex == 10 ? (mBtnWidth + mBtnPadding) : 0;
        }

        // Update widget fitting size
        this->mFitSize = this->mFitSize.expandedTo(QSize(lXpos + lWidth + mBtnPadding, lYpos + mBtnHeight + mBtnPadding));

        // Final
        pButton->setGeometry(lXpos, lYpos, lWidth, mBtnHeight);

    }

private:
    digitBtn* mDigitBtns[11]; /**< We have 11 buttons (0 to 9 and dot) */
    QSize mFitSize; /**< The required size of parent to fit this widget (w and h in px) */
};

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
    mainframe() : QWidget()
    {
        this->instanciate();
    }

public:
    /**
     * @brief instanciate
     * Create an instance of this window
     */
    inline void instanciate()
    {
        // Instanciate a digipad
        this->mDigiPad = new digiPad(this);

        // Fit the windows size to this widget
        this->setFixedSize(this->mDigiPad->size());

        // Instanciate operator buttons
        // @todo
    }


private:
    digiPad* mDigiPad; /**< Our home made and lovely digit pad widget */
    digitBtn* mOperators[4]; /**< @todo */

};
