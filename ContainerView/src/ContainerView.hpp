/*
 * ScrollControlView.h
 *
 *  Created on: 31-10-2012
 *      Author: masi
 */

#ifndef SCROLLCONTROLVIEW_H_
#define SCROLLCONTROLVIEW_H_

#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/Control>
#include <bb/cascades/ArrayDataModel>

#include <bb/cascades/DataModelChangeType>
#include <bb/cascades/AbsoluteLayoutProperties>
//
//#include <QObject>
//#include <QVariantList>

#include "NavigatingOrientation.h"
#include "ContainerItemProvider.h"

class ContainerItemProvider;

class ContainerView: public bb::cascades::CustomControl {
Q_OBJECT
Q_PROPERTY(NavigatingOrientation::Type orientation READ getOrientation WRITE setOrientation)
//Q_PROPERTY(bool mAutoDeleteItems READ isAutoDeleteItems WRITE setAutoDeleteItems RESET resetAutoDeleteItems NOTIFY autoDeleteItemsChanged FINAL)
//Q_PROPERTY(bb::cascades::ArrayDataModel mDataModel READ dataModel WRITE setDataModel RESET resetDataModel NOTIFY dataModelChanged FINAL)

// dataModel
// itemProvider

public:
	ContainerView(bb::cascades::Container *parent = 0);
	virtual ~ContainerView();

	void setOrientation(NavigatingOrientation::Type orientation);
	NavigatingOrientation::Type getOrientation();

	bb::cascades::ArrayDataModel* dataModel() const;

	void setItemProvider(ContainerItemProvider* provider);

	//bool isAutoDeleteItems(){return mAutoDeleteItems;}
	//Q_SLOT void setAutoDeleteItems(bool value) {mAutoDeleteItems=value;}
	//Q_SLOT void resetAutoDeleteItems(){mAutoDeleteItems=true;}

Q_SIGNALS:
	//void autoDeleteItemsChanged(bool value);
	void switchedToNext();
	void switchedToPreviouse();
//	void dataModelChanged();

protected:
	void containerChanged(int index);

public:
//	Q_SLOT void setDataModel(bb::cascades::ArrayDataModel* dataModel);

	Q_SLOT void navigateTo(int index);
	Q_SLOT void navigateToNext();
	Q_SLOT void navidateToPreviouse();

private:

	Q_SLOT void onTouch(bb::cascades::TouchEvent* event);
	Q_SLOT void handleLayoutFrameUpdated(const QRectF& layoutFrame);
	Q_SLOT void setContainersPosition();
	// Setup container added in external DataModel
//	Q_SLOT void setupContainers(QVariantList indexPath);
//	Q_SLOT void setupAllContainers();

	void appendContainer(bb::cascades::Container* container);
	void insertContainer(int index, bb::cascades::Container* container);
	void resetDataModel();

	void moveHorizontal(int shift, bb::cascades::AbsoluteLayoutProperties* previouseLP,
			bb::cascades::AbsoluteLayoutProperties* currentLP, bb::cascades::AbsoluteLayoutProperties* nextLP);
	void moveVertical(int shift, bb::cascades::AbsoluteLayoutProperties* previouseLP,
			bb::cascades::AbsoluteLayoutProperties* currentLP, bb::cascades::AbsoluteLayoutProperties* nextLP);
private:
	//void setContainer(bb::cascades::VisualNode* node, ContainerPosition pos);

	NavigatingOrientation::Type mOrientation;
	bb::cascades::Container* mRootContainer;

	// User DataModel
	bb::cascades::ArrayDataModel* mDataModel;

	ContainerItemProvider* mContainerItemProvider;

	int mCurrentConatinerIndex;

	// Current position (x or y depending on orientation) of touch event
	int latestTouchPos;

	// Starting position (x or y depending on orientation) of touch event
	int startTouchPos;

	bool mAutoDeleteItems;
};

Q_DECLARE_METATYPE(ContainerView*);

#endif /* SCROLLCONTROLVIEW_H_ */
