#include "cuvinte/WordListModel.h"

#include <QLocale>
#include <algorithm>

WordListModel::WordListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_collator(QLocale(QLocale::Romanian, QLocale::Romania))
    , m_words(m_storage.load())
{
    m_collator.setCaseSensitivity(Qt::CaseInsensitive);

    // Sortăm ce am încărcat din fișier, ca să fie sigur în ordine.
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

bool WordListModel::add(const QString &text)
{
    const QString clean = text.simplified(); // taie spațiile de la capete și dublurile
    if (clean.isEmpty())
        return false;

    // Găsim locul corect în lista sortată și inserăm acolo.
    const auto pos = std::upper_bound(
        m_words.begin(), m_words.end(), clean,
        [this](const QString &a, const QString &b) { return lessThan(a, b); });
    const int row = static_cast<int>(pos - m_words.begin());

    beginInsertRows(QModelIndex(), row, row);
    m_words.insert(row, clean);
    endInsertRows();

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