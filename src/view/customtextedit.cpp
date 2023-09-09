// customtextedit.cpp
#include "customtextedit.h"
#include <QDebug>

CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent), m_isModified(false)
{
    // Initialisation du texte précédent au texte actuel lors de la création de l'objet
    connect(this, &QTextEdit::textChanged, this, &CustomTextEdit::onTextChanged);
    m_previousText = toPlainText();
}

bool CustomTextEdit::isTextChanged() const
{
    return m_isModified;
}

void CustomTextEdit::setIsModified(bool modified)
{
    m_isModified = modified;
}

void CustomTextEdit::onTextChanged()
{
    // Comparer le texte actuel avec le texte précédent pour déterminer s'il a vraiment changé
    QString currentText = toPlainText();
    bool conditionInit = (currentText.size() != 0 && m_previousText.size() != 0);
    bool conditionChangeText = (currentText != m_previousText);
    if(currentText.size() != 0 && m_previousText.size() == 0)
    {
        m_previousText = currentText;
    }
    if (conditionInit)
    {
        if(conditionChangeText)
        {
            m_isModified = true;
            emit textModified(true);
            m_previousText = currentText;
        }
    }
}