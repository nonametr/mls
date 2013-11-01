#include "gui_main.h"

void MlsMain::onSelectSource(string surface_handle)
{
    QList<QListWidgetItem*> selection = ui.list_sources->findItems(surface_handle.c_str(), Qt::MatchExactly);
    ui.list_sources->clearSelection();
    ui.list_sources->setFocus();
    if (selection.size())
        selection.first()->setSelected(true);
}

void MlsMain::onSourceContextMenuRequested(const QPoint &)
{
    menu["list_source_context"]->exec(QCursor::pos());
}

void MlsMain::onContextSourceAdd()
{
    menu["Add source..."]->exec(QCursor::pos());
}

void MlsMain::onSourcePressed(QListWidgetItem *item)
{
    string surface_handle = item->text().toStdString();
    view->selectSurface(surface_handle);

    if (QApplication::mouseButtons() == Qt::RightButton)
    {
        menu["list_source_actions"]->exec(QCursor::pos());
    }
}

void MlsMain::onDeleteSource(string source_name)
{
    QList<QListWidgetItem*> selected_sources = ui.list_sources->findItems(source_name.c_str(), Qt::MatchExactly);
    ASSERT_WITH_CODE(selected_sources.size(), "Error! Can't delete unknown source", return);
    delete selected_sources.first();
}

void MlsMain::onAddSource(string source_name)
{
    ui.list_sources->addItem(source_name.c_str());
}

void MlsMain::onSourceHideShow()
{
    if(view->isSurfaceVisible())
    {
        view->hideSurface(SELLECTED_SURFACE);
    }
    else
    {
        view->showSurface(SELLECTED_SURFACE);
    }
}

void MlsMain::onSourceRemove()
{
    view->deleteSurface(SELLECTED_SURFACE);
    if (ui.list_sources->selectedItems().size())
        delete ui.list_sources->selectedItems().first();
}

void MlsMain::onSourceSettings()
{
    view->showSurfaceSetting(SELLECTED_SURFACE);
}
