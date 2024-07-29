#include "gpioinputcontroller.h"
#include "controller/controllermanager.h"
#include "mcpreader.h"
#include "plaingpioreader.h"

#include "helpers.h"

QLatin1String GPIOInputController::GPIO_TYPE_PLAIN = QLatin1String("plain");
QLatin1String GPIOInputController::GPIO_TYPE_MCP = QLatin1String("mcp");


GPIOInputController::GPIOInputController(ControllerManager* manager, QString id, QObject *parent) : DigitalInputControllerBase (manager, id, parent)
{
    connect(&m_i2cSanityChecker, &I2CSanityChecker::i2cNotDetected, this, &GPIOInputController::onI2cNotDetected);
}

void GPIOInputController::init() {
    iDebug() << Q_FUNC_INFO;

    DigitalInputControllerBase::init();

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_clientSystemWarningsManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    if (m_config->getInt(this, "inputCount", 0) > 0) {        // can be overwritten by custom input count, if plain: mandatory to set
        m_inputCount = m_config->getInt(this, "inputCount", 0);
    }

    QString gpioType = m_config->getString(this, "gpioType", GPIO_TYPE_PLAIN);
    if (gpioType == GPIO_TYPE_PLAIN) {
        QString pins = m_config->getString(this, "pins", "");       // e.g. "3 21 33"
        QList<int> pinList;

        for (QString pin : pins.split(" ", QString::SkipEmptyParts)) {
            pinList << pin.toInt();
        }
        m_inputCount = pinList.count();
        iDebug() << "pins:" << pinList;

        m_reader = new PlainGPIOReader(pinList);
    } else if (gpioType == GPIO_TYPE_MCP) {
        int pinBase = m_config->getInt(this, "mcp.pinBase", 64);
        int addr = m_config->getInt(this, "mcp.addr", 0x20);
        int pinOffset = m_config->getInt(this, "mcp.pinOffset", 0);

        if (m_inputCount == 0) {
            m_inputCount = MCP23017_INPUT_COUNT;
        }

        iDebug() << "MCP init" << pinBase << addr;
        m_reader = new MCPReader(m_inputCount, addr, pinBase, pinOffset, true);
    } else {
        iWarning() << "Invalid gpio type or not set" << gpioType;
        Q_ASSERT(false);
    }

    int i2cBus = m_config->getInt(this, "i2cCheck.bus", 1);
    QStringList i2cDevs = m_config->getString(this, "i2cCheck.addr", "").split(" ", QString::SkipEmptyParts); // 32 33, as dec
    if (!i2cDevs.isEmpty()) {
        QList<int> devList;
        for (QString s : i2cDevs) {
            devList << s.toInt();
            iInfo() << "Adding to checklist" << s;
        }

        m_i2cSanityChecker.setBus(i2cBus);
        m_i2cSanityChecker.setDevList(devList);
    }


    Q_ASSERT(m_reader!=nullptr);
    Q_ASSERT(m_inputCount > 0);

    connect(m_reader, &GPIOReaderBase::stateChanged, this, &GPIOInputController::onStateChanged);
    connect(m_reader, &GPIOReaderBase::error, this, &GPIOInputController::onError);

}

void GPIOInputController::start() {
    iDebug() << Q_FUNC_INFO;

    m_reader->start();
    m_i2cSanityChecker.start();
}

quint8 GPIOInputController::inputCount() {
    return m_inputCount;
}

void GPIOInputController::onError(QString desc) {
    iWarning() << Q_FUNC_INFO << desc;
}

void GPIOInputController::onStateChanged(quint8 index, bool state) {
    Q_ASSERT(index < inputCount());
    m_valueManager->updateAndPublishValue(m_valueMappings.at(index), state);
}

void GPIOInputController::onI2cNotDetected() {
    iWarning() << Q_FUNC_INFO;

    m_clientSystemWarningsManager->raiseWarning("I2C not detected", QtMsgType::QtCriticalMsg);
}
