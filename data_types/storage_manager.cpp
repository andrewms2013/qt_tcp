#include <storage_manager.h>
#include <json_storage.h>
#include <stdexcept>
#include <QString>

// https://stackoverflow.com/a/874160

static bool hasEnding (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

JsonDeveloperStorage * StorageManager::createStorage(string & storageFileName){
    if(!hasEnding(storageFileName, ".json")){
        string exeption = storageFileName;
        exeption += " is not a JSON file";
        throw MessageException(exeption);
    }
    else {
        QString name = QString::fromStdString(storageFileName);
        return new JsonDeveloperStorage(name);
    }
}

