// Segmented Control project template
#include "mylistmodel.hpp"

#include <bb/data/JsonDataAccess>

using namespace bb::data;

MyListModel::MyListModel(QObject* parent)
: bb::cascades::QVariantListDataModel()
{
    setParent(parent);
    qDebug() << "Creating MyListModel object:" << this;
}

MyListModel::~MyListModel()
{
    qDebug() << "Destroying MyListModel object:" << this;
}

void MyListModel::load(const QString& file_name)
{
    // clear model
    clear();
    // clear not filtered data cache
    m_data.clear();
    {
        JsonDataAccess jda;
        m_data = jda.load(file_name).toList();
        if (jda.hasError()) {
            DataAccessError error = jda.error();
            qDebug() << file_name << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
        }
        else {
            qDebug() << file_name << "JSON data loaded OK!";
            // when loaded, show all data (no filtering)
            append(m_data);
        }
    }
}

void MyListModel::setFilter(int category)
{
    qDebug() << "setting category to:" << category;
    QVariantList lst;
    if(category == 0) {
        // all items pass, set on write copy (see implicit sharing) of m_data to the lst variable
        lst = m_data;
    }
    else {
        // pick only items that pass the fiter condition
        foreach(QVariant v, m_data) {
            if(v.toMap().value("category") == category) lst << v;
        }
    }
    // clear model
    clear();
    // set filtered data to the model
    append(lst);
}

