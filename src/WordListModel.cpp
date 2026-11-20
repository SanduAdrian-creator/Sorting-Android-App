#include "cuvinte/WordListModel.h"

#include <QLocale>
#include <algorithm>

WordListModel::WordListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_collator(QLocale(QLocale::Romanian, QLocale::Romania))
    , m_words(m_storage.load())
{
    m_collator.setCaseSensitivity(Qt::CaseInsensitive);

    std::sort(m_words.begin(), m_words.end(),
              [this](const QString &a, const QString &b) { return lessThan(a, b); });
}

QString WordListModel::firstLetter(const QString &word)
{
    return word.isEmpty() ? QString() : word.left(1).toUpper();
}

bool WordListModel::lessThan(const QString &a, const QString &b) const
{
    return m_collator.compare(a, b) < 0;
}

int WordListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : static_cast<int>(m_words.size());
}

QVariant WordListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_words.size())
        return {};

    const QString &word = m_words.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return word;
    case LetterRole:
        return firstLetter(word);
    default:
        return {};
    }
}

QHash<int, QByteArray> WordListModel::roleNames() const
{
    return {
        { Qt::DisplayRole, "display" },
        { LetterRole, "letter" }
    };
}

// Inserează cuvântul la locul corect în lista sortată (fără salvare).
void WordListModel::insertSorted(const QString &clean)
{
    const auto pos = std::upper_bound(
        m_words.begin(), m_words.end(), clean,
        [this](const QString &a, const QString &b) { return lessThan(a, b); });
    const int row = static_cast<int>(pos - m_words.begin());

    beginInsertRows(QModelIndex(), row, row);
    m_words.insert(row, clean);
    endInsertRows();
}

bool WordListModel::add(const QString &text)
{
    const QString clean = text.simplified();
    if (clean.isEmpty())
        return false;

    insertSorted(clean);
    m_storage.save(m_words);
    return true;
}

bool WordListModel::edit(int row, const QString &text)
{
    if (row < 0 || row >= m_words.size())
        return false;

    const QString clean = text.simplified();
    if (clean.isEmpty())
        return false;
    if (clean == m_words.at(row))
        return true; // nimic de schimbat

    // Scoatem vechiul cuvânt și îl punem pe cel nou la locul lui sortat,
    // ca să ajungă în secțiunea corectă dacă i s-a schimbat litera.
    beginRemoveRows(QModelIndex(), row, row);
    m_words.removeAt(row);
    endRemoveRows();

    insertSorted(clean);
    m_storage.save(m_words);
    return true;
}

void WordListModel::remove(int row)
{
    if (row < 0 || row >= m_words.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_words.removeAt(row);
    endRemoveRows();

    m_storage.save(m_words);
}