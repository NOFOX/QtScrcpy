#ifndef PHONEWALL_H
#define PHONEWALL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QPointer>
#include "groupcontroller.h"

class DeviceCard : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceCard(int deviceId, QWidget *parent = nullptr);
    
    void setOnline(bool online);
    void setDeviceName(const QString &name);
    int deviceId() const { return m_deviceId; }
    bool isOnline() const { return m_online; }
    
signals:
    void clicked(int deviceId);
    void doubleClicked(int deviceId);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int m_deviceId;
    bool m_online;
    bool m_hovered;
    QString m_deviceName;
};

class PhoneWallOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneWallOverlay(int deviceId, QWidget *parent = nullptr);
    void show();
    
signals:
    void closeRequested();
    void connectRequested(int deviceId);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_deviceId;
};

class PhoneWall : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneWall(QWidget *parent = nullptr);
    
    void setDeviceCount(int count);
    void updateDeviceStatus(int deviceId, bool online, const QString &name = QString());
    
signals:
    void deviceClicked(int deviceId);
    void deviceDoubleClicked(int deviceId);

private slots:
    void onDeviceCountChanged(int index);

private:
    void setupUI();
    void updateGridLayout();
    int getDeviceCountFromIndex(int index) const;

private:
    QComboBox *m_deviceCountCombo;
    QLabel *m_deviceCountLabel;
    QScrollArea *m_scrollArea;
    QWidget *m_container;
    QGridLayout *m_gridLayout;
    
    QMap<int, DeviceCard*> m_deviceCards;
    int m_currentDeviceCount;
};

#endif // PHONEWALL_H
