#ifndef WIDGET_H
#define WIDGET_H

#include <QHotkey>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

#include "inc/config.h"
#include "KeyThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void InitUi(void);
    void InitHotkey(void);

private slots:
    void on_spinBox_interval_valueChanged(int arg1);
    void on_keySequence_switch_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequence_start_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequence_key1_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequence_key2_keySequenceChanged(const QKeySequence &keySequence);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    struct menus { public: enum { Setting=0, Quit, Qty }; };

    Ui::Widget* m_ui;

    QAction* m_action[menus::Qty];
    QHotkey* m_pSwitchHotKey;
    QHotkey* m_pStartHotKey;
    QSystemTrayIcon* m_trayIcon;
    QMenu* m_menu;

    KeyThread m_t;

    HOTKEY_CFG m_config;
};
#endif // WIDGET_H
