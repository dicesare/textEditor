#include "tabwidgeteditor.h"

// Constructor: Initialize the widget and set up connections
TabWidgetEditor::TabWidgetEditor(QWidget *parent) : QTabWidget(parent), m_currentTextEdit(nullptr)
{
    m_modifiedTabs.append(false);
    connect(this, &QTabWidget::tabCloseRequested, this, &TabWidgetEditor::closeTab);
}

// Add a new tab with the given content and file path
void TabWidgetEditor::addTabWithContent(const QString &content, const QString &filePath)
{
    CustomTextEdit *textEditor = new CustomTextEdit(this);
    int index = addTab(textEditor, filePath);
    m_currentTextEdit = textEditor;

    textEditor->setPlainText(content);
    setTabsClosable(true);
    setCurrentIndex(index);
    setTabToolTip(index, filePath);

    connect(textEditor, &CustomTextEdit::textModified, this, &TabWidgetEditor::handleTextModified);
    connect(textEditor, &CustomTextEdit::cursorPositionChanged, this, [this, textEditor]() {
        emit cursorPositionChangedInEditor(textEditor);
    });

    m_modifiedTabs.append(false);
}

// Close the tab at the given index
void TabWidgetEditor::closeTab(int index)
{
    if (index < 0 || index >= count()) return;

    QString filePath = tabToolTip(index);
    QMessageBox::StandardButton confirmation = QMessageBox::question(
        this, "Confirmation", "Do you want to close this tab?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (confirmation != QMessageBox::Yes) return;

    CustomTextEdit *textEditor = qobject_cast<CustomTextEdit *>(widget(index));
    if (textEditor && textEditor->isTextChanged())
    {
        QMessageBox::StandardButton saveConfirmation = QMessageBox::question(
            this, "Confirmation", "Do you want to save changes?",
            QMessageBox::Yes | QMessageBox::No
        );

        if (saveConfirmation == QMessageBox::Yes)
        {
            QString content = textEditor->toPlainText();
            if (!m_controllerEditor.saveFile(filePath, content))
            {
                QMessageBox::critical(this, "Error", "Failed to save the file.");
                return;
            }
        }
    }

    QWidget *widgetToRemove = widget(index);
    removeTab(index);
    delete widgetToRemove;
    m_modifiedTabs.remove(index);
}

// Mark a tab as modified or not
void TabWidgetEditor::setTabModified(int index, bool modified)
{
    if (index < 0 || index >= m_modifiedTabs.size()) return;

    m_modifiedTabs[index] = modified;
}

// Update the tab text when the content is modified
void TabWidgetEditor::handleTextModified(bool modified)
{
    // Get the index of the current tab
    int index = this->currentIndex();
    // Exit if no tab is selected
    if (index == -1) return;

    // Get the QTextEdit of the current tab
    QTextEdit *textEditor = qobject_cast<QTextEdit *>(widget(index));
    // Exit if the widget couldn't be cast to QTextEdit
    if (!textEditor) return;

    // Get the current tab text
    QString tabText = this->tabText(index);

    if (modified) {
        // Add an asterisk only if it's not already there.
        if (!tabText.endsWith("*")) {
            setTabText(index, tabText + "*");
        }
    } else {
        // Remove the asterisk if the file is no longer modified.
        if (tabText.endsWith("*")) {
            setTabText(index, tabText.left(tabText.length() - 1));
        }
    }

    // Emit a signal to notify that the file has been modified
    emit fileModified(modified);
}


// Set the modified state for the current CustomTextEdit
void TabWidgetEditor::setCurrentTextEditModified(bool modified)
{
    int currentIndex = this->currentIndex();
    CustomTextEdit* textEdit = qobject_cast<CustomTextEdit*>(this->widget(currentIndex));

    if(textEdit == nullptr) {
        qDebug() << "CustomTextEdit pointer is null. Exiting function.";
        return;
    }

    m_currentTextEdit = textEdit;

    if (m_currentTextEdit != nullptr) {
        m_currentTextEdit->setIsModified(modified);
    }
    else
    {
        qDebug() << "Attention : m_currentTextEdit n'est pas initialisé.";
    }
}

