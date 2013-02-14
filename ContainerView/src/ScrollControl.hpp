// Default empty project template
#ifndef ScrollControl_HPP_
#define ScrollControl_HPP_


#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/application.h>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/WebView>


#include "ContainerView.hpp"
#include "ContainerItemProvider.h"

using namespace bb::cascades;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ScrollControl: public QObject, public ContainerItemProvider {
Q_OBJECT
public:
	ScrollControl(bb::cascades::Application *app);
	virtual ~ScrollControl() {
	}

	virtual bb::cascades::Container* createItem(ItemType::ETYPE type);

private:

	bb::cascades::Container* createImageContainer(QString s);
	bb::cascades::Container* createWebViewContainer(QString s);

	int setRandomPhoto(ImageView *imageView);

	ArrayDataModel* mArrayDataModel;

};

#endif /* ScrollControl_HPP_ */
