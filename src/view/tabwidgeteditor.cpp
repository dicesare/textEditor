#include "tabwidgeteditor.h"

TabWidgetEditor::TabWidgetEditor(QWidget *parent) : QTabWidget(parent)
{
    m_modifiedTabs.append(false);
    connect(this, &QTabWidget::tabCloseRequested, this, &TabWidgetEditor::closeTab);
}

void TabWidgetEditor::addTabWithContent(const QString &content, const QString &filePath)
{
    CustomTextEdit *textEditor = new CustomTextEdit(this);
    int index = addTab(textEditor, filePath);
    m_currentTextEdit = textEditor;
    textEditor->setPlainText(content);
    // textEditor->setIsModified(false);

    setTabsClosable(true);
    setCurrentIndex(index);
    setTabToolTip(index, filePath);
    connect(textEditor, &CustomTextEdit::textModified, this, &TabWidgetEditor::handleTextModified);
    m_modifiedTabs.append(false);
}
void TabWidgetEditor::closeTab(int index)
{
    if (index >= 0 && index < count())
    {
        // Récupérer le chemin du fichier à partir du tooltip de l'onglet
        QString filePath = mCurrentDirectory + "/" + tabToolTip(index);
        // Demander une confirmation à l'utilisateur
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous fermer cet onglet ?",
                                             QMessageBox::Yes | QMessageBox::No);

        // Si l'utilisateur confirme, fermer l'onglet
        if (confirmation == QMessageBox::Yes)
        {
            CustomTextEdit *textTabEdit = qobject_cast<CustomTextEdit *>(widget(index));
            // Si l'onglet actif est modifié, demandez à l'utilisateur s'il veut sauvegarder les modifications
            if (textTabEdit && textTabEdit->isTextChanged())
            {
                QTextEdit *textEditor = qobject_cast<QTextEdit *>(widget(index));
                QString content = textEditor->toPlainText();
                QMessageBox::StandardButton saveConfirmation;
                saveConfirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous sauvegarder les modifications ?",
                                                         QMessageBox::Yes | QMessageBox::No);
                // Utilisez mCurrentDirectory comme emplacement par défaut pour l'enregistrement
                if (saveConfirmation == QMessageBox::Yes)
                {
                    // Sauvegarder le fichier
                    if (!m_controllerEditor.saveFile(filePath, content))
                    {
                        QMessageBox::critical(this, "Erreur", "Échec de la sauvegarde du fichier.");
                        return; // Ne pas fermer l'onglet si la sauvegarde échoue.
                    }
                }
            }

            QWidget *widgetToRemove = widget(index);
            removeTab(index);
            delete widgetToRemove;
            // Retirer l'état modifié de l'onglet supprimé du QVector
            m_modifiedTabs.remove(index);
        }
    }
}

void TabWidgetEditor::setTabModified(int index, bool modified)
{
    if (index >= 0 && index < m_modifiedTabs.size())
    {
        m_modifiedTabs[index] = modified; // Définissez la valeur correspondante dans le QVector
        // m_modifiedLabels[index]->setVisible(modified); // Affiche ou masque l'astérisque
    }
}

void TabWidgetEditor::handleTextModified(bool modified)
{
    int currentTabIndex = this->currentIndex();
    if (currentTabIndex != -1)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(widget(currentTabIndex));
        if (textEdit)
        {
            QString tabText = this->tabText(currentTabIndex); // Utilisez 'this->' pour accéder à la fonction de la classe de base
            if (modified)
            {
                // Si le fichier est modifié, ajouter un astérisque (*) à son nom dans l'onglet
                if (!tabText.endsWith("*"))
                {
                    setTabText(currentTabIndex, tabText + "*");
                    emit fileModified(true);
                }
            }
            else
            {
                // Si le fichier n'est plus modifié, enlever l'astérisque (*) de son nom dans l'onglet
                if (tabText.endsWith("*"))
                {
                    setTabText(currentTabIndex, tabText.left(tabText.length() - 1));
                    emit fileModified(false);
                }
            }
        }
    }
}

void TabWidgetEditor::setCurrentTextEditModified(bool modified)
{
    if (m_currentTextEdit)
    {
        m_currentTextEdit->setIsModified(modified);
    }
}
