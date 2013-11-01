#include "gui_surface_settings.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QThread>
#include <qcolordialog.h>

MqsSurfaceSettings::MqsSurfaceSettings(QWidget *parent, Qt::WindowFlags flags) : _parent(parent)
{
	ui.setupUi(this);
}


MqsSurfaceSettings::~MqsSurfaceSettings(void)
{
}

void MqsSurfaceSettings::showEvent ( QShowEvent * event )
{
	//position
	ui.spinBox_X_Pos->setValue(surface->xPos()*100);
	ui.spinBox_Y_Pos->setValue(surface->yPos()*100);
	ui.spinBox_Clip_Bottom->setValue(surface->bottomCut()*100);
	ui.spinBox_Clip_Top->setValue(surface->topCut()*100);
	ui.spinBox_Clip_Left->setValue(surface->leftCut()*100);
	ui.spinBox_Clip_Right->setValue(surface->rightCut()*100);
	ui.spinBox_X_Angle->setValue(surface->xAngle());
	ui.spinBox_Y_Angle->setValue(surface->yAngle());
	ui.spinBox_Z_Angle->setValue(surface->zAngle());
	ui.spinBox_Height->setValue(surface->xScale()*100);
	ui.spinBox_Width->setValue(surface->yScale()*100);
	ui.spinBox_R->setValue(surface->rColor()*256);
	ui.spinBox_G->setValue(surface->gColor()*256);
	ui.spinBox_B->setValue(surface->bColor()*256);
	ui.spinBox_Transparency->setValue((1-surface->alfa())*100);

	ui.spinBox_chroma_R->setValue(surface->RChroma()*256);
	ui.spinBox_chroma_G->setValue(surface->GChroma()*256);
	ui.spinBox_chroma_B->setValue(surface->BChroma()*256);
	ui.spinBox_chroma_RT->setValue(surface->RTChroma()*256);
	ui.spinBox_chroma_GT->setValue(surface->GTChroma()*256);
	ui.spinBox_chroma_BT->setValue(surface->BTChroma()*256);
	ui.spinBox_Contrast->setValue(surface->contrast()*100);
	ui.spinBox_Brightness->setValue(surface->brightnes()*100);
	ui.checkBoxChromaEnabled->setCheckState(surface->chromaEnabled() ? Qt::Checked: Qt::Unchecked);

	QPalette pal = ui.button_pick_color->palette();
	pal.setColor(QPalette::Button, QColor(ui.horizontalSlider_chroma_R->value(), ui.horizontalSlider_chroma_G->value(), ui.horizontalSlider_chroma_B->value()));
	ui.button_pick_color->setPalette(pal);

	if(surface->keepAspect())
		ui.checkBox_keepaspect->setCheckState(Qt::Checked);
	else
		ui.checkBox_keepaspect->setCheckState(Qt::Unchecked);

	QObject::connect(ui.spinBox_X_Pos, SIGNAL(valueChanged(int)), this, SLOT(XPosChanged(int)));
	QObject::connect(ui.spinBox_Y_Pos, SIGNAL(valueChanged(int)), this, SLOT(YPosChanged(int)));

	QObject::connect(ui.spinBox_Height, SIGNAL(valueChanged(int)), this, SLOT(HeightChanged(int)));
	QObject::connect(ui.spinBox_Width, SIGNAL(valueChanged(int)), this, SLOT(WidthChanged(int)));

	QObject::connect(ui.spinBox_X_Angle, SIGNAL(valueChanged(int)), this, SLOT(XAngleChanged(int)));
	QObject::connect(ui.spinBox_Y_Angle, SIGNAL(valueChanged(int)), this, SLOT(YAngleChanged(int)));
	QObject::connect(ui.spinBox_Z_Angle, SIGNAL(valueChanged(int)), this, SLOT(ZAngleChanged(int)));

	QObject::connect(ui.spinBox_R, SIGNAL(valueChanged(int)), this, SLOT(RChanged(int)));
	QObject::connect(ui.spinBox_G, SIGNAL(valueChanged(int)), this, SLOT(GChanged(int)));
	QObject::connect(ui.spinBox_B, SIGNAL(valueChanged(int)), this, SLOT(BChanged(int)));

	QObject::connect(ui.spinBox_Brightness, SIGNAL(valueChanged(int)), this, SLOT(BrightnessChanged(int)));
	QObject::connect(ui.spinBox_Contrast, SIGNAL(valueChanged(int)), this, SLOT(ContrastChanged(int)));

	QObject::connect(ui.spinBox_chroma_R, SIGNAL(valueChanged(int)), this, SLOT(ChromaRChanged(int)));
	QObject::connect(ui.spinBox_chroma_G, SIGNAL(valueChanged(int)), this, SLOT(ChromaGChanged(int)));
	QObject::connect(ui.spinBox_chroma_B, SIGNAL(valueChanged(int)), this, SLOT(ChromaBChanged(int)));
	QObject::connect(ui.spinBox_chroma_RT, SIGNAL(valueChanged(int)), this, SLOT(ChromaRTChanged(int)));
	QObject::connect(ui.spinBox_chroma_GT, SIGNAL(valueChanged(int)), this, SLOT(ChromaGTChanged(int)));
	QObject::connect(ui.spinBox_chroma_BT, SIGNAL(valueChanged(int)), this, SLOT(ChromaBTChanged(int)));
	QObject::connect(ui.checkBoxChromaEnabled, SIGNAL(stateChanged(int)), this, SLOT(ChromaEnabledChaneged(int)));

	QObject::connect(ui.spinBox_Transparency, SIGNAL(valueChanged(int)), this, SLOT(AlfaChanged(int)));

	QObject::connect(ui.spinBox_Clip_Bottom, SIGNAL(valueChanged(int)), this, SLOT(BottomClipChanged(int)));
	QObject::connect(ui.spinBox_Clip_Left, SIGNAL(valueChanged(int)), this, SLOT(LeftClipChanged(int)));
	QObject::connect(ui.spinBox_Clip_Right, SIGNAL(valueChanged(int)), this, SLOT(RightClipChanged(int)));
	QObject::connect(ui.spinBox_Clip_Top, SIGNAL(valueChanged(int)), this, SLOT(TopClipChanged(int)));

	QObject::connect(ui.button_pick_color, SIGNAL(pressed()), this, SLOT(pickColorPressed()));

	QObject::connect(ui.checkBox_keepaspect, SIGNAL(stateChanged(int)), this, SLOT(KeepAspectChanged(int)));
}
bool MqsSurfaceSettings::checkLimits(float x_pos, float y_pos, float x_scale, float y_scale)
{
	///min scale check
	if(x_scale <= 0.1 || y_scale <= 0.1)
		return true;
	///x limits
	if(1 - x_pos < x_scale || x_pos < 0)
		return true;
	///y limits
	if(1 - y_pos < y_scale || y_pos < 0)
		return true;
	return false;
}
void MqsSurfaceSettings::pickColorPressed()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ASSERT_WITH_CODE(color.isValid(), "Not valid color picked!", return);
    ui.spinBox_chroma_R->setValue(color.red());
    ui.spinBox_chroma_G->setValue(color.green());
    ui.spinBox_chroma_B->setValue(color.blue());
}
void MqsSurfaceSettings::ChromaEnabledChaneged(int new_state)
{
	if(new_state == Qt::Checked)
	{
		ui.spinBox_chroma_R->setEnabled(true);
		ui.spinBox_chroma_G->setEnabled(true);
		ui.spinBox_chroma_B->setEnabled(true);
		ui.spinBox_chroma_RT->setEnabled(true);
		ui.spinBox_chroma_GT->setEnabled(true);
		ui.spinBox_chroma_BT->setEnabled(true);

		ui.horizontalSlider_chroma_R->setEnabled(true);
		ui.horizontalSlider_chroma_G->setEnabled(true);
		ui.horizontalSlider_chroma_B->setEnabled(true);
		ui.horizontalSlider_chroma_RT->setEnabled(true);
		ui.horizontalSlider_chroma_GT->setEnabled(true);
		ui.horizontalSlider_chroma_BT->setEnabled(true);
		ui.button_pick_color->setEnabled(true);

		ui.spinBox_chroma_R->setValue(0);
		ui.spinBox_chroma_G->setValue(0);
		ui.spinBox_chroma_B->setValue(0);
		ui.spinBox_chroma_RT->setValue(20);
		ui.spinBox_chroma_GT->setValue(20);
		ui.spinBox_chroma_BT->setValue(20);
		surface->chromaEnabled() = true;
	}
	else
	{
		ui.spinBox_chroma_R->setEnabled(false);
		ui.spinBox_chroma_G->setEnabled(false);
		ui.spinBox_chroma_B->setEnabled(false);
		ui.spinBox_chroma_RT->setEnabled(false);
		ui.spinBox_chroma_GT->setEnabled(false);
		ui.spinBox_chroma_BT->setEnabled(false);

		ui.horizontalSlider_chroma_R->setEnabled(false);
		ui.horizontalSlider_chroma_G->setEnabled(false);
		ui.horizontalSlider_chroma_B->setEnabled(false);
		ui.horizontalSlider_chroma_RT->setEnabled(false);
		ui.horizontalSlider_chroma_GT->setEnabled(false);
		ui.horizontalSlider_chroma_BT->setEnabled(false);
		ui.button_pick_color->setEnabled(false);

		ui.spinBox_chroma_R->setValue(0);
		ui.spinBox_chroma_G->setValue(0);
		ui.spinBox_chroma_B->setValue(0);
		ui.spinBox_chroma_RT->setValue(0);
		ui.spinBox_chroma_GT->setValue(0);
		ui.spinBox_chroma_BT->setValue(0);
		surface->chromaEnabled() = false;
	}
}
void MqsSurfaceSettings::BrightnessChanged(int brightness)
{
	surface->brightnes() = brightness*0.01f;
}
void MqsSurfaceSettings::ContrastChanged(int contrast)
{
	surface->contrast() = contrast*0.01f;
}
void MqsSurfaceSettings::ChromaRChanged(int r_chroma)
{
	QPalette pal = ui.button_pick_color->palette();
	pal.setColor(QPalette::Button, QColor(r_chroma, ui.horizontalSlider_chroma_G->value(), ui.horizontalSlider_chroma_B->value()));
	ui.button_pick_color->setPalette(pal);
	surface->RChroma() = r_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::ChromaGChanged(int g_chroma)
{
	QPalette pal = ui.button_pick_color->palette();
	pal.setColor(QPalette::Button, QColor(ui.horizontalSlider_chroma_R->value(), g_chroma, ui.horizontalSlider_chroma_B->value()));
	ui.button_pick_color->setPalette(pal);
	surface->GChroma() = g_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::ChromaBChanged(int b_chroma)
{
	QPalette pal = ui.button_pick_color->palette();
	pal.setColor(QPalette::Button, QColor(ui.horizontalSlider_chroma_R->value(), ui.horizontalSlider_chroma_G->value(), b_chroma));
	ui.button_pick_color->setPalette(pal);
	surface->BChroma() = b_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::ChromaRTChanged(int rt_chroma)
{
	surface->RTChroma() = rt_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::ChromaGTChanged(int gt_chroma)
{
	surface->GTChroma() = gt_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::ChromaBTChanged(int bt_chroma)
{
	surface->BTChroma() = bt_chroma*0.004f;//1/256
}
void MqsSurfaceSettings::AlfaChanged(int a)
{
	surface->alfa() = 1.0f - (a * 0.01f);
}
void MqsSurfaceSettings::RChanged(int r)
{
	surface->rColor() = r*0.004f;//1/256
}
void MqsSurfaceSettings::GChanged(int g)
{
	surface->gColor() = g*0.004f;//1/256
}
void MqsSurfaceSettings::BChanged(int b)
{
	surface->bColor() = b*0.004f;//1/256
}
void MqsSurfaceSettings::HeightChanged(int height)
{
	if(!checkLimits(surface->xPos(), surface->yPos(), surface->xScale(), height *0.01f))
		surface->yScale() = height *0.01f;
	else
		ui.spinBox_Height->setValue(surface->yScale()*100);
}
void MqsSurfaceSettings::WidthChanged(int width)
{
	if(!checkLimits(surface->xPos(), surface->yPos(), width * 0.01f, surface->yScale()))
		surface->xScale() = width *0.01f;
	else
		ui.spinBox_Width->setValue(surface->xScale()*100);
}
void MqsSurfaceSettings::KeepAspectChanged(int state)
{
	surface->keepAspect() = state;
}
void MqsSurfaceSettings::BottomClipChanged(int bot_clip)
{
	surface->bottomCut() = bot_clip * 0.01f * 0.5f;
	surface->updateClipping();
}
void MqsSurfaceSettings::TopClipChanged(int top_clip)
{
	surface->topCut() = top_clip * 0.01f * 0.5f;
	surface->updateClipping();
}
void MqsSurfaceSettings::RightClipChanged(int right_clip)
{
	surface->rightCut() = right_clip * 0.01f * 0.5f;
	surface->updateClipping();
}
void MqsSurfaceSettings::LeftClipChanged(int left_clip)
{
	surface->leftCut() = left_clip * 0.01f * 0.5f;
	surface->updateClipping();
}
void MqsSurfaceSettings::XAngleChanged(int new_x_angle)
{
	surface->xAngle() = new_x_angle;
}
void MqsSurfaceSettings::YAngleChanged(int new_y_angle)
{
	surface->yAngle() = new_y_angle;
}
void MqsSurfaceSettings::ZAngleChanged(int new_z_angle)
{
	surface->zAngle() = new_z_angle;
}
void MqsSurfaceSettings::XPosChanged(int new_xpos)
{
	surface->xPos() = new_xpos*0.01f * (1 - surface->xScale());
}
void MqsSurfaceSettings::YPosChanged(int new_ypos)
{
	surface->yPos() = new_ypos*0.01f * (1 - surface->yScale());
}
void MqsSurfaceSettings::closeEvent ( QCloseEvent * event )
{
}
