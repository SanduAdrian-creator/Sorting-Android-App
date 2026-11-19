#include "cuvinte/WordStorage.h"

#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QStandardPaths>
#include <QTextStream>

WordStorage::WordStorage()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    m_filePath = dir + "/cuvinte.txt";
}

WordStorage::WordStorage(QString filePath)
    : m_filePath(std::move(filePath))
{
}

QString WordStorage::filePath() const
{
    return m_filePath;
}

QStringList WordStorage::load() const
{
    QStringList words;
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return words; // prima rulare: fișierul nu există încă

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    while (!in.atEnd()) {
        const QString line = in.readLine();
        if (!line.isEmpty())
            words << line;
    }
    return words;
}

bool WordStorage::save(const QStringList &words) const
{
    // QSaveFile scrie întâi într-un fișier temporar, ca să nu se corupă
    // lista dacă aplicația se închide în timpul salvării.
    QSaveFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    for (const QString &word : words)
        out << word << '\n';

    return file.commit();
}