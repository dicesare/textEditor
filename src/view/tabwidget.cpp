// tabwidget.cpp
#include "tabwidget.h"


TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    connect(this, &QTabWidget::tabCloseRequested, this, &TabWidget::closeTab);
    // connect(ui->tabWidgetEditor,  &QAction::triggered, this,&TabWidget::closeTab);
}

void TabWidget::addTabWithContent(const QString &content, const QString &filePath)
{
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setText(content);

    int newIndex = addTab(textEdit, filePath);
    setCurrentIndex(newIndex);

    // Initialiser l'état modifié à false pour le nouvel onglet
    m_modifiedTabs.append(false);
}

void TabWidget::closeTab(int index)
{
    if (index >= 0 && index < count())
    {
        // Récupérer le chemin du fichier à partir du tooltip de l'onglet
        QString filePath = tabToolTip(index);

        // Demander une confirmation à l'utilisateur
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous fermer cet onglet ?",
                                             QMessageBox::Yes | QMessageBox::No);

        // Si l'utilisateur confirme, fermer l'onglet
        if (confirmation == QMessageBox::Yes)
        {
            // Vérifier si l'onglet a été modifié
            if (m_modifiedTabs.at(index))
            {
                QTextEdit *textEdit = qobject_cast<QTextEdit *>(widget(index));
                QString content = textEdit->toPlainText();
                QMessageBox::StandardButton saveConfirmation;
                saveConfirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous sauvegarder les modifications ?",
                                                         QMessageBox::Yes | QMessageBox::No);

                if (saveConfirmation == QMessageBox::Yes)
                {
                    // Sauvegarder le fichier
                    if (!m_editorViewModel.saveFile(filePath, content))
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

void TabWidget::setTabModified(int index, bool modified)
{
    if (index >= 0 && index < m_modifiedTabs.size())
    {
        m_modifiedTabs[index] = modified; // Définissez la valeur correspondante dans le QVector
    }
}