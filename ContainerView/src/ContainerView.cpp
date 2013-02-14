#include "ContainerView.hpp"

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/LayoutUpdateHandler>

using namespace bb::cascades;

ContainerView::ContainerView(bb::cascades::Container* parent) :
		bb::cascades::CustomControl(parent), mOrientation(NavigatingOrientation::Horizontal), mDataModel(NULL), mContainerItemProvider(NULL), mAutoDeleteItems(true) {

	mCurrentConatinerIndex = -1;
	latestTouchPos = startTouchPos = 0;

	LayoutUpdateHandler::create(this).onLayoutFrameChanged(this, SLOT(handleLayoutFrameUpdated(const QRectF &)));

	mRootContainer = new Container();
	mRootContainer->setLayout(new AbsoluteLayout());

	setRoot(mRootContainer);

	connect(this, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(onTouch(bb::cascades::TouchEvent*)));

}

ContainerView::~ContainerView() {
	resetDataModel();
	delete mRootContainer;
}

void ContainerView::setOrientation(NavigatingOrientation::Type orientation) {
	mOrientation = orientation;
}

NavigatingOrientation::Type ContainerView::getOrientation(){
	return mOrientation;
}

//bb::cascades::ArrayDataModel* ContainerView::dataModel() const {
//	return mDataModel;
//}

//void ContainerView::setDataModel(bb::cascades::ArrayDataModel* dataModel) {
//	mAutoDeleteItems = false;
//	resetDataModel();
//
//	mDataModel = dataModel;
//
//	connect(mDataModel, SIGNAL(itemAdded(QVariantList)), this, SLOT(setupContainers(QVariantList)));
//	//connect(mDataModel, SIGNAL(itemUpdated(QVariantList)), this, SLOT(setupContainers(QVariantList)));
//	connect(mDataModel, SIGNAL(itemRemoved(QVariantList)), this, SLOT(setupContainers(QVariantList)));
//	connect(mDataModel, SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type, QSharedPointer<bb::cascades::DataModel::IndexMapper>)), this,
//			SLOT(setupAllContainers()));
//
//	if (mDataModel->size() > 0 && mCurrentConatinerIndex == -1) {
//		mCurrentConatinerIndex = 0;
//		setupAllContainers();
//	}
//}

//void ContainerView::setupContainers(QVariantList indexPath) {
//	int index = indexPath[0].toInt();
//	if (mDataModel == NULL) {
//		return;
//	}
//
//	Container* container = mDataModel->value(index, QVariant::fromValue(0)).value<Container*>();
//	if (container) {
//		AbsoluteLayoutProperties* alp = ((AbsoluteLayoutProperties*) (container)->layoutProperties());
//		if (alp == NULL) {
//			container->setLayoutProperties(AbsoluteLayoutProperties::create());
//		}
//	}
//}

//void ContainerView::setupAllContainers() {
//	if (mDataModel == NULL) {
//		return;
//	}
//
//	for (int i = 0; i < mDataModel->size(); i++) {
//		Container* container = mDataModel->value(i, QVariant::fromValue(0)).value<Container*>();
//		if (container) {
//			AbsoluteLayoutProperties* alp = ((AbsoluteLayoutProperties*) (container)->layoutProperties());
//			if (alp == NULL) {
//				container->setLayoutProperties(AbsoluteLayoutProperties::create());
//			}
//			mRootContainer->add(container);
//		}
//	}
//}

void ContainerView::resetDataModel() {

	if (mDataModel && mDataModel->parent() == NULL) {
		delete mDataModel;
		mDataModel = NULL;
		mCurrentConatinerIndex = -1;
	}
}

void ContainerView::moveHorizontal(int shift, bb::cascades::AbsoluteLayoutProperties* previouseLP,
		bb::cascades::AbsoluteLayoutProperties* currentLP, bb::cascades::AbsoluteLayoutProperties* nextLP){
	if (previouseLP) {
		previouseLP->setPositionX(previouseLP->positionX() + shift);
	}
	if (currentLP) {
		int posX = currentLP->positionX() + shift;

		if (previouseLP == NULL) {
			if (posX > preferredWidth() / 10)
				posX = preferredWidth() / 10;
		}
		if (nextLP == NULL) {
			if (posX <= -preferredWidth() / 10)
				posX = -preferredWidth() / 10;
		}

		currentLP->setPositionX(posX);
	}
	if (nextLP) {
		nextLP->setPositionX(nextLP->positionX() + shift);
	}
}

void ContainerView::moveVertical(int shift, bb::cascades::AbsoluteLayoutProperties* previouseLP,
		bb::cascades::AbsoluteLayoutProperties* currentLP, bb::cascades::AbsoluteLayoutProperties* nextLP){
	if (previouseLP) {
		previouseLP->setPositionY(previouseLP->positionY() + shift);
	}
	if (currentLP) {
		int posY = currentLP->positionY() + shift;

		if (previouseLP == NULL) {
			if (posY > preferredHeight() / 10)
				posY = preferredHeight() / 10;
		}
		if (nextLP == NULL) {
			if (posY <= -preferredHeight() / 10)
				posY = -preferredHeight() / 10;
		}

		currentLP->setPositionY(posY);
	}
	if (nextLP) {
		nextLP->setPositionY(nextLP->positionY() + shift);
	}
}

void ContainerView::onTouch(bb::cascades::TouchEvent* event) {
	Container* container = mDataModel->value(mCurrentConatinerIndex - 1, QVariant::fromValue(0)).value<Container*>();
	AbsoluteLayoutProperties* previouseLP = container == NULL ? NULL : ((AbsoluteLayoutProperties*) (container)->layoutProperties());

	container = mDataModel->value(mCurrentConatinerIndex, QVariant::fromValue(0)).value<Container*>();
	AbsoluteLayoutProperties* currentLP = container == NULL ? NULL : ((AbsoluteLayoutProperties*) (container)->layoutProperties());

	container = mDataModel->value(mCurrentConatinerIndex + 1, QVariant::fromValue(0)).value<Container*>();
	AbsoluteLayoutProperties* nextLP = container == NULL ? NULL : ((AbsoluteLayoutProperties*) (container)->layoutProperties());

	if (event->isMove()) {
		if(mOrientation == NavigatingOrientation::Horizontal){
			int shift = event->windowX() - latestTouchPos;
			moveHorizontal(shift, previouseLP, currentLP, nextLP);
			latestTouchPos = event->windowX();
		} else {
			int shift = event->windowY() - latestTouchPos;
			moveVertical(shift, previouseLP, currentLP, nextLP);
			latestTouchPos = event->windowY();
		}
	}
	if (event->isDown()) { // Touch
		if(mOrientation == NavigatingOrientation::Horizontal){
			latestTouchPos = event->windowX();
			startTouchPos = event->windowX();
		} else {
			latestTouchPos = event->windowY();
			startTouchPos = event->windowY();
		}
	}
	if (event->isUp()) { // Release
		if (currentLP) {
			if(mOrientation == NavigatingOrientation::Horizontal){
				if (currentLP->positionX() > preferredWidth() / 2) {
					navidateToPreviouse();
					return;
				}
				if (currentLP->positionX() < -preferredWidth() / 2 && currentLP->positionX() < 0) {
					navigateToNext();
					return;
				}
			} else {
				if (currentLP->positionY() > preferredHeight() / 2) {
					navidateToPreviouse();
					return;
				}
				if (currentLP->positionY() < -preferredHeight() / 2 && currentLP->positionY() < 0) {
					navigateToNext();
					return;
				}
			}
		}

		navigateTo(mCurrentConatinerIndex);
	}
}

void ContainerView::appendContainer(Container* container) {
	if (container) {
		AbsoluteLayoutProperties* layoutProperties = ((AbsoluteLayoutProperties*) (container)->layoutProperties());
		if (layoutProperties == NULL) {
			container->setLayoutProperties(AbsoluteLayoutProperties::create());
		}

		mRootContainer->add(container);
		mDataModel->append(QVariant::fromValue(container));
		container->setParent(mDataModel);
	}
}

void ContainerView::insertContainer(int index, Container* container) {

	if (container) {
		AbsoluteLayoutProperties* layoutProperties = ((AbsoluteLayoutProperties*) (container)->layoutProperties());
		if (layoutProperties == NULL) {
			container->setLayoutProperties(AbsoluteLayoutProperties::create());
		}

		mRootContainer->add(container);
		mDataModel->insert(index, QVariant::fromValue(container));
		container->setParent(mDataModel);
	}
}

/**
 * When ContainerItemProvides is set ConatinerView asks for 3 Containers.
 * You can ContainerItemProvides zero or three Containers
 */
void ContainerView::setItemProvider(ContainerItemProvider* provider) {
	mContainerItemProvider = provider;

	if (mContainerItemProvider == NULL) {
		return;
	}

	resetDataModel();
	mDataModel = new ArrayDataModel(this);

	// Add standard Containers
	appendContainer(mContainerItemProvider->createItem(ItemType::PREVIOUSE));
	appendContainer(mContainerItemProvider->createItem(ItemType::CURRENT));
	mCurrentConatinerIndex = mDataModel->size() - 1;
	appendContainer(mContainerItemProvider->createItem(ItemType::NEXT));

	// ItemType::CURRENT was not set.
	// Set the last Container as the current
	if (mCurrentConatinerIndex == -1 && mDataModel->isEmpty() == false) {
		mCurrentConatinerIndex = mDataModel->size() - 1;
	}

	// Connect DataModel signals to ContainerView slots
	connect(mDataModel, SIGNAL(itemAdded(QVariantList)), this, SLOT(setContainersPosition()));
	//connect(mDataModel, SIGNAL(itemUpdated(QVariantList)), this, SLOT(setContainersPosition()));
	connect(mDataModel, SIGNAL(itemRemoved(QVariantList)), this, SLOT(setContainersPosition()));
	connect(mDataModel, SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type, QSharedPointer<bb::cascades::DataModel::IndexMapper> )), this,
			SLOT(setContainersPosition()));

}

void ContainerView::handleLayoutFrameUpdated(const QRectF& layoutFrame) {

	qDebug() << "handleLayoutFrameUpdated" << layoutFrame;

	setPreferredWidth(layoutFrame.width());
	mRootContainer->setPreferredWidth(layoutFrame.width());
	setPreferredHeight(layoutFrame.height());
	mRootContainer->setPreferredHeight(layoutFrame.height());

	for (int i = 0; i < mDataModel->size(); i++) {
		Container *container = mDataModel->value(i).value<Container*>();
		if (container) {
			container->setPreferredWidth(layoutFrame.width());
			container->setPreferredHeight(layoutFrame.height());
		}
	}

	navigateTo(mCurrentConatinerIndex);
}

void ContainerView::setContainersPosition() {
	navigateTo(mCurrentConatinerIndex);
}
void ContainerView::navigateTo(int index) {
	qDebug() << "ContainerView::navigateTo(" << index << ")";
	if (mDataModel == NULL) {
		return;
	}
	// index outside the range
	if (mDataModel && (index > mDataModel->size() || index < 0)) {
		return;
	}

	mCurrentConatinerIndex = index;

	//Rearrange Containers
	AbsoluteLayoutProperties* layoutProperties = NULL;
	Container *container = NULL;

	for (int i = 0; i < mDataModel->size(); i++) {
		container = mDataModel->value(i).value<Container*>();
		if (container) {
			layoutProperties = ((AbsoluteLayoutProperties*) ((Container*) container)->layoutProperties());

			if (layoutProperties == NULL)
				continue;

			if(mOrientation == NavigatingOrientation::Horizontal){
				int x = 0; // rearrange current
				// rearrange LEFT side
				if (i < mCurrentConatinerIndex) {
					x = -preferredWidth() * (mCurrentConatinerIndex - i);
				} else
				// rearrange RIGHT side
				if (i > mCurrentConatinerIndex) {
					x = preferredWidth() * (i - mCurrentConatinerIndex);
				}
				layoutProperties->setPositionX(x);
			} else {
				// rearrange TOP side
				int y = 0; // rearrange current
				if (i < mCurrentConatinerIndex) {
					y = -preferredHeight() * (mCurrentConatinerIndex - i);
				} else
				// rearrange BOTTOM side
				if (i > mCurrentConatinerIndex) {
					y = preferredHeight() * (i - mCurrentConatinerIndex);
				}
				layoutProperties->setPositionY(y);
			}

		}
	}
}

void ContainerView::navigateToNext() {
	int navigateToIndex = mCurrentConatinerIndex + 1;

	if (navigateToIndex == mDataModel->size() - 1) {
		Container *container = mContainerItemProvider->createItem(ItemType::NEXT);
		if (container) {
			if (mAutoDeleteItems) {
				mDataModel->removeAt(0);
			}

			appendContainer(container);

			navigateToIndex = mCurrentConatinerIndex;

			emit switchedToNext();
		}
	}

	navigateTo(navigateToIndex);
}

void ContainerView::navidateToPreviouse() {
	int navigateToIndex = mCurrentConatinerIndex - 1;

	if (navigateToIndex == 0) {
		Container *container = mContainerItemProvider->createItem(ItemType::PREVIOUSE);
		if (container) {
			if (mAutoDeleteItems) {
				mDataModel->removeAt(2);
			}

			// add new container in front of array
			insertContainer(0, container);

			navigateToIndex = mCurrentConatinerIndex;
			emit switchedToPreviouse();
		}
	}

	navigateTo(navigateToIndex);
}
