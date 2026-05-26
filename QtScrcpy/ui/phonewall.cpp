#include "phonewall.h"
#include <QApplication>
#include <QScreen>

// DeviceCard implementation
DeviceCard::DeviceCard(int deviceId, QWidget *parent)
    : QWidget(parent)
    , m_deviceId(deviceId)
    , m_online(false)
    , m_hovered(false)
    , m_deviceName(QString("Device %1").arg(deviceId))
{
    setMinimumSize(120, 220);
    setCursor(Qt::PointingHandCursor);
    setToolTip(QString("Double-click to connect Device %1").arg(deviceId));
}

void DeviceCard::setOnline(bool online)
{
    m_online = online;
    update();
}

void DeviceCard::setDeviceName(const QString &name)
{
    m_deviceName = name.isEmpty() ? QString("Device %1").arg(m_deviceId) : name;
    update();
}

void DeviceCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Background
    QColor bgColor = m_hovered ? QColor(25, 25, 35) : QColor(18, 18, 24);
    if (m_online) {
        bgColor = m_hovered ? QColor(25, 35, 25) : QColor(18, 28, 24);
    }
    
    painter.fillRect(rect(), bgColor);
    
    // Border
    QColor borderColor = m_hovered ? QColor(255, 107, 107) : QColor(40, 40, 50);
    painter.setPen(QPen(borderColor, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(rect().adjusted(2, 2, -2, -2), 8, 8);
    
    // Status indicator
    int indicatorSize = 10;
    int indicatorMargin = 8;
    QRect indicatorRect(indicatorMargin, indicatorMargin, indicatorSize, indicatorSize);
    painter.setBrush(m_online ? QColor(0, 255, 0) : QColor(255, 0, 0));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(indicatorRect.center(), indicatorSize/2, indicatorSize/2);
    
    // Screen area (9:16 aspect ratio)
    int screenMargin = 30;
    int screenWidth = width() - 2 * screenMargin;
    int screenHeight = (screenWidth * 16) / 9;
    int screenX = screenMargin;
    int screenY = (height() - screenHeight) / 2;
    
    QRect screenRect(screenX, screenY, screenWidth, screenHeight);
    painter.setBrush(QColor(30, 30, 40));
    painter.setPen(QPen(QColor(60, 60, 80), 1));
    painter.drawRoundedRect(screenRect, 4, 4);
    
    // Device name label
    QFont font = painter.font();
    font.setPointSize(10);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QColor(255, 255, 255));
    QString displayText = m_deviceName;
    if (displayText.length() > 15) {
        displayText = displayText.left(12) + "...";
    }
    painter.drawText(screenRect.bottomLeft().x(), 
                     screenRect.bottomLeft().y() + 25, 
                     width() - 2*screenMargin, 
                     20, 
                     Qt::AlignCenter, 
                     displayText);
    
    // Connection hint
    if (!m_online) {
        QFont smallFont = painter.font();
        smallFont.setPointSize(8);
        painter.setFont(smallFont);
        painter.setPen(QColor(150, 150, 150));
        painter.drawText(rect(), Qt::AlignBottom | Qt::AlignHCenter, "Double-click to connect");
    }
}

void DeviceCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(m_deviceId);
    }
    QWidget::mousePressEvent(event);
}

void DeviceCard::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit doubleClicked(m_deviceId);
    }
    QWidget::mouseDoubleClickEvent(event);
}

void DeviceCard::enterEvent(QEvent *event)
{
    m_hovered = true;
    update();
    QWidget::enterEvent(event);
}

void DeviceCard::leaveEvent(QEvent *event)
{
    m_hovered = false;
    update();
    QWidget::leaveEvent(event);
}

// PhoneWallOverlay implementation
PhoneWallOverlay::PhoneWallOverlay(int deviceId, QWidget *parent)
    : QWidget(parent)
    , m_deviceId(deviceId)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(400, 300);
}

void PhoneWallOverlay::show()
{
    QWidget::show();
    raise();
    activateWindow();
}

void PhoneWallOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Semi-transparent background
    painter.fillRect(rect(), QColor(0, 0, 0, 200));
    
    // Content box
    QRect contentRect = rect().adjusted(50, 50, -50, -50);
    painter.setBrush(QColor(30, 30, 40));
    painter.setPen(QPen(QColor(255, 107, 107), 2));
    painter.drawRoundedRect(contentRect, 10, 10);
    
    // Device info
    painter.setPen(QColor(255, 255, 255));
    QFont font = painter.font();
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    QString title = QString("Device %1").arg(m_deviceId);
    painter.drawText(contentRect, Qt::AlignTop | Qt::AlignHCenter, title);
    
    // Instructions
    font.setPointSize(12);
    font.setBold(false);
    painter.setFont(font);
    painter.setPen(QColor(200, 200, 200));
    QString instructions = "Click outside to close\nDouble-click card to connect";
    painter.drawText(contentRect, Qt::AlignCenter, instructions);
}

void PhoneWallOverlay::mousePressEvent(QMouseEvent *event)
{
    // Close when clicking outside the content area
    QRect contentRect = rect().adjusted(50, 50, -50, -50);
    if (!contentRect.contains(event->pos())) {
        emit closeRequested();
        close();
    }
    QWidget::mousePressEvent(event);
}

// PhoneWall implementation
PhoneWall::PhoneWall(QWidget *parent)
    : QWidget(parent)
    , m_currentDeviceCount(8)
{
    setupUI();
}

void PhoneWall::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    
    // Toolbar
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    m_deviceCountLabel = new QLabel("Devices:");
    m_deviceCountLabel->setStyleSheet("color: #ffffff; font-weight: bold;");
    toolbarLayout->addWidget(m_deviceCountLabel);
    
    m_deviceCountCombo = new QComboBox();
    m_deviceCountCombo->addItem("4 devices", 4);
    m_deviceCountCombo->addItem("8 devices", 8);
    m_deviceCountCombo->addItem("12 devices", 12);
    m_deviceCountCombo->addItem("16 devices", 16);
    m_deviceCountCombo->addItem("18 devices", 18);
    m_deviceCountCombo->addItem("24 devices", 24);
    m_deviceCountCombo->setCurrentIndex(1); // Default to 8
    m_deviceCountCombo->setStyleSheet(
        "QComboBox { "
        "   background-color: #2a2a3a; "
        "   color: #ffffff; "
        "   border: 1px solid #ff6b6b; "
        "   padding: 5px; "
        "   border-radius: 4px; "
        "} "
        "QComboBox::drop-down { "
        "   border: none; "
        "   width: 20px; "
        "} "
        "QComboBox QAbstractItemView { "
        "   background-color: #2a2a3a; "
        "   color: #ffffff; "
        "   border: 1px solid #ff6b6b; "
        "}"
    );
    connect(m_deviceCountCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &PhoneWall::onDeviceCountChanged);
    toolbarLayout->addWidget(m_deviceCountCombo);
    
    toolbarLayout->addStretch();
    
    mainLayout->addLayout(toolbarLayout);
    
    // Scroll area for grid
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setStyleSheet(
        "QScrollArea { "
        "   background-color: transparent; "
        "   border: none; "
        "}"
    );
    
    m_container = new QWidget();
    m_gridLayout = new QGridLayout(m_container);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSpacing(15);
    
    m_scrollArea->setWidget(m_container);
    mainLayout->addWidget(m_scrollArea);
    
    updateGridLayout();
}

void PhoneWall::updateGridLayout()
{
    // Clear existing cards
    QLayoutItem *child;
    while ((child = m_gridLayout->takeAt(0)) != nullptr) {
        child->widget()->deleteLater();
        delete child;
    }
    m_deviceCards.clear();
    
    // Create new cards
    for (int i = 0; i < m_currentDeviceCount; ++i) {
        DeviceCard *card = new DeviceCard(i + 1);
        m_deviceCards[i + 1] = card;
        
        connect(card, &DeviceCard::clicked, this, &PhoneWall::deviceClicked);
        connect(card, &DeviceCard::doubleClicked, this, &PhoneWall::deviceDoubleClicked);
        
        int row = i / 8; // 8 columns fixed
        int col = i % 8;
        m_gridLayout->addWidget(card, row, col);
    }
    
    // Add stretch to fill remaining space
    for (int col = 0; col < 8; ++col) {
        m_gridLayout->setColumnStretch(col, 1);
    }
}

void PhoneWall::onDeviceCountChanged(int index)
{
    int count = getDeviceCountFromIndex(index);
    if (count != m_currentDeviceCount) {
        m_currentDeviceCount = count;
        updateGridLayout();
    }
}

int PhoneWall::getDeviceCountFromIndex(int index) const
{
    switch (index) {
        case 0: return 4;
        case 1: return 8;
        case 2: return 12;
        case 3: return 16;
        case 4: return 18;
        case 5: return 24;
        default: return 8;
    }
}

void PhoneWall::setDeviceCount(int count)
{
    int index = 1; // Default to 8
    if (count == 4) index = 0;
    else if (count == 12) index = 2;
    else if (count == 16) index = 3;
    else if (count == 18) index = 4;
    else if (count == 24) index = 5;
    
    m_deviceCountCombo->setCurrentIndex(index);
}

void PhoneWall::updateDeviceStatus(int deviceId, bool online, const QString &name)
{
    if (m_deviceCards.contains(deviceId)) {
        m_deviceCards[deviceId]->setOnline(online);
        if (!name.isEmpty()) {
            m_deviceCards[deviceId]->setDeviceName(name);
        }
    }
}
