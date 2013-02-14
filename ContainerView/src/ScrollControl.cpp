// Default empty project template
#include "ScrollControl.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LayoutOrientation>
#include <bb/cascades/ListItemProvider>

#include "ContainerView.hpp"
#include "NavigatingOrientation.h"

ScrollControl::ScrollControl(bb::cascades::Application *app) :
		QObject(app), ContainerItemProvider(), mArrayDataModel(new ArrayDataModel()) {

	qmlRegisterType < ContainerView > ("custom.lib", 1, 0, "ContainerView");
	qmlRegisterType < NavigatingOrientation > ("custom.lib", 1, 0, "NavigatingOrientation");

	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	Page *page = qml->createRootObject<Page>();
	app->setScene(page);

	ContainerView* containerView = page->findChild<ContainerView*>("containerView");
	containerView->setItemProvider(this);

}

bb::cascades::Container* ScrollControl::createImageContainer(QString s) {
	QmlDocument *qml = QmlDocument::create("asset:///article.qml").parent(this);

	// create root object for the UI
	Container *article = qml->createRootObject<Container>();

	qml->setParent(article);

	ImageView* imageView = article->findChild<ImageView*>("imageView");

	int c = setRandomPhoto(imageView);

	article->findChild<Label*>("label")->setProperty("text", s);

	if (c == 0) {
		if (article) {
			article->findChild<Label*>("label")->setProperty("text", "Camera folder is empty");
		}
	}

	return article;
}

bb::cascades::Container* ScrollControl::createWebViewContainer(QString s) {
	QmlDocument *qml = QmlDocument::create("asset:///webview_article.qml").parent(this);

	Container *article = qml->createRootObject<Container>();

	qml->setParent(article);

	return article;
}

bb::cascades::Container* ScrollControl::createItem(ItemType::ETYPE itemType) {

	Container *article = NULL;

	switch (itemType) {
	case ItemType::PREVIOUSE:
		article = createImageContainer("ItemType::PREVIOUSE");
		break;
	case ItemType::CURRENT:
		article = createImageContainer("ItemType::CURRENT");
		break;
	case ItemType::NEXT:
		//article = createImageContainer("ItemType::NEXT");
		article = createWebViewContainer("http://www.blackberry.com");
		break;
	}

	return article;
}

int ScrollControl::setRandomPhoto(ImageView* imageView) {

	QDir dir("/accounts/1000/shared/camera/");
	dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

	QFileInfoList photosList = dir.entryInfoList();

	if (photosList.count() > 0) {
		qsrand(QDateTime::currentDateTime().toTime_t());
		int r = double(qrand()) / RAND_MAX * (photosList.count() - 1);

		QString path = photosList.at(r).absoluteFilePath();

		imageView->setImage(Image(path));
	}

	return photosList.count();
}
