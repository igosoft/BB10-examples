// Segmented Control project template
/*
 * ListModel.h
 *
 *  Created on: 03 May 2012
 *      Author: fvacek@rim.com
 */

#ifndef MyListModel_HPP_
#define MyListModel_HPP_

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMetaType>
#include <bb/cascades/QListDataModel>

/*!
 * @brief Mutable linear list model implementation
 */
class MyListModel : public bb::cascades::QVariantListDataModel
{
    Q_OBJECT
public Q_SLOTS:
    /*!
     * @brief Convenience method to load the model data.
     *
     * @param file_name name of JSON data file
     */
    void load(const QString& file_name);
    /*!
     * @brief Set model data only to items of certain category.
     *
     * @param category  only items of this category can pass filter
     */
    void setFilter(int category);
public:
    MyListModel(QObject* parent = 0);
    virtual ~MyListModel();
private:
    QVariantList m_data; ///< not filtered data storage
};


#endif /* MyListModel_HPP_ */
