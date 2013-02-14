/*
 * NavigatingOrientation.h
 *
 *  Created on: 06-11-2012
 *      Author: masi
 */

#ifndef NAVIGATINGORIENTATION_H_
#define NAVIGATINGORIENTATION_H_

#include <QObject>
#include <bb/cascades/LayoutOrientation>

class NavigatingOrientation: public QObject{
	Q_OBJECT
	Q_ENUMS (Type)
public:
	enum Type {
		Horizontal, Vertical
	};
};

#endif /* NAVIGATINGORIENTATION_H_ */
