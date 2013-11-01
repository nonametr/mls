#ifndef MLS_MAIN_H
#define MLS_MAIN_H

#include <qmainwindow>
#include <qmap.h>
#include <qrunnable>
#include <qstring.h>

#include "ui_mqs_main.h"

#include "opengl_render_widget.h"
#include "gui_config.h"

#define CHANNELS_TAB    0
#define ENCODERS_TAB    1
#define GENERAL_TAB     2

class MlsMain : public QMainWindow
{
	Q_OBJECT
public:
    MlsMain(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MlsMain();
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual bool eventFilter( QObject * watched, QEvent * event );
private:
	void initMenu();

    QMenu *regMenu(QPushButton *button);
    QMenu *regMenu(QString internal_name, QString tr_name);
    QMenu *regMenu(QMenu *menu, QString internal_name, QString tr_name);
    QMenu* getMenu(QPushButton *button);
    QMenu* getMenu(string menu_name);
    QAction *regMenuAction(QMenu *menu, QString name, const char* slot);
    void regMenuSeporator(QMenu *menu);

	GLRenderWidget *view;
	QPoint offset;
	QMap<string, QMenu*> menu;
	GLRenderWidget *v_gl;
    Ui::MediaQuickSyncClass ui;
signals:
    void onFrameReady(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height);
public slots:
    void onOpenGLRenderComplete(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height);

	void clickChangeScaleViewport();
	void clickDisablePreview();
    void clickLanguageChange();
	void clickChangeFrameRate();
	void clickResolutionChoose();

	void clickFileNew();
	void clickFileSave();
	void clickFileLoad();
	void clickFileAddCamera();
	void clickFileExit();
	void clickChannelsEdit();
	void onChannelAction();
	void clickEncodersEdit();
	void clickSaveScreenShot();
	void clickToolsDelay();
	void clickToolsRecordings();
	void clickToolsSettings();
	void clickHelpContents();
	void clickHelpForum();
	void clickHelpNews();
	void clickHelpUpdates();
	void clickHelpAbout();

    //gui update
    void updateMain(GUIUpdate update_type);//external interface to update gui from other modules
    void updateSize();//internal use
    void updateBroadcasts();//internal use
    void updateResolutions();//internal use
    void updateScenes();//internal use
    void updateScale();//internal use
    void updateFPS();//internal use
    void updateTranslations();//internal use
    void updatePlugins();//internal use

    //scene managment
    void onSceneCreate();
    void onSceneDelete();
    void onSceneRename();
    void onSceneSetBackground();
    void onScenePressed(QListWidgetItem *);
    void onSceneContextMenuRequested(const QPoint &);

    //source managment
    void onContextSourceAdd();
    void onSourcePressed(QListWidgetItem *item);
    void onSourceHideShow();
    void onSourceRemove();
    void onSourceSettings();
    void onSelectSource(string surface_handle);
    void onAddSource(string source_name);
    void onDeleteSource(string source_name);
    void onSourceContextMenuRequested(const QPoint &);
};

extern MlsMain *main_window;

#endif
