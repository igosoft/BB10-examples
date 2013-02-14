/*
 * ContainerItemProvider.h
 *
 *  Created on: 01-11-2012
 *      Author: Igor Andruszkiewicz
 */

#ifndef CONTAINERITEMPROVIDER_H_
#define CONTAINERITEMPROVIDER_H_

#include <QObject>
#include <bb/cascades/Container>
#include "ContainerView.hpp"

class ItemType {
public:
	enum ETYPE {
		PREVIOUSE = 0, CURRENT = 1, NEXT = 2
	};
};

class ContainerItemProvider {
public:
	ContainerItemProvider();
	virtual ~ContainerItemProvider();

//	virtual bb::cascades::VisualNode* createNext() =0;
//	virtual bb::cascades::VisualNode* createPreviouse()=0;

	virtual bb::cascades::Container* createItem(ItemType::ETYPE type)=0;

private:
	Q_DISABLE_COPY (ContainerItemProvider)
	;
};

//QML_DECLARE_TYPE(ContainerItemProvider)

#endif /* CONTAINERITEMPROVIDER_H_ */
