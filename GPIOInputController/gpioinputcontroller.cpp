#include "gpioinputcontroller.h"
#include "controller/controllermanager.h"
#include "mcpreader.h"
#include "plaingpioreader.h"

#include "helpers.h"

QLatin1String GPIOInputController::GPIO_TYPE_PLAIN = QLatin1String("plain");
QLatin1String GPIOInputController::GPIO_TYPE_MCP = QLatin1String("mcp");


GPIOInputController::GPIOInputController(ControllerManager* manager, QString id, QObject *parent) : DigitalInputControllerBase (manager, id, parent)
{
}

void GPIOInputController::init() {
    iDebug() << Q_FUNC_INFO;

    DigitalInputControllerBase::init();

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);


    if (m_config->getInt("inputCount", 0) > 0) {        // can be overwritten by custom input count, if plain: mandatory to set
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

        if (m_inputCount == 0) {
            m_inputCount = MCP23017_INPUT_COUNT;
        }

        iDebug() << "MCP init" << pinBase << addr;
        m_reader = new MCPReader(m_inputCount, addr, pinBase);
    } else {
        iWarning() << "Invalid gpio type or not set" << gpioType;
        Q_ASSERT(false);
    }

    Q_ASSERT(m_reader!=nullptr);
    Q_ASSERT(m_inputCount > 0);

    connect(m_reader, &GPIOReaderBase::stateChanged, this, &GPIOInputController::onStateChanged);
    connect(m_reader, &GPIOReaderBase::error, this, &GPIOInputController::onError);

}

void GPIOInputController::start() {
    iDebug() << Q_FUNC_INFO;

    m_reader->start();
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
