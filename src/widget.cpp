#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::Widget)
{
    m_ui->setupUi(this);
    InitUi();
    InitHotkey();
}

Widget::~Widget()
{
    delete m_ui;
}

void Widget::InitUi()
{
    m_ui->spinBox_interval->setSingleStep(1000);
    m_ui->spinBox_interval->setMaximum(2000000000);
    m_config = Config::GetConfig();
    m_ui->keySequence_switch->setKeySequence(m_config.toKey(HOTKEY_CFG::next));
    m_ui->keySequence_start->setKeySequence(m_config.toKey(HOTKEY_CFG::stop));
    m_ui->keySequence_key1->setKeySequence(m_config.toKey(HOTKEY_CFG::key1));
    m_ui->keySequence_key2->setKeySequence(m_config.toKey(HOTKEY_CFG::key2));
    m_ui->spinBox_interval->setValue(m_config.nTimeInterval);

    QIcon icon = QIcon(ICON_RES);
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(icon);
    m_trayIcon->setToolTip("小小按键精灵");
    m_trayIcon->show();

    m_action[menus::Setting] = new QAction("设置", this);
    connect(m_action[menus::Setting], SIGNAL(triggered()), this, SLOT(showNormal()));

    m_action[menus::Quit] = new QAction("退出", this);
    connect(m_action[menus::Quit], SIGNAL(triggered()), qApp, SLOT(quit()));

    m_menu = new QMenu(this);
    m_menu->addAction(m_action[menus::Setting]);
    m_menu->addAction(m_action[menus::Quit]);
    m_trayIcon->setContextMenu(m_menu);

    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void Widget::InitHotkey()
{
    m_pSwitchHotKey = new QHotkey(QKeySequence(m_config.vkNext), true, this);

    connect(m_pSwitchHotKey, &QHotkey::activated, this, [&](){
        qDebug() << "Hotkey Activated - Next Shutcut";
        this->m_t.switchKey();
    });


    m_pStartHotKey = new QHotkey(QKeySequence(m_config.vkStop), true, this);
    connect(m_pStartHotKey, &QHotkey::activated, this, [&](){

        if (this->m_t.isRunning()) {
            qDebug() << "Hotkey Activated - Stop Shutcut";
            this->m_t.stop();
        } else {
            qDebug() << "Hotkey Activated - Start Shutcut";
            this->m_t.start();
        }
    });
}


void Widget::on_spinBox_interval_valueChanged(int arg1)
{
    m_config.nTimeInterval = arg1;
    Config::SetConfig(m_config);
    m_t.reset(m_config);
}

void Widget::on_keySequence_switch_keySequenceChanged(const QKeySequence &keySequence)
{
    if (keySequence.count() == 0) return;
    m_config.vkNext = keySequence[0];
    Config::SetConfig(m_config);
    m_t.reset(m_config);
    m_pSwitchHotKey->setShortcut(QKeySequence(m_config.vkNext), true);
}

void Widget::on_keySequence_start_keySequenceChanged(const QKeySequence &keySequence)
{
    if (keySequence.count() == 0) return;
    m_config.vkStop = keySequence[0];
    Config::SetConfig(m_config);
    m_t.reset(m_config);
    m_pSwitchHotKey->setShortcut(QKeySequence(m_config.vkStop), true);
}

void Widget::on_keySequence_key1_keySequenceChanged(const QKeySequence &keySequence)
{
    if (keySequence.count() == 0) return;
    m_config.vkKey1 = keySequence[0];
    Config::SetConfig(m_config);
    m_t.reset(m_config);
}

void Widget::on_keySequence_key2_keySequenceChanged(const QKeySequence &keySequence)
{
    if (keySequence.count() == 0) return;
    m_config.vkKey2 = keySequence[0];
    Config::SetConfig(m_config);
    m_t.reset(m_config);
}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger: break;
    case QSystemTrayIcon::DoubleClick: showNormal(); break;
    case QSystemTrayIcon::MiddleClick: break;
    default: break;
    }

}

void Widget::changeEvent(QEvent *e)
{
    if((e->type() == QEvent::WindowStateChange) && isMinimized())
    {
        e->ignore();
        hide();
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    m_t.stop();
    m_t.quit();
    m_t.wait();
    event->accept();
}

