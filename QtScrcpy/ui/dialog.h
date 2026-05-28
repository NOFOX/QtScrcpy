#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QPointer>
#include <QMessageBox>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QListWidget>
#include <QTimer>
#include <QTreeWidget>
#include <QLineEdit>
#include <QProcess>
#include <QTextEdit>

class QGridLayout;
class QComboBox;
class QPushButton;
class QGroupBox;
class QFrame;
class QVBoxLayout;

#include "adbprocess.h"
#include "../QtScrcpyCore/include/QtScrcpyCore.h"
#include "audio/audiooutput.h"

namespace Ui
{
    class Widget;
}

struct DeviceInfo {
    QString serial;
    QString deviceName;
    QString alias;
    QString group;
    QString ip;
    bool online = false;
};

class QYUVOpenGLWidget;
class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void outLog(const QString &log, bool newLine = true);
    bool filterLog(const QString &log);
    void getIPbyIp();

private slots:
    void onDeviceConnected(bool success, const QString& serial, const QString& deviceName, const QSize& size);
    void onDeviceDisconnected(QString serial);

    void on_updateDevice_clicked();
    void on_startServerBtn_clicked();
    void on_stopServerBtn_clicked();
    void on_wirelessConnectBtn_clicked();
    void on_startAdbdBtn_clicked();
    void on_getIPBtn_clicked();
    void on_wirelessDisConnectBtn_clicked();
    void on_selectRecordPathBtn_clicked();
    void on_recordPathEdt_textChanged(const QString &arg1);
    void on_adbCommandBtn_clicked();
    void on_stopAdbBtn_clicked();
    void on_clearOut_clicked();
    void on_stopAllServerBtn_clicked();
    void on_refreshGameScriptBtn_clicked();
    void on_applyScriptBtn_clicked();
    void on_recordScreenCheck_clicked(bool checked);
    void on_usbConnectBtn_clicked();
    void on_wifiConnectBtn_clicked();
    void on_connectedPhoneList_itemDoubleClicked(QListWidgetItem *item);
    void on_updateNameBtn_clicked();
    void on_useSingleModeCheck_clicked();
    void on_serialBox_currentIndexChanged(const QString &arg1);

    void on_startAudioBtn_clicked();

    void on_stopAudioBtn_clicked();

    void on_installSndcpyBtn_clicked();

    void on_autoUpdatecheckBox_toggled(bool checked);

    void showIpEditMenu(const QPoint &pos);
    void onPhoneSlotClicked();
    void onPhoneWallCountChanged(const QString &count);

    // Window control slots
    void onMinimize();
    void onMaximize();
    void onClose();

    // Sidebar slots
    void onToggleSidebar();
    void onScanDevices();
    void onFilterChanged();
    void onDeviceTreeDoubleClicked(QTreeWidgetItem *item, int column);
    void onTerminalCommandEntered();
    void readTerminalOutput();
    void onDeviceTreeContextMenu(const QPoint &pos);
    void onEditAlias();
    void onEditGroup();

private:
    bool checkAdbRun();
    void initUI();
    void updateBootConfig(bool toView = true);
    void execAdbCmd();
    void delayMs(int ms);
    QString getGameScript(const QString &fileName);
    void slotActivated(QSystemTrayIcon::ActivationReason reason);
    int findDeviceFromeSerialBox(bool wifi);
    quint32 getBitRate();
    const QString &getServerPath();
    void loadIpHistory();
    void saveIpHistory(const QString &ip);
    void loadPortHistory();
    void savePortHistory(const QString &port);

    void showPortEditMenu(const QPoint &pos);
    void createPhoneWall();
    void createSidebar();

    int findPhoneSlot(const QString &serial) const;
    int findEmptyPhoneSlot() const;
    void updatePhoneSlot(int index, const QString &serial, const QString &deviceName, bool online);
    void clearPhoneSlot(int index);
    void refreshPhoneWallSlots();
    void updateDeviceTree();

protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::Widget *ui;
    qsc::AdbProcess m_adb;
    QSystemTrayIcon *m_hideIcon;
    QMenu *m_menu;
    QAction *m_showWindow;
    QAction *m_quit;
    AudioOutput m_audioOutput;
    QTimer m_autoUpdatetimer;

    // Phone Wall
    QGroupBox *m_phoneWallGroupBox = nullptr;
    QWidget *m_phoneWallContainer = nullptr;
    QGridLayout *m_phoneWallGrid = nullptr;
    QComboBox *m_phoneCountBox = nullptr;
    QVector<QFrame*> m_phoneSlotWidgets;
    QVector<QString> m_phoneSlotSerials;
    int m_phoneWallCount = 24;

    // Sidebar
    QWidget *m_sidePanel = nullptr;
    QPushButton *m_expandBtn = nullptr;
    QTreeWidget *m_deviceTree = nullptr;
    QLineEdit *m_filterEdit = nullptr;
    QTextEdit *m_terminalOutput = nullptr;
    QLineEdit *m_terminalInput = nullptr;
    QProcess *m_powershell = nullptr;

    QMap<QString, DeviceInfo> m_devices; // serial -> info

    // Drag move
    QPoint m_dragPosition;
    bool m_isDragging = false;
    QWidget *m_titleBar = nullptr;
};

#endif // DIALOG_H
