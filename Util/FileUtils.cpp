#include <QFile>

#include "FileUtils.h"

namespace Util
{

bool CheckFile(const QString& path)
{
    QFile file(path);
    return file.exists() && file.open(QFile::ReadOnly | QIODevice::Text);
}

}
