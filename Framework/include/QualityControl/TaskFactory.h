///
/// \file   TaskFactory.h
/// \author Barthelemy von Haller
///

#ifndef QUALITYCONTROL_LIBS_CORE_TASKFACTORY_H_
#define QUALITYCONTROL_LIBS_CORE_TASKFACTORY_H_

#include <iostream>
#include <memory>
// O2
#include <Common/Exceptions.h>
#include "QualityControl/TaskConfig.h"
#include "QualityControl/TaskDevice.h"

namespace o2 {
namespace quality_control {
namespace core {

class TaskInterface;

class ObjectsManager;

/// \brief Factory in charge of creating tasks
///
/// The factory needs a library name and a class name provided as an object of type TaskConfig.
/// The class loaded in the library must inherit from TaskInterface.
class TaskFactory
{
  public:
    TaskFactory();
    virtual ~TaskFactory();

    /// \brief Create a new instance of a TaskInterface.
    /// The TaskInterface actual class is decided based on the parameters passed.
    /// \todo make it static ?
    /// \author Barthelemy von Haller
    TaskInterface *create(TaskConfig &taskConfig, std::shared_ptr<ObjectsManager> objectsManager);
};

} // namespace core
} // namespace QualityControl
} // namespace o2

#endif // QUALITYCONTROL_LIBS_CORE_TASKFACTORY_H_
