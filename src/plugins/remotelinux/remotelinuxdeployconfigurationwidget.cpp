/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/
#include "remotelinuxdeployconfigurationwidget.h"
#include "ui_remotelinuxdeployconfigurationwidget.h"

#include "remotelinuxdeployconfiguration.h"
#include "remotelinuxdeploymentdatamodel.h"

#include <projectexplorer/project.h>
#include <projectexplorer/target.h>
#include <utils/qtcassert.h>

using namespace ProjectExplorer;

namespace RemoteLinux {
namespace Internal {

class RemoteLinuxDeployConfigurationWidgetPrivate
{
public:
    Ui::RemoteLinuxDeployConfigurationWidget ui;
    RemoteLinuxDeployConfiguration *deployConfiguration;
    RemoteLinuxDeploymentDataModel deploymentDataModel;
};

} // namespace Internal

using namespace Internal;

RemoteLinuxDeployConfigurationWidget::RemoteLinuxDeployConfigurationWidget(QWidget *parent) :
    DeployConfigurationWidget(parent), d(new RemoteLinuxDeployConfigurationWidgetPrivate)
{
    d->ui.setupUi(this);
    d->ui.deploymentDataView->setTextElideMode(Qt::ElideMiddle);
    d->ui.deploymentDataView->setWordWrap(false);
    d->ui.deploymentDataView->setUniformRowHeights(true);
    d->ui.deploymentDataView->setModel(&d->deploymentDataModel);
}

RemoteLinuxDeployConfigurationWidget::~RemoteLinuxDeployConfigurationWidget()
{
    delete d;
}

void RemoteLinuxDeployConfigurationWidget::init(DeployConfiguration *dc)
{
    d->deployConfiguration = qobject_cast<RemoteLinuxDeployConfiguration *>(dc);
    QTC_ASSERT(d->deployConfiguration, return);

    connect(dc->target()->project(), SIGNAL(buildSystemEvaluated()),
            SLOT(updateDeploymentDataModel()));
    updateDeploymentDataModel();
}

void RemoteLinuxDeployConfigurationWidget::updateDeploymentDataModel()
{
    d->deploymentDataModel.setDeploymentData(d->deployConfiguration->target()->deploymentData());
    d->ui.deploymentDataView->resizeColumnToContents(0);
}

} // namespace RemoteLinux
