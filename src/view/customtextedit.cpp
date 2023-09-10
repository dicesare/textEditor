// customtextedit.cpp
#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent), m_isModified(false)
{
    // Connect the textChanged signal to the onTextChanged slot
    // Initialize m_previousText to the initial content of the text editor
    connect(this, &QTextEdit::textChanged, this, &CustomTextEdit::onTextChanged);
    m_previousText = toPlainText();
}

bool CustomTextEdit::isTextChanged() const
{
    return m_isModified;
}

void CustomTextEdit::setIsModified(bool modified)
{    
    if(this == nullptr)
    {
        qDebug() << "Object is null. Returning.";
        return;
    }
    m_isModified = modified;
}

void CustomTextEdit::onTextChanged()
{
    // Compare the current text with the previous text to determine if it has actually changed
    QString currentText = toPlainText();
    bool conditionInit = (currentText.size() != 0 && m_previousText.size() != 0);
    bool conditionChangeText = (currentText != m_previousText);

    // Check if the text is not empty, but m_previousText is empty
    if(currentText.size() != 0 && m_previousText.size() == 0)
    {
        m_previousText = currentText;
    }

    // Both currentText and m_previousText should not be empty for the change to be meaningful
    if (conditionInit)
    {
        // Check if the text has actually changed
        if(conditionChangeText)
        {
            m_isModified = true;
            emit textModified(true); // Emit the signal
            m_previousText = currentText; // Update m_previousText
        }
    }
}
