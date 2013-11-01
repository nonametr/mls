#include <qmessagebox>
#include <qinputdialog.h>
#include <qcolordialog.h>
#include <qrgb.h>

#include "gui_main.h"
#include "settings.h"

void MlsMain::onSceneContextMenuRequested(const QPoint &pos)
{
    menu["list_scenes_context"]->exec(QCursor::pos());
}

void MlsMain::onScenePressed(QListWidgetItem *item)
{
    string scene_handle = item->text().toStdString();

    if (QApplication::mouseButtons() == Qt::RightButton)
    {
        menu["list_scenes_actions"]->exec(QCursor::pos());
        return;
    }

    view->save();
    view->load(scene_handle);
}

void MlsMain::onSceneCreate()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Scene creation", "Scene name:", QLineEdit::Normal, "type name here", &ok);
    if (ok == true)
    {
        settings->query("INSERT INTO scene VALUES('%s', 1, 0)", name.toStdString().c_str());
        ui.list_scenes->addItem(name);
    }
}

void MlsMain::onSceneDelete()
{
    if(QMessageBox::question(this,"Confirmation","Are you really want to delete scene?",QMessageBox::Yes,QMessageBox::No) ==	QMessageBox::No)
        return;
    if (ui.list_scenes->selectedItems().first()->text() == "Default")
    {
        QMessageBox::information(this, "Can't remove", "Can't delete default scene. It's configured as startup scene.", QMessageBox::Ok);
        return;
    }
    if (ui.list_scenes->selectedItems().size())
    {
        QListWidgetItem *item = ui.list_scenes->selectedItems().first();
        settings->query("DELETE FROM surface WHERE scene = '%s'", item->text().toStdString().c_str());
        settings->query("DELETE FROM scene WHERE name = '%s'", item->text().toStdString().c_str());
        delete item;
    }
}

void MlsMain::onSceneSetBackground()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ASSERT_WITH_CODE(color.isValid(), "Not valid color picked!", return);
    settings->query("UPDATE scene SET background_r = %u, background_g = %u, background_b = %u WHERE active = 1", color.red(), color.green(), color.blue());
    view->setBG(color.red(), color.green(), color.blue());
}

void MlsMain::onSceneRename()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Scene rename", "Scene name:", QLineEdit::Normal, ui.list_scenes->selectedItems().first()->text(), &ok);
    if (ok == true)
    {
        QString old_name = ui.list_scenes->selectedItems().first()->text();
        //settings->query("UPDATE surface SET scene = '%s' WHERE scene = '%s'", name.toStdString().c_str(), old_name.toStdString().c_str());//its should be done automatically by current foreign key rules but we still do it manualy
        settings->query("UPDATE scene SET name = '%s' WHERE name = '%s'", name.toStdString().c_str(), old_name.toStdString().c_str());
        ui.list_scenes->selectedItems().first()->setText(name);
    }
}

void MlsMain::updateScenes()
{
    ui.list_scenes->clear();
    QSqlRecord scenes_info = settings->query("SELECT count(*) as is_exist FROM scene").record();
    if(!scenes_info.value("is_exist").toBool())
    {
        traceerr("Warning! There is no active scenes. Please create some scene first!");
        return;
    }
    QSqlQuery scenes_result = settings->query("SELECT name FROM scene");
    do
    {
        QSqlRecord scene = scenes_result.record();
        ui.list_scenes->addItem(scene.value("name").toString());
    } while (scenes_result.next());
}
