#ifndef MLS_SURFACE_SETTINGS_H
#define MLS_SURFACE_SETTINGS_H

#include <qwidget.h>
#include "ui_mqs_surface_settings.h"
#include "isurface.h"

class MqsSurfaceSettings : public QWidget
{
	Q_OBJECT
public:
	MqsSurfaceSettings(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	void setControlSurface(IMqsSurface *p_surface){ surface = p_surface; ChromaEnabledChaneged(surface->chromaEnabled() ? Qt::Checked:Qt::Unchecked);};
	virtual ~MqsSurfaceSettings(void);
	virtual void closeEvent ( QCloseEvent * event );
	virtual void showEvent ( QShowEvent * event );
private:
	QObject *_parent;
	bool checkLimits(float x_pos, float y_pos, float x_scale, float y_scale);
	IMqsSurface *surface;
	Ui::SurfaceSetting ui;
public slots:
	void RChanged(int r);
	void GChanged(int g);
	void BChanged(int b);
	void AlfaChanged(int a);
	void HeightChanged(int height);
	void WidthChanged(int width);
	void KeepAspectChanged(int state);
	void XPosChanged(int new_xpos);
	void YPosChanged(int new_ypos);
	void XAngleChanged(int new_xpos);
	void YAngleChanged(int new_ypos);
	void ZAngleChanged(int new_zpos);
	void BottomClipChanged(int bot_clip);
	void TopClipChanged(int bot_clip);
	void RightClipChanged(int bot_clip);
	void LeftClipChanged(int bot_clip);
	void ChromaRChanged(int r_chroma);
	void ChromaGChanged(int g_chroma);
	void ChromaBChanged(int b_chroma);
	void ChromaRTChanged(int rt_chroma);
	void ChromaGTChanged(int gt_chroma);
	void ChromaBTChanged(int bt_chroma);
	void BrightnessChanged(int brightness);
	void ContrastChanged(int contrast);
	void ChromaEnabledChaneged(int new_state);
	void pickColorPressed();
};

#endif
