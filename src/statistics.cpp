// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2023 Fabian Köhler <me@fkoehler.org>
#include "statistics.hpp"
#include "libktailctl_wrapper.h"
#include "logging_statistics.hpp"
#include "tailscale.hpp"

#include <QFile>
#include <QTextStream>

Statistics::Statistics(QObject *parent)
    : QObject(parent)
    , mTimerTotalSpeed(new QTimer(this))
    , mSpeedUpTotal(new SpeedStatistics(this))
    , mSpeedDownTotal(new SpeedStatistics(this))
{
    // for (const Peer *peer : Tailscale::instance()->peers()) {
    //     auto iterUp = mSpeedUp.insert(peer->id(), new SpeedStatistics(this));
    //     auto iterDown = mSpeedDown.insert(peer->id(), new SpeedStatistics(this));
    //     iterUp.value()->update(peer->txBytes());
    //     iterDown.value()->update(peer->rxBytes());

    //     QObject::connect(peer, &Peer::txBytesChanged, iterUp.value(), &SpeedStatistics::update);
    //     QObject::connect(peer, &Peer::rxBytesChanged, iterDown.value(), &SpeedStatistics::update);
    // }

    QObject::connect(mTimerTotalSpeed, &QTimer::timeout, this, &Statistics::refreshTotalSpeed);
    mTimerTotalSpeed->setInterval(200);
    mTimerTotalSpeed->start();
}

SpeedStatistics *Statistics::speedUp(const QString &id)
{
    auto iter = mSpeedUp.find(id);
    if (iter == mSpeedUp.end()) {
        qCCritical(Logging::Statistics) << "No up speed statistics for peer" << id;
        return nullptr;
    }
    return iter.value();
}
SpeedStatistics *Statistics::speedDown(const QString &id)
{
    auto iter = mSpeedDown.find(id);
    if (iter == mSpeedDown.end()) {
        qCCritical(Logging::Statistics) << "No down speed statistics for peer" << id;
        return nullptr;
    }
    return iter.value();
}

SpeedStatistics *Statistics::totalUpSpeed() const
{
    return mSpeedUpTotal;
}
SpeedStatistics *Statistics::totalDownSpeed() const
{
    return mSpeedDownTotal;
}

void Statistics::statusRefreshed()
{
    // bool newPeers = false;
    // for (const Peer *peer : Tailscale::instance()->peers()) {
    //     if (mSpeedUp.contains(peer->id())) {
    //         continue;
    //     }

    //     newPeers = true;

    //     auto iterUp = mSpeedUp.insert(peer->id(), new SpeedStatistics(this));
    //     auto iterDown = mSpeedDown.insert(peer->id(), new SpeedStatistics(this));
    //     iterUp.value()->update(peer->txBytes());
    //     iterDown.value()->update(peer->rxBytes());

    //     QObject::connect(peer, &Peer::txBytesChanged, iterUp.value(), &SpeedStatistics::update);
    //     QObject::connect(peer, &Peer::rxBytesChanged, iterDown.value(), &SpeedStatistics::update);
    // }

    // if (newPeers) {
    //     emit speedUpChanged();
    //     emit speedDownChanged();
    // }
}

void Statistics::refreshTotalSpeed()
{
    // GoString tmpName;
    // tailscale_get_interface_name(&tmpName);
    // const auto name = QString::fromUtf8(tmpName.p, tmpName.n);

    // QFile fileTx(QString("/sys/class/net/%1/statistics/tx_bytes").arg(name));
    // if (!fileTx.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qCCritical(logcat_statistics, "Cannot read tx_bytes");
    //     return;
    // }
    // QTextStream streamTx(&fileTx);
    // long bytes = 0;
    // streamTx >> bytes;
    // mSpeedUpTotal->update(bytes);

    // QFile fileRx(QString("/sys/class/net/%1/statistics/rx_bytes").arg(name));
    // if (!fileRx.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qCCritical(logcat_statistics, "Cannot read tx_bytes");
    //     return;
    // }
    // QTextStream streamRx(&fileRx);
    // streamRx >> bytes;
    // mSpeedDownTotal->update(bytes);
}
