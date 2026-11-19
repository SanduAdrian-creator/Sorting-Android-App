#pragma once

#include <QAbstractListModel>
#include <QByteArray>
#include <QCollator>
#include <QHash>
#include <QString>
#include <QStringList>

#include "cuvinte/WordStorage.h"

// Model sortat alfabetic. Fiecare element expune și litera cu care începe,
// ca interfața să poată grupa cuvintele pe secțiuni.
class WordListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        LetterRole = Qt::UserRole + 1
    };

    explicit WordListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool add(const QString &text);
    Q_INVOKABLE void remove(int row);

private:
    static QString firstLetter(const QString &word);
    bool lessThan(const QString &a, const QString &b) const;

    WordStorage m_storage;
    QCollator m_collator;
    QStringList m_words;
};