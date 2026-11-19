#pragma once

#include <QString>
#include <QStringList>

// Salvează și încarcă lista de cuvinte într-un fișier text local.
class WordStorage
{
public:
    WordStorage();
    explicit WordStorage(QString filePath);

    QStringList load() const;
    bool save(const QStringList &words) const;
    QString filePath() const;

private:
    QString m_filePath;
};